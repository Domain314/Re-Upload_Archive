// Holds (most) output.
// Ready to spam it as fast as possible
// Instead of asking all foreign objects for their variables to
// display them in EACH frame, the display-class TAKES ONLY CHANGES
// of the fields. ==> shorter output times ==> more fps possible

#ifndef INC_3_FINALDOMAIN314_DISPLAY_HPP
#define INC_3_FINALDOMAIN314_DISPLAY_HPP


#include <iostream>
#include <string>
#include <vector>
#include "Dictionary.h"
#include "../Domain/globals.hpp"
#include "Team.hpp"

class Display : public Dictionary {
public:
    explicit Display(std::vector<Team*> teams);
    ~Display();
    void createLines(int screenX);
    void setCharacters(std::vector<Team*> teams);
    void addMessage(std::string mes);
    void resetAllMessages();
    void playersTurnMessage(std::string entity, std::string name, int teamNum);
    void playersTurnMessage(std::string entity, std::string name, int mana, int teamNum);

    void printDisplays();
    static void printWall();
    void printDisplay();

    void markPlayer(int teamNum, int playerIndex, bool isGroupSpell);
    void unMarkPlayer(int teamNum, int playerIndex, bool isGroupSpell);
    void unMarkAll();

    void markConsoleLine(int index);
    void unMarkConsoleLine(int index);

    void animateDecision(std::string name);

private:
    int maxX;
    std::vector<std::vector<std::string>> display1;
    std::vector<std::vector<std::string>> display2;
    std::string thisTurn;
    std::vector<std::string> console;
    std::string fullLine;
    std::string emptyLine;

};


#endif //INC_3_FINALDOMAIN314_DISPLAY_HPP
