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

std::string &rtrim(std::string& str) { //trim trailing whitespace from the right - log always adds a \n
	std::string whitespace = " \t\f\v\n\r";
	size_t space = str.find_last_not_of(whitespace);
	if (space != std::string::npos)
		str.erase(space + 1);
	else
		str.clear();

	return str;

}

std::string& ltrim(std::string& str) { //trim trailing whitespace from the left
	std::string whitespace = " \t\f\v\n\r"; //move to .h
	size_t space = str.find_first_not_of(whitespace); //find the first non w/space char
	if (space != std::string::npos) {
		str = str.substr(space, str.size());
	}
	
	return str;
}

std::string& trim(std::string& str) {
	return ltrim(rtrim(str));
}
