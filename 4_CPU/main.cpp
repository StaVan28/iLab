
#include "CPU.h"

//-----------------------------------------------------------------

int main(int argc, char const *argv[]) {

	assembling_file();

	CPU_t CPU = {};
	CPU_construct(&CPU);

	CPU_accomplishment(&CPU); 

	CPU_destruct(&CPU);

}
/* TODO
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
	-- jump 
	-- unit test jump
	-- обработка ошибок в текстовой библиотеки
	-- обработка ошибок в CPU
	-- text_lib upgrade
*/

