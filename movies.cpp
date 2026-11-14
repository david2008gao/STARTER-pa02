// movies.cpp
// Author: David Gao
// All class declarations related to defining a single movie go here
// The ordering least to greatest is: rating, then alphabetical

#include "movies.h"
#include <iostream>
#include <string>
using namespace std;

Movie::Movie(const string& n, double r){
    name = n;
    rating = r;
}
const string& Movie::getName() const{
    return name;
}
double Movie::getRating() const{
    return rating;
}
bool Movie::operator<(const Movie& rhs) const{
    if (rating == rhs.rating){
        return name < rhs.name;
    }
    return rating > rhs.rating;
}
bool Movie::operator>(const Movie& rhs) const{
    return rhs < *this;
}
bool Movie::operator==(const Movie& rhs) const{
    return (rating == rhs.rating && name == rhs.name);
}
std::ostream& operator<<(std::ostream& os, const Movie& m){
    return os << m.getName() << ", " << m.getRating() << "\n";
}

