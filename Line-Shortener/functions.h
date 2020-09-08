#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define LEFT 1 //trimmer
#define RIGHT 2
#define BOTH 3

#define MAX_VECTOR_SIZE 1536870912  // ~0.5GB

void log(std::ofstream& outfile, std::string& text); //
unsigned long getListSize(std::ifstream* inFile); //file needs to be already opened
int removeDuplicates(std::ifstream* inFile, std::ofstream* logFile);

#endif
