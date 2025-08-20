// Main game logic
// Also holds everything together

#ifndef INC_3_FINALDOMAIN314_GAME_HPP
#define INC_3_FINALDOMAIN314_GAME_HPP

#include <unistd.h>
#include <string>
#include "Intro.hpp"
#include "Team.hpp"
#include "TurnEngine.hpp"
#include "Dictionary.h"
#include "../Domain/Input.hpp"
#include "Display.hpp"


class Game {
public:
    Game();
    ~Game();
    void setupTeams();

private:
    std::vector<Team*> teams;
    TurnEngine* turnEngine;
    Dictionary* dictionary;
    Input* input;
    Display* display;

    void gameLoop();
    void playerTurn(Player* player, int teamNum);
    void NPCTurn(Player* player, int teamNum);

    void usePlayerSpell(Player* player, int teamNum, Skill* chosenSkill, Vector2* target);
    Skill* listSkills(std::vector<Spell*> spells);
    Skill* listItems(std::vector<Item*> items);

    Vector2* chooseTarget(bool isGroupSpell);
    int chooseAction(int min, int max);

    void castSpell(Player* player, Player* target, Skill* skill);
    void executeSpell(Player* target, int amount);

    int finalizeTurn();

    void getRandomItem(Player* player);
    static void subtractItemUse(Player* player, Skill* skill);
};


#endif //INC_3_FINALDOMAIN314_GAME_HPP
