#include "hasm.h"

#include "assembler/twopasses/twopassesassembler.h"


Hasm::Hasm() { }


Hasm::~Hasm() {
  delete oldAssembler;
  delete hasmData;
  delete assembler;
  delete input;
  // delete linker;
  // delete outputGen;
}


Hasm::Hasm(std::vector<std::string> args) {
  HasmParametersParser parser(args);
  parameters = parser.run();

  hasmData = new HasmData(parameters);
  // oldAssembler = new OldAssembler(parameters.filenames);
  input = new Input(hasmData);
  assembler = new TwoPassesAssembler(hasmData->getAssemblyData());
}


void Hasm::run() {
  input->readFiles(); // Deve também lançar exceção se existirem arquivos
                      // de tipos diferentes.

  // oldAssembler->assemble();
  assembler->run();

  // for (auto source : hasmData->getAssemblyData()->getSources()) {
  //   std::cout << *source << std::endl;
  // }
  // for (auto source : hasmData->getAssemblyData()->getNthSource(0)->) {
  //   std::cout << *source << std::endl;
  // }

  for (int i = 0; i < hasmData->getAssemblyData()->getSources().size(); ++i) {
    std::cout << "us table" << std::endl;
    std::cout << *(hasmData->getAssemblyData()->getNthSource(i)->getUsageTable()) << std::endl;
    std::cout << "def table" << std::endl;
    std::cout << *(hasmData->getAssemblyData()->getNthSource(i)->getDefinitionsTable()) << std::endl;
  }

  /*
  if (input.areAssemblyFiles() hasmData.isAssembleOnly()) {
    assembler = new TwoPassesAssembler(hasmData);
    assembler->run();

    if (hasmData.isAssembleOnly) {
      outputGen = new OutputGenerator(hasmData);
      outputGen->run();
      return;
    }
  }

  if (hasmData.mustLink()) {
    linker = new Linker(hasmData);
    linker->run()
  }

  outputGen = new OutputGenerator(hasmData);
  outputGen->run();
  */
}
