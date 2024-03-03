#include "priv.h"


std::string arithmetic::cropper(std::string a) {
	char tmp[2];
	tmp[1] = '\0';
	
	int ii = a.length();
	for (int i = 0; i < a.length(); --ii, ++i) {
		if (!(a[i] == '-')) {
			tmp[0] = a[i];
			if (!(std::isdigit(tmp[0]))) 
				a[i] = ' ', a[ii] = ' ';
		}
	}

	return a;
}

void arithmetic::checker() {
	for (const auto& i : this->numbers) {
		try {
			int num = std::stoi(i);
			this->sum.push_back(static_cast<d16>(num));
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << '\n';
		}
	}
}

d16 arithmetic::product() {
	d16 prod = this->sum[0];
	int ii = 1;
	for (auto i : this->types) {
		if (ii < this->sum.size()) {
			switch (i) {
			case '+':
				prod += this->sum[ii];
				break;
			case '-':
				prod -= this->sum[ii];
				break;
			case '*':
				// Check for multiplication overflow
				if (prod > 0 && this->sum[ii] > 0 && prod > INT64_MAX / this->sum[ii]) 
					throw std::overflow_error("Multiplication overflow");
				else if (prod < 0 && this->sum[ii] < 0 && prod < INT64_MIN / this->sum[ii]) 
					throw std::overflow_error("Multiplication underflow");
				prod *= this->sum[ii];
				break;
			case '/':
				// Check for division by zero
				if (this->sum[ii] == 0) {
					throw std::runtime_error("Division by zero");
				}
				prod /= this->sum[ii];
				break;
			case '%':
				// Convert prod and this->sum[ii] to integral types before modulo operation
				int64 prodInt = static_cast<int64>(prod);
				int64 divisorInt = static_cast<int64>(this->sum[ii]);
				// Perform modulo operation
				prodInt %= divisorInt;
				prod = static_cast<d16>(prodInt);
				break;
			}
			ii++;
		}
		else
			break;
	}

	return prod;
}


arithmetic::arithmetic(std::string a) {
	this->org = a;
	int place = 0;
	
	this->breaks.push_back(0);
	for (auto i : this->org) {
		if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%') {
			this->types.push_back(i);
			this->breaks.push_back(place);
		}
		place++;
	}
	this->breaks.push_back(a.length());
	int start, end;

	for (int i = 0; i < this->breaks.size() - 1; ++i) {
			start = this->breaks[i];
			end = this->breaks[i + 1];
			std::string substring = this->org.substr(start, end - start);
			this->numbers.push_back(substring);
			std::cout << substring << " ";
			
	}
	checker();
	std::cout << " = " << product() << std::endl;
}

arithmetic::~arithmetic() {
	sum.clear();
	numbers.clear();
	breaks.clear();
	types.clear();
}


int main() {

	std::string b;
	label:
	std::cin >> b;

	arithmetic a(b);


	a.~arithmetic();
	goto label;
	return 0;
}