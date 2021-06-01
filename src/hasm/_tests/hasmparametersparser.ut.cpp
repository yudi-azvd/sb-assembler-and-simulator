#include <iostream>

#include "doctest/doctest.h"
#include "hasm/hasmparametersparser.h"


TEST_SUITE("hasm-hasmparameters-parser") {

TEST_CASE("should get correct file names") {
  std::vector<std::string> args = {"a.asm", "b.asm"};

  HasmParametersParser parser(args);

  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct single file name even with -c flag") {
  std::vector<std::string> args = {"a.asm", "-c"};

  HasmParametersParser parser(args);

  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct file names even with -c flag") {
  std::vector<std::string> args = {"a.asm", "b.asm", "-c"};

  HasmParametersParser parser(args);

  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm", "b.asm"};

  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct file names even with -o flag") {
  std::vector<std::string> args = {"a.asm", "-o", "a.o"};

  HasmParametersParser parser(args);

  HasmParameters params = parser.run();

  std::vector<std::string> expectedFilenames = {"a.asm"};

  INFO("exp ", expectedFilenames);
  INFO("got ", params.filenames);
  CHECK_EQ(expectedFilenames, params.filenames);
}


TEST_CASE("should get correct output names with -o flag") {
  std::vector<std::string> args = {"a.asm", "-o", "a.o"};

  HasmParametersParser parser(args);

  HasmParameters params = parser.run();

  std::string expectedOutputName = {"a.o"};

  CHECK_EQ(expectedOutputName, params.outputFilename);
}


TEST_CASE("should throw exception when input name is the same as output name") {
  std::vector<std::string> args = {"a.asm", "-o", "a.asm"};

  HasmParametersParser parser(args);

  CHECK_THROWS_WITH_AS(parser.run(),
    "erro: Nome de saída é igual ao nome de entrada",
    HasmParameterException
  );
}


TEST_CASE("should throw exception when no output name is given using -o flag") {
  std::vector<std::string> args = {"a.asm", "-o"};

  HasmParametersParser parser(args);

  CHECK_THROWS_WITH_AS(parser.run(),
    "erro: Falta o nome do arquivo depois de '-o'",
    HasmParameterException);
}


TEST_CASE("should throw exception when given multiple input files while  using -o flag") {
  std::vector<std::string> args = {"a.asm", "b.asm", "-o", "c.o"};

  HasmParametersParser parser(args);

  CHECK_THROWS_WITH_AS(parser.run(),
    "erro: Não é permitido usar '-o' com mútiplos arquivos",
    HasmParameterException);
}


TEST_CASE("should throw exception when no input files are given") {
  std::vector<std::string> args = {};

  HasmParametersParser parser(args);

  CHECK_THROWS_WITH_AS(parser.run(),
    "erro: Não há arquivos de entrada",
    HasmParameterException);
}


TEST_CASE("should throw exception when no input files are given while using -o") {
  std::vector<std::string> args = {"-o", "outfile"};

  HasmParametersParser parser(args);

  CHECK_THROWS_WITH_AS(parser.run(),
    "erro: Não há arquivos de entrada",
    HasmParameterException);
}


TEST_CASE("should throw exception when using wrong constructor") {
  try {
    HasmParametersParser parser;
  }
  catch (std::runtime_error& e) {
    std::string exceptionMessage(e.what());
    CHECK("default constructor should not be used. Use "
      "'HasmParametersParser(std::vector<std::string> args)' instead"
      == exceptionMessage);
  }
  catch(...) {
    FAIL_CHECK("exception not caught");
  }
}

}



// TEST_SUITE_END();
