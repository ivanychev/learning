#ifndef GANYMEDE_INCLUDE_
#define GANYMEDE_INCLUDE_

#include "assert.h"
#include "fstream"
#include "iostream"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string"

extern std::ofstream strlog;

using namespace std;

const int int_poison = 0xDEADBABE;
const double double_poison = 3.1415;
const char char_poison = 0x42;

const int MAXGANCOMMAND = 5;

struct Code;

void emergency_terminate(Code *code_buffer);

#define IS_ZERO(value) (abs(value) < 0.0000001)
#define EQUAL(a, b) IS_ZERO((a) - (b))
#endif