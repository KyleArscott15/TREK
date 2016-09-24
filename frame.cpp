#include <frame.h>

Frame::Frame() {
  collectionFrame = false;
  setQuantity(1);
  setUserNotes("");
}

Frame::~Frame() {}

int Frame::setName(string frameName) {
  int ret = frameName.length();

  name = frameName;
  return ret;
}

int Frame::setName(char *frameName) {
  int ret = name.length();

  name = string(frameName);
  return ret;
}

int Frame::addSlot(char *slot_name, char *unit, All_type default_val) {
  Slot slot(slot_name, unit, default_val);

  slots.push_back(slot);
}

bool Frame::setUserNotes(string notes) {
  userNotesAboutFrame = notes;
  return true;
}

