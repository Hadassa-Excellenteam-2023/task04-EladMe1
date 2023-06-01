#include "CitySearch.h"


int main() {
	try
	{
		CitySearch c("data.txt");

		c.run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << "\n";
	}

}
