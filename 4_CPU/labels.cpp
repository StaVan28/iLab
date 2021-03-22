
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
int labels::check_label(char* name_of_label, int position, bool type)
{
	assert(name_of_label);
	assert(position >= POISON_POSETION);

	size_t tmp_IP = parsing_labels(name_of_label, type);
	size_t indx   = 0;

	while (indx < label_counter) {

		if (array_of_labels[indx].name_of_label == nullptr)
			break;

		if (!strcmp(array_of_labels[indx].name_of_label, name_of_label + tmp_IP)){

			if (position != POISON_POSETION) {
				array_of_labels[indx].position      = position;
				array_of_labels[indx].flag_complete = COMPLETE;
				return position;
			}
			
			return POISON_POSETION;
		}

		indx++;
	}

	if (array_of_labels[indx].flag_complete == UNCOMPLETE)
		add_label(name_of_label, position);

	return POISON_POSETION;
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

size_t labels::parsing_labels(char* name_of_label, bool type)
{
	assert(name_of_label);

	size_t tmp_IP = 0;

	if (type == MARK_SYMB) {
		const char* ptr_on_MARK_LABEL = strchr(name_of_label, MARK_LABEL);
		POINTER_ON_(name_of_label, (ptr_on_MARK_LABEL - name_of_label), char) = '\0';
	}
	else {
		tmp_IP = JMP_SIZE;
		while (isspace(name_of_label[tmp_IP]))
			tmp_IP++;				
	}

	return tmp_IP;
}

//-----------------------------------------------------------------

void labels::add_label(char* name_of_label, int position)
{
	assert(name_of_label);
	assert(position >= POISON_POSETION);

	if (label_counter == capacity)
		realloc_array_of_label();

	array_of_labels[label_counter].name_of_label = name_of_label;
	array_of_labels[label_counter].position      = position;

	label_counter++;
}

//-----------------------------------------------------------------

void labels::labels_dump(void)
{
	FILE* labels_dump = fopen("./txt/dump_labels.txt", "wb");
    assert(labels_dump);

    fprintf(labels_dump, "\n******************************************************\n");

    fprintf(labels_dump, "Pointer array of labels: %p\n\n", array_of_labels);

    fprintf(labels_dump, "Capacity = %ld\n", capacity);

    fprintf(labels_dump, "\n{Number in array}[position]\n\n");

    for (size_t indx = 0; indx < capacity; indx++) {
        fprintf(labels_dump, "{%ld}[%d] %s\n", indx, array_of_labels[indx].position, array_of_labels[indx].name_of_label);
    }

    fprintf(labels_dump, "\n******************************************************\n");

    fclose(labels_dump);

}

