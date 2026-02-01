#pragma once

#include <string>
#include <string_view>
#include <cctype>

namespace phil_norm {

enum class ForeignLanguage {
    SPANISH,
    ENGLISH,
};
enum class LatinOrthography {
    ABAKADA,    // a, b, k, d, e,    g, h, i,       l, m, m,    ng, o, p,    r, s, t, u,    w,    y,
    ALPABETONG, // a, b, c, d, e, f, g, h, i, j, k, l, m, n, ñ, ng, o, p, q, r, s, t, u, v, w, x, y, z
};
enum class Diphthong {
    TRADITIONAL,
    REFORMED,
};
enum class InitialCluster {
    TRADITIONAL,
    REFORMED,
};

constexpr bool is_vowel(const char c) noexcept {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

constexpr bool is_consonant(const char c) noexcept {
    return (c >= 'a' && c <= 'z') && !is_vowel(c);
}

/**
 * consonant_normalizer is a first pass normalization function. it converts alpha to lower case, reduces whitespace,
 * expands ng and mga, and performs phonetic substitution for the specified orthography.
 *
 * this is basically working on foreign words,
 * @param input
 * @param mode
 * @param ortho
 * @return
 */
inline std::string foreign_normalizer(const std::string_view& input,
    const ForeignLanguage mode=ForeignLanguage::SPANISH,
    const LatinOrthography ortho=LatinOrthography::ABAKADA,
    const Diphthong dipht_mode=Diphthong::REFORMED,
    const InitialCluster initial_cluster_mode=InitialCluster::REFORMED) {

    bool in_whitespace = false;
    std::string out;
    out.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        // TODO: bug we are looking ahead down in the code and those haven't been to-lowered yet
        const char c = input[i] >= 'A' && input[i] <= 'Z' ? input[i] | static_cast<char>(0x20) : input[i];
        if (std::isspace(c)) {
            if (!out.empty() && !in_whitespace) {
                out.push_back(' ');
                in_whitespace = true;
            }
            continue;
        }
        in_whitespace = false;

        // Expansion: mga/ng
        if (out.empty() || out.back() == ' ') {
            if (c == 'm' && (i + 2 < input.size()) && (input[i+1]|0x20) == 'g' && (input[i+2]|0x20) == 'a') {
                if (const size_t next = i + 3; next == input.size() || std::isspace(static_cast<unsigned char>(input[next]))) {
                    out.append("manga");
                    i += 2; continue;
                }
            }
            if (c == 'n' && (i + 1 < input.size()) && (input[i+1]|0x20) == 'g') {
                if (const size_t next = i + 2; next == input.size() || std::isspace(static_cast<unsigned char>(input[next]))) {
                    out.append("nang");
                    i += 1; continue;
                }
            }
        }

        switch (c) {
            case 'f':
                out.push_back(ortho == LatinOrthography::ABAKADA ? 'p' : 'f');
                continue;
            case 'v':
                out.push_back(ortho == LatinOrthography::ABAKADA ? 'b' : 'v');
                continue;
            case 'z':
                out.push_back(ortho == LatinOrthography::ABAKADA ? 's' : 'z');
                continue;
            case 'x':
                out.append(ortho == LatinOrthography::ABAKADA ? "ks" : "x");
                continue;

            case 'c': {
                std::array hard_vowels = {'a', 'o', 'u'};
                // TODO: this might be the best place to handle double vowels since we know its not a Philippine word
                // chair -> tser
                if (auto next = i+1; next < input.size()) {
                    if (input[next] == 'h') {
                        if (++next; next < input.size() && not is_vowel(input[next])) {
                                out.append("k");
                                i++;
                                continue;
                        }
                        out.append("ts");
                        i++;
                        continue;
                    }
                    if (input[next] == 'k') {
                        out.append("k");
                        i++;
                        continue;
                    }
                    if (std::ranges::count(hard_vowels.begin(), hard_vowels.end(), input[next]) or not is_vowel(input[next])) {
                        out.append("k");
                        continue;
                    }
                } else {
                    out.append("k");
                    continue;
                }
                out.append("s");
                continue;
            }
            case 'j':
                if (auto next = i+1; next < input.size()) {
                    // TODO: this might be the best place to handle double vowels since we know its not a Philippine word
                    if (input[next] == 'u') {
                        std::array es_double_vowel_clues = { 'a', 'e', 'i'};
                        if (++next; next < input.size() && std::ranges::count(es_double_vowel_clues, input[next])) {
                            out.append("h");
                            continue;
                        }
                    }
                }
                out.append("dy");
                continue;
            case 'q':
                if (const auto next = i+1; next < input.size()) {
                    if (input[next] == 'u') {
                        out.append(mode == ForeignLanguage::ENGLISH ? "kw" : "k");
                        i++;
                        continue;
                    }
                    out.push_back('k');
                    continue;
                }

            // handle spanish or modern filipino ñ, Ñ
            case static_cast<char>(0xC3):
                if (const auto next=i+1; next<input.size()) {
                    if (input[next] == static_cast<char>(0xB1) ||
                        input[next] == static_cast<char>(0x91)) {
                        out.append("ny");
                        i++;
                        }
                }
                continue;

            // handle native diphthongs
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':

            // TODO: we may want to convert digits to the phonetic spellings
            // for now, pass-through punctuation, numbers etc.
            default:
                out.push_back(c);
                continue;
        }
    }
    if (!out.empty() && out.back() == ' ') out.pop_back();
    return std::move(out);
}

inline void smooth_initial_cluster(std::string& s) {
    if (s.size() < 2) return;

    size_t start = 0;
    while (start < s.size()) {
        // Find start of word
        while (start < s.size() && !std::isalpha(static_cast<unsigned char>(s[start]))) start++;

        if (start + 1 < s.size() && is_consonant(s[start]) && is_consonant(s[start+1])) {
            // Check for 'ng' digraph (don't break it)
            if ((s[start] == 'n' && s[start+1] == 'g') ||
                (s[start] == 'k' && s[start+1] == 'w') ||
                (s[start] == 't' && s[start+1] == 's') ||
                (s[start] == 'd' && s[start+1] == 'y') ||
                (s[start] == 'n' && s[start+1] == 'y') ||
                (s[start] == 'k' && s[start+1] == 's') ){
                // Move to next word
            } else {
                // Insert vowel (defaulting to the first following vowel)
                char v = 'i';
                for (size_t j = start + 2; j < s.size() && !std::isspace(s[j]); ++j) {
                    if (is_vowel(s[j])) { v = s[j]; break; }
                }
                s.insert(start + 1, 1, v);
            }
        }
        // Jump to next space to only affect the word onset
        while (start < s.size() && !std::isspace(static_cast<unsigned char>(s[start]))) start++;
    }
}

inline void handle_diphthongs(std::string& s, bool expand) {
    std::string out;
    out.reserve(s.size());

    for (size_t i = 0; i < s.size(); ++i) {
        const char c = s[i];

        if (const char next = (i + 1 < s.size()) ? s[i+1] : '\0'; is_vowel(c) && is_vowel(next)) {
            if (expand) {
                out.push_back(c);
                if (c == 'i') out.push_back('y');
                else if (c == 'u' || c == 'o') out.push_back('w');
                // 'next' is handled in the next iteration
            } else {
                // Drop second vowel (Mindanao -> Mindana, India -> Indi)
                out.push_back(c);
                i++;
            }
        } else {
            out.push_back(c);
        }
    }
    s = std::move(out);
}


[[nodiscard]] inline std::string fast_normalizer(
    const std::string_view& input,
    const ForeignLanguage lang=ForeignLanguage::SPANISH,
    const LatinOrthography ortho=LatinOrthography::ABAKADA,
    const Diphthong dipht=Diphthong::REFORMED,
    const InitialCluster clusters=InitialCluster::REFORMED) {

    std::string s = foreign_normalizer(input, lang, ortho, dipht, clusters);
    return std::move(s);
}

} // namespace phil_norm
