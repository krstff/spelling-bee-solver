#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char*read_line(FILE *file){
	int size = 0;
	int capacity = 16;
	char *buffer = malloc(capacity);
	char c;

	while((c = fgetc(file)) != EOF && c != '\n'){
		if(size == capacity){
			size *= 2;
			char *temp = realloc(buffer, size + 2);
			if(!temp){
				free(buffer);
				return "dopici";
			}
			buffer = temp;
		}
		buffer[size++] = c;
	}
	buffer[size] = '\0';
	return buffer;
}

void deletion(){
	FILE *all_words = fopen("all_words.txt", "r");
	FILE *all_longer_words = fopen("all_longer_words.txt", "w");
	if(!(all_longer_words && all_words)){
		return;
	}
	char *line = NULL;

    while(!feof(all_words)) {
		line = read_line(all_words);
		
		if(strlen(line) >= 4){
			// fputs(line, all_longer_words);
			// fputc(0, all_longer_words);
			fwrite(line, strlen(line), 1, all_longer_words);
			fwrite("\n", 1, 1, all_longer_words);
		}
		free(line);
	}
	fclose(all_words);
	fclose(all_longer_words);
}

int main(){
	deletion();
	return 0;
}
