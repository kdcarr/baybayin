#pragma once

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
}

constexpr bool
is_vowel(const char c) noexcept {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

constexpr bool
is_consonant(const char c) noexcept {
    return (c >= 'a' && c <= 'z') && !is_vowel(c);
}
