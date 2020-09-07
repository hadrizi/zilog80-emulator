#include "CPUZ80.h"
#include "GameBoy.h"

CPUZ80::CPUZ80()
{
	using h = CPUZ80;

	opcodes =
	{
		/*0*/  									  /*1*/ 								     /*2*/									        /*3*/								       /*4*/									  /*5*/								     /*6*/						     		   /*7*/								   /*8*/									 /*9*/								  /*A*/										  /*B*/							              /*C*/									  /*D*/									 /*E*/							   /*F*/
/*00*/	{"NOP",		&h::NOP,	 &h::dnop,    4}, {"LD BC",   &h::LD_BC,   &h::dimm_16, 12}, {"LD (BC)",  &h::LD_M_BC,	  &h::da,	    8}, {"INC",		&h::INC_16,  &h::dbc,	   8}, {"INC",     &h::INC_8,	&h::db,		  4}, {"DEC",     &h::DEC_8,   &h::db,	 4}, {"LD B",    &h::LD_B,	  &h::dimm_8,  8}, {"RLCA",    &h::RLCA,	&h::dnop,  4}, {"LD",	   &h::LD_M_NN, &h::dsp,	20}, {"ADD HL", &h::ADD_HL, &h::dbc,  8}, {"LD A",	  &h::LD_A,	   &h::mbc,		 8}, {"DEC",		&h::DEC_16, &h::dbc,	 8}, {"INC",    &h::INC_8,  &h::dc,	      4}, {"DEC",   &h::DEC_8, &h::dc,		 4}, {"LD C",  &h::LD_C, &h::dimm_8, 8}, {"RRCA",    &h::RRCA,   &h::dnop,  4}, /*00*/
/*10*/	{"STOP",	&h::STOP,	 &h::dnop,    4}, {"LD DE",   &h::LD_DE,   &h::dimm_16, 12}, {"LD (DE)",  &h::LD_M_DE,	  &h::da,	    8}, {"INC",		&h::INC_16,  &h::dde,	   8}, {"INC",     &h::INC_8,	&h::dd,		  4}, {"DEC",     &h::DEC_8,   &h::dd,	 4}, {"LD D",    &h::LD_D, 	  &h::dimm_8,  8}, {"RLA",     &h::RLA,	    &h::dnop,  4}, {"JR",	   &h::JR,		&h::dimm_8,  8}, {"ADD HL", &h::ADD_HL, &h::dde,  8}, {"LD A",	  &h::LD_A,	   &h::mde,		 8}, {"DEC",		&h::DEC_16, &h::dde,	 8}, {"INC",    &h::INC_8,  &h::de,	      4}, {"DEC",   &h::DEC_8, &h::de,		 4}, {"LD E",  &h::LD_E, &h::dimm_8, 8}, {"RRA",	 &h::RRA,    &h::dnop,  4}, /*10*/
/*20*/	{"JR NZ",	&h::JRNZ,	 &h::dimm_8,  8}, {"LD HL",   &h::LD_HL,   &h::dimm_16, 12}, {"LDI (HL)", &h::LDI_M_HL,	  &h::da,	    8}, {"INC",		&h::INC_16,  &h::dhl,	   8}, {"INC",	   &h::INC_8,	&h::dh,		  4}, {"DEC",     &h::DEC_8,   &h::dh,	 4}, {"LD H",	 &h::LD_H,	  &h::dimm_8,  8}, {"DAA",     &h::DAA,	    &h::dnop,  4}, {"JR Z",    &h::JRZ,		&h::dimm_8,	 8}, {"ADD HL", &h::ADD_HL, &h::dhl,  8}, {"LDI A",	  &h::LDI_A,   &h::mhl,		 8}, {"DEC",		&h::DEC_16, &h::dhl,	 8}, {"INC",    &h::INC_8,  &h::dl,	      4}, {"DEC",   &h::DEC_8, &h::dl,		 4}, {"LD L",  &h::LD_L, &h::dimm_8, 8}, {"CPL",	 &h::CPL,    &h::dnop,  4}, /*20*/
/*30*/	{"JR NC",	&h::JRNC,	 &h::dimm_8,  8}, {"LD SP",   &h::LD_SP,   &h::dimm_16, 12}, {"LDD (HL)", &h::LDD_M_HL,	  &h::da,	    8}, {"INC",		&h::INC_16,  &h::dsp,	   8}, {"INC",     &h::INC_8,	&h::mhl,     12}, {"DEC",     &h::DEC_8,   &h::mhl, 12}, {"LD (HL)", &h::LD_M_HL, &h::dimm_8, 12}, {"SCF",     &h::SCF,	    &h::dnop,  4}, {"JR C",    &h::JRC,		&h::dimm_8,	 8}, {"ADD HL", &h::ADD_HL, &h::dsp,  8}, {"LDD A",	  &h::LDD_A,   &h::mhl,		 8}, {"DEC",		&h::DEC_16, &h::dsp,	 8}, {"INC",	&h::INC_8,  &h::da,	      4}, {"DEC",	&h::DEC_8, &h::da,		 4}, {"LD A",  &h::LD_A, &h::dimm_8, 8}, {"CCF",	 &h::CCF,    &h::dnop,  4}, /*30*/
/*40*/	{"LD B",	&h::LD_B,	 &h::db,	  4}, {"LD B",    &h::LD_B,	   &h::dc,		 4}, {"LD B",	  &h::LD_B,		  &h::dd,	    4}, {"LD B",	&h::LD_B,	 &h::de,	   4}, {"LD B",    &h::LD_B,	&h::dh,		  4}, {"LD B",    &h::LD_B,	   &h::dl,	 4}, {"LD B",    &h::LD_B,	  &h::mhl,	   8}, {"LD B",    &h::LD_B,    &h::da,	   4}, {"LD C",    &h::LD_C,	&h::db,		 4}, {"LD C",	&h::LD_C,	&h::dc,	  4}, {"LD C",	  &h::LD_C,	   &h::dd,		 4}, {"LD C",		&h::LD_C,	&h::de,		 4}, {"LD C",	&h::LD_C,	&h::dh,	      4}, {"LD C",  &h::LD_C,  &h::dl,       4}, {"LD C",  &h::LD_C, &h::mhl,	 8}, {"LD C",	 &h::LD_C,   &h::da,	4}, /*40*/
/*50*/	{"LD D",	&h::LD_D,	 &h::db,	  4}, {"LD D",    &h::LD_D,	   &h::dc,		 4}, {"LD D",	  &h::LD_D,		  &h::dd,	    4}, {"LD D",	&h::LD_D,	 &h::de,	   4}, {"LD D",    &h::LD_D,	&h::dh,		  4}, {"LD D",	  &h::LD_D,	   &h::dl,	 4}, {"LD D",    &h::LD_D,	  &h::mhl,	   8}, {"LD D",	   &h::LD_D,	&h::da,	   4}, {"LD E",    &h::LD_E,	&h::db,		 4}, {"LD E",	&h::LD_E,	&h::dc,	  4}, {"LD E",	  &h::LD_E,	   &h::dd,		 4}, {"LD E",		&h::LD_E,	&h::de,		 4}, {"LD E",	&h::LD_E,	&h::dh,	      4}, {"LD E",  &h::LD_E,  &h::dl,		 4}, {"LD E",  &h::LD_E, &h::mhl,	 8}, {"LD E",	 &h::LD_E,   &h::da,	4}, /*50*/
/*60*/	{"LD H",	&h::LD_H,	 &h::db,	  4}, {"LD H",	  &h::LD_H,	   &h::dc,		 4}, {"LD H",	  &h::LD_H,		  &h::dd,	    4}, {"LD H",    &h::LD_H,	 &h::de,	   4}, {"LD H",    &h::LD_H,	&h::dh,		  4}, {"LD H",    &h::LD_H,	   &h::dl,	 4}, {"LD H",    &h::LD_H,	  &h::mhl,	   8}, {"LD H",	   &h::LD_H,	&h::da,	   4}, {"LD L",    &h::LD_L,	&h::db,		 4}, {"LD L",	&h::LD_L,	&h::dc,	  4}, {"LD L",	  &h::LD_L,	   &h::dd,		 4}, {"LD L",		&h::LD_L,	&h::de,		 4}, {"LD L",   &h::LD_L,	&h::dh,	      4}, {"LD L",  &h::LD_L,  &h::dl,		 4}, {"LD E",  &h::LD_L, &h::mhl,	 8}, {"LD L",	 &h::LD_L,   &h::da,	4}, /*60*/
/*70*/	{"LD (HL)", &h::LD_M_HL, &h::db,	  8}, {"LD (HL)", &h::LD_M_HL, &h::dc,		 8}, {"LD (HL)",  &h::LD_M_HL,	  &h::dd,	    8}, {"LD (HL)", &h::LD_M_HL, &h::de,	   8}, {"LD (HL)", &h::LD_M_HL,	&h::dh,		  4}, {"LD (HL)", &h::LD_M_HL, &h::dl,	 8}, {"HALT",    &h::HALT,	  &h::dnop,	   4}, {"LD (HL)", &h::LD_M_HL, &h::da,	   8}, {"LD A",    &h::LD_A,	&h::db,		 4}, {"LD A",	&h::LD_A,	&h::dc,	  4}, {"LD A",	  &h::LD_A,	   &h::dd,		 4}, {"LD A",		&h::LD_A,	&h::de,		 4}, {"LD A",	&h::LD_A,	&h::dh,	      4}, {"LD A",  &h::LD_A,  &h::dl,		 4}, {"LD A",  &h::LD_A, &h::mhl,	 8}, {"LD A",	 &h::LD_A,   &h::da,	4}, /*70*/
/*80*/	{"ADD A",	&h::ADD_A,	 &h::db,	  4}, {"ADD A",   &h::ADD_A,   &h::dc,		 4}, {"ADD A",	  &h::ADD_A,	  &h::dd,	    4}, {"ADD A",	&h::ADD_A,   &h::de,	   4}, {"ADD A",   &h::ADD_A,	&h::dh,		  4}, {"ADD A",   &h::ADD_A,   &h::dl,	 4}, {"ADD A",   &h::ADD_A,	  &h::mhl,	   8}, {"ADD A",   &h::ADD_A,   &h::da,	   4}, {"ADC A",   &h::ADC,		&h::db,		 4}, {"ADC A",  &h::ADC,	&h::dc,	  4}, {"ADC A",   &h::ADC,	   &h::dd,		 4}, {"ADC A",		&h::ADC,	&h::de,		 4}, {"ADC A",  &h::ADC,	&h::dh,	      4}, {"ADC A", &h::ADC,   &h::dl,		 4}, {"ADC A", &h::ADC,  &h::mhl,	 8}, {"ADC A",   &h::ADC,    &h::da,	4}, /*80*/
/*90*/	{"SUB",		&h::SUB,	 &h::db,	  4}, {"SUB",     &h::SUB,	   &h::dc,		 4}, {"SUB",	  &h::SUB,		  &h::dd,	    4}, {"SUB",		&h::SUB,	 &h::de,	   4}, {"SUB",     &h::SUB,		&h::dh,		  4}, {"SUB",     &h::SUB,	   &h::dl,	 4}, {"SUB",     &h::SUB,	  &h::mhl,	   8}, {"SUB",     &h::SUB,	    &h::da,	   4}, {"SBC A",   &h::SBC,		&h::db,		 4}, {"SBC A",  &h::SBC,	&h::dc,	  4}, {"SBC A",   &h::SBC,	   &h::dd,		 4}, {"SBC A",		&h::SBC,	&h::de,		 4}, {"SBC A",  &h::SBC,	&h::dh,	      4}, {"SBC A", &h::SBC,   &h::dl,		 4}, {"SBC A", &h::SBC,  &h::mhl,	 8}, {"SBC A",   &h::SBC,    &h::da,	4}, /*90*/
/*A0*/	{"AND",		&h::AND,	 &h::db,	  4}, {"AND",	  &h::AND,	   &h::dc,		 4}, {"AND",	  &h::AND,		  &h::dd,	    4}, {"AND",		&h::AND,	 &h::de,	   4}, {"AND",     &h::AND,		&h::dh,		  4}, {"AND",     &h::AND,	   &h::dl,	 4}, {"AND",     &h::AND,	  &h::mhl,	   8}, {"AND",     &h::AND,	    &h::da,	   4}, {"XOR",     &h::XOR,		&h::db,		 4}, {"XOR",	&h::XOR,	&h::dc,   4}, {"XOR",	  &h::XOR,	   &h::dd,		 4}, {"XOR",		&h::XOR,	&h::de,		 4}, {"XOR",    &h::XOR,	&h::dh,	      4}, {"XOR",	&h::XOR,   &h::dl,		 4}, {"XOR",   &h::XOR,  &h::mhl,	 8}, {"XOR",	 &h::XOR,    &h::da,	4}, /*A0*/
/*B0*/	{"OR",		&h::OR,	     &h::db,	  4}, {"OR",      &h::OR,	   &h::dc,		 4}, {"OR",		  &h::OR,		  &h::dd,	    4}, {"OR",		&h::OR,	     &h::de,	   4}, {"OR",	   &h::OR,		&h::dh,		  4}, {"OR",      &h::OR,	   &h::dl,	 4}, {"OR",      &h::OR,	  &h::mhl,	   8}, {"OR",	   &h::OR,	    &h::da,	   4}, {"CP",      &h::CP,		&h::db,		 4}, {"CP",		&h::CP,		&h::dc,	  4}, {"CP",	  &h::CP,	   &h::dd,		 4}, {"CP",			&h::CP,		&h::de,	     4}, {"CP",		&h::CP,		&h::dh,		  4}, {"CP",	&h::CP,    &h::dl,		 4}, {"CP",	   &h::CP,   &h::mhl,	 8}, {"CP",		 &h::CP,	 &h::da,	4}, /*B0*/
/*C0*/	{"RET NZ",	&h::RET_NZ,  &h::dnop,	  8}, {"POP",	  &h::POP,	   &h::dbc,		12}, {"JP NZ",	  &h::JPNZ,		  &h::dimm_16, 12}, {"JP",		&h::JP,	     &h::dimm_16, 12}, {"CALL NZ", &h::CALL_NZ,	&h::dimm_16, 12}, {"PUSH",    &h::PUSH,	   &h::dbc, 16}, {"ADD A",   &h::ADD_A,	  &h::dimm_8,  8}, {"RST $00", &h::RST_00,  &h::dnop, 32}, {"RET Z",   &h::RET_Z,	&h::dnop,	 8}, {"RET",	&h::RET,	&h::dnop, 8}, {"JP Z",	  &h::JPZ,	   &h::dimm_16, 12}, {"PREFIX $CB", &h::PREFIX, &h::dimm_8,  4}, {"CALL Z", &h::CALL_Z, &h::dimm_16, 12}, {"CALL",  &h::CALL,  &h::dimm_16, 12}, {"ADC A", &h::ADC,  &h::dimm_8, 8}, {"RST $08", &h::RST_08, &h::dnop, 32}, /*C0*/
/*D0*/	{"RET NC",	&h::RET_NC,  &h::dnop,	  8}, {"POP",	  &h::POP,	   &h::dde,		12}, {"JP NC",	  &h::JPNC,		  &h::dimm_16, 12}, {"???",		&h::XXX,	 &h::dnop,	  00}, {"CALL NC", &h::CALL_NC,	&h::dimm_16, 12}, {"PUSH",    &h::PUSH,	   &h::dde,	16}, {"SUB",     &h::SUB,	  &h::dimm_8,  8}, {"RST $10", &h::RST_10,  &h::dnop, 32}, {"RET C",   &h::RET_C,	&h::dnop,	 8}, {"RETI",	&h::RETI,	&h::dnop, 8}, {"JP D",	  &h::JPC,	   &h::dimm_16, 12}, {"???",		&h::XXX,	&h::dnop,   00}, {"CALL C", &h::CALL_C, &h::dimm_16, 12}, {"???",	&h::XXX,   &h::dnop,	00}, {"SBC A", &h::SBC,  &h::dimm_8, 8}, {"RST $18", &h::RST_18, &h::dnop, 32}, /*D0*/
/*E0*/	{"LDH (n)", &h::LDH_M,	 &h::da,	 12}, {"POP",	  &h::POP,	   &h::dhl,		12}, {"LD (C)",	  &h::LD_M_FFFOC, &h::da,	    8}, {"???",		&h::XXX,	 &h::dnop,	  00}, {"???",     &h::XXX,		&h::dnop,	 00}, {"PUSH",    &h::PUSH,	   &h::dhl, 16}, {"AND",     &h::AND,	  &h::dimm_8,  8}, {"RST $20", &h::RST_20,  &h::dnop, 32}, {"ADD SP",  &h::ADD_SP,	&h::dimm_8, 16}, {"JP",		&h::JP,		&h::dhl,  4}, {"LD",	  &h::LD_M_NN, &h::da,		16}, {"???",		&h::XXX,	&h::dnop,   00}, {"???",    &h::XXX,	&h::dnop,	 00}, {"???",	&h::XXX,   &h::dnop, 	00}, {"XOR",   &h::XOR,  &h::dimm_8, 8}, {"RST $28", &h::RST_28, &h::dnop, 32}, /*E0*/
/*F0*/	{"LDH A",	&h::LD_A,	 &h::mFF00n, 12}, {"POP",	  &h::POP,	   &h::daf,		12}, {"LD A",	  &h::LD_A,		  &h::mFF00c,   8}, {"DI",		&h::DI,	     &h::dnop,	   4}, {"???",     &h::XXX,		&h::dnop,	 00}, {"PUSH",    &h::PUSH,	   &h::daf, 16}, {"OR",      &h::OR,	  &h::dimm_8,  8}, {"RST $30", &h::RST_30,  &h::dnop, 32}, {"LDHL",    &h::LDHL,	&h::dspn,	12}, {"LD SP",	&h::LD_SP,  &h::dhl,  8}, {"LD A",	  &h::LD_A,	   &h::mimm_16, 16}, {"EI",			&h::EI,		&h::dnop,    4}, {"???",    &h::XXX,	&h::dnop,	 00}, {"???",	&h::XXX,   &h::dnop,	00}, {"CP",	   &h::CP,   &h::dimm_8, 8}, {"RST $38", &h::RST_38, &h::dnop, 32}  /*F0*/
	};	
	prefixes =
	{
		/*0*/  							/*1*/							/*2*/							/*3*/							/*4*/							/*5*/							/*6*/								 /*7*/							 /*8*/							/*9*/						   /*A*/						  /*B*/							 /*C*/							/*D*/						   /*E*/							   /*F*/
/*00*/	{"RLC",  &h::RLC,	&h::db, 8}, {"RLC",  &h::RLC,   &h::dc, 8}, {"RLC",  &h::RLC,   &h::dd, 8}, {"RLC",  &h::RLC,   &h::de, 8}, {"RLC",  &h::RLC,   &h::dh, 8}, {"RLC",  &h::RLC,	&h::dl, 8}, {"RLC",  &h::RLC,	   &h::mhl, 16}, {"RLC",  &h::RLC,	 &h::da, 8}, {"RRC", &h::RRC,	&h::db, 8}, {"RRC", &h::RRC,   &h::dc, 8}, {"RRC", &h::RRC,	  &h::dd, 8}, {"RRC", &h::RRC,	 &h::de, 8}, {"RRC", &h::RRC,	&h::dh, 8}, {"RRC", &h::RRC,   &h::dl, 8}, {"RRC", &h::RRC,		 &h::mhl, 16}, {"RRC", &h::RRC,	  &h::da, 8},
/*10*/	{"RL",   &h::RL,	&h::db, 8}, {"RL",   &h::RL,    &h::dc, 8}, {"RL",   &h::RL,    &h::dd, 8}, {"RL",   &h::RL,    &h::de, 8}, {"RL",   &h::RL,    &h::dh, 8}, {"RL",   &h::RL,	&h::dl, 8}, {"RL",   &h::RL,	   &h::mhl, 16}, {"RL",   &h::RL,	 &h::da, 8}, {"RR",  &h::RR,	&h::db, 8}, {"RR",  &h::RR,    &h::dc, 8}, {"RR",  &h::RR,	  &h::dd, 8}, {"RR",  &h::RR,	 &h::de, 8}, {"RR",	 &h::RR,	&h::dh, 8}, {"RR",  &h::RR,    &h::dl, 8}, {"RR",  &h::RR,		 &h::mhl, 16}, {"RR",  &h::RR,	  &h::da, 8},
/*20*/	{"SLA",  &h::SLA,	&h::db, 8}, {"SLA",	 &h::SLA,   &h::dc, 8}, {"SLA",  &h::SLA,   &h::dd, 8}, {"SLA",  &h::SLA,   &h::de, 8}, {"SLA",  &h::SLA,   &h::dh, 8}, {"SLA",  &h::SLA,   &h::dl, 8}, {"SLA",  &h::SLA,	   &h::mhl, 16}, {"SLA",  &h::SLA,	 &h::da, 8}, {"SRA", &h::SRA,	&h::db, 8}, {"SRA", &h::SRA,   &h::dc, 8}, {"SRA", &h::SRA,	  &h::dd, 8}, {"SRA", &h::SRA,	 &h::de, 8}, {"SRA", &h::SRA,	&h::dh, 8}, {"SRA", &h::SRA,   &h::dl, 8}, {"SRA", &h::SRA,		 &h::mhl, 16}, {"SRA", &h::SRA,	  &h::da, 8},
/*30*/	{"SWAP", &h::SWAP,	&h::db, 8}, {"SWAP", &h::SWAP,  &h::dc, 8}, {"SWAP", &h::SWAP,  &h::dd, 8}, {"SWAP", &h::SWAP,  &h::de, 8}, {"SWAP", &h::SWAP,  &h::dh, 8}, {"SWAP", &h::SWAP,  &h::dl, 8}, {"SWAP", &h::SWAP,	   &h::mhl, 16}, {"SWAP", &h::SWAP,  &h::da, 8}, {"SRL", &h::SRL,	&h::db, 8}, {"SRL", &h::SRL,   &h::dc, 8}, {"SRL", &h::SRL,	  &h::dd, 8}, {"SRL", &h::SRL,	 &h::de, 8}, {"SRL", &h::SRL,	&h::dh, 8}, {"SRL", &h::SRL,   &h::dl, 8}, {"SRL", &h::SRL,		 &h::mhl, 16}, {"SRL", &h::SRL,	  &h::da, 8},
/*40*/	{"BIT",  &h::BIT_B, &h::b0, 8}, {"BIT",	 &h::BIT_C, &h::b0, 8}, {"BIT",  &h::BIT_D, &h::b0, 8}, {"BIT",  &h::BIT_E, &h::b0, 8}, {"BIT",  &h::BIT_H, &h::b0, 8}, {"BIT",  &h::BIT_L, &h::b0, 8}, {"BIT",	 &h::BIT_M_HL, &h::b0,  16}, {"BIT",  &h::BIT_A, &h::b0, 8}, {"BIT", &h::BIT_B, &h::b1, 8}, {"BIT", &h::BIT_C, &h::b1, 8}, {"BIT", &h::BIT_D, &h::b1, 8}, {"BIT", &h::BIT_E, &h::b1, 8}, {"BIT", &h::BIT_H, &h::b1, 8}, {"BIT", &h::BIT_L, &h::b1, 8}, {"BIT", &h::BIT_M_HL, &h::b1,  16}, {"BIT", &h::BIT_A, &h::b1, 8},
/*50*/	{"BIT",  &h::BIT_B, &h::b2, 8}, {"BIT",  &h::BIT_C, &h::b2, 8}, {"BIT",  &h::BIT_D, &h::b2, 8}, {"BIT",  &h::BIT_E, &h::b2, 8}, {"BIT",  &h::BIT_H, &h::b2, 8}, {"BIT",  &h::BIT_L, &h::b2, 8}, {"BIT",  &h::BIT_M_HL, &h::b2,  16}, {"BIT",  &h::BIT_A, &h::b2, 8}, {"BIT", &h::BIT_B, &h::b3, 8}, {"BIT", &h::BIT_C, &h::b3, 8}, {"BIT", &h::BIT_D, &h::b3, 8}, {"BIT", &h::BIT_E, &h::b3, 8}, {"BIT", &h::BIT_H, &h::b3, 8}, {"BIT", &h::BIT_L, &h::b3, 8}, {"BIT", &h::BIT_M_HL, &h::b3,  16}, {"BIT", &h::BIT_A, &h::b3, 8},
/*60*/	{"BIT",  &h::BIT_B, &h::b4, 8}, {"BIT",  &h::BIT_C, &h::b4, 8}, {"BIT",  &h::BIT_D, &h::b4, 8}, {"BIT",  &h::BIT_E, &h::b4, 8}, {"BIT",  &h::BIT_H, &h::b4, 8}, {"BIT",  &h::BIT_L, &h::b4, 8}, {"BIT",  &h::BIT_M_HL, &h::b4,  16}, {"BIT",  &h::BIT_A, &h::b4, 8}, {"BIT", &h::BIT_B, &h::b5, 8}, {"BIT", &h::BIT_C, &h::b5, 8}, {"BIT", &h::BIT_D, &h::b5, 8}, {"BIT", &h::BIT_E, &h::b5, 8}, {"BIT", &h::BIT_H, &h::b5, 8}, {"BIT", &h::BIT_L, &h::b5, 8}, {"BIT", &h::BIT_M_HL, &h::b5,  16}, {"BIT", &h::BIT_A, &h::b5, 8},
/*70*/	{"BIT",  &h::BIT_B, &h::b6, 8}, {"BIT",  &h::BIT_C, &h::b6, 8}, {"BIT",  &h::BIT_D, &h::b6, 8}, {"BIT",  &h::BIT_E, &h::b6, 8}, {"BIT",  &h::BIT_H, &h::b6, 8}, {"BIT",  &h::BIT_L, &h::b6, 8}, {"BIT",  &h::BIT_M_HL, &h::b6,  16}, {"BIT",  &h::BIT_A, &h::b6, 8}, {"BIT", &h::BIT_B, &h::b7, 8}, {"BIT", &h::BIT_C, &h::b7, 8}, {"BIT", &h::BIT_D, &h::b7, 8}, {"BIT", &h::BIT_E, &h::b7, 8}, {"BIT", &h::BIT_H, &h::b7, 8}, {"BIT", &h::BIT_L, &h::b7, 8}, {"BIT", &h::BIT_M_HL, &h::b7,  16}, {"BIT", &h::BIT_A, &h::b7, 8},
/*80*/	{"RES",  &h::RES_B, &h::b0, 8}, {"RES",  &h::RES_C, &h::b0, 8}, {"RES",  &h::RES_D, &h::b0, 8}, {"RES",  &h::RES_E, &h::b0, 8}, {"RES",  &h::RES_H, &h::b0, 8}, {"RES",  &h::RES_L, &h::b0, 8}, {"RES",  &h::RES_M_HL, &h::b0,  16}, {"RES",  &h::RES_A, &h::b0, 8}, {"RES", &h::RES_B, &h::b1, 8}, {"RES", &h::RES_C, &h::b1, 8}, {"RES", &h::RES_D, &h::b1, 8}, {"RES", &h::RES_E, &h::b1, 8}, {"RES", &h::RES_H, &h::b1, 8}, {"RES", &h::RES_L, &h::b1, 8}, {"RES", &h::RES_M_HL, &h::b1,  16}, {"RES", &h::RES_A, &h::b1, 8},
/*90*/	{"RES",  &h::RES_B, &h::b2, 8}, {"RES",  &h::RES_C, &h::b2, 8}, {"RES",  &h::RES_D, &h::b2, 8}, {"RES",  &h::RES_E, &h::b2, 8}, {"RES",  &h::RES_H, &h::b2, 8}, {"RES",  &h::RES_L, &h::b2, 8}, {"RES",  &h::RES_M_HL, &h::b2,  16}, {"RES",  &h::RES_A, &h::b2, 8}, {"RES", &h::RES_B, &h::b3, 8}, {"RES", &h::RES_C, &h::b3, 8}, {"RES", &h::RES_D, &h::b3, 8}, {"RES", &h::RES_E, &h::b3, 8}, {"RES", &h::RES_H, &h::b3, 8}, {"RES", &h::RES_L, &h::b3, 8}, {"RES", &h::RES_M_HL, &h::b3,  16}, {"RES", &h::RES_A, &h::b3, 8},
/*A0*/	{"RES",  &h::RES_B, &h::b4, 8}, {"RES",  &h::RES_C, &h::b4, 8}, {"RES",  &h::RES_D, &h::b4, 8}, {"RES",  &h::RES_E, &h::b4, 8}, {"RES",  &h::RES_H, &h::b4, 8}, {"RES",  &h::RES_L, &h::b4, 8}, {"RES",  &h::RES_M_HL, &h::b4,  16}, {"RES",  &h::RES_A, &h::b4, 8}, {"RES", &h::RES_B, &h::b5, 8}, {"RES", &h::RES_C, &h::b5, 8}, {"RES", &h::RES_D, &h::b5, 8}, {"RES", &h::RES_E, &h::b5, 8}, {"RES", &h::RES_H, &h::b5, 8}, {"RES", &h::RES_L, &h::b5, 8}, {"RES", &h::RES_M_HL, &h::b5,  16}, {"RES", &h::RES_A, &h::b5, 8},
/*B0*/	{"RES",  &h::RES_B, &h::b6, 8}, {"RES",  &h::RES_C, &h::b6, 8}, {"RES",  &h::RES_D, &h::b6, 8}, {"RES",  &h::RES_E, &h::b6, 8}, {"RES",  &h::RES_H, &h::b6, 8}, {"RES",  &h::RES_L, &h::b6, 8}, {"RES",  &h::RES_M_HL, &h::b6,  16}, {"RES",  &h::RES_A, &h::b6, 8}, {"RES", &h::RES_B, &h::b7, 8}, {"RES", &h::RES_C, &h::b7, 8}, {"RES", &h::RES_D, &h::b7, 8}, {"RES", &h::RES_E, &h::b7, 8}, {"RES", &h::RES_H, &h::b7, 8}, {"RES", &h::RES_L, &h::b7, 8}, {"RES", &h::RES_M_HL, &h::b7,  16}, {"RES", &h::RES_A, &h::b7, 8},
/*C0*/	{"SET",  &h::SET_B, &h::b0, 8}, {"SET",  &h::SET_C, &h::b0, 8}, {"SET",  &h::SET_D, &h::b0, 8}, {"SET",  &h::SET_E, &h::b0, 8}, {"SET",  &h::SET_H, &h::b0, 8}, {"SET",  &h::SET_L, &h::b0, 8}, {"SET",  &h::SET_M_HL, &h::b0,  16}, {"SET",  &h::SET_A, &h::b0, 8}, {"SET", &h::SET_B, &h::b1, 8}, {"SET", &h::SET_C, &h::b1, 8}, {"SET", &h::SET_D, &h::b1, 8}, {"SET", &h::SET_E, &h::b1, 8}, {"SET", &h::SET_H, &h::b1, 8}, {"SET", &h::SET_L, &h::b1, 8}, {"SET", &h::SET_M_HL, &h::b1,  16}, {"SET", &h::SET_A, &h::b1, 8},
/*D0*/	{"SET",  &h::SET_B, &h::b2, 8}, {"SET",  &h::SET_C, &h::b2, 8}, {"SET",  &h::SET_D, &h::b2, 8}, {"SET",  &h::SET_E, &h::b2, 8}, {"SET",  &h::SET_H, &h::b2, 8}, {"SET",  &h::SET_L, &h::b2, 8}, {"SET",  &h::SET_M_HL, &h::b2,  16}, {"SET",  &h::SET_A, &h::b2, 8}, {"SET", &h::SET_B, &h::b3, 8}, {"SET", &h::SET_C, &h::b3, 8}, {"SET", &h::SET_D, &h::b3, 8}, {"SET", &h::SET_E, &h::b3, 8}, {"SET", &h::SET_H, &h::b3, 8}, {"SET", &h::SET_L, &h::b3, 8}, {"SET", &h::SET_M_HL, &h::b3,  16}, {"SET", &h::SET_A, &h::b3, 8},
/*E0*/	{"SET",  &h::SET_B, &h::b4, 8}, {"SET",  &h::SET_C, &h::b4, 8}, {"SET",  &h::SET_D, &h::b4, 8}, {"SET",  &h::SET_E, &h::b4, 8}, {"SET",  &h::SET_H, &h::b4, 8}, {"SET",  &h::SET_L, &h::b4, 8}, {"SET",  &h::SET_M_HL, &h::b4,  16}, {"SET",  &h::SET_A, &h::b4, 8}, {"SET", &h::SET_B, &h::b5, 8}, {"SET", &h::SET_C, &h::b5, 8}, {"SET", &h::SET_D, &h::b5, 8}, {"SET", &h::SET_E, &h::b5, 8}, {"SET", &h::SET_H, &h::b5, 8}, {"SET", &h::SET_L, &h::b5, 8}, {"SET", &h::SET_M_HL, &h::b5,  16}, {"SET", &h::SET_A, &h::b5, 8},
/*F0*/	{"SET",  &h::SET_B, &h::b6, 8}, {"SET",  &h::SET_C, &h::b6, 8}, {"SET",  &h::SET_D, &h::b6, 8}, {"SET",  &h::SET_E, &h::b6, 8}, {"SET",  &h::SET_H, &h::b6, 8}, {"SET",  &h::SET_L, &h::b6, 8}, {"SET",  &h::SET_M_HL, &h::b6,  16}, {"SET",  &h::SET_A, &h::b6, 8}, {"SET", &h::SET_B, &h::b7, 8}, {"SET", &h::SET_C, &h::b7, 8}, {"SET", &h::SET_D, &h::b7, 8}, {"SET", &h::SET_E, &h::b7, 8}, {"SET", &h::SET_H, &h::b7, 8}, {"SET", &h::SET_L, &h::b7, 8}, {"SET", &h::SET_M_HL, &h::b7,  16}, {"SET", &h::SET_A, &h::b7, 8}
	};
}

CPUZ80::~CPUZ80()
{

}

std::map<H_WORD, std::string> CPUZ80::disassemble(H_WORD start, H_WORD stop)
{
	H_DWORD addr = start;
	H_BYTE val = 0x00, lo = 0x00, hi = 0x00;
	H_WORD word_val = 0x0000;
	std::map < H_WORD, std::string> map_lines;
	H_WORD line_addr = 0;

	auto hex = [](H_DWORD n, H_BYTE d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	while (addr <= (H_DWORD)stop)
	{
		line_addr = addr;

		std::string line_str = "$" + hex(addr, 4) + ": ";

		H_BYTE d_opcode = gb->read(addr);
		addr++;
		line_str += opcodes[d_opcode].name + " ";

		if (opcodes[d_opcode].op_func == &CPUZ80::LD_M_NN)
		{
			lo = gb->read(addr);
			addr++;
			hi = gb->read(addr);
			addr++;
			line_str += "($" + hex(hi, 2) + hex(lo, 2) + ") ";
		}

		if (opcodes[d_opcode].data_func == &CPUZ80::dimm_8)
		{
			val = gb->read(addr);
			addr++;
			line_str += "$" + hex(val, 2);
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::da)
		{
			line_str += "A";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::db)
		{
			line_str += "B";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dc)
		{
			line_str += "C";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dd)
		{
			line_str += "D";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::de)
		{
			line_str += "E";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dh)
		{
			line_str += "H";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dl)
		{
			line_str += "L";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dimm_16)
		{
			lo = gb->read(addr);
			addr++;
			hi = gb->read(addr);
			addr++;			
			line_str += "$" + hex(hi, 2) + hex(lo, 2);
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::daf)
		{
			line_str += "AF";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dbc)
		{
			line_str += "BC";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dde)
		{
			line_str += "DE";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dhl)
		{
			line_str += "HL";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dsp)
		{
			line_str += "SP";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::dspn)
		{
			val = gb->read(addr);
			addr++;
			line_str += "SP + $" + hex(val, 2);
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mimm_16)
		{
			lo = gb->read(addr);
			addr++;
			hi = gb->read(addr);
			addr++;
			line_str += "($" + hex(hi, 2) + hex(lo, 2) + ")";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mbc)
		{
			line_str += "(BC)";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mde)
		{
			line_str += "(DE)";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mhl)
		{
			line_str += "(HL)";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mFF00c)
		{
			line_str += "($FF00 + C)";
		}
		else if (opcodes[d_opcode].data_func == &CPUZ80::mFF00n)
		{
			val = gb->read(addr);
			addr++;
			line_str += "($FF00 + $" + hex(val, 2) + ")";
		}

		map_lines[line_addr] = line_str;
	}

	return map_lines;
}

void CPUZ80::write(H_WORD addr, H_BYTE data)
{
	gb->write(addr, data);
}

H_BYTE CPUZ80::read(H_WORD addr)
{
	return gb->read(addr);
}

H_BYTE* CPUZ80::read_ptr(H_WORD addr)
{
	return gb->read_ptr(addr);
}

void CPUZ80::write(Register addr, H_BYTE data)
{
	gb->write(addr.reg, data);
}

H_BYTE CPUZ80::read(Register addr)
{
	return gb->read(addr.reg);
}

H_BYTE* CPUZ80::read_ptr(Register addr)
{
	return gb->read_ptr(addr.reg);
}

void CPUZ80::reset()
{
	gb->write(0xFFFF, 0x00);

	//AF = 0x01B0;
	//BC = 0x0013;
	//DE = 0x00D8;
	//HL = 0x014D;
	AF    = 0x00B0;
	BC    = 0x0000;
	DE    = 0x0000;
	//HL    = 0xCAFE;
	HL    = 0x0000;
	SP    = 0xFFFF;
	PC    = 0x0100;

	IME = true;
	PEI = false;
	PDI = false;
	IE = gb->read_ptr(0xFFFF);
	IF = gb->read_ptr(0xFF0F);
}

bool CPUZ80::complete()
{
	return cycles == 0;
}

// One clock cycle of CPU
void CPUZ80::clock()
{
	if (cycles == 0)
	{
		CPU_PENDING_IME();
		opcode = read(PC);
		PC++;

		cycles = opcodes[opcode].cycles;

		(this->*opcodes[opcode].data_func)();
		(this->*opcodes[opcode].op_func)();
	}	

	clock_count++;
	cycles--;

	CPU_PERFORM_INT();
}

// Returns current F register bit status
H_BYTE CPUZ80::get_flag(FLAGS f)
{
	return((AF.lo & f) > 00) ? 1 : 0;
}

// Sets current F register bit status
void CPUZ80::set_flag(FLAGS f, bool condition)
{
	if (condition)
		AF.lo |= f;
	else
		AF.lo &= ~f;
}

// Resets current F register bit status
void CPUZ80::reset_flag(FLAGS f)
{
	set_flag(f, false);
}

// DATA DUNCTIONS
/*	
	As mentioned earlies these functions take data from specific source(register or memory)
	at put its refernece to fetched pointer register. So we don't copy data but manipulate it
	through pointer.
	Further I will describe each function.
*/

// 8-bit Data Immidiate Function
// Immidiate means byte right after opcode
// In our case it is data at (PC) because we have already incremented PC
void CPUZ80::dimm_8()
{
	fetched8_ptr = read_ptr(PC);
	inc_PC();
}

// A Register Data Function
void CPUZ80::da()
{
	fetched8_ptr = &AF.hi;
}

// B Register Data Function
void CPUZ80::db()
{
	fetched8_ptr = &BC.hi;
}

// C Register Data Function
void CPUZ80::dc()
{
	fetched8_ptr = &BC.lo;
}

// D Register Data Function
void CPUZ80::dd()
{
	fetched8_ptr = &DE.hi;
}

// E Register Data Function
void CPUZ80::de()
{
	fetched8_ptr = &DE.lo;
}

// H Register Data Function
void CPUZ80::dh()
{
	fetched8_ptr = &HL.hi;
}

// L Register Data Function
void CPUZ80::dl()
{
	fetched8_ptr = &HL.lo;
}

// First Bit Data Function.
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b0()
{
	fetched8_ptr = nullptr;
	temp = 0;
}

// Second Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b1()
{
	fetched8_ptr = nullptr;
	temp = 1;
}

// Third Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b2()
{
	fetched8_ptr = nullptr;
	temp = 2;
}

// Fourth Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b3()
{
	fetched8_ptr = nullptr;
	temp = 3;
}

// Fifth Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b4()
{
	fetched8_ptr = nullptr;
	temp = 4;
}

// Sixth Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b5()
{
	fetched8_ptr = nullptr;
	temp = 5;
}

// Seventh Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b6()
{
	fetched8_ptr = nullptr;
	temp = 6;
}

// Eighth Bit Data Function
// It doesnt put anything to fetched pointer(actually it resets it)
// but put specific number to temp register
void CPUZ80::b7()
{
	fetched8_ptr = nullptr;
	temp = 7;
}

// 16-bit Memory Immidiate Data Function
// 16-bit immidiate value is value at (PC+1) shifted left by 8 and ORed by (PC). Consider endianess
void CPUZ80::mimm_16()
{
	fetched8_ptr = read_ptr((read(PC + 1) << 8) | read(PC));
	inc_PC(2);
}

// BC Register Memory Data Function
void CPUZ80::mbc()
{
	fetched8_ptr = read_ptr(BC);
}

// DE Register Memory Data Function
void CPUZ80::mde()
{
	fetched8_ptr = read_ptr(DE);
}

// HL Register Memory Data Function
void CPUZ80::mhl()
{
	fetched8_ptr = read_ptr(HL);
}

// Specific Memory Data Function
// It fetches data from (FF00+C)
void CPUZ80::mFF00c()
{
	fetched8_ptr = read_ptr(0xFF00 + BC.lo);
}

// Specific Immidiate Memory Data Function
// It fetches data from (FF00+n)
// n is immidiate 8-bit value
void CPUZ80::mFF00n()
{
	H_BYTE n = read(PC);
	fetched8_ptr = read_ptr(0xFF00 + n);
	inc_PC();
}

// 16-bit Data Immidiate Function
// Immidiate means byte right after opcode
// In this case it is data at (PC+1) shifted left by 8 and ORed by (PC). Consider endianess
// As we cannot store pointer to 16 bit value from memory it will be fetched to temp register
void CPUZ80::dimm_16()
{
	temp = ((read(PC+1) << 8) | read(PC));
	inc_PC(2);
}

// AF Register Data Function
void CPUZ80::daf()
{
	fetched16_ptr = &AF.reg;
}

// BC Register Data Function
void CPUZ80::dbc()
{
	fetched16_ptr = &BC.reg;
}

// DE Register Data Function
void CPUZ80::dde()
{
	fetched16_ptr = &DE.reg;
}

// HL Register Data Function
void CPUZ80::dhl()
{
	fetched16_ptr = &HL.reg;
	temp = HL.reg; // For JP instruction
}

// SP Register Data Function
void CPUZ80::dsp()
{
	fetched16_ptr = &SP.reg;
}

// SP+n Register Data Function
// n is 8-bit immidiate value
// As we got nothing to point to we will store this value in temp register
void CPUZ80::dspn()
{
	H_BYTE n = read(PC);
	temp = SP.reg + n;
	unsigned int v = SP.reg + n;

	set_flag(C, v > 0xFFFF);
	set_flag(H, (SP.reg & 0x000F) + (n & 0x000F) > 0x000F);
	inc_PC();
}

// Empty Data Function
// Although it stated as "empty" in fact it resets all data registers
// So it can be used as Reset Data Function. However I cannot imagine such case
void CPUZ80::dnop()
{
	fetched8_ptr = nullptr;
	fetched16_ptr = nullptr;
	temp = 0x0000;
}

// INSTRUCTIONS

// CPU FUNCTIONS

void CPUZ80::CPU_REG_LOAD(Register& reg, H_WORD data)
{
	reg = data;
}

void CPUZ80::CPU_MEM_LOAD(H_WORD addr, H_BYTE data)
{
	write(addr, data);
}

void CPUZ80::CPU_MEM_LOAD(Register& addr, H_BYTE data)
{
	write(addr, data);
}

void CPUZ80::CPU_ACC_ADD(H_BYTE data)
{
	set_flag(H, ((AF.hi & 0xF) + (data & 0xF)) > 0xF);
	AF.hi += data;
	unsigned int v = AF.hi + data;
	reset_flag(N);
	set_flag(Z, AF.hi == 0);
	set_flag(C, v > 0xFF);
}

void CPUZ80::CPU_ACC_SUB(H_BYTE data, bool compare)
{
	if (compare)
	{
		H_BYTE v = AF.hi + data;

		set_flag(H, ((AF.hi & 0xF)) < (data & 0xF));
		set_flag(C, AF.hi < data);
		reset_flag(N);
		set_flag(Z, v == 0);
	}
	else
	{
		set_flag(H, ((AF.hi & 0xF)) < (data & 0xF));
		set_flag(C, AF.hi < data);
		AF.hi -= data;
		unsigned int v = AF.hi + data;
		reset_flag(N);
		set_flag(Z, AF.hi == 0);
	}

}

void CPUZ80::CPU_ACC_AND(H_BYTE data)
{
	AF.hi &= data;
	reset_flag(N);
	reset_flag(C);
	set_flag(H, true);
	set_flag(Z, AF.hi == 0);
}

void CPUZ80::CPU_ACC_OR(H_BYTE data)
{
	AF.hi |= data;
	reset_flag(N);
	reset_flag(C);
	reset_flag(H);
	set_flag(Z, AF.hi == 0);
}

void CPUZ80::CPU_ACC_XOR(H_BYTE data)
{
	AF.hi ^= data;
	reset_flag(N);
	reset_flag(C);
	reset_flag(H);
	set_flag(Z, AF.hi == 0);
}

void CPUZ80::CPU_16REG_INC(H_WORD* reg)
{
	(*reg)++;
}

void CPUZ80::CPU_8REG_INC(H_BYTE* reg)
{
	reset_flag(N);
	set_flag(H, ((*reg & 0xF) + (1 & 0xF)) > 0xF);
	(*reg)++;
	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_16REG_DEC(H_WORD* reg)
{
	(*reg)--;
}

void CPUZ80::CPU_8REG_DEC(H_BYTE* reg)
{
	set_flag(N, true);
	set_flag(H, ((*reg & 0xF)) < (1 & 0xF));
	(*reg)--;
	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_HL_ADD(H_WORD data)
{
	set_flag(H, ((HL.reg & 0xF) + (data & 0xF)) > 0xF);
	reset_flag(N);
	unsigned int v = HL.reg + data;
	HL = HL + data;
	set_flag(C, v > 0xFFFF);
}

void CPUZ80::CPU_SP_ADD(H_BYTE data)
{
	set_flag(H, ((SP.reg & 0xF) + (data & 0xF)) > 0xF);
	reset_flag(N);
	reset_flag(Z);

	unsigned int v = SP.reg + (H_WORD)data;
	inc_SP(data);

	set_flag(C, v > 0xFFFF);
}

void CPUZ80::CPU_8REG_SWAP(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);
	reset_flag(C);

	*reg = (((*reg & 0xF0) >> 4) | ((*reg & 0x0F) << 4));

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_16REG_SWAP(H_WORD* reg)
{
	*reg = (((*reg & 0xFF00) >> 8) | ((*reg & 0x00FF) << 8));
}

void CPUZ80::CPU_ACC_FLIP()
{
	set_flag(N, true);
	set_flag(H, true);
	AF.hi ^= 0xFF;
}

bool CPUZ80::CPU_TEST_BIT(H_BYTE subject, size_t bit)
{	
	reset_flag(N);
	set_flag(H, true);
	H_BYTE mask = 1 << bit;
	set_flag(Z, (subject & mask) == 0);
	return (subject & mask) > 0 ? true : false;
}

void CPUZ80::CPU_SET_BIT(H_BYTE* subject, size_t bit)
{
	H_BYTE mask = 1 << bit;
	*subject |= mask;
}

void CPUZ80::CPU_RESET_BIT(H_BYTE* subject, size_t bit)
{
	H_BYTE mask = 1 << bit;
	*subject &= ~mask;
}

void CPUZ80::CPU_8REG_RL(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);
	
	H_BYTE old_C = get_flag(C);
	set_flag(C, CPU_TEST_BIT(*reg, 7));

	*reg <<= 1;

	if (old_C == 1)
		CPU_SET_BIT(reg, 0);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_RLC(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	set_flag(C, CPU_TEST_BIT(*reg, 7));

	*reg <<= 1;

	if (get_flag(C) == 1)
		CPU_SET_BIT(reg, 0);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_RR(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	H_BYTE old_C = get_flag(C);
	set_flag(C, CPU_TEST_BIT(*reg, 0));

	*reg >>= 1;

	if (old_C == 1)
		CPU_SET_BIT(reg, 7);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_RRC(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	set_flag(C, CPU_TEST_BIT(*reg, 0));

	*reg <<= 1;

	if (get_flag(C) == 1)
		CPU_SET_BIT(reg, 7);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_SLA(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	set_flag(C, CPU_TEST_BIT(*reg, 7));

	*reg <<= 1;

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_SRA(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	bool msb = CPU_TEST_BIT(*reg, 7);
	set_flag(C, CPU_TEST_BIT(*reg, 0));

	*reg >>= 1;

	if (msb)
		CPU_SET_BIT(reg, 7);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_8REG_SRL(H_BYTE* reg)
{
	reset_flag(N);
	reset_flag(H);

	set_flag(C, CPU_TEST_BIT(*reg, 0));

	*reg >>= 1;
	CPU_RESET_BIT(reg, 7);

	set_flag(Z, *reg == 0);
}

void CPUZ80::CPU_PUSH_8(H_BYTE data)
{
	write(SP, data);
	dec_SP();
}

void CPUZ80::CPU_PUSH_16(H_WORD data)
{
	H_BYTE hi = (data & 0xFF00) >> 8;
	write(SP, hi);
	H_BYTE lo = (data & 0x00FF);
	write(SP - 1, lo);

	dec_SP(2);
}

H_BYTE CPUZ80::CPU_POP_8()
{
	inc_SP();
	return read(SP);
}

H_WORD CPUZ80::CPU_POP_16()
{
	inc_SP(2);

	H_WORD data = (read(SP) << 8) | read(SP - 1);
	return data;
}

void CPUZ80::CPU_SERVICE_INT(size_t i)
{
	CPU_PUSH_16(PC.reg);

	switch (i)
	{
	case 0: PC = 0x0040; break;
	case 1: PC = 0x0048; break;
	case 2: PC = 0x0050; break;
	case 3: PC = 0x0060; break;
	default:
		break;
	}

	IME = false;
	CPU_RESET_BIT(IF, i);
}

void CPUZ80::CPU_PERFORM_INT()
{
	// We check if interupts are allowed globally
	if (IME)
	{
		for (int bit = 0; bit <= 4; bit++)
		{
			// Here we check if specific interup is allowed and requsted
			if (CPU_TEST_BIT(*IF, bit) && CPU_TEST_BIT(*IE, bit))
				CPU_SERVICE_INT(bit);
		}
	}
}

void CPUZ80::CPU_PENDING_IME()
{
	if (PEI && (read(PC - 0x0001) == 0xFB))
	{
		IME = true;
		PEI = false;
	}

	if (PDI && (read(PC - 0x0001) == 0xF3))
	{
		IME = false;
		PDI = false;
	}
}

void CPUZ80::CPU_REQUEST_INT(size_t bit)
{
	CPU_SET_BIT(IF, bit);
}

// 8-BIT LOAD FUNCTIONS
// These functions put some 8-bit data to some source
// Data is taken from Data Registers(feteched8_ptr, fetched16_ptr or temp)

// Loads fetched data to A register
void CPUZ80::LD_A()
{
	H_WORD data = (*fetched8_ptr << 8) | AF.lo;
	CPU_REG_LOAD(AF, data);
}

// Loads fetched data to B register
void CPUZ80::LD_B()
{
	H_WORD data = (*fetched8_ptr << 8) | BC.lo;
	CPU_REG_LOAD(BC, data);
}

// Loads fetched data to C register
void CPUZ80::LD_C()
{
	H_WORD data = (BC.hi << 8) | *fetched8_ptr;
	CPU_REG_LOAD(BC, data);
}

// Loads fetched data to D register
void CPUZ80::LD_D()
{
	H_WORD data = (*fetched8_ptr << 8) | DE.lo;
	CPU_REG_LOAD(DE, data);
}

// Loads fetched data to E register
void CPUZ80::LD_E()
{
	H_WORD data = (DE.hi << 8) | *fetched8_ptr;
	CPU_REG_LOAD(DE, data);
}

// Loads fetched data to H register
void CPUZ80::LD_H()
{
	H_WORD data = (*fetched8_ptr << 8) | HL.lo;
	CPU_REG_LOAD(HL, data);
}

// Loads fetched data to L register
void CPUZ80::LD_L()
{
	H_WORD data = (HL.hi << 8) | *fetched8_ptr;
	CPU_REG_LOAD(HL, data);
}

// Loads fetched data to HL memory address
void CPUZ80::LD_M_HL()
{
	CPU_MEM_LOAD(HL, *fetched8_ptr);
}

// Loads fetched data to BC memory address
void CPUZ80::LD_M_BC()
{
	CPU_MEM_LOAD(BC, *fetched8_ptr);
}

// Loads fetched data to DE memory address
void CPUZ80::LD_M_DE()
{
	CPU_MEM_LOAD(DE, *fetched8_ptr);
}

// Loads fetched data to DE memory address
void CPUZ80::LD_M_NN()
{
	// another one hehe
	if (opcode == 0x08)
	{
		H_BYTE lo = (*fetched16_ptr) & 0x00FF;
		H_BYTE hi = ((*fetched16_ptr) & 0xFF00) >> 8;

		H_WORD nn = ((read(PC + 1) << 8) | read(PC));
		CPU_MEM_LOAD(nn, lo);
		nn++;
		CPU_MEM_LOAD(nn, hi);
		inc_PC(2);
	}
	else
	{
		H_WORD nn = ((read(PC + 1) << 8) | read(PC));
		CPU_MEM_LOAD(nn, *fetched8_ptr);
		inc_PC(2);
	}

}

// Loads fetched data to FF00+C memory address
void CPUZ80::LD_M_FFFOC()
{
	CPU_MEM_LOAD(0xFF00 + BC.lo, *fetched8_ptr);
}

// Loads fetched data to AF memory
// Decrements HL register
void CPUZ80::LDD_A()
{
	H_WORD data = (*fetched8_ptr << 8) | AF.lo;
	CPU_REG_LOAD(AF, data);
	HL--;
}

// Loads fetched data to HL memory address
// Decrements HL register
void CPUZ80::LDD_M_HL()
{
	CPU_MEM_LOAD(HL, *fetched8_ptr);
	HL--;
}

// Loads fetched data to AF memory
// Increments HL register
void CPUZ80::LDI_A()
{
	H_WORD data = (*fetched8_ptr << 8) | AF.lo;
	CPU_REG_LOAD(AF, data);
	HL++;
}

// Loads fetched data to HL memory address
// Increments HL register
void CPUZ80::LDI_M_HL()
{
	CPU_MEM_LOAD(HL, *fetched8_ptr);
	HL++;
}

// Loads fetched data to FF00+n memory address
// n is immidiate 8-bit value
void CPUZ80::LDH_M()
{
	H_BYTE n = read(PC);
	CPU_MEM_LOAD(0xFF00 + n, *fetched8_ptr);
	inc_PC();
}

// Loads fetched data to BC register
void CPUZ80::LD_BC()
{
	CPU_REG_LOAD(BC, temp);
	//inc_PC(2);
}

// Loads fetched data to BC register
void CPUZ80::LD_DE()
{
	CPU_REG_LOAD(DE, temp);
	//inc_PC(2);
}

// Loads fetched data to HL register
void CPUZ80::LD_HL()
{
	CPU_REG_LOAD(HL, temp);
	//inc_PC(2);
}

// Loads fetched data to SP register
void CPUZ80::LD_SP()
{
	// I would consider this as crutch but I don't actually know how to solve this problem
	// However it seems like the only case
	if (opcode == 0xF9)
	{
		CPU_REG_LOAD(SP, *fetched16_ptr);
	}
	else
	{
		CPU_REG_LOAD(SP, temp);
		//inc_PC(2);
	}
}

// Loads fetched data to HL register
void CPUZ80::LDHL()
{
	reset_flag(Z);
	reset_flag(N);
	CPU_REG_LOAD(HL, temp);
}

// Pushes fetched data onto stack
void CPUZ80::PUSH()
{
	CPU_PUSH_16(*fetched16_ptr);
}

// Pops data from stack to fetched data pointer
void CPUZ80::POP()
{
	*fetched16_ptr = CPU_POP_16();
}

// Adds fetched data to A register
void CPUZ80::ADD_A()
{
	CPU_ACC_ADD(*fetched8_ptr);
}

// Adds fetched data+C flag to A register
void CPUZ80::ADC()
{
	CPU_ACC_ADD(*fetched8_ptr+get_flag(C));
}

// Subtracts fetched data from A register
void CPUZ80::SUB()
{
	CPU_ACC_SUB(*fetched8_ptr);
}

// Subtracts fetched data+C flag from A register
void CPUZ80::SBC()
{
	CPU_ACC_SUB(*fetched8_ptr + get_flag(C));
}

// Logically AND fetched data with A register, result in A
void CPUZ80::AND()
{
	CPU_ACC_AND(*fetched8_ptr);
}

// Logically OR fetched data with A register, result in A
void CPUZ80::OR()
{
	CPU_ACC_OR(*fetched8_ptr);
}

// Logically OR fetched data with A register, result in A
void CPUZ80::XOR()
{
	CPU_ACC_XOR(*fetched8_ptr);
}

// Compares fetched data with A register, no results written
void CPUZ80::CP()
{
	CPU_ACC_SUB(*fetched8_ptr, true);
}

// Increments 8-bit fetched data
void CPUZ80::INC_8()
{
	CPU_8REG_INC(fetched8_ptr);
}

// Decrements 8-bit fetched data
void CPUZ80::DEC_8()
{
	CPU_8REG_DEC(fetched8_ptr);
}

// Adds fetched 16-bit data to HL register
void CPUZ80::ADD_HL()
{
	CPU_HL_ADD(*fetched16_ptr);
}

// Adds fetched 16-bit data to HL register
void CPUZ80::ADD_SP()
{
	CPU_SP_ADD(*fetched8_ptr);
}

// Increments 16-bit fetched data
void CPUZ80::INC_16()
{
	CPU_16REG_INC(fetched16_ptr);
}

// Decrements 16-bit fetched data
void CPUZ80::DEC_16()
{
	CPU_16REG_DEC(fetched16_ptr);
}

// This function excutes extended opcodes
void CPUZ80::PREFIX()
{
	opcode = read(PC);
	PC++;

	cycles += prefixes[opcode].cycles;

	(this->*prefixes[opcode].data_func)();
	(this->*prefixes[opcode].op_func)();
}

// Swaps nibbles of fetched data
void CPUZ80::SWAP()
{
	CPU_8REG_SWAP(fetched8_ptr);
}

// Not yet implemented
void CPUZ80::DAA()
{
	// TODO
}

// Flips all bits of A register
void CPUZ80::CPL()
{
	CPU_ACC_FLIP();
}

// Flips C flag
void CPUZ80::CCF()
{
	reset_flag(N);
	reset_flag(H);
	set_flag(C, get_flag(C) != 1);
}

// Sets C flag
void CPUZ80::SCF()
{
	reset_flag(N);
	reset_flag(H);
	set_flag(C, true);
}

// Nothing happens
void CPUZ80::NOP()
{

}

// Not yet implemented
void CPUZ80::HALT()
{
	// TODO
}

// Not yet implemented
void CPUZ80::STOP()
{
	// TODO
}

// Disables interupts after next instruction is executed
// Sets IME to true
void CPUZ80::DI()
{
	PDI = true;
}

// Enables interupts after next instruction is executed
// Sets IME to true
void CPUZ80::EI()
{
	PEI = true;
}

// Rotates A left
void CPUZ80::RLCA()
{
	CPU_8REG_RLC(&AF.hi);
}

// Rotates A left through C flag
void CPUZ80::RLA()
{
	CPU_8REG_RL(&AF.hi);
}

// Rotates A right
void CPUZ80::RRCA()
{
	CPU_8REG_RRC(&AF.hi);
}

// Rotates A right through C flag
void CPUZ80::RRA()
{
	CPU_8REG_RR(&AF.hi);
}

// Rotates fetched data left
void CPUZ80::RLC()
{
	CPU_8REG_RLC(fetched8_ptr);
}

// Rotates fetched data through C flag
void CPUZ80::RL()
{
	CPU_8REG_RL(fetched8_ptr);
}

// Rotates fetched data right
void CPUZ80::RRC()
{
	CPU_8REG_RRC(fetched8_ptr);
}

// Rotates fetched data right through C flag
void CPUZ80::RR()
{
	CPU_8REG_RR(fetched8_ptr);
}

// Shifts arithmetically fetched data left
void CPUZ80::SLA()
{
	CPU_8REG_SLA(fetched8_ptr);
}

// Shifts arithmetically fetched data right
void CPUZ80::SRA()
{
	CPU_8REG_SRA(fetched8_ptr);
}

// Shifts logically fetched data right
void CPUZ80::SRL()
{
	CPU_8REG_SRL(fetched8_ptr);
}

// Tests fetched data bit of A register
void CPUZ80::BIT_A()
{
	CPU_TEST_BIT(AF.hi, temp);
}

// Tests fetched data bit of B register
void CPUZ80::BIT_B()
{
	CPU_TEST_BIT(BC.hi, temp);
}

// Tests fetched data bit of C register
void CPUZ80::BIT_C()
{
	CPU_TEST_BIT(BC.lo, temp);
}

// Tests fetched data bit of D register
void CPUZ80::BIT_D()
{
	CPU_TEST_BIT(DE.hi, temp);
}

// Tests fetched data bit of E register
void CPUZ80::BIT_E()
{
	CPU_TEST_BIT(DE.lo, temp);
}

// Tests fetched data bit of H register
void CPUZ80::BIT_H()
{
	CPU_TEST_BIT(HL.hi, temp);
}

// Tests fetched data bit of L register
void CPUZ80::BIT_L()
{
	CPU_TEST_BIT(HL.lo, temp);
}

// Tests fetched data bit of (HL)
void CPUZ80::BIT_M_HL()
{
	CPU_TEST_BIT(read(HL), temp);
}

// Sets fetched data bit of A register
void CPUZ80::SET_A()
{
	CPU_SET_BIT(&AF.hi, temp);
}

// Sets fetched data bit of B register
void CPUZ80::SET_B()
{
	CPU_SET_BIT(&BC.hi, temp);
}

// Sets fetched data bit of C register
void CPUZ80::SET_C()
{
	CPU_SET_BIT(&BC.lo, temp);
}

// Sets fetched data bit of D register
void CPUZ80::SET_D()
{
	CPU_SET_BIT(&DE.hi, temp);
}

// Sets fetched data bit of E register
void CPUZ80::SET_E()
{
	CPU_SET_BIT(&DE.lo, temp);
}

// Sets fetched data bit of H register
void CPUZ80::SET_H()
{
	CPU_SET_BIT(&HL.hi, temp);
}

// Sets fetched data bit of L register
void CPUZ80::SET_L()
{
	CPU_SET_BIT(&HL.lo, temp);
}

// Sets fetched data bit of (HL)
void CPUZ80::SET_M_HL()
{
	CPU_SET_BIT(read_ptr(HL), temp);
}

// Resets fetched data bit of A register
void CPUZ80::RES_A()
{
	CPU_RESET_BIT(&AF.hi, temp);
}

// Resets fetched data bit of B register
void CPUZ80::RES_B()
{
	CPU_SET_BIT(&BC.hi, temp);
}

// Resets fetched data bit of C register
void CPUZ80::RES_C()
{
	CPU_RESET_BIT(&BC.lo, temp);
}

// Resets fetched data bit of D register
void CPUZ80::RES_D()
{
	CPU_RESET_BIT(&DE.hi, temp);
}

// Resets fetched data bit of E register
void CPUZ80::RES_E()
{
	CPU_RESET_BIT(&DE.lo, temp);
}

// Resets fetched data bit of H register
void CPUZ80::RES_H()
{
	CPU_RESET_BIT(&HL.hi, temp);
}

// Resets fetched data bit of L register
void CPUZ80::RES_L()
{
	CPU_RESET_BIT(&HL.lo, temp);
}

// Resets fetched data bit of (HL)
void CPUZ80::RES_M_HL()
{
	CPU_RESET_BIT(read_ptr(HL), temp);
}

// Jumps to the fetched data
// Actually it sets PC to fetched data
void CPUZ80::JP()
{
	PC = temp;
}

// Jumps to the fetched data if Z is reset
// Actually it sets PC to fetched data
void CPUZ80::JPNZ()
{
	if(get_flag(Z) == 0)
		PC = temp;
}

// Jumps to the fetched data if Z is set
// Actually it sets PC to fetched data
void CPUZ80::JPZ()
{
	if (get_flag(Z) == 1)
		PC = temp;
}

// Jumps to the fetched data if C is reset
// Actually it sets PC to fetched data
void CPUZ80::JPNC()
{
	if (get_flag(C) == 0)
		PC = temp;
}

// Jumps to the fetched data if C is set
// Actually it sets PC to fetched data
void CPUZ80::JPC()
{
	if (get_flag(C) == 1)
		PC = temp;
}

// Jumps to current address + fetched data
// Actually it adds fetched data to PC
void CPUZ80::JR()
{
	PC = (PC - 2) + (H_S_BYTE)(*fetched8_ptr);
}

// Jumps to current address + fetched data if Z is reset
// Actually it adds fetched data to PC
void CPUZ80::JRNZ()
{
	if(get_flag(Z) == 0)
		PC = (PC - 2) + (H_S_BYTE)(*fetched8_ptr);
}

// Jumps to current address + fetched data if Z is set
// Actually it adds fetched data to PC
void CPUZ80::JRZ()
{
	if (get_flag(Z) == 1)
		PC = (PC - 2) + (H_S_BYTE)(*fetched8_ptr);
}

// Jumps to current address + fetched data if C is reset
// Actually it adds fetched data to PC
void CPUZ80::JRNC()
{
	if (get_flag(C) == 0)
		PC = (PC - 2) + (H_S_BYTE)(*fetched8_ptr);
}
// Jumps to current address + fetched data if C is set
// Actually it adds fetched data to PC
void CPUZ80::JRC()
{
	if (get_flag(C) == 1)
		PC = (PC - 2) + (H_S_BYTE)(*fetched8_ptr);
}

// Jumps to the fetched data
// Pushes PC to the stack;
void CPUZ80::CALL()
{
	CPU_PUSH_16(PC.reg);
	PC = temp;
}

// Jumps to the fetched data if Z is reset
// Pushes PC to the stack;
void CPUZ80::CALL_NZ()
{
	if (get_flag(Z) == 0)
	{
		CPU_PUSH_16(PC.reg);
		PC = temp;
	}
}

// Jumps to the fetched data if Z is set
// Pushes PC to the stack;
void CPUZ80::CALL_Z()
{
	if (get_flag(Z) == 1)
	{
		CPU_PUSH_16(PC.reg);
		PC = temp;
	}
}

// Jumps to the fetched data if C is reset
// Pushes PC to the stack;
void CPUZ80::CALL_NC()
{
	if (get_flag(C) == 0)
	{
		CPU_PUSH_16(PC.reg);
		PC = temp;
	}
}

// Jumps to the fetched data if C is set
// Pushes PC to the stack;
void CPUZ80::CALL_C()
{
	if (get_flag(C) == 1)
	{
		CPU_PUSH_16(PC.reg);
		PC = temp;
	}
}

// Jumpst to 0000+00
// Pushes PC-1 onto stack
void CPUZ80::RST_00()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x00;
}

// Jumpst to 0000+08
// Pushes PC-1 onto stack
void CPUZ80::RST_08()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x08;
}

// Jumpst to 0000+10
// Pushes PC-1 onto stack
void CPUZ80::RST_10()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x10;
}

// Jumpst to 0000+18
// Pushes PC-1 onto stack
void CPUZ80::RST_18()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x18;
}

// Jumpst to 0000+20
// Pushes PC-1 onto stack
void CPUZ80::RST_20()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x20;
}

// Jumpst to 0000+28
// Pushes PC-1 onto stack
void CPUZ80::RST_28()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x28;
}

// Jumpst to 0000+30
// Pushes PC-1 onto stack
void CPUZ80::RST_30()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x30;
}

// Jumpst to 0000+38
// Pushes PC-1 onto stack
void CPUZ80::RST_38()
{
	CPU_PUSH_16(PC.reg - 1);
	PC = 0x0000 + 0x38;
}

// Pops 16-bit value from stack
// Jumps to that value
void CPUZ80::RET()
{
	PC = CPU_POP_16();
}

// Pops 16-bit value from stack if Z is reset
// Jumps to that value
void CPUZ80::RET_NZ()
{
	if(get_flag(Z) == 0)
		PC = CPU_POP_16();
}
// Pops 16-bit value from stack if Z is set
// Jumps to that value
void CPUZ80::RET_Z()
{
	if (get_flag(Z) == 1)
		PC = CPU_POP_16();
}

// Pops 16-bit value from stack if C is reset
// Jumps to that value
void CPUZ80::RET_NC()
{
	if (get_flag(C) == 0)
		PC = CPU_POP_16();
}

// Pops 16-bit value from stack if C is set
// Jumps to that value
void CPUZ80::RET_C()
{
	if (get_flag(C) == 1)
		PC = CPU_POP_16();
}

// Pops 16-bit value from stack
// Jumps to that value and enable interrupts
void CPUZ80::RETI()
{
	PC = CPU_POP_16();
	IME = true;
}

// Unknown function
void CPUZ80::XXX()
{

}

