#pragma once
#include <iostream>
#include <filesystem>
#include <vector>

#define CSV_EXTENSION ".csv"

namespace fs = std::filesystem;

bool isDirExists(const fs::path&);

std::vector<fs::path> readDir(const fs::path&);

bool isCSVFile(const fs::path&);