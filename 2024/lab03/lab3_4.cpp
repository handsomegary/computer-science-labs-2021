#include <iostream>
#include <limits>

bool readWithin(int& number, int lower, int upper)
{
    while (true) {
        if (std::cin >> number) {
            if (number > lower && number < upper) {
                return true;
            }
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Out of range! Please enter again: ";
    }
}

int main()
{
    int target = 0;
    std::cout << "Enter the bomb number (0~100): ";
    if (!readWithin(target, 0, 100)) {
        return 0;
    }
    int lower = 0;
    int upper = 100;
    int guess = 0;
    int rounds = 0;
    while (true) {
        std::cout << "Range " << lower << '~' << upper << ": ";
        if (!readWithin(guess, lower, upper)) {
            return 0;
        }
        ++rounds; // Invalid input retries are not guesses.
        if (guess == target) {
            break;
        } else if (guess < target) {
            lower = guess;
        } else {
            upper = guess;
        }
    }
    // The Review requests these two values but omits their exact final wording.
    std::cout << "Bomb number: " << target << "\nRounds: " << rounds << '\n';
    return 0;
}
