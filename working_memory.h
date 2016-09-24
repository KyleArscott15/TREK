#ifndef WORKING_MEMORY_H
#define WORKING_MEMORY_H

#include "state.h"
#include "frame.h"
#include "top_level_inclusions.h"
#include "latex.h"

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
typedef map<string, All_type>StateTable; // TODO version two should have a State
                                         // object, not an All_type object

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

  int addFrame(Frame frame, All_type optional_value) {
    string frame_name = frame.getName();

    if (packingList.count(frame_name) > 0) {
      return ALREADY_EXISTS;
    }

    packingList[frame_name] = frame;

    packingListOptional[frame_name] = optional_value;
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
      list += it->second.getName();
      list += string(" => ");
      list += packingListOptional[it->first].atToString();
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

  map<string, Frame>getPackingList() {
    return packingList;
  }

  map<string, All_type>getPackingListOptional() {
    return packingListOptional;
  }

private:

  map<string, Frame>    packingList; // string key is the frame_name of
  map<string, All_type> packingListOptional;

  // the frame it stores, used a map
  // for fast "existence" queries
};

class ListNotes {
public:

  ListNotes() {}

  ~ListNotes() {}

  string addNote(const string& note, All_type optionalValue) {
    notes.push_back(note);
    return note;
  }

  vector<string>getNotes() {
    return notes;
  }

  string getNotesString() {
    int count = 0;
    string noteString;

    for (vector<string>::iterator it = notes.begin();
         it != notes.end();
         ++it, count++) {
      noteString += string(to_string(count));
      noteString += string(". ");
      noteString += *it;
      noteString += "\n";
    }
    return noteString;
  }

private:

  vector<string> notes;
};

class WorkingMemory {
public:

  WorkingMemory();
  ~WorkingMemory();

  int printMemoryDump();

  int wmStateAccess(
    WORKING_MEMORY_ACTION action,
    string                state,
    All_type              optionalValue);

  int wmListAccess(
    WORKING_MEMORY_ACTION action,
    Frame                *frame,
    All_type              optionalValue);

  int wmNoteAccess(
    WORKING_MEMORY_ACTION action,
    const string        & note,
    All_type              optionalValue);

  int      printList();
  All_type getStateValue(string state);

  int      saveList(string filename);

private:

  int memoryDump(string& returnString);

  // these are the 4 main sections of the working memory
  StateTable  stateTable;
  HistoryList promptHistory;
  PackingList packingList;
  ListNotes   listNotes;

  // output objects for final document
  Latex latex;
};

#endif // ifndef WORKING_MEMORY_H
