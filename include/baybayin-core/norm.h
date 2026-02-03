#pragma once

#include <baybayin-core/norm/consonants.h>
#include <baybayin-core/norm/vowels.h>
#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

namespace phil_norm {

inline std::string
normalizer(const std::string_view &input, const ForeignLanguage language, const LatinOrthography orthography,
           const Diphthong diphthongs, const InitialCluster clusters
) {
    std::string firstPass, secondPass;
    consonant_normalize_dispatch(input, firstPass, language, orthography);
    vowel_normalize_dispatch(firstPass, secondPass, language, orthography, diphthongs);
    if (clusters == InitialCluster::TRADITIONAL) {
        // TODO: smooth consonant cluster first-syllables with an extra vowel
    }
    return std::move(secondPass);
}
}
