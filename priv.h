#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdint>
#pragma once
#define int64 long long
#define d16 long double

class arithmetic {
private:
	std::string org; // originalus skaicius
	std::vector<d16> sum; // convertinti skaiciai
	std::vector<std::string> numbers;
	std::vector<int> breaks;
	std::vector<char> types;
public:
	arithmetic(std::string a);
	~arithmetic();
	void checker();
	d16 product();
	std::string cropper(std::string a);
};
