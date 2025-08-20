#ifndef INC_3_FINALDOMAIN314_TURNENGINE_HPP
#define INC_3_FINALDOMAIN314_TURNENGINE_HPP

#include <vector>
#include <algorithm>
#include "../Domain/Domain.h"
#include "Team.hpp"

using namespace Domain;

class TurnEngine {
public:
    TurnEngine(std::vector<Team*> teams);
    ~TurnEngine();
    int nextTurnsPlayerID();
    void deletePlayerByID(int id);

private:
    std::vector<Vector3*> playerList;
    Vector3* makePlayer(Player* player);
};


#endif //INC_3_FINALDOMAIN314_TURNENGINE_HPP
