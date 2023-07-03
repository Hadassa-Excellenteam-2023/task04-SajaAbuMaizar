#include "FileIO.h"
#include <fstream>
#include <sstream>

bool FileIO::readCitiesFromFile(const std::string& fileName, std::vector<City>& cities) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::string name = line;

        std::getline(inputFile, line); // Read the line with coordinates
        std::stringstream ss(line);
        double x, y;
        ss >> x >> y;

        cities.emplace_back(name, x, y);
    }

    inputFile.close();
    return true;
}
