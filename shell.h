#ifndef SHELL_H
#define SHELL_H

#include "top_level_inclusions.h"
#include "state.h"
#include "frame.h"
#include "user_input.h"
#include "knowledge_base.h"
#include "inference_engine.h"

// built-in functions
#define DOC string("doc")
#define EXIT string("exit")
#define HELP string("help")

class Shell {
public:

  Shell(UserInput       *user_input,
        WorkingMemory   *working_memory,
        InferenceEngine *inference_engine);
  ~Shell();
  void run();

protected:

private:

  int beginConsultation();
  int endConsultation();
  int usage();
  int help();
  int recognizeBuiltIn(string response);

  UserInput *ui;
  WorkingMemory   *wm;
  InferenceEngine *ie;
};

#endif // ifndef SHELL_H
