#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <chrono>

struct Ship {
    int rank;
    Ship* parent;
};

Ship* FIND_SET(Ship& x);
void UNION(Ship& x, Ship& y);
std::unique_ptr<Ship> MAKE_SET();

void writeNumOfWarnings(const std::string& inputFilename) {
    std::vector<std::unique_ptr<Ship>> ships;
    std::ostringstream outputBuffer;

    try {
        std::ifstream infile(inputFilename);
        if (!infile.is_open()) {
            std::cerr << "Error: '" << inputFilename << "' not found.\n";
            return;
        }

        int count = 0;
        bool start = true;
        int N = 0, M = 0;

        while (start) {
            std::string line;
            if (!std::getline(infile, line)) break;

            std::istringstream iss(line);
            iss >> N >> M;

            if ((N == 0 && M == 0)) break;

            for (int incr = 0; incr < N; ++incr) { // inicializacija ladij oz. disjunktnih množic
                ships.push_back(MAKE_SET());
            }

            for (int incr = 0; incr < M; incr++) {
                if (!std::getline(infile, line)) break;

                std::istringstream iss2(line);
                std::string i, j;
                iss2 >> i >> j;

                UNION(*ships[std::stoi(i) - 1], *ships[std::stoi(j) - 1]);
            }

            int result = 0;
            for (int incr = 0; incr < N; ++incr) {
                if (ships[incr]->parent == ships[incr].get()) {
                    result++;
                }
            }
            outputBuffer << result << std::endl;

            ships.clear();
        }

        std::string outputContent = outputBuffer.str();
        if (!outputContent.empty() && outputContent.back() == '\n') {
            outputContent.pop_back(); // Remove the last newline character
        }
        std::cout << outputContent;

    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    }
}

std::unique_ptr<Ship> MAKE_SET() {
    auto ship = std::make_unique<Ship>();
    ship->rank = 0;
    ship->parent = ship.get();
    return ship;
}

void UNION(Ship& x, Ship& y) {
    Ship* p = FIND_SET(x);
    Ship* q = FIND_SET(y);
    if (p == q) return;
    if (p->rank > q->rank) {
        q->parent = p;
    }
    else {
        p->parent = q;
        if (p->rank == q->rank) {
            q->rank = q->rank + 1;
        }
    }
}

Ship* FIND_SET(Ship& x) {
    if (&x != x.parent) {
        x.parent = FIND_SET(*x.parent);
    }
    return x.parent;
}

int main() {
    // output the time it takes to run the function
    auto start = std::chrono::high_resolution_clock::now();
    writeNumOfWarnings("testni_primer.txt");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    //std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}

