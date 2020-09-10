//menu.cpp
#include "menu.h"

void banner() {
	std::cout << "Type in your preferred option \n";
	std::cout << "Then type in how many/what characters you want to remove \n";
	std::cout << "Hit enter! \n";
}

void printMenu() {
	std::cout << "-------------- Menu --------------\n";
	std::cout << "[1] Shorten from the left [number of chars to remove]\n";
	std::cout << "[2] Shorten from the right [number of chars to remove]\n";
	std::cout << "[3] Delete before [string/char] \n";
	std::cout << "[4] Delete after [string/char] \n";
	std::cout << "[5] Delete all blank lines \n";
	std::cout << "[6] Trimmer [left/right/both]\n";
	std::cout << "[7] Remove duplicate lines\n";
	std::cout << "[8] Line append [left/right/both] \n";
	std::cout << "[0] Exit \n";
	std::cout << "----------------------------------\n";
}

std::string& rtrim(std::string& str) { //trim trailing whitespace from the right - works but log always adds a \n
	size_t space = str.find_last_not_of(whitespace);
	if (space != std::string::npos)
		str.erase(space + 1);
	else
		str.clear(); //all whitespace

	return str;

}

std::string& ltrim(std::string& str) { //trim trailing whitespace from the left - works
	size_t space = str.find_first_not_of(whitespace); //find the first non w/space char
	if (space != std::string::npos) {
		str = str.substr(space, str.size());
	}
	
	return str;
}

std::string& trim(std::string& str) {
	return ltrim(rtrim(str));
}


//maybe make inline to make it faster
