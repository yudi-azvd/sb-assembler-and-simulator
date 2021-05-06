// #include <iostream>
// #include <vector>

// #include "../../lib/doctest/doctest.h"
// #include "../../src/montador/assembler.h"
// #include "../../src/montador/util.h"

// TEST_CASE("adjust data section") {
//   std::map<std::string, int> symbolTable = {
//     {"label1", 1},
//     {"label2", 2},
//     {"label3", 3},
//     {"label4", 4},
//   };

//   std::map<std::string, int> expectedSymbolTable = {
//     {"label1", 9},
//     {"label2", 10},
//     {"label3", 11},
//     {"label4", 12},
//   };

//   Assembler as;

//   int offset = 8;

//   as.setSymbolTable(symbolTable);
//   as.adjustForDataSection();

//   std::map<std::string, int> gotSymbolTable = as.symbolTable();

//   INFO("exp: ", strToIntMapToString(expectedSymbolTable));
//   INFO("got: ", strToIntMapToString(gotSymbolTable));

//   CHECK_EQ(expectedSymbolTable, gotSymbolTable);
// }
