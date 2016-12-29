#include "assembler.h"
#include "parser.h"

void read_file(string);
void write_file(string);
vector<string> parse(string);
void handle_line(vector<string>);

Parser parser;
vector<string> assembly_instructions;

int main(int argc, char *argv[]) {
    parser = Parser();
    read_file("test.txt");
    write_file("out.txt");
    return 0;
}

void read_file(string filePath) {
    ifstream file(filePath);
    string line;
    vector<string> tokens;

    while (getline(file, line)) {
        cout << "input: " << line << endl;

        if (!line.empty())
             tokens = parse(line);

        handle_line(tokens);
    }
}

void write_file(string filePath) {
    ofstream file(filePath);

    for (vector<string>::const_iterator i = assembly_instructions.begin(); i != assembly_instructions.end(); i++) {
        file << *i << endl;
    }
}

vector<string> parse(string line) {
    string buffer;
    stringstream ss(line);
    vector<string> tokens;

    while (ss >> buffer)
        tokens.push_back(buffer);
    
    return tokens;
}

void handle_line(vector<string> tokens) {
    string identifier(tokens[0]);
    transform(tokens[0].begin(), tokens[0].end(), identifier.begin(), ::tolower);

    if (identifier.compare("if") == 0) {
        assembly_instructions.push_back(parser.ParseControl(tokens));
    }
    else if (identifier.compare("else") == 0) {
        assembly_instructions.push_back(parser.ParseControl(tokens));
    }
    else if (identifier.compare("loop") == 0) {
        assembly_instructions.push_back(parser.ParseLoop(tokens));
    }
    else {
        assembly_instructions.push_back(parser.ParseArithmetic(tokens));
    }
}