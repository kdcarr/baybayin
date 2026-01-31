#include <iostream>
#include <filesystem>
#include <CLI/CLI.hpp>
#include <baybayin-core/tl.h>
#include <baybayin-core/norm.h>
#include "include/utils.h"

using namespace baybayin;

int normalize(std::istream& istream, std::ostream& ostream, const Orthography& ortho) {
    std::string line;
    while (std::getline(istream, line)) {
        ostream << latin_to_phonetic_abakada(line) << std::endl;
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
                 "constraints of the Baybayin Abugida.", "norm"};
    app.option_defaults()->always_capture_default();

    std::filesystem::path input_param;
    app.add_option("input", input_param, "Input file or '-' to read from stdin")
        ->required()
        ->check(CLI::ExistingFile | CLI::IsMember({"-"}));

    const char* REFORMED={"reformed"};
    std::string_view ortho_param = REFORMED;
    app.add_option("--orthography", ortho_param)
        ->check(CLI::IsMember({"traditional", REFORMED}));

    std::filesystem::path output_param;
    app.add_option("--output", output_param, "Output file, otherwise stdout");
    CLI11_PARSE(app, argc, argv);

    const auto ortho = ortho_param == REFORMED ? Orthography::Reformed : Orthography::Traditional;

    if (const auto istream = get_input_stream(input_param); istream->good()) {
        if (const auto ostream = get_output_stream(output_param); ostream->good()) {
            return normalize(*istream, *ostream, ortho);
        }
        std::cerr << "failed to write output: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "failed to read input: " << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
}
