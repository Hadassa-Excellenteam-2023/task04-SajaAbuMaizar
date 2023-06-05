#pragma once
#ifndef CITYDATAMANAGER_H
#define CITYDATAMANAGER_H

#include <vector>
#include "City.h"

class CityDataManager {
private:
    std::vector<City> cities;

public:
    bool loadCitiesFromFile(const std::string& fileName);
    City* findCityByName(const std::string& cityName);
    std::vector<City> getCities() const;
};

#endif  // CITYDATAMANAGER_H
