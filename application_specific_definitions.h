#ifndef APPLICATION_SPECIFIC_H
#define APPLICATION_SPECIFIC_H

#define PACKING_LIST_FILENAME string("trek_packing_list.txt")

// http://www.patorjk.com/software/taag/#p=display&f=Alpha&t=TREK
int cool_ascii_name() {
  printf(
    "\n"
    "      _____                    _____                    _____                    _____   \n"
    "     /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\   \n"
    "    /::\\    \\                /::\\    \\                /::\\    \\                /::\\____\\   \n"
    "    \\:::\\    \\              /::::\\    \\              /::::\\    \\              /:::/    /    \n"
    "     \\:::\\    \\            /::::::\\    \\            /::::::\\    \\            /:::/    /      \n"
    "      \\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/    /        \n"
    "       \\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/____/          \n"
    "       /::::\\    \\      /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /::::\\    \\           \n"
    "      /::::::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\____\\________   \n"
    "     /:::/\\:::\\    \\  /:::/\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::::::::::\\    \\   \n"
    "    /:::/  \\:::\\____\\/:::/  \\:::\\   \\:::|    |/:::/__\\:::\\   \\:::\\____\\/:::/  |:::::::::::\\____\\   \n"
    "   /:::/    \\::/    /\\::/   |::::\\  /:::|____|\\:::\\   \\:::\\   \\::/    /\\::/   |::|~~~|~~~~~         \n"
    "  /:::/    / \\/____/  \\/____|:::::\\/:::/    /  \\:::\\   \\:::\\   \\/____/  \\/____|::|   |               \n"
    " /:::/    /                 |:::::::::/    /    \\:::\\   \\:::\\    \\            |::|   |                \n"
    "/:::/    /                  |::|\\::::/    /      \\:::\\   \\:::\\____\\           |::|   |                 \n"
    "\\::/    /                   |::| \\::/____/        \\:::\\   \\::/    /           |::|   |                  \n"
    " \\/____/                    |::|  ~|               \\:::\\   \\/____/            |::|   |                  \n"
    "                            |::|   |                \\:::\\    \\                |::|   |                  \n"
    "                            \\::|   |                 \\:::\\____\\               \\::|   |                  \n"
    "                             \\:|   |                  \\::/    /                \\:|   |                  \n"
    "                              \\|___|                   \\/____/                  \\|___|                  \n"
    "");
}

int welcome() {
  cool_ascii_name();

  // system(
  //  "cowsay -f stegosaurus Welcome to TREK, your packing buddy and expert
  // system");
    printf("\n\nWelcome to TREK, your packing buddy and expert system\n");
    printf("Loading knowledge");

  for (int i = 1; i < 50; i++) {
    printf(".");
    fflush(stdout);

    // usleep(5000);//70000);
  }
  printf("\n");
}

int description() {
  printf("Purpose: help with packing lists for trips\n");
  printf(
    "Includes kayak trips, hiking trips for multiple people over many days\n");
}

int listSpecialCommands() {
  printf("");
}

// https://en.wikipedia.org/wiki/Rete_algorithm#Overview
int documentation() {
  printf(
    "\n\n------------------TREK Expert System Documentation------------------\n\n");
  printf("KNOWLEDGE\n");
  printf(
    "TREK has knowledge of packing lists, good tools to have for what purposes, calculations to optimize weight, volume usage, safety, fun.\n");
  printf("Knowledge representation uses production rules that use frames.\n");
  printf("Rules codify knowledge about what situations gear is appropriate and\n");
  printf(
    "frames are used to represent individual packing list items like boots, packs, frisbees.\n");
  printf("Example rule:\n");
  printf("if trail > 3 km then suggest item boots\n");
  printf("\n");
  printf("IMPLEMENTATION\n");
  printf("\nConcepts\n");
  printf(
    "1. State: Global values such as fishing=true or NumberOfNights=3. These states are used in the evaluation sections of production rules and are modified in the action sections of them.\n");
  printf(
    "2. Static information: packing list items (ex. boots) are stored as frames in a file. If the trekker does not have an item, default values are used. Static information about trekker profiles is also saved. Loading trekker profiles adds preset state and items into TREK before beginning.\n");
  printf(
    "3. Working memory: a sandbox for figuring things out. State, the current packing list and all other information for decisions are in this memory.\n");
  printf(
    "4. Explanation facility: for each item on the final packing list the user can ask why it was suggested, possible substitutes, all info on that item. At any point in the consulation the user can ask why a question is being asked, example or expected answers from the user, the current packing list.\n");
  printf(
    "5. Constraints and optimization: all calculation is used to create the ideal packing list. Rules can invoke computation.\n");
  printf("\nRules\n");
  printf("Rules have an evaluation and action section.\n");
  printf(
    "Rete match algorithm: The eval section of rules are compiled into a tree (during program compile-time) to speed-up rule inferencing at run-time.\n");
  printf(
    "\n\n--------------END TREK Expert System Documentation------------------\n\n");
}

#endif // ifndef APPLICATION_SPECIFIC_H
