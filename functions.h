#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

#include "Country.h"

#define CSV_EXTENSION ".csv"
#define WINNERS_NUM 10

namespace fs = std::filesystem;

bool isDirExists(const fs::path&);

std::vector<fs::path> readDir(const fs::path&);

bool isCSVFile(const fs::path&);

std::vector<Country> getCountries(const std::vector<fs::path>& paths);

void distributePoints(std::vector<Country>&);

void giveRates(std::vector<Country>& countries);

void sortByRate(std::vector<Country>& countries);

std::vector<Country> calcResults(const std::vector<fs::path>& paths);