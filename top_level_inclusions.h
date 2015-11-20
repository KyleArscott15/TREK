#ifndef STANDARD_INCLUSION_H
#define STANDARD_INCLUSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // bzero
#include <string>
#include <vector>
#include <map>
#include <boost/function.hpp>

#define GENERIC_SUCCESS         (0)  // functions return this value if an action happened and/or it was successful
#define GENERIC_ERROR           (-1) // functions return this value if an action did NOT happen and/or the action was unsuccessful
#define STRING_LENGTH           (128)
#define RESPONSE_LENGTH         (64)
#define SCANF_FORMAT_LENGTH     (16)
#define SCANF_SUCCESS           (1)

#define INVALID_INTEGER         (-1)
#define INVALID_BOOL            (false)

#define HLINE(){ \
	 printf("==================================================\n"); \
}

typedef boost::function<int(void)> builtin_func_t;
typedef std::map<std::string,builtin_func_t> builtin_t;

enum DATA_TYPE{
	TYPE_INVALID = -1,
	TYPE_BOOL = 0,
	TYPE_INTEGER = 1,
	TYPE_STRING = 2,
	TYPE_STATE = 3 // void* in All_type is for this purpose
};

class All_type{
public:
	All_type(){
		i = INVALID_INTEGER;
		b = INVALID_BOOL;
		type = TYPE_INVALID;
	}
	
	All_type(int value){
		type = TYPE_INTEGER;
		i = value;
	}

	All_type(char* str){
		type = TYPE_STRING;
		s = std::string(str);
	}

	~All_type(){
	}

	std::string s;
	int i;
	bool b;	
	void *state;
	DATA_TYPE type;
private:
};

#endif // STANDARD_INCLUSION_H
