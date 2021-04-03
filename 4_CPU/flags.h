
#ifndef FLAGS_H_INCLUDED
#define FLAGS_H_INCLUDED

//-----------------------------------------------------------------

//// FLAGS 
// CF -- Флаг переноса(Carry Flag) 
// PF -- Флаг паритета(Parity Flag)
// AF -- Вспомогательный флаг переноса(Auxiliary carry Flag)
// ZF -- Флаг нуля(Zero Flag)
// SF -- Флаг знака(Sign Flag)
// OF -- Флаг переполнения(Overflow Flag)

//-----------------------------------------------------------------

// Flags bits
#define CF 0b00000001
#define PF 0b00000010
#define AF 0b00000100
#define ZF 0b00001000
#define SF 0b00010000
#define OF 0b00100000

/*
*	enum class Flags: char {
*		CF = (1 << 0);
*		PF = (1 << 1);
*		AF = (1 << 2);
*		ZF = (1 << 3);
*		SF = (1 << 4);
*		OF = (1 << 5);
*	};
*/

//-----------------------------------------------------------------

static const int NUM_OF_FLAGS = 6;

//-----------------------------------------------------------------

// Operations with flags
#define SET_FLAG(FLAG, REG)	\
		REG |=  FLAG 		\

#define CLEAR_FLAG(FLAG, REG)	\
		REG &= ~FLAG         	\

//-----------------------------------------------------------------

//void set_CF(CPU_t* CPU); // V
//void set_PF(CPU_t* CPU);
//void set_AF(CPU_t* CPU);
//void set_ZF(CPU_t* CPU); // V
//void set_SF(CPU_t* CPU);
//void set_OF(CPU_t* CPU);

//-----------------------------------------------------------------

#endif // FLAGS_H_INCLUDED