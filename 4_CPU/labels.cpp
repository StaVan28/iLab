
#include "CPU.h"
#include "labels.h"

//-----------------------------------------------------------------

labels::labels(void) 
{
	// check labels_t

	capacity = START_CAPACITY;

	array_of_labels = (label_info_t*) calloc(START_CAPACITY, sizeof(label_info_t));
	assert(array_of_labels);
}

//-----------------------------------------------------------------

labels::~labels(void)
{
	// check labels_t

	free(array_of_labels);
	array_of_labels = nullptr;
}

//-----------------------------------------------------------------
//!TODO
int labels::check_label(char* name_of_label, int pos_to_jmp, int func_call)
{
	assert(name_of_label);
	assert(pos_to_jmp >= POISON_POSITION);

	parsing_label(name_of_label, func_call);

	for (size_t indx = 0; indx < label_counter; indx++) {
		if (!strcmp(array_of_labels[indx].name_of_label, name_of_label)) {
			if (pos_to_jmp != POISON_POSITION)  {
				array_of_labels[indx].pos_to_jmp = pos_to_jmp;
				return POISON_POSITION;
			}
			else 
				return POISON_POSITION;
		}
	}

	add_label(name_of_label, pos_to_jmp);

	return POISON_POSITION;
}

//-----------------------------------------------------------------

void labels::parsing_label(char* name_of_label, int func_call) 
{
	assert(name_of_label);

	switch(func_call) {

		case FROM_JMP_CMD:		return;

		case FROM_MARK_LABEL:	const char* ptr_on_MARK_LABEL = strchr(name_of_label, MARK_LABEL);
								POINTER_ON_(name_of_label, (ptr_on_MARK_LABEL - name_of_label), char) = '\0';
								return;
	}

}
    
//-----------------------------------------------------------------
// небезопасно
int labels::find_label(char* name_of_label) 
{
	size_t indx = 0;

	while (indx < label_counter) {
		if (!strcmp(name_of_label, array_of_labels[indx].name_of_label))
			break;	
		indx++;
	}

	return array_of_labels[indx].pos_to_jmp;
}
//-----------------------------------------------------------------

void labels::realloc_array_of_label(void)
{
	capacity *= 2;

	label_info_t* tmp_array_of_labels = array_of_labels;

	array_of_labels = (label_info_t*) realloc(array_of_labels, capacity * sizeof(label_info_t));

	if (array_of_labels == nullptr) {
		array_of_labels = tmp_array_of_labels;
		// error
	}

}

//-----------------------------------------------------------------

void labels::add_label(char* name_of_label, int pos_to_jmp)
{
	assert(name_of_label);
	assert(pos_to_jmp >= POISON_POSITION);

	if (label_counter == capacity)
		realloc_array_of_label();

	array_of_labels[label_counter].name_of_label = name_of_label;
	array_of_labels[label_counter].pos_to_jmp    = pos_to_jmp;

	label_counter++;
}

//-----------------------------------------------------------------

void labels::labels_dump(void)
{
	FILE* labels_dump = fopen("./txt/dump_labels.txt", "wb");
    assert(labels_dump);

    fprintf(labels_dump, "\n******************************************************\n");

    fprintf(labels_dump, "		LABELS:\n\n");

    fprintf(labels_dump, "Pointer array of labels: %p\n\n", array_of_labels);

    fprintf(labels_dump, "Capacity      = %ld\n", capacity);
    fprintf(labels_dump, "Label counter = %ld\n", label_counter);

    fprintf(labels_dump, "\n{Number in array}[position]\n\n");

    for (size_t indx = 0; indx < capacity; indx++) {
        fprintf(labels_dump, "{%ld}[%d] %s\n", indx + 1, array_of_labels[indx].pos_to_jmp, array_of_labels[indx].name_of_label);
    }

    fprintf(labels_dump, "\n******************************************************\n");

    fclose(labels_dump);

}

//-----------------------------------------------------------------
