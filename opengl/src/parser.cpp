#include "parser.h"

Parser::Parser(int argc, char** argv) : program("template-opengl", "1.0", argparse::default_arguments::none) {
    // add options to the parser
    program.add_argument("-h").help("Display this help message and exit.").default_value(false).implicit_value(true);

    // extract the variables from the command line
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl << std::endl << program; exit(EXIT_FAILURE);
    }

    // print help if the help flag was provided
    if (program.get<bool>("-h")) {
        std::cout << program.help().str(); exit(EXIT_SUCCESS);
    }
}
