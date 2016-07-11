#ifndef ERROR_H
#define ERROR_H

#include </usr/include/asm/errno.h>

typedef enum RETURN_VALUE {
  FAILED_ACTION  = 4,
  ALREADY_EXISTS = -3,
  NO_MATCH       = -2, // no string match, no rule match
  ERROR          = -1, // an action did NOT happen or the action was
                       // unsuccessful
  SUCCESS = 0          // an action happened or it wassuccessful
} RET_VAL;

#endif // ifndef ERROR_H
