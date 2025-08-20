//Dictionary for all items, skills, messages,..
#ifndef INC_3_FINALDOMAIN314_DICTIONARY_H
#define INC_3_FINALDOMAIN314_DICTIONARY_H

#include <map>
#include <string>
#include <vector>
#include "Spell.hpp"
#include "Item.hpp"


class Dictionary {
public:
    Dictionary();
    ~Dictionary();
    std::string getMessageSnippet(int key);
    std::string getRandomNPCName();
    std::vector<int> getCharClass(char c);
    std::vector<Spell*> getSpellTree(char c);
    std::vector<Spell*> getStdSpell();
    Item* getRandomItem();

private:
    std::map<int, std::string> mesSnippets;
    std::vector<std::string> npcNames;
    std::map<char, std::vector<int>> charClasses;
    std::vector<Spell*> spellStd;
    std::vector<Spell*> spellTreeW;
    std::vector<Spell*> spellTreeM;
    std::vector<Spell*> spellTreeP;
    std::vector<Spell*> spellTreeS;
    std::vector<Item*> items;
};


#endif //INC_3_FINALDOMAIN314_DICTIONARY_H
