
#include "unit_tests.h"

//-----------------------------------------------------------------------------

void unit_test_1(const char* file_path, const char* source) {

    assembling_file(file_path, source);

    int ch1  = 0; 
	  int ch2  = 0;
  	int line = 1;

	  FILE* f1 = fopen("./unit_tests/txt/obj_test1_source", "rb"); 
  	assert(f1);

    FILE* f2 = fopen("./unit_tests/txt/obj_test1_comparison", "rb"); 
    assert(f2);

 	  while (!feof(f1) && !feof(f2) && (ch1 == ch2)) {

   	    ch1 = fgetc(f1);
   		  ch2 = fgetc(f2);
        
   		  if ((ch1 == '\n') && (ch2 == '\n'))
   			    line++;
	  }

	  if (ch1 == ch2) 
   	    printf("\nUnit_test_1: (OK) Func \"void assembling_file(...)\" work correctly\n");
	  else {
   	  	printf("\nUnit_test_1: (ERROR) Func \"void assembling_file(char* txt_file_path)\" doesn't work correctly. It's broke on %d line\n", line);
    	  printf("Check upgrade number commands\n");
  	}

  	fclose(f1);
  	fclose(f2);
}

//-----------------------------------------------------------------------------

void unit_test_2(const char* file_path, const char* obj_source) {

	int ch1  = 0; 
	int ch2  = 0;
  int line = 1;
  int indx = 0;

	CPU_t CPU = {};
	CPU_construct(&CPU, file_path, obj_source);

	char* obj_file_path = concat(file_path, nullptr, obj_source);

	FILE* obj_file = fopen(obj_file_path,  "rb");
	assert(obj_file);

	int num_symbols = text_t::txtlib_number_of_symbols_buff(CPU.buffer_cmd);

 	while (!feof(obj_file) && (indx < num_symbols) && (ch1 == ch2)) {

   		ch1 = fgetc(obj_file);

   		ch2 = CPU.buffer_cmd[indx];
   		indx++;
 	
   		if ((ch1 == '\n') && (ch2 == '\n'))
   			line++;
	}

	if (ch1 == ch2) {
   		printf("Unit_test_2: (OK) Func \"void CPU_construct(...)\" make correct buffer\n");
	}
	else {
   		printf("Unit_test_2: (ERROR) Func \"void CPU_construct(...)\" doesn't make correct buffer. It's broke on %d line\n", line);
    	printf("Check texlib\n");
  	}

	fclose(obj_file);

	CPU_destruct(&CPU);
}

//-----------------------------------------------------------------------------
