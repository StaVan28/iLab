
#include "CPU.h"
#include "labels.h"

//-----------------------------------------------------------------

Labels::Labels(void) 
{
	// check Labels_t

	capacity_  = START_CAPACITY;

	array_of_labels_ = (label_info_t*) calloc(START_CAPACITY, sizeof(label_info_t));
	assert(array_of_labels_);
}

//-----------------------------------------------------------------

Labels::~Labels(void)
{
	// check Labels_t

	free(array_of_labels_);
	array_of_labels_ = nullptr;
}

//-----------------------------------------------------------------
//!TODO
int Labels::check_label(char* name_of_label, int pos_to_jmp, int func_call)
{
	assert(name_of_label);
	assert(pos_to_jmp >= POISON_POSITION);

	parsing_label(name_of_label, func_call);

	for (size_t indx = 0; indx < label_counter_; indx++) {
		if (!strcmp(array_of_labels_[indx].name_of_label, name_of_label)) {
			if (pos_to_jmp != POISON_POSITION)  {
				array_of_labels_[indx].pos_to_jmp = pos_to_jmp;
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

void Labels::parsing_label(char* name_of_label, int func_call) 
{
	assert(name_of_label);

	switch(func_call) {

		case FROM_JMP_CMD:		return;

		case FROM_MARK_LABEL:	const char* ptr_on_MARK_LABEL = strchr(name_of_label, MARK_LABEL);
								POINTER_ON_(name_of_label, (ptr_on_MARK_LABEL - name_of_label), char) = '\0';
								return;
	}
	
/*
*	if (func_call == FROM_JMP_CMD)
*		return;
*	else if (func_call == FROM_MARK_LABEL) {
*		const char* ptr_on_MARK_LABEL = strchr(name_of_label, MARK_LABEL);
*		POINTER_ON_(name_of_label, (ptr_on_MARK_LABEL - name_of_label), char) = '\0';
*		return;
*	}
*/

}
    
//-----------------------------------------------------------------

int Labels::find_label(char* name_of_label) 
{
	for(size_t indx = 0; indx < label_counter_; indx++) {
		if (!strcmp(name_of_label, array_of_labels_[indx].name_of_label))	
			return array_of_labels_[indx].pos_to_jmp;	
	}

	return POISON_POSITION;
}
//-----------------------------------------------------------------

void Labels::realloc_array_of_label(void)
{
	capacity_  *= 2;

	label_info_t* tmp_array_of_labels_ = array_of_labels_;

	array_of_labels_ = (label_info_t*) realloc(array_of_labels_, capacity_  * sizeof(label_info_t));

	if (array_of_labels_ == nullptr) {
		array_of_labels_ = tmp_array_of_labels_;
		// error
	}

}

//-----------------------------------------------------------------

void Labels::add_label(char* name_of_label, int pos_to_jmp)
{
	assert(name_of_label);
	assert(pos_to_jmp >= POISON_POSITION);

	if (label_counter_ == capacity_ )
		realloc_array_of_label();

	array_of_labels_[label_counter_].name_of_label = name_of_label;
	array_of_labels_[label_counter_].pos_to_jmp    = pos_to_jmp;

	label_counter_++;
}

//-----------------------------------------------------------------

void Labels::labels_dump(void)
{
	assert(this);

	FILE* labels_dump = fopen("./txt/dump_labels.txt", "wb");
    assert(labels_dump);

    fprintf(labels_dump, "\n******************************************************\n");

    fprintf(labels_dump, "		Labels:\n\n");

    fprintf(labels_dump, "Pointer array of labels: %p\n\n", array_of_labels_);

    fprintf(labels_dump, "capacity_       = %ld\n", capacity_ );
    fprintf(labels_dump, "Label counter = %ld\n", label_counter_);

    fprintf(labels_dump, "\n{Number in array}[position]\n\n");

    for (size_t indx = 0; indx < capacity_ ; indx++) {
        fprintf(labels_dump, "{%ld}[%d] %s\n", indx + 1, array_of_labels_[indx].pos_to_jmp, array_of_labels_[indx].name_of_label);
    }

    fprintf(labels_dump, "\n******************************************************\n");

    fclose(labels_dump);

}

//-----------------------------------------------------------------
