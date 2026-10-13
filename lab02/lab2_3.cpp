#include <cmath>
#include <iostream>

int main()
{
    double weight = 0.0;
    double height = 0.0;
    std::cout << "Please enter your weight: ";
    if (!(std::cin >> weight)) {
        std::cerr << "Invalid weight.\n";
        return 1;
    }
    std::cout << "Please enter your height: ";
    if (!(std::cin >> height) || !std::isfinite(weight)
        || !std::isfinite(height) || weight <= 0.0 || height <= 0.0) {
        std::cerr << "Weight and height must be positive numbers.\n";
        return 1;
    }

    const double bmi = weight / height / height;
    if (!std::isfinite(bmi)) {
        std::cerr << "BMI is outside the supported numeric range.\n";
        return 1;
    }
    std::cout << "Your BMI is " << bmi << '\n';
    if (bmi < 18.5) {
        std::cout << "You need to eat more\n";
    } else if (bmi < 24.0) {
        std::cout << "You are healthy\n";
    } else {
        std::cout << "You need to control your diet\n";
    }
    return 0;
}
