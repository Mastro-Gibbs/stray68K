#ifndef __ASSEMBLER_TYPES_H__
#define __ASSEMBLER_TYPES_H__

#include "clowncommon.h"

#include "dictionary.h"
#include "strcmpci.h"
#include "syntactic.h"
#include "lexical.h"

#define EXIT_WARNING 2

typedef enum SymbolType
{
	SYMBOL_CONSTANT,
	SYMBOL_VARIABLE,
	SYMBOL_MACRO,
	SYMBOL_LABEL
} SymbolType;

typedef struct Location
{
	struct Location *previous;

	char *file_path;
	unsigned long line_number;
} Location;

typedef struct FixUp
{
	struct FixUp *next;

	Statement statement;
	unsigned long program_counter;
	long output_position;
	char *last_global_label;
	char *source_line;
	Location location;
	char *label;
} FixUp;

typedef struct SourceLineListNode
{
	struct SourceLineListNode *next;

	char *source_line;
} SourceLineListNode;

typedef struct SourceLineList
{
	SourceLineListNode *head;
	SourceLineListNode *tail;
} SourceLineList;

typedef struct SemanticState
{
	cc_bool success;
	FILE *output_file;
	FILE *listing_file;
    char *root_path;
	cc_bool equ_set_descope_local_labels;
	unsigned long program_counter;
	FixUp *fix_up_list_head;
	FixUp *fix_up_list_tail;
	cc_bool fix_up_needed;
	cc_bool doing_fix_up;
	cc_bool doing_final_pass;
	Dictionary_State dictionary;
	char *last_global_label;
	Location *location;
	yyscan_t flex_state;
	char line_buffer[1024];
	const char *source_line;
	unsigned int current_if_level;
	unsigned int false_if_level;
    char* _asseble_error;
	cc_bool end;
    cc_bool can_write_simhalt;


	enum
	{
		MODE_NORMAL,
		MODE_REPT,
		MODE_MACRO,
		MODE_WHILE
	} mode;
	union
	{
		struct
		{
			unsigned long repetitions;
			unsigned long line_number;
			SourceLineList source_line_list;
		} rept;
		struct
		{
			char *name;
			unsigned long line_number;
			IdentifierListNode *parameter_names;
			SourceLineList source_line_list;
			cc_bool is_short;
		} macro;
		struct
		{
			Expression expression;
			char *source_line;
			unsigned long line_number;
			SourceLineList source_line_list;
		} while_statement;
	} shared;
} SemanticState;

typedef struct Macro
{
	char *name;
	IdentifierListNode *parameter_names;
	SourceLineListNode *source_line_list_head;
} Macro;

#endif // __ASSEMBLER_TYPES_H__