// This file contains the 'main' function. Program execution begins and ends there.
// ToDo: blank line remover, delete characters, file append

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "menu.h"

size_t CharNum = 0; //must be >= 0
std::string inputFile = "list.txt";
std::string outputFile = "output.txt";
bool verbose = true;

void log(std::ofstream& outfile, std::string& text);
int shortenLeft(std::ifstream* inFile, std::ofstream* logFile, size_t number);
int shortenRight(std::ifstream* inFile, std::ofstream* logFile, size_t number);
int deleteAfter(std::ifstream* inFile, std::ofstream* logFile, std::string& characters); //new w/pointers
int deleteBefore(std::ifstream* inFile, std::ofstream* logFile, std::string& characters); //new w/pointers

int trimLineRight(std::ifstream* inFile, std::ofstream* logFile);
int trimLineLeft(std::ifstream* inFile, std::ofstream* logFile);

enum choices {shortleft = 1, shortright, delbefore, delafter};

int main()
{
        std::cout << "Line Remover\n";
	std::cout << "Version 1.2\n\n";

	//banner();
	printMenu();

	std::ifstream* infile(new std::ifstream(inputFile)); //  (open the file pointer)
	std::ofstream* outfile(new std::ofstream(outputFile, std::ofstream::app)); //  (open the file pointer) append


	std::cout << "Input file: " << inputFile << "\n";
	std::cout << "Output file: " << outputFile << "\n\n";


	int mode;
	std::string input;
	std::cin >> mode;
	mode = static_cast<choices>(mode);

	switch (mode) {
		case shortleft:
			std::cout << "Type in how many characters do you wish to remove\n";
			std::cin >> CharNum;
			if (CharNum > 0) shortenLeft(infile, outfile, CharNum);
			break;

		case shortright:
			std::cout << "Type in how many characters do you wish to remove\n";
			std::cin >> CharNum;
			if (CharNum > 0) shortenRight(infile, outfile, CharNum);
			break;

		case delbefore:
			std::cout << "Type in a string\n";
			std::cin >> input;
			if (!input.empty()) deleteBefore(infile, outfile, input);
			break;

		case delafter:
			std::cout << "Type in a string\n";
			std::cin >> input;
			if (!input.empty()) deleteAfter(infile, outfile, input);
			break;

		default:
			return EXIT_SUCCESS;
	}


	char c = getchar(); //removes warning
	delete infile;//deallocate pointers
	delete outfile;
	return EXIT_SUCCESS;

}

void log(std::ofstream& outfile, std::string& text) { //pass by reference
	//std::ofstream outfile(outputFile, std::ofstream::app); //append mode
	if (outfile.is_open()) {
		outfile << text + "\n";
		//outfile.close();
	}
	else {
		std::cout << "Error: can't open file \n";
	}
}

int shortenLeft(std::ifstream* inFile, std::ofstream* logFile, size_t number) {
	std::string line;

	while (getline(*inFile, line)) {
		if (line.size() > number) {
			//if (verbose) std::cout << line + "\n"; /*print all lines in file*/
			std::string newline = line.substr(number, line.size()); //remove from the left
			if (verbose) std::cout << newline + "\n"; /*shortened*/
			log(*logFile, newline);
		}
	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int shortenRight(std::ifstream* inFile, std::ofstream* logFile, size_t number) {
	std::string line;

	while (getline(*inFile, line)) {
		if (line.size() > number) {
			//if (verbose) std::cout << line + "\n"; /*print all lines in file*/
			std::string newline = line.substr(0, line.size() - number); //remove from the right
			if (verbose) std::cout << newline + "\n"; /*shortened*/
			log(*logFile, newline);
		}
	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int trimLineRight(std::ifstream* inFile, std::ofstream* logFile) {
	/*removes all trailing whitespace on the right
	*/
	std::string line;

	while (getline(*inFile, line)) {
		std::string newline = rtrim(line); //trim right side
		if (verbose) std::cout << newline + "\n";
		log(*logFile, newline); //works but log adds \n

	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int trimLineLeft(std::ifstream* inFile, std::ofstream* logFile) {
	/*removes all trailing whitespace on the right
	*/
	std::string line;

	while (getline(*inFile, line)) {
		std::string newline = ltrim(line); //trim left side
		if (verbose) std::cout << newline + "\n";
		log(*logFile, newline);

	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int deleteAfter(std::ifstream* inFile, std::ofstream* logFile, std::string& characters) { //new with pointers
	/*removes anything after the specified character/string
	*/
	std::string line;

	while (getline(*inFile, line)) {
		if (line.find(characters) != std::string::npos) //contains characters
		{
			//std::string newline = line.substr(0, line.find_first_of(characters)); //remove end (char only)
			std::string newline = line.substr(0, line.find(characters) + characters.size()); //remove end (works with string)
			if (verbose) std::cout << newline + " delete after\n";
			log(*logFile, newline);
		}
		else {
			if (verbose) std::cout << line + " doesn't contain" + characters + " \n";
			log(*logFile, line); //write the line anyway
		}
	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int deleteBefore(std::ifstream* inFile, std::ofstream* logFile, std::string& characters) {
	/*removes anything before the specified character/string
	*/
	std::string line;

	while (getline(*inFile, line)) {
		if (line.find(characters) != std::string::npos) //contains characters
		{
			//find gets the first position, line - 1 to get the last position
			std::string newline = line.substr(line.find(characters), line.size() - 1); //remove end (works with string)
			if (verbose) std::cout << newline + " delete before\n";
			log(*logFile, newline);
		}
		else {
			if (verbose) std::cout << line + " doesn't contain" + characters + " \n";
			log(*logFile, line); //write the line anyway
		}
	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}
