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
#include <map>
#include <vector>
#include <algorithm>
#include "sbb_socket.h"

int calculateIndex(double confidenceInterval, int count){
    //printf("confidenceInterval %d \n", confidenceInterval);
    //printf("count %d \n", count);
    
    int indexIntoPnLVector = (count - ((confidenceInterval/100)* count)) - 1;  //has to deduct 1 because index starts from 0
    //printf("Index into PnL Vector %d \n", indexIntoPnLVector);
    return indexIntoPnLVector;
}


struct VaR{
    double total_VaR;//total VaR
    double creditRisk_component;//credit risk component of VaR
    double interestRisk_component;//interest risk component of VaR
    
};

struct _by_totalVar{
    bool operator()(VaR const &a, VaR const &b) { 
        return a.total_VaR < b.total_VaR;
    }
    
};

struct _by_CR_Var{
    bool operator()(VaR const &a, VaR const &b) { 
        return a.creditRisk_component < b.creditRisk_component;
    }
    
};

struct _by_IR_Var{
    bool operator()(VaR const &a, VaR const &b) { 
        return a.interestRisk_component < b.interestRisk_component;
    }
    
};

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
        
        
        //SBB_instrument_input_file _opening_trading_file((char*)arg[1]);//get opening trading book file name from run.sh
        SBB_instrument_input_file _closing_trading_file((char*)arg[2]);//get closing trading book file name from run.sh
        SBB_instrument_input_file yieldFile((char*)arg[3]);//get yieldcurve.txt from run.sh
        
        int _opening_book_records_count = 0;
        int _closinging_book_records_count = 0;
        int yield_record_count = 0;
        
        
        //SBB_instrument_fields* _opening_book_fields = _opening_trading_file.get_records(_opening_book_records_count); //load the opening trading book
        SBB_instrument_fields* _closing_book_fields = _closing_trading_file.get_records(_closinging_book_records_count); //load the closing trading book
        
        //printf("_opening_book_records_count..%d \n", _opening_book_records_count);
        //printf("_closinging_book_records_count..%d \n", _closinging_book_records_count);
        SBB_instrument_fields* _yc_fields = yieldFile.get_records(yield_record_count);//load the yield file
        
        /*
        SBB_bond_ratings bond_ratings;
        
        double _total_opening_lgd_amount_adjusted = 0.0; //total portfolio LGD at the start of the day aka opening trading book
        double _total_closing_lgd_amount_adjusted = 0.0; //total portfolio LGD at the end of the day aka closing trading book
        double _total_opening_portfolio_amount = 0.0; //total portfolio amount at the start of the day
        double _total_closing_portfolio_amount = 0.0; //total portfolio amount at the end of the day
        */
        
        std::vector<double> _t2_file; //create a map that holds the treasury data for T2
        std::vector<double> _t5_file; //create a map that holds the treasury data for T5
        std::vector<double> _t10_file; //create a map that holds the treasury data for T10
        std::vector<double> _t30_file; //create a map that holds the treasury data for T30
        
        std::vector<VaR> bookVector;//trading book vector for PnL calculation
        
        for(int i = 0 ; i < _closinging_book_records_count ; i++){
            
            //std::cout<< _closing_book_fields[i].SecurityID ;
            
            //Get LGD from start of the day
            //_total_opening_lgd_amount_adjusted += (bond_ratings.LGD_given_SnP_Fitch(_opening_book_fields[i].Quality.c_str()) * _opening_book_fields[i].Amount); //calculate total LGD by multiplying LGD with the amount
            
            //Get LGD from end of the day
            //_total_closing_lgd_amount_adjusted += (bond_ratings.LGD_given_SnP_Fitch(_closing_book_fields[i].Quality.c_str())  * _closing_book_fields[i].Amount);
            
            //this is temporary output for debugging
            //printf("Opening lgd amount : %s %.3f %.3f \n",_opening_book_fields[i].SecurityID, _opening_bond_lgd, _opening_bond_lgd * _opening_book_fields[i].Amount);
            //printf("Closing lgd amount : %s %.3f %.3f \n",_closing_book_fields[i].SecurityID, _closing_bond_lgd, _closing_bond_lgd * _closing_book_fields[i].Amount);
            
            //Get total portfolio amount for beginning of the day and end of the day
           // _total_opening_portfolio_amount += _opening_book_fields[i].Amount;
            //_total_closing_portfolio_amount += _closing_book_fields[i].Amount;
            
            /** BASE PRICE CALCULATION ***/
            
            //Calculate the years to matuirty of this security using closing trading book Settlement Date and Maturity Date
            BondPrice_calculator* priceCalculator;
            int years_to_maturity = priceCalculator->calculate_years_to_maturity(_closing_book_fields[i].SettlementDate, _closing_book_fields[i].MaturityDate);
            //printf("Years to maturity %d \n", years_to_maturity);
            
            double yield_closing = _closing_book_fields[i].YieldRate;
            if(strcmp(_closing_book_fields[i].RateType.c_str(), "SPREAD") == 0){//if RateType is SPREAD
                
                double spread = _closing_book_fields[i].YieldRate;
                int closet_months_to_treasury;
                for(int index = 0 ; index < yield_record_count; index++){
                    
                    //find the number of months to treasury 
                    SBB_date bmDate; 
                    SBB_date ymDate;
                    bmDate.set_from_yyyymmdd(_closing_book_fields[i].MaturityDate);
                    ymDate.set_from_yyyymmdd(_yc_fields[index].MaturityDate);
                    int months_to_treasury = 0;
                    /*
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
                    }*/
                    months_to_treasury = bmDate.calculate_date_difference(ymDate);
                    if(index == 0){
                        closet_months_to_treasury = months_to_treasury;
                        yield_closing = _yc_fields[index].YieldRate + (spread * 0.01);
                    }else{
                        if(months_to_treasury < closet_months_to_treasury){
                            closet_months_to_treasury = months_to_treasury;
                            yield_closing = _yc_fields[index].YieldRate + ( spread * 0.01);
                        }
                    }
                }
                
                
            }
            if(_closing_book_fields[i].CouponRate == 0.0){
                priceCalculator = new Zero_Coupon_Calculator(yield_closing, _closing_book_fields[i].Frequency, years_to_maturity);
                
            }
            
            if(_closing_book_fields[i].CouponRate > 0.0){
                priceCalculator = new Coupon_Bond_Calculator(yield_closing, _closing_book_fields[i].CouponRate, _closing_book_fields[i].Frequency, years_to_maturity);
                // cout << priceCalculator->yield << " " << priceCalculator->frequency << " " << priceCalculator->yearsToMature <<endl;
                
            }
            double basePrice = priceCalculator->calculate_price();
            //printf("***** Base Price is %.3f \n", basePrice);
            /*** END OF BASE PRICE CALCULATION **** /
             
             
             /*
             * Get the historic data file name and open the files
             */
            std::string security_filename =  _closing_book_fields[i].SecurityID;
            std::string filename = arg[4] + security_filename + ".txt";
            SBB_instrument_input_file _historical_file((char*)filename.c_str());
            
            int _historical_data_count = 0;
            SBB_instrument_fields* _historic_data = _historical_file.get_historic_records(_historical_data_count);
            
            /*
             * Determine whether or not the historical file contain YIELD or SPREAD
             */
            bool _is_yield = true;
            
            if(_historical_data_count > 1){
                if(strcmp(_historic_data[0].RateType.c_str(), "YIELD") == 0){
                    _is_yield = true;
                }else{
                    _is_yield = false;
                    
                    std::string _treasury_filename = arg[4];
                    
                    if(_historic_data[0].BenchmarkTicker.compare("T2") == 0){
                        //printf("Initializing T2...\n");
                        
                        _treasury_filename += "T2.txt";
                        SBB_instrument_input_file _treasury_file((char*)_treasury_filename.c_str());
                        
                        _treasury_file.initialize_treasury_values(_t2_file); //initialize the historic t2 files data
                        
                    }else if(_historic_data[0].BenchmarkTicker.compare("T5") == 0){
                        
                        //printf("Initializing T5...\n");
                        
                        _treasury_filename += "T5.txt";
                        SBB_instrument_input_file _treasury_file((char*)_treasury_filename.c_str());
                        
                        _treasury_file.initialize_treasury_values(_t5_file); //initialize the historic t5 files data
                        
                    }else if(_historic_data[0].BenchmarkTicker.compare("T10") == 0){
                        //printf("Initializing T10...\n");
                        
                        _treasury_filename += "T10.txt";
                        SBB_instrument_input_file _treasury_file((char*)_treasury_filename.c_str());
                        
                        _treasury_file.initialize_treasury_values(_t10_file); //initialize the historic t10 files data
                        
                    }else if(_historic_data[0].BenchmarkTicker.compare("T30") == 0){
                        //printf("Initializing T30...\n");
                        
                        _treasury_filename += "T30.txt";
                        SBB_instrument_input_file _treasury_file((char*)_treasury_filename.c_str());
                        
                        _treasury_file.initialize_treasury_values(_t30_file); //initialize the historic t30 files data
                    }   
                }
            }
            
            /*
             * If this is the first time, then initalize our trading book vector to 0.0 for calculation,
             
             if(bookVector.size() <= 0){
             bookVector.assign(_historical_data_count,0.0);
             }
             */
            //loop through 
            double prev_price = 0.0;
            double prev_yield = 0.0;
            std::vector<VaR> _PnL_Vector; //using full pricing
            
            /*
            if(_is_yield){
                std::cout<< " Yield Case  .. Closing Yield/Spread :  "<<_closing_book_fields[i].YieldRate <<"\n" ;
            }else{
                std::cout<< " Spread Case . Closing Yield/Spread :  "<<_closing_book_fields[i].YieldRate <<"\n" ;
            }*/
            
            /** VaR calculation according his lecture ***/
            for(int j = 0; j < _historical_data_count ; j++){
                double yield = 0.0;
                double historic_yield_diff = 0.0;
                double yield_diff = 0.0;                            
                
                if( j == 0){
                    prev_yield = _historic_data[j].YieldRate;
                }
                historic_yield_diff = _historic_data[j].YieldRate - prev_yield;
                //printf("BP change is %.3f \n", bp_diff);
                
                if(_is_yield){ //if the historic file is YIELD, then just use that yield rate 
                    yield = yield_closing + historic_yield_diff;
                }else{ //if the historic file is SPREAD, then get the corresponding YIELD from T2 file, and add the corresponding spread
                    //printf("............ %d \n", _historic_data[j].SettlementDate-1);
                    
                    //here historic_yield_diff is in base point instead of in percentage
                    if(j == 0){
                        yield = 0+ yield_closing + (historic_yield_diff/100);
                    }else{
                        //std::string benchmark = _historic_data[j].BenchmarkTicker;
                        //benchmark = benchmark.erase(benchmark.length()-1);
                        //printf("Bench mark is %s \n", benchmark);
                        if(_historic_data[j].BenchmarkTicker.compare("T2") == 0){
                            yield_diff = _t2_file[j] - _t2_file[(j-1)];
                            //yield = (_t2_file[j] - _t2_file[(j-1)])+ yield_closing + (bp_diff/100);
                            
                        }else if(_historic_data[j].BenchmarkTicker.compare("T5") == 0){
                            yield_diff = _t5_file[j] - _t5_file[(j-1)];
                            //yield = (_t5_file[j] - _t5_file[(j-1)])+ yield_closing + (bp_diff/100); 
                            
                        }else if(_historic_data[j].BenchmarkTicker.compare("T10") == 0){
                            yield_diff = _t10_file[j] - _t10_file[(j-1)];
                            //yield = (_t10_file[j] - _t10_file[(j-1)])+ yield_closing + (bp_diff/100); 
                            
                        }else if(_historic_data[j].BenchmarkTicker.compare("T30") == 0){
                            yield_diff = _t30_file[j] - _t30_file[(j-1)];
                        }  
                        yield = yield_diff + yield_closing + (historic_yield_diff/100); 
                        
                    }
                }
                
                //printf(" Calculated Yield is %.3f ", yield);
                
                if(_closing_book_fields[i].CouponRate == 0.0){
                    
                    priceCalculator = new Zero_Coupon_Calculator(yield, _closing_book_fields[i].Frequency, years_to_maturity);
                }
                
                if(_closing_book_fields[i].CouponRate > 0.0){ 
                    priceCalculator = new Coupon_Bond_Calculator(yield, 
                                                                 _closing_book_fields[i].CouponRate, _closing_book_fields[i].Frequency, years_to_maturity);
                }
               
                
                double newPrice = priceCalculator->calculate_price();
                VaR v;
                v.total_VaR = ((newPrice - basePrice)/100) * _closing_book_fields[i].Amount;
                
                if(_is_yield){
                    //if this is yield case, then we don't need to divide by 100 since yield difference is in percent points
                    priceCalculator->yield = yield_closing + (historic_yield_diff);
                    
                }else{
                    //if this is yield case, then we need to divide by 100 since bp needs to convert to percent points
                    
                    priceCalculator->yield = yield_closing + (historic_yield_diff/100);

                }
                double spreadYield = priceCalculator->yield ; //closing yield + yield difference in corporate file
                //printf("Spread Yield %.3f ", priceCalculator->yield);
                       
                v.creditRisk_component = ((priceCalculator->calculate_price() - basePrice)/100)* _closing_book_fields[i].Amount;//please note that this is in decimal
               
                priceCalculator->yield = yield_closing + yield_diff;
                double corporateYield = priceCalculator->yield ; //closing yield + difference between historic yield in TREASURY FILE;
                //printf("Coporate Yield %.3f ", priceCalculator->yield);
                
                v.interestRisk_component = ((priceCalculator->calculate_price() - basePrice)/100)* _closing_book_fields[i].Amount;
              /* 
                printf("Date: %d Historic Yield %.3f Spread Yield %.3f Coporate Yield %.3f Calculated Yield %.3f PnL is %.3f  CR is %.3f  IR is %.3f \n", 
                       _historic_data[j].SettlementDate, _historic_data[j].YieldRate, spreadYield, corporateYield, yield, v.total_VaR, 
                       v.creditRisk_component,  
                       v.interestRisk_component);*/
                
                _PnL_Vector.push_back(v);
                
                prev_price = newPrice;
                prev_yield = _historic_data[j].YieldRate;
            }
            _historical_file.free_records(); //free the records for the historic data
            //_historical_file.close_file();
            
            
            if(i == 0){
                for(int tindex = 0; tindex < _PnL_Vector.size(); tindex++){
                    bookVector.push_back(_PnL_Vector[tindex]);
                }
            }else{
                for(int tindex = 0; tindex < _PnL_Vector.size(); tindex++){
                    bookVector[tindex].total_VaR = bookVector[tindex].total_VaR + _PnL_Vector[tindex].total_VaR;
                    bookVector[tindex].creditRisk_component = bookVector[tindex].creditRisk_component + _PnL_Vector[tindex].creditRisk_component;
                    bookVector[tindex].interestRisk_component = bookVector[tindex].interestRisk_component + _PnL_Vector[tindex].interestRisk_component;
                   
                    /*
                    printf(" Total VaR is %.3f  Credit component is %.3f  Interest component is %.3f \n", 
                           bookVector[tindex].total_VaR ,
                          bookVector[tindex].creditRisk_component, 
                           bookVector[tindex].interestRisk_component);*/
                }
            }
            
        }
        int index_to_var = calculateIndex(99, bookVector.size());
        //printf("index to var is %d ", index_to_var);
        sort(bookVector.begin(), bookVector.end(),_by_totalVar());
        double _total_var = bookVector[index_to_var].total_VaR;
        
        sort(bookVector.begin(), bookVector.end(),_by_CR_Var());
        double _cr_var = bookVector[index_to_var].creditRisk_component;
        
        sort(bookVector.begin(), bookVector.end(),_by_IR_Var());
        double _ir_var = bookVector[index_to_var].interestRisk_component;
        
        //printf("99 percent confidence interval for total number of %d of %.3f \n", bookVector.size(),_VaR);
        
        //double _lgd_change = _total_opening_lgd_amount_adjusted - _total_closing_lgd_amount_adjusted;
        //printf("LGD change : %.3f\n", _lgd_change);
        
        //double _portfolio_amt_change = _total_opening_portfolio_amount - _total_closing_portfolio_amount;
        //printf("Portfolio Amount change : %.3f\n", _portfolio_amt_change);
        
        
        timer.end_clock(realtime, usertime, systemtime);
        /* 
         * ack back to the client 
         */
        sprintf (msg, "%.3f %.3f %.3f %.3f %.3f %.3f", _total_var/1000, _cr_var/1000,_ir_var/1000, realtime, usertime, systemtime);
        
        //strcpy(msg," this is the server message response!");
        if (send(sd_current, msg, strlen(msg), 0) == -1) {
            fprintf(stderr,"SBB send(...) failed errno: %d exiting...\n", errno);
            exit(1);
        }
    }
    
    if( 0 == ret ) {
        printf("SBB client exited...\n");
        /* For TCP sockets	
         * the return value 0 means the peer has closed its half side of the connection 
         */
        close(sd_current); 

    }else if( -1 == ret ) {
        fprintf(stderr,"SBB recv(...) returned failed - errno: %d exiting...\n", errno);	
        exit(1);
    }
    
    close(sd);
}


