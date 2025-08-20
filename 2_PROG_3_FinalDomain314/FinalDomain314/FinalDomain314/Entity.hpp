// Base class for player and NPC

#ifndef INC_3_FINALDOMAIN314_ENTITY_HPP
#define INC_3_FINALDOMAIN314_ENTITY_HPP

#include "../Domain/Domain.h"
using namespace Domain;

#include <string>
#include <map>
#include <vector>
#include <iostream>


class Entity {
public:
    Entity(std::vector<int> cClass, int ID, char charClass, bool isPlayer);
    virtual ~Entity();
    int getID() const;
    bool checkID(int ID) const;
    void setIndex(int index);
    int getIndex() const;
    bool getIsAlive() const;
    void setName(std::string name);
    std::string getName();
    char getCharClass() const;
    Vector2* getHealth();
    void changeHealth(int amount);
    std::string getHealthAsString();
    std::string getNameAsString() const;
    Vector2* getMana();
    bool checkIfPlayer() const;

    void setupStats(std::vector<int> cClass);
    void resetStats();
    int getStat(std::string stat);
    std::vector<int> getAllStats();
    void buffStats(std::vector<int> buffStats);
    void setStats(std::vector<int> newStats);

protected:
    int ID;
    int index;
    bool isPlayer;
    bool isAlive;
    std::string name;
    char charClass;
    Vector2* health;
    Vector2* mana;
    std::map<std::string, Vector2*> stats;
};


#endif //INC_3_FINALDOMAIN314_ENTITY_HPP
