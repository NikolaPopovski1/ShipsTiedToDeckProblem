#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>

struct Ship {
    int rank;
    int num;
    void* next;
    void* head;
};

std::unordered_map<int, Ship> getNumOfWarnings(const std::string& inputFilename, const std::string& outputFilename) {
    std::unordered_map<int, Ship> ships;
	void* head = nullptr;
	void* tail = nullptr;

    try {
        std::ifstream infile(inputFilename);
        if (!infile.is_open()) {
            std::cerr << "Error: '" << inputFilename << "' not found.\n";
            return;
        }

        int count = 0;
        bool start = true;
        int N = 0, M = 0;

        while (start || (N != 0 && M != 0)) {
            start = false;
            std::string line;
            if (!std::getline(infile, line)) break;

            std::istringstream iss(line);
            iss >> N >> M;

            //std::cout << count << std::endl;
            //count++;

			for (int incr = 0; incr < N; ++incr) { // inicializacija ladij oz. disjunktnih množic
                ships[incr + 1] = makeSet();
            }

            for (int incr = 0; incr < M; ++incr) {
                if (!std::getline(infile, line)) break;

                std::istringstream iss2(line);
                std::string i, j;
                iss2 >> i >> j;

                

                //std::cout << count << std::endl;
                //count++;
            }
        }

        std::ofstream outfile(outputFilename);
        if (!outfile.is_open()) {
            std::cerr << "Error: Unable to open '" << outputFilename << "' for writing.\n";
            return;
        }

        // Add any necessary output logic here
        std::cout << "File '" << inputFilename << "' copied successfully to '" << outputFilename << "'.\n";

    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    }
	return ships;
}

Ship makeSet() {
	Ship ship = Ship();
	ship.rank = 0;
	ship.num = 0;
	ship.next = nullptr;
	ship.head = nullptr;
	return ship;
}

void union(Ship& x, Ship& y) {
	return;
}



int main() {
    std::unordered_map<int, Ship> ships = getNumOfWarnings("testni_primer.txt", "output.txt");

    return 0;
}