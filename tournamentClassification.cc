#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <chrono>
#include <fstream>

using namespace std;

void tournament_counter()
{
    ofstream file("out-cp.txt");

    map<string, int> counts =
        {
            {"Blitz", 0}, {"Bullet", 0}, {"Rapid", 0}, {"UltraBullet", 0}, {"Classical", 0}};
    int tournament_count = 0;
    auto start = chrono::high_resolution_clock::now();
    string line;
    while (getline(cin, line))
    {

        if (line.length() > 6 && line.substr(1, 5) == "Event")
        {
            if (line.find("tournament") != string::npos)
            {
                tournament_count++;
                if (line.find("Blitz") != string::npos)
                {
                    counts["Blitz"]++;
                    continue;
                }
                else if (line.find("Bullet") != string::npos)
                {
                    counts["Bullet"]++;
                    continue;
                }
                else if (line.find("Rapid") != string::npos)
                {
                    counts["Rapid"]++;
                    continue;
                }
                else if (line.find("UltraBullet") != string::npos)
                {
                    counts["UltraBullet"]++;
                    continue;
                }
                else if (line.find("Classical") != string::npos)
                {
                    counts["Classical"]++;
                    continue;
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    if (file.is_open())
    {
        file << "Time taken is: " << elapsed.count() << " seconds\n";
        file << "Tournament counts:\n";
        for (const auto &pair : counts)
        {
            file << pair.first << ": " << pair.second << "\n";
        }
        file << "Total tournaments: " << tournament_count << "\n";
        file.close();
    }
}

int main()
{
    tournament_counter();
    return 0;
}
