#ifndef TWOPASSESASSEMBLER_H_INCLUDED
#define TWOPASSESASSEMBLER_H_INCLUDED

#include "assembler/assemblydata.h"
#include "assembler/twopasses/zerothpass.h"

class TwoPassesAssembler {
public:
  TwoPassesAssembler(AssemblyData* ad) {
    assemblyData = ad;
    zerothPass = ZerothPass(ad);
  }

  void run() {
    for (auto source : assemblyData->getSources()) {
      zerothPass = ZerothPass(assemblyData);
      zerothPass.run();
    }

  }

private:
  AssemblyData* assemblyData;

  ZerothPass zerothPass;
};

#endif // !TWOPASSESASSEMBLER_H_INCLUDED
