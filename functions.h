#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#pragma once
#include <vector>

#include "Country.h"

#define CSV_EXTENSION ".csv"
#define WINNERS_NUM 10

namespace fs = std::filesystem;

bool isDirExists(const fs::path&);

std::vector<fs::path> readDir(const fs::path&);

bool isCSVFile(const fs::path&);

std::vector<Country> getCountries(const std::vector<fs::path>& paths);