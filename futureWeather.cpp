//#include <CityLinkedList.cpp>
#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <map>
#include <string>

size_t WriteCallback2(void *contents, size_t size, size_t nmemb,
                      std::string *s) {
  size_t newLength = size * nmemb;
  size_t oldLength = s->size();
  try {
    s->resize(oldLength + newLength);
  } catch (std::bad_alloc &e) {
    return 0;
  }

  std::copy((char *)contents, (char *)contents + newLength,
            s->begin() + oldLength);
  return size * nmemb;
}

std::string weatherCodeToDescription(int code) {
  std::map<int, std::string> weatherCodes = {
      {0, "Clear sky"},
      {1, "Mainly clear"},
      {2, "Partly cloudy"},
      {3, "Overcast"},
      {45, "Fog"},
      {48, "Depositing rime fog"},
      {51, "Light drizzle"},
      {53, "Moderate drizzle"},
      {55, "Dense drizzle"},
      {56, "Light freezing drizzle"},
      {57, "Dense freezing drizzle"},
      {61, "Slight rain"},
      {63, "Moderate rain"},
      {65, "Heavy rain"},
      {66, "Light freezing rain"},
      {67, "Heavy freezing rain"},
      {71, "Slight snow fall"},
      {73, "Moderate snow fall"},
      {75, "Heavy snow fall"},
      {77, "Snow grains"},
      {80, "Slight rain showers"},
      {81, "Moderate rain showers"},
      {82, "Violent rain showers"},
      {85, "Slight snow showers"},
      {86, "Heavy snow showers"},
      {95, "Slight thunderstorm"},
      {96, "Thunderstorm with slight hail"},
      {99, "Thunderstorm with heavy hail"}};
  return weatherCodes[code];
}

void futureWeather() {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://api.open-meteo.com/v1/"
                     "forecast?latitude=52.52&longitude=13.41&daily=weather_"
                     "code%2Ctemperature_2m_max%2Ctemperature_2m_min&"
                     "temperature_unit=fahrenheit&timezone=auto");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback2);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    struct curl_slist *headers = NULL;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    Json::Value jsonData;
    Json::CharReaderBuilder jsonReaderBuilder;
    std::unique_ptr<Json::CharReader> const reader(
        jsonReaderBuilder.newCharReader());

    JSONCPP_STRING errs;
    if (reader->parse(readBuffer.c_str(),
                      readBuffer.c_str() + readBuffer.size(), &jsonData,
                      &errs)) {
      Json::Value times = jsonData["daily"]["time"];
      Json::Value weather_codes = jsonData["daily"]["weather_code"];
      Json::Value max_temps = jsonData["daily"]["temperature_2m_max"];
      Json::Value min_temps = jsonData["daily"]["temperature_2m_min"];

      for (unsigned int i = 0; i < times.size(); i++) {
        std::cout << "Date: " << times[i].asString() << std::endl;
        std::cout << "Weather: "
                  << weatherCodeToDescription(weather_codes[i].asInt())
                  << std::endl;
        std::cout << "Max Temperature: " << max_temps[i].asFloat() << "°F"
                  << std::endl;
        std::cout << "Min Temperature: " << min_temps[i].asFloat() << "°F"
                  << std::endl;
        std::cout << "----------------------------------" << std::endl;
      }
    } else {
      std::cout << "Failed to parse JSON" << std::endl;
    }
  }
}
