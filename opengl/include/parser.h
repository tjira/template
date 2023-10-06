#pragma once

#include <argparse/argparse.hpp>

class Parser {
public:
    // constructor
    Parser(int argc, char** argv);

private:
    argparse::ArgumentParser program;
};
