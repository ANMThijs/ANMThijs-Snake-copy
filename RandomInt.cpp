#include "RandomInt.h"

int RandomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);

	int i = dist(gen);
	return i;
}