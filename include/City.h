#pragma once
#ifndef CITY_H
#define CITY_H

#include <string>

class City {
private:
    std::string name;
    double x;
    double y;

public:
    City(const std::string& name, double x, double y);
    std::string getName() const;
    double getX() const;
    double getY() const;
    double distanceTo(const City& other) const;
};

#endif  // CITY_H
