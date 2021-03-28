
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

//-----------------------------------------------------------------

// Operations with flags
#define SET_FLAG(FLAG, REG)	\
		REG |=  FLAG 		\

#define CLEAR_FLAG(FLAG, REG)	\
		REG &= ~FLAG         	\

//-----------------------------------------------------------------

inline void set_CF(CPU_t* CPU); // V
inline void set_PF(CPU_t* CPU);
inline void set_AF(CPU_t* CPU);
inline void set_ZF(CPU_t* CPU); // V
inline void set_SF(CPU_t* CPU);
inline void set_OF(CPU_t* CPU);

//-----------------------------------------------------------------

#endif // FLAGS_H_INCLUDED