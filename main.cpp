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

  DPRINT("Hello DARLING.\n"); // xxx KA

  Shell sh(&ui, &wm, &ie);

  sh.run();

  return 0;
}

