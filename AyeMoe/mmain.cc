//  BondPricing
//
//  Created by Aye Sandar Moe on 9/25/11.
#include <iostream>
#include "BondPrice_calculator.h"
#include <math.h>
#include <SBB_util.h>
#include <string.h>
#include <SBB_ratings.h>
#include <fstream>
using namespace std;

#define SBB_INSTRUMENT_ID_LENGTH 32
#define SBB_INSTRUMENT_RATETYPE_LENGTH 7
#define SBB_INSTRUMENT_TICKER_LENGTH 2
#define SBB_INSTRUMENT_QUALITY_LENGTH 3



int main(int argc, const char* arg[])
{
    //start the timer
    SBB_util timer;
    timer.start_clock();
    
    string tradingFile = arg[1];
    string yield = arg[2];
    
    SBB_instrument_input_file inputFile(tradingFile.c_str());
    SBB_instrument_input_file yieldFile(yield.c_str());
    
    ofstream outputTradingBookFile("tradingbook.txt");
    ofstream outputResultFile("results.txt");
    
    outputTradingBookFile << "# " <<endl;
    outputTradingBookFile << "# Aye Moe (N14398710) " <<endl;
    outputTradingBookFile << "# asm422" <<endl;
    outputTradingBookFile << "# " <<endl;
    outputTradingBookFile << "# " <<endl;
    outputTradingBookFile << "# " <<endl;
    
    outputResultFile << "# " <<endl;
    outputResultFile << "# Aye Moe (N14398710) " <<endl;
    outputResultFile << "# asm422" <<endl;
    outputResultFile << "# " <<endl;
    outputResultFile << "# " <<endl;
    outputResultFile << "# " <<endl;
    
    BondPrice_calculator* priceCalculator;
    
    int record_count = inputFile.get_record_count();
    int yield_record_count = yieldFile.get_record_count();
    
    //printf("input file record count is %d \n", record_count);
    
    SBB_instrument_fields* bonds = inputFile.get_records(record_count); //load the trading book
    SBB_instrument_fields* _yc_fields = yieldFile.get_records(yield_record_count);//load the yield file
    SBB_bond_ratings bond_ratings;
    
    int largestLongIndex = -1;
    int largestShortIndex = -1;
    int riskIndex = -1;
    double totalRisk = 0.0;
    double riskiest = 0.0;

    double price = 0.0;
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
        if(bonds[i].CouponRate == 0.0){
            priceCalculator = new Zero_Coupon_Calculator(yield, bonds[i].Frequency, years_to_maturity);
           
        }
        
        if(bonds[i].CouponRate > 0.0){
            priceCalculator = new Coupon_Bond_Calculator(yield, bonds[i].CouponRate, bonds[i].Frequency, years_to_maturity);
           // cout << priceCalculator->yield << " " << priceCalculator->frequency << " " << priceCalculator->yearsToMature <<endl;
        
        }
        double price = priceCalculator->calculate_price();
       
        double dv01 = priceCalculator->calculate_dv01();
        outputTradingBookFile.precision(3);
        outputTradingBookFile.setf(ios::fixed);
        outputTradingBookFile << bonds[i].SecurityID <<" " <<bonds[i].Ticker << " " << bonds[i].SettlementDate << " ";
        outputTradingBookFile << bonds[i].CouponRate << " " << bonds[i].MaturityDate << " " << bonds[i].Frequency << " ";
        outputTradingBookFile << bonds[i].RateType << " " << bonds[i].YieldRate << " " << bonds[i].Quality << " " ;
        outputTradingBookFile << bonds[i].Amount << " " << price << " " << dv01 <<" " << (dv01/100) * bonds[i].Amount << " ";
        //printf(">> Bond dv01 is %.3f\n", dv01);
        //printf(">> Risk is %.3f\n", (dv01/100) * bonds[i].Amount);
        double lgd = bond_ratings.LGD_given_SnP_Fitch(bonds[i].Quality.c_str());
        //printf(">> lgd %.3f\n", lgd *  bonds[i].Amount);
        outputTradingBookFile << lgd *  bonds[i].Amount << endl;
        double currentPositionRisk = dv01 * bonds[i].Amount;
        if(currentPositionRisk > riskiest){
            riskiest = currentPositionRisk;
            riskIndex = i;
        }
        totalRisk = totalRisk + currentPositionRisk;
        
        if(largestLongIndex == -1 && bonds[i].Amount > 0 ){
            largestLongIndex = i;
        }else{
            if(bonds[i].Amount > 0 && bonds[i].Amount > bonds[largestLongIndex].Amount){
                largestLongIndex = i;
            }
        }
        
        if(largestShortIndex == -1 && bonds[i].Amount < 0 ){
            largestShortIndex = i;
        }else{
            if(bonds[i].Amount < 0 && bonds[i].Amount < bonds[largestShortIndex].Amount){
                largestShortIndex = i;
            }
        }
    }
    outputResultFile.precision(3);
    outputResultFile.setf(ios::fixed);
    outputResultFile << bonds[largestLongIndex].Amount << endl;
    outputResultFile << bonds[largestShortIndex].Amount << endl;
    outputResultFile << riskiest << endl;
    outputResultFile << totalRisk << endl;
    timer.end_clock();
    
    
    return 0;
}

