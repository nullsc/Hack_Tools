#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


size_t CharNum = 6; //must be > 0
std::string inputFile = "list.txt";
std::string outputFile = "output.txt";
bool verbose = false; //debug

void log(std::ofstream& infile, std::string& text);

int main()
{
    std::cout << "Line Remover\n";
	std::cout << "Version 1.0\n\n";

	std::cout << "Input file: " << inputFile << "\n";
	std::cout << "Output file: " << outputFile << "\n\n";
	std::cout << "How many characters do you want to remove?\n";

	std::cin >> CharNum;
	if (CharNum < 1) {
		std::cout << "Error: Must be atleast 1!\n";
		return EXIT_FAILURE;
	}

	std::cout << "Line Removing the first " << CharNum << " characters" "\n\n";

	std::ifstream infile(inputFile);
	std::string line;

	if (!infile) {
		std::cout << "Error: can't open " << inputFile << "\n";
		return EXIT_FAILURE;
	}

	std::ofstream outfile(outputFile, std::ofstream::app); //append mode
	if (!outfile) {
		std::cout << "Error: can't open " << outputFile << "\n";
		return EXIT_FAILURE;
	}

	while (infile >> line) {
		//std::cout << line + "\n"; /*print all lines in file*/
		if (line.size() > CharNum) {
			//if (verbose) std::cout << line + "\n"; /*print all lines in file*/
			std::string newline = line.substr(CharNum, line.size());
			if (verbose) std::cout << newline + "\n"; /*shortened*/
			log(outfile, newline);
		}
	}

	outfile.close();


}

void log(std::ofstream& outfile, std::string& text) { //pass by reference
	if (outfile.is_open()) {
		outfile << text + "\n";
		//outfile.close();
	}
	else {
		std::cout << "Error: can't open file \n";
	}
}

