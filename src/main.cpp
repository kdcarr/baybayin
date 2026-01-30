#include <iostream>
#include <filesystem>
#include <CLI/CLI.hpp>
#include <baybayin.h>

int transliterate(std::istream& istream, const baybayin::Orthography& ortho) {
    std::string line;
    while (std::getline(istream, line)) {
        std::cout << baybayin::latin_to_baybayin(line, ortho) << std::endl;
    }
    if (istream.bad()) {
        std::cerr << "Error reading stdin: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    CLI::App app{"\nA phonetic transliteration tool that converts from Latin to Baybayin", "bbn"};
    app.option_defaults()->always_capture_default();

    std::filesystem::path input_param;
    app.add_option("input", input_param, "Input file or '-' to read from stdin")
        ->required()
        ->check(CLI::ExistingFile | CLI::IsMember({"-"}));

    std::string_view ortho_param = "reformed";
    app.add_option("--ortho", ortho_param, "Preferred orthography")
        ->check(CLI::IsMember({"traditional", "reformed"}))
        ->type_name("");

    std::filesystem::path output_param;
    app.add_option("--output", output_param, "Output file");
    CLI11_PARSE(app, argc, argv);

    baybayin::Orthography ortho = baybayin::Orthography::Traditional;
    if (ortho_param == "reformed") {
        ortho = baybayin::Orthography::Reformed;
    }

    if (input_param.compare("-") == 0) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return transliterate(std::cin, ortho);
    }
    std::ifstream in_file(input_param);
    if (!in_file) {
        std::cerr << "Error: could not open input file " << input_param << " " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }


    return transliterate(in_file, ortho);
}