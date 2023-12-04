#include "set.h"

// BASIC OPERATIONS //

// Instert Song object into set
void SongRecommendationSet::insert(const Song& song) {
    songSet.insert(song);
}

// Returns int that is the size of the set
int SongRecommendationSet::getSetSize() {
    return songSet.size();
}

// Return Song object with highest score (most compatible song to user)
Song SongRecommendationSet::getHighestScore() {
    return *songSet.rbegin();
}

// FILTER FUNCTIONS //

// Filter out songs that aren't of the preferred genre
void SongRecommendationSet::filterByGenre(string genre) {
    // Make sure temp songSet is empty
    tempSongSet.clear();
    // If genre of Song object matches preferred genre, then add the whole song to the temp songSet
    for (const Song& it : songSet) {
        if (it.genre == genre)
            tempSongSet.insert(it);
    }
    // Main songSet values swapped with new filtered values and temp songSet is cleared
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// Same as above but with preferred year
void SongRecommendationSet::filterByYear(int year) {
    tempSongSet.clear();
    for (const Song& it : songSet) {
        if (it.year == year)
            tempSongSet.insert(it);
    }
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// Same as above but with preferred streaming count
void SongRecommendationSet::filterByStreamingCount(double streamingCount) {
    tempSongSet.clear();
    for (const Song& it : songSet) {
        if (it.streamingCount >= streamingCount)
            tempSongSet.insert(it);
    }
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// Same as above but with preferred duration
void SongRecommendationSet::filterByDuration(int duration) {
    tempSongSet.clear();
    for (const Song& it : songSet) {
        if (it.duration <= duration)
            tempSongSet.insert(it);
    }
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// Same as above but with preferred rating
void SongRecommendationSet::filterByRating(string rating) {
    tempSongSet.clear();
    // Change rating user input to all lowercase (since explicit and clear are all lowercase)
    for (int i = 0; i < rating.size(); i++)
        rating.at(i) = tolower(rating.at(i));
    for (const Song& it : songSet) {
        if (it.rating == rating)
            tempSongSet.insert(it);
    }
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// Same as above but with preferred artist (not used)
void SongRecommendationSet::filterByArtist(string artist) {
    tempSongSet.clear();
    for (const Song& it : songSet) {
        if (find(it.artists.begin(), it.artists.end(), artist) != it.artists.end()) 
            tempSongSet.insert(it);
    }
    this->songSet = tempSongSet;
    tempSongSet.clear();
}

// DEBUG FUNCTIONS //

// DEBUG ONLY: Function for printing songSet size
void SongRecommendationSet::printSetSize() {
    std::cout << "(DEBUG) Size of set: " << songSet.size() << "\n";
}

// DEBUG ONLY: Function for printing all songs in songMap. Prints title and score
void SongRecommendationSet::printSetSongs() {
    for (const Song& it : songSet) {
        std::cout << "(DEBUG) Printing all songs in set:\n";
        std::cout << "Title: " << it.title << "| Score: " << ((it.score * 10.0) / 1) / 10.0 << "\n";
    }
}

// DEBUG ONLY: Prints top 10 Song object titles and scores
void SongRecommendationSet::printTop10() {
    std::cout << "\n(DEBUG) Top 10 songs in the SET:\n";
    int i = 0;
    for (auto it = songSet.rbegin(); it != songSet.rend(); ++it) {
        std::cout << "Title: " << it->title << " | Score: " << ((it->score * 10.0) / 1) / 10.0 << "\n";
        i++;
        if (i == 10) 
            return;
    }
}