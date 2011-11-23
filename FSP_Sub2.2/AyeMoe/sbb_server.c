#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "BondPrice_calculator.h"
#include <math.h>
#include "SBB_util.h"
#include <string.h>
#include "SBB_ratings.h"
#include <fstream>
#include "sbb_socket.h"

main(int argc, const char* arg[])
{
	/* 
	 * get an internet domain socket 
	 */
	int sd;
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* 
	 * set up the socket structure 
	 */
	struct sockaddr_in	sock_addr;

	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;

#ifdef SBB_ANY
	/* set to INADDR_ANY if want server to be open to any client on any machine */
	sock_addr.sin_addr.s_addr = INADDR_ANY;
#else
	char	hostname[128];
	/*
	 *  we'll default to this host and call a section 3 func to get this host
	 */
	if( gethostname(hostname,sizeof(hostname)) ){
		fprintf(stderr," SBB gethostname(...) failed errno: %d\n", errno);
		exit(1);
	}
	printf("SBB gethostname() local hostname: \"%s\"\n", hostname);

	/*
	 * set up socket structure for our host machine
	 */
	struct hostent *hp;
	if ((hp = gethostbyname(hostname)) == 0) {
		fprintf(stderr,"SBB gethostbyname(...) failed errno: %d exiting...\n", errno);
		exit(1);
	}
	sock_addr.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
#endif
	sock_addr.sin_port = htons(PORT);

	/* 
	 * bind the socket to the port number 
	 */
	if (bind(sd, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) == -1) {
		perror("bind");
		exit(1);
	}

	/* 
	 * advertise we are available on this socket/port
	 */
	if (listen(sd, 5) == -1) {
		perror("listen");
		exit(1);
	}

	/* 
	 * wait for a client to connect 
	 */
	struct sockaddr_in	sock_addr_from_client;
        socklen_t addrlen = sizeof(sock_addr_from_client); 
	int sd_current;
	if ((sd_current = accept(sd, (struct sockaddr *)  &sock_addr_from_client, &addrlen)) == -1) {
		fprintf(stderr,"SBB accept(...) failed errno: %d  exiting...\n", errno);
		exit(1);
	}
	printf("SBB client ip address: %s port: %x\n",
		inet_ntoa(sock_addr_from_client.sin_addr),
		PORT);

//		ntohs(sock_addr_from_client.sin_port));

	/*
	 * block on socket waiting for client message
	 */
	int ret = 0;
        char	msg[MSGSIZE];
	fprintf(stderr," SBB: sizeof msg: %d\n", sizeof(msg));

	while (ret = recv(sd_current, msg, sizeof(msg), 0) > 0) {
        	printf("SBB server received msg: [%s] from client\n", msg);
        
        /*
         * read in the tradingbook.txt and perform calculation
         */
        
        //start the timer
        double realtime = 0.0, usertime = 0.0, systemtime = 0.0;
        SBB_util timer;
        timer.start_clock();
        
        
        //get the opening and closing trading book from the arguments
        std::string _opening_book_filename = arg[1];
        std::string _closing_book_filename = arg[2];
        
        SBB_instrument_input_file _opening_trading_file(_opening_book_filename.c_str());
        SBB_instrument_input_file _closing_trading_file(_closing_book_filename.c_str());
        

        int _opening_book_records_count = _opening_trading_file.get_record_count();
        int _closinging_book_records_count = _closing_trading_file.get_record_count();
        
        
        SBB_instrument_fields* _opening_book_fields = _opening_trading_file.get_records(_opening_book_records_count); //load the opening trading book
        SBB_instrument_fields* _closing_book_fields = _closing_trading_file.get_records(_closinging_book_records_count); //load the closing trading book
        
        //SBB_instrument_fields* _yc_fields = yieldFile.get_records(yield_record_count);//load the yield file
        SBB_bond_ratings bond_ratings;
        
        double _total_opening_lgd = 0.0; //total portfolio LGD at the start of the day aka opening trading book
        double _total_closing_lgd = 0.0; //total portfolio LGD at the end of the day aka closing trading book
        double _total_opening_portfolio_amount = 0.0; //total portfolio amount at the start of the day
        double _total_closing_portfolio_amount = 0.0; //total portfolio amount at the end of the day
        
        for(int i = 0 ; i < _opening_book_records_count ; i++){
             
            //Get LGD from start of the day
            double _opening_bond_lgd = bond_ratings.LGD_given_SnP_Fitch(_opening_book_fields[i].Quality.c_str());//get the LGD from the array using bond's rating
            _total_opening_lgd += (_opening_bond_lgd * _opening_book_fields[i].Amount); //calculate total LGD by multiplying LGD with the amount
            
            //Get LGD from end of the day
            double _closing_bond_lgd = bond_ratings.LGD_given_SnP_Fitch(_closing_book_fields[i].Quality.c_str());
            _total_closing_lgd += (_closing_bond_lgd * _closing_book_fields[i].Amount);
            
            //this is temporary output for debugging
            printf("Opening lgd amount : %s %.3f %.3f \n",_opening_book_fields[i].SecurityID, _opening_bond_lgd, _opening_bond_lgd * _opening_book_fields[i].Amount);
            printf("Closing lgd amount : %s %.3f %.3f \n",_closing_book_fields[i].SecurityID, _closing_bond_lgd, _closing_bond_lgd * _closing_book_fields[i].Amount);
            
            //Get total portfolio amount for beginning of the day and end of the day
            _total_opening_portfolio_amount += _opening_book_fields[i].Amount;
            _total_closing_portfolio_amount += _closing_book_fields[i].Amount;
            
            
        }
        double _lgd_change = _total_opening_lgd - _total_closing_lgd;
        printf("LGD change : %.3f\n", _lgd_change);
        
        double _portfolio_amt_change = _total_opening_portfolio_amount - _total_closing_portfolio_amount;
        printf("Portfolio Amount change : %.3f\n", _portfolio_amt_change);
        
        
        timer.end_clock(realtime, usertime, systemtime);
        /* 
		 * ack back to the client 
		 */
        sprintf (msg, "%.3f %.3f %.3f %.3f %.3f %.3f", 0.0, _lgd_change,_portfolio_amt_change, realtime, usertime, systemtime);
        
		//strcpy(msg," this is the server message response!");
		if (send(sd_current, msg, strlen(msg), 0) == -1) {
			fprintf(stderr,"SBB send(...) failed errno: %d exiting...\n", errno);
			exit(1);
		}
	}

	if( 0 == ret ) {
		printf("SBB ciient exited...\n");
		/* For TCP sockets	
		 * the return value 0 means the peer has closed its half side of the connection 
		 */
	}
	else if( -1 == ret ) {
		fprintf(stderr,"SBB recv(...) returned failed - errno: %d exiting...\n", errno);	
		exit(1);
	}

	close(sd_current); 
	close(sd);
}
