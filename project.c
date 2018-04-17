#include "spimcore.h"


/* ALU */
/* Written by Jordan Starkey */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	// Assumes ALUControl in int format
	switch(ALUControl) {
		// A + B
		case 0:
			*ALUresult = A + B;
			break;
		// A - B
		case 1:
			*ALUresult = A + B;
			break;
		// A < B (signed)
		case 2:
            *ALUresult = ((signed)A < (signed)B) ? 1 : 0;
        //  A < B (unsigned)
		case 3:
			*ALUresult = (A < B) ? 1 : 0;
        // A and B
        case 4: 
            *ALUresult = A & B;
            break;
        // A or B
        case 5: 
            *ALUresult = A | B;
            break;
 		// Shift left B by 16 bits
        case 6:
            *ALUresult = B << 16;  
            break;
        // Negate A
        case 7:
            *ALUresult = ~A;
            break;
	}

	// Set Zero based on bits of ALUResult
    *Zero = (*ALUresult == 0) ? 1 : 0;
}

/* instruction fetch */
/* Written by Jordan Starkey */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// Check word alignment (multiple of 4) 
	// Check if memeory location legal - If PC is assumed to be at starting addr 
	// then I dont need this condition
    if (PC % 4 == 0 && PC <= 0xFFFF)
    {
    	//Multiply PC by 4 to get the proper address in memory
        *instruction = Mem[PC >> 2];
        return 0;
    }
    return 1;
}


/* instruction partition */
/* Written by Jordan Starkey */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// Use bit-masking
	// AND with 1111 1100 0000 0000 0000 0000 0000 0000 and then shift 26 to get op.
	*op = (instruction & 0xFC000000) >> 26;

	// AND with 0000 0011 1110 0000 0000 0000 0000 0000 and then shift 21 to get r1.
	*r1 = (instruction & 0x03C00000) >> 21;

	// AND with 0000 0000 0001 1111 0000 0000 0000 0000 and then shift 16 to get r2.
	*r2 = (instruction & 0x001F0000) >> 16;

	// AND with 0000 0000 0000 0000 1111 1000 0000 0000 and then shift 11 to get r3.
	*r3 = (instruction & 0x0000F800) >> 11;

	// AND with 0000 0000 0000 0000 0000 0000 0011 1111 to get funct.
	*funct = (instruction & 0x0000003F);

	// AND with 0000 0000 0000 0000 1111 1111 1111 1111 to get offset.
	*offset = (instruction & 0x0000FFFF);

	// AND with 0000 0011 1111 1111 1111 1111 1111 1111 to get jsec.
	*jsec = (instruction & 0x03FFFFFF);

}



/* instruction decode */
//Wriiten by Edward Vo
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
  switch(op)
    {
        //ALU ADD
        case 000:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=0;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //ALU SUB
        case 001:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=1;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //ALU SLT
        case 010:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=2;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //ALU SLTI
        case 011:
        controls->RegDst=0;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=3;
        controls->MemWrite=0;
        controls->ALUSrc=1;
        controls->RegWrite=1;
        break;
        //ALU AND
        case 100:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=4;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //ALU OR
       case 101:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=5;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //ALU Shift left
        case 110:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=6;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=0;
        break;
        //R-TYPE instruction
        case 111:
        controls->RegDst=1;
        controls->Jump=0;
        controls->Branch=0;
        controls->MemRead=0;
        controls->MemtoReg=0;
        controls->ALUOp=7;
        controls->MemWrite=0;
        controls->ALUSrc=0;
        controls->RegWrite=1;
        break;
        //if halt occurs then return 1;
        default:
            return 1;

    }
  //else return 0
    return 0;
}

/* Read Register */
//Written by Edward Vo
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1=Reg[r1];
    *data2=Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

