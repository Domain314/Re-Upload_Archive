#include "Item.hpp"

// Constructors for Dictionary and for copying from Dictionary
Item::Item(std::string name, int value, bool isGroupSpell, bool isMagic, bool isBuff, int quantity, bool isUsable, std::vector<int> attributes, std::string quote) :
Skill(name, value, isGroupSpell, isMagic, isBuff, attributes) {
    this->name = name;
    this->value = value;
    this->isGroupSpell = isGroupSpell;
    this->attributes = attributes;
    this->quantity = quantity;
    this->isUsable = isUsable;
    this->quote = quote;
}
Item::Item(Item* item) {
    this->name = item->getName();
    this->value = item->getValue();
    this->isGroupSpell = item->getIsGroupSpell();
    this->attributes = item->getAttributes();
    this->quantity = item->getQuantity();
    this->isUsable = item->getIsUsable();
    this->quote = item->getQuote();
}

// Lonely De-Constructor
Item::~Item() {}

void Item::addQuantity(int amount) {
    quantity += amount;
}

bool Item::subtractQuantity() {
    quantity -= 1;
    if (quantity <= 0) {
        return true;
    } else {
        return false;
    }
}

int Item::getQuantity() {
    return quantity;
}

bool Item::getIsUsable() {
    return isUsable;
}

std::vector<int> Item::getAttributes() {
    return attributes;
}

std::string Item::getQuote() {
    return quote;
}