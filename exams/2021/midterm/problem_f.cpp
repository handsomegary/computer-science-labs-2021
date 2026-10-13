// Based on the provided exam and reference code.
// Search denominations and compute exact coverage; no answer table is hardcoded.
#include <algorithm>
#include <iostream>
#include <vector>

int coverage(const std::vector<int>& minimumStamps, int maximumStamps)
{
    int value = 1;
    while (value < static_cast<int>(minimumStamps.size()) && minimumStamps[value] <= maximumStamps) ++value;
    return value - 1;
}

void searchDenominations(int maximumStamps, int denominationCount, int selected,
                         int previous, int consecutive, const std::vector<int>& minimumStamps,
                         int& best)
{
    if (selected == denominationCount) {
        best = std::max(best, consecutive);
        return;
    }
    // Even the next denomination cannot exceed the first uncovered value.
    // Adding another denomination can cover no more than h*(coverage+1).
    int optimistic = consecutive;
    for (int remaining = selected; remaining < denominationCount; ++remaining)
        optimistic = maximumStamps * (optimistic + 1);
    if (optimistic <= best) return;

    for (int denomination = consecutive + 1; denomination > previous; --denomination) {
        std::vector<int> next(static_cast<std::size_t>(maximumStamps * denomination + 1), maximumStamps + 1);
        std::copy(minimumStamps.begin(), minimumStamps.end(), next.begin());
        for (int value = denomination; value < static_cast<int>(next.size()); ++value) {
            if (next[value - denomination] < maximumStamps)
                next[value] = std::min(next[value], next[value - denomination] + 1);
        }
        searchDenominations(maximumStamps, denominationCount, selected + 1, denomination,
                            coverage(next, maximumStamps), next, best);
    }
}

int optimumCoverage(int maximumStamps, int denominationCount)
{
    // Denomination 1 is necessary to make the first value of the sequence.
    std::vector<int> minimumStamps(static_cast<std::size_t>(maximumStamps + 1));
    for (int value = 0; value <= maximumStamps; ++value) minimumStamps[value] = value;
    int best = 0;
    searchDenominations(maximumStamps, denominationCount, 1, 1, maximumStamps, minimumStamps, best);
    return best;
}

int main()
{
    int cached[9][9] = {};
    int maximumStamps = 0, denominationCount = 0;
    while (std::cin >> maximumStamps >> denominationCount) {
        if (maximumStamps == 0 && denominationCount == 0) return 0;
        if (maximumStamps < 1 || denominationCount < 1 || maximumStamps > 8
            || denominationCount > 8 || maximumStamps + denominationCount > 9) {
            std::cerr << "Invalid stamp limits.\n";
            return 1;
        }
        int& answer = cached[maximumStamps][denominationCount];
        if (answer == 0) answer = optimumCoverage(maximumStamps, denominationCount);
        std::cout << answer << '\n';
    }
    return 0;
}
