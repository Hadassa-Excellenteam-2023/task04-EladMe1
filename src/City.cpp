#include "City.h"


City::City() : name(""), x(0.0), y(0.0) {}

City::City(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

bool City::operator==(const City& other) const {
    return this->getName() == other.getName();
}

const std::string& City::getName() const {
    return name;
}

double City::getX() const {
    return x;
}

double City::getY() const {
    return y;
}

double City::calculateDistance(const City& other, int norm) const {
    if (norm == 0) {
        // Euclidean distance
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
    else if (norm == 1) {
        // Chebyshev distance
        return std::max(std::abs(x - other.x), std::abs(y - other.y));
    }
    else if (norm == 2) {
        // Manhattan distance
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
    return 0.0;
}
