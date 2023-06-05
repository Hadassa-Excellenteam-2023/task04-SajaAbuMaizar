#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>

struct City {
    std::string name;
    double x;
    double y;
};

double distance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

int main() {
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<City> cities;
    std::string line;
    while (std::getline(inputFile, line)) {
        City city;
        city.name = line;

        std::getline(inputFile, line); // Read the line with coordinates
        std::stringstream ss(line);
        ss >> city.x >> city.y;

        cities.push_back(city);
    }

    inputFile.close();


    while (true) {
        std::string cityName;
        double radius;
        int norm;
        double x;
        double y;
        std::vector<std::string> naighboutCities;

        std::cout << "Please enter the selected city name (with a line break after it):" << std::endl;
        std::getline(std::cin, cityName);

        if (cityName == "0") {
            break;
        }

        bool cityFound = false; // Flag to track if a city with matching name is found

        for (const auto& city : cities) {
            if (city.name == cityName) {
                cityFound = true;
                x = city.x;
                y = city.y;
                break; // Found a matching city, no need to continue the loop
            }
        }

        if (!cityFound) {
            std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
            continue; // Go back to the beginning of the loop and ask for the city name again
        }

        std::cout << "Please enter the radius: ";
        std::cin >> radius;

        std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):";
        std::cin >> norm;

        std::cout << "Cities within the specified radius:" << std::endl;
        int count = 0;
        int northCount = 0;
        for (const auto& city : cities) {
            if (city.name != cityName) {
                double dist;
                switch (norm) {
                case 0:
                    dist = distance(city.x, city.y, x, y);
                    break;
                case 1:
                    dist = std::max(std::abs(city.x - x), std::abs(city.y - y));
                    break;
                case 2:
                    dist = std::abs(city.x - x) + std::abs(city.y - y);
                    break;
                default:
                    std::cout << "Invalid norm." << std::endl;
                    return 1;
                }
                if (dist <= radius) {
                    naighboutCities.push_back(city.name);
                    count++;
                }
                if (city.y > y)
                {
                    northCount++;
                }
            }
        }

        std::cout << count << " city/cities found in the given radius." << std::endl;
        std::cout << northCount << " cities are to the north of the selected city." << std::endl;
        std::cout << "City List:" << std::endl;
        for (const auto& city : naighboutCities) {
            std::cout << city << std::endl;
        }


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}