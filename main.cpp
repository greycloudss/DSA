#include "priv.h"


std::string arithmetic::cropper(std::string a) {
    for (size_t i = 0; i < a.length(); ++i) {
        // Check if the character is not a digit and not a minus sign
        if (!(a[i] == '-') && !std::isdigit(a[i])) {
            // Replace non-digit characters (except for the minus sign) with spaces
            a[i] = ' ';
        }
    }
    return a;
}

void arithmetic::checker() {
        for (auto& i : numbers) {
            i = cropper(i);
            try {
                long long num = std::stoll(i);
                sum.push_back(num); // Directly push the number to sum
            }
            catch (const std::invalid_argument& ia) {
                std::cerr << "Invalid argument: " << ia.what() << '\n';
            }
        }
    }

d16 arithmetic::product() {
	d16 prod = this->sum[0];
	int ii = 1;
	std::string statustr;
	for (auto i : this->types) {
		if (ii < this->sum.size()) {
    switch (i) {
        case '+': {
            prod += this->sum[ii];
            break;
        }
        case '-': {
            prod -= this->sum[ii];
            break;
        }
        case '*': {
            // Check for multiplication overflow
            if (prod > 0 && this->sum[ii] > 0 && prod > INT64_MAX / this->sum[ii])
                throw std::overflow_error("Multiplication overflow");
            else if (prod < 0 && this->sum[ii] < 0 && prod < INT64_MIN / this->sum[ii])
                throw std::overflow_error("Multiplication underflow");
            prod *= this->sum[ii];
            break;
        }
        case '/': {
            // Check for division by zero
            if (this->sum[ii] == 0) {
                throw std::runtime_error("Division by zero");
            }
            prod /= this->sum[ii];
            break;
        }
        case '%': {
            // Convert prod and this->sum[ii] to integral types before modulo operation
            int64 prodInt = static_cast<int64>(prod);
            int64 divisorInt = static_cast<int64>(this->sum[ii]);
            // Perform modulo operation
            prodInt %= divisorInt;
            prod = static_cast<d16>(prodInt);
            break;
        }
        /*case '=': {
            uint64_t prodBit = *reinterpret_cast<uint64_t*>(&prod);
            uint64_t sumBit = *reinterpret_cast<uint64_t*>(&sum[ii]);

            // Perform bitwise operations
            uint64_t resultBit = prodBit ^ sumBit;

            if (resultBit == 1)
            {
                return "false";
            }
            else return "true";

            if (prod ^ sum[ii]) {
                return "false";
            }
            break;
        } WORK IN PROGRESS IGNORE PLS */
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
	//bool skip = false;

	this->breaks.push_back(0);
	for (auto i : this->org) {

        // skip if comparison operator
        //if (skip) {skip = false; continue;}

		if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%') {
			this->types.push_back(i);
			this->breaks.push_back(place);



		}
		place++;
		/*if ((i == '=' && i + 1 == '=') || (i == '!' && i + 1 == '=') || (i == '>' && i + 1 == '=') || (i == '<' && i + 1 == '=') ) {

            this->types.push_back(i);
			this->breaks.push_back(place + 1);

			place++;
			place++;
			skip = true;
		} */

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
	std::cout << std::fixed;
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

	while (1)
	{
	    std::cin >> b;

        arithmetic a(b);

        a.~arithmetic();

	}

	return 0;
}
