
#include "txtlib.h"

int main() {

	FILE* source = fopen("./txt/source.txt",  "rb");

	Text text(source, WORD_PARSING);

	text.txtlib_text_dump();

	fclose(source);

    return 0;
}

