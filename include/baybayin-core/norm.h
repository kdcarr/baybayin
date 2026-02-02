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

template<LatinOrthography Tortho>
[[gnu::always_inline]] void f_normalizer(std::string &output) {
    switch (Tortho) {
    case LatinOrthography::ABAKADA:
        output.push_back('p');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('f');
        break;
    }
}

template<LatinOrthography Tortho>
[[gnu::always_inline]] void v_normalizer(std::string &output) {
    switch (Tortho) {
    case LatinOrthography::ABAKADA:
        output.push_back('b');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('v');
        break;
    }
}

template<LatinOrthography Tortho>
[[gnu::always_inline]] void x_normalizer(std::string &output) {
    switch (Tortho) {
    case LatinOrthography::ABAKADA:
        output.append("ks");
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('x');
        break;
    }
}

template<LatinOrthography Tortho>
[[gnu::always_inline]] void z_normalizer(std::string &output) {
    switch (Tortho) {
    case LatinOrthography::ABAKADA:
        output.push_back('s');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('z');
        break;
    }
}

template<ForeignLanguage Tlang, LatinOrthography Tortho>
[[gnu::always_inline]] size_t ll_normalizer(const std::string_view &input, size_t pos, std::string &output) {
    size_t count = 0;
    switch (Tlang) {
    case ForeignLanguage::ENGLISH:
        output.push_back('l');
        break;
    case ForeignLanguage::SPANISH:
        if (const auto next = pos + 1; next < input.size()) {
            if (input[next] == 'l') {
                output.push_back('y');
                count++;
            }
            else {
                output.push_back('k');
            }
            break;
        }
        break;
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography Tortho>
[[gnu::always_inline]] size_t c_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    if constexpr (TLang == ForeignLanguage::ENGLISH and Tortho == LatinOrthography::ABAKADA) {
    }
    // TODO: this might be the best place to handle double vowels since we know its not a Philippine word
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA:
            if (auto next = pos + 1; next < input.size()) {
                if (input[next] == 'h') {
                    if (++next; next < input.size() && not is_vowel(input[next])) {
                        output.push_back('k');
                        count++;
                    }
                    else {
                        output.append("ts");
                        count++;
                    }
                    break;
                }
                if (input[next] == 'k') {
                    output.push_back('k');
                    count++;
                    break;
                }
                if (std::array hard_vowels = {'a', 'o', 'u'}; std::ranges::count(hard_vowels.begin(), hard_vowels.end(),
                                                                  input[next]) or not is_vowel(input[next])) {
                    output.push_back('k');
                    break;
                }
                output.push_back('s');
                break;
            }
            output.push_back('k');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('c');
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA: {
            auto next = pos + 1;
            if (input[next] == 'h') {
                if (++next; next < input.size() && not is_vowel(input[next])) {
                    output.push_back('k');
                    count++;
                }
                else {
                    output.append("ts");
                    count++;
                }
                break;
            }
            if (std::array hard_vowels = {'a', 'o', 'u'}; std::ranges::count(hard_vowels.begin(), hard_vowels.end(),
                                                                             input[next])) {
                output.push_back('k');
                break;
            }
            output.push_back('s');
            break;
        }
        case LatinOrthography::ALPABETONG:
            output.push_back('c');
            break;
        }
        break;
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography Tortho>
[[gnu::always_inline]] void j_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    // TODO: this is not done, j at the end in spanish, etc.
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA:
            output.append("dy");
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('j');
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA:
            output.append("h");
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('j');
            break;
        }
        break;
    }
}

template<ForeignLanguage TLang, LatinOrthography Tortho>
[[gnu::always_inline]] size_t q_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1; next < input.size()) {
                if (input[next] == 'u') {
                    output.append("kw");
                    count++;
                }
                else {
                    output.push_back('k');
                }
                break;
            }
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('q');
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (Tortho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1; next < input.size()) {
                if (input[next] == 'u') {
                    count++;
                }
                output.push_back('k');
                break;
            }
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('q');
            break;
        }
        break;
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography Tortho>
void fast_normalizer(const std::string_view &input, std::string &output, Diphthong dipht, InitialCluster clusters) {
    bool in_whitespace = false;
    output.reserve(input.size());

    //#pragma clang loop interleave(enable)
    for (size_t i = 0; i < input.size(); ++i) {
        // TODO: bug we are looking ahead down in the code and those haven't been to-lowered yet
        const char c = input[i] >= 'A' && input[i] <= 'Z' ? input[i] | static_cast<char>(0x20) : input[i];
        if (std::isspace(c)) {
            if (!output.empty() && !in_whitespace) {
                output.push_back(' ');
                in_whitespace = true;
            }
            continue;
        }
        in_whitespace = false;

        // Expansion: mga/ng
        if (output.empty() || output.back() == ' ') {
            if (c == 'm' && (i + 2 < input.size()) && (input[i + 1] | 0x20) == 'g' && (input[i + 2] | 0x20) == 'a') {
                // TODO: this is a bug we need a word boundry test that understands punctuation as well
                if (const size_t next = i + 3; next == input.size() || std::isspace(
                                               static_cast<unsigned char>(input[next]))) {
                    output.append("manga");
                    i += 2;
                    continue;
                }
            }
            if (c == 'n' && (i + 1 < input.size()) && (input[i + 1] | 0x20) == 'g') {
                if (const size_t next = i + 2; next == input.size() || std::isspace(
                                               static_cast<unsigned char>(input[next]))) {
                    output.append("nang");
                    i += 1;
                    continue;
                }
            }
        }

        switch (c) {
        case 'f':
            f_normalizer<Tortho>(output);
            continue;
        case 'v':
            v_normalizer<Tortho>(output);
            continue;
        case 'z':
            z_normalizer<Tortho>(output);
            continue;
        case 'x':
            x_normalizer<Tortho>(output);
            continue;
        case 'c':
            i += c_normalizer<TLang, Tortho>(input, i, output);
            continue;
        case 'j':
            j_normalizer<TLang, Tortho>(input, i, output);
            continue;
        case 'q':
            i += q_normalizer<TLang, Tortho>(input, i, output);
            continue;
        case 'l':
            i += ll_normalizer<TLang, Tortho>(input, i, output);
            continue;

        // handle spanish or modern filipino ñ, Ñ
        case static_cast<char>(0xC3):
            if (const auto next = i + 1; next < input.size()) {
                if (input[next] == static_cast<char>(0xB1) || input[next] == static_cast<char>(0x91)) {
                    output.append("ny");
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
            output.push_back(c);
            continue;
        }
    }
    if (!output.empty() && output.back() == ' ')
        output.pop_back();
}

inline std::string fast_normalize_dispatcher(const std::string_view &input, const ForeignLanguage lang,
                                             const LatinOrthography ortho, const Diphthong diphthong,
                                             const InitialCluster clusters
) {

    // TODO: we need to do diphthongs / clusters in a seconds or maybe third pass. best to have the logic separated
    // we can trigger on foreign word indicators to know how to treat the vowels
    std::string output;
    switch (lang) {
    case ForeignLanguage::ENGLISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            fast_normalizer<ForeignLanguage::ENGLISH, LatinOrthography::ABAKADA>(input, output, diphthong, clusters);
            break;
        case LatinOrthography::ALPABETONG:
            fast_normalizer<ForeignLanguage::ENGLISH, LatinOrthography::ALPABETONG>(input, output, diphthong, clusters);
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            fast_normalizer<ForeignLanguage::SPANISH, LatinOrthography::ABAKADA>(input, output, diphthong, clusters);
            break;
        case LatinOrthography::ALPABETONG:
            fast_normalizer<ForeignLanguage::SPANISH, LatinOrthography::ALPABETONG>(input, output, diphthong, clusters);
            break;
        }
        break;
    }
    return std::move(output);
}
}
