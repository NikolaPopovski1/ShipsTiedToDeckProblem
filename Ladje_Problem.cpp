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

Ship* FIND_SETds(Ship& x);
void UNIONds(Ship& x, Ship& y);
std::unique_ptr<Ship> MAKE_SET();

void writeNumOfWarnings(const std::string& inputFilename, const std::string& outputFilename) {
    std::vector<std::unique_ptr<Ship>> ships;

    std::ofstream outfile(outputFilename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open '" << outputFilename << "' for writing.\n";
        return;
    }

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

                UNIONds(*ships[std::stoi(i) - 1], *ships[std::stoi(j) - 1]);
            }

            int result = 0;
            for (int incr = 0; incr < N; ++incr) {
                if (ships[incr]->parent == ships[incr].get()) {
                    result++;
                }
            }
            outfile << result << std::endl;

			ships.clear();
        }

        std::cout << "File '" << inputFilename << "' copied successfully to '" << outputFilename << "'.\n";

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

void UNIONds(Ship& x, Ship& y) {
    Ship* p = FIND_SETds(x);
    Ship* q = FIND_SETds(y);
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

Ship* FIND_SETds(Ship& x) {
    if (&x != x.parent) {
        x.parent = FIND_SETds(*x.parent);
    }
    return x.parent;
}

int main() {
	// output the time it takes to run the function
    auto start = std::chrono::high_resolution_clock::now();
    writeNumOfWarnings("testni_primer.txt", "output.txt");
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}
