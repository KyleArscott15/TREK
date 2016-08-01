#include "knowledge_base.h"

int Rule::setPrompt(char *input_prompt)
{
  prompt = string(input_prompt);
}

int Rule::setPrompt(string input_prompt)
{
  prompt = input_prompt;
}

int Rule::setFormat(char *input_format)
{
  format = string(input_format);
}

int Rule::setFormat(string input_format)
{
  format = input_format;
}

KnowledgeBase::KnowledgeBase()
{
  initializeRules();
}

KnowledgeBase::~KnowledgeBase()
{}

map<string,
    Frame>KnowledgeBase:: frames = KnowledgeBase::initializeFrames();

// Frame references
#define BOOTS       string("boots")
#define AQUATABS    string("aqua tabs")
#define BASIC_KAYAKING_LIST string("basic kayaking list")
#define FLOATING_ROPE_50_FT string("floating rope 50ft")
#define KAYAK_PADDLE string("kayak paddle")
#define BAILING_DEVICE string("bailing bucket")
#define LIFE_JACKET string("life jacket")
map<string, Frame>KnowledgeBase::initializeFrames()
{
  map<string, Frame> frames;

  // xxx KA this is application specific code to initialize frames that are
  // useful for TREK only
  Frame
    boots,
    aquatabs,
    floating_rope_50ft,
    whistle,
    kayak_paddle,
    bailing_bucket,
    life_jacket
  ;

  boots.setName(BOOTS);
  All_type shoe_size(13);
  boots.addSlot((char *)"shoe size", (char *)"US", shoe_size);

  aquatabs.setName(AQUATABS);

  floating_rope_50ft.setName(FLOATING_ROPE_50_FT);
  All_type length(50);

  // create the final frame list
  frames[BOOTS]    = boots;
  frames[AQUATABS] = aquatabs;

  return frames;
}

vector<Rule *>KnowledgeBase::contendingRules(WorkingMemory *wm)
{
  // subset of all rules, all which are if(true).
  // Let the inference enginer decide which one to
  // run. If the rule is
  vector<Rule *> rule_set;

  for (vector<Rule *>::iterator it = rules.begin(); it != rules.end();
       it++) {
    Rule *r = *it;

          printf("Reviewing rule [%s]\n", r->getRuleName().c_str());

    // if one shot and already triggered, then do not return this rule
    if ((r->getProperty(ONE_SHOT) == true) &&
        (r->getRuleTriggered() == true)) {
          printf("Rule [%s] is not going to be used.\n", r->getRuleName().c_str());
    } else {
      if (r->evaluateAntecendant(wm)) {
        if ((r->getRuleType() == PROCESSING_RULE) || (r->getRuleType() ==
                                                      OUTPUT_RULE)) {
          printf("Rule [%s] is processing or output.\n", r->getRuleName().c_str());
          r->evaluateAction(wm);
          r->setRuleTriggered(true);
        } else if (r->getRuleType() == INPUT_RULE) {
          printf("Rule [%s] is an input rule.\n", r->getRuleName().c_str());
          rule_set.push_back(r);
        } else {
          printf("Rule [%s] has no type!\n",      r->getRuleName().c_str());
          exit(-1);
        }
      }
    }
    fflush(stdout);
  }

  return rule_set;
}

/*
   Suggestions:
   1. Split up rules into InputType, ProcessType and OutputType.
   I type will only prompt user and add to WM. Doing this eliminates clutter.
   -antecedant will be the trigger for issuing that prompt message
   -action will be the instructions of what to call the result and where to put
      in WM
   P type will only use what is in the WM and reason with it.
   -antecendant is what triggers the rule to activate
   -action is how to either: a) change the WM, b) change session (ex. end
      session fast flag is set), c) add to packing list buffer
   O type will use the result of the P type to add to the final packing list.
 */

/*
   N() means a "notice", an informative and contextual message that is put on
      the final packing list
 */

#define NO_FORMAT ""
#define NO_PROMPT ""

// Hiking Rules (below)

// input rules

HikeTrueRule::HikeTrueRule() : Rule() {
  ruleName     = string("HikeTrueRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_BOOL;
  setFormat("%s\n");
  setPrompt("Are you hiking?");
  setProperty(ONE_SHOT, true);
}

HikeTrueRule::~HikeTrueRule() {}

bool HikeTrueRule::evaluateAntecendant(WorkingMemory *wm) {
  return true;
}

bool HikeTrueRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int HikeTrueRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, HIKE_TRUE, at);
}

HikeDistanceRule::HikeDistanceRule() : Rule() {
  ruleName     = string("HikeDistanceRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_INTEGER;
  setFormat("%s\n");
  setPrompt("How far will you hike, in meters?\n");
  setProperty(ONE_SHOT, false);
}

HikeDistanceRule::~HikeDistanceRule() {}

bool HikeDistanceRule::evaluateAntecendant(WorkingMemory *wm) {
  All_type hike = wm->getStateValue(HIKE_TRUE);

  if (hike.type == TYPE_INVALID) {
    return false;
  } else if (hike.type == TYPE_BOOL) {
    return hike.b == true;
  } else {
    return false;
  }
}

bool HikeDistanceRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int HikeDistanceRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, HIKE_DISTANCE_M, at);
}

// processing rules

// output rules

BootsRule::BootsRule() : Rule() {
  ruleName     = string("BootsRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, false);
}

BootsRule::~BootsRule() {}

#define BOOT_SUGGESTION_DISTANCE_THRESHOLD_M         (4000)
bool BootsRule::evaluateAntecendant(WorkingMemory *wm) {
  All_type dist = wm->getStateValue(HIKE_DISTANCE_M);

  if (dist.type == TYPE_INVALID) {
    return false;
  } else {
    return dist.i > BOOT_SUGGESTION_DISTANCE_THRESHOLD_M;
  }
}

bool BootsRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(BOOTS), All_type(-1)); // xxx KA
  return true;
}

AquaTabsRule::AquaTabsRule() : Rule() {
  ruleName     = string("AquaTabsRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, false);
}

AquaTabsRule::~AquaTabsRule() {}

#define AQUATAB_SUGGESTION_DISTANCE_THRESHOLD_M         (5000)
#define AQUATAB_NIGHT_THRESHOLD (1)
bool AquaTabsRule::evaluateAntecendant(WorkingMemory *wm) {
  All_type dist      = wm->getStateValue(HIKE_DISTANCE_M);
  All_type outdoors  = wm->getStateValue(OUTDOORS);
  All_type numNights = wm->getStateValue(NUM_NIGHTS);

  // if ((dist.type == TYPE_INVALID)
  //   || (outdoors.type == TYPE_INVALID)
  //    || (numNights.type == TYPE_INVALID)) {
  //  return false;
  // } else {
  return dist.i > AQUATAB_SUGGESTION_DISTANCE_THRESHOLD_M ||
         (outdoors.b && numNights.i > AQUATAB_NIGHT_THRESHOLD);

  // }
}

bool AquaTabsRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(AQUATABS), All_type(-1)); // xxx KA
  return true;
}

/*
   OUTPUT_RULE(BasicHikingListRule, wmStateAccess(WM_GET, HIKING_TRUE, NULL) ==
 ||||||||||||||||||||||||||||||||true, wmListAccess(WM_ADD,
 |||||||||||||||||||||||||||||||F(BASIC_HIKING_LIST),
 |||||||||||||||||||||||||||||||NULL));

   OUTPUT_RULE(ShortsRule, wmStateAccess(WM_GET,
                   MAX_DAILY_TEMPERATURE_C).i >
     SHORTS_SUGGESTION_TEMP_THRESHOLD_C, wmListAccess(WM_ADD, F(SHORTS), NULL));

   OUTPUT_RULE(RainRule, wmStateAccess(WM_GET, POP).i >
     RAIN_GEAR_SUGGESTION_THRESHOLD_PERCENT,
     wmListAccess(WM_ADD, F(RAIN_PONCHO), F(EXTRA_SOCKS), F(UMBRELLA)));

   INPUT_RULE(SeasonWinterRule,
     "Will you be out in the winter?\n",
     TYPE_BOOL,
     WINTER);

   OUTPUT_RULE(WinterBootsRule, wmStateAccess(WM_GET, WINTER, NULL) == true,
 ||||||||||||||||||||||||||||||||wmListAccess(WM_ADD, f(WINTER_BOOTS), NULL));

   INPUT_RULE(TickRule,
     wmStateAccess(WM_GET, HIKING_TRUE, NULL) == true,
     "Will you be going into tick territory?\n",
     TYPE_BOOL,
     TICKS);

   OUTPUT_RULE(TickNoticeRule, wmStateAccess(WM_GET, TICKS, NULL) == true,
 ||||||||||||||||||||||||||||||||wmListAccess(WM_ADD, N("Be careful of ticks in
 |||||||||||||||||||||||||||||||the
 |||||||||||||||||||||||||||||||area.
 |||||||||||||||||||||||||||||||Wear
 |||||||||||||||||||||||||||||||pants
 |||||||||||||||||||||||||||||||at
 |||||||||||||||||||||||||||||||all
 ||||||||||||||||||||||||||||||||times."), NULL));

   OUTPUT_RULE(AnimalRule, wmStateAccess(WM_GET, SOUTHERN_ONTARIO) == true,
 ||||||||||||||||||||||||||||||||wmListAccess(WM_ADD,
 |||||||||||||||||||||||||||||||N(SOUTHER_ONTARIO_ANIMALS_WARNING),
 |||||||||||||||||||||||||||||||true));

   // Camping Rules (below)

   OUTPUT_RULE(BasicCampingListRule,
     wmStateAccess(WM_GET, NUM_NIGHTS) > BASIC_CAMPING_LIST_MIN_NIGHTS,
     wmListAccess(WM_ADD, BASIC_CAMPING_LIST, BASIC_HIKING_LIST));

   INPUT_RULE(CarCampingRule,
   wmStateAccess(WM_GET, CAMPING) == true,
     "Are you going to be car camping?\n",
     TYPE_BOOL,
     CAR_CAMPING

   OUTPUT_RULE(BedComfortRule, wmStateAccess(WM_GET, CAR_CAMPING, NULL) == true,
 ||||||||||||||||||||||||||||||||)
     wmListAccess(WM_ADD, GROUND_COVER, "You can add this non-essential item
 ||||||||||||||||||||||||||||||||because you can afford the space."),
     wmListAccess(WM_ADD, AIR_MATTRESS, AIR_MATTRESS_REPAIR_KIT));

   OUTPUT_RULE(NotCarCampingRule,
     wmStateAccess(WM_GET, CAR_CAMPING) == false,
     wmListAccess(WM_ADD, ROPE_50_FT, QUANTITY_2, "To put cooler into trees."),
     wmListAccess(WM_ADD, BASIC_BACKCOUNTRY_LIST));

   // Boating Rules (below)

   INPUT_RULE(BoatingRule,
     true,
     "Will you be boating (canoe, kayak, yacht)?\n",
     TYPE_BOOL,
     BOATING);

   OUTPUT_RULE(BoatingLawRule,
     wmStateAccess(WM_GET, BOATING_TRUE, NULL) == true,
     wmListAccess(WM_ADD, BASIC_BOATING_LAW_LIST, BASIC_BOATING_LIST,
                  BASIC_HIKING_LIST));

   INPUT_RULE(KayakingRule,
     wmStateAccess(WM_GET, BOATING_TRUE, NULL) == true,
     "Will you be kayaking?\n",
     TYPE_BOOL,
     KAYAKING_TRUE);

   OUTPUT_RULE(KayakSuppliesRule,
     wmStateAccess(WM_GET, KAYAKING_TRUE) == true,
     wmListAccess(WM_ADD, KAYAK_PADDLE, SPARE_PADDLE, KAYAK_REPAIR_KIT,
                  DECK_COMPASS));

   INPUT_RULE(CanoeingRule,
     wmStateAccess(WM_GET, BOATING_TRUE, NULL) == true,
     "Will you be canoeing?\n",
     TYPE_BOOL,
     CANOEING_TRUE);

   OUTPUT_RULE(CanoeSuppliesRule,
     wmStateAccess(WM_GET, CANOEING_TRUE) == true,
     wmListAccess(WM_ADD, CANOEING_PADDLE,     QUANTITY_2),
     wmListAccess(WM_ADD, CANOEING_REPAIR_KIT, COMPASS));

   // Fishing Rules (below)

   INPUT_RULE(FishingRule,
     true,
     "Will you be fishing?\n",
     TYPE_BOOL,
     FISHING_TRUE);

   OUTPUT_RULE(FishingSuppliesRule,
     wmStateAccess(WM_GET, FISHING_TRUE) == true,
     wmListAccess(WM_ADD, BASIC_FISHING_LIST));

   INPUT_RULE(FishingBoatingRule,
     wmStateAccess(WM_GET, FISHING_TRUE) == true,
     "Will you be fishing with a boat?\n",
     TYPE_BOOl,
     FISHING_BOAT_TRUE);

   PROCESSING_RULE(BoatImplicationRule,
    wmStateAccess(WM_GET, FISHING_BOAT_TRUE) == true,
    wmStateAccess(WM_ADD, BOATING_TRUE, All_type(true)));

   OUTPUT_RULE(TrollingMotorRule,
     wmStateAccess(WM_GET,
                   FISHING_TRUE) == true && wmStateAccess(WM_GET,
                                                          BOATING_TRUE) == true,
     wmListAccess(WM_ADD, FISH_FINDER, TROLLING_MOTOR));
 */

// /*
int KnowledgeBase::initializeRules()
{
  rules.push_back(new HikeDistanceRule());
  rules.push_back(new BootsRule());
  rules.push_back(new AquaTabsRule());
  rules.push_back(new HikeTrueRule());

  // rules.push_back(new AquaTabsRule());
  return ERROR;
}

// */

