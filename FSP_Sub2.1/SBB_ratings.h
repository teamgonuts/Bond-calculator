#ifndef SBB_BOND_RATINGS_H
#define SBB_BOND_RATINGS_H

typedef
struct bond_ratings_info {
	char* moody;
	char* s_and_p_fitch;
	char* grade;
	char* risk;
	double EL;
	double PD;
} BOND_RATINGS;

class SBB_bond_ratings {
	public:
		SBB_bond_ratings();
		~SBB_bond_ratings();

		//
		// returns an array of pointers to the quality code strings which will be 
		// our primary key to search into the ratings table...
		//
		char** get_quality_code_namespace(int& count) const {
			return get_quality_code_namespace_s_and_p(count);
		}
			
		//
		// Once you have the quality code array, pass individual codes from it to access
		// the rest of the  table data
		//
		const BOND_RATINGS* get_ratings_record(char* s_and_p_code) const;
	
		//
		// Caller's responsibility to free memory when done with this object
		// 
		void free_list_of_codes();
		
		// 
		// Returns he Loss Given Default given quality code
		//
		double LGD_given_SnP_Fitch(const char* code) const;

		void show() const;

	private:
		// We will use S&P codes from the ratings table (not moody's)
		// This mf returns an array of strings that we'll use to search for rest of data
		// (e.g., probability of default, expected loss)
		char** get_quality_code_namespace_s_and_p(int& count) const;

		char** _quality_code_namespace_s_and_p;
		int _table_count;
};

/****
   example call:
	SBB_bond_ratings ratings;
	ratings.show();

	int quality_code_count;
	char** quality_codes = ratings.get_quality_code_namespace(quality_code_count);
	for(int i=0;i< quality_code_count;i++){
		printf("quality code: %d is: %s\n", i, quality_codes[i] );	
	}
****/

#endif
