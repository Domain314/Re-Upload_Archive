#include "Entity.hpp"

// Constructor
Entity::Entity(std::vector<int> cClass, int ID, char charClass, bool isPlayer) {
    this->ID = ID;
    this->isAlive = true;
    this->isPlayer = isPlayer;
    if (isPlayer) {
        std::cout << "Enter name: ";
        std::cin >> this->name;
    }
    this->charClass = charClass;
    this->health = new Vector2(cClass.at(0), cClass.at(0));
    this->mana = new Vector2(cClass.at(1), cClass.at(1));
    setupStats(cClass);
}

// De-Constructor
Entity::~Entity() {
    delete health;
    delete mana;
    delete stats.at("HP");
    delete stats.at("MP");
    delete stats.at("ATK");
    delete stats.at("INT");
    delete stats.at("DEF");
    delete stats.at("KRIT");
    delete stats.at("SPEED");
    std::map<std::string, Vector2*>().swap(stats);
}

// set stats and add a bit of random SPEED to avoid player's turns at same time. But not necessary.
void Entity::setupStats(std::vector<int> cClass) {
    int rnd = randomNum(100);
    stats = {
            {"HP", new Vector2(cClass.at(0), cClass.at(0))},
            {"MP", new Vector2(cClass.at(1), cClass.at(1))},
            {"ATK", new Vector2(cClass.at(2), cClass.at(2))},
            {"INT", new Vector2(cClass.at(3), cClass.at(3))},
            {"DEF", new Vector2(cClass.at(4), cClass.at(4))},
            {"KRIT", new Vector2(cClass.at(5), cClass.at(5))},
            {"SPEED", new Vector2(cClass.at(6) + rnd, cClass.at(6) + rnd)}
    };
}

// reset all stats after a fight.
// Y-> holds original/max value
void Entity::resetStats() {
    stats.at("HP")->x = stats.at("HP")->y;
    stats.at("MP")->x = stats.at("MP")->y;
    stats.at("ATK")->x = stats.at("ATK")->y;
    stats.at("INT")->x = stats.at("INT")->y;
    stats.at("DEF")->x = stats.at("DEF")->y;
    stats.at("KRIT")->x = stats.at("KRIT")->y;
    stats.at("SPEED")->x = stats.at("SPEED")->y;
    health->y = stats.at("HP")->x;
    health->x = health->y;
    mana->y = stats.at("MP")->x;
    mana->x = mana->y;
    isAlive = true;
}

int Entity::getStat(std::string stat) {
    return stats.at(stat)->x;
}

// create vector<int>, add all stats and return it
std::vector<int> Entity::getAllStats() {
    std::vector<int> newStats;
    newStats.push_back(getStat("HP"));
    newStats.push_back(getStat("MP"));
    newStats.push_back(getStat("ATK"));
    newStats.push_back(getStat("INT"));
    newStats.push_back(getStat("DEF"));
    newStats.push_back(getStat("KRIT"));
    newStats.push_back(getStat("SPEED"));
    return newStats;
}

// set stats according to a vector<int>
void Entity::setStats(std::vector<int> newStats) {
    stats.at("HP")->y = newStats.at(0);
    stats.at("MP")->y = newStats.at(1);
    stats.at("ATK")->y = newStats.at(2);
    stats.at("INT")->y = newStats.at(3);
    stats.at("DEF")->y = newStats.at(4);
    stats.at("KRIT")->y = newStats.at(5);
    stats.at("SPEED")->y = newStats.at(6);
    resetStats();
}

void Entity::buffStats(std::vector<int> buffStats) {
    stats.at("ATK")->x += buffStats.at(2);
    stats.at("INT")->x += buffStats.at(3);
    stats.at("DEF")->x += buffStats.at(4);
    stats.at("KRIT")->x += buffStats.at(5);
}

bool Entity::checkIfPlayer() const {
    return isPlayer;
}

bool Entity::getIsAlive() const {
    return isAlive;
}

int Entity::getID() const {
    return ID;
}

bool Entity::checkID(int id) const {
    return this->ID == id;
}

void Entity::setIndex(int index) {
    this->index = index;
}

int Entity::getIndex() const {
    return index;
}

void Entity::setName(std::string name) {
    this->name = name;
}

std::string Entity::getName() {
    return name;
}

char Entity::getCharClass() const {
    return charClass;
}

Vector2* Entity::getHealth() {
    return health;
}

Vector2* Entity::getMana() {
    return mana;
}

void Entity::changeHealth(int amount) {
    this->health->x += amount;
    health->x = health->x > health->y ? health->y : health->x;
    health->x = health->x < 0 ? 0 : health->x;
    isAlive = health->x > 0;
}

std::string Entity::getHealthAsString() {
    if (!isAlive) { return "  † "; }
    if (health->x < 10) { return "  " + std::to_string(health->x) + " "; }
    else if (health->x < 100) { return " " + std::to_string(health->x) + " "; }
    else if (health->x < 1000) { return " " + std::to_string(health->x); }
    else if (health->x < 10000) { return std::to_string(health->x); }
    else { return " " +  std::to_string(health->x/1000) + "k"; }
}
std::string Entity::getNameAsString() const {
    if (isAlive) {
        std::string str = isPlayer ? "p" : "c";
        return str + getCharClass();
    } else {
        return "--";
    }

}

