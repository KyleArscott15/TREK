#include "working_memory.h"

PromptHistory::PromptHistory() {}

PromptHistory::~PromptHistory() {}

PackingList::PackingList() {}

PackingList::~PackingList() {}

static StateTable initializeInitialStateTable() {
  StateTable st;

  // st[SESSION_DURATION] = new IntegerState(SESSION_DURATION);
  return st;
}

static StateTable initial_state_table = initializeInitialStateTable();

WorkingMemory::WorkingMemory() {
  // add in sessional information to initialize the working memory
#define SESSION_DURATION_MINUTES "session duration minutes"
  wmStateAccess(WM_ADD, SESSION_DURATION_MINUTES, 65);
}

WorkingMemory::~WorkingMemory() {}

int WorkingMemory::wmStateAccess(
  WORKING_MEMORY_ACTION action,
  string                state,
  All_type              optional_value) {
  switch (action) {
  case (WM_EXISTS): {
    break;
  };

  case (WM_ADD): {
    if (wmStateAccess(WM_EXISTS, state, optional_value)) {
      return ALREADY_EXISTS;
    }

    stateTable[state] = optional_value;
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

int WorkingMemory::wmListAccess(
  WORKING_MEMORY_ACTION action,
  string                state,
  All_type              optional_value) {
  switch (action) {
  case (WM_EXISTS): {
    break;
  };

  case (WM_ADD): {
    if (wmStateAccess(WM_EXISTS, state, optional_value)) {
      return ALREADY_EXISTS;
    }

    stateTable[state] = optional_value;
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

