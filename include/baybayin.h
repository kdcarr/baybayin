#pragma once
#include <string>
#include <string_view>

namespace baybayin {

/// ASCII-only lowercase (SIMD-friendly, branchless-ish)
inline char ascii_lower(char c) noexcept {
    return (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
}

inline bool is_vowel(char c) noexcept {
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}

inline void emit_vowel(std::string& out, char v) {
    // a / e,i / o,u
    switch (v) {
        case 'a': out += "ᜀ"; break;
        case 'e':
        case 'i': out += "ᜁ"; break;
        case 'o':
        case 'u': out += "ᜂ"; break;
    }
}

inline void emit_consonant(std::string& out, char c) {
    switch (c) {
        case 'b': out += "ᜊ"; break;
        case 'k': out += "ᜃ"; break;
        case 'd': out += "ᜇ"; break;
        case 'g': out += "ᜄ"; break;
        case 'h': out += "ᜑ"; break;
        case 'l': out += "ᜎ"; break;
        case 'm': out += "ᜋ"; break;
        case 'n': out += "ᜈ"; break;
        case 'p': out += "ᜉ"; break;
        case 'r': out += "ᜇ"; break;
        case 's': out += "ᜐ"; break;
        case 't': out += "ᜆ"; break;
        case 'w': out += "ᜏ"; break;
        case 'y': out += "ᜌ"; break;
    }
}




inline std::string latin_to_baybayin(std::string_view in) {
    std::string out;
    out.reserve(in.size() * 3); // UTF-8 Baybayin ≈ 3 bytes/glyph

    const size_t n = in.size();
    for (size_t i = 0; i < n; ++i) {
        char c = ascii_lower(in[i]);

        // --- NG digraph ---
        if (c == 'n' && i + 1 < n && ascii_lower(in[i + 1]) == 'g') {
            out += "ᜅ";
            ++i;

            if (i + 1 < n && is_vowel(ascii_lower(in[i + 1]))) {
                char v = ascii_lower(in[i + 1]);
                if (v == 'i' || v == 'e') out += "ᜒ";
                else if (v == 'o' || v == 'u') out += "ᜓ";
                ++i;
            } else {
                out += "᜔"; // virama
            }
            continue;
        }

        // --- standalone vowel ---
        if (is_vowel(c)) {
            emit_vowel(out, c);
            continue;
        }

        // --- consonant ---
        switch (c) {
            case 'b': case 'k': case 'd': case 'g': case 'h':
            case 'l': case 'm': case 'n': case 'p': case 'r':
            case 's': case 't': case 'w': case 'y':
                emit_consonant(out, c);

                if (i + 1 < n && is_vowel(ascii_lower(in[i + 1]))) {
                    char v = ascii_lower(in[i + 1]);
                    if (v == 'i' || v == 'e') out += "ᜒ";
                    else if (v == 'o' || v == 'u') out += "ᜓ";
                    ++i;
                } else {
                    out += "᜔";
                }
                break;

            default:
                // punctuation / space / digits
                out += in[i];
        }
    }

    return out;
}

} // namespace baybayin
