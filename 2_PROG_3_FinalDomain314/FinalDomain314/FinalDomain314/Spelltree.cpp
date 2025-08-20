#include "Spelltree.hpp"

// Constructor
Spelltree::Spelltree(std::vector<Spell*> spellTree) {
    value = 0;
    amount = 0;
    for (auto & i : spellTree) {
        this->tree.push_back( new Spell(i));
        amount++;
    }
}

// De-Constructor
Spelltree::~Spelltree() {
    for (int i = tree.size()-1; i >= 0; --i) {
        delete getSpell(i);
    }
}

Spell* Spelltree::getSpell(int index) {
    return tree.at(index);
}

int Spelltree::getValue() {
    return value;
}

void Spelltree::addValue(int value) {
    this->value += value;
}