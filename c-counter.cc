#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <map>


using namespace std;
int main() {
    std::string filename;
    map<string, int> tournament_counts = { { "Blitz_tournaments", 0 }, { "Bullet_tournaments", 0 }, { "Rapid_tournaments", 0 },
        { "UltraBullet_tournaments", 0 }, { "Classical_tournaments", 0 },{ "Blitz_non_tournaments", 0 }, { "Bullet_non_tournaments", 0 }, { "Rapid_non_tournaments", 0 },
        { "UltraBullet_non_tournaments", 0 }, { "Classical_non_tournaments", 0 } };
    int number_of_tournaments = 0;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::cout << filename << "\n";

    std::ifstream file(filename);
    std::ofstream outfile("out-c.txt");
    file.is_open();

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        ++lineCount;

        if (line.length() > 6 && line.substr(1, 5) == "Event") {
            if (line.find("tournament") != string::npos)
            {
                number_of_tournaments++;
                if (line.find("Blitz") != string::npos) {
                    tournament_counts["Blitz_tournaments"]++;
                    continue;
                }
                else if (line.find(" Bullet") != string::npos) {
                    tournament_counts["Bullet_tournaments"]++;
                    continue;
                }
                else if (line.find("Rapid") != string::npos) {
                    tournament_counts["Rapid_tournaments"]++;
                    continue;
                }
                else if (line.find("UltraBullet") != string::npos) {
                    tournament_counts["UltraBullet_tournaments"]++;
                    continue;
                }
                else if (line.find("Classical") != string::npos) {
                    tournament_counts["Classical_tournaments"]++;
                    continue;
                }
            }
            else {
                if (line.find("Blitz") != string::npos) {
                    tournament_counts["Blitz_non_tournaments"]++;
                    continue;
                }
                else if (line.find(" Bullet") != string::npos) {
                    tournament_counts["Bullet_non_tournaments"]++;
                    continue;
                }
                else if (line.find("Rapid") != string::npos) {
                    tournament_counts["Rapid_non_tournaments"]++;
                    continue;
                }
                else if (line.find("UltraBullet") != string::npos) {
                    tournament_counts["UltraBullet_non_tournaments"]++;
                    continue;
                }
                else if (line.find("Classical") != string::npos) {
                    tournament_counts["Classical_non_tournaments"]++;
                    continue;
                }

            }
        }
    }



    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    file.close();
    outfile.is_open();
    outfile << lineCount;

    std::cout << "Number of lines in the file: " << lineCount << std::endl;
    std::cout << "Number of tournaments in the file: " << number_of_tournaments << std::endl;
    for (auto& key_value : tournament_counts)
    {
        std::cout << key_value.first << " : " << key_value.second << "\n";
    }



    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;


    return 0;
}
