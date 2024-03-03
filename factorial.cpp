#include <iostream>
#include <vector>

int main()
{
    std::cout << "Calculate n!   Enter n (max 10000): ";
    unsigned int input{};
    if ((std::cin >> input) && (input <= 10000)) {
        std::vector<unsigned int> result(3000, 0); 
        result.back() = 1;                         
        for (unsigned int count = 2; count <= input; count++)
        {
            unsigned int sum{}, remainder{};
            unsigned int i = result.size() - 1;
            while (i > 0)
            {
                sum = result[i] * count + remainder;
                result[i--] = sum % 10;
                remainder = sum / 10;
            }
        }
        bool showZeros{ false };
        for (const unsigned int i : result) {
            if ((i != 0) || showZeros) {
                std::cout << i;
                showZeros = true;
            }
        }
    }
    else std::cerr << "\nError: Wrong input.";
}