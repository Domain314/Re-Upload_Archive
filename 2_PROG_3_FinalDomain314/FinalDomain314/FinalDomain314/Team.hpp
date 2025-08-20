#ifndef INC_3_FINALDOMAIN314_TEAM_HPP
#define INC_3_FINALDOMAIN314_TEAM_HPP

#include <iostream>
#include <vector>
#include "Player.hpp"
#include "../Domain/Input.hpp"
#include "Dictionary.h"

class Team {
public:
    Team(int teamNum, Dictionary* dictionary);
    ~Team();
    Player* getPlayerByID(unsigned int ID);
    void addPlayer(Player* player);
    void deletePlayer(unsigned int ID);

    std::vector<Player*> getPlayers();
    Player* getPlayer(int index);
    int getRandomPlayerIndex();
    int getLowestHPPlayerIndex();

    void levelUpGroup();


private:
    std::vector<Player*> players;
    Input* input;
    std::string attrName;
    std::vector<std::vector<std::string>> attrDisplay;

    static int generateID(int team);
    void choosePlayer(Dictionary* dictionary, int teamNum);
    void chooseNPC(Dictionary* dictionary, int teamNum);
    std::vector<int> randomStats();
    Player* customPlayer(Dictionary* dictionary, int teamNum);

    int checkHowMuchToChange(int index);
    bool checkIfLegitToDecrease(std::vector<int> oldStats, std::vector<int> newStats, int index);
    std::vector<int> customizeStats(std::vector<int> stats, int skillPoints);
    void generateStats(std::vector<int> stats, std::string name);
    void markStats(int index);
    void unMarkStats(int index);
    void changeStats(int index, int value);
    void printStats();
    void printCharacters();


};


#endif //INC_3_FINALDOMAIN314_TEAM_HPP
