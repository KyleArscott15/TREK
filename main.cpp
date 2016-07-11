#include "user_input.h"
#include "knowledge_base.h"
#include "inference_engine.h"
#include "shell.h"

int main() {
  UserInput ui;
  WorkingMemory   wm;
  KnowledgeBase   kb;
  InferenceEngine ie(&kb);

  Shell sh(&ui, &wm, &ie);

  sh.run();

  return 0;
}

