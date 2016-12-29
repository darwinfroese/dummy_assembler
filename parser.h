#pragma once

#include "assembler.h"

class Parser {
public:
    Parser();
    ~Parser();

    string ParseArithmetic(vector<string>);
    string ParseControl(vector<string>);
    string ParseLoop(vector<string>);

    void ResetParser();
private:
    static const int register_count = 32;

    vector<string> conditional_labels;
    vector<string> loop_labels;
    vector<int32_t> registers;
    vector<bool> usedRegisterFlags;

    int find_unused_register();
    bool is_variable(string);
    string convert_variables(string, string);
    string create_label(vector<string> &, string);

    string generate_conditional(vector<string>, string);
};