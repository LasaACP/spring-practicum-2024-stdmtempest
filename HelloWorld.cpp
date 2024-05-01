// STDMTempest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
