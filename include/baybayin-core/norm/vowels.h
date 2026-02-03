#pragma once

#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

using namespace phil_norm;

template<ForeignLanguage TLang, LatinOrthography TOrtho> // TODO: templated for diphthong?
[[gnu::always_inline]] size_t
a_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            output.push_back('a');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('a');
            break;
        }
        break;
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const size_t next = pos + 1;
                next < input.size() and std::ranges::count(std::to_array({'i', 'y'}), input[next])) {
                output.append("ey");
                count++;
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and std::ranges::count(std::to_array({'u', 'w'}), input[next])) {
                output.push_back('o');
                count++;
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and std::ranges::count(std::to_array({'e'}), input[next])) {
                output.push_back('o');
                count++;
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and is_consonant(input[next]) and next + 1 < input.size() and input[next + 1] ==
                'e') {
                output.append("ey");
                break;
            }
            output.push_back('a');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('a');
            break;
        }
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography TOrtho> // TODO: templated for diphthong?
[[gnu::always_inline]] size_t
o_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            output.push_back('o');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('o');
            break;
        }
        break;
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const size_t next = pos + 1;
                next < input.size() and std::ranges::count(std::to_array({'a'}), input[next])) {
                output.push_back('o');
                count++;
                break;
            }
            output.push_back('o');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('o');
            break;
        }
    }
    return count;
}

template<ForeignLanguage TLang, LatinOrthography TOrtho> // TODO: templated for diphthong?
[[gnu::always_inline]] size_t
e_normalizer(const std::string_view &input, const size_t pos, std::string &output) {
    size_t count = 0;
    switch (TLang) {
    case ForeignLanguage::SPANISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            output.push_back('e');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('e');
            break;
        }
        break;
    case ForeignLanguage::ENGLISH:
        switch (TOrtho) {
        case LatinOrthography::ABAKADA:
            if (const size_t next = pos + 1; // todo: make this use a boundary function for words
                next == input.size() or std::isspace(input[next])) {
                break;
            }
            if (const size_t next = pos + 1;
                next < input.size() and input[next] == 'e') {
                output.push_back('i');
                count++;
                break;
            }
            output.push_back('e');
            break;
        case LatinOrthography::ALPABETONG:
            output.push_back('e');
            break;
        }
        break;
    }
    return count;
}

/**
 * @name vowel_normalize
 * @brief
 * @tparam TLang
 * @tparam TOrtho
 * @tparam TDipht
 * @param input
 * @param output
 */
template<ForeignLanguage TLang, LatinOrthography TOrtho, Diphthong TDipht>
[[gnu::always_inline]] void
vowel_normalize(const std::string_view &input, std::string &output) {
    output.reserve(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        switch (const char c = input[i]) {
        case 'a':
            i += a_normalizer<TLang, TOrtho>(input, i, output);
            break;
        case 'e':
            i += e_normalizer<TLang, TOrtho>(input, i, output);
            break;
        case 'i':
            output.push_back('i');
            break;
        case 'o':
            i += o_normalizer<TLang, TOrtho>(input, i, output);
            break;
        case 'u':
            output.push_back('u');
            break;
        case 'y': default:
            output.push_back(c);
            break;
        }
    }
}

inline void
vowel_normalize_dispatch(const std::string_view &input, std::string &output, const ForeignLanguage lang,
                         const LatinOrthography ortho, const Diphthong dipht
) {
    switch (lang) {
    case ForeignLanguage::SPANISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            switch (dipht) {
            case Diphthong::TRADITIONAL:
                vowel_normalize<ForeignLanguage::SPANISH, LatinOrthography::ABAKADA, Diphthong::TRADITIONAL>(
                input, output);
                break;
            case Diphthong::REFORMED:
                vowel_normalize<ForeignLanguage::SPANISH, LatinOrthography::ABAKADA,
                                Diphthong::REFORMED>(input, output);
                break;
            }
            break;
        case LatinOrthography::ALPABETONG:
            switch (dipht) {
            case Diphthong::TRADITIONAL:
                vowel_normalize<ForeignLanguage::SPANISH, LatinOrthography::ALPABETONG, Diphthong::TRADITIONAL>(
                input, output);
                break;
            case Diphthong::REFORMED:
                vowel_normalize<ForeignLanguage::SPANISH, LatinOrthography::ALPABETONG, Diphthong::REFORMED>(
                input, output);
                break;
            }
            break;
        }
        break;
    case ForeignLanguage::ENGLISH:
        switch (ortho) {
        case LatinOrthography::ABAKADA:
            switch (dipht) {
            case Diphthong::TRADITIONAL:
                vowel_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ABAKADA, Diphthong::TRADITIONAL>(
                input, output);
                break;
            case Diphthong::REFORMED:
                vowel_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ABAKADA,
                                Diphthong::REFORMED>(input, output);
                break;
            }
            break;
        case LatinOrthography::ALPABETONG:
            switch (dipht) {
            case Diphthong::TRADITIONAL:
                vowel_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ALPABETONG, Diphthong::TRADITIONAL>(
                input, output);
                break;
            case Diphthong::REFORMED:
                vowel_normalize<ForeignLanguage::ENGLISH, LatinOrthography::ALPABETONG, Diphthong::REFORMED>(
                input, output);
                break;
            }
            break;
        }
    }
}
