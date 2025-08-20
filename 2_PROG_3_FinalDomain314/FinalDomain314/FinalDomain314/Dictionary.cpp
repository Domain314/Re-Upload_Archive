#include "Dictionary.h"


Dictionary::Dictionary() {
    this->mesSnippets = {
            {10, "Choose teams:\n",},
            {20, " Action",},
            {21, " Use Item",},
            {22, "Choose a target. (Arrow-Keys), (Enter)",},
            {30, "",},
    };
    this->npcNames = {
            {"Klaus"},
            {"Martin"},
            {"Babsi"},
            {"Günther"},
            {"Mathilda"},
            {"Siegfried"},
            {"Heinrich"}
    };

    // Warrior, Mage, Priest, Skeleton, Custom
    // HP, MP,      ATK, INT, DEF, KRIT, SPEED
    this->charClasses = {
            {'w', {150, 30,     3, 1, 3, 2, 1000}},
            {'m', {100, 120,    1, 1, 1, 2, 1300}},
            {'p', {110, 200,     1, 1, 1, 3, 900}},
            {'s', {60, 20,      2, 1, 1, 1, 800}},
            {'c', {100, 0,    0, 0, 0, 1, 1000}}
    };

    this->spellStd.push_back(new Spell("Attack", 1, false, false, false, {-3,1, 1, 1, 1, 1, 1}, "Standard Damage.", new Vector2(1,1)));
    this->spellStd.push_back(new Spell("Use", 1, false, false, false,{0,0, 0, 0, 0, 0, 0}, "Use an item.", new Vector2(1,1)));

    this->spellTreeW = {
            new Spell("Add Moral", 1, true, true, true, {5,5, 3, 3, 2, 2, 1}, "Buff all group member.", new Vector2(0,1)),
            new Spell("Brutal Hit", 1, false, false, false, {-8,1, 3, 1, 1, 3, 1}, "Make a devastating Hit", new Vector2(0,1)),
            new Spell("Demoralize", 10, true, true, true, {-5,2, 0, 0, 0, 0, 10}, "Debuff all Groupmember.", new Vector2(0,1)),
            new Spell("Roundhouse Kick", 10, true, false, false, {-15,20, 1, 1, 1, 1, 1}, "Buff all Groupmember.", new Vector2(0,1)),

    };
    this->spellTreeM = {
            new Spell("Fire Bolt", 1, false, true, false, {-10, 5, 1, 1, 1, 1, 1}, "Firaaaaah.", new Vector2(0,1)),
            new Spell("Ice Bolt", 1, false, true, false, {-10, 5, 1, 1, 1, 1, 1}, "Cold as ice.", new Vector2(0,1)),
            new Spell("Vulcan", 10, true, true, false, {-5, 20, 1, 1, 1, 1, 1}, "Cleanse with lava.", new Vector2(0,1)),
            new Spell("Blizzard", 10, true, true, false, {-6, 20, 1, 1, 1, 1, 1}, "Not the Game-Studio.", new Vector2(0,1)),

    };
    this->spellTreeP = {
            new Spell("Flash Heal", 1, false, true, false, {20, 5, 0, 0, 0, 6, 0}, "Higher chance to krit.", new Vector2(0,1)),
            new Spell("Regeneration", 1, false, true, false, {30, 5, 0, 0, 0, 0, 0}, "Safe heal", new Vector2(0,1)),
            new Spell("Circle Heal", 10, true, true, false, {20, 20, 0, 0, 0, 0, 0}, "Heal 'em all!.", new Vector2(0,1)),
            new Spell("Heal Spring", 10, true, true, false, {15, 20, 0, 0, 0, 4, 0}, "Swirly heal.", new Vector2(0,1))

    };
    this->spellTreeS = {
            new Spell("Bite", 1, false, false, false, {-2, 1, 1, 1, 1, 1, 1}, "Bites you in the a**.", new Vector2(0,1)),
            new Spell("Growl", 1, false, false, true, {-5, -1, 0, 0, 0, 0, 0}, "Demonstrate your dominance.", new Vector2(0,1)),
            new Spell("Enrage", 10, false, false, true, {1, 1, 1, 1, 1, 1, 1}, "Buff your mates with anger.", new Vector2(0,1)),
            new Spell("Riot", 10, true, true, false, {-3, 1, 1, 1, 1, 1, 1}, "Chaotic Group Damage.", new Vector2(0,1)),

    };

    this->items = {
            new Item("Grenade", 1, true, false, false, 1, true, {-3,1, 1, 1, 1, 1, 1}, "Explosive joy."),
            new Item("Throw Stone ", 1, false, false, false, 1, true, {-1,1, 1, 1, 1, 1, 1}, "Better then nothing."),
            new Item("Grenade", 1, true, false, false, 1, true, {-3,1, 1, 1, 1, 1, 1}, "Explosive joy."),
            new Item("Throw Stone", 1, false, false, false, 1, true, {-1,1, 1, 1, 1, 1, 1}, "Are you THAT desperate?"),
            new Item("Grenade", 1, true, false, false, 1, true, {-3,1, 1, 1, 1, 1, 1}, "Explosive joy."),
            new Item("Throw Holy Stone", 1, true, false, false, 1, true, {-10,3, 3, 3, 3, 3, 3}, "How do you know it is holy?"),
            new Item("Heal Potion", 1, false, false, false, 3, true, {5,1, 1, 1, 1, 1, 1}, "Restore some HP."),
            new Item("Group Potion", 1, true, false, false, 1, true, {5,1, 1, 1, 1, 1, 1}, "Restore some HP for all"),
            new Item("Heal Potion", 1, false, false, false, 3, true, {5,1, 1, 1, 1, 1, 1}, "Restore some HP."),

    };
}

Dictionary::~Dictionary() {
    for (int i = spellStd.size()-1; i >= 0 ; --i) {
        delete spellStd.at(i);
    }
    for (int i = spellTreeW.size()-1; i >= 0 ; --i) {
        delete spellTreeW.at(i);
    }
    for (int i = spellTreeM.size()-1; i >= 0 ; --i) {
        delete spellTreeM.at(i);
    }
    for (int i = spellTreeP.size()-1; i >= 0 ; --i) {
        delete spellTreeP.at(i);
    }
    for (int i = spellTreeS.size()-1; i >= 0 ; --i) {
        delete spellTreeS.at(i);
    }
    for (int i = items.size()-1; i >= 0 ; --i) {
        delete items.at(i);
    }
}

std::string Dictionary::getMessageSnippet(int key) {
    return mesSnippets.at(key);
}

std::string Dictionary::getRandomNPCName() {
    return npcNames.at(randomNum(npcNames.size()));
}

std::vector<int> Dictionary::getCharClass(char c) {
    return charClasses.at(c);
}

std::vector<Spell*> Dictionary::getSpellTree(char c) {
    switch (c) {
        case 'w': return spellTreeW;
        case 'm': return spellTreeM;
        case 'p': return spellTreeP;
        case 's': return spellTreeS;
        default: return spellTreeW;
    }
}

std::vector<Spell*> Dictionary::getStdSpell() {
    return spellStd;
}

Item* Dictionary::getRandomItem() {
    return items.at(randomNum(items.size()));
}