#include <functional>
#include <iostream>
#include <fstream>
#include <queue>
#include <tuple>
#include <vector>

#include <libfuzzymatch/levenshtein.h>
#include <libfuzzymatch/util.h>

#include "../common/pairwise.h"
#include "../common/plain_index.h"
#include "../common/timer.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: \n\t query-index <index> <query-file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> queries;
    std::ifstream file(argv[argc - 1]);
    for (std::string line; std::getline(file, line);) {
        queries.push_back(line);
    }
    file.close();

    std::vector<std::vector<uint32_t>> index;
    loadIndex(argv[argc - 2], index);

    Timer timer;

    benchLevenshtein(queries, index, levenshtein<std::vector<uint32_t>, std::vector<uint32_t>>);

    double t = timer.getAndReset();
    std::cout << "RESULT algo=pairwise threshold=-1 index=" << argv[1] << " queries=" << argv[2] << " time=" << t << std::endl;
}
