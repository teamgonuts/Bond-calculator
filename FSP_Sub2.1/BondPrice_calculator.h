#ifndef BP_CAL.h
#define BP_CAL.h

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "math.h"
#include "SBB_io.h"
#include "SBB_date.h"





/**
 * This class calculates price of a bond
 * In order to calculate bond price, we will need 
 * 1) Determine # of coupon payments
 * 2) Determine value of each coupon payments
 * 3) Deterime the yield
 * 4) Use closed form formula
 */
class BondPrice_calculator{
    
public:
    BondPrice_calculator(double yieldRate, short freq, int yearsToMaturity){
        yield = yieldRate;
        frequency = freq;
        yearsToMature = yearsToMaturity;
    }
    int calculate_years_to_maturity(int SettlementDate, int MaturityDate);
    virtual double calculate_price() = 0;
    double calculate_dv01();
    double yield;
    short frequency;
    int yearsToMature;
};

class Zero_Coupon_Calculator : public BondPrice_calculator{

public:
    Zero_Coupon_Calculator(double y, short f, int ytm) : BondPrice_calculator(y, f, ytm){
    }
    double calculate_price();
    //double calculate_dv01();
};

class Coupon_Bond_Calculator : public BondPrice_calculator{
    
public:
    Coupon_Bond_Calculator(double y, double c, short f, int ytm) :  BondPrice_calculator(y, f,ytm), CouponRate(c){
       
    }
    double calculate_price();
    //double calculate_dv01();
    double CouponRate;
};

#endif