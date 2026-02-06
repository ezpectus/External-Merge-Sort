#include "generator.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <stdexcept>

void generateFile(const std::string& filename, size_t targetSizeBytes) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file for generation");
    }

    std::mt19937_64 rng(123);
    std::uniform_real_distribution<double> dist(-1e300, 1e300);

    size_t written = 0;

    while (written < targetSizeBytes) {
        double x = dist(rng);

        std::ostringstream ss;
        ss << std::scientific << std::setprecision(17) << x << '\n';
        std::string line = ss.str();

        out << line;
        written += line.size();
    }
}


// Generates a file with random double values in text format


