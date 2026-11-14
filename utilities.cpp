//utilities.cpp
//Author: David Gao

#include "utilities.h"

bool sortByName(const Movie& a, const Movie& b) {
    return a.getName() < b.getName();
}