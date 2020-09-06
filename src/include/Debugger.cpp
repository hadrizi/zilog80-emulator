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
	DrawString(x, y, "FLAGS:", olc::WHITE);
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

bool Debugger::OnUserCreate()
{
	std::stringstream ss;
	ss << "3E 13 EA 00 FF 3E BB EA 01 FF 7A 86 4F 23 78 8E 47 2B";
	uint16_t offset = 0x0100;
	while (!ss.eof())
	{
		std::string b;
		ss >> b;
		gb->m_memory[offset++] = (uint8_t)std::stoul(b, nullptr, 16);
	}

	map_asm = gb->cpu.disassemble(0x0000, 0xFFFF);
	gb->cpu.reset();
	return true;
}

bool Debugger::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);

	if (GetKey(olc::Key::SPACE).bPressed)
	{
		do
		{
			gb->cpu.clock();
		} while (!gb->cpu.complete());
	}

	if (GetKey(olc::Key::R).bPressed)
		gb->cpu.reset();

	draw_ram(2, 2, 0xFF00, 16, 16);
	draw_ram(2, 182, 0x0100, 16, 16);
	draw_cpu(448, 2);
	draw_code(448, 82, 25);

	DrawString(10, 370, "SPACE = Step Instruction    R = RESET");

	return true;
}