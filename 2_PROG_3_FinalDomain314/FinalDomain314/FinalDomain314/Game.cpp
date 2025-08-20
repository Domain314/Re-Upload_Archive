#include "Game.hpp"

// De-Constructor
Game::~Game() {
    for (int i = (teams.size()-1); i >= 0; --i) {
        delete teams.at(i);
    }
    delete dictionary;
    delete input;
}

// Constructor + initialize game
Game::Game() {
    dictionary = new Dictionary();
    input = new Input();
    Intro* intro = new Intro();
    intro->playIntro();
    delete intro;
    while (true) {
        if (input->getInput() == '.') {
            break;
        }
    }
    setupTeams();
    gameLoop();
}

// print "Choose teams:" and create 2 teams
void Game::setupTeams() {
    std::cout << dictionary->getMessageSnippet(10);
    teams.push_back(new Team(0, dictionary));
    teams.push_back(new Team(1, dictionary));

}

// set up turnEngine and display for a fight.
// repeat rounds, until finalizeTurn() returns a winner Team
// print fight result and ask for next fight. y -> swap loserteam and restart gameLoop()
void Game::gameLoop() {
    int winnerTeam = -1;
    turnEngine = new TurnEngine(teams);
    display = new Display(teams);
    display->setCharacters(teams);
    while (true) {
        display->resetAllMessages();

        int id = turnEngine->nextTurnsPlayerID();
        int teamNum = (id / 10000) - 1;
        Player* playerThisTurn = teams.at(teamNum)->getPlayerByID(id);
        display->markPlayer(teamNum, playerThisTurn->getIndex(), false);

        if (playerThisTurn->checkIfPlayer()) {
            playerTurn(playerThisTurn, teamNum);
        } else {
            NPCTurn(playerThisTurn, teamNum);
        }
        winnerTeam = finalizeTurn();
        if (winnerTeam != -1) {
            break;
        }

    }
    display->printDisplays();
    int loserTeam = (winnerTeam+1)%2;
    std::cout << "Team " << winnerTeam+1 << " wins!" << std::endl;
    std::cout << "Team " << loserTeam+1 << " loses!" << std::endl;
    delete display;
    delete turnEngine;
    std::cout << "next round? (y)es\n";
    if (input->_getChar() == 'y') {
        delete teams.at(loserTeam);
        teams.at(winnerTeam)->levelUpGroup();
        teams.at(loserTeam) = new Team(loserTeam, dictionary);
        gameLoop();
    }
}

// check if all players of a team are dead. return opposing (winner) teamNum
int Game::finalizeTurn() {
    display->unMarkAll();
    display->setCharacters(teams);
    int alive;
    for (int j = 0; j < 2; ++j) {
        alive = teams.at(j)->getPlayers().size();
        for (int i = 0; i < teams.at(j)->getPlayers().size(); ++i) {
            alive = teams.at(j)->getPlayer(i)->getIsAlive() ? alive : --alive;
        }
        if (alive <= 0) {
            return ((j+1)%2);
        }
    }
    return -1;
}

// display menu to choose spell or item.
// choose target and initialize usage of a skill (spells & items inherit from skill)
// roll dice for a randomItem
void Game::playerTurn(Player* player, int teamNum) {
    Skill* chosenSkill = nullptr;
    bool isItem;
    do {
        display->playersTurnMessage("Player ", player->getName(), player->getMana()->x, teamNum);
        display->printDisplays();
        chosenSkill = listSkills(player->getSkills());
        isItem = false;
        if (chosenSkill == nullptr) { continue; }
        if (chosenSkill->getName() == "Use") {
            if (player->getInventory().empty()) { chosenSkill = nullptr; continue; }
            display->playersTurnMessage("Player ", player->getName(), player->getMana()->x, teamNum);
            chosenSkill = listItems(player->getInventory());
            isItem = true;
        }
    } while (chosenSkill == nullptr);

    display->resetAllMessages();
    display->addMessage(dictionary->getMessageSnippet(22));
    Vector2* target = chooseTarget(chosenSkill->getIsGroupSpell());
    //std::cout << "Target's pos: "<< target->x << target->y << std::endl;
    if (target->x == -1 && target->y == -1) {
        display->markPlayer(teamNum, player->getIndex(), false);
        playerTurn(player, teamNum);
    } else {
        if ((chosenSkill->getIsMagic() && player->getMana()->x >= chosenSkill->getAttributes().at(1)) || !chosenSkill->getIsMagic() ) {
            player->getMana()->x -= chosenSkill->getAttributes().at(1);
            usePlayerSpell(player, teamNum, chosenSkill, target);
        } else if (chosenSkill->getIsMagic() && player->getMana()->x < chosenSkill->getAttributes().at(1)){
            playerTurn(player, teamNum);
        }
    }
    getRandomItem(player);
    if (isItem) {
        subtractItemUse(player, chosenSkill);
    }
    delete target;
}

// roll dice for a random item
void Game::getRandomItem(Player* player) {
    if (randomNum(CHANCE_FOR_ITEM) == 0) {
        Item* newItem = new Item(dictionary->getRandomItem());
        player->addItem(newItem);
        display->addMessage(player->getName() + " found " + newItem->getName() + "!");
        display->printDisplays();
        usleep(NPC_SLEEP);
    }
}

// search for item in inventory and subtract one "quantity"
void Game::subtractItemUse(Player* player, Skill* skill) {
    for (int i = 0; i < player->getInventory().size(); ++i) {
        if (player->getInventory().at(i)->getName() == skill->getName()) {
            player->itemUsage(i);
            break;
        }
    }
}

// if group spell -> cast spell on all targets
void Game::usePlayerSpell(Player* player, int teamNum, Skill* chosenSkill, Vector2* target) {
    if (chosenSkill->getIsGroupSpell()) {
        for (int i = 0; i < teams.at(target->x)->getPlayers().size(); ++i) {
            castSpell(player, teams.at(target->x)->getPlayer(i), chosenSkill);
        }
    } else {
        castSpell(player, teams.at(target->x)->getPlayer(target->y), chosenSkill);
    }
}

// calculate spell power (not very balanced)
void Game::castSpell(Player* player, Player* target, Skill* skill) {
    if (skill->getIsBuff()) {
        target->buffStats(skill->getAttributes());
    } else if (skill->getAttributes().at(0) > 0 && target->getHealth()->x > 0) {
        int healAmount = player->getStat("INT") * skill->getAttributes().at(0);
        if (randomNum(10) <= player->getStat("KRIT") + skill->getAttributes().at(5)) {
            healAmount *= 2;
            executeSpell(target, healAmount);
            // mark krit in console
        } else {
            executeSpell(target, healAmount);
        }
    } else if (target->getHealth()->x <= 0) {
        executeSpell(target, 0);
    } else {
        int multiplier = skill->getIsMagic() ?
                player->getStat("INT") + skill->getAttributes().at(3) :
                player->getStat("ATK") + skill->getAttributes().at(2);
        int damage = skill->getAttributes().at(0) * multiplier - target->getStat("DEF");
        if (randomNum(10) <= player->getStat("KRIT") + skill->getAttributes().at(5)) {
            damage *= 2;
            executeSpell(target, damage);
            // mark krit in console
        } else {
            executeSpell(target, damage);
        }
    }
}

// display a damage/heal message in a fitting colour and execute Spell
void Game::executeSpell(Player* target, int amount) {
    if (amount < 0) {
        amount += randomNum(10);
        display->addMessage(BOLDRED + target->getName() + " lost " + std::to_string(amount*-1) + "HP" + RESET);
    } else if (amount == 0) {
        display->addMessage("Nothing happend.");
    } else {
        amount += randomNum(10);
        display->addMessage(BOLDGREEN + target->getName() + " healed " + std::to_string(amount) + "HP" + RESET);
    }
    target->changeHealth(amount);
    if (!target->getIsAlive()) {
        turnEngine->deletePlayerByID(target->getID());
    }
    display->printDisplays();
    usleep(NPC_SLEEP);
}

// Menu for choosing a target
Vector2* Game::chooseTarget(bool isGroupSpell) {
    Vector2* target = new Vector2();
    display->markPlayer(target->x, target->y, isGroupSpell);
    display->printDisplays();
    while (true) {
        switch (input->getInput()) {
            case 'w':
                display->unMarkPlayer(target->x, target->y, isGroupSpell);
                target->x = (target->x + 1) % 2;
                display->markPlayer(target->x, target->y, isGroupSpell);
                break;
            case 's':
                display->unMarkPlayer(target->x, target->y, isGroupSpell);
                target->x = (target->x + 1) % 2;
                display->markPlayer(target->x, target->y, isGroupSpell);
                break;
            case 'a':
                display->unMarkPlayer(target->x, target->y, isGroupSpell);
                target->y = target->y - 1 < 0 ? teams.at(target->x)->getPlayers().size()-1 : target->y - 1;
                display->markPlayer(target->x, target->y, isGroupSpell);
                break;
            case 'd':
                display->unMarkPlayer(target->x, target->y, isGroupSpell);
                target->y = (target->y + 1) % teams.at(target->x)->getPlayers().size();
                display->markPlayer(target->x, target->y, isGroupSpell);
                break;
            case ',':
                display->unMarkPlayer(target->x, target->y, isGroupSpell);
                target->x = -1; target->y = -1;
                std::cout<<"esc pressed";
                return target;
                break;
            case '.':
                if (teams.at(target->x)->getPlayers().size() > target->y) {
                    return target;
                }


        }
        display->printDisplays();
    }
}

// display all spells and let the player choose one
Skill* Game::listSkills(std::vector<Spell*> spells) {
    for (auto & spell : spells) {
        display->addMessage(" " + spell->getName());
    }
    int dec = chooseAction(0, spells.size()-1);
    if (dec == -1) {
        return nullptr;
    } else {
        return spells.at(dec);
    }
}

// display all items and let the player choose one
Skill* Game::listItems(std::vector<Item*> items) {
    for (auto & item : items) {
        display->addMessage(" " + std::to_string(item->getQuantity()) + "x " + item->getName() + ": " + item->getQuote());
    }
    int dec = chooseAction(0, items.size()-1);
    if (dec == -1) {
        return nullptr;
    } else {
        return items.at(dec);
    }
}

// Menu for choosing an action (spell/item)
int Game::chooseAction(int min, int max) {
    int decision = min;
    display->markConsoleLine(decision);
    display->printDisplays();
    while (true) {
        switch (input->getInput()) {
            case 'w':
                display->unMarkConsoleLine(decision);
                decision = decision-1 < min ? max : --decision;
                display->markConsoleLine(decision);
                break;
            case 's':
                display->unMarkConsoleLine(decision);
                decision = decision+1 > max ? min : ++decision;;
                display->markConsoleLine(decision);
                break;
            case ',':
                return -1; break;
            case '.':
                return decision; break;
        }
        display->printDisplays();
    }
}

// calculate NPC choice for spell and target/s, simulate thinking process and execute the decisions
void Game::NPCTurn(Player* player, int teamNum) {
    display->playersTurnMessage("NPC ", player->getName(), teamNum);
    display->printDisplays();
    usleep(NPC_SLEEP);

    Skill* chosenSkill = nullptr;
    if (randomNum(3) == 0 || player->getCharClass() == 'm' || player->getCharClass() == 'p') {
        int counter = 0;
        while (chosenSkill == nullptr) {
            chosenSkill = player->getSkills().at(randomNum(player->getSkills().size()));

            if (counter++ > 10) { chosenSkill = player->getSkills().at(0); }
        }

    } else {
        chosenSkill = player->getSkills().at(0);
    }

    display->animateDecision(player->getName());
    display->addMessage(player->getName() + " choose " + chosenSkill->getName());
    display->printDisplays();

    int targetPlayer;
    int targetTeam = chosenSkill->getAttributes().at(0) > 0 ? teamNum : (teamNum+1)%2;
    if (targetTeam == teamNum) {
        targetPlayer = teams.at(targetTeam)->getLowestHPPlayerIndex();
    }
    targetPlayer = teams.at(targetTeam)->getRandomPlayerIndex();

    display->animateDecision(player->getName());
    display->markPlayer(targetTeam, targetPlayer, chosenSkill->getIsGroupSpell());
    display->addMessage(player->getName() + " choose " + teams.at(targetTeam)->getPlayers().at(targetPlayer)->getName());
    display->printDisplays();

    if (chosenSkill->getIsGroupSpell()) {
        for (int i = 0; i < teams.at(targetTeam)->getPlayers().size(); ++i) {
            castSpell(player, teams.at(targetTeam)->getPlayer(i), chosenSkill);
        }
    }
    castSpell(player, teams.at(targetTeam)->getPlayer(targetPlayer), chosenSkill);
    display->printDisplays();
}