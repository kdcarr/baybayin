#pragma once

#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

using namespace phil_norm;

template<ForeignLanguage TLang, LatinOrthography TOrtho, Diphthong TDipht>
[[gnu::always_inline]] void
vowel_normalize(const std::string_view &input, std::string &output) {
    output = input;
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
