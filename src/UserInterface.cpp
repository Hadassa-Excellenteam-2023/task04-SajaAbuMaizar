#include "UserInterface.h"
#include <iostream>
#include <limits>
#include "CityDataManager.h"

// Function to run the user interface
void UserInterface::run() {
    CityDataManager cityDataManager;

    std::string fileName;

    // Load cities from file
    if (!cityDataManager.loadCitiesFromFile("data.txt")) {
        std::cout << "Failed to open input file." << std::endl;
        return;
    }

    // Main loop of the user interface
    while (true) {
        std::string cityName;
        double radius;
        int norm;
        std::vector<std::string> neighbourCities;

        std::cout << "Please enter selected city name (with line break after it): ";
        std::getline(std::cin, cityName);

        if (cityName == "0") {
            break;
        }

        // Find the selected city in the city data
        City* selectedCity = cityDataManager.findCityByName(cityName);
        if (selectedCity == nullptr) {
            std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
            continue;
        }

        std::cout << "Please enter the radius: ";
        // Read and validate the radius input
        if (!(std::cin >> radius)) {
            std::cout << "ERROR: Invalid input. Radius must be a number." << std::endl;
            return;
        }

        // Ensure the radius is a positive value
        while (radius <= 0) {
            std::cout << "ERROR: Invalid radius. Please enter a positive value." << std::endl;
            if (!(std::cin >> radius)) {
                std::cout << "ERROR: Invalid input. Radius must be a number." << std::endl;
                return;
            }
        }

        std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):";
        // Read and validate the norm input
        if (!(std::cin >> norm)) {
            std::cout << "ERROR: Invalid input. Norm must be a number." << std::endl;
            return;
        }

        // Ensure the norm value is between 0 and 2
        while (norm < 0 || norm > 2) {
            std::cout << "ERROR: Invalid norm. Please enter a value between 0 and 2." << std::endl;
            if (!(std::cin >> norm)) {
                std::cout << "ERROR: Invalid input. Norm must be a number." << std::endl;
                return;
            }
        }

        std::cout << "Cities within the specified radius:" << std::endl;
        int count = 0;
        int northCount = 0;
        // Iterate over all cities and calculate the distance and other statistics
        for (const auto& city : cityDataManager.getCities()) {
            if (city.getName() != cityName) {
                double dist;
                switch (norm) {
                case 0:
                    // Calculate the distance using L2 norm (Euclidean distance)
                    dist = selectedCity->distanceTo(city);
                    break;
                case 1:
                    // Calculate the distance using Linf norm (Chebyshev distance)
                    dist = std::max(std::abs(selectedCity->getX() - city.getX()), std::abs(selectedCity->getY() - city.getY()));
                    break;
                case 2:
                    // Calculate the distance using L1 norm (Manhattan distance)
                    dist = std::abs(selectedCity->getX() - city.getX()) + std::abs(selectedCity->getY() - city.getY());
                    break;
                default:
                    std::cout << "Invalid norm." << std::endl;
                    return;
                }
                // Check if the distance is within the specified radius
                if (dist <= radius / 2) {
                    neighbourCities.push_back(city.getName());
                    count++;
                }
                // Count cities that are to the north of the selected city
                if (city.getY() > selectedCity->getY()) {
                    northCount++;
                }
            }
        }

        std::cout << count << " city/cities found in the given radius." << std::endl;
        std::cout << northCount << " cities are to the north of the selected city." << std::endl;
        std::cout << "City List:" << std::endl;
        // Print the list of neighboring cities
        for (const auto& city : neighbourCities) {
            std::cout << city << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}