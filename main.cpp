#include "assembler.h"

void read_file(string);
vector<string> parse(string);

int main(int argc, char *argv[]) {
    read_file("test.txt");

    return 0;
}

void read_file(string filePath) {
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        cout << line << endl;
        vector<string> tokens = parse(line);

        for (vector<string>::const_iterator i = tokens.begin(); i != tokens.end(); i++)
            cout << *i << ' ';
        
        cout << endl;
    }
}

vector<string> parse(string line) {
    string buffer;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);
    
    return tokens;
}