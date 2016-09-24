#include "user_input.h"
#include "knowledge_base.h"
#include "inference_engine.h"
#include "shell.h"
#include "debug_log.h"

DNAMESPACE();
DINIT();

int main() {
  DMETHOD();

  UserInput ui;
  WorkingMemory   wm;
  KnowledgeBase   kb;
  InferenceEngine ie(&kb);

  DPRINT("Debug Output is on and functional.\n");

  Shell sh(&ui, &wm, &ie);

  sh.run();

  return 0;
}

