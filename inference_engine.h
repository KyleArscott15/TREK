#ifndef INFERENCE_ENGINE_H
#define INFERENCE_ENGINE_H

#include "top_level_inclusions.h"
#include "knowledge_base.h"

class InferenceEngine {
public:

  InferenceEngine(KnowledgeBase *knowledgeBase);

  ~InferenceEngine();

  int inferNextRule(Rule         **rule,
                    WorkingMemory *wm);

private:

  KnowledgeBase *kb;
};

#endif // ifndef INFERENCE_ENGINE_H
