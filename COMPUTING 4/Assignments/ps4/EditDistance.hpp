#include <iostream>
#include <string>
class ED {
private:
	std::string string1;
	std::string string2;
	int size_string1;
	int size_string2;
	int **opt;
public:
	ED(std::string s1, std::string s2);
	int penalty(char a, char b);
	int min(int a, int b, int c);
	int OptDistance();
	std::string Alignment();
};
