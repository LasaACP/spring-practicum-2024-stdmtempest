// STDMTempest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <curl/cURLpp.hpp>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main()
{
    cout << "\t+----------------------------------+" << endl;
    cout << "\t\tSTDM Tempest v.1" << endl;
    cout << "\t+----------------------------------+" << endl;
    cout << "\tEnter city name: ";
    string city;
    getline(cin, city);

    http_client client(U("https://api.openweathermap.org/data/2.5"));
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
            cout << "\tTemperature is " << (body[U("main")][U("temp")].as_double()-273.15)*(9/5+32) << " F" << endl;

        }).wait();


        return 0;
  
}