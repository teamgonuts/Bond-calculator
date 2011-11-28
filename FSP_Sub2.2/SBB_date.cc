#include "SBB_date.h"

static int
is_leap(int year)
{
	// valid range is 1 AD and later
	return (year & 0x03) == 0 && ((year % 100) != 0 || (year % 400) == 0);  
}

static int
get_month_length(int is_leap, int month)
{
	static int month_lengths[2][13] = {
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
	};
	
	if(month < 1 || month > 12) {
		fprintf(stderr," invalid month passed to get_month_length(...): %d\n", month);
		// SBB throw
		return SBB_ERROR;
	}

	return month_lengths[is_leap ? 1 : 0][month];
} 

void
SBB_date::set_from_yyyymmdd(long yyyymmdd) 
{
	_day = yyyymmdd % 100;	
	if(_day < 1 || _day > 31){
		fprintf(stderr,"invalid day (passed in long date %d) -  %d)\n", 
		yyyymmdd, _day);
	}
	yyyymmdd /= 100; // strip days
	_month = yyyymmdd % 100;
	if(_month < 1 || _month > 12){
		fprintf(stderr,"invalid month (passed in long date %d) - %d\n", 
		yyyymmdd, _month);
	}
	_year = yyyymmdd / 100;
}

void
SBB_date::add_months(int number) 
{
	if(number >= 0){
		_month += (char) (number % 12);
	}
	else
	{
		_month -= (char) ((-number) % 12);
	}

	_year += (short) (number / 12);

	while( _month > DECEMBER) { 
		_month -= DECEMBER;
		++_year;
	}

	while( _month < JANUARY) {
		_month += DECEMBER;
		--_year;
	}

	while( _month > DECEMBER) {
		_month -= DECEMBER;
		++_year;
	}

	while( _month < JANUARY) {
		_month += DECEMBER;
		--_year;
	}

	// SBB set or clip to last day of month if necessary.
	// should not be called since all mat dates given are on 15th (avoid end of month adjustments)
	int dim = get_month_length(is_leap(_year), _month);
	if( _day > dim) {
		_day = dim;
	}

	if(!is_valid()) {
		// throw error - invalid date!
		// SBB_throw("SBB_date::add_months produced invalid date
		fprintf(stderr,"SBB_date::add_months(...) produced invalid date\n");
		// set null
	}
}

int 
SBB_date::is_valid()
{
	return 
		_year >= SBB_FIRST_VALID_YEAR &&
		_month >= JANUARY &&
		_month <= DECEMBER &&
		_day >= 1 &&
		_day <= get_month_length(is_leap(_year), _month);
}
