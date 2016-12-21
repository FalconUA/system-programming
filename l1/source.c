#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// in plain C, you have to define this type
typedef enum { false, true } bool;

bool has_double_consonant(char* string){
	// reversed english alphabet:   zyxwvutsrqponmlkjihgfedcba
	const unsigned int bit_mask = 0b10111011111011111011101110;
	size_t i;
	for (i = 1; i < strlen(string); i++){
		char a = tolower(string[i]), b = tolower(string[i-1]);
		if (a == b && ((1 << (a - 'a')) & bit_mask)) 
			return true;
	}
	return false;
};

int main(int argc, char* argv[]){
	int file_count;
	const char* separators = " ,.!?\"\':][}{()\n\t-*&@#$%^";

	for (file_count = 1; file_count < argc; file_count++){
		FILE* text_file = fopen(argv[file_count], "r");
		char* line = NULL;
		size_t len = 0;
		ssize_t read;

		if (text_file == NULL){
			fprintf(stderr, "Cannot open file %s. Continue.", argv[file_count]);
			continue;
		}
		while (getline(&line, &len, text_file) != -1){
			char* word = strtok(line, separators);
			while (word != NULL){
				if (has_double_consonant(word))
					fprintf(stdout, "%s\n", word);
				word = strtok(NULL, separators);
			}
		}	
		fclose(text_file);
	}
	return 0;
}
