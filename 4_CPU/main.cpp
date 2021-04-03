
#include "CPU.h"

//-----------------------------------------------------------------

int main() {

	assembling_file();

	CPU_t CPU;

	CPU.run(); 
	CPU.dump();

}
/* TODO
	-- remove two pass functions
	-- directories in project
	V	-- работа с разными фалами
	V	-- unit_tests на конструктор и деструктор
	V	-- assembling
	V	-- чекнуть работает ли '\0'
	V	-- CPU_accomplshment
	V	-- in  func
	V	-- pop func
	-- Assembler unit_test
	-- CPU_accomplshment unit-test
	-- listing 
	V	-- регистры
	-- unit test регистры
	V	-- jump 
	-- unit test jump
	-- обработка ошибок в текстовой библиотеки
	-- обработка ошибок в CPU
	-- text_lib upgrade
*/

