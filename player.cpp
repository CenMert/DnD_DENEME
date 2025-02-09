#include "Player.h"


using json = nlohmann::json;
namespace fs = std::filesystem;

Player::Player(string name, string characterName) : name(name), characterName(characterName) {}

Player::Player(string name, string characterName, double baseAttack, double health, string story)
    : name(name), characterName(characterName), health(health), baseAttack(baseAttack), story(story)
{
}

Player::Player()
{
	this->name = "-NO NAME-";
	this->characterName = "-NO NAME-";
	this->health = 100;
	this->baseAttack = 10;
	this->story = "-NO STORY-";
}

Player& Player::operator=(const Player& p)
{
	this->name = p.getName();
	this->characterName = p.getCharacterName();
	this->baseAttack = p.getBaseAttack();
	this->health = p.getHealth();
	this->story = p.getStory();

    return *this;
}

string Player::getName() const { return this->name; }

string Player::getCharacterName() const { return this->characterName; }

double Player::getHealth() const { return this->health; }

double Player::getBaseAttack() const { return this->baseAttack; }

string Player::getStory() const { return this->story; }

void Player::setName(const string& name) { this->name = name; }

void Player::setCharacterName(const string& characterName) { this->characterName = characterName; }

void Player::setHealth(const double health) { this->health = health; }

void Player::setBaseAttack(const double baseAttack) { this->baseAttack = baseAttack; }

void Player::setStory(const std::string& story) { this->story = story; }

void Player::display() const 
{
    std::cout << "DISPLAYING A CHARACTER" << "\n\n";
    std::cout <<
        "Name: " << this->name << "\n" <<
        "Character Name: " << this->characterName << "\n" <<
        "Health: " << this->health << "\n" <<
        "BaseAttack: " << this->baseAttack << "\n" <<
        "Story: " << this->story << "\n";
}



