#include "functions.h"
#include "menu.h"


void log(std::ofstream& outfile, std::string& text) { //pass by reference (maybe put verbose print line in here)
	//std::ofstream outfile(outputFile, std::ofstream::app); //append mode
	if (outfile.is_open()) {
		outfile << text + "\n";
	}
	else {
		std::cout << "Error: can't open file \n";
	}
}

std::streamoff getListSize(std::ifstream* inFile) {
	/*Get file size in bytes
	unsigned long max value = 4294967295 
	may change to convert to mb
	https://stackoverflow.com/questions/15172315/c-resolving-istreamtellg-warning
	streamoff = long long
	*/
	unsigned long file_size;
	inFile->seekg(0, std::ios::end); //move pointer to end of file
	file_size = inFile->tellg();
	//std::cout << inFile->tellg() << " bytes \n"; //get file size
	inFile->seekg(0, std::ios::beg); //reset to the beginning for the other functions

	return file_size; // /1024 to get mb
}

bool isAllBlank(std::string& str) {
	//std::string whitespace = " \t\f\v\n\r";
	size_t space = str.find_first_not_of(whitespace);
	if (space != std::string::npos)
		return false;
	else
		return true; //is all blank/whitespace
}

bool isValidChar(const char c) {
	/*Checks to see if a character is a valid ASCII
	https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
	255 for extended ASCII*/
	return (c >= 0 && c < 128) ? true : false;
}

std::string removeNonChars(std::string str) {
	std::string tempstr;
	for (size_t i = 0; i < str.length(); ++i) {
		if (isValidChar(str[i])) { //if it's valid, write it
			tempstr += str[i];
		}
	}
	return tempstr;
}

std::string rtrim(std::string str) { //trim trailing whitespace from the right - works but log always adds a \n
	/*pass and return value*/
	size_t space = str.find_last_not_of(whitespace);
	if (space != std::string::npos)
		str.erase(space + 1);
	else
		str.clear(); //all whitespace

	return str;

}

std::string ltrim(std::string str) { //trim trailing whitespace from the left - works
	size_t space = str.find_first_not_of(whitespace); //find the first non w/space char
	if (space != std::string::npos) {
		str = str.substr(space, str.size());
	}

	return str;
}

std::string trim(std::string str) {
	return ltrim(rtrim(str));
}


//maybe make inline to make it faster

int lineAppend(std::ifstream* inFile, std::ofstream* logFile, std::string& str, size_t mode) {
	/*append a string to each side of the string
	need to add a blank line check*/
	std::string line;
	std::string newline;

	if (mode > BOTH || mode < LEFT) {
		std::cout << "Error: Please enter a valid number\n";
		return EXIT_FAILURE;
	}

	while (getline(*inFile, line) && !isAllBlank(line)) {
		

		switch (mode) {
		case LEFT:
			newline = str + line;
			log(*logFile, newline);
			if (verbose) std::cout << newline + "\n";
			break;

		case RIGHT:
			newline = line + str;
			log(*logFile, newline);
			if (verbose) std::cout << newline + "\n";
			break;

		case BOTH:
			newline = str + line + str;
			log(*logFile, newline);
			if (verbose) std::cout << newline + "\n";
			break;

		default:
			std::cout << "Error: Please enter a number between 1-3 \n";
			return 1;

		}

	}

	return EXIT_SUCCESS;
}

int removeDuplicates(std::ifstream* inFile, std::ofstream* logFile) {
	/*Seems to work with vectors
	Check if it is a big file to see if it should use vectors or a temp.txt file
	add a trim function to make things easier otherwise you get duplicates with whitespace
	Might change this to a map function*/

	std::string line;
	if (getListSize(inFile) < MAX_VECTOR_SIZE) { //check if the file is too big to put into a vector (in bytes)
		std::vector<std::string> lines = {};
		while (getline(*inFile, line)) {
			if (!isAllBlank(line)) { //if it's not blank, write it
				//if (verbose) std::cout << line + " \n";
				//log(*logFile, line); need to include (move to functions)
				line = trim(line); //remove all whitespace
				if (std::find(lines.begin(), lines.end(), line) != lines.end()) { //search the vector for a duplicate
					//continue; //if it's found do nothing
				}
				else {
					lines.push_back(line); //line not in vector array, so add it (not a duplicate)
					std::cout << line + " \n";
					log(*logFile, line);
				}
				

			}

		}
	}
	
	return EXIT_SUCCESS;
}
