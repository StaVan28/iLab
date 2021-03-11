
#include "txtlib.h"

int main() {

	FILE* source = fopen("./txt/source.txt",  "rw");

	text_t text(source, STRING_PARSING);

	fclose(source);

    return 0;
}

