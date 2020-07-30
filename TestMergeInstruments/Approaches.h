#pragma once

#include <string>

void aproach1(std::string& g1, std::string& g2);

void aproach2(std::string& g1, std::string& g2);

void aproach3(std::string& g1, std::string& g2, char** argv);

void aproach4(std::string& g1, std::string& g2, char** argv);

std::string extractGenomeNameFromFullPath(std::string fullpath);