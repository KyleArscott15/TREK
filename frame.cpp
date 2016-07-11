#include <frame.h>

Frame::Frame() {}

Frame::~Frame() {}

int Frame::setName(char *frame_name) {
  int ret = name.length();

  name = string(frame_name);
  return ret;
}

int Frame::addSlot(char *slot_name, char *unit, All_type default_val) {
  Slot slot(slot_name, unit, default_val);

  slots.push_back(slot);
}

