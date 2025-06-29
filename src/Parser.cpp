#include "../includes/Parser.hpp"

Parser::Parser() {};

Parser::~Parser() {
  for (int i = 0; i < filesToRemove.size(); ++i) {
    std::string filepath = filesToRemove.at(i);
    if (remove(filepath.c_str()) == 0) {
      std::cout << "File deleted succesfully: " << filepath << "\n";
    }
    else {
      std::cerr << "Error deleting file: " << filepath << "\n";
    };
  };
};

pokemonNode* Parser::parserHelper(const std::string& pokemon) {
  CURL* curl;
  CURLcode result;
  std::string response_data;
  pokemonNode* pokemonData = nullptr;
  
  std::string URL = "https://pokeapi.co/api/v2/pokemon/" + pokemon + "/";

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
      std::string* response = static_cast<std::string*>(userdata);
      response->append(ptr, size * nmemb);
      return size * nmemb;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    result = curl_easy_perform(curl);
  };
  // ALL of the pokemonNode pokemonData

  if (result == CURLE_OK) {
    pokemonData = new pokemonNode();
    
    try {
      auto j = nlohmann::json::parse(response_data);

      // Default Node Parse
      pokemonData->name = j["name"];
      pokemonData->id = j["id"];
      // Stats
      pokemonData->hp = j["stats"][0]["base_stat"];
      pokemonData->atk = j["stats"][1]["base_stat"];
      pokemonData->def = j["stats"][2]["base_stat"];
      pokemonData->spAtk = j["stats"][3]["base_stat"];
      pokemonData->spDef = j["stats"][4]["base_stat"];
      pokemonData->speed = j["stats"][5]["base_stat"];
      pokemonData->bst = pokemonData->hp + pokemonData->atk
      + pokemonData->def + pokemonData->spAtk + pokemonData->spDef + pokemonData->speed;
      
      // Sprites
      pokemonData->spriteFront = j["sprites"]["front_default"];
      pokemonData->spriteBack = j["sprites"]["back_default"];
      pokemonData->shinySpriteFront = j["sprites"]["front_shiny"];
      pokemonData->shinySpriteBack = j["sprites"]["back_shiny"];

      // Abilities
      for (int i = 0; i < j["abilities"].size(); ++i) {
        // std::string abilityName = j["abilities"][i]["ability"]["name"];
        // pokemonData->abilities.push_back(abilityName);
      };

      // Moves
      for (int i = 0; i < j["moves"].size(); ++i) {
        // std::string moveName = j["moves"][i]["move"]["name"];
        // pokemonData->moves.push_back(moveName);
      };     

    }
    catch (const std::exception& e) {
      std::cerr << "JSON Parse Error: " << e.what() << "\n";
    };

    curl_easy_cleanup(curl);
    std::string speciesData;
    CURLcode descriptionCurl;
    curl = nullptr;
    curl = curl_easy_init();

    URL = "https://pokeapi.co/api/v2/pokemon-species/" + pokemon + "/";

    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
        std::string* response = static_cast<std::string*>(userdata);
        response->append(ptr, size * nmemb);
        return size * nmemb;
      });

      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &speciesData);
      descriptionCurl = curl_easy_perform(curl);
    };

    std::cout << (descriptionCurl == CURLE_OK) << "\n";

    if (descriptionCurl == CURLE_OK) {
      try {
        auto j = nlohmann::json::parse(speciesData);
        pokemonData->description = j["flavor_text_entries"][0]["flavor_text"];
      }
      catch (const std::exception& e) {
        std::cerr << "JSON Parse Error " << e.what() << "\n";
      };
    };
  };

  curl_easy_cleanup(curl);

  storedNodes.push_back(pokemonData);

  return pokemonData;
};

pokemonNode* Parser::ParsePokemon(unsigned int id) {
  return parserHelper(std::to_string(id));
};
pokemonNode* Parser::ParsePokemon(const std::string& name) {
  pokemonNode* toReturn = parserHelper(name);
  if (toReturn) {
  };
  return toReturn;
};

std::string Parser::easyImage(pokemonNode* data) {
  FILE* fp = nullptr;
  CURL* curl;
  CURLcode result;
  std::string returnValue;

  curl = curl_easy_init();
  if (curl) {
    try {
      returnValue = "temp/" + data->name + ".png";
      std::cout << returnValue << "\n";
      fp = fopen(returnValue.c_str(), "wb");
      std::string copy(data->spriteFront);
      curl_easy_setopt(curl, CURLOPT_URL, copy.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void *ptr, size_t size, size_t nmemb, FILE *stream) {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
      });

      
      if (fp != NULL) {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        result = curl_easy_perform(curl);
        filesToRemove.push_back(returnValue);
        fclose(fp);
      };
    }
    catch (std::exception& e) {
      std::cerr << "Failed to save file: " << e.what() << "\n"; 
    };
  };

  curl_easy_cleanup(curl);

  return returnValue;
};