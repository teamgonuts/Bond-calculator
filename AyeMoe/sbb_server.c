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

main()
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
        double realtime = 0.0, usertime = 0.0, systemtime = 0.0;
        SBB_util timer;
        timer.start_clock();
        
        std::string tradingFile = "tradingbook1.txt";
        std::string yield = "yieldcurve.txt";
        
        SBB_instrument_input_file inputFile(tradingFile.c_str());
        SBB_instrument_input_file yieldFile(yield.c_str());
        
        BondPrice_calculator* priceCalculator;
        
        int record_count = inputFile.get_record_count();
        int yield_record_count = yieldFile.get_record_count();
        
        //printf("input file record count is %d \n", record_count);
        
        SBB_instrument_fields* bonds = inputFile.get_records(record_count); //load the trading book
        SBB_instrument_fields* _yc_fields = yieldFile.get_records(yield_record_count);//load the yield file
        
        double totalBucketRisk = 0.0; //total risk of the bonds in 10-30 yr bucket
        double totalMarketValue_yieldUp = 0.0; //total market value of portfolio after 100 bp yield up
        double totalMarketValue_yieldDown = 0.0; //total market value of portfolio after 100bp yiled down
        double dv01_2yrT = 0.0; //dv01 of 2 yr T bonds
        
        /*
         * Find dv01 of 2 year Treasury bonds
         */
        for(int index = 0 ; index < yield_record_count; index++){
            if(strcmp(_yc_fields[index].SecurityID, "T2") == 0){
                if(_yc_fields[index].CouponRate > 0.0){
                    priceCalculator = new Coupon_Bond_Calculator(_yc_fields[index].YieldRate,_yc_fields[index].CouponRate, _yc_fields[index].Frequency, 2);
                }else{
                    priceCalculator = new Zero_Coupon_Calculator(_yc_fields[index].YieldRate, _yc_fields[index].Frequency, 2);
                }
                dv01_2yrT = priceCalculator->calculate_dv01();
                printf("2Yr T dv01 is %f \n", dv01_2yrT);
            }
        }
        
        for(int i = 0 ; i < record_count ; i++){
            //bonds[i].show();
            
            //first find the years to maturity
            int years_to_maturity = priceCalculator->calculate_years_to_maturity(bonds[i].SettlementDate, bonds[i].MaturityDate);
            double yield = bonds[i].YieldRate;
          
            if(strcmp(bonds[i].RateType.c_str(), "SPREAD") == 0){
                
                double spread = bonds[i].YieldRate;
                int closet_months_to_treasury;
                for(int index = 0 ; index < yield_record_count; index++){
                    
                    //find the number of months to treasury 
                    SBB_date bmDate; 
                    SBB_date ymDate;
                    bmDate.set_from_yyyymmdd(bonds[i].MaturityDate);
                    ymDate.set_from_yyyymmdd(_yc_fields[index].MaturityDate);
                    int months_to_treasury = 0;
                    if(bmDate <= ymDate){
                        while (bmDate != ymDate) {
                            bmDate.add_months(1);
                            months_to_treasury++;
                        }
                    }
                    if(bmDate >= ymDate){
                        while (bmDate != ymDate) {
                            bmDate.add_months(-1);
                            months_to_treasury++;
                        }
                    }
                    if(index == 0){
                        closet_months_to_treasury = months_to_treasury;
                        yield = _yc_fields[index].YieldRate + (spread * 0.01);
                    }else{
                        if(months_to_treasury < closet_months_to_treasury){
                            closet_months_to_treasury = months_to_treasury;
                            yield = _yc_fields[index].YieldRate + ( spread * 0.01);
                        }
                    }
                }
                
                
            }
            
            if(bonds[i].CouponRate == 0.0){ //100 basis point = 1%
                priceCalculator = new Zero_Coupon_Calculator(yield + 0.01, bonds[i].Frequency, years_to_maturity);
                
            }
            
            if(bonds[i].CouponRate > 0.0){
                priceCalculator = new Coupon_Bond_Calculator(yield + 0.01, bonds[i].CouponRate, bonds[i].Frequency, years_to_maturity);
                
            }
            double price_yieldup = priceCalculator->calculate_price();
            totalMarketValue_yieldUp += price_yieldup * bonds[i].Amount;
            
            //now decrease 100 basis point
            //priceCalculator.yield = yield - 0.01;
            if(bonds[i].CouponRate == 0.0){ //100 basis point = 1%
                priceCalculator = new Zero_Coupon_Calculator(yield - 0.01, bonds[i].Frequency, years_to_maturity);
                //priceCalculator.yield = yield - 0.01;
                
            }
            
            if(bonds[i].CouponRate > 0.0){
                priceCalculator = new Coupon_Bond_Calculator(yield - 0.01, bonds[i].CouponRate, bonds[i].Frequency, years_to_maturity);
                
            }
            double price_yielddown = priceCalculator->calculate_price();
            totalMarketValue_yieldDown += price_yielddown * bonds[i].Amount;
            
            
            if(years_to_maturity >= 10 && years_to_maturity < 30){
                if(bonds[i].CouponRate == 0.0){ //100 basis point = 1%
                    priceCalculator = new Zero_Coupon_Calculator(yield, bonds[i].Frequency, years_to_maturity);
                }
                
                if(bonds[i].CouponRate > 0.0){
                    priceCalculator = new Coupon_Bond_Calculator(yield, bonds[i].CouponRate, bonds[i].Frequency, years_to_maturity);
                }
                
                totalBucketRisk += priceCalculator->calculate_dv01() * bonds[i].Amount;

            }
        }
        
        double numOf2YrBond = totalBucketRisk/dv01_2yrT;
        
        timer.end_clock(realtime, usertime, systemtime);
        /* 
		 * ack back to the client 
		 */
        sprintf (msg, "%.3f %.3f %.3f %.3f %.3f %.3f", totalMarketValue_yieldUp, totalMarketValue_yieldDown,numOf2YrBond, realtime, usertime, systemtime);

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
