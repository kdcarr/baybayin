#include <iostream>
#include <filesystem>
#include <CLI/CLI.hpp>
#include <baybayin-core/tl.h>
#include "include/utils.h"

using namespace baybayin;

int transliterate(std::istream &istream, std::ostream &ostream, const Orthography &ortho) {
    std::string line;
    while (std::getline(istream, line)) {
        ostream << latin_to_baybayin(line, ortho) << std::endl;
        if (ostream.bad()) {
            std::cerr << "Error writing output: " << std::strerror(errno) << std::endl;
            return EXIT_FAILURE;
        }
    }
    if (istream.bad()) {
        std::cerr << "Error reading input: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(const int argc, char **argv) {
    CLI::App app{
    "\nA fast and deterministic phonetic transliteration tool that converts normalized "
    "latin alphabet to baybayin abugita.",
    "tl"};
    app.option_defaults()->always_capture_default();

    std::filesystem::path input_param;
    app.add_option("--input", input_param, "Input file or '-' to read from stdin")->check(CLI::ExistingFile);

    std::filesystem::path output_param;
    app.add_option("--output", output_param, "Output file, otherwise stdout");

    const char *REFORMED = {"reformed"};
    std::string_view ortho_param = REFORMED;
    app.add_option("--orthography", ortho_param)->check(CLI::IsMember({"traditional", REFORMED}));

    CLI11_PARSE(app, argc, argv);

    const auto ortho = ortho_param == REFORMED ? Orthography::Reformed : Orthography::Traditional;

    if (const auto istream = get_input_stream(input_param); istream->good()) {
        if (const auto ostream = get_output_stream(output_param); ostream->good()) {
            return transliterate(*istream, *ostream, ortho);
        }
        std::cerr << "failed to write output: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "failed to read input: " << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
}
