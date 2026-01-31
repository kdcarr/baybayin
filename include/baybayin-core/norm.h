#pragma once

namespace baybayin {

inline void first_pass(std::string& text) {

    for (size_t i = 0; i < text.size(); ++i) {
        auto& c = reinterpret_cast<unsigned char&>(text[i]);

        // 1. Bitwise Lowercase
        if (c >= 'A' && c <= 'Z') c |= 0x20;

        // 2. Greedy 1-to-1 Mapping
        switch (c) {
            case 'f': c = 'p'; break;
            case 'v': c = 'b'; break;
            case 'z': c = 's'; break;
            //case 'q': c = 'k'; break;
            //case 'j': c = 'i'; break; // 'j' can also be 'h' in Spanish loans, but 'i' is safer for 1:1
            case 'c': {
                if (i + 1 < text.size()) {
                    const unsigned char next = text[i + 1] | 0x20;

                    // If it's 'ch', we MUST skip it for Pass Two
                    // are there others?
                    if (next == 'h') break;

                    // Otherwise, it's a "Safe C" -> resolve to s or k
                    c = (next == 'e' || next == 'i') ? 's' : 'k';
                } else {
                    c = 'k'; // Trailing C
                }
                break;
            }
            default: break;
        }
    }
}

[[nodiscard]] inline std::string second_pass(std::string_view input) {
    std::string result;
    result.reserve(input.size() + 16);

    for (size_t i = 0; i < input.size(); ++i) {
        const char c = input[i];

        // 1. Word Expansions
        if (i == 0 || std::isspace(static_cast<unsigned char>(input[i-1])) && i+2 < input.size()) {
            if (input.substr(i, 2) == "ng" && std::isspace(static_cast<unsigned char>(input[i+2]))) {
                result += "nang"; i += 1; continue;
            }
            if (i+3 < input.size()) {
                if (input.substr(i, 3) == "mga" && std::isspace(static_cast<unsigned char>(input[i+3]))) {
                    result += "manga"; i += 2; continue;
                }
            }
        }

        // 2. The "C" Logic (Digraphs + Singletons)
        if (c == 'c') {
            if (i + 1 < input.size()) {
                const char next = input[i+1];
                // Case: ch
                if (next == 'h') {
                    if (i + 2 < input.size() && is_vowel(input[i+2])) {
                        result += "ts"; // ch + vowel -> ts
                    } else {
                        result += 'k';  // ch + consonant -> k
                    }
                    i += 1; // Skip 'h'
                    continue;
                }
                // Case: Single 'c' (not 'ch')
                result += (next == 'e' || next == 'i') ? 's' : 'k';
            } else {
                result += 'k'; // Trailing 'c'
            }
            continue;
        }

        // 3. Expansion: 'x' -> 'ks'
        if (c == 'x') {
            result += "ks";
            continue;
        }

        result += c;
    }
    return std::move(result);
}

inline std::string latin_to_phonetic_abakada(std::string &in, const Orthography ortho = Orthography::Reformed) {
    first_pass(in);
    auto second = second_pass(in);
    return std::move(second);
}

}