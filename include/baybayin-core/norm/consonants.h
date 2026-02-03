#pragma once

#include <algorithm>
#include <array>
#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

using namespace phil_norm;

template<LatinOrthography TOrtho>
[[gnu::always_inline]] void
f_normalizer(std::string &output) {
    switch (TOrtho) {
    case LatinOrthography::ABAKADA:
        output.push_back('p');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('f');
        break;
    }
}

template<LatinOrthography TOrtho>
[[gnu::always_inline]] void
v_normalizer(std::string &output) {
    switch (TOrtho) {
    case LatinOrthography::ABAKADA:
        output.push_back('b');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('v');
        break;
    }
}

template<ForeignLanguage TLang, LatinOrthography TOrtho>
[[gnu::always_inline]] void
x_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (pos == 0 or std::isspace(input[pos - 1])) {
                // TODO: bug we need a word_boundary function that knows about punctuation
                output.push_back('s');
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and is_consonant(input[next])) {
                output.push_back('s');
                break;
            }
            output.append("ks");
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('x');
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (pos == 0 or std::isspace(input[pos - 1])) {
                // TODO: bug we need a word_boundary function that knows about punctuation
                output.push_back('s');
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and is_consonant(input[next])) {
                output.push_back('s');
                break;
            }
            output.append("ks");
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('x');
            break;
        }
        break;
    }
}

template<LatinOrthography TOrtho>
[[gnu::always_inline]] void
z_normalizer(std::string &output) {
    switch (TOrtho) {
    case LatinOrthography::ABAKADA:
        output.push_back('s');
        break;
    case LatinOrthography::ALPABETONG:
        output.push_back('z');
        break;
    }
}

template<ForeignLanguage Tlang, LatinOrthography TOrtho>
[[gnu::always_inline]] size_t
ll_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (Tlang) {
    case ForeignLanguage::ENGLISH:
        output.push_back('l');
        break;
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1;
                next < input.size()) {
                if (input[next] == 'l') {
                    output.push_back('y');
                    count++;
                    break;
                }
                output.push_back('l');
                break;
            }
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('l');
            break;
        }
        break;
    }
    return count;
}

template<ForeignLanguage Tlang, LatinOrthography TOrtho>
[[gnu::always_inline]] size_t
ph_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (Tlang) {
    case ForeignLanguage::SPANISH:
        output.push_back('p'); // ph doesn't occur in spanish
        break;
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1;
                next < input.size() and input[next] == 'h') {
                output.push_back('p');
                count++;
                break;
            }
            output.push_back('p');
            break;
        case LatinOrthography::ALPABETONG:
            if (const auto next = pos + 1;
                next < input.size() and input[next] == 'h') {
                output.push_back('f');
                count++;
                break;
            }
            output.push_back('p');
            break;
        }
        break;
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography TOrtho>
[[gnu::always_inline]] size_t
c_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    if constexpr (TLang == ForeignLanguage::ENGLISH and TOrtho == LatinOrthography::ABAKADA) {
    }
    // TODO: this might be the best place to handle double vowels since we know its not a Philippine word
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (auto next = pos + 1;
                next < input.size()) {
                if (input[next] == 'h') {
                    if (++next;
                        next < input.size() && not is_vowel(input[next])) {
                        output.push_back('k');
                        count++;
                    } else {
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
                if (std::array hard_vowels = {'a', 'o', 'u'};
                    std::ranges::count(hard_vowels.begin(), hard_vowels.end(), input[next]) or not
                    is_vowel(input[next])) {
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
        switch (TOrtho) {
        case LatinOrthography::ABAKADA: {
            auto next = pos + 1;
            if (input[next] == 'h') {
                if (++next;
                    next < input.size() && not is_vowel(input[next])) {
                    output.push_back('k');
                    count++;
                } else {
                    output.append("ts");
                    count++;
                }
                break;
            }
            if (std::array hard_vowels = {'a', 'o', 'u'};
                std::ranges::count(hard_vowels.begin(), hard_vowels.end(), input[next])) {
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

template<ForeignLanguage TLang, LatinOrthography TOrtho>
[[gnu::always_inline]] void
j_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    // TODO: this is not done, j at the end in spanish, etc.
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            output.append("dy");
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('j');
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
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

template<ForeignLanguage TLang, LatinOrthography TOrtho>
[[gnu::always_inline]] size_t
q_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1;
                next < input.size()) {
                if (input[next] == 'u') {
                    output.append("kw");
                    count++;
                } else {
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
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const auto next = pos + 1;
                next < input.size()) {
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

template<ForeignLanguage TLang, LatinOrthography TOrtho>
[[gnu::always_inline]] void
consonant_normalize(const std::string_view &input, std::string &output) {
    output.reserve(input.size());
    bool in_whitespace = false;
    for (size_t i = 0; i < input.size(); i++) {
        // FIXME: we are looking ahead down in the code and those haven't been to-lowered yet
        const char c = input[i] >= 'A' && input[i] <= 'Z' ? input[i] | static_cast<char>(0x20) : input[i];
        if (std::isspace(c)) {
            if (!output.empty() && !in_whitespace) {
                output.push_back(' ');
                in_whitespace = true;
            }
            continue;
        }
        in_whitespace = false;
        // FIXME: we need a word boundary function and replace all checks for ' ' or isspace()
        if (output.empty() || output.back() == ' ') { // Expansion: mga/ng
            if (c == 'm' && (i + 2 < input.size()) && (input[i + 1] | 0x20) == 'g' && (input[i + 2] | 0x20) == 'a') {
                if (const size_t next = i + 3;
                    next == input.size() || std::isspace(static_cast<unsigned char>(input[next]))) {
                    output.append("manga");
                    i += 2;
                    continue;
                }
            }
            if (c == 'n' && (i + 1 < input.size()) && (input[i + 1] | 0x20) == 'g') {
                if (const size_t next = i + 2;
                    next == input.size() || std::isspace(static_cast<unsigned char>(input[next]))) {
                    output.append("nang");
                    i += 1;
                    continue;
                }
            }
        }
        switch (c) {
        case 'f':
            f_normalizer<TOrtho>(output);
            continue;
        case 'v':
            v_normalizer<TOrtho>(output);
            continue;
        case 'z':
            z_normalizer<TOrtho>(output);
            continue;
        case 'x':
            x_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case 'c':
            i += c_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case 'j':
            j_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case 'q':
            i += q_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case 'l':
            i += ll_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case 'p':
            i += ph_normalizer<TLang, TOrtho>(input, i, output);
            continue;
        case static_cast<char>(0xC3): // handle spanish or modern filipino ñ, Ñ
            // TODO: make this a templated function for orthography
            if (const auto next = i + 1;
                next < input.size()) {
                if (input[next] == static_cast<char>(0xB1) || input[next] == static_cast<char>(0x91)) {
                    output.append("ny");
                    i++;
                }
            }
            continue;
        default:
            output.push_back(c);
        }
    }
    if (!output.empty() && output.back() == ' ')
        output.pop_back();
}

/**
 * @name consonant_normalize_dispatch
 * @brief Calls the appropriate templated function for consonant_normalize based on the runtime parameters provided.
 * @param input Input string
 * @param output Empty output string
 * @param lang Input language
 * @param ortho Output orthography
 */
inline void
consonant_normalize_dispatch(const std::string_view &input, std::string &output, const ForeignLanguage lang,
                             const LatinOrthography ortho
) {
    // TODO: we need to do diphthongs / clusters in a seconds or maybe third pass. best to have the logic separated
    // we can trigger on foreign word indicators to know how to treat the vowels
    switch (lang) {
    case ForeignLanguage::ENGLISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            consonant_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ABAKADA>(input, output);
            break;
        case LatinOrthography::ALPABETONG:
            consonant_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ALPABETONG>(input, output);
            break;
        }
        break;
    case ForeignLanguage::SPANISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            consonant_normalize<ForeignLanguage::SPANISH, LatinOrthography::ABAKADA>(input, output);
            break;
        case LatinOrthography::ALPABETONG:
            consonant_normalize<ForeignLanguage::SPANISH, LatinOrthography::ALPABETONG>(input, output);
            break;
        }
        break;
    }
}
