// STDMTempest.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <curl/curl.h>
#include <iostream>
#include <string>

// using namespace std;

int main() {
  std::cout << "\t+----------------------------------+" << std::endl;
  std::cout << "\t\tSTDM Tempest v.1" << std::endl;
  std::cout << "\t+----------------------------------+" << std::endl;

  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://api.openweathermap.org/data/2.5/"
                     "weather?q=Austin&appid=6671712a2ca189d80eff02bc5f2c8727");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    struct curl_slist *headers = NULL;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
  }
  curl_easy_cleanup(curl);
  return 0;

  return 0;
}