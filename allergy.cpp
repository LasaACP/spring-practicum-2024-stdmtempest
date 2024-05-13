#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <string>

void allergyReport() {
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://air-quality-api.open-meteo.com/v1/air-quality?latitude=30.2672&longitude=-97.7431&hourly=us_aqi&timezone=auto");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    struct curl_slist *headers = NULL;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
  }
  curl_easy_cleanup(curl);
}