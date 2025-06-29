#pragma once
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

class defaultNode {
  public:
    defaultNode() = default;
    unsigned int id;
    std::string name;
    std::string description;
};

class pokemonNode : public defaultNode {
  public:
    pokemonNode() = default;
    int bst;
    // Individual Stats
    int atk;
    int def;
    int hp;
    int spAtk;
    int spDef;
    int speed;
    // Pokemon
    bool isShiny = false;
    std::string spriteFront;
    std::string spriteBack;
    std::string shinySpriteFront;
    std::string shinySpriteBack;
    std::vector<std::string> abilities;
    std::vector<std::string> moves;
};

class abilityNode : public defaultNode {
  public:
    std::vector<std::string> owners;
    bool is_hidden = false;
};

class Parser {
  private:
    pokemonNode* parserHelper(const std::string& pokemon);
    std::vector<std::string> filesToRemove;
    std::vector<pokemonNode*> storedNodes;
  public:
    Parser();
    ~Parser();
    pokemonNode* ParsePokemon(unsigned int id);
    pokemonNode* ParsePokemon(const std::string& name);
    std::string easyImage(pokemonNode* data);
    // abilityNode ParseAbility(const std::string& name);
};