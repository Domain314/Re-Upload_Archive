#include "TurnEngine.hpp"

// Constructor
TurnEngine::TurnEngine(std::vector<Team*> teams) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < teams.at(i)->getPlayers().size(); ++j) {
            playerList.push_back(makePlayer(teams.at(i)->getPlayer(j)));
        }
    }
}

// De-Constructor
TurnEngine::~TurnEngine() {
    for (int i = playerList.size() -1; i >= 0 ; --i) {
        delete playerList.at(i);
    }
}

// create an image of a player for the turn-queue.
// X-> actual SPEED for decreasing
// Y-> max/original value
// Z-> PlayerID
Vector3* TurnEngine::makePlayer(Player *player) {
    return new Vector3(player->getStat("SPEED"), player->getStat("SPEED"), player->getID());
}

// search for lowest SPEED->x (shortestTurn)
// subtract shortestTurn from all SPEED->x
// set lowest SPEED->x to SPEED->y (max) and return SPEED->z (playerID)
int TurnEngine::nextTurnsPlayerID() {
    int index = 0;
    int shortestTurn = 10000;
    for (int i = 0; i < playerList.size(); ++i) {
        if (playerList.at(i)->x < shortestTurn) {
            shortestTurn = playerList.at(i)->x;
            index = i;
        }
    }
    for (auto & i : playerList) {
        i->x -= shortestTurn;
    }
    playerList.at(index)->x = playerList.at(index)->y;
    return playerList.at(index)->z;
}

// https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
void TurnEngine::deletePlayerByID(int id) {
    for (int i = 0; i < playerList.size(); ++i) {
        if (playerList.at(i)->z == id) {
            delete playerList.at(i);
            playerList.erase(playerList.begin() + i);
        }
    }
}