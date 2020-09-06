#pragma once
#include <cstdint>

typedef uint8_t H_BYTE;
typedef int8_t  H_S_BYTE;

typedef uint16_t H_WORD;
typedef int16_t  H_S_WORD;

typedef uint32_t H_DWORD;
typedef int32_t  H_S_DWORD;

struct Register
{
	union
	{
		H_WORD reg;
		struct
		{
			H_BYTE lo;
			H_BYTE hi;
		};
	};

	Register() : reg(0x0000) {};
	Register(H_WORD _reg) : reg(_reg) {};

	// Math operators
	inline Register operator  +(H_WORD other) const { return Register(reg + other); }
	inline Register operator  -(H_WORD other) const { return Register(reg - other); }
	inline Register operator +=(H_WORD other) const { return Register(reg + other); }
	inline Register operator -=(H_WORD other) const { return Register(reg - other); }

	inline Register operator  +(const Register& other) const { return Register(reg + other.reg); }
	inline Register operator  -(const Register& other) const { return Register(reg - other.reg); }
	inline Register operator +=(const Register& other) const { return Register(reg + other.reg); }
	inline Register operator -=(const Register& other) const { return Register(reg - other.reg); }

	inline Register& operator ++() { reg++;  return *this; }
	inline Register& operator --() { reg--;  return *this; }

	inline Register operator ++(int) { Register temp = *this; ++* this; return temp; }
	inline Register operator --(int) { Register temp = *this; --* this; return temp; }

	// Boolean operators
	inline bool operator ==(H_WORD other) const { return reg == other; }
	inline bool operator !=(H_WORD other) const { return reg != other; }
	inline bool operator  <(H_WORD other) const { return reg <  other; }
	inline bool operator  >(H_WORD other) const { return reg >  other; }
	inline bool operator <=(H_WORD other) const { return reg <= other; }
	inline bool	operator >=(H_WORD other) const { return reg >= other; }

	inline bool operator ==(const Register& other) const { return reg == other.reg; }
	inline bool	operator !=(const Register& other) const { return reg != other.reg; }
	inline bool	operator  <(const Register& other) const { return reg <  other.reg; }
	inline bool	operator  >(const Register& other) const { return reg >  other.reg; }
	inline bool	operator <=(const Register& other) const { return reg <= other.reg; }
	inline bool	operator >=(const Register& other) const { return reg >= other.reg; }

	// Assignment operators
	inline void operator =(const H_WORD other) { reg = other; }
};

struct Color
{
	union
	{
		struct
		{
			H_BYTE r, g, b, a;
		};
		H_BYTE raw[4];
		H_DWORD val;
	};

	explicit Color() : val(0) {
	}

	explicit Color(H_BYTE R, H_BYTE G, H_BYTE B, H_BYTE A = 255) : b(B), g(G), r(R), a(A) {
	}

	explicit Color(H_DWORD v) : val(v) {
	}

	explicit Color(const Color& c) : val(c.val) {
	}
};
