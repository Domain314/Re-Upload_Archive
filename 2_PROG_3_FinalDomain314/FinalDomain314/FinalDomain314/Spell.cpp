#include "Spell.hpp"

// Constructors for Dictionary and for copying from Dictionary
Spell::Spell(
        std::string name,
        int value,
        bool isGroupSpell,
        bool isMagic,
        bool isBuff,
        std::vector<int> attributes,
        std::string tooltip,
        Vector2* level) :
Skill(name, value, isGroupSpell, isMagic, isBuff, attributes) {
    this->tooltip = tooltip;
    this->level = level;
}

Spell::Spell(Spell* spell) {
    this->name = spell->getName();
    this->value = spell->getValue();
    this->isGroupSpell = spell->getIsGroupSpell();
    this->isMagic = spell->getIsMagic();
    this->isBuff = spell->getIsBuff();
    for (int i = 0; i < spell->getAttributes().size(); ++i) {
        this->attributes.push_back(spell->getAttributes().at(i));
    }
    this->tooltip = spell->getTooltip();
    this->level = new Vector2(spell->getLevel()->x,spell->getLevel()->y);
}

Spell::~Spell() {
    delete level;
}

std::string Spell::getTooltip() {
    return tooltip;
}

Vector2* Spell::getLevel() {
    return level;
}

std::string Spell::printSpell() {
    std::stringstream text;
    text << name << ": " << tooltip;
    if (isGroupSpell) {
        text << " Group";
    }
    if (isBuff) {
        text << " Buff";
    }
    if (isMagic) {
        text << " costs: " << attributes.at(1) << " MP";
    }
    return text.str();
}