#pragma once
#ifndef MENU_H
#define MENU_H

//menu
#include <iostream>
#include <string>
#include <fstream>

void banner();
void printMenu();

const std::string whitespace = " \t\f\v\n\r"; //needs to be const

std::string& rtrim(std::string &str);
std::string& ltrim(std::string& str);
std::string& trim(std::string& str);


#endif
