
#include "unit_tests.h" 	

//----------------------------------------------------------------

int main() {

	const char* file_path = "./unit_tests/txt/";
	const char* source    = "source";

	const char* test1_source = concat("test1_", nullptr, source);
	unit_test_1(file_path, test1_source);

	const char* obj_test2_source = concat("obj_test2_", nullptr, source);
	unit_test_2(file_path, obj_test2_source);

	return 0;
}
