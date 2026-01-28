#pragma once
#include <string>
#include <string_view>

namespace baybayin {

enum class Orthography {
    // NOTES: https://luffykudo.wordpress.com/2020/08/10/how-to-read-and-write-baybayin/
    Traditional,  // Pre-colonial: no ending consonants for syllables (or words)
    Reformed,     // Added ending consonants for syllables (and words), adds word spacing, | as comma,
    Modern        // Suggestions (added additional sounds:  f, j, v, z ??
};

enum class Virama {
    Krus,         // Standard Spanish "+"
    Pamudpod      // Modern curved slash style "᜴ "
};

inline char ascii_lower(char c) noexcept {
    return (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
}

inline bool is_vowel(char c) noexcept {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

inline void emit_vowel(std::string& out, char v) {
    switch (v) {
        case 'a': out += "ᜀ"; break;
        case 'e': case 'i': out += "ᜁ"; break;
        case 'o': case 'u': out += "ᜂ"; break;
    }
}

inline void emit_consonant(std::string& out, char c, Orthography ortho) {
    switch (c) {
        case 'b': out += "ᜊ"; break;
        case 'k': out += "ᜃ"; break;
        // r and d are allophones of the same phoneme
        case 'r':
        case 'd': out += "ᜇ"; break;
        case 'g': out += "ᜄ"; break;
        case 'h': out += "ᜑ"; break;
        case 'l': out += "ᜎ"; break;
        case 'm': out += "ᜋ"; break;
        case 'n': out += "ᜈ"; break;
        case 'p': out += "ᜉ"; break;
        case 's': out += "ᜐ"; break;
        case 't': out += "ᜆ"; break;
        case 'w': out += "ᜏ"; break;
        case 'y': out += "ᜌ"; break;
    }
}

inline std::string latin_to_baybayin(const std::string_view in,
                                     const Orthography ortho = Orthography::Reformed,
                                     const Virama style = Virama::Krus) {
    std::string out;
    out.reserve(in.size() * 3);
    const size_t n = in.size();

    auto apply_virama = [&](char c, size_t pos) {
        if (ortho != Orthography::Traditional) {
            emit_consonant(out, c, ortho);
            out += (style == Virama::Pamudpod ? "᜴" : "᜔");
        }
    };

    for (size_t i = 0; i < n; ++i) {
        char c = ascii_lower(in[i]);

        // --- NG Digraph ---
        if (c == 'n' && i + 1 < n && ascii_lower(in[i + 1]) == 'g') {
            size_t ng_pos = i + 1; // Position of the 'g'
            if (ng_pos + 1 < n && is_vowel(ascii_lower(in[ng_pos + 1]))) {
                out += "ᜅ";
                char v = ascii_lower(in[ng_pos + 1]);
                if (v == 'i' || v == 'e') out += "ᜒ";
                else if (v == 'o' || v == 'u') out += "ᜓ";
                i += 2; // Skip 'g' and vowel
            } else {
                // It's a trailing NG
                if (ortho == Orthography::Modern || (ortho == Orthography::Reformed && (ng_pos == n - 1 || std::isspace(in[ng_pos+1])))) {
                    out += "ᜅ";
                    out += (style == Virama::Pamudpod ? "᜴" : "᜔");
                }
                i += 1; // Skip 'g'
            }
            continue;
        }

        // --- Standalone Vowel ---
        if (is_vowel(c)) {
            emit_vowel(out, c);
            continue;
        }

        // --- Consonant Cluster / Coda ---
        switch (c) {
            case 'b': case 'k': case 'd': case 'g': case 'h':
            case 'l': case 'm': case 'n': case 'p': case 'r':
            case 's': case 't': case 'w': case 'y':
                if (i + 1 < n && is_vowel(ascii_lower(in[i + 1]))) {
                    emit_consonant(out, c, ortho);
                    char v = ascii_lower(in[i + 1]);
                    if (v == 'i' || v == 'e') out += "ᜒ";
                    else if (v == 'o' || v == 'u') out += "ᜓ";
                    ++i;
                } else {
                    apply_virama(c, i);
                }
                break;
            default:
                out += in[i]; // Non-alphabetic
        }
    }
    return out;
}

} // namespace baybayin
