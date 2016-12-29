#include "assembler.h"

void read_file(string);
void write_file(string, vector<string>);
vector<string> parse(string);
ExpressionType check_expression(string);

int main(int argc, char *argv[]) {
    read_file("test.txt");

    return 0;
}

void read_file(string filePath) {
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        cout << "input: " << line << endl;
        vector<string> tokens = parse(line);

        write_file("out.txt", tokens);
        ExpressionType expr = check_expression(tokens[0]);
    }
}

void write_file(string filePath, vector<string> lines) {
    ofstream file(filePath, ofstream::out | ofstream::app);

    for (vector<string>::const_iterator i = lines.begin(); i != lines.end(); i++) {
        file << *i << ' ';
    }

    file << endl;
}

vector<string> parse(string line) {
    string buffer;
    stringstream ss(line);
    vector<string> tokens;

    while (ss >> buffer)
        tokens.push_back(buffer);
    
    return tokens;
}

ExpressionType check_expression(string line) {
    ExpressionType expr = ET_ARITHMETIC;

    if (line == "if")
        expr = ET_CONTROL;
    else if (line == "loop")
        expr = ET_LOOP;
        
    return expr;
}