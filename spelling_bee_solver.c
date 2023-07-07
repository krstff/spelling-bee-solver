#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


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
				return NULL;
			}
			buffer = temp;
		}
		buffer[size++] = c;
	}
	buffer[size] = '\0';
	return buffer;
}
bool contains(char *haystack, char needle){
	for(int i = 0; i < 7; i++){
		if(haystack[i] == needle){
			return true;
		}
	}
	return false;
}
char consists_only_of(char letters[7], char *word){
	for(int i = 0; i < strlen(word); i++){
		if(!contains(letters, word[i])){
			return false;
		}
	}
	return true;
}
void solve(char main, char letters[6]){
	FILE *all_words = fopen("all_longer_words.txt", "r");
	FILE *output = fopen("solution.txt", "w");

	if(!all_words || !output){
		printf("fail\n");
		return;
	}
	char *line = NULL;
	char all_letters[7];
    for(int i = 0; i < 6; i++){
        all_letters[i] = letters[i];
    }
	all_letters[6] = main;

	while(!feof(all_words)){
		line = read_line(all_words);
		if(line == NULL){
			break;
		}
		if(!consists_only_of(all_letters, line)){
			free(line);
			continue;
		}
        if(!contains(line, main)){
            free(line);
            continue;
        }
		fwrite(line, strlen(line), 1, output);
		fwrite("\n", 1, 1, output);
		free(line);
	}
	fclose(all_words);
	fclose(output);
	printf("Solution generated in solution.txt\n");
}

int main(void){
	printf("Input middle letter:");
	char main = getchar();
	char letters[6];
	char c;
	int inputed = 0;
	printf("Input six surrounding letters:");
	while(inputed != 6){
		if((c = getchar()) != '\n'){
			letters[inputed] = c;
			inputed++;
		}
	}
	printf("\n\nYou have inputed:\n Middle: %c\nSurrounding:", main);
	for (int i = 0; i < 6; i++) {
   		printf(" %c", letters[i]);
	}
	while((c = getchar()) != 'n'){
		printf("\n\nDo you wish to continue? If so input *y*, if no input *n*\n");
		if(c == 'y'){
			printf("Solving..\n");
			solve(main, letters);
			return 0;
		}
	}
	return 1;
}
