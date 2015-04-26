#ifndef GANYMEDE_INCLUDE_
#define GANYMEDE_INCLUDE_

#include "stdlib.h"
#include "stdio.h"
#include "string"
#include "assert.h"
#include "iostream"
#include "fstream"
#include "math.h"

extern std::ofstream strlog;

using namespace std;



const int int_poison = 0xDEADBABE;
const double double_poison = 3.1415;
const char char_poison = 0x42;

const int MAXGANCOMMAND = 5;

struct Code;

void emergency_terminate(Code* code_buffer);																																	\



#define IS_ZERO(value) (abs(value) < 0.0000001)
#define EQUAL(a, b) IS_ZERO((a) - (b))
#endif