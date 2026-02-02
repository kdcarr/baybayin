#pragma once

#include <baybayin-core/norm/consonants.h>
#include <baybayin-core/util/util.h>
#include <string>
#include <string_view>

namespace phil_norm {

inline std::string
normalizer(const std::string_view &input, const ForeignLanguage lang, const LatinOrthography ortho,
           const Diphthong diphthong, const InitialCluster clusters
) {
    std::string output;
    consonant_normalize_dispatch(input, output, lang, ortho);
    // TODO: we may want to convert digits to the phonetic spellings
    return std::move(output);
}
}
