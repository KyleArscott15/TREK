#include "working_memory.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

WorkingMemory::WorkingMemory() {
  // add in sessional information to initialize the working memory
#define SESSION_DURATION_MINUTES "session duration minutes"
  wmStateAccess(WM_ADD, SESSION_DURATION_MINUTES, All_type(65));
}

WorkingMemory::~WorkingMemory() {}

int WorkingMemory::wmStateAccess(
  WORKING_MEMORY_ACTION action,
  string                state,
  All_type              optional_value) {
  switch (action) {
  case (WM_EXISTS): {
    if (stateTable.count(state) > 0) {
      return true;
    } else {
      return false;
    }
  };

  case (WM_ADD): {
    // if (wmStateAccess(WM_EXISTS, state, optional_value)) {
    //  return ALREADY_EXISTS;
    // }
    printf("Adding [%s][%s] to wm.\n", state.c_str(),
           optional_value.atToString().c_str());
    stateTable[state] = optional_value;
    break;
  };

  case (WM_REMOVE): {
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

All_type WorkingMemory::getStateValue(string state) {
  All_type atReturn;

  if (stateTable.count(state) == 0) {
    // if you query for something that is not there,
    // like the statement below, you will create it
    atReturn.type = TYPE_INVALID;
  } else {
    atReturn = stateTable[state];
  }
  return atReturn;
}

int WorkingMemory::printMemoryDump() {
  string s;

  return memoryDump(s);
}

int WorkingMemory::memoryDump(string& returnString) {
  string output;

  cout << endl;
  cout << "WORKING MEMORY" << endl;

  // HLINE();

  cout << "State Table: " << endl;

  for (StateTable::iterator it = stateTable.begin(); it != stateTable.end();
       ++it) {
    cout << it->first << " => " << it->second << '\n';
  }

  // HLINE();
  cout << endl;
  cout << endl;

  // cout << output;

  // if (returnString != NULL) {
  //  returnString = output;
  // }

  return SUCCESS;
}

int WorkingMemory::printList() {
  return packingList.printList();
}

int WorkingMemory::saveList(string filename) {
  int fd = open(
    filename.c_str(), O_WRONLY | O_CREAT | S_IWGRP | S_IRGRP | S_IRUSR | S_IWUSR); //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // xxx
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // KA
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // why
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // does
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // this
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // not
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // create
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // correct
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   //
                                                                                   // permissions?
  char buffer[2048];

  bzero(buffer, 2048);
  char *h = "hello there friend\n";
  memcpy(buffer, h, strlen(h));
  write(fd, buffer, strlen(buffer));
  close(fd);
}

