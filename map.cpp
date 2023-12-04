#include "map.h"

// BASIC OPERATIONS //

// Instert Song object into map with new int size as key
void SongRecommendationMap::insert(const Song& song) {
    songMap[songMap.size() + 1] = song;
}

// Returns int that is the size of the map
int SongRecommendationMap::getMapSize() {
    return songMap.size();
}

// Using a vector to sort the Song objects by value since maps can only sort by key
void SongRecommendationMap::sortSongMap() {
    // Initialize vector
    vector<Song> sortedSongVector;
    // Copy elements of map to new vector
    for (const auto& pair : songMap) 
        sortedSongVector.push_back(pair.second);
    // Sort vector
    std::sort(sortedSongVector.begin(), sortedSongVector.end());
    // Clear map
    songMap.clear();
    // Copy elements of sorted vector to new map with indexes as keys
    for (int i = 0; i < sortedSongVector.size(); i++) 
        songMap[i + 1] = sortedSongVector.at(i);
}

// Return Song object with highest score (most compatible song to user)
Song SongRecommendationMap::getHighestScore() {
    return songMap.rbegin()->second;
}

// FILTER FUNCTIONS //

// Filter out songs that aren't of the preferred genre
void SongRecommendationMap::filterByGenre(string genre) {
    // Make sure temp songMap is empty
    tempSongMap.clear();
    // If genre of Song object matches preferred genre, then add the whole song to the temp songMap
    for (const auto& pair : songMap) {
        if (pair.second.genre == genre) 
            tempSongMap[pair.first] = pair.second;
    }
    // Main songMap values swapped with new filtered values and temp songMap is cleared
    this->songMap = tempSongMap;
    tempSongMap.clear();
    // songMap is sorted to give final order of song compatibility
    sortSongMap();
}

// Same as above but with preferred year
void SongRecommendationMap::filterByYear(int year) {
    tempSongMap.clear();
    for (const auto& pair : songMap) {
        if (pair.second.year == year) 
            tempSongMap[pair.first] = pair.second;
    }
    this->songMap = tempSongMap;
    tempSongMap.clear();
    sortSongMap();
}

// Same as above but with preferred streaming count
void SongRecommendationMap::filterByStreamingCount(double streamingCount) {
    tempSongMap.clear();
    for (const auto& pair : songMap) {
        if (pair.second.streamingCount >= streamingCount) 
            tempSongMap[pair.first] = pair.second;
    }
    this->songMap = tempSongMap;
    tempSongMap.clear();
    sortSongMap();
}

// Same as above but with preferred duration
void SongRecommendationMap::filterByDuration(int duration) {
    tempSongMap.clear();
    for (const auto& pair : songMap) {
        if (pair.second.duration <= duration) 
            tempSongMap[pair.first] = pair.second;
    }
    this->songMap = tempSongMap;
    tempSongMap.clear();
    sortSongMap();
}

// Same as above but with preferred rating
void SongRecommendationMap::filterByRating(string rating) {
    tempSongMap.clear();
    // Change rating user input to all lowercase (since explicit and clear are all lowercase)
    for (int i = 0; i < rating.size(); i++) {
        rating.at(i) = tolower(rating.at(i));
    }
    for (const auto& pair : songMap) {
        if (pair.second.rating == rating)
            tempSongMap[pair.first] = pair.second;
    }
    this->songMap = tempSongMap;
    tempSongMap.clear();
    sortSongMap();
}

// Same as above but with preferred artist (not used)
void SongRecommendationMap::filterByArtist(string artist) {
    tempSongMap.clear();
    for (const auto& pair : songMap) {
        if (find(pair.second.artists.begin(), pair.second.artists.end(), artist) != pair.second.artists.end())
            tempSongMap[pair.first] = pair.second;
    }
    this->songMap = tempSongMap;
    tempSongMap.clear();
    sortSongMap();
}

// DEBUG FUNCTIONS //

// DEBUG ONLY: Function for printing songMap size
void SongRecommendationMap::printMapSize() {
    std::cout << "(DEBUG) Size of map: " << songMap.size() << "\n";
}

// DEBUG ONLY: Function for printing all songs in songMap. Prints title and score
void SongRecommendationMap::printMapSongs() {
    for (const auto& pair : songMap) {
        std::cout << "(DEBUG) Printing all songs in map:\n";
        std::cout << "Title: " << pair.second.title << "| Score: " << ((pair.second.score * 10.0) / 1) / 10.0 << "\n";
    }
}

// DEBUG ONLY: Prints top 10 Song object titles and scores
void SongRecommendationMap::printTop10() {
    std::cout << "\n(DEBUG) Top 10 songs in the MAP:\n";
    int i = 0;
    for (auto it = songMap.rbegin(); it != songMap.rend(); ++it) {
        std::cout << "Title: " << it->second.title << " | Score: " << ((it->second.score * 10.0) / 1) / 10.0 << "\n";
        i++;
        if (i == 10)
            return;
    }
}