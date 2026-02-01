#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

/*class worker_base {
    std::unique_ptr<std::istream, void(*)(std::istream*)> input;
    std::unique_ptr<std::ostream, void(*)(std::ostream*)> output;

    static std::unique_ptr<std::ostream, void(*)(std::ostream*)> get_output_stream(const std::filesystem::path& fn) {
        if (fn.empty()) {
            std::ios_base::sync_with_stdio(false);
            return { &std::cout, [](std::ostream*) {
                // do not try to delete cout
            } };
        }
        return { new std::ofstream(fn), [](std::ostream* p) {
            delete p;
        } };
    }
    static std::unique_ptr<std::istream, void(*)(std::istream*)> get_input_stream(const std::filesystem::path& fn) {
        if (fn.empty()) {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return { &std::cin, [](std::istream*) {
                // do not try to delete cin
            } };
        }
        return { new std::ifstream(fn), [](std::istream* p) {
            delete p;
        } };
    }
    public:
    worker_base(const std::filesystem::path& ifn, const std::filesystem::path& ofn)
    : input(get_input_stream(ifn)), output(get_output_stream(ofn)) { }

    worker_base(const worker_base&) = delete;
    worker_base& operator=(const worker_base&) = delete;
};*/

inline std::unique_ptr<std::ostream, void(*)(std::ostream*)> get_output_stream(const std::filesystem::path& fn) {
    if (fn.empty()) {
        std::ios_base::sync_with_stdio(false);
        return { &std::cout, [](std::ostream*) {
            // do not try to delete cout
        } };
    }
    return { new std::ofstream(fn), [](std::ostream* p) {
        delete p;
    } };
}

inline std::unique_ptr<std::istream, void(*)(std::istream*)> get_input_stream(const std::filesystem::path& fn) {
    if (fn.empty()) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return { &std::cin, [](std::istream*) {
            // do not try to delete cin
        } };
    }
    return { new std::ifstream(fn), [](std::istream* p) {
        delete p;
    } };
}