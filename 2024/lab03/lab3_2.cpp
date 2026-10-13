// The Review supplies ride thresholds, but no literal input/output prompts.
#include <cmath>
#include <iostream>

int main()
{
    double first = 0.0;
    double second = 0.0;
    double third = 0.0;
    int ride = 0;
    if (!(std::cin >> first >> second >> third >> ride)
        || !std::isfinite(first) || !std::isfinite(second) || !std::isfinite(third)
        || first < 0 || second < 0 || third < 0) {
        std::cerr << "Enter three nonnegative heights and a ride number.\n";
        return 1;
    }
    int minimumHeight = 0;
    if (ride == 1) {
        minimumHeight = 140;
    } else if (ride == 2) {
        minimumHeight = 120;
    } else if (ride == 3) {
        minimumHeight = 100;
    } else {
        std::cerr << "Ride must be 1, 2, or 3.\n";
        return 1;
    }
    int people = 0;
    if (first >= minimumHeight) {
        ++people;
    }
    if (second >= minimumHeight) {
        ++people;
    }
    if (third >= minimumHeight) {
        ++people;
    }
    std::cout << people << '\n';
    return 0;
}
