#include "assembler.h"

void read_file(std::string);

int main(int argc, char *argv[]) {
    read_file("test.txt");

    return 0;
}

void read_file(std::string filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}