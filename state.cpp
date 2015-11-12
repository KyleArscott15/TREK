#include <state.h>

State::State(){}
State::~State(){}

//------------------------------------------------------------------------------

IntegerState::IntegerState(){
}
IntegerState::~IntegerState(){
}

STATE_TYPE IntegerState::getStateType(){
	return INTEGER_STATE;
}

//------------------------------------------------------------------------------

RangeState::RangeState(int min, int max) : min_value(min), max_value(max){
}
RangeState::~RangeState(){
}

STATE_TYPE RangeState::getStateType(){
	return RANGE_STATE;
}

int RangeState::setValue(int value){
	if(value > max_value  || value < min_value){
		return -1;
	}else{
		state_value = value;
	}
}

//------------------------------------------------------------------------------

BooleanState::BooleanState() : RangeState(0,1) {
}

BooleanState::~BooleanState() {
}

STATE_TYPE BooleanState::getStateType(){
	return BOOLEAN_STATE;
}

//------------------------------------------------------------------------------


