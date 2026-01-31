#pragma once

#include <array>
#include <string>

struct TranslateTestCase {
    std::string_view latin;
    std::string_view baybayin;
};

// Traditional is also known as B17 (Baybayin 17) since there are 17 characters,
// three vowels and 14 consonants.
static constexpr std::array SyllablesTraditional = std::to_array<TranslateTestCase>({
    {"ba", "ᜊ"},{"be", "ᜊᜒ"},{"bi", "ᜊᜒ"},{"bo", "ᜊᜓ"},{"bu", "ᜊᜓ"},
    {"ka", "ᜃ"},{"ke", "ᜃᜒ"},{"ki", "ᜃᜒ"},{"ko", "ᜃᜓ"},{"ku", "ᜃᜓ"},
    {"ga", "ᜄ"},{"ge", "ᜄᜒ"},{"gi", "ᜄᜒ"},{"go", "ᜄᜓ"},{"gu", "ᜄᜓ"},
    // d and r are allophones of the same phoneme
    {"ra", "ᜇ"},{"re", "ᜇᜒ"},{"ri", "ᜇᜒ"},{"ro", "ᜇᜓ"},{"ru", "ᜇᜓ"},
    {"da", "ᜇ"},{"de", "ᜇᜒ"},{"di", "ᜇᜒ"},{"do", "ᜇᜓ"},{"du", "ᜇᜓ"},
    {"ha", "ᜑ"},{"he", "ᜑᜒ"},{"hi", "ᜑᜒ"},{"ho", "ᜑᜓ"},{"hu", "ᜑᜓ"},
    {"la", "ᜎ"},{"le", "ᜎᜒ"},{"li", "ᜎᜒ"},{"lo", "ᜎᜓ"},{"lu", "ᜎᜓ"},
    {"ma", "ᜋ"},{"me", "ᜋᜒ"},{"mi", "ᜋᜒ"},{"mo", "ᜋᜓ"},{"mu", "ᜋᜓ"},
    {"na", "ᜈ"},{"ne", "ᜈᜒ"},{"ni", "ᜈᜒ"},{"no", "ᜈᜓ"},{"nu", "ᜈᜓ"},
    {"nga", "ᜅ"},{"nge", "ᜅᜒ"},{"ngi", "ᜅᜒ"},{"ngo", "ᜅᜓ"},{"ngu", "ᜅᜓ"},
    {"pa", "ᜉ"},{"pe", "ᜉᜒ"},{"pi", "ᜉᜒ"},{"po", "ᜉᜓ"},{"pu", "ᜉᜓ"},
    {"sa", "ᜐ"},{"se", "ᜐᜒ"},{"si", "ᜐᜒ"},{"so", "ᜐᜓ"},{"su", "ᜐᜓ"},
    {"ta", "ᜆ"},{"te", "ᜆᜒ"},{"ti", "ᜆᜒ"},{"to", "ᜆᜓ"},{"tu", "ᜆᜓ"},
    {"wa", "ᜏ"},{"we", "ᜏᜒ"},{"wi", "ᜏᜒ"},{"wo", "ᜏᜓ"},{"wu", "ᜏᜓ"},
    {"ya", "ᜌ"},{"ye", "ᜌᜒ"},{"yi", "ᜌᜒ"},{"yo", "ᜌᜓ"},{"yu", "ᜌᜓ"},

    // lone vowels
    {"a", "ᜀ"},
    {"e", "ᜁ"}, // e/i are allophones
    {"i", "ᜁ"},
    {"o", "ᜂ"},  // o/u are allophones
    {"u", "ᜂ"},
});

// Reformed is also known as B17+ for the addition of the vowel-"killing" krus
static constexpr std::array SyllablesReformed = std::to_array<TranslateTestCase>({
    {"b", "ᜊ᜔"},{"k", "ᜃ᜔"},{"g", "ᜄ᜔"},{"d", "ᜇ᜔"},{"h", "ᜑ᜔"},{"l", "ᜎ᜔"},
    {"m", "ᜋ᜔"},{"n", "ᜈ᜔"},{"ng", "ᜅ᜔"},{"p", "ᜉ᜔"},
    {"s", "ᜐ᜔"},{"t", "ᜆ᜔"},{"w", "ᜏ᜔"},{"y", "ᜌ᜔"}
});

/*static constexpr std::array SyllablesModern = std::to_array<TranslateTestCase>({
    {"ra", "ᜍ"},{"re", "ᜍᜒ"},{"ri", "ᜍᜒ"},{"ro", "ᜍᜓ"},{"ru", "ᜍᜓ"},{"r", "ᜍ᜔"},
});*/

struct Translation {
    std::string_view latin;
    std::string_view traditional;
    std::string_view reformed;
};

constexpr std::array TestVocabulary = std::to_array<Translation>({
    {"baybayin", "ᜊᜊᜌᜒ", "ᜊᜌ᜔ᜊᜌᜒᜈ᜔"},
    {"basa", "ᜊᜐ", "ᜊᜐ"},
    {"basag", "ᜊᜐ", "ᜊᜐᜄ᜔"},
    {"bansa", "ᜊᜐ", "ᜊᜈ᜔ᜐ"},
    {"bagsak", "ᜊᜐ", "ᜊᜄ᜔ᜐᜃ᜔"},
    {"pagmamahal", "ᜉᜋᜋᜑ", "ᜉᜄ᜔ᜋᜋᜑᜎ᜔"},
    {"bahay", "ᜊᜑ", "ᜊᜑᜌ᜔"},
    {"kulog", "ᜃᜓᜎᜓ", "ᜃᜓᜎᜓᜄ᜔"},
    {"akin", "ᜀᜃᜒ", "ᜀᜃᜒᜈ᜔"},
    {"paano", "ᜉᜀᜈᜓ", "ᜉᜀᜈᜓ"},
    {"kabuuan", "ᜃᜊᜓᜂᜀ", "ᜃᜊᜓᜂᜀᜈ᜔"},
    {"naiwan", "ᜈᜁᜏ", "ᜈᜁᜏᜈ᜔"},
    {"opo", "ᜂᜉᜓ", "ᜂᜉᜓ"},
    {"nang", "ᜈ", "ᜈᜅ᜔"},
    {"manga", "ᜋᜅ","ᜋᜅ"}

    // Initial consonant clusters
    //{"plano", "ᜉᜒᜎᜈᜓ", "ᜉ᜔ᜎ 1q2ᜈᜓ"}
});

constexpr TranslateTestCase TranslationTraditional (const Translation& l) {
    return { l.latin, l.traditional };
};

constexpr TranslateTestCase TranslationReformed(const Translation& l) {
    return { l.latin, l.reformed };
}

template<size_t N, typename Mapper>
constexpr auto extractTestCases(const std::array<Translation, N>& source, Mapper mapper) {
    using TargetType = decltype(mapper(source[0]));
    std::array<TargetType, N> out{};
    std::transform(source.begin(), source.end(), out.begin(), mapper);
    return out;
}

static constexpr auto VocabularyTraditional = extractTestCases(TestVocabulary, TranslationTraditional);
static constexpr auto VocabularyReformed = extractTestCases(TestVocabulary, TranslationReformed);
