#pragma once

#include <argparse/argparse.hpp>

class Parser {
public:
    // constructor
    Parser(int argc, char** argv);

    // getters
    template <typename T> T get(const std::string& key) {return program.get<T>(key);}
    bool has(const std::string& key) {return program.is_used(key);}

private:
    argparse::ArgumentParser program;
};
