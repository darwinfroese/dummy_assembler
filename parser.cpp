#include "parser.h"

Parser::Parser() {
    registers = vector<int32_t>(register_count);
    usedRegisterFlags = vector<bool>(register_count);
}

Parser::~Parser() {

}

void Parser::ResetParser() {
    conditional_labels.clear();
    loop_labels.clear();

    registers = vector<int32_t>(register_count);
    usedRegisterFlags = vector<bool>(register_count);
}

string Parser::ParseArithmetic(vector<string> expression) {
    return string("Arithmetic");
}

string Parser::ParseControl(vector<string> expression) {
    string instruction;

    if (expression[2] == "==") {
        instruction = generate_conditional(expression, "bne");
    }
    else if (expression[2] == "!=") {
        instruction = generate_conditional(expression, "beq");
    }
    else if (expression[2] == "<=") {
        instruction = generate_conditional(expression, "bgt");
    }
    else if (expression[2] == ">=") {
        instruction = generate_conditional(expression, "blt");
    }
    else if (expression[2] == "<") {
        instruction = generate_conditional(expression, "bge");
    }
    else if (expression[2] == ">") {
        instruction = generate_conditional(expression, "ble");
    }

    return instruction;
}

string Parser::ParseLoop(vector<string> expression) {
    return string("Loop");
}

int Parser::find_unused_register() {
    int register_index = 0;

    for (vector<bool>::const_iterator i = usedRegisterFlags.begin(); i != usedRegisterFlags.end(); i++) {
        if (!*i) {
            usedRegisterFlags[register_index] = true;
            break;
        }
        register_index++;
    }

    return register_index;
}

bool Parser::is_variable(string token) {
    bool isVariable = true;

    if (isdigit(token[0]) || token[0] == '\'' || token[0] == '\"')
        isVariable = false;

    return isVariable;
}

string Parser::generate_conditional(vector<string> expression, string opcode) {
    ostringstream instruction;

    instruction << opcode << " ";

    string lhs = expression[1].substr(1);
    string rhs = expression[3].substr(0, expression[3].length()-1);

    instruction << convert_variables(lhs, rhs);

    // TODO: Handle variable re-use
    instruction << ", " << create_label(conditional_labels, "control");

    return instruction.str();
}

string Parser::convert_variables(string one, string two) {
    ostringstream vars;

    // Handle left side
    if (is_variable(one)) {
        vars << "$" << find_unused_register() << ", ";
    }
    else {
        vars << one << ", ";
    }

    // Handle right side
    if (is_variable(two)) {
        vars << "$" << find_unused_register() << ", ";
    }
    else {
        vars << two << ", ";
    }

    return vars.str();
}

string Parser::create_label(vector<string> &labels, string identifier) {
    ostringstream label; 

    label << identifier << labels.size();
    labels.push_back(label.str());

    return label.str();
}