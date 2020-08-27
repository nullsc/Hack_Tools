#pragma once
#ifndef MENU_H
#define MENU_H

//menu
#include <iostream>
#include <string>

void banner();
void printMenu();

const std::string whitespace = " \t\f\v\n\r";

std::string& rtrim(std::string &str);
std::string& ltrim(std::string& str);
std::string& trim(std::string& str);

#endif
