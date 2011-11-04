#include <stdio.h>
#include "SBB_ratings.h"
#include <string.h>

//
//	Ratings table with (thinned) ratings from both ratings agencies 
//	*includes "expected loss" and "probability of default" data
//
//                      Standard & Poors/Fitch
//
//	 Moody's	S&P/Fitch 	Grade 		Risk    		EL	PD	 
//
static BOND_RATINGS bond_ratings_table[] = {

	"Aaa",		"AAA",		"Investment",	"Highest Quality   ",	0,	0,
	"Aa",		"AA",		"Investment",	"High Quality      ",	0,	0,
	"A",		"A",		"Investment",	"Strong            ",	0,	0,
	"Baa",		"BBB",		"Investment",	"Medium Grade      ",	0,	0,
	"Ba",		"BB",		"Junk      ",	"Speculative       ",	1,	5,
	"B",		"B",		"Junk      ",	"Speculative       ",	10,	20,
	"Caa2",		"CCC",		"Junk      ",	"Highly Speculative",	20,	40,
	"Caa3",		"CC",		"Junk      ",	"Highly Speculative",	30,	70,
	"Ca",		"C",		"Junk      ",	"Highly Speculative",	50,	100,
	"C",		"D",		"Junk      ",	"In Default        ",	100,	100
};

SBB_bond_ratings::SBB_bond_ratings() 
{
	_table_count = sizeof(bond_ratings_table) / sizeof(BOND_RATINGS);
	//printf("table row count is: %d\n", _table_count);

	_quality_code_namespace_s_and_p = new char*[ _table_count ];

	for(int i=0;i<_table_count;i++){
		_quality_code_namespace_s_and_p[i] = bond_ratings_table[i].s_and_p_fitch;
	}
};

const
BOND_RATINGS* 
SBB_bond_ratings::get_ratings_record(char* s_and_p_code)
const
{
	// do linear search through static array and return a pointer to the struct to be able to access
	// fields Grade, Ris, etc.
	for(int i=0;i<_table_count;i++){
		if(0==strcmp(bond_ratings_table[i].s_and_p_fitch, s_and_p_code)){
			return &bond_ratings_table[i];
		}
	}
	fprintf(stderr,"ERROR no match for code: %s!\n", s_and_p_code);
	// if no match
	return NULL;
}

void
SBB_bond_ratings::free_list_of_codes()
{
	delete[] _quality_code_namespace_s_and_p;
}


SBB_bond_ratings::~SBB_bond_ratings() 
{
	// in case caller instantiates this class on stack and falls out of scope, don't delete memory here - make caller do it
	// delete[] _quality_code_namespace_s_and_p;
};


void 
SBB_bond_ratings::show()
const
{
	printf("\n========================================== BOND RATINGS INFO ======================================\n");
	printf("Moodys\tS&P/Fitch\tGrade\t\t\tRisk\t\t\t\tEL\t\tPD\n");
	printf("___________________________________________________________________\n");
	for(int i=0;i<_table_count;i++){

		printf("%s\t%s\t\t%s\t\t%s\t\t%.0f\t\t%.0f\n",
			bond_ratings_table[i].moody,
			bond_ratings_table[i].s_and_p_fitch,
			bond_ratings_table[i].grade,
			bond_ratings_table[i].risk,
			bond_ratings_table[i].EL,
			bond_ratings_table[i].PD
			);
	}
	printf("===================================================================================================\n");
}

//
// Expected Loss "EL" 
// Probability of Default "PD"
// Loss Given Default "LGD"
//
// EL = PD * LGD
//
// for each rating we'll assume a PD and LGD, thus EL will be constant
// however I'll implement so PD and LGD could overwrite the values in the table
// for future expandability
//

char** 
SBB_bond_ratings::get_quality_code_namespace_s_and_p(int& count) 
const
{
	count = _table_count;
	return _quality_code_namespace_s_and_p;
}

double
SBB_bond_ratings::LGD_given_SnP_Fitch(const char* code)
const
{
	// linear search through table to find PD and EL, and solve for LGD
	bool found =  false;
	double LGD = -1;
	for(int i=0;i<_table_count;i++){
		BOND_RATINGS* ptr = &bond_ratings_table[i];
		if( 0==strcmp(ptr->s_and_p_fitch, code ) ){
			if(0==ptr->PD){
				LGD=0;	// so don't divide by 0
			}
			else {
				LGD = ptr->EL / ptr->PD;
			}
			found = true;
		}
	}
	if(!found){
		fprintf(stderr,"ERROR %s not found in ratings table! in func: %s\n", 	
			code, __PRETTY_FUNCTION__);
		LGD = -1;
	}
	return LGD;
}

//
// to compile this, add -DTEST_DRIVER on compile line e.g., : "g++ SBB_ratings.cc -DTEST_DRIVER"
// then execute "a.out 2> error_logfile" to test 
// if error_logfile is empty we passed the tests ok...
//
#ifdef TEST_DRIVER
main()
{
	SBB_bond_ratings ratings;
	ratings.show();

	// get first entry
	const char* highest_quality = "AAA";
	double expected_LGD_highest_quality = 0;

	const char* just_above_default = "C";
	double expected_LGD_just_above_default = .5;

	const char* in_default = "D";
	double expected_LGD_in_default = 1;

	double LGD;

	LGD=ratings.LGD_given_SnP_Fitch(highest_quality);
	printf("LGD for code: %s is: %.2f\n",  highest_quality, LGD);
	if(LGD !=  expected_LGD_highest_quality){
		fprintf(stderr,"TEST DRIVER FAILED! - got LGD: %f expected: %f\n", 
			LGD, 
			expected_LGD_highest_quality);
	}

	LGD=ratings.LGD_given_SnP_Fitch(just_above_default);
	printf("LGD for code: %s is: %.2f\n",  just_above_default, ratings.LGD_given_SnP_Fitch(just_above_default));
	if(LGD != expected_LGD_just_above_default){
		fprintf(stderr,"TEST DRIVER FAILED! - got LGD: %f expected: %f\n", 
			LGD, 
			expected_LGD_just_above_default);
	}

	LGD=ratings.LGD_given_SnP_Fitch(in_default);
	printf("LGD for code: %s is: %.2f\n",  in_default, LGD);
	if(LGD != expected_LGD_in_default){
		fprintf(stderr,"TEST DRIVER FAILED! - got LGD: %f expected: %f\n", 
			LGD, 
			expected_LGD_in_default);
	}
}
#endif
