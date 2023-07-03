#include "City.h"
#include <cmath>

City::City(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

std::string City::getName() const {
    return name;
}

double City::getX() const {
    return x;
}

double City::getY() const {
    return y;
}

double City::distanceTo(const City& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}
