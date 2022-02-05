#include <iostream>
class LFSR
{
	public:
		LFSR(std::string seed, int t);
		int step();
		int generate(int k);
		friend std::ostream& operator<<(std::ostream& out, LFSR& lsfr);
	private:
		std::string Seed;
		int tap;
};
