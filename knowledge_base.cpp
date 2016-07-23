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
#define BOOTS       "boots"
#define AQUATABS    "aqua tabs"
#define BASIC_KAYAKING_LIST "basic kayaking list"
#define FLOATING_ROPE_50_FT "floating rope 50ft"
#define KAYAK_PADDLE "kayak paddle"
#define BAILING_DEVICE "bailing bucket"
#define LIFE_JACKET "life jacket"
map<string, Frame>KnowledgeBase::initializeFrames()
{
  map<string, Frame> frames;

  // xxx KA this is application specific code to initialize frames that are
  // useful for TREK only
  Frame
    boots,
    floating_rope_50ft,
    whistle,
    kayak_paddle,
    bailing_bucket,
    life_jacket
  ;

  boots.setName((char *)"boots");
  All_type shoe_size(13);
  boots.addSlot((char *)"shoe size", (char *)"US", shoe_size);

  floating_rope_50ft.setName((char *)FLOATING_ROPE_50_FT);
  All_type length(50);

  // create the final frame list
  frames[BOOTS] = boots;

  return frames;
}

vector<Rule *>KnowledgeBase::contendingRules()
{
  // subset of all rules, all which are if(true).
  // Let the inference enginer decide which one to
  // run
  vector<Rule *> rule_set;

  for (vector<Rule *>::iterator it = rules.begin(); it != rules.end();
       it++) {
    Rule *r = *it;

    if (r->evaluateAntecendant()) rule_set.push_back(r);
  }
  return rule_set;
}

#define BOOT_SUGGESTION_DISTANCE_THRESHOLD_M         (5000)     // m
#define AQUATAB_SUGGESTION_DISTANCE_THRESHOLD_M         (10000) // m

// XXX KA for quick development, rules are implemted as c++ objects

/*
   RULE_DEFINE(NumNightsRule, "%s\n", "How many nights will you go?",
      TYPE_INTEGER);
   RULE_IF(NumNightsRule, true);
   RULE_AC(NumNightsRule, wmStateAccess(WM_ADD, WM_STATE, NUM_NIGHTS, NULL));

   RULE_DEFINE_PROP(KayakTrueRule, "%s\n", "Are you kayaking?", TYPE_BOOL);
   RULE_PROPERTY(KayakTrueRule, ONE_SHOT, true);
   RULE_IF(KayakTrueRule, true);
   RULE_AC(KayakTrueRule,
        wmAccess(WM_ADD, F(BASIC_KAYAKING_LIST), NULL));
 */

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

#define NO_FORMAT NULL
#define NO_PROMPT NULL

// Hiking Rules (below)

/*
   INPUT_RULE(HikeDistanceRule, wmStateAccess(WM_GET,
                                           HIKING_TRUE,
                                           NULL) == true,
           "How far will you hike, in meters?\n", TYPE_INTEGER,
           HIKE_DISTANCE_M);
 */


HikeDistanceRule::HikeDistanceRule() : Rule() {
  responseType = TYPE_INTEGER;
  setFormat("%s\n");
  setPrompt("How far will you hike, in meters?\n");
}

HikeDistanceRule::~HikeDistanceRule() {}

bool HikeDistanceRule::evaluateAntecendant() {
  return true;
}

bool HikeDistanceRule::evaluateAction() {
  return false;
}

int HikeDistanceRule::setProperties() {
  return -1;
}

int HikeDistanceRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, HIKE_DISTANCE_M, at);
}

string HikeDistanceRule::getPrompt() {
  return string("gold");
}

/*
   OUTPUT_RULE(BootsRule, wmStateAccess(WM_GET, HIKING_DISTANCE_M, NULL).i >
      BOOT_SUGGESTION_DISTANCE_THRESHOLD_M, wmListAccess(WM_ADD, F(BOOTS), NULL)

   OUTPUT_RULE(AquaTabsRule,
   wmStateAccess(WM_GET,
                   HIKING_DISTANCE_M,
                   NULL).i > AQUATAB_SUGGESTION_DISTANCE_THRESHOLD_M)
 || (wmStateAccess(WM_GET,
                  OUTDOORS, NULL).b &&
    wmStateAccess(WM_GET, NUM_NIGHTS, NULL) > AQUATAB_NIGHT_THRESHOLD),
   wmListAccess(WM_ADD, F(AQUATABS), NULL);

   INPUT_RULE(HikeTrueRule, true, "Are you hiking?\n", TYPE_BOOL, HIKING_TRUE);

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

  // rules.push_back(new AquaTabsRule());
  return ERROR;
}

// */

