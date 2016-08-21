#ifndef STATE_HEADER
#define STATE_HEADER

#include <tuple>

#include "top_level_inclusions.h"

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

// XXX KA State objects will not be used in version 1
class State {
public:

  State();
  State(const char *unique_identifier);
  ~State();
  virtual STATE_TYPE getStateType() {
    return INVALID_STATE;
  }

protected:

private:

  string state_unique_identifier;
  STATE_TYPE state_type;
  All_type   state_value; // only has a value if STATE_TYPE !=
                          // MULTI_STATE
  // vector<State *> sub_states; // only used if STATE_TYPE == MULTI_STATE
};

class IntegerState : public State {
public:

  IntegerState(const char *unique_identifier);
  ~IntegerState();
  virtual STATE_TYPE getStateType();
  virtual int        getValue() {
    return state_value;
  }

  virtual int setValue() {}

protected:

  int state_value;

private:
};

class RangeState : public IntegerState {
public:

  RangeState(const char *unique_identifier,
             int         min,
             int         max);
  ~RangeState();
  virtual STATE_TYPE getStateType();
  virtual int        setValue(int value);

protected:

private:

  int min_value;
  int max_value;
};

class BooleanState : public RangeState {
public:

  BooleanState(const char *unique_identifier);
  ~BooleanState();
  virtual STATE_TYPE getStateType();

protected:

private:
};

#endif // ifndef STATE_HEADER
