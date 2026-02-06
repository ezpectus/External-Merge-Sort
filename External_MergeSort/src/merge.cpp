#include "merge.h"

#include <queue>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cstdio>

struct Node {
    double value;
    size_t fileId;

    bool operator>(const Node& other) const {
        return value > other.value;
    }
};

void merge_files(size_t fileCount, const std::string& outputFile) {
    std::vector<std::ifstream> inputs(fileCount);

    for (size_t i = 0; i < fileCount; ++i) {
        inputs[i].open("chunk_" + std::to_string(i));
        if (!inputs[i]) {
            throw std::runtime_error("Cannot open chunk file");
        }
    }

    std::priority_queue<Node, std::vector<Node>, std::greater<>> heap;

    for (size_t i = 0; i < fileCount; ++i) {
        double x;
        if (inputs[i] >> x) {
            heap.push({ x, i });
        }
    }

    std::ofstream out(outputFile);
    if (!out) {
        throw std::runtime_error("Cannot open output file");
    }

    while (!heap.empty()) {
        Node n = heap.top();
        heap.pop();

        out << std::scientific << std::setprecision(17) << n.value << '\n';

        double next;
        if (inputs[n.fileId] >> next) {
            heap.push({ next, n.fileId });
        }
    }

    // cleanup temporary files
    for (size_t i = 0; i < fileCount; ++i) {
        std::remove(("chunk_" + std::to_string(i)).c_str());
    }
}
