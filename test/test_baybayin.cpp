#include <gtest/gtest.h>
#include <baybayin.h>

struct TranslateTestCase {
    std::string_view input;
    std::string_view expected;
};

class LatinToBaybayin : public ::testing::TestWithParam<TranslateTestCase> {};

TEST_P(LatinToBaybayin, latin_to_baybayin) {
    const auto& [input, expected] = GetParam();
    EXPECT_EQ(baybayin::latin_to_baybayin(input), expected)
        << "translation failed for input \"" << input << "\"";
};

/*
 * We test the following phonetics.
 *
 *      a	    i/e	    o/u	    final
 * -----------------------------------
 * b	bata	bisa	buto	bundok
 * k	kaba	kilat	kubo	katok
 * g	gabi	giliw	gulo	gandî
 * d	dama	dili	dulo	dikit
 * h	halo	hiling	hulo	hahad
 * l	lupa	lilim	luto	langit
 * m	mata	mili	mulo	malam
 * n	nara	nini	nuno	ngipin
 * ng	ngala	ngili	ngulo	ngipin
 * p	puno	pili	puso	pampal
 * r	rala	riri	ruro	araro
 * s	sapa	sili	suso	sakít
 * t	tula	titi	tulo	matut
 * w	walo	wini	wulo	buwan
 * y	yaya	yini	yulo	yayat
 */
INSTANTIATE_TEST_SUITE_P(
    LatinToBaybayin,
    LatinToBaybayin,
    testing::Values(
        TranslateTestCase{ "bata",   "ᜊᜆ" },
        TranslateTestCase{ "bisa",   "ᜊᜒᜐ" },
        TranslateTestCase{ "buto",   "ᜊᜓᜆᜓ" },
        TranslateTestCase{ "bundok", "ᜊᜓᜈ᜔ᜇᜓᜃ᜔" },
        TranslateTestCase{ "kaban",  "ᜃᜊᜈ᜔" },
        TranslateTestCase{ "kilat",  "ᜃᜒᜎᜆ᜔" },
        TranslateTestCase{ "kubo",   "ᜃᜓᜊᜓ" },
        TranslateTestCase{ "katok",  "ᜃᜆᜓᜃ᜔" },
        TranslateTestCase{ "gabi",   "ᜄᜊᜒ" },
        TranslateTestCase{ "giliw",  "ᜄᜒᜎᜒᜏ᜔" },
        TranslateTestCase{ "gulo",   "ᜄᜓᜎᜓ" },
        TranslateTestCase{ "gandî",  "ᜄᜈ᜔ᜇ᜔î"},
        TranslateTestCase{ "dama",   "ᜇᜋ" },
        TranslateTestCase{ "dili",   "ᜇᜒᜎᜒ" },
        TranslateTestCase{ "dulo",   "ᜇᜓᜎᜓ" },
        TranslateTestCase{ "dikit",  "ᜇᜒᜃᜒᜆ᜔" },
        TranslateTestCase{ "halo",   "ᜑᜎᜓ" },
        TranslateTestCase{ "hiling", "ᜑᜒᜎᜒᜅ᜔" },
        TranslateTestCase{ "hilab",  "ᜑᜒᜎᜊ᜔" },
        TranslateTestCase{ "hulo",   "ᜑᜓᜎᜓ" },
        TranslateTestCase{ "hahad",  "ᜑᜑᜇ᜔" },
        TranslateTestCase{ "lupa",   "ᜎᜓᜉ" },
        TranslateTestCase{ "lilim",  "ᜎᜒᜎᜒᜋ᜔" },
        TranslateTestCase{ "lilib",  "ᜎᜒᜎᜒᜊ᜔" },
        TranslateTestCase{ "luto",   "ᜎᜓᜆᜓ" },
        TranslateTestCase{ "langit", "ᜎᜅᜒᜆ᜔" },
        TranslateTestCase{ "mata",   "ᜋᜆ" },
        TranslateTestCase{ "mili",   "ᜋᜒᜎᜒ" },
        TranslateTestCase{ "mulo",   "ᜋᜓᜎᜓ" },
        TranslateTestCase{ "malam",  "ᜋᜎᜋ᜔" },
        TranslateTestCase{ "nara",   "ᜈᜇ" },
        TranslateTestCase{ "nini",   "ᜈᜒᜈᜒ" },
        TranslateTestCase{ "nuno",   "ᜈᜓᜈᜓ" },
        TranslateTestCase{ "ngipin", "ᜅᜒᜉᜒᜈ᜔" },
        TranslateTestCase{ "ngala",  "ᜅᜎ" },
        TranslateTestCase{ "ngili",  "ᜅᜒᜎᜒ" },
        TranslateTestCase{ "ngulo",  "ᜅᜓᜎᜓ" },
        TranslateTestCase{ "puno",   "ᜉᜓᜈᜓ" },
        TranslateTestCase{ "pili",   "ᜉᜒᜎᜒ" },
        TranslateTestCase{ "puso",   "ᜉᜓᜐᜓ" },
        TranslateTestCase{ "pampal", "ᜉᜋ᜔ᜉᜎ᜔" },
        TranslateTestCase{ "palad",  "ᜉᜎᜇ᜔" },
        TranslateTestCase{ "rala",   "ᜇᜎ" },
        TranslateTestCase{ "riri",   "ᜇᜒᜇᜒ" },
        TranslateTestCase{ "ruro",   "ᜇᜓᜇᜓ"},
        TranslateTestCase{ "araro",  "ᜀᜇᜇᜓ" },
        TranslateTestCase{ "sapa",   "ᜐᜉ" },
        TranslateTestCase{ "sili",   "ᜐᜒᜎᜒ" },
        TranslateTestCase{ "suso",   "ᜐᜓᜐᜓ" },
        TranslateTestCase{ "sakít",  "ᜐᜃ᜔íᜆ᜔" },
        TranslateTestCase{ "sakit",  "ᜐᜃᜒᜆ᜔" },
        TranslateTestCase{ "tula",   "ᜆᜓᜎ" },
        TranslateTestCase{ "titi",   "ᜆᜒᜆᜒ" },
        TranslateTestCase{ "tulo",   "ᜆᜓᜎᜓ" },
        TranslateTestCase{ "matut",  "ᜋᜆᜓᜆ᜔" },
        TranslateTestCase{ "tatak",  "ᜆᜆᜃ᜔" },
        TranslateTestCase{ "walo",   "ᜏᜎᜓ" },
        TranslateTestCase{ "wini",   "ᜏᜒᜈᜒ" },
        TranslateTestCase{ "wulo",   "ᜏᜓᜎᜓ" },
        TranslateTestCase{ "buwan",  "ᜊᜓᜏᜈ᜔" },
        TranslateTestCase{ "yaya",   "ᜌᜌ" },
        TranslateTestCase{ "yini",   "ᜌᜒᜈᜒ" },
        TranslateTestCase{ "yulo",   "ᜌᜓᜎᜓ" },
        TranslateTestCase{ "yayat",  "ᜌᜌᜆ᜔" }
        )
    );