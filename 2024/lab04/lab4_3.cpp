// Interface selected locally: weight, then counts of 1/5/10/25/50 kg boxes.
#include <algorithm>
#include <iostream>

bool smallerBoxesFit(long long weight, long long ones, long long fives, long long tens)
{
    weight -= std::min(tens, weight / 10) * 10;
    weight -= std::min(fives, weight / 5) * 5;
    return weight <= ones;
}

int main()
{
    long long weight = 0;
    long long ones = 0, fives = 0, tens = 0, twentyFives = 0, fifties = 0;
    if (!(std::cin >> weight >> ones >> fives >> tens >> twentyFives >> fifties)
        || weight < 0 || ones < 0 || fives < 0 || tens < 0 || twentyFives < 0 || fifties < 0) {
        std::cerr << "Enter a nonnegative weight and five nonnegative box counts.\n";
        return 1;
    }
    const long long cappedFifties = std::min(fifties, weight / 50);
    const long long cappedTwentyFives = std::min(twentyFives, weight / 25);
    long long units = std::min(weight / 25, 2 * cappedFifties + cappedTwentyFives);
    bool possible = false;
    if (twentyFives == 0) {
        units -= units % 2; // With only 50 kg boxes, 25 kg unit counts are even.
        possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
    } else {
        // 2*a+b spans every integer from 0 through 2*fifties+twentyFives.
        // For each parity, use its largest unit count. Smaller same-parity
        // counts add 50 kg to the remainder and cannot improve feasibility
        // for the divisible chain 10, 5, 1.
        possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
        if (!possible && units > 0) {
            possible = smallerBoxesFit(weight - (units - 1) * 25, ones, fives, tens);
        }
    }
    std::cout << (possible ? "YES\n" : "NO\n");
    return 0;
}
