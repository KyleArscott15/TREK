#ifndef TYPES_H
#define TYPES_H

#include <string>

#include "error.h"
#include "values.h"

using namespace std;

typedef enum DATA_TYPE {
  TYPE_INVALID = -1,
  TYPE_BOOL    = 0,
  TYPE_INTEGER = 1,
  TYPE_STRING  = 2,
  TYPE_STATE   = 3 // void* in All_type is for this purpose
} TYPE;

class All_type {
public:

  All_type() {
    i    = INVALID_INTEGER;
    b    = INVALID_BOOL;
    type = TYPE_INVALID;
  }

  All_type(int value) {
    type = TYPE_INTEGER;
    i    = value;
  }

  All_type(char *str) {
    type = TYPE_STRING;
    s    = string(str);
  }

  ~All_type() {}

  TYPE   type;
  string s;
  int    i;
  bool   b;
  void  *state;

private:
};

#endif // ifndef TYPES_H
