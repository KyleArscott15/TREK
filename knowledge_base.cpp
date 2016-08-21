#include "knowledge_base.h"

bool Rule::boolStateValue(WorkingMemory *wm, string state) {
  All_type stateVal = wm->getStateValue(state);

  if (stateVal.type == TYPE_INVALID) {
    return false;
  } else {
    if (stateVal.type == TYPE_BOOL) {
      return stateVal.b;
    } else {
      return false;
    }
  }
}

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

// basic camping list
#define BASIC_CAMPING_LIST string("basic camping list")
#define AQUATABS    string("aqua tabs")
#define TENT   string("tent")
#define TARP   string("tarp")
#define SLEEPING_BAG  string("sleeping bag")
#define SLEEPING_PAD   string("sleeping pad")
#define PILLOW   string("pillow")
#define DRY_BAGS   string("dry bags")
#define COLEMAN_STOVE   string("coleman stove")
#define ROPE   string("rope")
#define POTS_AND_PANS   string("pots and pans")
#define COOKWARE   string("bowls, plates, utensils")
#define SAW   string("saw or hatchet")
#define KNIFE   string("general purpose knife")
#define EMERGENCY_KIT   string("emergency warmth blanket and kit")
#define FIRST_AID_KIT   string("first aid kit")
#define LIGHTER   string("lighter")
#define FLASHLIGHT   string("flashlight")
#define TOILETRIES   string( \
    "toiletries (tooth paste, tooth brush, floss, nail clippers, toilet paper)")
#define TYLENOL   string("tylenol")
#define CAMP_SOAP   string("biodegradeable camp soap")
#define GARBAGE_BAGS   string("garbage bags (make sure they are resealable)")
#define FOOD_BARREL   string("food barrel")
#define RAIN_WARE   string("rain jacket and pants")
#define EXTRA_SOCKS   string("extra socks")
#define DRY_FIT_SHIRT   string("dry-fit shirt")
#define DRY_FIT_SHORTS   string("dry-fit shorts")

// car camping list
#define GROUND_COVER            string("ground cover")
#define AIR_MATTRESS            string("air mattress")
#define AIR_MATTRESS_REPAIR_KIT string("air mattress repair kit")

// basic hiking list
#define BASIC_HIKING_LIST string("basic hiking list")
#define BOOTS       string("boots")
#define HIKING_PANTS string("hiking pants")
#define SUNSCREEN string("sunscreen")
#define HIKING_MAP string("map")
#define SUN_GLASSES string("polarizing sun glasses")
#define BUG_SPRAY  string("bug spray")
#define COMPASS  string("compass")
#define WATER_BOTTLE    string("water bottle")
#define BACKPACK string("backpack")

// basic kayaking list
#define BASIC_KAYAKING_LIST string("basic kayaking list")
#define BASIC_KAYAKING_LEGAL_REQUIREMENTS string( \
    "Kayaking Legal requirements list")
#define FLOATING_ROPE_50_FT string("floating rope 50ft")
#define KAYAK_PADDLE string("kayak paddle")
#define BAILING_DEVICE string("bailing bucket")
#define LIFE_JACKET string("life jacket or PFD")
#define SOUND_SIGNALLING_DEVICE string( \
    "passive sound-signalling device. ex. whistle")
#define BASIC_KAYAKING_LEGAL_REQUIREMENTS_NIGHT_TIME string( \
    "Kayaking Legal requirements list, at night")
#define WATERPROOF_FLASHLIGHT string("wateproof flashlight")
#define WHITE_DECK_LIGHT string("360 degree visible white deck light")
#define FLARES string("flares")
#define KAYAK string("kayak")
#define KAYAK_REPAIR_KIT string( \
    "kayak repair kit (adhesive, plastic patches, marine epoxy)")
#define TIDAL_WAVE_CHARTS string("tidal and wave charts")
#define KAYAKING_MAP string("kayaking map")
#define DECK_COMPASS string("deck compass")
#define MARINE_RADIO string("marine radio")
#define MARINE_RADIO_RF_CHART string("marine radio frequency channels chart")
#define RADAR_REFELCTOR string("kayak radar reflector")
#define WATER_SHOES string("water shoes")

map<string, Frame>KnowledgeBase::initializeFrames()
{
  map<string, Frame> frames;

  // application specific code to initialize frames that are useful for TREK
  // only
  Frame
    basicCampingList,
    aquatabs,
    tent,
    tarp,
    sleepingBag,
    sleepingPad,
    pillow,
    dryBags,
    stove,
    rope,
    potsAndPans,
    cookware,
    saw,
    knife,
    emergencyKit,
    firstAidKit,
    lighter,
    flashlight,
    toiletries,
    tylenol,
    campSoap,
    garbageBags,
    foodBarrel,
    rainWare,
    extraSocks,
    dryFitShirt,
    dryFitShorts,

    groundCover,
    airMattress,
    airMattressRepairKit,

    basicHikingList,
    boots,
    hikingPants,
    sunscreen,
    hikingMap,
    sunGlasses,
    bugSpray,
    compass,
    waterBottle,
    backpack,

    basicKayakingList,
    basicKayakingListLegal,
    floatingRope50Ft,
    kayakPaddle,
    bailingBucket,
    lifeJacket,
    soundSignallingDevice,
    basicKayakingListLegalNight,
    waterproofFlashlight,
    whiteDeckLight,
    flares,
    kayak,
    kayakRepairKit,
    tidalWaveCharts,
    deckCompass,
    marineRadio,
    marineRadioRFCharts,
    radarReflector,
    waterShoes,
    kayakingMap
  ;

  boots.setName(BOOTS);
  All_type shoe_size(13);
  boots.addSlot((char *)"shoe size", (char *)"US", shoe_size);

  basicCampingList.setName(BASIC_CAMPING_LIST);
  aquatabs.setName(AQUATABS);
  tent.setName(TENT);
  tarp.setName(TARP);
  sleepingBag.setName(SLEEPING_BAG);
  sleepingPad.setName(SLEEPING_PAD);
  pillow.setName(PILLOW);
  dryBags.setName(DRY_BAGS);
  stove.setName(COLEMAN_STOVE);
  rope.setName(ROPE);
  potsAndPans.setName(POTS_AND_PANS);
  cookware.setName(COOKWARE);
  saw.setName(SAW);
  knife.setName(KNIFE);
  emergencyKit.setName(EMERGENCY_KIT);
  firstAidKit.setName(FIRST_AID_KIT);
  lighter.setName(LIGHTER);
  flashlight.setName(FLASHLIGHT);
  toiletries.setName(TOILETRIES);
  tylenol.setName(TYLENOL);
  campSoap.setName(CAMP_SOAP);
  garbageBags.setName(GARBAGE_BAGS);
  foodBarrel.setName(FOOD_BARREL);
  rainWare.setName(RAIN_WARE);
  extraSocks.setName(EXTRA_SOCKS);
  dryFitShirt.setName(DRY_FIT_SHIRT);
  dryFitShorts.setName(DRY_FIT_SHORTS);

  vector<Frame> bcl;
  bcl.push_back(aquatabs);
  bcl.push_back(tent);
  bcl.push_back(tarp);
  bcl.push_back(sleepingBag);
  bcl.push_back(sleepingPad);
  bcl.push_back(pillow);
  bcl.push_back(dryBags);
  bcl.push_back(stove);
  bcl.push_back(rope);
  bcl.push_back(potsAndPans);
  bcl.push_back(cookware);
  bcl.push_back(saw);
  bcl.push_back(knife);
  bcl.push_back(emergencyKit);
  bcl.push_back(firstAidKit);
  bcl.push_back(lighter);
  bcl.push_back(flashlight);
  bcl.push_back(toiletries);
  bcl.push_back(tylenol);
  bcl.push_back(campSoap);
  bcl.push_back(garbageBags);
  bcl.push_back(foodBarrel);
  bcl.push_back(rainWare);
  bcl.push_back(extraSocks);
  bcl.push_back(dryFitShirt);
  bcl.push_back(dryFitShorts);
  basicCampingList.setCollection(bcl);

  groundCover.setName(GROUND_COVER);
  airMattress.setName(AIR_MATTRESS);
  airMattressRepairKit.setName(AIR_MATTRESS_REPAIR_KIT);

  basicHikingList.setName(BASIC_HIKING_LIST);
  boots.setName(BOOTS);
  hikingPants.setName(HIKING_PANTS);
  sunscreen.setName(SUNSCREEN);
  hikingMap.setName(HIKING_MAP);
  sunGlasses.setName(SUN_GLASSES);
  bugSpray.setName(BUG_SPRAY);
  compass.setName(COMPASS);
  waterBottle.setName(WATER_BOTTLE);
  backpack.setName(BACKPACK);

  vector<Frame> bhl;
  bhl.push_back(boots);
  bhl.push_back(hikingPants);
  bhl.push_back(sunscreen);
  bhl.push_back(hikingMap);
  bhl.push_back(sunGlasses);
  bhl.push_back(bugSpray);
  bhl.push_back(compass);
  bhl.push_back(waterBottle);
  bhl.push_back(backpack);
  basicHikingList.setCollection(bhl);

  basicKayakingList.setName(BASIC_KAYAKING_LIST);
  basicKayakingListLegal.setName(BASIC_KAYAKING_LEGAL_REQUIREMENTS);
  floatingRope50Ft.setName(FLOATING_ROPE_50_FT);
  kayakPaddle.setName(KAYAK_PADDLE);
  bailingBucket.setName(BAILING_DEVICE);
  lifeJacket.setName(LIFE_JACKET);
  soundSignallingDevice.setName(SOUND_SIGNALLING_DEVICE);
  basicKayakingListLegalNight.setName(
    BASIC_KAYAKING_LEGAL_REQUIREMENTS_NIGHT_TIME);
  waterproofFlashlight.setName(WATERPROOF_FLASHLIGHT);
  whiteDeckLight.setName(WHITE_DECK_LIGHT);
  flares.setName(FLARES);
  kayak.setName(KAYAK);
  kayakRepairKit.setName(KAYAK_REPAIR_KIT);
  tidalWaveCharts.setName(TIDAL_WAVE_CHARTS);
  deckCompass.setName(DECK_COMPASS);
  marineRadio.setName(MARINE_RADIO);
  marineRadioRFCharts.setName(MARINE_RADIO_RF_CHART);
  radarReflector.setName(RADAR_REFELCTOR);
  waterShoes.setName(WATER_SHOES);
  kayakingMap.setName(KAYAKING_MAP);

  vector<Frame> bkll;
  bkll.push_back(floatingRope50Ft);
  bkll.push_back(kayakPaddle);
  bkll.push_back(bailingBucket);
  bkll.push_back(lifeJacket);
  bkll.push_back(soundSignallingDevice);
  basicKayakingListLegal.setCollection(bkll);

  vector<Frame> bklln;
  bklln.push_back(waterproofFlashlight);
  bklln.push_back(whiteDeckLight);
  bklln.push_back(flares);
  basicKayakingListLegalNight.setCollection(bklln);

  vector<Frame> bkl;
  bkl.push_back(basicKayakingListLegal);
  bkl.push_back(kayak);
  bkl.push_back(kayakRepairKit);
  bkl.push_back(tidalWaveCharts);
  bkl.push_back(deckCompass);
  bkl.push_back(marineRadio);
  bkl.push_back(marineRadioRFCharts);
  bkl.push_back(radarReflector);
  bkl.push_back(waterShoes);
  bkl.push_back(kayakingMap);
  basicKayakingList.setCollection(bkl);

  // create the final frame list
  frames[BASIC_CAMPING_LIST] = basicCampingList;
  frames[AQUATABS]           = aquatabs;
  frames[TENT]               = tent;
  frames[TARP]               = tarp;
  frames[SLEEPING_BAG]       = sleepingBag;
  frames[SLEEPING_PAD]       = sleepingPad;
  frames[PILLOW]             = pillow;
  frames[DRY_BAGS]           = dryBags;
  frames[COLEMAN_STOVE]      = stove;
  frames[DRY_BAGS]           = dryBags;
  frames[ROPE]               = rope;
  frames[POTS_AND_PANS]      = potsAndPans;
  frames[COOKWARE]           = cookware;
  frames[SAW]                = saw;
  frames[KNIFE]              = knife;
  frames[EMERGENCY_KIT]      = emergencyKit;
  frames[FIRST_AID_KIT]      = firstAidKit;
  frames[LIGHTER]            = lighter;
  frames[FLASHLIGHT]         = flashlight;
  frames[TOILETRIES]         = toiletries;
  frames[TYLENOL]            = tylenol;
  frames[CAMP_SOAP]          = campSoap;
  frames[GARBAGE_BAGS]       = garbageBags;
  frames[FOOD_BARREL]        = foodBarrel;
  frames[RAIN_WARE]          = rainWare;
  frames[EXTRA_SOCKS]        = extraSocks;
  frames[DRY_FIT_SHIRT]      = dryFitShirt;
  frames[DRY_FIT_SHORTS]     = dryFitShorts;

  frames[GROUND_COVER]            = groundCover;
  frames[AIR_MATTRESS]            = airMattress;
  frames[AIR_MATTRESS_REPAIR_KIT] = airMattressRepairKit;

  frames[BASIC_HIKING_LIST] = basicHikingList;
  frames[BOOTS]             = boots;
  frames[HIKING_PANTS]      = hikingPants;
  frames[SUNSCREEN]         = sunscreen;
  frames[HIKING_MAP]        = hikingMap;
  frames[SUN_GLASSES]       = sunGlasses;
  frames[BUG_SPRAY]         = bugSpray;
  frames[COMPASS]           = compass;
  frames[WATER_BOTTLE]      = waterBottle;
  frames[BACKPACK]          = backpack;

  frames[BASIC_KAYAKING_LIST]                          = basicKayakingList;
  frames[BASIC_KAYAKING_LEGAL_REQUIREMENTS]            = basicKayakingListLegal;
  frames[FLOATING_ROPE_50_FT]                          = floatingRope50Ft;
  frames[KAYAK_PADDLE]                                 = kayakPaddle;
  frames[BAILING_DEVICE]                               = bailingBucket;
  frames[LIFE_JACKET]                                  = lifeJacket;
  frames[SOUND_SIGNALLING_DEVICE]                      = soundSignallingDevice;
  frames[BASIC_KAYAKING_LEGAL_REQUIREMENTS_NIGHT_TIME] =
    basicKayakingListLegalNight;
  frames[WATERPROOF_FLASHLIGHT] = waterproofFlashlight;
  frames[WHITE_DECK_LIGHT]      = whiteDeckLight;
  frames[FLARES]                = flares;
  frames[KAYAK]                 = kayak;
  frames[KAYAK_REPAIR_KIT]      = kayakRepairKit;
  frames[TIDAL_WAVE_CHARTS]     = tidalWaveCharts;
  frames[DECK_COMPASS]          = deckCompass;
  frames[MARINE_RADIO]          = marineRadio;
  frames[MARINE_RADIO_RF_CHART] = marineRadioRFCharts;
  frames[RADAR_REFELCTOR]       = radarReflector;
  frames[WATER_SHOES]           = waterShoes;
  frames[KAYAKING_MAP]          = kayakingMap;

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

// input rules

/*
   #define INPUT_RULE_IMPLEMENTATION(ruleName, prompt,                      \
                                  antecendant, action, promptResponse)   \
   ruleName::ruleName() : Rule() {                                        \
    ruleName     = string("ruleName");                                   \
    ruleType     = INPUT_RULE;                                           \
    responseType = TYPE_BOOL;                                            \
    setFormat("%s\n");                                                   \
    setPrompt("prompt");                                                 \
    setProperty(ONE_SHOT, true);                                         \
   }                                                                      \
   ruleName::~ruleName() {}                                               \
   bool ruleName::evaluateAntecendant(WorkingMemory * wm) {               \
    antecendant;                                                         \
   }                                                                      \
   bool ruleName::evaluateAction(WorkingMemory * wm) {                    \
    action;                                                              \
   }                                                                      \
   int ruleName::setPromptResponseToWM(All_type at, WorkingMemory * wm) { \
    promptResponse;                                                      \
   }

   #define INPUT_RULE_IMPLEMENTATION(HikeTrueRule, Are you hiking ? ,
   return true, return false, return wm->wmStateAccess(WM_ADD, HIKE_TRUE, at));
 */

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

CampingTrueRule::CampingTrueRule() : Rule() {
  ruleName     = string("CampingTrueRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_BOOL;
  setFormat("%s\n");
  setPrompt("Are you camping?");
  setProperty(ONE_SHOT, true);
}

CampingTrueRule::~CampingTrueRule() {}

bool CampingTrueRule::evaluateAntecendant(WorkingMemory *wm) {
  return true;
}

bool CampingTrueRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int CampingTrueRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, CAMPING_TRUE, at);
}

CarCampingTrueRule::CarCampingTrueRule() : Rule() {
  ruleName     = string("CarCampingTrueRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_BOOL;
  setFormat("%s\n");
  setPrompt("Are you car camping?");
  setProperty(ONE_SHOT, true);
}

CarCampingTrueRule::~CarCampingTrueRule() {}

bool CarCampingTrueRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, CAMPING_TRUE);
}

bool CarCampingTrueRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int CarCampingTrueRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, CAR_CAMPING_TRUE, at);
}

KayakingTrueRule::KayakingTrueRule() : Rule() {
  ruleName     = string("KayakingTrueRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_BOOL;
  setFormat("%s\n");
  setPrompt("Are you kayaking?");
  setProperty(ONE_SHOT, true);
}

KayakingTrueRule::~KayakingTrueRule() {}

bool KayakingTrueRule::evaluateAntecendant(WorkingMemory *wm) {
  return true;
}

bool KayakingTrueRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int KayakingTrueRule::setPromptResponseToWM(All_type at, WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, KAYAKING_TRUE, at);
}

KayakingNightTrueRule::KayakingNightTrueRule() : Rule() {
  ruleName     = string("KayakingTrueRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_BOOL;
  setFormat("%s\n");
  setPrompt("Are you kayaking at night?");
  setProperty(ONE_SHOT, true);
}

KayakingNightTrueRule::~KayakingNightTrueRule() {}

bool KayakingNightTrueRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, KAYAKING_TRUE);
}

bool KayakingNightTrueRule::evaluateAction(WorkingMemory *wm) {
  return false;
}

int KayakingNightTrueRule::setPromptResponseToWM(All_type       at,
                                                 WorkingMemory *wm) {
  return wm->wmStateAccess(WM_ADD, KAYAKING_NIGHT_TRUE, at);
}

HikeDistanceRule::HikeDistanceRule() : Rule() {
  ruleName     = string("HikeDistanceRule");
  ruleType     = INPUT_RULE;
  responseType = TYPE_INTEGER;
  setFormat("%s\n");
  setPrompt("How far will you hike, in meters?");
  setProperty(ONE_SHOT, true);
}

HikeDistanceRule::~HikeDistanceRule() {}

bool HikeDistanceRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, HIKE_TRUE);
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
  setProperty(ONE_SHOT, true);
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

BasicHikingListRule::BasicHikingListRule() : Rule() {
  ruleName     = string("BasicHikingListRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, true);
}

BasicHikingListRule::~BasicHikingListRule() {}

bool BasicHikingListRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, HIKE_TRUE);
}

bool BasicHikingListRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(BASIC_HIKING_LIST), All_type(-1)); // xxx KA
  return true;
}

BasicCampingListRule::BasicCampingListRule() : Rule() {
  ruleName     = string("BasicCampingListRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, true);
}

BasicCampingListRule::~BasicCampingListRule() {}

bool BasicCampingListRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, CAMPING_TRUE);
}

bool BasicCampingListRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(BASIC_CAMPING_LIST), All_type(-1)); // xxx KA
  return true;
}

BasicKayakingListRule::BasicKayakingListRule() : Rule() {
  ruleName     = string("BasicKayakingListRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, true);
}

BasicKayakingListRule::~BasicKayakingListRule() {}

bool BasicKayakingListRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, KAYAKING_TRUE);
}

bool BasicKayakingListRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(BASIC_KAYAKING_LIST), All_type(-1)); // xxx KA
  return true;
}

BasicKayakingListNightRule::BasicKayakingListNightRule() : Rule() {
  ruleName     = string("BasicKayakingListNightRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, true);
}

BasicKayakingListNightRule::~BasicKayakingListNightRule() {}

bool BasicKayakingListNightRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, KAYAKING_NIGHT_TRUE);
}

bool BasicKayakingListNightRule::evaluateAction(WorkingMemory *wm) {
  // xxx KA
  wm->wmListAccess(WM_ADD, F(
                     BASIC_KAYAKING_LEGAL_REQUIREMENTS_NIGHT_TIME), All_type(-1));
  return true;
}

BasicCarCampingRule::BasicCarCampingRule() : Rule() {
  ruleName     = string("BasicCarCampingRule");
  ruleType     = OUTPUT_RULE;
  responseType = TYPE_INVALID;
  setFormat(NO_FORMAT);
  setPrompt(NO_PROMPT);
  setProperty(ONE_SHOT, true);
}

BasicCarCampingRule::~BasicCarCampingRule() {}

bool BasicCarCampingRule::evaluateAntecendant(WorkingMemory *wm) {
  return boolStateValue(wm, CAR_CAMPING_TRUE);
}

bool BasicCarCampingRule::evaluateAction(WorkingMemory *wm) {
  wm->wmListAccess(WM_ADD, F(GROUND_COVER),
                   All_type(
                     "You can add this non-essential item because you can afford the space."));
  wm->wmListAccess(WM_ADD, F(AIR_MATTRESS),
                   All_type(
                     "You can add this non-essential item because you can afford the space."));
  wm->wmListAccess(WM_ADD, F(AIR_MATTRESS_REPAIR_KIT),
                   All_type(
                     "You can add this non-essential item because you can afford the space."));
  return true;
}

int KnowledgeBase::initializeRules()
{
  // input rules
  rules.push_back(new HikeTrueRule());
  rules.push_back(new HikeDistanceRule());
  rules.push_back(new CampingTrueRule());
  rules.push_back(new CarCampingTrueRule());
  rules.push_back(new KayakingTrueRule());
  rules.push_back(new KayakingNightTrueRule());

  // processing rules

  // output rules
  rules.push_back(new BootsRule());
  rules.push_back(new AquaTabsRule());
  rules.push_back(new BasicHikingListRule());
  rules.push_back(new BasicCampingListRule());
  rules.push_back(new BasicKayakingListRule());
  rules.push_back(new BasicKayakingListNightRule());
  rules.push_back(new BasicCarCampingRule());

  return ERROR;
}

