#include "inference_engine.h"

InferenceEngine::InferenceEngine(KnowledgeBase *knowledgeBase) {
  kb = knowledgeBase;
}

InferenceEngine::~InferenceEngine() {}

int InferenceEngine::inferNextRule(Rule **rule, WorkingMemory *wm) {
  vector<Rule *> ruleSet = kb->contendingRules(wm);

  if (ruleSet.size() > 0) {
    *rule = ruleSet[0];

    // inference algorithm: take the first rule you get
    if ((*rule)->evaluateAntecendant(wm)) {
      return SUCCESS;
    }
  }
  return NO_MATCH;
}

