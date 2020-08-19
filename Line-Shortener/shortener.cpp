#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


size_t CharNum = 0;
std::string inputFile = "list.txt";
std::string outputFile = "output.txt";
bool verbose = true;

void log(std::ofstream& infile, std::string& text);
int shortenLeft(std::string& filename, std::string& logfile, size_t number);
int shortenRight(std::string& filename, std::string& logfile, size_t number); //input, output, number of chars to remove

enum choices {shortleft = 1, shortright};

int main()
{
        std::cout << "Line Remover\n";
	std::cout << "Version 1.0\n\n";

	std::cout << "Input file: " << inputFile << "\n";
	std::cout << "Output file: " << outputFile << "\n\n";
	std::cout << "How many character do you want to remove?\n";

	std::cin >> CharNum;
	if (CharNum < 1) {
		std::cout << "Error: Must be atleast 1!\n";
		return EXIT_FAILURE;
	}

	std::cout << "From left or right? (1, 2)\n";
	choices choice;
	int mode;
	std::cin >> mode;
	mode = static_cast<choices>(mode);

	switch (mode) {
		case shortleft:
			shortenLeft(inputFile, outputFile, CharNum);
			break;

		case shortright:
			shortenRight(inputFile, outputFile, CharNum);
			break;
	}

	std::cout << "Removing the first " << CharNum << " characters" "\n\n";
	

	getchar();
	return EXIT_SUCCESS;

}

void log(std::ofstream& outfile, std::string& text) { //pass by reference
	if (outfile.is_open()) {
		outfile << text + "\n";
	}
	else {
		std::cout << "Error: can't open file \n";
	}
}

int shortenLeft(std::string& filename, std::string& logfile, size_t number) {
	std::ifstream infile(filename);
	std::string line;

	if (!infile) {
		std::cout << "Error: can't open " << inputFile << "\n";
		return EXIT_FAILURE;
	}

	std::ofstream outfile(logfile, std::ofstream::app); //append mode
	if (!outfile) {
		std::cout << "Error: can't open " << logfile << "\n";
		return EXIT_FAILURE;
	}

	while (infile >> line) {
		if (line.size() > number) {
			std::string newline = line.substr(number, line.size()); //remove from the right
			if (verbose) std::cout << newline + "\n"; /*shortened*/
			log(outfile, newline);
		}
	}

	outfile.close();
	return EXIT_SUCCESS;
}

int shortenRight(std::string& filename, std::string& logfile, size_t number) {
	std::ifstream infile(filename);
	std::string line;

	if (!infile) {
		std::cout << "Error: can't open " << inputFile << "\n";
		return EXIT_FAILURE;
	}

	std::ofstream outfile(logfile, std::ofstream::app); //append mode
	if (!outfile) {
		std::cout << "Error: can't open " << logfile << "\n";
		return EXIT_FAILURE;
	}

	while (infile >> line) {
		if (line.size() > number) {
			//if (verbose) std::cout << line + "\n"; /*print all lines in file*/
			std::string newline = line.substr(0, line.size() - number); //remove from the right
			if (verbose) std::cout << newline + "\n"; /*shortened*/
			log(outfile, newline);
		}
	}

	outfile.close();
	return EXIT_SUCCESS;
}

