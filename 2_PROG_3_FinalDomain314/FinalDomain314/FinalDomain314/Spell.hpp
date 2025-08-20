#ifndef INC_3_FINALDOMAIN314_SPELL_HPP
#define INC_3_FINALDOMAIN314_SPELL_HPP

#include <sstream>
#include "Skill.hpp"
#include "../Domain/Domain.h"
using namespace Domain;

class Spell : public Skill{
public:
    Spell(
            std::string name,
            int value,
            bool isGroupSpell,
            bool isMagic,
            bool isBuff,
            std::vector<int> attributes,
            std::string tooltip,
            Vector2* level
            );
    Spell(Spell* spell);
    ~Spell();
    std::string getTooltip();
    Vector2* getLevel();

    std::string printSpell();

private:
    std::string tooltip;
    Vector2* level;
};


#endif //INC_3_FINALDOMAIN314_SPELL_HPP
