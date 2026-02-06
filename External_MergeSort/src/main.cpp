#include "common.h"
#include "generator.h"
#include "split_sort.h"
#include "merge.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        if (argc == 4 && std::string(argv[1]) == "--generate") {
            generateFile(argv[2], std::stoull(argv[3]));
            return 0;
        }

        if (argc < 3) {
            std::cerr << "Usage:\n";
            std::cerr << "  external_sort <input_file> <output_file>\n";
            std::cerr << "  external_sort --generate <file> <size_bytes>\n";
            return 1;
        }

        size_t chunks = split_and_sort(argv[1]);
        merge_files(chunks, argv[2]);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
