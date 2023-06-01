#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include "City.h"

class CitySearch {
public:
    CitySearch(const std::string& filePath);
    void searchCities(const std::string& cityName, double radius, int norm);
    void run();

private:
    std::map<std::string, City> cities;

    void loadDataFromFile(const std::string& filePath);
    int countCitiesNorthOfSelectedCity(const City& selectedCity, double radius, int norm) const;
    bool validateCity(const std::string& city);
    double validateRadiusInput();
    int validateNormInput(const std::string& normInput);
    int getValidatedNorm();
};


