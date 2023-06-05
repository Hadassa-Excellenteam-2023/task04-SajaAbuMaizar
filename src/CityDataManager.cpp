#include "CityDataManager.h"
#include "FileIO.h"

bool CityDataManager::loadCitiesFromFile(const std::string& fileName) {
    return FileIO::readCitiesFromFile(fileName, cities);
}

City* CityDataManager::findCityByName(const std::string& cityName) {
    for (auto& city : cities) {
        if (city.getName() == cityName) {
            return &city;
        }
    }
    return nullptr;
}

std::vector<City> CityDataManager::getCities() const {
    return cities;
}
