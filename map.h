#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <map>
#include <algorithm> // Used for sort()
#include "song.h"
using namespace std;

class SongRecommendationMap {
public:
    // Basic operations
    void insert(const Song& song);
    int getMapSize();
    void sortSongMap();
    Song getHighestScore();

    // Filter functions
    void filterByGenre(string genre);
    void filterByYear(int year);
    void filterByStreamingCount(double streamingCount);
    void filterByDuration(int duration);
    void filterByRating(string rating);
    void filterByArtist(string artist); // not used

    // Debug functions
    void printMapSize();
    void printMapSongs();
    void printTop10();
private:
    // Data structures
    std::map<int, Song> songMap; // Auto sorts by key, so we sort with a vector
    std::map<int, Song> tempSongMap; // Temp songMap for filtering/sorting
};

#endif