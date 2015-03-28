// Generated by Flexc++ V1.08.00 on Sat, 28 Mar 2015 20:01:21 +0530

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// $insert class_ih
#include "Scanner.ih"
int Scanner::line_num =1;


    // s_ranges__: use (unsigned) characters as index to obtain
    //           that character's range-number.
    //           The range for EOF is defined in a constant in the
    //           class header file
size_t const ScannerBase::s_ranges__[] =
{
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,
    18,18,18,18,18,18,19,19,20,21,22,23,24,25,25,26,27,28,28,29,30,31,31,31,31,
    31,31,31,31,31,31,31,31,31,31,31,31,31,32,33,33,34,35,36,37,37,37,38,39,40,
    41,42,43,44,45,46,47,47,48,49,50,51,52,52,53,54,55,56,57,58,59,60,60,61,62,
    63,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
    64,64,64,64,64,65,
};

    // s_dfa__ contains the rows of *all* DFAs ordered by start state.
    // The enum class StartCondition__ is defined in the baseclass header
    // INITIAL is always 0.
    // Each entry defines the row to transit to if the column's
    // character range was sensed. Row numbers are relative to the
    // used DFA and d_dfaBase__ is set to the first row of the subset to use.
    // The row's final two values are begin and end indices in
    // s_rfc__[] (rule, flags and count), defining the state's rule details
int const ScannerBase::s_dfa__[][69] =
{
    // INITIAL
    {-1, 1,-1, 2, 3,-1, 4,-1, 5, 5, 5, 6, 5, 5, 7, 5, 8, 9, 9, 9,
         -1, 5,10,11,12,-1,13,13,13,13,13,13,13,13, 5,-1, 5,-1,13,13,
         13,13,14,15,13,13,16,13,13,13,13,13,13,17,13,13,13,18,19,13,
         13, 5,20, 5,-1,-1,-1,   0, 0},  // 0
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   0, 1},  // 1
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   1, 2},  // 2
    {-1,22,22,22,23,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,-1,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,-1,-1,   2, 2},  // 3
    {-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   2, 2},  // 4
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   2, 3},  // 5
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   3, 4},  // 6
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,26,26,26,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   4, 4},  // 7
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,28,28,28,29,
         -1,-1,-1,-1,-1,-1,-1,30,-1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,30,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,
         -1,-1,-1,-1,-1,-1,-1,   4, 5},  // 8
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1, 9, 9, 9, 9,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   5, 6},  // 9
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   6, 7},  // 10
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,32,33,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   7, 8},  // 11
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,   8, 9},  // 12
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,   9,10},  // 13
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,35,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  10,11},  // 14
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,36,13,13,37,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  11,12},  // 15
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,38,13,13,13,13,13,13,39,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  12,13},  // 16
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,40,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  13,14},  // 17
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,41,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  14,15},  // 18
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,42,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  15,16},  // 19
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,43,-1,-1,-1,-1,  16,16},  // 20
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  16,17},  // 21
    {-1,22,22,22,23,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,44,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,-1,-1,  17,17},  // 22
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  17,18},  // 23
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  18,19},  // 24
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  19,20},  // 25
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,26,26,26,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  20,21},  // 26
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,27,27,27,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  21,22},  // 27
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,28,28,28,29,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  22,23},  // 28
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,29,29,29,29,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  23,23},  // 29
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,30,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  23,24},  // 30
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,31,31,31,
         -1,-1,-1,-1,-1,-1,31,31,31,31,31,-1,-1,-1,-1,-1,-1,-1,31,31,
         31,31,31,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  24,25},  // 31
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  25,26},  // 32
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  26,27},  // 33
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  27,28},  // 34
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,46,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  28,29},  // 35
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,47,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  29,30},  // 36
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,48,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  30,31},  // 37
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  31,32},  // 38
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,49,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  32,33},  // 39
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,50,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  33,34},  // 40
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,51,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  34,35},  // 41
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,52,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  35,36},  // 42
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  36,37},  // 43
    {-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,55,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  37,37},  // 44
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,56,-1,-1,57,57,57,57,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  37,38},  // 45
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,58,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  38,39},  // 46
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,59,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  39,40},  // 47
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  40,41},  // 48
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  41,42},  // 49
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,60,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  42,43},  // 50
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,61,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  43,44},  // 51
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,62,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  44,45},  // 52
    {-1,22,22,22,23,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,63,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,-1,-1,  45,45},  // 53
    {-1,22,22,22,23,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,64,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,-1,-1,  45,45},  // 54
    {-1,22,22,22,23,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,65,22,22,22,22,
         22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,
         22,22,22,22,22,-1,-1,  45,45},  // 55
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,56,56,56,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  45,46},  // 56
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,57,57,57,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  46,47},  // 57
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  47,48},  // 58
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,66,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  48,49},  // 59
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,67,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  49,50},  // 60
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  50,51},  // 61
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,68,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  51,52},  // 62
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,55,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  52,52},  // 63
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  52,52},  // 64
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,  52,52},  // 65
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  52,53},  // 66
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,69,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  53,54},  // 67
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  54,55},  // 68
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,
         -1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1,-1,-1,-1,13,13,
         13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
         13,-1,-1,-1,-1,-1,-1,  55,56},  // 69
};

    // The first value is the rule index
    // The second value is the FLAG: see the scannerbase.h file
    // 1: Final     4: Count        11: Final/BOL,Inc     
    // 2: Inc.      5: Final,Count  13: Final/BOL,Count
    // 3: Final,Inc 9: Final/BOL    
    // The third value is the LOP count value (valid for Count flags)
size_t const ScannerBase::s_rfc__[][3] =
{
//     R  F  C
     {20, 1, 0},  // 0
     {19, 1, 0},  // 1
     {19, 1, 0},  // 2
     {19, 1, 0},  // 3
     {16, 1, 0},  // 4
     {16, 1, 0},  // 5
     {19, 1, 0},  // 6
     {19, 1, 0},  // 7
     {19, 1, 0},  // 8
     { 8, 1, 0},  // 9
     { 8, 1, 0},  // 10
     { 8, 1, 0},  // 11
     { 8, 1, 0},  // 12
     { 8, 1, 0},  // 13
     { 8, 1, 0},  // 14
     { 8, 1, 0},  // 15
     {13, 1, 0},  // 16
     {17, 1, 0},  // 17
     {14, 1, 0},  // 18
     { 9, 1, 0},  // 19
     {18, 1, 0},  // 20
     {18, 1, 0},  // 21
     {16, 1, 0},  // 22
     {16, 1, 0},  // 23
     {16, 1, 0},  // 24
     {11, 1, 0},  // 25
     {10, 1, 0},  // 26
     {12, 1, 0},  // 27
     { 8, 1, 0},  // 28
     { 8, 1, 0},  // 29
     { 8, 1, 0},  // 30
     { 3, 1, 0},  // 31
     { 8, 1, 0},  // 32
     { 8, 1, 0},  // 33
     { 8, 1, 0},  // 34
     { 8, 1, 0},  // 35
     {15, 1, 0},  // 36
     {18, 1, 0},  // 37
     { 8, 1, 0},  // 38
     { 8, 1, 0},  // 39
     { 5, 1, 0},  // 40
     { 1, 1, 0},  // 41
     { 8, 1, 0},  // 42
     { 8, 1, 0},  // 43
     { 8, 1, 0},  // 44
     {18, 1, 0},  // 45
     {18, 1, 0},  // 46
     { 4, 1, 0},  // 47
     { 8, 1, 0},  // 48
     { 8, 1, 0},  // 49
     { 0, 1, 0},  // 50
     { 8, 1, 0},  // 51
     { 2, 1, 0},  // 52
     { 8, 1, 0},  // 53
     { 6, 1, 0},  // 54
     { 7, 1, 0},  // 55
};

int const (*ScannerBase::s_dfaBase__[])[69] =
{
    s_dfa__ + 0,
};

size_t ScannerBase::s_istreamNr = 0;

// $insert inputImplementation
ScannerBase::Input::Input()
:
    d_in(0),
    d_lineNr(1)
{}

ScannerBase::Input::Input(std::istream *iStream, size_t lineNr)
:
    d_in(iStream),
    d_lineNr(lineNr)
{}

size_t ScannerBase::Input::get()
{
    switch (size_t ch = next())         // get the next input char
    {
        case '\n':
            ++d_lineNr;
        // FALLING THROUGH

        default:
        return ch;
    }
}

size_t ScannerBase::Input::next()
{
    size_t ch;

    if (d_deque.empty())                    // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : static_cast<size_t>(AT_EOF);
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void ScannerBase::Input::reRead(size_t ch)
{
    if (ch < 0x100)
    {
        if (ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void ScannerBase::Input::reRead(std::string const &str, size_t fm)
{
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

ScannerBase::ScannerBase(std::istream &in, std::ostream &out)
:
    d_filename("-"),
    d_startCondition(StartCondition__::INITIAL),
    d_state(0),
    d_out(new std::ostream(out.rdbuf())),
    d_sawEOF(false),
    d_atBOL(true),
    d_tailCount(21, std::numeric_limits<size_t>::max()),
// $insert interactiveInit
    d_in(0),
    d_input(new std::istream(in.rdbuf())),
    d_dfaBase__(s_dfa__)
{}

void ScannerBase::switchStream__(std::istream &in, size_t lineNr)
{
    d_input.close();
    d_state = 0;
    d_input = Input(new std::istream(in.rdbuf()), lineNr);
    d_sawEOF = false;
    d_atBOL = true;
}


ScannerBase::ScannerBase(std::string const &infilename, std::string const &outfilename)
:
    d_filename(infilename),
    d_startCondition(StartCondition__::INITIAL),
    d_state(0),
    d_out(outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
          outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                  new std::ofstream(outfilename)),
    d_sawEOF(false),
    d_atBOL(true),
    d_tailCount(21, std::numeric_limits<size_t>::max()),
    d_input(new std::ifstream(infilename)),
    d_dfaBase__(s_dfa__)
{}

void ScannerBase::switchStreams(std::istream &in, std::ostream &out)
{
    switchStream__(in, 1);
    switchOstream(out);
}


void ScannerBase::switchOstream(std::ostream &out)
{
    *d_out << std::flush;
    d_out.reset(new std::ostream(out.rdbuf()));
}

// $insert debugFunctions
void ScannerBase::setDebug(bool onOff)
{}

bool ScannerBase::debug() const
{
    return false;
}

void ScannerBase::redo(size_t nChars)
{
    size_t from = nChars >= length() ? 0 : length() - nChars;
    d_input.reRead(d_matched, from);
    d_matched.resize(from);
}

void ScannerBase::switchOstream(std::string const &outfilename)
{
    *d_out << std::flush;
    d_out.reset(
            outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
            outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                    new std::ofstream(outfilename));
}


void ScannerBase::switchIstream(std::string const &infilename)
{
    d_input.close();
    d_filename = infilename;
    d_input = Input(new std::ifstream(infilename));
    d_sawEOF = false;
    d_atBOL = true;
}

void ScannerBase::switchStreams(std::string const &infilename,
                           std::string const &outfilename)
{
    switchOstream(outfilename);
    switchIstream(infilename);
}

void ScannerBase::pushStream(std::istream  &istr)
{
    std::istream *streamPtr = new std::istream(istr.rdbuf());
    p_pushStream("(istream)", streamPtr);
}

void ScannerBase::pushStream(std::string const &name)
{
    std::istream *streamPtr = new std::ifstream(name);
    if (!*streamPtr)
    {
        delete streamPtr;
        throw std::runtime_error("Cannot read " + name);
    }
    p_pushStream(name, streamPtr);
}


void ScannerBase::p_pushStream(std::string const &name, std::istream *streamPtr)
{
    if (d_streamStack.size() == s_maxSizeofStreamStack__)
    {
        delete streamPtr;
        throw std::length_error("Max stream stack size exceeded");
    }

    d_streamStack.push_back(StreamStruct{d_filename, d_input});
    d_filename = name;
    d_input = Input(streamPtr);
    d_sawEOF = false;
    d_atBOL = true;
}


bool ScannerBase::popStream()
{
    d_input.close();

    if (d_streamStack.empty())
        return false;

    StreamStruct &top = d_streamStack.back();

    d_input =   top.pushedInput;
    d_filename = top.pushedName;
    d_streamStack.pop_back();
    d_sawEOF = false;

    return true;
}

ScannerBase::ActionType__ ScannerBase::actionType__(size_t range)
{
    d_nextState = d_dfaBase__[d_state][range];

    if (d_nextState != -1)                  // transition is possible
        return ActionType__::CONTINUE;

    if (atFinalState())                     // FINAL state reached
        return ActionType__::MATCH;

    if (d_matched.size())
        return ActionType__::ECHO_FIRST;    // no match, echo the 1st char

    return range != s_rangeOfEOF__ ? 
                ActionType__::ECHO_CH 
            : 
                ActionType__::RETURN;
}

void ScannerBase::accept(size_t nChars)          // old name: less
{
    if (nChars < d_matched.size())
    {
        d_input.reRead(d_matched, nChars);
        d_matched.resize(nChars);
    }
}

  // The size of d_matched is determined:
  //    The current state is a known final state (as determined by 
  // inspectRFCs__(), just prior to calling matched__). 
  //    The contents of d_matched are reduced to d_final's size or (if set)
  // to the LOP-rule's tail size.
void ScannerBase::determineMatchedSize(FinData const &final)
{
    size_t length = final.matchLen;
    if (final.tailCount != std::numeric_limits<size_t>::max())
        length -= final.tailCount;

    d_input.reRead(d_matched, length);      // reread the tail section
    d_matched.resize(length);               // return what's left
}

  // At this point a rule has been matched.  The next character is not part of
  // the matched rule and is sent back to the input.  The final match length
  // is determined, the index of the matched rule is determined, and then
  // d_atBOL is updated. Finally the rule index is returned.
size_t ScannerBase::matched__(size_t ch)
{
    d_input.reRead(ch);

    if (!d_atBOL)
        d_final.atBOL.rule = std::numeric_limits<size_t>::max();

    FinData &final = d_final.atBOL.rule == std::numeric_limits<size_t>::max() ? 
                            d_final.notAtBOL
                        :
                            d_final.atBOL;

    determineMatchedSize(final);

    d_atBOL = *d_matched.rbegin() == '\n';


    return final.rule;
}

size_t ScannerBase::getRange__(int ch)       // using int to prevent casts
{
    if (ch != AT_EOF)
        d_sawEOF = false;

    return ch == AT_EOF ? static_cast<size_t>(s_rangeOfEOF__) : s_ranges__[ch];
}

  // At this point d_nextState contains the next state and continuation is
  // possible. The just read char. is appended to d_match, and LOP counts
  // are updated.
void ScannerBase::continue__(int ch)
{
    d_state = d_nextState;

    if (ch != AT_EOF)
        d_matched += ch;
}

void ScannerBase::echoCh__(size_t ch)
{
    *d_out << static_cast<char>(ch);
    d_atBOL = ch == '\n';
}


   // At this point there is no continuation. The last character is
   // pushed back into the input stream as well as all but the first char. in
   // the buffer. The first char. in the buffer is echoed to stderr. 
   // If there isn't any 1st char yet then the current char doesn't fit any
   // rules and that char is then echoed
void ScannerBase::echoFirst__(size_t ch)
{
    d_input.reRead(ch);
    d_input.reRead(d_matched, 1);
    echoCh__(d_matched[0]);
}

    // Inspect all s_rfc__ elements associated with the current state
    //  If the s_rfc__ element has its COUNT flag set then set the 
    // d_tailCount[rule] value to the element's tailCount value, if it has its 
    // INCREMENT flag set then increment d_tailCount[rule]
    //  If neither was set set the d_tailCount[rule] to numeric_limits<size_t>::max()
    // 
    // If the s_rfc__ element has its FINAL flag set then store the rule number
    // in d_final.second. If it has its FINAL + BOL flags set then store the
    // rule number in d_final.first
void ScannerBase::inspectRFCs__()
{
    for 
    (
        size_t begin = d_dfaBase__[d_state][s_finacIdx__], 
                 end = d_dfaBase__[d_state][s_finacIdx__ + 1];
            begin != end;
                ++begin
    )
    {
        size_t const *rfc = s_rfc__[begin];
        size_t flag = rfc[FLAGS];
        size_t rule = rfc[RULE];

        if (flag & INCREMENT)
            ++d_tailCount[rule];
        else 
            d_tailCount[rule] = (flag & COUNT) ? rfc[ACCCOUNT] : std::numeric_limits<size_t>::max();

        if (flag & FINAL)
        {
            FinData &final = (flag & BOL) ? d_final.atBOL : d_final.notAtBOL;
            final = FinData { rule, d_matched.size(), d_tailCount[rule] };
        }
    }
}

void ScannerBase::reset__()
{
    d_final = Final { {std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() }, 
                      {std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() } };
    d_state = 0;
    d_return = true;

    if (!d_more)
        d_matched.clear();

    d_more = false;
}

int Scanner::executeAction__(size_t ruleIdx)
try
{
    switch (ruleIdx)
    {
        // $insert actions
        case 0:
        {
#line 27 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::VOID;}

        }
        break;
        case 1:
        {
#line 28 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::INT;}

        }
        break;
        case 2:
        {
#line 29 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::FLOAT;}

        }
        break;
        case 3:
        {
#line 30 "lex.l"
            return Parser::IF;

        }
        break;
        case 4:
        {
#line 31 "lex.l"
            return Parser::ELSE;

        }
        break;
        case 5:
        {
#line 32 "lex.l"
            return Parser::FOR;

        }
        break;
        case 6:
        {
#line 33 "lex.l"
            return Parser::WHILE;

        }
        break;
        case 7:
        {
#line 34 "lex.l"
            return Parser::RETURN;

        }
        break;
        case 8:
        {
#line 35 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::IDENTIFIER;}

        }
        break;
        case 9:
        {
#line 36 "lex.l"
            return Parser::INC_OP;

        }
        break;
        case 10:
        {
#line 37 "lex.l"
            return Parser::EQ_OP;

        }
        break;
        case 11:
        {
#line 38 "lex.l"
            return Parser::LE_OP;

        }
        break;
        case 12:
        {
#line 39 "lex.l"
            return Parser::GE_OP;

        }
        break;
        case 13:
        {
#line 40 "lex.l"
            return Parser::NE_OP;

        }
        break;
        case 14:
        {
#line 41 "lex.l"
            return Parser::AND_OP;

        }
        break;
        case 15:
        {
#line 42 "lex.l"
            return Parser::OR_OP;

        }
        break;
        case 16:
        {
#line 43 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::INT_CONSTANT;}

        }
        break;
        case 17:
        {
#line 44 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::STRING_LITERAL;}

        }
        break;
        case 18:
        {
#line 45 "lex.l"
            {Parser::d_val__ = std::string(matched());return Parser::FLOAT_CONSTANT;}

        }
        break;
        case 19:
        {
#line 46 "lex.l"
            return matched()[0];

        }
        break;
        case 20:
        {
#line 47 "lex.l"
            {(Scanner::line_num)++;}

        }
        break;
    }
    noReturn__();
    return 0;
}
catch (Leave__ value)
{
    return static_cast<int>(value);
}

int Scanner::lex__()
{
    reset__();
    preCode();

    while (true)
    {
        size_t ch = get__();                // fetch next char
        size_t range = getRange__(ch);      // determine the range

        inspectRFCs__();                    // update d_tailCount values

        switch (actionType__(range))        // determine the action
        {
            case ActionType__::CONTINUE:
                continue__(ch);
            continue;

            case ActionType__::MATCH:
            {
                d_token__ = executeAction__(matched__(ch));
                if (return__())
                {
                    print();
                    postCode(PostEnum__::RETURN);
                    return d_token__;
                }
                break;
            }

            case ActionType__::ECHO_FIRST:
                echoFirst__(ch);
            break;

            case ActionType__::ECHO_CH:
                echoCh__(ch);
            break;

            case ActionType__::RETURN:
                if (!popStream())
                {
                     postCode(PostEnum__::END);
                     return 0;
                }
                postCode(PostEnum__::POP);
             continue;
        } // switch

        postCode(PostEnum__::WIP);

        reset__();
        preCode();
    } // while
}

void ScannerBase::print__() const
{
}


