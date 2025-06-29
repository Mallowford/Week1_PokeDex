#include "../includes/Parser.hpp"

pokemonNode parserHelper(const std::string& pokemon) {
  CURL* curl;
  CURLcode result;
  std::string response_data;
  curl = curl_easy_init();
  pokemonNode pokemonData;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://pokeapi.co/api/v2/pokemon/" + pokemon + "/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
      std::string* response = static_cast<std::string*>(userdata);
      response->append(ptr, size * nmemb);
      return size * nmemb;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    result = curl_easy_perform(curl);
  };

  FILE* fp = nullptr;

  if (result == CURLE_OK) {
    try {
      auto j = nlohmann::json::parse(response_data);
      // Stats
      pokemonData.hp = j["stats"][0]["base_stat"];
      pokemonData.atk = j["stats"][1]["base_stat"];
      pokemonData.def = j["stats"][2]["base_stat"];
      pokemonData.spAtk = j["stats"][3]["base_stat"];
      pokemonData.spDef = j["stats"][4]["base_stat"];
      pokemonData.speed = j["stats"][5]["base_stat"];
      pokemonData.bst = pokemonData.hp + pokemonData.atk
      + pokemonData.def + pokemonData.spAtk + pokemonData.spDef + pokemonData.speed;
      
      // Sprites
      pokemonData.spriteFront = j["sprites"]["front_default"];
      pokemonData.spriteBack = j["sprites"]["back_default"];
      pokemonData.shinySpriteFront = j["sprites"]["front_shiny"];
      pokemonData.shinySpriteBack = j["sprites"]["back_shiny"];

      // Abilities
      for (int i = 0; i < j["abilities"].size(); ++i) {
        std::string abilityName = j["abilities"][i]["ability"]["name"];
        pokemonData.abilities.push_back(abilityName);
      };

      // Moves
      for (int i = 0; i < j["moves"].size(); ++i) {
        std::string moveName = j["moves"][i]["move"]["name"];
        pokemonData.moves.push_back(moveName);
      };     

    }
    catch (const std::exception& e) {
      std::cerr << "JSON Parse Error: " << e.what() << "\n";
    };
  };

};

pokemonNode Parser::ParsePokemon(unsigned int id) {
  return parserHelper(std::to_string(id));
};
pokemonNode Parser::ParsePokemon(const std::string& name) {
  return parserHelper(name);
};