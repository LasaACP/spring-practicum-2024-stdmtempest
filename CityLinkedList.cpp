#include "CityLinkedList.h"
#include <cstring>
using namespace std;
/*

Class Library File

*/

City::City() {
  cityName = "";
  population = 0;
  latitude = 0.0;
  longitude = 0.0;
};
City::City(string name, int pop, double lat, double lon) {
  cityName = name;
  population = pop;
  latitude = lat;
  longitude = lon;
}
City::~City() {
  cityName = "";
  population = 0;
  latitude = 0.0;
  longitude = 0.0;
}

string City::toString() {
  string s = this->cityName;
  s += " ";
  s += to_string(this->population);
  s += " ";
  s += to_string(this->latitude);
  s += " ";
  s += to_string(this->longitude);
  return s;
}

node::node(City *a) {
  data = a;
  next = nullptr;
}

node::node(City *a, node *n) {
  data = a;
  next = n;
}

// Constructor
CityLinkedList::CityLinkedList() { head = nullptr; }

// Destructor
CityLinkedList::~CityLinkedList() {
  node *current = head;
  while (current != nullptr) {
    node *temp = current;
    current = current->next;
    delete temp;
  }
  head = nullptr;
}

// add(value)				//Adds a new value to the end of this
// list.
void CityLinkedList::add(City c) {
  node *newNode = new node(new City(c), nullptr);
  if (head == nullptr) {
    head = newNode;
  } else {
    node *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
}

// clear()					//Removes all elements from this
// list.
void CityLinkedList::clear() {
  node *current = head;
  while (current != nullptr) {
    node *temp = current;
    current = current->next;
    delete temp;
  }
  head = nullptr;
}

// getLat takes city name as input, outputs its latitude
double CityLinkedList::getLat(string name) {
  node *current = head;
  while (current != nullptr) {
    if (!(current->data->cityName.compare(name))) {
      return current->data->latitude;
    } else {
      current = current->next;
    }
  }
  return 0.0;
}

// getLon takes city name as input, outputs its longitude
double CityLinkedList::getLon(string name) {
  node *current = head;
  while (current != nullptr) {
    if (!(current->data->cityName.compare(name))) {
      return -1 * (current->data->longitude);
    } else {
      current = current->next;
    }
  }
  return 0.0;
}

// toString()				//Converts the list to a printable
// string representation.
string CityLinkedList::toString() {
  if (head == nullptr) {
    return "\n";
  } else {
    node *current = head;
    string s = "";
    while (current != nullptr) {
      s += current->data->toString() + "\n";
      current = current->next;
    }
    return s;
  }
}