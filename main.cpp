#include <iostream>
#include <fstream>  // Add this line
#include <sstream>  // Add this line
#include <chrono> // For measuring time in ms. SOURCE: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/

#include <algorithm> // These two added to run on other compiler

#include "song.h"
#include "map.h"
#include "set.h"
using namespace std;

int main() {
    // Open the CSV file and check if file is open
    std::ifstream file("incremental_titles_songs_dataset.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening music data file.\n";
        return 1;
    }

    // Create user input variables for preferences as well as instances of SongRecommendationMap and SongRecommendationSet
    std::string preferredGenre;
    int preferredYear;
    double preferredStreamingCount;
    int preferredDuration;
    std::string preferredRating;
    SongRecommendationMap recommendationMap;
    SongRecommendationSet recommendationSet;
    double mapInsertTime = 0.0;
    double setInsertTime = 0.0;
    double mapSortTime = 0.0;
    double setSortTime = 0.0;

    // Main menu title
    std::cout
        << "----------------------------------------------\n"
        << "                SONG GENERATOR                \n"
        << "----------------------------------------------\n"
        << "\n";

    // Get user preferences from input
    std::cout << "Enter your preferences below followed by ENTER\n";
    std::cout << "Preferred Genre: ";
    std::cin >> preferredGenre;
    std::cout << "Preferred Year: ";
    std::cin >> preferredYear;
    std::cout << "Preferred Minimum Streaming Count: ";
    std::cin >> preferredStreamingCount;
    std::cout << "Preferred Maximum Duration (in seconds): ";
    std::cin >> preferredDuration;
    std::cout << "Preferred Rating (explicit or clean): ";
    std::cin >> preferredRating;

    // Skip the first line: title, artist, genre, year, streaming_count, duration,rating
    std::string line;
    std::getline(file, line);

    // Read each line of the CSV file
    while (std::getline(file, line)) {
        // Create a string stream to parse each line
        std::stringstream ss(line);

        // Declare variables to store each field
        std::string title, artists, genre, rating;
        int year, duration;
        double streamingCount;

        // Parse the CSV fields
        if (std::getline(ss, title, ',') &&
            std::getline(ss, artists, ',') &&
            std::getline(ss, genre, ',') &&
            ss >> year &&
            ss.ignore() && // Ignore the comma
            ss >> streamingCount &&
            ss.ignore() && // Ignore the comma
            ss >> duration &&
            ss.ignore() && // Ignore the comma
            std::getline(ss, rating))
        {
            // Split the artists string into a vector
            std::vector<std::string> artistList;
            std::stringstream artistsStream(artists);
            std::string artist;

            while (std::getline(artistsStream, artist, '+')) {
                artistList.push_back(artist);
            }

            // Create song object and calculate score
            Song song(title, artistList, genre, year, streamingCount, duration, rating);
            song.calculateScore(preferredGenre, preferredYear, preferredStreamingCount, preferredDuration, preferredRating);

            // Insert the song into the map and set
            auto start = chrono::high_resolution_clock::now(); // Source for code to measure execution time: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
            //
            recommendationMap.insert(song); // Map insert function
            //
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
            mapInsertTime += duration.count();

            start = chrono::high_resolution_clock::now();
            //
            recommendationSet.insert(song); // Set insert function
            //
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds> (stop - start);
            setInsertTime += duration.count();
        }
        else {
            std::cerr << "Error parsing line: " << line << "\n";
        }
    }

    // Close the file
    file.close();

    // Now you have all your songs inserted into the map and set!

    // Get user priority for preference
    int userPriority = 0;
    std::cout << "\n"
        << "Which of these preferences would be your top priority?\n"
        << "1. Genre\n"
        << "2. Year\n"
        << "3. Streaming Count\n"
        << "4. Duration\n"
        << "5. Rating\n"
        << "6. Doesn't matter\n"
        << "Answer (1-6): ";
    std::cin >> userPriority;

    // Filter out unwanted preferences
    // Also sorting map and set (vector sort for map, auto sort for set)
    if (userPriority == 1) {
        // Filter and get time passed in ms for map
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.filterByGenre(preferredGenre); // Map filter function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        // Add duration to total map time taken
        mapSortTime += duration.count();

        // Filter and get time passed in ms for set
        start = chrono::high_resolution_clock::now();
        //
        recommendationSet.filterByGenre(preferredGenre); // Set filter function
        //
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        // Add duration to total set time taken
        setSortTime += duration.count();
    }
    else if (userPriority == 2) {
        // Filter and get time passed in ms for map
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.filterByYear(preferredYear); // Map filter function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        mapSortTime += duration.count();

        // Filter and get time passed in ms for set
        start = chrono::high_resolution_clock::now();
        //
        recommendationSet.filterByYear(preferredYear); // Set filter function
        //
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        setSortTime += duration.count();

    }
    else if (userPriority == 3) {
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.filterByStreamingCount(preferredStreamingCount); // Map filter function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        mapSortTime += duration.count();

        start = chrono::high_resolution_clock::now();
        //
        recommendationSet.filterByStreamingCount(preferredStreamingCount); // Set filter function
        //
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        setSortTime += duration.count();
    }
    else if (userPriority == 4) {
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.filterByDuration(preferredDuration); // Map filter function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        mapSortTime += duration.count();

        start = chrono::high_resolution_clock::now();
        //
        recommendationSet.filterByDuration(preferredDuration); // Set filter function
        //
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        setSortTime += duration.count();
    }
    else if (userPriority == 5) {
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.filterByRating(preferredRating); // Map filter function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        mapSortTime += duration.count();

        start = chrono::high_resolution_clock::now();
        //
        recommendationSet.filterByRating(preferredRating); // Set filter function
        //
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        setSortTime += duration.count();
    }
    else {
        auto start = chrono::high_resolution_clock::now();
        //
        recommendationMap.sortSongMap(); // Map sort function
        //
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds> (stop - start);
        mapSortTime += duration.count();
    }

    // If map or set are empty, then no songs match user preferences
    if (recommendationMap.getMapSize() == 0 || recommendationSet.getSetSize() == 0) {
        std::cout << "\nNo songs match your preferences :(\n";
    }
    else {
        // If map's top song is the same as set's top song, then sorting was successful
        if (recommendationMap.getHighestScore() == recommendationSet.getHighestScore()) {
            Song userTopSong = recommendationSet.getHighestScore();

            // Output the top recommended song
            std::cout << "\nTop Recommended Song:\n";
            userTopSong.printSongInfo();
        }
        else {
            std::cout << "\nError: map and set produce different sorting orders\n";
        }
    }

    // Print results for execution time per data structure;
    std::cout << std::fixed << std::setprecision(0);
    std::cout 
        << "\n"
        << "The std::map data structure took a total of " << mapInsertTime / 1000.0 << "ms to insert song data and " << mapSortTime / 1000.0 << "ms to sort.\n"
        << "That's a total of " << (mapInsertTime + mapSortTime) / 1000.0 << "ms!\n";

    std::cout
        << "\n"
        << "The std::set data structure took a total of " << setInsertTime / 1000.0 << "ms to insert song data and " << setSortTime / 1000.0 << "ms to sort.\n"
        << "That's a total of " << (setInsertTime + setSortTime) / 1000.0 << "ms!\n";

    std::cout
        << "\n"
        << "Press ENTER to exit :)\n";
    cin.ignore();
    cin.get();

    return 0;
}