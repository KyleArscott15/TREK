#include "working_memory.h"

WorkingMemory::WorkingMemory() {
  // add in sessional information to initialize the working memory
#define SESSION_DURATION_MINUTES "session duration minutes"
  wmStateAccess(WM_ADD, SESSION_DURATION_MINUTES, All_type(65));
}

WorkingMemory::~WorkingMemory() {}

All_type WorkingMemory::wmStateAccess(
  WORKING_MEMORY_ACTION action,
  string                state,
  All_type              optional_value) {
  switch (action) {
  case (WM_EXISTS): {
    break;
  };

  case (WM_ADD): {
    // if (wmStateAccess(WM_EXISTS, state, optional_value)) {
    // return All_type(-1); // ALREADY_EXISTS;
    // }
    stateTable[state] = optional_value;
    break;
  };

  case (WM_REMOVE): {
    break;
  };

  case (WM_GET): {
    return stateTable[state];
  };

  case (WM_SET): {
    break;
  };

  default: {
    printf("Default for %s\n", __FUNCTION__);
  };
  }

  return All_type(-1);
}

int  WorkingMemory::wmListAccess(
  WORKING_MEMORY_ACTION action,
  Frame                *frame,
  All_type              optional_value) {
  switch (action) {
  case (WM_EXISTS): {
    break;
  };

  case (WM_ADD): {
    printf("Adding [%s][%s] to list.\n",
           frame->getName().c_str(), optional_value.atToString(
             ).c_str());

    packingList.addFrame(*frame);
    break;
  };

  case (WM_REMOVE): {
    break;
  };

  case (WM_GET): {
    break;
  };

  case (WM_SET): {
    break;
  };

  default: {
    printf("Default for %s\n", __FUNCTION__);
  };
  }

  return SUCCESS;
}

All_type WorkingMemory::getStateValue(void *input) {
  All_type all(6);

  return all;
}

int WorkingMemory::printMemoryDump() {
  cout << endl;
  cout << "WORKING MEMORY" << endl;
  HLINE();

  cout << "State Table: " << endl;

  for (StateTable::iterator it = stateTable.begin(); it != stateTable.end();
       ++it) {
    cout << it->first << " => " << it->second << '\n';
  }

  HLINE();

  return SUCCESS;
}

int WorkingMemory::printList() {
  return packingList.printList();
}

