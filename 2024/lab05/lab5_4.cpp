#include <iostream>
#include <limits>

int main()
{
    long long height = 0, width = 0;
    std::cout << "Enter height and width: ";
    if (!(std::cin >> height >> width) || height < 3 || width < 3
        || height > 2147483647LL || width > 2147483647LL) {
        std::cerr << "This interface supports dimensions from 3 to 2147483647.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char seq1 = '.', seq2 = '.', seq3 = '.', seq4 = '.';
    char seq5 = '.', seq6 = '.', seq7 = '.', seq8 = '.';
    int length = 0;
    bool valid = false;
    do {
        std::cout << "Enter Sequence: ";
        length = 0;
        valid = true;
        char symbol = 0;
        while (std::cin.get(symbol) && symbol != '\n') {
            if (symbol == '\r') continue;
            if (length <= 8) ++length;
            if (symbol != '.' && !(symbol >= 'a' && symbol <= 'z')
                && !(symbol >= 'A' && symbol <= 'Z')) valid = false;
            switch (length) {
            case 1: seq1 = symbol; break;
            case 2: seq2 = symbol; break;
            case 3: seq3 = symbol; break;
            case 4: seq4 = symbol; break;
            case 5: seq5 = symbol; break;
            case 6: seq6 = symbol; break;
            case 7: seq7 = symbol; break;
            case 8: seq8 = symbol; break;
            default: valid = false; break;
            }
        }
        if (!std::cin) return 0;
        if (length == 0 || length > 8) valid = false;
        if (!valid) std::cout << "Out of the bound. Enter again.\n";
    } while (!valid);

    const long long route = 2 * (height + width - 2);
    long long positionA = 0, positionB = 0;
    long long scoreA = 100, scoreB = 100;
    std::cout << "\nStart Game!";
    while (positionA < route && positionB < route) {
        std::cout << '\n';
        // The Review completes both A and B's turn before ending a round.
        for (int player = 0; player < 2; ++player) {
            int steps = 0;
            bool accepted = false;
            do {
                std::cout << (player == 0 ? "A move: " : "B move: ");
                if (std::cin >> steps) {
                    accepted = steps >= 1 && steps <= 6;
                } else {
                    if (std::cin.eof()) return 0;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (!accepted) std::cout << "Out of the bound. Enter again.\n";
            } while (!accepted);
            long long position = player == 0 ? positionA : positionB;
            long long score = player == 0 ? scoreA : scoreB;
            position += steps;
            if (position == height - 1 || position == height + width - 2
                || position == 2 * height + width - 3) position -= 2;
            if (position > route) position = route;
            if (position < route) {
                const int index = static_cast<int>((position + length - 1) % length + 1);
                char symbol = '.';
                switch (index) {
                case 1: symbol = seq1; break;
                case 2: symbol = seq2; break;
                case 3: symbol = seq3; break;
                case 4: symbol = seq4; break;
                case 5: symbol = seq5; break;
                case 6: symbol = seq6; break;
                case 7: symbol = seq7; break;
                case 8: symbol = seq8; break;
                }
                if (symbol >= 'a' && symbol <= 'z') score += symbol - 'a' + 1;
                else if (symbol >= 'A' && symbol <= 'Z') score -= symbol - 'A' + 1;
            }
            if (player == 0) { positionA = position; scoreA = score; }
            else { positionB = position; scoreB = score; }
        }
        std::cout << "A and B are at position " << positionA << " and " << positionB << '\n'
                  << "A and B have score " << scoreA << " and " << scoreB << '\n';
    }
    if (scoreA > scoreB) std::cout << "Player A wins the game!\n";
    else if (scoreB > scoreA) std::cout << "Player B wins the game!\n";
    else std::cout << "The two players are tied!\n";
    return 0;
}
