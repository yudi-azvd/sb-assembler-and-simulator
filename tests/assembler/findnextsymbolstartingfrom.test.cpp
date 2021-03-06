#include <iostream>
#include <vector>

#include "../../lib/doctest/doctest.h"

#include "../../include/errors.h"
#include "../../include/parseline.h"
#include "../../include/assembler.h"


TEST_CASE("fntsf: findNextTokenStartingFrom") {
  int tokenStartsAt = 0;
  Assembler as; 
  std::string token;

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA: SPACE", tokenStartsAt);
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 10);

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA: SPACE ", tokenStartsAt);
  CHECK_EQ(token, "SPACE");

  //                                                !           
  token = as.findNextTokenStartingFrom(9, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 10);

  //                                       !           
  token = as.findNextTokenStartingFrom(0, "OLD_DATA  :    SPACE ", tokenStartsAt);
  CHECK_EQ(token, "OLD_DATA");
  CHECK_EQ(tokenStartsAt, 0);
}


TEST_CASE("fntsf: sequential calls to findNextTokenStartingFrom 1") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as; 
  std::string line = "COPY NEW_DATA,OLD_DATA";
  std::string token = "";

  token = as.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "COPY");
  CHECK_EQ(tokenStartsAt, 0);

  token = as.findNextTokenStartingFrom(newStart+1, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "NEW_DATA,OLD_DATA");
  CHECK_EQ(tokenStartsAt, 5);
}


TEST_CASE("fntsf: sequential calls to findNextTokenStartingFrom 2") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as; 
  std::string line = "NEW_DATA:SPACE     ";
  std::string token = "";

  token = as.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 0);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 8);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");
}


TEST_CASE("fntsf: sequential calls to findNextTokenStartingFrom 3") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as;

  std::string line = "      NEW_DATA:SPACE     ";
  std::string token = "";
  std::vector<std::string> tokens;

  token = as.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 6);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 14);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);


  line = "\tNEW_DATA  :   SPACE     ";

  token = as.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "NEW_DATA");
  CHECK_EQ(tokenStartsAt, 1);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, ":");
  CHECK_EQ(tokenStartsAt, 11);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "SPACE");
  CHECK_EQ(tokenStartsAt, 15);
}


TEST_CASE("fntsf: sequential calls to findNextTokenStartingFrom 4 - comment") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as; 
  std::string line = "NEW_DATA:SPACE  ; tem qie ser ignorado";
  std::string token = "";

  token = as.findNextTokenStartingFrom(0, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "NEW_DATA");

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, ":");

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "SPACE");

  // vai começar o comentário

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart += token.length();
  CHECK_EQ(token, "");
}

TEST_CASE("fntsf: should not find tokens at the end of the line") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as; 
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";

  token = as.findNextTokenStartingFrom(6, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "NEW_DATA,OLD_DATA");
  CHECK_EQ(tokenStartsAt, 8);

  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE  ; tem qie ser ignorado";

  int semiColonPosition = 16;
  token = as.findNextTokenStartingFrom(semiColonPosition, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);


  line = "NEW_DATA:SPACE     ";

  newStart = 15;
  token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
  newStart = token.length() + tokenStartsAt;
  CHECK_EQ(token, "");
  CHECK_EQ(tokenStartsAt, -1);
}


TEST_CASE("fntsf: should work in iterative calls") {
  int newStart = 0;
  int tokenStartsAt = 0;
  Assembler as; 
  std::string line = "COPY    NEW_DATA,OLD_DATA";
  std::string token = "";
  std::vector<std::string> expectedtokens = {"COPY", "NEW_DATA,OLD_DATA"};
  std::vector<std::string> gotTokens;

  while (tokenStartsAt >= 0) {
    token = as.findNextTokenStartingFrom(newStart, line, tokenStartsAt);
    newStart = token.length() + tokenStartsAt;
    gotTokens.push_back(token);
  }

  gotTokens.pop_back();
  CHECK_EQ(gotTokens, expectedtokens);
}
