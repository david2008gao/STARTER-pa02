// Fall'26
// Instructor: Diba Mirza
// Student name: David Gao
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <unordered_map>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> storage;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            Movie m(movieName, movieRating);
            storage.push_back(m);
    }

    movieFile.close();

    sort(storage.begin(), storage.end(), sortByName);

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            for(auto it: storage){
                cout << it;
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    vector<Movie> topMovies;
    vector<string> topPrefixes;

    for (string pre: prefixes){   // binary search on each prefix
        int lo = 0;             // lo is start of prefixes 
        int hi = storage.size();
        while (lo < hi){
            int mid = lo + ((hi - lo) / 2);
            if (storage[mid].getName() < pre){
                lo = mid+1;
            }
            else{
                hi = mid;
            }
        }

                if (lo >= (int)storage.size() || storage[lo].getName().compare(0, pre.size(), pre) != 0) {
            cout << "No movies found with prefix " << pre << endl;
            continue;                                   // skip the rest for this prefix
        }
        vector<Movie> moviesWithPrefix;
        for (int i = lo; i < (int)storage.size() && storage[i].getName().compare(0, pre.size(), pre) == 0; i++){
            moviesWithPrefix.push_back(storage[i]);
        }
        sort(moviesWithPrefix.begin(), moviesWithPrefix.end());
        topMovies.push_back(moviesWithPrefix[0]);
        topPrefixes.push_back(pre);                     // keeps prefix and best movie paired
        for (int i = 0; i < (int)moviesWithPrefix.size(); i++){
            cout << moviesWithPrefix[i];
        }
        cout << '\n';                                   // blank line after each found block
    }
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (int i = 0; i < (int)topMovies.size(); i++){
        cout << "Best movie with prefix " << topPrefixes[i] << " is: " << topMovies[i].getName()
            << " with rating " << topMovies[i].getRating() << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}