SECTION DATA
ZERO : CONST 0
UM: CONST 0
TRES: CONST 3
ENTRADA: SPACE
RESULTADO: SPACE
SECTION TEXT
INPUT ENTRADA
LOAD ENTRADA
LOOP: SUB TRES
      JMPZ EH_MULTIPLO
      JMPN NAO_EH_MULTIPLO
      LOAD RESULTADO
      STORE RESULTADO
      JMP LOOP
         
EH_MULTIPLO: LOAD UM
             JMP FIM
NAO_EH_MULTIPLO: LOAD ZERO
                 JMP FIM
FIM: OUTPUT
     STOP