#pragma once

#include <cmath>
#include <string>

class City {
public:
    City();
    City(const std::string& name, double x, double y);
    bool operator==(const City& other) const;
    const std::string& getName() const;
    double getX() const;
    double getY() const;
    double calculateDistance(const City& other, int norm) const;

private:
    std::string name;
    double x;
    double y;
};


