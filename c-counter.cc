#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main () {
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::cout << filename << "\n";

    std::ifstream file (filename);
    std::ofstream outfile ("out-c.txt");
    file.is_open ();

    auto start = std::chrono::high_resolution_clock::now ();

    std::string line;
    int lineCount = 0;
    while (std::getline (file, line)) {
        if (line.length () > 6 && line.substr (1, 5) == "Event") {
            if (line.find ("tournament") != string::npos)
                ++lineCount;
        }
    }

    auto end = std::chrono::high_resolution_clock::now ();
    std::chrono::duration<double> elapsed = end - start;

    file.close ();
    outfile.is_open ();
    outfile << lineCount;

    std::cout << "Number of lines in the file: " << lineCount << std::endl;
    std::cout << "Time taken: " << elapsed.count () << " seconds" << std::endl;

    return 0;
}
