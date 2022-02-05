#include <SFML/System.hpp>
#include "EditDistance.hpp"
int main()
{
	sf::Clock clock;
	sf::Time time;

	std::string string1, string2;
	std::cin >> string1 >> string2;

	ED edit_distance(string1,string2);
	int distance = edit_distance.OptDistance();
	std::cout << "Edit distance = " << distance << "\n";

	std::string result = edit_distance.Alignment();
	std::cout << result;

	time = clock.getElapsedTime();
	std::cout << "Execution time is " << time.asSeconds() << " seconds \n";
}
