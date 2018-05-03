#ifndef __CPU__H__ 
#define __CPU__H__ 

#define OPCODE_LENGTH 35

typedef struct 
{
	Uint16 mask[OPCODE_LENGTH];
	Uint16 id[OPCODE_LENGTH];
}JUMP;
JUMP opcode;
void CHIP8_InitJump();
Uint8 CHIP8_GetInstruction(Uint16 opcode);
Uint8 CHIP8_InterpreterInstruction(Uint16 opcode);

#define MEMORY 0xFFF + 0x1
#define BMEMORY 0x200
#define REGISTER 0x10
#define STACK 0x10

typedef struct 
{
	Uint8 memory[MEMORY];
	Uint16 pc;
	
	Uint8 V[REGISTER];
	Uint16 I; 
	
	Uint16 stack[STACK];
	Uint8 jump;
	
	Uint8 system;
	Uint8 audio;
}CPU;

CPU cpu;

void CHIP8_InitCpu();
void CHIP8_DeductCpu();
Uinit16 CHIP8_GetOPCODE();
#endif 