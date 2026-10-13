// 2024 P113028: configurable reference implementation of the supplied diagrams.
// The Review omits the iteration-count and round-selection rules. Those values
// are explicit inputs here; FEISTEL_SPEC.md distinguishes them from lecture rules.
#include <cstdint>
#include <iostream>

std::uint32_t swap_bits(std::uint32_t value, unsigned first, unsigned second) {
    if (((value >> first) & 1u) != ((value >> second) & 1u))
        value ^= (1u << first) | (1u << second);
    return value;
}

std::uint32_t scramble(std::uint32_t control, std::uint32_t value) {
    // SWAP(x,y) in the slide: x.bit4 controls y.bit7 <-> y.bit5;
    // x.bit3 controls y.bit2 <-> y.bit0. Native bits preserve leading zeros.
    if (control & 16u) value = swap_bits(value, 7, 5);
    if (control & 8u) value = swap_bits(value, 2, 0);
    return value;
}

std::uint32_t select_key(int index, std::uint32_t key0, std::uint32_t key1,
                         std::uint32_t key2, std::uint32_t key3) {
    switch (index) {
        case 0: return key0;
        case 1: return key1;
        case 2: return key2;
        default: return key3;
    }
}

bool round_function(unsigned selector, std::uint32_t right,
                    std::uint32_t key, std::uint32_t& result) {
    switch (selector) {
        case 0: result = right ^ key; break;
        case 1: result = right & key; break;
        case 2: result = right | key; break;
        case 3: {
            // The slide's MOD applies separately to the two 8-bit halves.
            const std::uint32_t high_divisor = key >> 8;
            const std::uint32_t low_divisor = key & 255u;
            if (high_divisor == 0 || low_divisor == 0) return false;
            result = (((right >> 8) % high_divisor) << 8)
                     | ((right & 255u) % low_divisor);
            break;
        }
        default: return false;
    }
    return true;
}

bool feistel_round(std::uint32_t& left, std::uint32_t& right,
                   std::uint32_t key, unsigned selector, bool inverse) {
    std::uint32_t transformed;
    if (!round_function(selector, inverse ? left : right, key, transformed)) return false;
    if (inverse) {
        const std::uint32_t old_right = left;
        left = right ^ transformed;
        right = old_right;
    } else {
        const std::uint32_t old_right = right;
        right = left ^ transformed;
        left = old_right;
    }
    return true;
}

bool read_byte(std::uint32_t& value) {
    long long input;
    if (!(std::cin >> input) || input < 0 || input > 255) return false;
    value = static_cast<std::uint32_t>(input);
    return true;
}

int main() {
    std::uint32_t key0, key1, key2, key3;
    int control0, control1, control2, control3;
    if (!read_byte(key0) || !read_byte(key1) || !read_byte(key2) || !read_byte(key3)
        || !(std::cin >> control0 >> control1 >> control2 >> control3)
        || control0 < -1 || control0 > 3 || control1 < -1 || control1 > 3
        || control2 < -1 || control2 > 3 || control3 < -1 || control3 > 3) {
        std::cout << "error\n";
        return 1;
    }
    // All controls refer to the original input keys; -1 means no scrambling.
    const std::uint32_t scrambled0 = control0 == -1 ? key0
        : scramble(select_key(control0, key0, key1, key2, key3), key0);
    const std::uint32_t scrambled1 = control1 == -1 ? key1
        : scramble(select_key(control1, key0, key1, key2, key3), key1);
    const std::uint32_t scrambled2 = control2 == -1 ? key2
        : scramble(select_key(control2, key0, key1, key2, key3), key2);
    const std::uint32_t scrambled3 = control3 == -1 ? key3
        : scramble(select_key(control3, key0, key1, key2, key3), key3);
    const std::uint32_t KEY1 = (scrambled0 << 8) | scrambled1;
    const std::uint32_t KEY2 = (scrambled2 << 8) | scrambled3;

    char mode;
    std::uint32_t byte0, byte1, byte2, byte3;
    if (!(std::cin >> mode)) return 1;
    if (mode == 'N') {
        if (!read_byte(byte0) || !read_byte(byte1) || !read_byte(byte2) || !read_byte(byte3)) {
            std::cout << "error\n";
            return 1;
        }
    } else if (mode == 'T') {
        // Exactly one delimiter follows T; the next four raw bytes are the text.
        char delimiter, char0, char1, char2, char3;
        if (!std::cin.get(delimiter) || (delimiter != ' ' && delimiter != '\n' && delimiter != '\t')
            || !std::cin.get(char0) || !std::cin.get(char1)
            || !std::cin.get(char2) || !std::cin.get(char3)) {
            std::cout << "error\n";
            return 1;
        }
        byte0 = static_cast<unsigned char>(char0);
        byte1 = static_cast<unsigned char>(char1);
        byte2 = static_cast<unsigned char>(char2);
        byte3 = static_cast<unsigned char>(char3);
    } else {
        std::cout << "error\n";
        return 1;
    }
    std::uint32_t left = (byte0 << 8) | byte1;
    std::uint32_t right = (byte2 << 8) | byte3;
    long long rounds;
    if (!(std::cin >> rounds) || rounds < 0) {
        std::cout << "error\n";
        return 1;
    }
    for (long long i = 0; i < rounds; ++i) {
        char direction;
        int key_index;
        long long selector;
        if (!(std::cin >> direction >> key_index >> selector)
            || (direction != 'E' && direction != 'D')
            || (key_index != 1 && key_index != 2)
            || selector < 0 || selector > 3
            || !feistel_round(left, right, key_index == 1 ? KEY1 : KEY2,
                              static_cast<unsigned>(selector), direction == 'D')) {
            std::cout << "error\n";
            return 1;
        }
    }
    if (mode == 'N') {
        std::cout << (left >> 8) << ' ' << (left & 255u) << ' '
                  << (right >> 8) << ' ' << (right & 255u) << '\n';
    } else {
        std::cout << static_cast<char>(left >> 8) << static_cast<char>(left & 255u)
                  << static_cast<char>(right >> 8) << static_cast<char>(right & 255u) << '\n';
    }
    return 0;
}
