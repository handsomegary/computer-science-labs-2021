// Based on the provided exam and reference code.
#include <iostream>

void Hanoi(int disks, char source, char auxiliary, char target);

int main()
{
    int disks = 0;
    if (!(std::cin >> disks) || disks < 3 || disks > 10) {
        std::cerr << "Invalid disk count.\n";
        return 1;
    }
    Hanoi(disks, 'A', 'B', 'C');
    return 0;
}

void Hanoi(int disks, char source, char auxiliary, char target)
{
    if (disks == 0) return;
    Hanoi(disks - 1, source, target, auxiliary);
    std::cout << "move disk " << disks << " from " << source << " to " << target << '\n';
    Hanoi(disks - 1, auxiliary, source, target);
}
