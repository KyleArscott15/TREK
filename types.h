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

  friend ostream& operator<<(ostream       & os,
                             const All_type& at);

  TYPE            getType() {
    return type;
  }

  TYPE   type;
  string s;
  int    i;
  bool   b;
  void  *state;

private:
};

inline ostream& operator<<(ostream& out, const All_type& at) {
  if (at.type == TYPE_BOOL) {
    out << at.b;
  } else if (at.type == TYPE_STRING) {
    out << at.s;
  } else if (at.type == TYPE_INTEGER) {
    out << at.i;
  } else {
    out << "null";
  }
  return out;
}

#endif // ifndef TYPES_H
