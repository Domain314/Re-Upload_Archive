#ifndef INC_3_FINALDOMAIN314_SKILL_HPP
#define INC_3_FINALDOMAIN314_SKILL_HPP

#include <string>
#include <vector>

class Skill {
public:
    Skill(std::string name, int amount, bool isGroupSpell, bool isMagic, bool isBuff, std::vector<int> attributes);
    Skill();
    virtual ~Skill();
    std::string getName();
    int getValue();
    bool getIsGroupSpell();
    bool getIsMagic();
    bool getIsBuff();

    std::vector<int> getAttributes();

protected:
    std::string name;
    int value;
    bool isGroupSpell;
    bool isMagic;
    bool isBuff;
    std::vector<int> attributes;
};


#endif //INC_3_FINALDOMAIN314_SKILL_HPP
