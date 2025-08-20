#ifndef INC_3_FINALDOMAIN314_ITEM_HPP
#define INC_3_FINALDOMAIN314_ITEM_HPP

#include "../Domain/Domain.h"
#include "../Domain/globals.hpp"
#include "Skill.hpp"
#include <string>
#include <vector>

using namespace Domain;

class Item : public Skill{
public:
    Item(
            std::string name,
            int value,
            bool isGroupSpell,
            bool isMagic,
            bool isBuff,
            int quantity,
            bool isUsable,
            std::vector<int> attributes,
            std::string quote);
    Item(Item* item);
    ~Item();

    void addQuantity(int amount);
    int getQuantity();
    bool subtractQuantity();
    bool getIsUsable();
    std::vector<int> getAttributes();
    std::string getQuote();

private:
    int quantity;
    bool isUsable;
    std::string quote;

};


#endif //INC_3_FINALDOMAIN314_ITEM_HPP
