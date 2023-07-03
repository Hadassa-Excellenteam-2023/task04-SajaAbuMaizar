#pragma once
#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include "City.h"

class FileIO {
public:
    static bool readCitiesFromFile(const std::string& fileName, std::vector<City>& cities);
};

#endif  // FILEIO_H
