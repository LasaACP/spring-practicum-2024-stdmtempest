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

  // std::cout << "\tEnter city name: ";
  // string city;
  // getline(cin, city);

  /*http_client client(U("https://api.openweathermap.org/data/2.5"));
  uri_builder builder(U("/weather"));
  builder.append_query(U("q"), utility
      ::conversions::to_string_t(city));
  builder.append_query(U("appid"), U("6671712a2ca189d80eff02bc5f2c8727"));
  http_request request(methods::GET);
  request.set_request_uri(builder.to_string());

  client.request(request).then([](http_response response) {
      return response.extract_json();
      }
  ).then([](web::json::value body) {
          cout << "\tTemperature is " <<
  (body[U("main")][U("temp")].as_double()-273.15)*(9/5+32) << " F" << endl;

      }).wait();


      return 0;
}