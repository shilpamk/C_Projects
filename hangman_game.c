/* Guess the word */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main() {
	srand(time(NULL));
	char words[][10] = {"London", "Paris", "Madrid", "Phenix", "Mumbai"};
	int numWords = sizeof(words)/ sizeof(words[0]);
	printf("number of words: %d\n", numWords);
	int index = rand()% numWords;
	char *gw = words[index];
	int len = strlen(words[index]);
	// printf("Index: %d Word to guess:%s Length: %d\n", index, words[index], len);
	
	int fillup[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	
	char usrg[10];
	int flag = 1;
	int attempts = 0; 
	int i = 0;
	int guessCount = 0;
	while(attempts < len) {
		printf("\nUSER guess the word\n");
		fgets(usrg, 10, stdin);
		for(i=0; i<len; i++) {
			if(usrg[0] == words[index][i]) {
				if(fillup[i] == 1) {
					printf("Letter was already guessed!\n");
				} else {
					printf("Letter guessed right!\n");
					fillup[i] = 1;
					guessCount++;
					printf("guessCount: %d\n", guessCount);
				}
			} 
		}
		attempts ++;
		printf("Attempts: %d\n", attempts);
		for(i=0; i<len; i++) {
			if(fillup[i] == 1) {
				printf("%c ", words[index][i]);
			} else {
				printf(" - ");
			}
		}
		if((attempts == len) || (guessCount == len)) {
			printf("\nCheck for win\n");
			for(i=0; i<len; i++) {
				if(fillup[i] != 1) {
					printf("You did not guess all letters. Attempts over!");
					flag = 0;
					break;
				} 
			}
			break;
		}
	}
	if(flag) {
		printf("\nYOU WON!!!\n");
	} else {
		printf("\nYOU LOST...\n");
	}
	return 0;
}
