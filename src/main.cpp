#include <iostream>
#include <filesystem>
#include <CLI/CLI.hpp>
#include <baybayin.h>

int transliterate(std::istream& istream) {
    std::string line;
    while (std::getline(istream, line)) {
        std::cout << baybayin::latin_to_baybayin(line) << std::endl;
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

    std::filesystem::path input;
    app.add_option("input", input, "Input file or '-' to read from stdin");

    std::string_view ortho = "reformed";
    app.add_option("--ortho", ortho, "Set the preferred orthography")
        ->check(CLI::IsMember({"traditional", "reformed"}))
        ->type_name("");

    std::filesystem::path output;
    app.add_option("--output", output, "Output text file UTF8");
    CLI11_PARSE(app, argc, argv);

    if (input.compare("-") == 0) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return transliterate(std::cin);
    }
    std::ifstream in_file(input);
    if (!in_file) {
        std::cerr << "Error: could not open input file " << input << " " << std::strerror(errno) << std::endl;
    }
    return transliterate(in_file);
}