#include "CitySearch.h"


CitySearch::CitySearch(const std::string& filePath) {
    loadDataFromFile(filePath);
}

// Search cities within a given radius and norm
void CitySearch::searchCities(const std::string& cityName, double radius, int norm) {

// Find the selected city in the map
const City* selectedCity = nullptr;
auto iter = cities.find(cityName);
if (iter != cities.end()) {
    selectedCity = &(iter->second);
}

// If the selected city is not found, return
if (selectedCity == nullptr) {
    return;
}

std::vector<City> matchingCities;
// Filter and transform the cities based on the given criteria
std::transform(cities.begin(), cities.end(), std::back_inserter(matchingCities),
    [selectedCity, radius, norm](const auto& cityPair) {
        const auto& city = cityPair.second;
        return city.getName() != selectedCity->getName() &&
            selectedCity->calculateDistance(city, norm) <= radius ? city : City();
    });
// Remove empty cities from the vector
matchingCities.erase(std::remove_if(matchingCities.begin(), matchingCities.end(),
    [](const City& city) { return city.getName().empty(); }), matchingCities.end());

// Sort the matching cities based on the distance from the selected city
std::sort(matchingCities.begin(), matchingCities.end(),
    [selectedCity, norm](const City& a, const City& b) {
        return selectedCity->calculateDistance(a, norm) <
            selectedCity->calculateDistance(b, norm);
    });

std::cout << matchingCities.size() << " city/cities found in the given radius.\n";

int countNorth = std::count_if(matchingCities.begin(), matchingCities.end(), [&](const City& city) {
    return city.getX() < selectedCity->getX();
    });

std::cout << countNorth << " cities are to the north of the selected city." << std::endl;

// Print the list of cities
std::cout << "City list:\n";
std::for_each(matchingCities.begin(), matchingCities.end(),
    [](const City& city) {
        std::cout << city.getName() << "\n";
    });
}

// Run the city search program
void CitySearch::run() {
    try {
        std::string cityName;
        double radius;
        int norm;

        while (true) {
            std::cout << "Please enter selected city name (with line break after it):\n";
            std::getline(std::cin, cityName);

            if (cityName == "0") {
                break;
            }

            if (!validateCity(cityName)) {
                std::cout << "ERROR: \"" << cityName << "\" is not found in the city list. Please try again.\n";
                continue;
            }

            radius = validateRadiusInput();

            norm = getValidatedNorm();

            searchCities(cityName, radius, norm);
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "Bye\n";

}

// Load city data from a file
void CitySearch::loadDataFromFile(const std::string& filePath) {
    std::ifstream fin(filePath);
    std::string line, name;
    double first, second;

    while (std::getline(fin, line)) {
        if (line.length() > 0) {
            name = line;
            std::getline(fin, line);
            int pos = line.find("-");
            first = std::stod(line.substr(0, pos));
            second = std::stod(line.substr(pos + 1));

            cities[name] = City(name, first, second);
        }
    }
    fin.close();
}

// Validate if a city exists in the city list
bool CitySearch::validateCity(const std::string& city) {
    return std::find_if(cities.begin(), cities.end(), [&city](const std::pair<const std::string, City>& c) {
        return c.first == city;
        }) != cities.end();
}

// Validate user input for the radius
double CitySearch::validateRadiusInput()
{
    std::string radiusInput;
    std::cout << "Please enter the desired radius:\n";
    std::getline(std::cin, radiusInput);
    try {
        double radius = std::stod(radiusInput);
        return radius;
    }
    catch (const std::invalid_argument&) {
        throw std::runtime_error("Invalid input. Radius must be a double.");
        return validateRadiusInput();
    }
}

// Validate user input for the norm
int CitySearch::validateNormInput(const std::string& normInput)
{
    int norm = std::stoi(normInput);
    if (norm < 0 || norm > 2) {
        throw std::runtime_error("Invalid input. Norm must be 0, 1, or 2.");
    }
    return norm;
}

// Get and validate user input for the norm
int CitySearch::getValidatedNorm()
{
    std::string normInput;
    std::cout << "Please enter the desired norm (0 - L2, 1 - Linf, 2 - L1):\n";
    std::getline(std::cin, normInput);

    try {
        return validateNormInput(normInput);
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << " Please try again.\n";
        return getValidatedNorm();  
    }
}




