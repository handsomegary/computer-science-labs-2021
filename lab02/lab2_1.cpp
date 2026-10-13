#include <cmath>
#include <iostream>

int main()
{
    double celsius = 0.0;
    std::cout << "Please input temperature value in Celsius degree: ";
    if (!(std::cin >> celsius) || !std::isfinite(celsius)) {
        std::cerr << "Invalid temperature.\n";
        return 1;
    }
    const double fahrenheit = celsius * (9.0 / 5.0) + 32.0;
    if (!std::isfinite(fahrenheit)) {
        std::cerr << "Temperature is outside the supported numeric range.\n";
        return 1;
    }
    std::cout << "The corresponding value in Fahrenheit degree is: "
              << fahrenheit << '\n';
    return 0;
}
