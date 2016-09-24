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
#define WM_CONTENTS string("wm")
#define PRINT_LIST string("list")

class Shell {
public:

  Shell(UserInput       *user_input,
        WorkingMemory   *working_memory,
        InferenceEngine *inference_engine);
  ~Shell();
  void   run();
  string getBuiltInCommands();

protected:

private:

  int  beginConsultation();
  int  endConsultation();
  int  usage();
  int  help();
  int  wmContents();
  int  printList();
  int  recognizeBuiltIn(string response);
  bool ruleNull(Rule *rule);

  UserInput *ui;
  WorkingMemory   *wm;
  InferenceEngine *ie;
};

#endif // ifndef SHELL_H
