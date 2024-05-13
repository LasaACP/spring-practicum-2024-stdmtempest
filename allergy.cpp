#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <string>

size_t WriteCallback3(void *contents, size_t size, size_t nmemb,
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

void allergyReport() {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://air-quality-api.open-meteo.com/v1/"
                     "air-quality?latitude=30.2672&longitude=-97.7431&hourly="
                     "us_aqi&timezone=auto");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback3);
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

      for (unsigned int i = 0; i < times.size(); i++) {
        if (!us_aqi_values[i].isNull()) {
          std::cout << "Date: " << times[i].asString() << std::endl;
          std::cout << "US AQI Value: " << us_aqi_values[i].asInt()
                    << std::endl;
          std::cout << "----------------------------------" << std::endl;
        }
      }
    } else {
      std::cout << "Failed to parse JSON" << std::endl;
    }
  }
}
