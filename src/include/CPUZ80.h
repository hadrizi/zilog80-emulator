#pragma once
#include <vector>
#include <string>
#include <map>

#include "core.h"

class GameBoy;

class CPUZ80
{
public:
	CPUZ80();
	~CPUZ80();

	inline void connect_device(GameBoy* instance) { gb = instance; };
	void clock();
	std::map<H_WORD, std::string> disassemble(H_WORD, H_WORD);
	void reset(); // Resets CPU according to documentation
	bool complete();
public:
	/*
	FLAGS
	Flag register(F) consists of the following bits
	7 6 5 4 3 2 1 0
	Z N H C 0 0 0 0

	Zero Flag (Z):
	This bit is set when the result of a math operation
	is zero or two values match when using the CP
	instruction.

	Subtract Flag (N):
	This bit is set if a subtraction was performed in the
	last math instruction.

	Half Carry Flag (H):
	This bit is set if a carry occurred from the lower
	nibble in the last math operation.

	Carry Flag (C):
	This bit is set if a carry occurred from the last
	math operation or if register A is the smaller value
	when executing the CP instruction.

	As Game Boy CPU is not the exact replica of Zilog 80 CPU
	it only has 4 flags, when Z80 had 8 of them
*/
	enum FLAGS
	{
		Z = (1 << 7), // Zero Flag
		N = (1 << 6), // Subtract Flag
		H = (1 << 5), // Half Carry Flag
		C = (1 << 4)  // Carry Flag
	};

	/*
		Z80 CPU has eight 8-bit registers and two 16-bit registers
		However some instructions allows to use them as 16-bit registers in pairing

		16bit Hi   Lo   Name/Function
		AF    A    F    Accumulator & Flags
		BC    B    C    BC
		DE    D    E    DE
		HL    H    L    HL
		SP    -    -    Stack Pointer
		PC    -    -    Program Counter/Pointer

		Register structure uses union to imitate this behavior
	*/

	Register AF = 0x0000;
	Register BC = 0x0000;
	Register DE = 0x0000;
	Register HL = 0x0000;

	Register PC = 0x0000; // Program Counter - points to the next instruction to be executed
	Register SP = 0x0000; // Stack Pointer - points to the current stack position
private:
	H_BYTE* fetched8_ptr  = nullptr; // This custom register is used by Data Functions to store 8-bit fetched data
	H_WORD* fetched16_ptr = nullptr; // This custom register is used by Data Functions to store 16-bit fetched data
	H_WORD  temp		    = 0x0000;  // A buffer register. Just for case
	H_BYTE  opcode        = 0x00;    // Instruction byte
	H_BYTE  cycles        = 0;	   // Counts how many cycles has remaining
	H_DWORD clock_count   = 0;       // Counts how many cycles have passed. Emulator doesn't use it's only foe debugging

	// GameBoy instance
	GameBoy* gb = nullptr;
	void    write(H_WORD, H_BYTE);
	H_BYTE  read(H_WORD);
	H_BYTE* read_ptr(H_WORD);
	void    write(Register, H_BYTE);
	H_BYTE  read(Register);
	H_BYTE* read_ptr(Register);

	struct INSTRUCTION
	{
		std::string name;
		void (CPUZ80::* op_func)(void) = nullptr;
		void (CPUZ80::* data_func)(void) = nullptr;
		H_BYTE cycles = 0;
	};
	std::vector<INSTRUCTION> opcodes;
	std::vector<INSTRUCTION> prefixes;

private:
	// Functions to manipulate F register
	H_BYTE get_flag(FLAGS);
	void set_flag(FLAGS, bool);
	void reset_flag(FLAGS);

	inline void inc_PC(int k = 1) { PC = PC + 1 * k; }
	inline void inc_SP(int k = 1) { SP = SP + 1 * k; }
	inline void dec_SP(int k = 1) { SP = SP - 1 * k; }

	/*
		CPU Functions
		These functions are not aprt of the original Game Boy CPU
		and they don't have opcodes
		I implemented them just to sophisticate realization of opcodes

		TODO add templates
	*/

	void CPU_REG_LOAD  (Register&, H_WORD);			 // Loads data to register
	void CPU_MEM_LOAD  (H_WORD, H_BYTE);				 // Loads data to memory
	void CPU_MEM_LOAD  (Register&, H_BYTE);			 // Loads data to memory
	void CPU_ACC_ADD   (H_BYTE);					     // Adds data to accumulator register(A)
	void CPU_HL_ADD    (H_WORD);					     // Adds data to HL register(16-bit)
	void CPU_SP_ADD	   (H_BYTE);					     // Adds data to SP register(8-bit)
	void CPU_ACC_SUB   (H_BYTE, bool compare = false); // Subtracts data from accumulator register(A). It is also compare function
	void CPU_ACC_AND   (H_BYTE);					     // Bitwise AND with accumulator register(A)
	void CPU_ACC_OR    (H_BYTE);					     // Bitwise OR with accumulator register(A)
	void CPU_ACC_XOR   (H_BYTE);					     // Bitwise XOR with accumulator register(A)
	void CPU_ACC_FLIP  ();							 // Flips all bits of accumulator register(A)
	void CPU_16REG_INC (H_WORD*);						 // Increments 16-bit register
	void CPU_8REG_INC  (H_BYTE*);				         // Increments 8-bit register
	void CPU_16REG_DEC (H_WORD*);						 // Decrements 16-bit register
	void CPU_8REG_DEC  (H_BYTE*);				         // Decrements 8-bit register
	void CPU_8REG_SWAP (H_BYTE*);				         // Swaps 8-bit register nibbles
	void CPU_16REG_SWAP(H_WORD*);				         // Swaps 16-bit register nibbles. Not used
	bool CPU_TEST_BIT  (H_BYTE,  size_t);		         // Checks if specific bit set
	void CPU_SET_BIT   (H_BYTE*, size_t);		         // Sets specific bit
	void CPU_RESET_BIT (H_BYTE*, size_t);		         // Resets specific bit
	void CPU_8REG_RL   (H_BYTE*);				         // Rotates 8-bit register left
	void CPU_8REG_RLC  (H_BYTE*);				         // Rotates 8-bit register left. Old bit 7 to C flag 
	void CPU_8REG_RR   (H_BYTE*);				         // Rotates 8-bit register right
	void CPU_8REG_RRC  (H_BYTE*);				         // Rotates 8-bit register right. Old bit 0 to C flag
	void CPU_8REG_SLA  (H_BYTE*);				         // Shifts arithmetically 8-bit register left. Old bit 7 to C flag
	void CPU_8REG_SRA  (H_BYTE*);				         // Shifts arithmetically 8-bit register right. Old bit 0 to C flag 
	void CPU_8REG_SRL  (H_BYTE*);				         // Shifts logically 8-bit register right. MSB set to 0. Old bit 7 to C flag 
	void CPU_PUSH_8    (H_BYTE);				         // Pushes 8-bit value onto stack. SP is decremented once 
	void CPU_PUSH_16   (H_WORD);				         // Pushes 16-bit value onto stack. SP is decremented twice 
	H_BYTE CPU_POP_8	   ();							 // Pops 8-bit value from stack. SP is incremented once
	H_WORD CPU_POP_16	   ();							 // Pops 16-bit value from stack. SP is incremented twice 


	/* 
		Data Functions
		I didn't know how to implement parameters functionality
		so I came up with the idea of Data Functions.

		They are pretty similar to NES Address Modes.
		They take data from specific source and put its reference to the fetched pointer register 
		or to the temp register
	*/

	// 8-bit Data Functions============================================================================

	void dimm_8();	// Immediate 8-bit data function. It fetches data from (PC)
	void da();		// A register data function. It fetches A register
	void db();		// B register data function. It fetches B register
	void dc();		// C register data function. It fetches C register
	void dd();		// D register data function. It fetches D register
	void de();		// E register data function. It fetches E register
	void dh();		// H register data function. It fetches H register
	void dl();		// L register data function. It fetches L register

	void b0();		// Bit data function. It fetches 00000001b
	void b1();		// Bit data function. It fetches 00000010b
	void b2();		// Bit data function. It fetches 00000100b
	void b3();		// Bit data function. It fetches 00001000b
	void b4();		// Bit data function. It fetches 00010000b
	void b5();		// Bit data function. It fetches 00100000b
	void b6();		// Bit data function. It fetches 01000000b
	void b7();		// Bit data function. It fetches 10000000b

	void mimm_16(); // Immidiate memory address data function. It fetches data from (nn)
	void mbc();		// BC memory address data function. It fetches data from (BC)
	void mde();		// DE memory address data function. It fetches data from (DE)
	void mhl();		// HL memory address data function. It fetches data from (HL)
	void mFF00c();	// Specific  memory address data function. It fetches data from (0xFF00 + C)
	void mFF00n();	// Immidiate specific memory address data function. It takes fetches from (0xFF00 + n)

	// =================================================================================================
	
	// 16-bit Data Functions============================================================================

	void dimm_16(); // Immediate 16-bit data function. It fetches data from ((PC) << 8) | (PC + 1))
	void daf();		// AF register data function. It fetches AF register
	void dbc();		// BC register data function. It fetches BC register
	void dde();		// DE register data function. It fetches DE register
	void dhl();		// HL register data function. It fetches HL register
	void dsp(); 	// SP register data function. It fetches SP
	void dspn();	// SP register data function. It fetches SP+n

	//void sp_16();	// Stack data function. It fetches data from ((SP) << 8) | (SP + 1))

	// =================================================================================================

	// Misc Data Functions==============================================================================
	
	void dnop(); // Empty data function. It fetches nothing
	
	// =================================================================================================

	// Opcodes Instructions=============================================================================

	// Load instructions
	void LD_A();   void LD_B();   void LD_C();   void LD_D(); 
	void LD_E();   void LD_H();   void LD_L();   void LDD_A();
	void LDI_A();  void LD_BC();  void LD_DE();  void LD_HL();	
	void LD_SP();  void LDHL();   void PUSH();	 void POP();
	
	void LD_M_BC();    void LD_M_DE();  void LD_M_HL();  void LD_M_NN(); 
	void LD_M_FFFOC(); void LDD_M_HL(); void LDI_M_HL(); void LDH_M();

	// ALU instructions
	void ADD_A();  void ADC();    void SUB();    void SBC(); 
	void AND();    void OR();     void XOR();    void CP();
	void INC_8();  void DEC_8();  void ADD_HL(); void ADD_SP();
	void INC_16(); void DEC_16();

	// Misc instructions
	void SWAP(); void DAA(); void CPL();    void CCF();
	void SCF();  void NOP(); void HALT();   void STOP();
	void DI();   void EI();  void PREFIX();

	// Rotate and Shift instructions
	void RLCA(); void RLA(); void RRCA(); void RRA();
	void RLC();  void RL();  void RRC();  void RR();
	void SLA();  void SRA(); void SRL();

	// Bit instructions
	void BIT_A(); void BIT_B(); void BIT_C(); void BIT_D();
	void BIT_E(); void BIT_H(); void BIT_L(); void BIT_M_HL();

	void SET_A(); void SET_B(); void SET_C(); void SET_D();
	void SET_E(); void SET_H(); void SET_L(); void SET_M_HL();

	void RES_A(); void RES_B(); void RES_C(); void RES_D();
	void RES_E(); void RES_H(); void RES_L(); void RES_M_HL();

	// Jump instructions
	void JP();   void JPNZ(); void JPZ();  void JPNC();
	void JPC();  void JR();   void JRNZ(); void JRZ();
	void JRNC(); void JRC();

	// Call instructions
	void CALL();   void CALL_NZ(); void CALL_Z(); void CALL_NC();
	void CALL_C();

	// Restart instructions
	void RST_00(); void RST_08(); void RST_10(); void RST_18();
	void RST_20(); void RST_28(); void RST_30(); void RST_38();

	// Return instructions
	void RET();   void RET_NZ(); void RET_Z(); void RET_NC();
	void RET_C(); void RETI();
	
	// Unknown instruction
	void XXX();

	// =================================================================================================
};

