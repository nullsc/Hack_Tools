// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "menu.h"
#include "functions.h"


size_t CharNum = 0;
std::string inputFile = "list.txt"; //
std::string outputFile = "output.txt";


int shortenLeft(std::ifstream* inFile, std::ofstream* logFile, size_t number);
int shortenRight(std::ifstream* inFile, std::ofstream* logFile, size_t number);
int deleteAfter(std::ifstream* inFile, std::ofstream* logFile, std::string& characters); //new w/pointers 
int deleteBefore(std::ifstream* inFile, std::ofstream* logFile, std::string& characters); //new w/pointers

int deleteEmptyLines(std::ifstream* inFile, std::ofstream* logFile); //remove whitespace lines
int trimLineRight(std::ifstream* inFile, std::ofstream* logFile);
int trimLineLeft(std::ifstream* inFile, std::ofstream* logFile);
int trimLineBoth(std::ifstream* inFile, std::ofstream* logFile);

int trimmer(std::ifstream** inFile, std::ofstream** logFile);
int removeNonASCIILines(std::ifstream* inFile, std::ofstream* logFile);


enum choices {shortleft = 1, shortright, delbefore, delafter, removeblanks, linetrimmer, removedupes, 
			lineappend, removenonascii};

int main(int argc, char* argv[])
{
	banner();
	std::cout << "\nLINET (Line Tool) ";
	std::cout << version << "\n\n";
	printMenu();

	if (argc != 3){
		std::cout << "Error: Usage " << argv[0] << " input_file output_file \n";
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	inputFile = argv[1]; //comment out for debug
	outputFile = argv[2];

	std::ifstream* infile(new std::ifstream(inputFile)); // open the file pointer
	std::ofstream* outfile(new std::ofstream(outputFile, std::ofstream::app)); //test  (open the file pointer) append
	if (!*infile) {
		std::cout << "Error: Can't open " << inputFile << "\n";
		return EXIT_FAILURE;
	}

	std::cout << "Input file: " << inputFile << "\n";
	std::cout << "Output file: " << outputFile << "\n\n"; 


	int mode; //maybe put in a function in menu.cpp to loop
	std::string input;
	std::cin >> mode;
	mode = static_cast<choices>(mode);

	switch (mode) {
		case shortleft:
			std::cout << "Type in how many characters you wish to remove\n";
			std::cin >> CharNum; //maybe just use input
			if (CharNum > 0) shortenLeft(infile, outfile, CharNum);
			break;

		case shortright:
			std::cout << "Type in how many characters you wish to remove\n";
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
			if (!input.empty()) deleteAfter(infile, outfile, input); //not sure if isempty needed
			break;

		case removeblanks:
			std::cout << "Deleting all blank lines\n";
			deleteEmptyLines(infile, outfile);
			break;

		case linetrimmer:
			std::cout << "Line trimmer (whitespace remover)\n";
			trimmer(&infile, &outfile);
			break;

		case removedupes:
			std::cout << "Removing duplicate lines\n";
			removeDuplicates(infile, outfile);
			break;

		case lineappend:
			std::cout << "Type in a string\n";
			std::cin >> input;
			std::cout << "Append [left 1 / Right 2 / Both 3]\n";
			std::cin >> CharNum;
			lineAppend(infile, outfile, input, CharNum);
			break;

		case removenonascii:
			std::cout << "Removing all non ASCII characters \n";
			removeNonASCIILines(infile, outfile);
			break;

		default:
			return EXIT_SUCCESS;
	}

	
	infile->close(); //close file pointers here, can remove from each function now
	outfile->close();

	std::cout << "Complete! Press any key to quit \n"
				  "Thank you for using LINET	\n";
	//std::cin >> input;
	std::cin.ignore();
	delete infile; //deallocate pointers
	delete outfile;

	return EXIT_SUCCESS;

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

	return EXIT_SUCCESS;
}

int trimmer(std::ifstream** inFile, std::ofstream** logFile/*,int mode*/) { //works - include types
	//trimLineRight(*inFile, *logFile);
	std::cout << "Trim [Left 1 / Right 2 / Both 3]\n";
	size_t input;
	std::cin >> input;
	
	switch (input) {
		case LEFT:
			trimLineLeft(*inFile, *logFile);
			break;

		case RIGHT:
			trimLineRight(*inFile, *logFile);
			break;

		case BOTH:
			trimLineBoth(*inFile, *logFile);
			break;

		default:
			std::cout << "Error: Please enter a number\n";
			return 1;

	}

	return EXIT_SUCCESS;
}

int trimLineBoth(std::ifstream* inFile, std::ofstream* logFile) {
	/*removes all trailing whitespace on the left & right
	maybe add a blank line check for trim both
	*/
	std::string line;

	while (getline(*inFile, line)) {
		std::string newline = trim(line); //trim both sides
		if (verbose) std::cout << newline + "\n";
		log(*logFile, newline); //works but log adds \n

	}

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

	return EXIT_SUCCESS;
}

int deleteEmptyLines(std::ifstream* inFile, std::ofstream* logFile) {
	/*deletes all empty lines
	*/
	std::string line;

	while (getline(*inFile, line)) {
		if (!isAllBlank(line)) { //if it's not blank, write it
			if (verbose) std::cout << line + " \n";
			log(*logFile, line);
		}
    
	}

	return EXIT_SUCCESS;
}

int removeNonASCIILines(std::ifstream* inFile, std::ofstream* logFile) {
	std::string line;

	while (getline(*inFile, line)) {
		//if (!isAllBlank(line)) { //if it's not blank, write it
		line = removeNonChars(line);
		if (verbose) std::cout << line + " \n";
		log(*logFile, line);
		//}

	}
	return EXIT_SUCCESS;
}
