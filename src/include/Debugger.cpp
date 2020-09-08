#include "GameBoy.h"
#include "Debugger.h"

std::string Debugger::hex(uint32_t n, uint8_t d)
{
	std::string s(d, '0');
	for (int i = d - 1; i >= 0; i--, n >>= 4)
		s[i] = "0123456789ABCDEF"[n & 0xF];
	return s;
}

void Debugger::draw_ram(int x, int y, uint16_t addr, int rows, int columns)
{
	int ram_x = x, ram_y = y;
	for (int row = 0; row < rows; row++)
	{
		std::string offset = "$" + hex(addr, 4) + ":";
		for (int col = 0; col < columns; col++)
		{
			offset += " " + hex(gb->read(addr), 2);
			addr++;
		}
		DrawString(ram_x, ram_y, offset, olc::GREEN);
		ram_y += 10;
	}
}

void Debugger::draw_cpu(int x, int y)
{
	DrawString(x,       y, "FLAGS:", olc::WHITE);
	DrawString(x + 64,  y, "Z", gb->cpu.AF.lo & CPUZ80::Z ? olc::BLUE : olc::RED);
	DrawString(x + 80,  y, "N", gb->cpu.AF.lo & CPUZ80::N ? olc::BLUE : olc::RED);
	DrawString(x + 96,  y, "H", gb->cpu.AF.lo & CPUZ80::H ? olc::BLUE : olc::RED);
	DrawString(x + 112, y, "C", gb->cpu.AF.lo & CPUZ80::C ? olc::BLUE : olc::RED);
	DrawString(x + 128, y, "-", olc::WHITE);
	DrawString(x + 144, y, "-", olc::WHITE);
	DrawString(x + 160, y, "-", olc::WHITE);
	DrawString(x + 178, y, "-", olc::WHITE);

	DrawString(x, y + 10, "REGISTERS:", olc::WHITE);

	DrawString(x, y + 20, "PC: ");
	DrawString(x + 30, y + 20, "$" + hex(gb->cpu.PC.reg, 4), olc::GREEN);

	DrawString(x,       y + 30, "A: ");
	DrawString(x + 25,  y + 30, "$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 104, y + 30, "F: ");
	DrawString(x + 129, y + 30, "$" + hex(gb->cpu.AF.lo, 2) + "  [" + std::to_string(gb->cpu.AF.lo) + "]", olc::GREEN);

	DrawString(x,       y + 40, "B: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 25,  y + 40, "$" + hex(gb->cpu.BC.hi, 2) + "  [" + std::to_string(gb->cpu.BC.hi) + "]", olc::GREEN);
	DrawString(x + 104, y + 40, "C: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 129, y + 40, "$" + hex(gb->cpu.BC.lo, 2) + "  [" + std::to_string(gb->cpu.BC.lo) + "]", olc::GREEN);

	DrawString(x,       y + 50, "D: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 25,  y + 50, "$" + hex(gb->cpu.DE.hi, 2) + "  [" + std::to_string(gb->cpu.DE.hi) + "]", olc::GREEN);
	DrawString(x + 104, y + 50, "E: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 129, y + 50, "$" + hex(gb->cpu.DE.lo, 2) + "  [" + std::to_string(gb->cpu.DE.lo) + "]", olc::GREEN);
	
	DrawString(x,       y + 60, "H: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 25,  y + 60, "$" + hex(gb->cpu.HL.hi, 2) + "  [" + std::to_string(gb->cpu.HL.hi) + "]", olc::GREEN);
	DrawString(x + 104, y + 60, "L: ");//"$" + hex(gb->cpu.AF.hi, 2) + "  [" + std::to_string(gb->cpu.AF.hi) + "]", olc::GREEN);
	DrawString(x + 129, y + 60, "$" + hex(gb->cpu.HL.lo, 2) + "  [" + std::to_string(gb->cpu.HL.lo) + "]", olc::GREEN);

	DrawString(x, y + 70, "STACK POINTER: ");
	DrawString(x + 115, y + 70, "$" + hex(gb->cpu.SP.reg, 4), olc::GREEN);
	//DrawString(x, y + 70, "STACK POINTER: $" + hex(gb->cpu.SP.reg, 4));
}

void Debugger::draw_cpu_special(int x, int y)
{
	if (gb->cpu.PEI)
		DrawString(x, y, "Pending Enable Interupt");
	else if (gb->cpu.PDI)
		DrawString(x, y, "Pending Disable Interupt");
	else
		DrawString(x, y, "");

	std::string IME = (gb->cpu.IME ? "TRUE" : "FALSE");
	DrawString(x,       y + 10, "IME: " + IME);
	DrawString(x,       y + 20, "ALLOWED:");
	DrawString(x + 86,  y + 20, "V", (*gb->cpu.IE) & 0x01 ? olc::BLUE : olc::RED);
	DrawString(x + 102, y + 20, "L", (*gb->cpu.IE) & 0x02 ? olc::BLUE : olc::RED);
	DrawString(x + 118, y + 20, "T", (*gb->cpu.IE) & 0x04 ? olc::BLUE : olc::RED);
	DrawString(x + 134, y + 20, "S", (*gb->cpu.IE) & 0x08 ? olc::BLUE : olc::RED);
	DrawString(x + 150, y + 20, "J", (*gb->cpu.IE) & 0x10 ? olc::BLUE : olc::RED);

	DrawString(x,      y + 30,  "REQUESTED:");
	DrawString(x + 86, y + 30,  "V", (*gb->cpu.IF) & 0x01 ? olc::BLUE : olc::RED);
	DrawString(x + 102, y + 30, "L", (*gb->cpu.IF) & 0x02 ? olc::BLUE : olc::RED);
	DrawString(x + 118, y + 30, "T", (*gb->cpu.IF) & 0x04 ? olc::BLUE : olc::RED);
	DrawString(x + 134, y + 30, "S", (*gb->cpu.IF) & 0x08 ? olc::BLUE : olc::RED);
	DrawString(x + 150, y + 30, "J", (*gb->cpu.IF) & 0x10 ? olc::BLUE : olc::RED);

	DrawString(x, y + 40, "");

	DrawString(x, y + 50, "TIMER:", ((*gb->cpu.clock.TAC) & 0x04) > 0 ? olc::WHITE : olc::RED);
	DrawString(x + 86, y + 50, "$" + hex((*gb->cpu.clock.TIMA), 2), olc::GREEN);

	DrawString(x, y + 60, "DIVIDER:");
	DrawString(x + 86, y + 60, "$" + hex((*gb->cpu.DIV), 2), olc::GREEN);

	DrawString(x, y + 70, "FREQUENCY:");
	switch ((*gb->cpu.clock.TAC) & 0x03)
	{
	case 0x00: DrawString(x + 86, y + 70, "4096 Hz");    break;
	case 0x01: DrawString(x + 86, y + 70, "2621444 Hz"); break;
	case 0x02: DrawString(x + 86, y + 70, "65536 Hz");   break;
	case 0x03: DrawString(x + 86, y + 70, "16384 Hz");   break;
	default:
		break;
	}

	DrawString(x, y + 80, "");

	DrawString(x, y + 90, "LCD", gb->cpu.LCD.enabled() ? olc::BLUE : olc::RED);

	DrawString(x, y + 100, "LCD MODE:");
	DrawString(x + 86, y + 100, "$" + hex((*gb->cpu.LCD.STAT) & 0x03, 2), olc::GREEN);

	DrawString(x, y + 110, "LINE:");
	DrawString(x + 86, y + 110, "$" + hex((*gb->cpu.LCD.LY), 2), olc::GREEN);

}

void Debugger::draw_code(int x, int y, int lines)
{
	auto it_a = map_asm.find(gb->cpu.PC.reg);
	int line_y = (lines >> 1) * 10 + y;
	if (it_a != map_asm.end())
	{
		DrawString(x, line_y, (*it_a).second, olc::CYAN);
		while (line_y < (lines * 10) + y)
		{
			line_y += 10;
			if (++it_a != map_asm.end())
				DrawString(x, line_y, (*it_a).second);
		}
	}

	it_a = map_asm.find(gb->cpu.PC.reg);
	line_y = (lines >> 1) * 10 + y;
	if (it_a != map_asm.end())
	{
		while (line_y > y)
		{
			line_y -= 10;
			if (--it_a != map_asm.end())
				DrawString(x, line_y, (*it_a).second);
		}
	}
}

void Debugger::draw_stack(int x, int y)
{
	DrawString(x, y, "STACK");
	H_WORD old_SP = gb->cpu.SP.reg;

	H_BYTE lo = gb->read(old_SP + 1);
	H_BYTE hi = gb->read(old_SP + 2);
	DrawString(x, y + 10, "+0 $" + hex(hi, 2) + hex(lo, 2));

	old_SP += 2;
	lo = gb->read(old_SP + 1);
	hi = gb->read(old_SP + 2);
	DrawString(x, y + 20, "+2 $" + hex(hi, 2) + hex(lo, 2));

	old_SP += 2;
	lo = gb->read(old_SP + 1);
	hi = gb->read(old_SP + 2);
	DrawString(x, y + 30, "+4 $" + hex(hi, 2) + hex(lo, 2));

	old_SP += 2;
	lo = gb->read(old_SP + 1);
	hi = gb->read(old_SP + 2);
	DrawString(x, y + 40, "+6 $" + hex(hi, 2) + hex(lo, 2));
}

bool Debugger::OnUserCreate()
{
	gb->cpu.reset();

	std::stringstream ss;
	ss << "F0 44 FE 90 38 FA AF E0 40 21 00 90 11 50 01 01 00 08 1A 22 13 0B 78 B1 20 F8 21 00 99 11 37 00 1A 22 13 A7 20 FA 3E E4 E0 47 AF E0 42 E0 43 E0 26 3E 81 E0 40 18 FE 48 65 6C 6C 6F 20 47 69 74 68 75 62 20 21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 F3 C3 00 00 CE ED 66 66 CC 0D 00 0B 03 73 00 83 00 0C 00 0D 00 08 11 1F 88 89 00 0E DC CC 6E E6 DD DD D9 99 BB BB 67 63 6E 0E EC CC DD DC 99 9F BB B9 33 3E 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 E7 FD AD 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 08 00 0C 00 08 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 80 80 80 80 80 80 80 80 80 00 00 80 80 00 00 00 00 6C 6C 6C 6C 48 48 00 00 00 00 00 00 00 00 48 48 FC FC 48 48 48 48 48 48 FC FC 48 48 00 00 10 10 7C 7C 90 90 78 78 14 14 F8 F8 10 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 60 60 90 90 50 50 60 60 94 94 98 98 6C 6C 00 00 00 00 38 38 38 38 08 08 10 10 00 00 00 00 00 00 18 18 20 20 20 20 20 20 20 20 20 20 18 18 00 00 18 18 04 04 04 04 04 04 04 04 04 04 18 18 00 00 00 00 10 10 54 54 38 38 54 54 10 10 00 00 00 00 00 00 10 10 10 10 7C 7C 10 10 10 10 00 00 00 00 00 00 00 00 00 00 00 00 30 30 30 30 60 60 00 00 00 00 00 00 00 00 7C 7C 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 60 60 60 60 00 00 00 00 04 04 08 08 10 10 20 20 40 40 80 80 00 00 30 30 58 58 CC CC CC CC CC CC 68 68 30 30 00 00 30 30 70 70 F0 F0 30 30 30 30 30 30 FC FC 00 00 78 78 CC CC 18 18 30 30 60 60 C0 C0 FC FC 00 00 78 78 8C 8C 0C 0C 38 38 0C 0C 8C 8C 78 78 00 00 38 38 58 58 98 98 FC FC 18 18 18 18 18 18 00 00 FC FC C0 C0 C0 C0 78 78 0C 0C CC CC 78 78 00 00 78 78 CC CC C0 C0 F8 F8 CC CC CC CC 78 78 00 00 FC FC 0C 0C 0C 0C 18 18 18 18 30 30 30 30 00 00 78 78 CC CC CC CC 78 78 CC CC CC CC 78 78 00 00 78 78 CC CC CC CC 7C 7C 0C 0C CC CC 78 78 00 00 00 00 C0 C0 C0 C0 00 00 C0 C0 C0 C0 00 00 00 00 00 00 C0 C0 C0 C0 00 00 C0 C0 40 40 80 80 00 00 04 04 18 18 60 60 80 80 60 60 18 18 04 04 00 00 00 00 00 00 FC FC 00 00 FC FC 00 00 00 00 00 00 80 80 60 60 18 18 04 04 18 18 60 60 80 80 00 00 78 78 CC CC 18 18 30 30 20 20 00 00 20 20 00 00 00 00 20 20 70 70 F8 F8 F8 F8 F8 F8 00 00 00 00 30 30 48 48 84 84 84 84 FC FC 84 84 84 84 00 00 F8 F8 84 84 84 84 F8 F8 84 84 84 84 F8 F8 00 00 3C 3C 40 40 80 80 80 80 80 80 40 40 3C 3C 00 00 F0 F0 88 88 84 84 84 84 84 84 88 88 F0 F0 00 00 FC FC 80 80 80 80 FC FC 80 80 80 80 FC FC 00 00 FC FC 80 80 80 80 FC FC 80 80 80 80 80 80 00 00 7C 7C 80 80 80 80 BC BC 84 84 84 84 78 78 00 00 84 84 84 84 84 84 FC FC 84 84 84 84 84 84 00 00 7C 7C 10 10 10 10 10 10 10 10 10 10 7C 7C 00 00 04 04 04 04 04 04 04 04 04 04 04 04 F8 F8 00 00 84 84 88 88 90 90 A0 A0 E0 E0 90 90 8C 8C 00 00 80 80 80 80 80 80 80 80 80 80 80 80 FC FC 00 00 84 84 CC CC B4 B4 84 84 84 84 84 84 84 84 00 00 84 84 C4 C4 A4 A4 94 94 8C 8C 84 84 84 84 00 00 78 78 84 84 84 84 84 84 84 84 84 84 78 78 00 00 F8 F8 84 84 84 84 F8 F8 80 80 80 80 80 80 00 00 78 78 84 84 84 84 84 84 A4 A4 98 98 6C 6C 00 00 F8 F8 84 84 84 84 F8 F8 90 90 88 88 84 84 00 00 7C 7C 80 80 80 80 78 78 04 04 84 84 78 78 00 00 7C 7C 10 10 10 10 10 10 10 10 10 10 10 10 00 00 84 84 84 84 84 84 84 84 84 84 84 84 78 78 00 00 84 84 84 84 84 84 84 84 84 84 48 48 30 30 00 00 84 84 84 84 84 84 84 84 B4 B4 CC CC 84 84 00 00 84 84 84 84 48 48 30 30 48 48 84 84 84 84 00 00 44 44 44 44 44 44 28 28 10 10 10 10 10 10 00 00 FC FC 04 04 08 08 10 10 20 20 40 40 FC FC 00 00 38 38 20 20 20 20 20 20 20 20 20 20 38 38 00 00 00 00 80 80 40 40 20 20 10 10 08 08 04 04 00 00 1C 1C 04 04 04 04 04 04 04 04 04 04 1C 1C 00 00 10 10 28 28 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF C0 C0 60 60 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 78 78 04 04 7C 7C 84 84 78 78 00 00 80 80 80 80 80 80 F8 F8 84 84 84 84 78 78 00 00 00 00 00 00 7C 7C 80 80 80 80 80 80 7C 7C 00 00 04 04 04 04 04 04 7C 7C 84 84 84 84 78 78 00 00 00 00 00 00 78 78 84 84 F8 F8 80 80 7C 7C 00 00 00 00 3C 3C 40 40 FC FC 40 40 40 40 40 40 00 00 00 00 00 00 78 78 84 84 7C 7C 04 04 F8 F8 00 00 80 80 80 80 F8 F8 84 84 84 84 84 84 84 84 00 00 00 00 10 10 00 00 10 10 10 10 10 10 10 10 00 00 00 00 10 10 00 00 10 10 10 10 10 10 E0 E0 00 00 80 80 80 80 84 84 98 98 E0 E0 98 98 84 84 00 00 10 10 10 10 10 10 10 10 10 10 10 10 10 10 00 00 00 00 00 00 68 68 94 94 94 94 94 94 94 94 00 00 00 00 00 00 78 78 84 84 84 84 84 84 84 84 00 00 00 00 00 00 78 78 84 84 84 84 84 84 78 78 00 00 00 00 00 00 78 78 84 84 84 84 F8 F8 80 80 00 00 00 00 00 00 78 78 84 84 84 84 7C 7C 04 04 00 00 00 00 00 00 BC BC C0 C0 80 80 80 80 80 80 00 00 00 00 00 00 7C 7C 80 80 78 78 04 04 F8 F8 00 00 00 00 40 40 F8 F8 40 40 40 40 40 40 3C 3C 00 00 00 00 00 00 84 84 84 84 84 84 84 84 78 78 00 00 00 00 00 00 84 84 84 84 48 48 48 48 30 30 00 00 00 00 00 00 84 84 84 84 84 84 A4 A4 58 58 00 00 00 00 00 00 8C 8C 50 50 20 20 50 50 8C 8C 00 00 00 00 00 00 84 84 84 84 7C 7C 04 04 F8 F8 00 00 00 00 00 00 FC FC 08 08 30 30 40 40 FC FC 00 00 18 18 20 20 20 20 40 40 20 20 20 20 18 18 00 00 10 10 10 10 10 10 10 10 10 10 10 10 10 10 00 00 30 30 08 08 08 08 04 04 08 08 08 08 30 30 00 00 00 00 00 00 48 48 A8 A8 90 90 00 00 00 00 00 00";
	//ss << "00";
	uint16_t offset = 0x0000;
	while (!ss.eof())
	{
		std::string b;
		ss >> b;
		gb->m_memory[offset++] = (uint8_t)std::stoul(b, nullptr, 16);
	}
	
	map_asm = gb->cpu.disassemble(0x0000, 0xFFFF);
	return true;
}

bool Debugger::OnUserUpdate(float fElapsedTime)
{
	//bool go = false;

	Clear(olc::BLACK);

	if (GetKey(olc::Key::SPACE).bHeld)
	{
		do
		{
			gb->cpu.cpu_clock();
		} while (!gb->cpu.complete());
	}

	if (GetKey(olc::Key::TAB).bPressed)
	{
		for (int i = 0; i < 10; i++)
		{
			do
			{
				gb->cpu.cpu_clock();
			} while (!gb->cpu.complete());
		}
	}

	if (GetKey(olc::Key::R).bPressed)
		gb->cpu.reset();

	draw_ram(2, 2, 0xFF00, 16, 16);
	draw_ram(2, 182, 0x0100, 16, 16);
	draw_cpu(448, 2);
	draw_cpu_special(2, 341);
	draw_code(448, 82, 25);
	draw_stack(615, 82);

	DrawString(2, 470, "SPACE = Step  TAB = 10 Steps G = GO!!!  R = RESET");

	return true;
}
