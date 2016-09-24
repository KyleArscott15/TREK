#ifndef FRAME_H
#define FRAME_H

#include "top_level_inclusions.h"

enum SLOT_INFO {
  SLOT_TYPE = 0,
  SLOT_DEFAULT_VALUE,
  SLOT_NAME
};

class Slot {
public:

  Slot(char    *slot_name,
       char    *slot_unit,
       All_type slot_default_val) {
    name        = string(slot_name);
    unit        = string(unit);
    default_val = slot_default_val;
  }

  virtual ~Slot() {}

  // return value in either an All_type returned or modify given pointer
  // If the pointer option is used then the returned All_type returns errors
  All_type get(SLOT_INFO get_type,
               All_type *at = NULL);

  // set a parameter of this slot based on what's in the All_type
  int set(SLOT_INFO set_type,
          All_type *at);

  //	boost::function() callback_procedure; // pg. 234 BES:AT

private:

  string   name;
  string   unit; // ex. "km"
  All_type value;
  All_type default_val;
};

class Frame {
public:

  Frame();
  ~Frame();

  string getName() {
    return name;
  }

  int setName(string frameName);
  int setName(char *frameName);
  int addSlot(char    *slot_name,
              char    *unit,
              All_type default_val);

  bool isCollection() {
    return collectionFrame;
  }

  vector<Frame>getCollection() {
    return collection;
  }

  bool setCollection(vector<Frame>newCollection) {
    bool wasCollectionFrameBefore = collectionFrame;

    collection      = newCollection;
    collectionFrame = true;
    return wasCollectionFrameBefore;
  }

  friend ostream& operator<<(ostream    & os,
                             const Frame& frame);

  string          getUserNote() {
    return userNotesAboutFrame;
  }

  uint getQuantity() {
    return quantity;
  }

  bool setUserNotes(string notes);

  uint setQuantity(uint newQuantity) {
    int ret = quantity;

    quantity = newQuantity;
    return ret;
  }

private:

  // true if this frame is actually a grouping of other frames
  bool collectionFrame;
  vector<Frame> collection;

  vector<Slot> slots;         // call-back functions to perform calculations
  string name;                // same string as the index into the frames map to
                              // retrieve this frame
  string userNotesAboutFrame; // merely pasted into final packing list for user
                              // information
  uint quantity;              // number of items to bring. ex. bring 2
                              // waterbottles for 2 people
  uint massInGrams;           // used for weight calculation for hiking
  uint volumeInLitres;        // used for determining how much you can pack into
                              // your kayak or backpack
  int sizeInt;                // generic number, depends on units in sizeUnits.
                              // ex. sizeInt = 13, sizeUnits = US mens shoe size
  string sizeIntUnits;        // paired with sizeInt to give supporting
                              // information
  string sizeString;          // generic string, ex. a shirt can be XXL
};

inline ostream& operator<<(ostream& out, const Frame& frame) {
  out << frame.name;
  return out;
}

#endif // FRAME_H
