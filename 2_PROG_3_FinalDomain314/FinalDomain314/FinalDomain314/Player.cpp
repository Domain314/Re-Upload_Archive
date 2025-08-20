#include "Player.hpp"

Player::Player(std::vector<int> cClass, int ID, char charClass, Dictionary* dictionary, bool isPlayer) : Entity(cClass, ID, charClass, isPlayer){
    this->charClass = charClass;

    this->spelltree = new Spelltree(dictionary->getSpellTree(charClass));
    spells.push_back(new Spell(dictionary->getStdSpell().at(0)));
    if (isPlayer) {
        spells.push_back(new Spell(dictionary->getStdSpell().at(1)));
    } else {
        spells.push_back(new Spell(spelltree->getSpell(0)));
        spells.push_back(new Spell(spelltree->getSpell(1)));
    }
}

Player::~Player() {
    delete spelltree;
    for (int i = inventory.size()-1; i >= 0; --i) {
        delete inventory.at(i);
    }
    for (int i = (spells.size()-1); i >= 0; --i) {
        delete spells.at(i);
    }
    std::vector<Item*>().swap(inventory);
}

std::vector<Spell*> Player::getSkills(){
    return spells;
}

std::vector<Item*> Player::getInventory(){
    return inventory;
}

void Player::decideOnSpellTree() {
    clearScreen();
    fflush(stdin);
    std::cout << "Choose a spell to learn." << std::endl;
    if (spelltree->getValue() == 0) {
        std::cout << "1. " << spelltree->getSpell(0)->printSpell() << "\n";
        std::cout << "2. " << spelltree->getSpell(1)->printSpell() << "\n";
        while (true) {
            int c = 0;
            std::cin >> c;
            if (c == 1 || c == 2) {
                spells.push_back(spelltree->getSpell(c-1));
                spelltree->addValue(1);
                break;
            }
        }
    } else if (spelltree->getValue() == 1) {
        std::cout << "1. " << spelltree->getSpell(2)->printSpell() << "\n";
        std::cout << "2. " << spelltree->getSpell(3)->printSpell() << "\n";
        while (true) {
            int c = 0;
            std::cin >> c;
            if (c == 1 || c == 2) {
                spells.push_back(spelltree->getSpell(c+1));
                spelltree->addValue(1);
                break;
            }
        }
    }
}

void Player::addItem(Item *item) {
    if (inventory.empty()) {
        inventory.push_back(item);
    } else {
        bool added = false;
        for (int i = 0; i < inventory.size(); ++i) {
            if (inventory.at(i)->getName() == item->getName()) {
                inventory.at(i)->addQuantity(1);
                added = true;
            }
        }
        if (!added) {
            inventory.push_back(item);
        }
    }
}

void Player::itemUsage(int index) {
    if (inventory.at(index)->subtractQuantity()) {
        delete inventory.at(index);
        inventory.erase(inventory.begin()+index);
    };
}


