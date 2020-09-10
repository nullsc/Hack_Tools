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

#define MAX_VECTOR_SIZE 1536870912  //10000 0.5GB

const std::string whitespace = " \t\f\v\n\r"; //needs to be const

void log(std::ofstream& outfile, std::string& text); //was ofstream& infile
bool isAllBlank(std::string& str);
unsigned long getListSize(std::ifstream* inFile); //file needs to be already opened
int removeDuplicates(std::ifstream* inFile, std::ofstream* logFile);


std::string& rtrim(std::string& str);
std::string& ltrim(std::string& str);
std::string& trim(std::string& str);

int lineAppend(std::ifstream* inFile, std::ofstream* logFile, std::string& str, size_t mode);
#endif