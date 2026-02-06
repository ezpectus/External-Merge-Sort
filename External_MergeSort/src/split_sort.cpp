#include "split_sort.h"
#include "common.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

size_t split_and_sort(const std::string& inputFile) {
    std::ifstream in(inputFile);
    if (!in) {
        throw std::runtime_error("Cannot open input file");
    }

    std::vector<double> buffer;
    buffer.reserve(CHUNK_SIZE / sizeof(double));

    size_t chunkId = 0;
    double value;

    while (in >> value) {
        buffer.push_back(value);

        if (buffer.size() * sizeof(double) >= CHUNK_SIZE) {
            std::sort(buffer.begin(), buffer.end());

            std::ofstream out("chunk_" + std::to_string(chunkId++));
            for (double v : buffer) {
                out << std::scientific << std::setprecision(17) << v << '\n';
            }
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end());

        std::ofstream out("chunk_" + std::to_string(chunkId++));
        for (double v : buffer) {
            out << std::scientific << std::setprecision(17) << v << '\n';
        }
    }

    return chunkId;
}
