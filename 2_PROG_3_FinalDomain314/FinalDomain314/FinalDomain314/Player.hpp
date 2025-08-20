#ifndef INC_3_FINALDOMAIN314_PLAYER_HPP
#define INC_3_FINALDOMAIN314_PLAYER_HPP

#include <vector>
#include "Entity.hpp"
#include "Skill.hpp"
#include "Item.hpp"
#include "Spell.hpp"
#include "Spelltree.hpp"
#include "Dictionary.h"

class Player : public Entity {
public:
    Player(std::vector<int> charClass, int ID, char c, Dictionary* dictionary, bool isPlayer);
    ~Player();

    std::vector<Spell*> getSkills();
    std::vector<Item*> getInventory();

    void addItem(Item* item);
    void itemUsage(int index);

    void decideOnSpellTree();

private:
    std::vector<Spell*> spells;
    std::vector<Item*> inventory;
    Spelltree* spelltree;

};


#endif //INC_3_FINALDOMAIN314_PLAYER_HPP
