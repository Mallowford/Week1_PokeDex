#include <iostream>
#include <curl/curl.h>

using std::cout;

int main() {

  CURL* curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://pokeapi.co/api/v2/pokemon/kyogre/");

    res = curl_easy_perform(curl);
  };

  if (res != CURLE_OK) {
    fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
  };

  curl_easy_cleanup(curl);

  return 0;
};