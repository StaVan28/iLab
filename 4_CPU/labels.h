
#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

//-----------------------------------------------------------------

static const int  POISON_POSITION = -1;

static const bool JUMP      = 0;
static const bool MARK_SYMB = 1;

static const char MARK_LABEL = ':';

//-----------------------------------------------------------------

struct label_info_t {
	char* name_of_label = nullptr;
	int   position      = POISON_POSITION;
};

//-

class labels {

	private:

		label_info_t* array_of_labels = nullptr;
		size_t        capacity        = 0;
		size_t        label_counter   = 0;

		void   realloc_array_of_label(void);
		size_t parsing_label(char* name_of_label);
		void   add_label    (char* name_of_label, int position);

	public:

		labels(void);
		~labels(void);

		labels(const labels&)              = delete;
		labels& operator = (const labels&) = delete;

		void check_label_jmp (char* name_of_label, int position);
		void check_label_mark(char* name_of_label, int position);

		int find_label(char* name_of_label);

		void labels_dump(void);
};

//-----------------------------------------------------------------

#endif // LABELS_H_INCLUDED