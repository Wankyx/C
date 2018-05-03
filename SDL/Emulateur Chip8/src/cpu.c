#include <SDL2/SDL.h>
#include "cpu.h"

void CHIP8_InitJump()
{
	opcode.mask[0]= 0x0000; opcode.id[0]=0x0FFF;          /* 0NNN */ 
  opcode.mask[1]= 0xFFFF; opcode.id[1]=0x00E0;          /* 00E0 */ 
  opcode.mask[2]= 0xFFFF; opcode.id[2]=0x00EE;          /* 00EE */ 
  opcode.mask[3]= 0xF000; opcode.id[3]=0x1000;          /* 1NNN */ 
  opcode.mask[4]= 0xF000; opcode.id[4]=0x2000;          /* 2NNN */ 
  opcode.mask[5]= 0xF000; opcode.id[5]=0x3000;          /* 3XNN */ 
  opcode.mask[6]= 0xF000; opcode.id[6]=0x4000;          /* 4XNN */ 
  opcode.mask[7]= 0xF00F; opcode.id[7]=0x5000;          /* 5XY0 */ 
  opcode.mask[8]= 0xF000; opcode.id[8]=0x6000;          /* 6XNN */ 
  opcode.mask[9]= 0xF000; opcode.id[9]=0x7000;          /* 7XNN */ 
  opcode.mask[10]= 0xF00F; opcode.id[10]=0x8000;          /* 8XY0 */ 
  opcode.mask[11]= 0xF00F; opcode.id[11]=0x8001;          /* 8XY1 */ 
  opcode.mask[12]= 0xF00F; opcode.id[12]=0x8002;          /* 8XY2 */ 
  opcode.mask[13]= 0xF00F; opcode.id[13]=0x8003;          /* BXY3 */ 
  opcode.mask[14]= 0xF00F; opcode.id[14]=0x8004;          /* 8XY4 */ 
  opcode.mask[15]= 0xF00F; opcode.id[15]=0x8005;          /* 8XY5 */ 
  opcode.mask[16]= 0xF00F; opcode.id[16]=0x8006;          /* 8XY6 */ 
  opcode.mask[17]= 0xF00F; opcode.id[17]=0x8007;          /* 8XY7 */ 
  opcode.mask[18]= 0xF00F; opcode.id[18]=0x800E;          /* 8XYE */ 
  opcode.mask[19]= 0xF00F; opcode.id[19]=0x9000;          /* 9XY0 */ 
  opcode.mask[20]= 0xF000; opcode.id[20]=0xA000;          /* ANNN */ 
  opcode.mask[21]= 0xF000; opcode.id[21]=0xB000;          /* BNNN */ 
  opcode.mask[22]= 0xF000; opcode.id[22]=0xC000;          /* CXNN */ 
  opcode.mask[23]= 0xF000; opcode.id[23]=0xD000;          /* DXYN */ 
  opcode.mask[24]= 0xF0FF; opcode.id[24]=0xE09E;          /* EX9E */ 
  opcode.mask[25]= 0xF0FF; opcode.id[25]=0xE0A1;          /* EXA1 */ 
  opcode.mask[26]= 0xF0FF; opcode.id[26]=0xF007;          /* FX07 */ 
  opcode.mask[27]= 0xF0FF; opcode.id[27]=0xF00A;          /* FX0A */ 
  opcode.mask[28]= 0xF0FF; opcode.id[28]=0xF015;          /* FX15 */ 
  opcode.mask[29]= 0xF0FF; opcode.id[29]=0xF018;          /* FX18 */ 
  opcode.mask[30]= 0xF0FF; opcode.id[30]=0xF01E;          /* FX1E */ 
  opcode.mask[31]= 0xF0FF; opcode.id[31]=0xF029;          /* FX29 */ 
  opcode.mask[32]= 0xF0FF; opcode.id[32]=0xF033;          /* FX33 */ 
  opcode.mask[33]= 0xF0FF; opcode.id[33]=0xF055;          /* FX55 */ 
  opcode.mask[34]= 0xF0FF; opcode.id[34]=0xF065;          /* FX65 */ 
}

Uint8 CHIP8_GetInstruction(Uint16 opcode)
{
	Uint8 instruction = 0;
	Uint16 result = 0;
	for(instruction = 0; instruction < OPCODE_LENGTH; instruction++)
	{
		result = (opcode.mask[instruction] & opcode);
		
		if(result == opcode.id[instruction])
		{
			instruction = OPCODE_LENGTH;
		}
	}
	return instruction;
}

Uint8 CHIP8_InterpreterInstruction(Uint16 opcode)
{
	Uint8 action = CHIP8_GetInstruction(opcode);
		
	switch(action)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
	}
}

/******************************************************/
void CHIP8_InitCpu()
{
	Uint16 iterator = 0;
	
	for(iterator = 0; iterator < MEMORY; iterator++)
	{
		cpu.memory[iterator] = 0;
	}
 
	for(iterator = 0; iterator < REGISTER; iterator++)
	{
		cpu.V[iterator] = 0;
	}
	 
	for(iterator = 0; iterator < STACK; iterator++)
	{
		cpu.stack[iterator] = 0;
	}
	
	cpu.I = 0;
	cpu.pc = 0;
	cpu.jump = 0;
	cpu.audio = 0;
	cpu.system = 0;
 	
}
void CHIP8_DeductCpu()
{
	if(cpu.system > 0)
		cpu.system = 0;
	if(cpu.audio > 0)
		cpu.audio = 0;
}

Uint16 CHIP8_GetOPCODE()
{
	return (cpu.memory[pc] << 8) + cpu.memory[pc+1];
}