#include <gtest/gtest.h>
#include <baybayin-core/norm.h>

TEST(norm, norm) {
    std::string str("christ coche cinema can chance");
    std::string result = phil_norm::fast_normalizer(str,
        phil_norm::ForeignLanguage::ENGLISH,
        phil_norm::LatinOrthography::ABAKADA,
        phil_norm::Diphthong::REFORMED,
        phil_norm::InitialCluster::REFORMED);
    // TODO: remove this when ready to automate tests
    std::cout << result << std::endl;
}