#include "functions.h"
#include "menu.h"


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

unsigned long getListSize(std::ifstream* inFile) {
	/*Get file size in bytes
	unsigned long max value = 4294967295 
	may change to convert to mb
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

std::string& rtrim(std::string& str) { //trim trailing whitespace from the right - works but log always adds a \n
	//std::string whitespace = " \t\f\v\n\r";
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

int lineAppend(std::ifstream* inFile, std::ofstream* logFile, std::string& str, size_t mode) {
	/*append a string to each side of the string
	need to add a blank line check*/
	std::string line;
	std::string newline;


	while (getline(*inFile, line) && !isAllBlank(line)) {
		//log(*logFile, newline);
		

		switch (mode) {
		case LEFT:
			newline = str + line;
			log(*logFile, newline);
			break;

		case RIGHT:
			newline = line + str;
			log(*logFile, newline);
			break;

		case BOTH:
			newline = str + line + str;
			log(*logFile, newline);
			break;

		default:
			std::cout << "Error: Please enter a number between 1-3 \n";
			return 1;

		}

	}

	inFile->close();
	logFile->close();
	return EXIT_SUCCESS;
}

int removeDuplicates(std::ifstream* inFile, std::ofstream* logFile) {
	/*Seems to work with vectors
	Check if it is a big file to see if it should use vectors or a temp.txt file
	add a trim function to make things easier otherwise you get duplicates with whitespace
	Might change this to a map function*/

	//std::cout << "vector \n"; //debug
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

		}//else
	}
	
	return EXIT_SUCCESS;
}
