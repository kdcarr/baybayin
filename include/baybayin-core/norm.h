#pragma once

#include <baybayin-core/norm/consonants.h>
#include <baybayin-core/norm/vowels.h>
#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

namespace phil_norm {

inline std::string
normalizer(const std::string_view &input, const ForeignLanguage lang, const LatinOrthography ortho,
           const Diphthong diphthong, const InitialCluster clusters
) {
    std::string firstPass, secondPass;
    consonant_normalize_dispatch(input, firstPass, lang, ortho);
    vowel_normalize_dispatch(firstPass, secondPass, lang, ortho, diphthong);
    // TODO: as an option, we may want to convert digits to the phonetic spellings
    return std::move(secondPass);
}
}
