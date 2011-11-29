#include "BondPrice_calculator.h"

 /*
double BondPrice_calculator::calculate_price(Bond* bond, double yield_rate){
    
       
    double total_num_of_periods = years_to_maturity * bond->Frequency;
    double yield_adjusted = 0.0;
   
    if(yield_rate == NULL){
        //std::cout << "Yield Rate : "<< bond->YieldRate <<std::endl;
        
        yield_adjusted = bond->YieldRate/(100*bond->Frequency);
        //std::cout << "Yield Adjusted : "<<yield_adjusted<<std::endl;
        
    }else{
        //std::cout << "Yield Rate 2 : "<< yield_rate <<std::endl;
        
        yield_adjusted = yield_rate/(100*bond->Frequency);
        
    }
    //std::cout << "yield_adjusted : "<< yield_adjusted <<std::endl;
    double pv_factor = 1/pow(1+yield_adjusted, total_num_of_periods);
    //std::cout << "pv_factor : "<< pv_factor <<std::endl;
    
    if(bond->getCoupon()== 0.0){ //zero coupon
        
        double principal_term = (100 * pv_factor);
        bond->Price = principal_term;
        return bond->Price;

    }else{
        double coupon_adjusted = bond->getCoupon()/(100*bond->Frequency);
        //std::cout << "coupon_adjusted : "<<coupon_adjusted <<std::endl;
        double pv_factor = 1/pow((1+yield_adjusted), total_num_of_periods);
        double coupon_factor = (1-pv_factor)/yield_adjusted;
        //std::cout << "coupon_factor : "<< coupon_factor <<std::endl;
        
        double coupon_term = coupon_factor * coupon_adjusted * 100;//has to multiple by 100 because coupon_adjusted needs to be in %
        //std::cout << "coupon_term : "<< coupon_term <<std::endl;
        
        double principal_term = (100 * pv_factor);
        //std::cout << "principal_term : "<< principal_term <<std::endl;
        
        bond->Price = coupon_term + principal_term;
        return bond->Price;

    }
   
    }
  */
double Zero_Coupon_Calculator::calculate_price(){
    double yield_adjusted = yield/(100*frequency);
    int total_num_of_periods = yearsToMature * frequency;
    
    double pv_factor = 1/pow(1+yield_adjusted, total_num_of_periods);
    
    double principal_term = (100 * pv_factor);
    return principal_term;
}

double Coupon_Bond_Calculator::calculate_price(){
    double yield_adjusted = yield/(100*frequency);
    int total_num_of_periods = yearsToMature * frequency;
    
    double coupon_adjusted = CouponRate/(100*frequency);
    double pv_factor = 1/pow((1+yield_adjusted), total_num_of_periods);
    double coupon_factor = (1-pv_factor)/yield_adjusted;
    
    double coupon_term = coupon_factor * coupon_adjusted * 100;//has to multiple by 100 because coupon_adjusted needs to be in %
    
    double principal_term = (100 * pv_factor);
    return coupon_term + principal_term;

}

int BondPrice_calculator::calculate_years_to_maturity(int SettlementDate, int MaturityDate){
    //find the number of years to maturity
    SBB_date sDate; 
    SBB_date mDate;
    sDate.set_from_yyyymmdd(SettlementDate);
    mDate.set_from_yyyymmdd(MaturityDate);
    int years_to_maturity = 0;
    //printf("Settlement Date %d \n", SettlementDate);
    //printf("Maturity Date %d \n", MaturityDate);
    while (sDate != mDate) {
		mDate.add_months(-12);
		years_to_maturity++;
	}
    return years_to_maturity;

}


double BondPrice_calculator::calculate_dv01(){
    yield = yield+0.01;
    double price_down = calculate_price();
    //printf("Price after 1% yield is %.2f\n", price_down);
    yield = yield-0.02;
    double price_up = calculate_price();
    //printf("Price after -1% yield is %.2f\n", price_up);
    
    return ((100 - price_down)+(price_up - 100))/2;
}

