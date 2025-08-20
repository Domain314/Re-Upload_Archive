#ifndef INC_3_FINALDOMAIN314_SPELLTREE_HPP
#define INC_3_FINALDOMAIN314_SPELLTREE_HPP


#include <map>
#include <string>
#include "Spell.hpp"

class Spelltree {
public:
    explicit Spelltree(std::vector<Spell*> spellTree);
    ~Spelltree();
    Spell* getSpell(int index);
    int getValue();
    void addValue(int value);


private:
    int value;
    int amount;
    std::vector<Spell*> tree;
};


#endif //INC_3_FINALDOMAIN314_SPELLTREE_HPP
