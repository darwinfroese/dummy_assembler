#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef enum {
    ET_CONTROL,
    ET_LOOP,
    ET_ARITHMETIC
}ExpressionType;