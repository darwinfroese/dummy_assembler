#include "parser.h"

Parser::Parser() {
    current_label_number = 0;

    registers = vector<int32_t>(register_count);
    usedRegisterFlags = vector<bool>(register_count);
}

Parser::~Parser() {

}

void Parser::ResetParser() {
    current_label_number = 0;

    conditional_labels.clear();
    loop_labels.clear();
    variable_register_map.clear();

    registers = vector<int32_t>(register_count);
    usedRegisterFlags = vector<bool>(register_count);
}

string Parser::ParseArithmetic(vector<string> expression) {
    return string("Arithmetic");
}

string Parser::ParseControl(vector<string> expression) {
    string instruction;

    if (expression[0].compare("if") == 0) {
        instruction = parse_if(expression);
    }
    else if (expression[0].compare("else") == 0) {
        if (expression.size() > 1 && expression[1].compare("if") == 0) {
            expression.erase(expression.begin());
            instruction = parse_if(expression);
        }
        else {
            instruction = parse_else(expression);
        }
    }
    else if (expression[0].compare("switch") == 0) {
        instruction = parse_switch(expression);
    }

    return instruction;
}

string Parser::ParseLoop(vector<string> expression) {
    return string("Loop");
}

string Parser::parse_if(vector<string>expression) {
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

string Parser::parse_else(vector<string> expression) {
    ostringstream label;

    label << conditional_labels.back() << ":";
    conditional_labels.pop_back();

    return label.str();
}

string Parser::parse_switch(vector<string> expression) {
    return string("Not Implemented - Switch Control");
}

int Parser::find_register(string var_name) {
    int register_index = 0;

    map<string, int>::iterator it = variable_register_map.find(var_name);
    if (it != variable_register_map.end()) {
        return it->second;
    }

    for (vector<bool>::const_iterator i = usedRegisterFlags.begin(); i != usedRegisterFlags.end(); i++) {
        if (!*i) {
            usedRegisterFlags[register_index] = true;
            variable_register_map.insert(pair<string, int>(var_name, register_index));
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

    instruction << create_label(conditional_labels, "control");

    return instruction.str();
}

string Parser::convert_variables(string one, string two) {
    ostringstream vars;

    // Handle left side
    if (is_variable(one)) {
        vars << "$" << find_register(one) << ", ";
    }
    else {
        vars << one << ", ";
    }

    // Handle right side
    if (is_variable(two)) {
        vars << "$" << find_register(two) << ", ";
    }
    else {
        vars << two << ", ";
    }

    return vars.str();
}

string Parser::create_label(vector<string> &labels, string identifier) {
    ostringstream label; 

    label << identifier << current_label_number++;
    labels.push_back(label.str());

    return label.str();
}