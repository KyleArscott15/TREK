#include "working_memory.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

DNAMESPACE();

WorkingMemory::WorkingMemory() {
  // add in sessional information to initialize the working memory
#define SESSION_DURATION_MINUTES "session duration minutes"
  wmStateAccess(WM_ADD, SESSION_DURATION_MINUTES, All_type(65));

  latex = new Latex();
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
    D(MEM, "Adding [%s][%s] to wm.\n", state.c_str(),
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
      D(MEM, "Adding [%s][%s] to list.\n",
      frame->getName().c_str(), optional_value.atToString(
        ).c_str());

    // if the frame is a collection frame, then unpack the collection
    // and add each frame individually
    if (frame->isCollection()) {
      D(MEM, "Frame [%s] is a collection.\n", frame->getName().c_str());

      vector<Frame> collection = frame->getCollection();

      // iterate through each item and add them recursively to the packing list
      for (vector<Frame>::iterator it = collection.begin(); it != collection.end();
           ++it) {
        wmListAccess(WM_ADD, &(*it), All_type(-1));
      }
    } else {
      packingList.addFrame(*frame, optional_value);
    }

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
  /*
     std::ofstream ofs;

     ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
   */

  latex->savePackingList(
    packingList.getPackingList(), packingList.getPackingListOptional());

  int fd = open(
    filename.c_str(),
    O_WRONLY | O_CREAT | O_TRUNC,
    S_IWGRP  | S_IRGRP | S_IRUSR | S_IWUSR);

  string list = packingList.returnList();
  char   buffer[list.length()];

  bzero(buffer, list.length());
  memcpy(buffer, list.c_str(), list.length());
  write(fd, buffer, strlen(buffer));
  close(fd);

  // ofs.close();
}

