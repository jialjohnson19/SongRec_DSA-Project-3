#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>

struct Song {
    std::string title;
    std::vector<std::string> artists;
    std::string genre;
    int year;
    double streamingCount;
    int duration;
    std::string rating;  // You might use this for explicit content, for example
    double score;

    // Default constructor. Sets all variables to nothing
    Song() {
        this->title = "";
        this->artists = {};
        this->genre = "";
        this->year = 0;
        this->streamingCount = 0.0;
        this->duration = 0;
        this->rating = "";
        this->score = 0.0;
    }

    // Constructor for making Song objects
    Song(std::string title, std::vector<std::string> artists, std::string genre,
        int year, double streamingCount, int duration, std::string rating) {
        this->title = title;
        this->artists = artists;
        this->genre = genre;
        this->year = year;
        this->streamingCount = streamingCount;
        this->duration = duration;
        this->rating = rating;
        this->score = 0.0;
    }

    // Copy constructor for copying Song objects
    Song(const Song& otherSong) {
        this->title = otherSong.title;
        this->artists = otherSong.artists;
        this->genre = otherSong.genre;
        this->year = otherSong.year;
        this->streamingCount = otherSong.streamingCount;
        this->duration = otherSong.duration;
        this->rating = otherSong.rating;
        this->score = otherSong.score;
    }

    // Overriding > operator to compare and sort based on Song score
    bool operator>(const Song& otherSong) const {
        // If scores (doubles) are close enough to equal then use streaming count to choose which is greater
        if (std::abs(this->score - otherSong.score) < 0.01) {
            // If streaming count are also close enough to equal then use titles instead
            if (std::abs(this->streamingCount - otherSong.streamingCount) < 0.01) {
                return this->title > otherSong.title;
            }
            else {
                return this->streamingCount > otherSong.streamingCount;
            }
        }
        // Compare based on scores
        else {
            return this->score > otherSong.score;
        }
    }

    // Same as above but with "<"
    bool operator<(const Song& otherSong) const {
        if (std::abs(this->score - otherSong.score) < 0.01) {
            if (std::abs(this->streamingCount - otherSong.streamingCount) < 0.01) {
                return this->title < otherSong.title;
            }
            else {
                return this->streamingCount < otherSong.streamingCount;
            }
        }
        else {
            return this->score < otherSong.score;
        }
    }

    // Overriding == operator to compare based on Song title
    bool operator==(const Song& otherSong) const {
        // If titles are the same and artists vector are the same then Song objects are equal
        return (this->title == otherSong.title) && (this->artists == otherSong.artists);
    }

    // Function to calculate score based on user preferences
    void calculateScore(std::string preferredGenre, int preferredYear,
        double preferredStreamingCount, int preferredDuration, std::string preferredRating) {
        // Add score based on how well the song matches user preferences
        if (this->genre == preferredGenre) this->score += 2.0;
        if (this->year == preferredYear) this->score += 1.5;
        if (this->streamingCount >= preferredStreamingCount) this->score += 1.0;
        if (this->duration <= preferredDuration) this->score += 1.0;
        if (this->rating == preferredRating) this->score += 1.0;
        // You can add more criteria based on your preferences
    }

    // Prints all song info and variables (except score because algorithm is private)
    void printSongInfo() {
        std::cout << "Title: " << this->title << "\n";
        std::cout << "Artists: ";
        // For loop to pring out individual artist names from vector
        for (int i = 0; i < artists.size(); i++) {
            std::cout << artists.at(i);
            // If it's the last artist being printed, then no comma after
            if (i != artists.size() - 1) 
                std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "Genre: " << this->genre << "\n";
        std::cout << "Year: " << this->year << "\n";
        std::cout << "Streaming Count: " << std::fixed << std::setprecision(0) << this->streamingCount << " streams\n";
        std::cout << "Duration: " << this->duration << " seconds\n";
        std::cout << "Rating: " << this->rating << "\n";
    }
};

#endif