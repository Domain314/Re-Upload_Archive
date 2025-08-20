#include "Skill.hpp"

// Constructor
Skill::Skill(std::string name, int value, bool isGroupSpell, bool isMagic, bool isBuff, std::vector<int> attributes) {
    this->name = name;
    this->value = value;
    this->isGroupSpell = isGroupSpell;
    this->isMagic = isMagic;
    this->isBuff = isBuff;
    this->attributes = attributes;
}

Skill::Skill() = default;

// Lonely De-Constructor
Skill::~Skill() {}

std::string Skill::getName() {
    return name;
}

int Skill::getValue() {
    return value;
}

bool Skill::getIsGroupSpell() {
    return isGroupSpell;
}

bool Skill::getIsMagic() {
    return isMagic;
}

bool Skill::getIsBuff() {
    return isBuff;
}

std::vector<int> Skill::getAttributes() {
    return attributes;
}