#pragma once
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

class defaultNode {
  public:
    unsigned int id;
    std::string name;
    std::string description;
};

class pokemonNode : public defaultNode {
  public:
    uint16_t bst;
    // Individual Stats
    uint8_t atk;
    uint8_t def;
    uint8_t hp;
    uint8_t spAtk;
    uint8_t spDef;
    uint8_t speed;
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
    pokemonNode parserHelper(...);
  public:
    pokemonNode ParsePokemon(unsigned int id);
    pokemonNode ParsePokemon(const std::string& name);
    // abilityNode ParseAbility(const std::string& name);
};