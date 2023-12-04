#ifndef SET_H
#define SET_H

#include <unordered_set>
#include <vector>
#include <algorithm>
#include <set>
#include "song.h"
using namespace std;

class SongRecommendationSet {
public:
    // Basic Operations
    void insert(const Song& song);
    int getSetSize();
    Song getHighestScore();

    // Filter Functions
    void filterByGenre(string genre);
    void filterByYear(int year);
    void filterByStreamingCount(double streamingCount);
    void filterByDuration(int duration);
    void filterByRating(string rating);
    void filterByArtist(string artist); // not used

    // Debug Functions
    void printSetSize();
    void printSetSongs();
    void printTop10();

private:
    // Data structures
    std::set<Song> songSet; // Auto sorts by value
    std::set<Song> tempSongSet; // Temp songSet for filtering/sorting
};

#endif