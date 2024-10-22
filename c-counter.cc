#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>

using namespace std;

int main() {
    std::string filename;
    map<string, int> tournament_counts = {
        { "UltraBullet_non_tournaments", 0 },
        { "UltraBullet_tournaments", 0 },
        { "Bullet_non_tournaments", 0 },
        { "Bullet_tournaments", 0 },
        { "Blitz_non_tournaments", 0 },
        { "Blitz_tournaments", 0 },
        { "Rapid_non_tournaments", 0 },
        { "Rapid_tournaments", 0 },
        { "Classical_non_tournaments", 0 },
        { "Classical_tournaments", 0 }
    };

    std::map<int, map<string, int>> tournament_data;

    for (int i = 0; i <= 4000; i += 100) {
        tournament_data[i] = tournament_counts;
    }
    int event_count = 0;
    int number_of_tournaments = 0;
    int number_of_non_tournaments = 0;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::cout << filename << "\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::ofstream outfile("out-c.csv");
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string line;
    int lineCount = 0;

    while (std::getline(file, line)) {
        ++lineCount;

        if (line.length() > 6 && line.substr(1, 5) == "Event") {
            event_count++;
            string event_line = line;
            int white_elo = 0, black_elo = 0;
            int bucket = 0;
            bool is_tournament = line.find("tournament") != string::npos;

            while (getline(file, line)) {
                lineCount++;

                if (line.length() > 9 && line.substr(1, 8) == "WhiteElo") {
                    int start = line.find("WhiteElo") + 9;
                    int end = line.find("]", start);
                    white_elo = std::stoi(line.substr(start + 1, end - start - 1));

                    getline(file, line);
                    ++lineCount;
                    start = line.find("BlackElo") + 9;
                    end = line.find("]", start);
                    black_elo = std::stoi(line.substr(start + 1, end - start - 1));
                    float avg_elo = (white_elo + black_elo) / 2.0;
                    bucket = static_cast<int>(avg_elo) / 100 * 100;
                    break;
                }
            }

            if (tournament_data.find(bucket) != tournament_data.end()) {
                if (is_tournament) {
                    number_of_tournaments++;
                    if (event_line.find("Blitz") != string::npos) {
                        tournament_counts["Blitz_tournaments"]++;
                        tournament_data[bucket]["Blitz_tournaments"]++;
                    }
                    else if (event_line.find(" Bullet") != string::npos) {
                        tournament_counts["Bullet_tournaments"]++;
                        tournament_data[bucket]["Bullet_tournaments"]++;
                    }
                    else if (event_line.find("Rapid") != string::npos) {
                        tournament_counts["Rapid_tournaments"]++;
                        tournament_data[bucket]["Rapid_tournaments"]++;
                    }
                    else if (event_line.find("UltraBullet") != string::npos) {
                        tournament_counts["UltraBullet_tournaments"]++;
                        tournament_data[bucket]["UltraBullet_tournaments"]++;
                    }
                    else if (event_line.find("Classical") != string::npos) {
                        tournament_counts["Classical_tournaments"]++;
                        tournament_data[bucket]["Classical_tournaments"]++;
                    }
                }
                else {
                    number_of_non_tournaments++;
                    if (event_line.find("Blitz") != string::npos) {
                        tournament_counts["Blitz_non_tournaments"]++;
                        tournament_data[bucket]["Blitz_non_tournaments"]++;
                    }
                    else if (event_line.find(" Bullet") != string::npos) {
                        tournament_counts["Bullet_non_tournaments"]++;
                        tournament_data[bucket]["Bullet_non_tournaments"]++;
                    }
                    else if (event_line.find("Rapid") != string::npos) {
                        tournament_counts["Rapid_non_tournaments"]++;
                        tournament_data[bucket]["Rapid_non_tournaments"]++;
                    }
                    else if (event_line.find("UltraBullet") != string::npos) {
                        tournament_counts["UltraBullet_non_tournaments"]++;
                        tournament_data[bucket]["UltraBullet_non_tournaments"]++;
                    }
                    else if (event_line.find("Classical") != string::npos) {
                        tournament_counts["Classical_non_tournaments"]++;
                        tournament_data[bucket]["Classical_non_tournaments"]++;
                    }
                }
            }
            else {
                std::cerr << "Bucket " << bucket << " does not exist in tournament_data." << std::endl;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    file.close();
    outfile.close();
    std::cout << std::left;

    std::cout << std::setw(40) << "Number of lines in the file " << ": " << lineCount << std::endl;
    std::cout << std::setw(40) << "Number of events in the file " << ": " << event_count << std::endl;
    std::cout << std::setw(40) << "Number of tournaments in the file : " << ": " << number_of_tournaments << std::endl;
    std::cout << std::setw(40) << "Number of tournaments non in the file : " << ": " << number_of_non_tournaments << std::endl;


    std::vector<std::string> print_order = {
        "UltraBullet_non_tournaments", "UltraBullet_tournaments",
        "Bullet_non_tournaments", "Bullet_tournaments",
        "Blitz_non_tournaments", "Blitz_tournaments",
        "Rapid_non_tournaments", "Rapid_tournaments",
        "Classical_non_tournaments", "Classical_tournaments"
    };

    std::cout << "\nTournament Counts:\n";
    std::cout << std::left;
    for (const auto& key : print_order) {
        std::cout << std::setw(30) << key << " : " << tournament_counts[key] << "\n";
    }

    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    outfile.open("out-c.csv");
    outfile << "Ratings,UltraBullet_non_tournaments,UltraBullet_tournaments,"
        "Bullet_non_tournaments,Bullet_tournaments,"
        "Blitz_non_tournaments,Blitz_tournaments,"
        "Rapid_non_tournaments,Rapid_tournaments,"
        "Classical_non_tournaments,Classical_tournaments" << std::endl;

    for (const auto& entry : tournament_data) {
        int key = entry.first;
        const auto& counts = entry.second;

        std::ostringstream oss;
        oss << key;

        for (const auto& tournament : print_order) {
            oss << "," << counts.at(tournament);
        }

        outfile << oss.str() << std::endl;
    }

    return 0;
}
