#include <gtest/gtest.h>
#include <baybayin.h>
#include <algorithm>
#include <filesystem>
#include <map>
#include "unit_tests.h"

using namespace baybayin;

class LatinToBaybayinTraditional : public ::testing::TestWithParam<TranslateTestCase> {};

TEST_P(LatinToBaybayinTraditional, Traditional) {
    const auto& [latin, baybayin] = GetParam();
    EXPECT_EQ(latin_to_baybayin(latin, Orthography::Traditional), baybayin)
        << "translation failed for latin \"" << latin << "\"";
};

INSTANTIATE_TEST_SUITE_P(
    SyllablesTraditional,
    LatinToBaybayinTraditional,
    testing::ValuesIn(SyllablesTraditional)
    );

INSTANTIATE_TEST_SUITE_P(
    WordsTraditional,
    LatinToBaybayinTraditional,
    testing::ValuesIn(VocabularyTraditional)
    );

class LatinToBaybayinReformedKrus : public ::testing::TestWithParam<TranslateTestCase> {};

TEST_P(LatinToBaybayinReformedKrus, Reformed) {
    const auto& [latin, baybayin] = GetParam();
    EXPECT_EQ(latin_to_baybayin(latin, Orthography::Reformed), baybayin)
        << "translation failed for latin \"" << latin << "\"";
};

INSTANTIATE_TEST_SUITE_P(
    SylablesReformedKrus,
    LatinToBaybayinReformedKrus,
    []() {
        // aggregate the traditional and reformed syllables
        std::vector<TranslateTestCase> testCases(SyllablesTraditional.begin(), SyllablesTraditional.end());
        testCases.insert(testCases.end(), SyllablesReformed.begin(), SyllablesReformed.end());
        return testing::ValuesIn(testCases);
    }()
    );

INSTANTIATE_TEST_SUITE_P(
    WordsReformedKrus,
    LatinToBaybayinReformedKrus,
    testing::ValuesIn(VocabularyReformed)
    );