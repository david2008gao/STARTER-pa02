// movies.h
// Author: David Gao
// All class declarations related to defining a single movie go here
// The ordering least to greatest is: rating, then alphabetical

#ifndef MOVIES_H
#define MOVIES_H
#include <iostream>
#include <string>
using namespace std;

class Movie {

 public:
    Movie(const string& n, double r);
    const string& getName() const;
    double getRating() const;
    bool operator<(const Movie& rhs) const;
    bool operator>(const Movie& rhs) const;
    bool operator==(const Movie& rhs) const;

 private:

   string name;
	double rating;
};

std::ostream& operator<<(std::ostream& os, const Movie& m);

#endif