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

class PromptHistory {
public:

  PromptHistory();
  ~PromptHistory();

private:

  string raw_response;
  int    prompt_response_id; // from [1, n] where n is number of user prompts
  string date_prompted;      // output of `date`, used to timestamp user
  // response for evidence in court
};

class PackingList {
public:

  PackingList();
  ~PackingList();
  int addFrame(Frame frame) {
    string frame_name = frame.getName();

    if (packing_list.count(frame_name) > 0) {
      return ALREADY_EXISTS;
    }

    packing_list[frame_name] = frame;
    return SUCCESS;
  }

  int removeFrame(Frame frame) {
    string frame_name = frame.getName();

    if (packing_list.count(frame_name) == 0) {
      return NO_MATCH;
    }
    int num_removed = packing_list.erase(frame_name);

    if (num_removed) {
      return SUCCESS;
    } else {
      return FAILED_ACTION;
    }
  }

private:

  map<string, Frame> packing_list; // string key is the frame_name of
  // the frame it stores, used a map
  // for fast "existence" queries
};

// WM specific types
typedef map<string, All_type>StateTable; // XXX KA don't make it a pointer,
                                         // just a normal. Just plain values
                                         // in working memory. Version 1 has
                                         // All_type, version 2 has State object
typedef vector<PromptHistory *>HistoryList;

class WorkingMemory {
public:

  WorkingMemory();
  ~WorkingMemory();

  int getHikingDistance() {
    return 6;
  }

  int wmStateAccess(
    WORKING_MEMORY_ACTION action,
    string                state,
    All_type              optional_value);

  int wmListAccess(
    WORKING_MEMORY_ACTION action,
    string                state,
    All_type              optional_value) {
private:

    // these are the 3 main sections of the working memory
    StateTable  stateTable;
    HistoryList promptHistory;
    PackingList packingList;

    All_type getStateValue(void *input);
  }

#endif // ifndef WORKING_MEMORY_H
