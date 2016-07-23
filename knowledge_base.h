#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <vector>

#include "top_level_inclusions.h"
#include "working_memory.h"
#include "frame.h"

#define RULE_IF(rule_name, condition)     \
  bool rule_name::evaluateAntecendant() { \
    return ((condition));                 \
  }

#define RULE_AC(rule_name, action)   \
  bool rule_name::evaluateAction() { \
    ((action));                      \
    return true;                     \
  }

typedef enum Rule_Property {
  ONE_SHOT = 0,
  PRIORITY = 1
} RuleProperty;
#define RULE_PROPERTY(rule_name, property, value) \
  int rule_name::setProperties() {                \
    properties[((property))] = ((value));         \
    return SUCCESS;                               \
  }

#define RULE_DEFINE(rule_name, format, prompt, response_type) \
  class rule_name : public Rule {                             \
public:                                                       \
      rule_name() {                                           \
      responseType = response_type;                           \
      setFormat(format);                                      \
      setPrompt(prompt);                                      \
    }                                                         \
    bool evaluateAntecendant();                               \
    bool evaluateAction();                                    \
protected:                                                    \
private:                                                      \
  }

#define RULE_DEFINE_PROP(rule_name, format, prompt, response_type) \
  class rule_name : public Rule {                                  \
public:                                                            \
    rule_name() {                                                  \
      responseType = response_type;                                \
      setFormat(format);                                           \
      setPrompt(prompt);                                           \
    }                                                              \
    bool evaluateAntecendant();                                    \
    bool evaluateAction();                                         \
    int setProperties();                                           \
protected:                                                         \
private:                                                           \
  }

#define RULE_DEFINE_PROP_(rule_name, format, prompt, response_type) \
  class rule_name : public Rule {                                   \
public:                                                             \
    rule_name() {                                                   \
      responseType = response_type;                                 \
      setFormat(format);                                            \
      setPrompt(prompt);                                            \
    }                                                               \
    bool evaluateAntecendant();                                     \
    bool evaluateAction();                                          \
    int setProperties();                                            \
protected:                                                          \
private:                                                            \
  }

#define RULE (rule_name, format, prompt, response_type, condition, action) { \
    RULE_DEFINE_PROP(rule_name, format, prompt, response_type);              \
    RULE_PROPERTY(rule_name, ONE_SHOT, true);                                \
    RULE_IF(rule_name, condition);                                           \
    RULE_AC(rule_name, action);                                              \
}

#define INPUT_RULE(rule_name, prompt, response_type, savedValue) { \
    RULE_DEFINE_PROP(rule_name, "%s\n", prompt, response_type);    \
    RULE_PROPERTY(rule_name, ONE_SHOT, true);                      \
}

class Rule;

class KnowledgeBase { // xxx TODO :public Singleton{
public:

  KnowledgeBase();
  ~KnowledgeBase();
  static map<string, Frame> frames;
  vector<Rule *>contendingRules();

protected:

private:

  static map<string, Frame>initializeFrames();
  int                      initializeRules();

  vector<Rule *> rules;
};

/*
   class A {
   public:

   virtual void print_me(void) {
    std::cout << "I'm A" << std::endl;
   }

   virtual ~A() {}
   };
 */

/*
   class Rule : public WorkingMemory {
   public:

   virtual bool evaluateAntecendant() {
   return false;
   }

   virtual ~Rule() {}
   };
 */

/*
   class B : public A {
   public:

   virtual void print_me(void) {
    std::cout << "I'm B" << std::endl;
   }
   };
 */

/*
   class HikeDistanceRule : public Rule {
   public:

   virtual bool evaluateAntecendant() {
    return true;
   }
   };
 */

class Rule {
public:

  Rule() {}

  virtual ~Rule() {}

  virtual bool evaluateAntecendant() {
    return false;
  }

  virtual bool evaluateAction() {
    return false;
  }

  virtual int setProperties() {
    return ERROR;
  }

  virtual int setPromptResponseToWM(All_type at, WorkingMemory *wm) {
    return -1;
  }

  int setPrompt(char *input_prompt);
  int setPrompt(string input_prompt);
  int setFormat(char *input_format);
  int setFormat(string input_format);
  string prompt;
  string format;
  TYPE   responseType;

  virtual string getPrompt() {
    return string("money");
  }

  TYPE getResponseType() {
    return responseType;
  }

  // int is either
  // a) bool (0 false, 1 true)
  // b) the integer literal
  // c) an index to a string
  map<RuleProperty, int> properties;

protected:

private:
};

class HikeDistanceRule : public Rule {
public:

  HikeDistanceRule();

  ~HikeDistanceRule();

  virtual bool   evaluateAntecendant();
  virtual bool   evaluateAction();
  virtual int    setProperties();
  virtual int    setPromptResponseToWM(All_type       at,
                                       WorkingMemory *wm);
  virtual string getPrompt();

protected:

private:
};


// Ways to access WM
#define F(item) (&KnowledgeBase::frames[item])

// states
#define NUM_NIGHTS             "kayaktrue"
#define HIKE_DISTANCE_M        "hdist" // used internally to differentiate
                                       // states,
                                       // does not matter to user

#endif // ifndef KNOWLEDGE_H
