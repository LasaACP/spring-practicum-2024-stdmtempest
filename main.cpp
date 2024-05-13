#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb,
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

double kelvinToFahrenheit(double kelvin) {
  return ((kelvin - 273.15) * 9 / 5) + 32;
}

double kelvinToCelsius(double kelvin) { return kelvin - 273.15; }

int main() {
  std::cout << "\t+----------------------------------+" << std::endl;
  std::cout << "\t\tSTDM Tempest v.1" << std::endl;
  std::cout << "\t+----------------------------------+" << std::endl;
  std::cout << "\tEnter city name: ";
  std::string city;
  getline(std::cin, city);
  std::cout << "\t+----------------------------------+" << std::endl;

  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     ("https://api.openweathermap.org/data/2.5/weather?q=" +
                      city + "&appid=6671712a2ca189d80eff02bc5f2c8727")
                         .c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
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
      std::string weather_main = jsonData["weather"][0]["main"].asString();
      std::string weather_description =
          jsonData["weather"][0]["description"].asString();
      double temp_kelvin = jsonData["main"]["temp"].asDouble();
      double feels_like_kelvin = jsonData["main"]["feels_like"].asDouble();

      std::cout
          << "Do you want the temperature in Fahrenheit or Celsius? (F/C): ";
      char temp_unit;
      std::cin >> temp_unit;

      double temp, feels_like;
      if (temp_unit == 'F' || temp_unit == 'f') {
        temp = kelvinToFahrenheit(temp_kelvin);
        feels_like = kelvinToFahrenheit(feels_like_kelvin);
      } else {
        temp = kelvinToCelsius(temp_kelvin);
        feels_like = kelvinToCelsius(feels_like_kelvin);
      }

      time_t t = time(0);
      struct tm *now = localtime(&t);
      std::cout << "Here is the weather in " << city << " on "
                << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'
                << now->tm_mday << std::endl;
      std::cout << "Main: " << weather_main << std::endl;
      std::cout << "Description: " << weather_description << std::endl;
      std::cout << "Temperature: " << temp << std::endl;
      std::cout << "Feels Like: " << feels_like << std::endl;
    } else {
      std::cout << "Failed to parse JSON" << std::endl;
    }
  }
  return 0;
}

// run with g++ main.cpp -ljsoncpp -lcurl -o STDMTempestv2