
#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

//-----------------------------------------------------------------


//-----------------------------------------------------------------

static const int  POISON_POSETION = -1;

static const bool JUMP      = 0;
static const bool MARK_SYMB = 1;

static const char MARK_LABEL = ':';

//-----------------------------------------------------------------

struct label_info_t {
	char* name_of_label = nullptr;
	int   position      = POISON_POSETION;
};

//-

class labels {

private:

	size_t capacity = 0;

	void   realloc_array_of_label(void);
	size_t parsing_labels(char* name_of_label, bool type);
	void   add_label     (char* name_of_label, int position);

public:

	label_info_t* array_of_labels = nullptr;
	size_t        label_counter   = 0;

	labels(void);
	~labels(void);

	labels(const labels&)              = delete;
	labels& operator = (const labels&) = delete;

	int check_label (char* name_of_label, int position, bool type);
	
};

//-----------------------------------------------------------------

//-----------------------------------------------------------------

//-----------------------------------------------------------------

//-----------------------------------------------------------------

//-----------------------------------------------------------------

//-----------------------------------------------------------------


#endif // CPU_H_INCLUDED