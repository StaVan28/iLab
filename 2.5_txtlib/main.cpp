
#include "txtlib.h"

int main() {

	FILE* source = fopen("./txt/source.txt",  "rw");

	text_t text(source, WORD_PARSING);

	fclose(source);

    return 0;
}
