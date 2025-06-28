#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using std::cout;
using std::string;

size_t write_data(void* ptr, size_t size, size_t memb, FILE *stream);

int main() {

  CURL* curl;
  CURLcode res;
  string response_data;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://pokeapi.co/api/v2/pokemon/kyogre/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
      string* response = static_cast<string*>(userdata);
      response->append(ptr, size * nmemb);
      return size * nmemb;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    res = curl_easy_perform(curl);
    curl_easy_setopt(curl, CURLOPT_URL, "https://pokeapi.co/api/v2/pokemon/kyogre/");
  };

  FILE* fp = nullptr;

  if (res == CURLE_OK) {
    try {
      auto j = json::parse(response_data);
      cout << "Name: " << j["name"] << "\n";
      cout << "ID: " << j["id"] << "\n";
      cout << "Weight: " << j["weight"] << "\n";
      cout << j["sprites"]["front_default"] << "\n";
      string name = j["name"];
      fp = fopen(name.append(".png").c_str(), "wb");
      curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/382.png");
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      if (fp != NULL ) {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);
      };
    }
    catch (const std::exception& e) {
      std::cerr << "JSON parse error: " << e.what() << "\n";
    };
  };

  if (res != CURLE_OK) {
    fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
  };

  curl_easy_cleanup(curl);

  return 0;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written = fwrite(ptr, size, nmemb, stream);
  return written;
};