#pragma once
#ifndef MENU_H
#define MENU_H

//menu
#include <iostream>
#include <string>

void banner();
void printMenu();

std::string& rtrim(std::string &str);
std::string& ltrim(std::string& str);
std::string& trim(std::string& str);

#endif
