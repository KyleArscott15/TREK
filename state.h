#ifndef STATE_HEADER
#define STATE_HEADER

#include <top_level_inclusions.h>
#include <tuple>

/*
class CLASSNAME{
public:
	CLASSNAME();
	~CLASSNAME(){};
	int method1(char *input1);
	int method2(char *input2);
protected:
private:
	std::string field1;
};

CLASSNAME::CLASSNAME(){
}

int CLASSNAME::method1(char *input1){
	field1 = std::string(input1);
}
*/

enum STATE_TYPE
{
	INVALID_STATE = 0,
	INTEGER_STATE,
	STRING_STATE,
	BOOLEAN_STATE,
	RANGE_STATE,
	MULTI_STATE // 2 or more of the following states rolled into one
};

enum TIER_TYPE
{
	INVALID_TIER = 0,
	ABSTRACT_DATA_TIER,
	ABSTRACT_DATA_USE_TIER,
	IMPLEMENTED_TIER
};

class State{
public:
	State();
	~State();
        virtual STATE_TYPE getStateType()=0;
protected:
private:
	STATE_TYPE state_type;
	All_type state_value; // only has a value if STATE_TYPE != MULTI_STATE
	std::vector<State*> sub_states; // only used if STATE_TYPE == MULTI_STATE
};

//------------------------------------------------------------------------------

class IntegerState : public State{
public:
	IntegerState();
	~IntegerState();
	virtual STATE_TYPE getStateType();
	virtual int getValue(){return state_value;}
	virtual int setValue()=0;//xxx KA it would make sense to make this non-v
				//irtual, but we want range to limit it now and
				// we want IntegerState to be abstract
protected:
	int state_value;
private:
};

//------------------------------------------------------------------------------

class RangeState : public IntegerState{
public:
	RangeState(int min, int max);
	~RangeState();
	virtual STATE_TYPE getStateType();
	virtual int setValue(int value);
protected:
private:
	int min_value;
	int max_value;
};

//------------------------------------------------------------------------------

class BooleanState : public RangeState{
public:
	BooleanState();
	~BooleanState();
	virtual STATE_TYPE getStateType();
protected:
private:
};

//------------------------------------------------------------------------------

#endif
