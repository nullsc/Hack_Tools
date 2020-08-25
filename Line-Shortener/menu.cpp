//menu.cpp
#include "menu.h"

void banner() {
	std::cout << "Type in your preferred option \n";
	std::cout << "Then type in how many/what characters you want to remove \n";
	std::cout << "Hit enter! \n";
}

void printMenu() {
	std::cout << "-------------- Menu --------------\n";
	std::cout << "[1] Shorten from the left \n";
	std::cout << "[2] Shorten from the right \n";
	std::cout << "[3] Delete before [string/char] \n";
	std::cout << "[4] Delete after [string/char] \n";
	std::cout << "[0] Exit \n";
	std::cout << "----------------------------------\n";
}
