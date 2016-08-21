#ifndef WORKING_MEMORY_H
#define WORKING_MEMORY_H

#include "state.h"
#include "frame.h"

enum WORKING_MEMORY_SECTION {
  WM_STATE          = 1,
  WM_PROMPT_HISTORY = 2,
  WM_PACKING_LIST   = 3
};
enum WORKING_MEMORY_ACTION {
  WM_EXISTS = 1, // can use at any time
  WM_ADD    = 2, // need to add before you can remove, get or set. Adds
                 // the state or item to the working memory
  WM_REMOVE = 3, // can remove only if its added
  WM_GET    = 4, // can get only if its added
  WM_SET    = 5  // can set only if its added
};

// WM specific types
typedef map<string, All_type>StateTable; // XXX KA don't make it a pointer,
                                         // just a normal. Just plain values
                                         // in working memory. Version 1 has
                                         // All_type, version 2 has State
                                         // object
class PromptHistory;
typedef vector<PromptHistory *>HistoryList;

class PromptHistory {
public:

  PromptHistory() {}

  ~PromptHistory() {}

private:

  string raw_response;
  int    prompt_response_id; // from [1, n] where n is number of user prompts
  string date_prompted;      // output of `date`, used to timestamp user
  // response for evidence in court
};

class PackingList {
public:

  PackingList() {}

  ~PackingList() {}

  int addFrame(Frame frame) {
    string frame_name = frame.getName();

    if (packingList.count(frame_name) > 0) {
      return ALREADY_EXISTS;
    }

    packingList[frame_name] = frame;
    return SUCCESS;
  }

  int removeFrame(Frame frame) {
    string frame_name = frame.getName();

    if (packingList.count(frame_name) == 0) {
      return NO_MATCH;
    }
    int num_removed = packingList.erase(frame_name);

    if (num_removed) {
      return SUCCESS;
    } else {
      return FAILED_ACTION;
    }
  }

  string returnList() {
    string list;

    list += string("\n");
    list += string("PACKING LIST\n");
    list += string("Packing List Table: \n");

    for (map<string, Frame>::iterator it = packingList.begin();
         it != packingList.end();
         ++it) {
      list += it->first;
      list += string(" => ");
      list += it->second.getName();
      list += string("\n");
    }

    list += string("\n");

    return list;
  }

  int printList() {
    /*
       cout << endl;
       cout << "PACKING LIST" << endl;
       HLINE();

       cout << "Packing List Table: " << endl;

       for (map<string, Frame>::iterator it = packingList.begin();
         it != packingList.end();
       ++it) {
       cout << it->first << " => " << it->second << '\n';
       }

       HLINE();
       cout << endl;
       cout << endl;
     */

    cout << returnList();

    return SUCCESS;
  }

private:

  map<string, Frame> packingList; // string key is the frame_name of
  // the frame it stores, used a map
  // for fast "existence" queries
};

class WorkingMemory {
public:

  WorkingMemory();
  ~WorkingMemory();

  int printMemoryDump();

  int wmStateAccess(
    WORKING_MEMORY_ACTION action,
    string                state,
    All_type              optional_value);

  int wmListAccess(
    WORKING_MEMORY_ACTION action,
    Frame                *frame,
    All_type              optional_value);

  int      printList();
  All_type getStateValue(string state);

  int      saveList(string filename);

private:

  int memoryDump(string& returnString);

  // these are the 3 main sections of the working memory
  StateTable  stateTable;
  HistoryList promptHistory;
  PackingList packingList;
};

#endif // ifndef WORKING_MEMORY_H
