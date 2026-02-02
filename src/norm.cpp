#include <iostream>
#include <filesystem>
#include <CLI/CLI.hpp>
#include <baybayin-core/tl.h>
#include <baybayin-core/norm.h>
#include "include/utils.h"

using namespace baybayin;
using namespace phil_norm;

int normalize(
    std::istream& istream,
    std::ostream& ostream,
    const ForeignLanguage language,
    const LatinOrthography orthography,
    const Diphthong diphthongs,
    const InitialCluster clusters
    ) {
    std::string line;
    while (std::getline(istream, line)) {
        ostream << fast_normalize_dispatcher(line, language, orthography, diphthongs, clusters) << std::endl;
        // TODO: check if ostream is still good and exit with error otherwise
    }
    if (istream.bad()) {
        std::cerr << "Error reading stdin: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(const int argc, char** argv) {
    CLI::App app{"\nA fast and deterministic normalization tool for Latin text. "
                 "As a precursor to transliteration, it shapes the input to suit the phonotactic "
                 "constraints of the specified orthography.", "norm"};
    app.option_defaults()->always_capture_default();

    std::filesystem::path input_param;
    app.add_option("-i,--input", input_param, "Input file or '-' to read from stdin")
        ->check(CLI::ExistingFile);

    std::filesystem::path output_param;
    app.add_option("-o,--output", output_param, "Output file, otherwise stdout")
        ->check(CLI::ExistingFile);

    const char* ABAKADA={"abakada"};
    std::string_view ortho_param = ABAKADA;
    app.add_option("-O,--orthography", ortho_param)
        ->check(CLI::IsMember({ABAKADA, "alpabetong"}));

    const char* SPANISH={"spanish"};
    std::string_view lang_param = SPANISH;
    app.add_option("-l,--language", lang_param)
        ->check(CLI::IsMember({SPANISH, "english"}));

    const char* REFORMED={"reformed"};
    std::string_view diphthongs_param = REFORMED;
    app.add_option("-d,--diphthong", diphthongs_param)
        ->check(CLI::IsMember({REFORMED, "traditional"}));

    std::string_view clusters_param = REFORMED;
    app.add_option("-c,--clusters", clusters_param)
        ->check(CLI::IsMember({REFORMED, "traditional"}));

    CLI11_PARSE(app, argc, argv);
    const auto ortho = ortho_param == ABAKADA ? LatinOrthography::ABAKADA : LatinOrthography::ALPABETONG;
    const auto lang = lang_param == SPANISH ? ForeignLanguage::SPANISH : ForeignLanguage::ENGLISH;
    const auto diphthong = diphthongs_param == REFORMED ? Diphthong::REFORMED : Diphthong::TRADITIONAL;
    const auto clusters = clusters_param == REFORMED ? InitialCluster::REFORMED : InitialCluster::TRADITIONAL;

    if (const auto istream = get_input_stream(input_param); istream->good()) {
        if (const auto ostream = get_output_stream(output_param); ostream->good()) {
            return normalize(*istream, *ostream, lang, ortho, diphthong, clusters);
        }
        std::cerr << "failed to write output: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "failed to read input: " << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
}
