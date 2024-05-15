#include "CityDataExtractor.cpp"
#include "CityLinkedList.cpp"

#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <stdlib.h>
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
void clear() {
  // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
  std::cout << "\x1B[2J\x1B[H";
}

double kelvinToCelsius(double kelvin) { return kelvin - 273.15; }

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

void futureWeather(double latitude, double longitude, string city) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" +
                      std::to_string(latitude) +
                      "&longitude=" + std::to_string(longitude) +
                      "&daily=weather_code%2Ctemperature_2m_max%2Ctemperature_"
                      "2m_min&temperature_unit=fahrenheit&timezone=auto";
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
      Json::Value times = jsonData["daily"]["time"];
      Json::Value weather_codes = jsonData["daily"]["weather_code"];
      Json::Value max_temps = jsonData["daily"]["temperature_2m_max"];
      Json::Value min_temps = jsonData["daily"]["temperature_2m_min"];

      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;
      std::cout << "\t\t\t\t\tFuture Weather Forecast in " << city << ": "
                << std::endl;
      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;

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

std::string interpretAQI(int aqi) {
  if (aqi <= 50) {
    return "Good air quality. It's a great day to be outside!";
  } else if (aqi <= 100) {
    return "Moderate air quality. Outdoor activities are generally safe.";
  } else if (aqi <= 150) {
    return "Unhealthy for sensitive groups. If you suffer from respiratory "
           "issues, consider staying indoors.";
  } else if (aqi <= 200) {
    return "Unhealthy air quality. Everyone may begin to experience health "
           "effects; members of sensitive groups may experience         "
           "serious health effects.";
  } else if (aqi <= 300) {
    return "Very unhealthy air quality. Health warnings of emergency "
           "conditions. Entire population is more likely to be affected.";
  } else {
    return "Hazardous air quality. Health alert: everyone may experience more "
           "serious health effects.";
  }
}

void allergyReport(double latitude, double longitude, string city) {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    std::string url =
        "https://air-quality-api.open-meteo.com/v1/air-quality?latitude=" +
        std::to_string(latitude) + "&longitude=" + std::to_string(longitude) +
        "&hourly=us_aqi&timezone=auto";
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
      Json::Value times = jsonData["hourly"]["time"];
      Json::Value us_aqi_values = jsonData["hourly"]["us_aqi"];
      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;
      std::cout << "\t\t\t\t\tAllergy Index for the next 4 days in " << city
                << ": " << std::endl;
      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;

      int count = 0;
      int sumAQI = 0;
      for (unsigned int i = 0; i < times.size(); i++) {
        if (!us_aqi_values[i].isNull()) {
          sumAQI = sumAQI + us_aqi_values[i].asInt();
          count++;
          if (count == 24) {
            count = 0;
            std::cout << "Date: " << times[i].asString() << std::endl;
            std::cout << "US AQI Value: " << sumAQI / 24 << std::endl;
            std::cout << interpretAQI(sumAQI / 24) << std::endl;
            std::cout << "----------------------------------" << std::endl;
            sumAQI = 0;
          }
        }
      }
    } else {
      std::cout << "Failed to parse JSON" << std::endl;
    }
  }
}

int main() {
  char again = 'y';
  while (again == 'y' || again == 'Y') {
    clear();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\t\t\t     \\     /    \n";
    std::cout << "\t\t\t      .-'-.     \n";
    std::cout << "\t\t\t _  .' .-. '.  \n";
    std::cout << "\t\t\t|\\| '-.   .-' '|\n";
    std::cout << "\t\t\t\\|\\'-..-' '-..-'|/\n";
    std::cout << "\t\t\t \\|             |/\n";
    std::cout << "\t\t\t  '-...____...-' \n";

    std::cout << "\t+----------------------------------+" << std::endl;
    std::cout << "\t\tSTDM Tempest v.3" << std::endl;
    std::cout << "\t\tThe Programmer's® Weather App" << std::endl;
    std::cout << "\t\tProudly Endorsed by the Balloon Lobby" << std::endl;
    std::cout << "\t+----------------------------------+" << std::endl;

    CityLinkedList cityList;
    CityDataExtractor cde;
    for (int i = 0; i < cde.CSVlength(); i++) {
      string cityName = cde.csv_array[i][0];
      double latitude = std::stod(cde.csv_array[i][2]);
      double longitude = std::stod(cde.csv_array[i][3]);
      cityList.add(City(cityName, 0, latitude, longitude));
    }
    std::string city;
    double latitude = 0.0;
    double longitude = 0.0;
    while (latitude == 0.0 && longitude == 0.0) {
      std::cout << "\tEnter (US) city name: ";

      getline(std::cin, city);
      std::cout << "\t+----------------------------------+" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "" << std::endl;
      latitude = cityList.getLat(city);
      longitude = cityList.getLon(city);
      if (latitude == 0.0 && longitude == 0.0) {
        std::cout << "City not found. Please enter a valid city name."
                  << std::endl;
      }
    }
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
        bool f = false;
        double temp, feels_like;
        std::string codeToPrint;
        if (temp_unit == 'F' || temp_unit == 'f') {
          temp = kelvinToFahrenheit(temp_kelvin);
          feels_like = kelvinToFahrenheit(feels_like_kelvin);
          f = true;
          codeToPrint = "°F";
        } else {
          temp = kelvinToCelsius(temp_kelvin);
          feels_like = kelvinToCelsius(feels_like_kelvin);
          codeToPrint = "°C";
        }

        time_t t = time(0);
        struct tm *now = localtime(&t);

        // printf("\033c");
        // clear();
        std::cout
            << "-----------------------------------------------------------"
               "-------------------------------------------"
            << std::endl;
        std::cout << "\t\t\t\t\tWeather Right Now In " << city << " on "
                  << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'
                  << now->tm_mday << std::endl;
        std::cout
            << "-----------------------------------------------------------"
               "-------------------------------------------"
            << std::endl;
        std::cout << "Main: " << weather_main << std::endl;
        std::cout << "Description: " << weather_description << std::endl;
        std::cout << "Temperature: " << temp << codeToPrint << std::endl;
        std::cout << "Feels Like: " << feels_like << std::endl;

      } else {
        std::cout << "Failed to parse JSON" << std::endl;
      }

      allergyReport(latitude, longitude, city);

      futureWeather(latitude, longitude, city);

      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;
      std::cout << "-----------------------------------------------------------"
                   "-------------------------------------------"
                << std::endl;
      std::cout << "Would you like to input another city? (y/n): ";
      std::cin >> again;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Add this line
    }
    std::cout << "" << std::endl;

    std::cout << "Ducky hopes to see you soon ;)" << std::endl;
  }

  return 0;
}

// run with g++ main.cpp -ljsoncpp -lcurl -o STDMTempestv3