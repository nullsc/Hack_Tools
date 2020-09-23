//menu.cpp
#include "menu.h"

void banner() {

	std::cout <<":::        ::::::::::: ::::    ::: :::::::::: ::::::::::: \n"
				":+:            :+:     :+:+:   :+: :+:            :+:     \n"
				"+:+            +:+     :+:+:+  +:+ +:+            +:+     \n"
				"+#+            +#+     +#+ +:+ +#+ +#++:++#       +#+     \n"
				"+#+            +#+     +#+  +#+#+# +#+            +#+     \n"
				"#+#            #+#     #+#   #+#+# #+#            #+#     	\n"
				"########## ########### ###    #### ##########     ###     \n\n";


	std::cout << "Type in your preferred option \n";
	std::cout << "Then type in how many/what characters you want to remove \n";
	std::cout << "Hit enter! \n";
}

void printMenu() {
	std::cout << "------------------- Menu -------------------\n";
	std::cout << "[1] Shorten from the left [number of chars to remove]\n";
	std::cout << "[2] Shorten from the right [number of chars to remove]\n";
	std::cout << "[3] Delete before [string/char] \n";
	std::cout << "[4] Delete after [string/char] \n";
	std::cout << "[5] Delete all blank lines \n";
	std::cout << "[6] Trimmer [left/right/both]\n";
	std::cout << "[7] Remove duplicate lines\n";
	std::cout << "[8] Line append [left/right/both] \n";
	std::cout << "[9] Remove all non ASCII characters \n";
	std::cout << "[0] Exit \n";
	std::cout << "--------------------------------------------\n";
}
