#include "Team.hpp"

// let user decide on team setup
Team::Team(int teamNum, Dictionary* dictionary) {
    this->input = new Input();
    int pos = 0;
    
    while (true) {
        clearScreen();
        if (teamNum == 0) { std::cout << BOLDYELLOW; }
        else { std::cout << MAGENTA; }
        std::cout << "Team" << teamNum + 1 << ":\n";
        std::cout << RESET;
        printCharacters();
        std::cout << "Position" << pos + 1 << ": \n(P)layer,   (C)omp,   (F)inish Team\n";
        switch (input->_getChar()) {
            case 'p': choosePlayer(dictionary, teamNum); pos++; break;
            case 'c': chooseNPC(dictionary, teamNum); pos++; break;
            case 'f': pos = -1; break;
        }
        if (pos > 100 || pos == -1) { break; }
    }
}

// De-Constructor
Team::~Team(){
    for (int i = (players.size()-1); i >= 0 ; --i) {
        delete players.at(i);
    }
    std::vector<Player*>().swap(players);
    std::vector<std::vector<std::string>>().swap(attrDisplay);
    delete input;
}

// search all players by ID and return pointer to him
Player *Team::getPlayerByID(unsigned int ID) {
    while (true) {
        for (auto & player : players) {
            if (player->checkID(ID)) { return player; }
        }
        return nullptr;
    }
}

int Team::generateID(int team) {
    return (team+1)*10000 + randomNum(10000);
}

// user decides character class
void Team::choosePlayer(Dictionary* dictionary, int teamNum) {
    std::cout << "Choose Player Class:\n(W)arrior, (M)age, (P)riest, (S)keleton, (C)ustom\n";
    switch (input->_getChar()) {
        case 'w': addPlayer(new Player(dictionary->getCharClass('w'), generateID(teamNum), 'w', dictionary, true)); break;
        case 'm': addPlayer(new Player(dictionary->getCharClass('m'), generateID(teamNum), 'm', dictionary, true)); break;
        case 'p': addPlayer(new Player(dictionary->getCharClass('p'), generateID(teamNum), 'p', dictionary, true)); break;
        case 's': addPlayer(new Player(dictionary->getCharClass('s'), generateID(teamNum), 's', dictionary, true)); break;
        case 'c': addPlayer(customPlayer(dictionary, teamNum)); break;
        default:
            choosePlayer(dictionary, teamNum); break;
    }
}

// user decides character class
void Team::chooseNPC(Dictionary* dictionary, int teamNum) {
    std::cout << "Choose NPC Class:\n(W)arrior, (M)age, (P)riest, (S)keleton, (R)andom\n";
    switch (input->_getChar()) {
        case 'w': addPlayer(new Player(dictionary->getCharClass('w'), generateID(teamNum), 'w', dictionary, false)); break;
        case 'm': addPlayer(new Player(dictionary->getCharClass('m'), generateID(teamNum), 'm', dictionary, false)); break;
        case 'p': addPlayer(new Player(dictionary->getCharClass('p'), generateID(teamNum), 'p', dictionary, false)); break;
        case 's': addPlayer(new Player(dictionary->getCharClass('s'), generateID(teamNum), 's', dictionary, false)); break;
        case 'r': addPlayer(new Player(randomStats(), generateID(teamNum), 's', dictionary, true)); break;
        default:
            chooseNPC(dictionary, teamNum); break;
    }
    players.at(players.size()-1)->setName(dictionary->getRandomNPCName());
}

// return random stats
std::vector<int> Team::randomStats() {
    return { randomNum(300), randomNum(300), randomNum(5), randomNum(5), randomNum(5), randomNum(5), 1000+randomNum(100) };
}

void Team::addPlayer(Player* player) {
    players.push_back(player);
}

// user decide on skillTree
Player* Team::customPlayer(Dictionary* dictionary, int teamNum) {
    int attrPoints = CUSTOM_ATTR_POINTS;
    std::vector<int> customStats = dictionary->getCharClass('c');
    generateStats(customStats, "Custom");
    customStats = customizeStats(customStats, attrPoints);
    clearScreen();
    std::cout << "Which SkillTree do you want to use?\n(W)arrior, (M)age, (P)riest" << std::endl;
    switch (input->_getChar()) {
        case 'W':
        case 'w': return new Player(customStats, generateID(teamNum), 'w', dictionary, true); break;
        case 'M':
        case 'm': return new Player(customStats, generateID(teamNum), 'm', dictionary, true); break;
        case 'P':
        case 'p': return new Player(customStats, generateID(teamNum), 'p', dictionary, true); break;
        default: return new Player(customStats, generateID(teamNum), 'w', dictionary, true); break;
    }
}

// user decide which stats to increase, after winning a fight.
void Team::levelUpGroup() {
    for (auto & player : players) {
        player->resetStats();
        if (player->checkIfPlayer()) {
            generateStats(player->getAllStats(), player->getName());
            player->setStats(customizeStats(player->getAllStats(), SKILLPOINTS_PER_LEVEL));
            player->decideOnSpellTree();
        }
    }
}

// user decide on custom stats.
std::vector<int> Team::customizeStats(std::vector<int> stats, int skillPoints) {
    std::vector<int> backup = stats;
    int decision = 0;
    markStats(decision);
    while (skillPoints >= 1) {
        int sign = 0;
        printStats();
        std::cout << "\n" << skillPoints << " Points Left\n";
        switch (input->getInput()) {
            case 'w':
                unMarkStats(decision);
                decision = decision-1 < 0 ? stats.size()-1 : --decision;
                markStats(decision); break;
            case 's':
                unMarkStats(decision);
                decision = decision+1 > stats.size()-1 ? 0 : ++decision;
                markStats(decision); break;
            case 'a':
                if (checkIfLegitToDecrease(backup, stats, decision)) {
                    stats.at(decision) -= checkHowMuchToChange(decision);
                    changeStats(decision, stats.at(decision));
                    skillPoints += 1;
                }
                break;
            case 'd':
                stats.at(decision) += checkHowMuchToChange(decision);
                changeStats(decision, stats.at(decision));
                skillPoints -= 1; break;
        }
    }
    return stats;
}

// return right amount for increasing/decreasing stat
int Team::checkHowMuchToChange(int index) {
    switch (index) {
        case 0: return HP_INCREASE; break;
        case 1: return MP_INCREASE; break;
        case 2: return ATK_INCREASE; break;
        case 3: return INT_INCREASE; break;
        case 4: return DEF_INCREASE; break;
        case 5: return KRIT_INCREASE; break;
        case 6: return SPEED_INCREASE; break;
    }
    return 0;
}

// compare new stat with old and forbid to decrease below old stat
bool Team::checkIfLegitToDecrease(std::vector<int> oldStats, std::vector<int> newStats, int index) {
    if (index == 6) {
        return (newStats.at(index) + checkHowMuchToChange(index)) <= oldStats.at(index);
    } else {
        return (newStats.at(index) - checkHowMuchToChange(index)) >= oldStats.at(index);
    }

}

void Team::markStats(int index) {
    attrDisplay.at(index).at(1) = ">";
    attrDisplay.at(index).at(3) = "<";
}

void Team::unMarkStats(int index) {
    attrDisplay.at(index).at(1) = " ";
    attrDisplay.at(index).at(3) = " ";
}

void Team::changeStats(int index, int value) {
    attrDisplay.at(index).at(2) = std::to_string(value);
}

// generate display for stats customization
void Team::generateStats(std::vector<int> stats, std::string name) {
    attrDisplay.clear();
    for (int i = 0; i < 7; ++i) {
        attrDisplay.push_back({" "," "," "," "});
    }
    this->attrName = name;
    attrDisplay.at(0).at(0) = "HP:";
    attrDisplay.at(0).at(2) = std::to_string(stats.at(0));

    attrDisplay.at(1).at(0) = "MP:";
    attrDisplay.at(1).at(2) = std::to_string(stats.at(1));

    attrDisplay.at(2).at(0) = "ATK:";
    attrDisplay.at(2).at(2) = std::to_string(stats.at(2));

    attrDisplay.at(3).at(0) = "INT:";
    attrDisplay.at(3).at(2) = std::to_string(stats.at(3));

    attrDisplay.at(4).at(0) = "DEF:";
    attrDisplay.at(4).at(2) = std::to_string(stats.at(4));

    attrDisplay.at(5).at(0) = "KRIT:";
    attrDisplay.at(5).at(2) = std::to_string(stats.at(5));

    attrDisplay.at(6).at(0) = "SPEED:";
    attrDisplay.at(6).at(2) = std::to_string(stats.at(6));

}

// print stats, while customization
void Team::printStats() {
    clearScreen();
    std::cout << attrName << " Stats:\n";
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << attrDisplay.at(i).at(j);
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// print group member, when setting up team
void Team::printCharacters() {
    std::cout << "Players: ";
    for (auto & player : players) {
        if (player->checkIfPlayer()) {
            std::cout << player->getCharClass() << " ";
        }
    }
    std::cout << "\nNPC: ";
    for (auto & player : players) {
        if (!player->checkIfPlayer()) {
            std::cout << player->getCharClass() << " ";
        }
    }
    std::cout << std::endl;
}

std::vector<Player*> Team::getPlayers() {
    return players;
}

Player* Team::getPlayer(int index) {
    if (index < players.size()) { return players.at(index); }
    else { return nullptr; }
}

// return a (random & alive) player index
int Team::getRandomPlayerIndex() {
    std::vector<int> alivePlayer;
    for (int i = 0; i < players.size(); ++i) {
        if (players.at(i)->getIsAlive()) { alivePlayer.push_back(i); }
    }
    return alivePlayer.at(randomNum(alivePlayer.size()));
}

// return player index with the lowest health (for healing)
int Team::getLowestHPPlayerIndex() {
    int indexPlayerWithLowestLife = 999999;
    for (int i = 0; i < players.size(); ++i) {
        if (players.at(i)->getIsAlive() && indexPlayerWithLowestLife > players.at(i)->getHealth()->x) {
            indexPlayerWithLowestLife = i;
        }
    }
    return indexPlayerWithLowestLife;
}