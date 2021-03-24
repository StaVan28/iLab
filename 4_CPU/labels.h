
#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

//-----------------------------------------------------------------

static const int  POISON_POSITION = -1;
static const char MARK_LABEL      = ':';

//-----------------------------------------------------------------

enum func_calls {
	FROM_JMP_CMD    = 0,
	FROM_MARK_LABEL = 1,
};

//-----------------------------------------------------------------

struct label_info_t {
	char* name_of_label = nullptr;
	int   pos_to_jmp    = POISON_POSITION;
};

//-

class labels {

	private:

		label_info_t* array_of_labels = nullptr;
		size_t        capacity        = 0;
		size_t        label_counter   = 0;

		void realloc_array_of_label(void);
		void parsing_label(char* name_of_label, int func_call);
		void add_label    (char* name_of_label, int pos_to_jmp);

	public:

		labels(void);
		~labels(void);

		labels(const labels&)              = delete;
		labels& operator = (const labels&) = delete;

		int  check_label(char* name_of_label, int pos_to_jmp, int func_call);
		int  find_label (char* name_of_label);

		void labels_dump(void);
};

//-----------------------------------------------------------------

#endif // LABELS_H_INCLUDED