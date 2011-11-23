#include "SBB_io.h"

SBB_instrument_input_file::SBB_instrument_input_file(const char * filename)
{
	_file = std::fopen(filename, "r"); // open read-only
	if (!_file){
		fprintf(stderr,"ERROR couldn't open: %s\n", filename);
		throw std::runtime_error("file open failure");
	}
}

SBB_instrument_input_file::~SBB_instrument_input_file() 
{
	if (std::fclose(_file)) {
		fprintf(stderr,"flose failed on file %s errno: %d\n", 
			_file, errno);
	}
}

int
SBB_instrument_input_file::get_record_count()
{
	// not including comments (first char is #) that is...
	// Comments interspersed in data lines is allowed
	int line_count_minus_comments = 0;
	int comment_count = 0;
	while(fgets(_line_buf,SBB_LINE_BUFFER_LENGTH,_file)){
		if('#' == _line_buf[0]) {
			comment_count++;
			continue; // skip through comments
		}
		++line_count_minus_comments;
	}
	//printf("comment count in file: %d\n", comment_count);

	rewind(_file);
	//fseek(_file, 0L, SEEK_SET);

	return line_count_minus_comments;
}

void
SBB_instrument_input_file::free_records()
{
	delete[] _fields_array;
}

SBB_instrument_fields*
SBB_instrument_input_file::get_records(int& length) 
{
	length = get_record_count();//get total number of record

	_fields_array = new SBB_instrument_fields[length];

	if(NULL ==  _fields_array){
		fprintf(stderr,"calloc failed - errno: %d\n", errno);
		return _fields_array;
	}
	int comment_count = 0;

	_line_buf[0] = ' ';
	int non_comments_line_count_read = 0; 
	char *token;
	while(std::fgets(_line_buf,SBB_LINE_BUFFER_LENGTH,_file)){

		//printf("SBB CHECK file line: %s\n", _line_buf);

		if('#' == _line_buf[0]) {
			continue; // skip through comments
			comment_count++;
		}

		// the line should be:
		// SecurityID SettlementDate CouponRate MaturityDate Frequency YieldRate

		// SecurityID
		token = strtok(_line_buf," ");
		if(NULL == token) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		} 
		//printf("SecurityID: %s\n", token);
		strcpy(_fields_array[non_comments_line_count_read].SecurityID, token);

        // Ticker
		token = strtok(NULL," ");
		if(NULL == token) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		}
        //printf("Ticker: %s\n", token);
		strcpy(_fields_array[non_comments_line_count_read].Ticker, token);
    
        
		// SettlementDate
		token = strtok(NULL," ");
		if(NULL == token) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		}
		//printf("SettlementDate: %s\n", token); 
		_fields_array[non_comments_line_count_read].SettlementDate = atoi(token);

		// CouponRate
		token = strtok(NULL," ");
		if(NULL == token ) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		}
		//printf("CouponRate: %s\n", token);
		_fields_array[non_comments_line_count_read].CouponRate = atof(token);

		// MaturityDate
		token = strtok(NULL," ");
		//printf("MaturityDate: %s\n", token);
		_fields_array[non_comments_line_count_read].MaturityDate = atoi(token);				

		// Frequency
		token = strtok(NULL," ");
		//printf("Frequency: %s\n", token);
		_fields_array[non_comments_line_count_read].Frequency = atoi(token);
        
        // RateType
		token = strtok(NULL," ");
		//printf("RateType: %s\n", token);
        _fields_array[non_comments_line_count_read].RateType = token;
		//strcpy(_bonds_array[non_comments_line_count_read].RateType,token);				
        
		// Yield/Rate (later we will load in spread and a string token of an OTR. Also will have a separate file
        
		token = strtok(NULL," ");
		if(NULL == token ) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		}
		//printf("YieldRate is:  %s\n", token);
		_fields_array[non_comments_line_count_read].YieldRate = atof(token);
        
        // Quality
		token = strtok(NULL," ");
		//printf("Quality: %s\n", token);
        _fields_array[non_comments_line_count_read].Quality=token;
		//strcpy(_bonds_array[non_comments_line_count_read].Quality,token);				
        
        //Amount
		token = strtok(NULL," ");
		if(NULL == token ) { 
			fprintf(stderr,"line parsing failed on buf: %s\n", _line_buf); 
			exit(1); 
		}
		//printf("Amount is:  %s\n", token);
		_fields_array[non_comments_line_count_read].Amount = atof(token);
        
        //std::fputs(_line_buf, "aha");
        non_comments_line_count_read++;
	}

	//printf("SBB lines read: %d \n", non_comments_line_count_read);

	return _fields_array;
}

