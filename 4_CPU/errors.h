
#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

//-----------------------------------------------------------------

#define RECREATE_DUMP_CPU_FILE								\
        FILE* dump_CPU = fopen("./txt/dump_CPU.txt", "wb");	\
        fclose(dump_CPU);									\

//-----------------------------------------------------------------

#define FPRINTF_REG(reg, reg_str)										\
        if (true) {														\
			if (CPU->reg == POISON_DOUBLE_STACK) {						\
				fprintf(listning_CPU, " {");							\
			}															\
			else														\
				fprintf(listning_CPU, "*{");							\
																		\
		    fprintf(listning_CPU, reg_str);                   			\
		    															\
			if (CPU->EAX == POISON_DOUBLE_STACK)						\
				fprintf(listning_CPU, "} : %lg (POISON)\n", CPU->reg);	\
			else														\
				fprintf(listning_CPU, "} : %lg\n"         , CPU->reg);	\
		}																\

//-----------------------------------------------------------------

void CPU_dump(CPU_t* CPU);

//-----------------------------------------------------------------

#endif // ERRORS_H_INCLUDED