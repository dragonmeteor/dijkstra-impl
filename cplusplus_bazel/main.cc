#include <iostream>
#include "graph.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Usage: main.exe [input-file-name] [output-file-name]" << std::endl;
        return 0;
    }

    std::string input_file_name = argv[1];
    std::cout << "Input file: " << input_file_name << std::endl;
    return 0;
}