#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <chrono>
#include <fstream>

using namespace std;

void tournament_counter() {
    ofstream file("out-cp.txt");

    map<string, int> counts =
     {
        {"Blitz", 0}, {"Bullet", 0}, {"Rapid", 0}, {"UltraBullet", 0}, {"Classical", 0}
    };
    int tournament_count = 0;
    auto start = chrono::high_resolution_clock::now();
    regex pattern1(R"(^\[Event\s+".*tournament.*"\]$)");
    regex pattern2(R"((\w+)\s+tournament)");

    string line;
    while (getline(cin, line)) {
        if (regex_match(line, pattern1)) {
            tournament_count++;
            cout << "Total tournaments: " << tournament_count << "\n";

            smatch match;
            if (regex_search(line, match, pattern2)) {
                string type = match[1].str();
                counts[type]++;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    if(file.is_open())
    {
        file << "Time taken is: " << elapsed.count() << " seconds\n";
        file << "Tournament counts:\n";
        for (const auto& pair : counts) {
            file << pair.first << ": " << pair.second << "\n";
        }
        file << "Total tournaments: " << tournament_count << "\n";
        file.close();
    }
    
}

int main() {
    tournament_counter();
    return 0;
}
