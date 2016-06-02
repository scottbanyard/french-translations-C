// scott banyard summer 2015 - greatly improved in march 2016 (covers 0 - 99999 number translations)
// very basic french program that translates numbers, months and colours with little tests - created to recap C and to recap basic french

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// declaring functions
void colourstest();
void numberstest();
void monthstest();
void upperCase(char a[]);
char toupper();
int isspace(); // used to check if space in array

// max number for questions in number test
int const MAX_NUMBER_FOR_TESTS = 200;

// translations from 0-19
char *translations[22] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept",
										"huit", "neuf", "dix", "onze", "douze", "treize", "quatorze",
										"quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
// translations for 10, 20, 30... 100
char *multiples[13] = {"", "dix", "vingt", "trente", "quarante", "cinquante", "soixante", "soixante-dix",
										"quatre-vingt", "quatre-vingt-dix", "cent", "mille"};


// removes whitespace at end of string
void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

// returns number translation in a buffer array
void numbers(int i, char* buff) {
	// // keep answer inside this array to return
	char finalAnswer[50];
	// // clears finalAnswer array incase want to know another number
	// memset(&finalAnswer[0], 0, sizeof(finalAnswer));
	// get from array using i as index
	if (i >= 0 && i <= 19) {
		strcpy(buff, translations[i]);
		// printf("%s", answer);
	} else {
		// get number length (number of digits)
		int nDigits = floor(log10(abs(i))) + 1;

		// error catching - no translations for over 100,000 at the moment
		if (nDigits >= 6) {
			printf("Please enter a number between 0 - 99999.\n");
		} else {

			// track each digit
			char* eachDigit[nDigits];
			int k = 0;
			int savedDigit;
			// put each digit into an array
				for (int e = 0; e < nDigits; e++) {
					// get digit
					k = i % 10;
					// first digit will be 1, 2, 3,...
					if (e == 0) {
						eachDigit[e] = translations[k];
					// second digit will be 10, 20, 30....
					} else if (e == 1) {
						eachDigit[e] = multiples[k];
					//third digit will be 100, 200, 300...
					} else if (e == 2) {
						// if 100, only say cent not un cent
						if (k == 1) {
							eachDigit[e] = multiples[10];
						} else if (k >= 2 && k <= 9) {
							char hundredValue[13] = "";
							// get value of hundred i.e. one hundred, two hundred etc
							strcpy(hundredValue, translations[k]);
							strcat(hundredValue, " ");
							// add on cent
							strcat(hundredValue, multiples[10]);
							eachDigit[e] = hundredValue;
						} else {
							// else will be zero - don't need to print that
							eachDigit[e] = "";
						}
					} else if (e == 3) {
						if (nDigits != 5) {
							if (k == 1) {
								eachDigit[e] = multiples[11];
							} else if (k >= 2 && k <= 9){
								char thousandValue[13] = "";
								// get value of hundred i.e. one hundred, two hundred etc
								strcpy(thousandValue, translations[k]);
								strcat(thousandValue, " ");
								// add on mille
								strcat(thousandValue, multiples[11]);
								eachDigit[e] = thousandValue;
							} else {
								// will be zero - don't need to print
								eachDigit[e] = "";
							}
						} else {
							savedDigit = k;
							// put mille into eachDigit
							eachDigit[e] = multiples[11];
						}
					} else if (e == 4) {
						// if in 10 thousands, use translations from 10 - 19
						if (k == 1) {
							// multiply current digit by 10 and add on previous digit i.e. 12000 = 1 | 2 as digits, 1*10 = 10 + 2 = 12
							int value = (k * 10) + savedDigit;
							eachDigit[e] = translations[value];
						} else {
							char thousandValue[25] = "";
							// get value of hundred i.e. one hundred, two hundred etc
							strcpy(thousandValue, multiples[k]);
							// if theres a second digit (not zero) then add that on
							if (savedDigit >= 2 && savedDigit <= 9) {
								strcat(thousandValue, " ");
								// add on second digit
								strcat(thousandValue, translations[savedDigit]);
							}
							eachDigit[e] = thousandValue;
						}
					}
					// go to next digit
					i /= 10;
			}

			int index = 0;
			// build together a string with spaces where necessary - may create unnecessary whitespace at end
			for (int f = nDigits-1; f >= 0; f--) {
				// if zero, then don't print i.e. not trente zero but trente (strcmp returns 0 if true) (same for "")
				if (strcmp(eachDigit[f], "zero")) {
					if (strcmp(eachDigit[f], "")) {
						strcat(finalAnswer, eachDigit[f]);
						strcat(finalAnswer, " ");
					}
				}
			}

			// remove uneccessary whitespace at end of string
			trim(finalAnswer);
			finalAnswer[strlen(finalAnswer)] = '\0';
			// copy final string into buffer to return to caller
			strcpy(buff, finalAnswer);
		}
	}
}



void months(char* month, char* buff) {
	if(strcmp(month, "january")==0) {
		strcpy(buff, "janvier");
	}
	else if(strcmp(month, "february")==0) {
		strcpy(buff, "fevrier");
	}
	else if(strcmp(month, "march")==0) {
		strcpy(buff, "mars");
	}
	else if(strcmp(month, "april")==0) {
		strcpy(buff, "avril");
	}
	else if(strcmp(month, "may")==0) {
		strcpy(buff, "mai");
	}
	else if(strcmp(month, "june")==0) {
		strcpy(buff, "juin");
	}
	else if(strcmp(month, "july")==0) {
		strcpy(buff, "juillet");
	}
	else if(strcmp(month, "august")==0) {
		strcpy(buff, "aout");
	}
	else if(strcmp(month, "september")==0) {
		strcpy(buff, "septembre");
	}
	else if(strcmp(month, "october")==0) {
		strcpy(buff, "octobre");
	}
	else if(strcmp(month, "november")==0) {
		strcpy(buff, "novembre");
	}
	else if(strcmp(month, "december")==0) {
		strcpy(buff, "decembre");

	}
	else {
		printf("That is not a valid month.");
	}
}

void colours(char* colour, char* buff) {
	if(strcmp(colour, "red")==0) {
		strcpy(buff, "rouge");
	}
	else if(strcmp(colour, "blue")==0) {
		strcpy(buff, "bleu");
	}
	else if(strcmp(colour, "green")==0) {
		strcpy(buff, "vert");
	}
	else if(strcmp(colour, "yellow")==0) {
		strcpy(buff, "jaune");
	}
	else if(strcmp(colour, "white")==0) {
		strcpy(buff, "blanc");
	}
	else if(strcmp(colour, "black")==0) {
		strcpy(buff, "noir");
	}
	else if(strcmp(colour, "grey")==0) {
		strcpy(buff, "gris");
	}
	else if(strcmp(colour, "orange")==0) {
		strcpy(buff, "orange");
	}
	else if(strcmp(colour, "brown")==0) {
		strcpy(buff, "marron");
	}
	else if(strcmp(colour, "pink")==0) {
		strcpy(buff, "rose");
	}
	else if(strcmp(colour, "blonde")==0) {
		strcpy(buff, "blond");
	}
	else if(strcmp(colour, "purple")==0) {
		strcpy(buff, "violet");
	}
	else {
		printf("We do not have any translation for that colour, sorry.");
	}

}

void colourstest() {
	int score = 0;
	int numQuestions = 0;
	// array so can use random number to choose index and therefore a random question
	char englishColours[12][10] = {"red", "blue", "green", "yellow", "white", "black", "grey", "orange", "brown", "pink", "blonde", "purple"};

	printf("How many questions would you like?\n");
	scanf("%d", &numQuestions);
	printf("\n");

	if (numQuestions < 0) {
		printf("\nYou can't choose less than 0 questions.\n");
		return;
	}

	/* skip first fgets - newline in stdin from scanfs but fflush(stdin) not working
	, so first fgets always skips in for loop - would replace all scanfs with fgets
	but too lazy atm so just skip this fgets outside loop*/
	char *colour = malloc (15);
	fgets(colour, 15, stdin);
	free(colour);

	// set random to always randomized even when currently processing - without this
	// random will always be the same numbers whenever program is re-run
	srand(time(NULL));

	// ask questions
	for (int i = 0; i < numQuestions; i++) {
		char buffer[15] = "";

		// generate random number to test
		int randColour = rand() % 11;
		printf("\nWhat is ");
		printf("%s", englishColours[randColour]);
		printf(" in French?\n");

		char *colour = malloc (15);
		// get the month, with size limit.
		fgets(colour, 15, stdin);

		// Remove trailing newline, if there. //
		if ((strlen(colour)>0) && (colour[strlen (colour) - 1] == '\n'))
		colour[strlen (colour) - 1] = '\0';

		// use english month to find translation into french and put in buffer
		colours(englishColours[randColour], buffer);

		// check correct answer and input answer
		if (strcmp(colour, buffer)==0) {
			printf("That's correct!\n");
			score++;
		} else {
			printf("That's incorrect! The correct answer is: ");
			printf("%s", buffer);
			printf("\n");
		}

		// reset buffer by clearing it
		memset(&buffer[0], 0, sizeof(buffer));
	}

	printf("The test is over. You scored %d out of %d!\n", score, numQuestions);
}

void monthstest() {
	int score = 0;
	int numQuestions = 0;
	// array so can use random number to choose index and therefore a random question
	char englishMonths[12][15] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};

	printf("How many questions would you like?\n");
	scanf("%d", &numQuestions);
	printf("\n");

	if (numQuestions < 0) {
		printf("\nYou can't choose less than 0 questions.\n");
		return;
	}

	/* skip first fgets - newline in stdin from scanfs but fflush(stdin) not working
	, so first fgets always skips in for loop - would replace all scanfs with fgets
	but too lazy atm so just skip this fgets outside loop*/
	char *month = malloc (15);
	fgets(month, 15, stdin);
	free(month);

	// set random to always randomized even when currently processing - without this
	// random will always be the same numbers whenever program is re-run
	srand(time(NULL));

	// ask questions
	for (int i = 0; i < numQuestions; i++) {
		char buffer[15] = "";

		// generate random number to test
		int randMonth = rand() % 11;
		printf("\nWhat is ");
		printf("%s", englishMonths[randMonth]);
		printf(" in French?\n");

		char *month = malloc (15);
		// get the month, with size limit.
		fgets(month, 15, stdin);

		// Remove trailing newline, if there. //
		if ((strlen(month)>0) && (month[strlen (month) - 1] == '\n'))
		month[strlen (month) - 1] = '\0';

		// use english month to find translation into french and put in buffer
		months(englishMonths[randMonth], buffer);

		// check correct answer and input answer
		if (strcmp(month, buffer)==0) {
			printf("That's correct!\n");
			score++;
		} else {
			printf("That's incorrect! The correct answer is: ");
			printf("%s", buffer);
			printf("\n");
		}

		// reset buffer by clearing it
		memset(&buffer[0], 0, sizeof(buffer));
	}

	printf("The test is over. You scored %d out of %d!\n", score, numQuestions);

}

void numberstest() {
	int score = 0;
	int numQuestions = 0;

	printf("How many questions would you like?\n");
	scanf("%d", &numQuestions);
	printf("\n");

	if (numQuestions < 0) {
		printf("\nYou can't choose less than 0 questions.\n");
		return;
	}

	// set random to always randomized even when currently processing - without this
	// random will always be the same numbers whenever program is re-run
	srand(time(NULL));

	/* skip first fgets - newline in stdin from scanfs but fflush(stdin) not working
	, so first fgets always skips in for loop - would replace all scanfs with fgets
	but too lazy atm so just skip this fgets outside loop*/
	char *number = malloc (100);
	fgets(number, 100, stdin);
	free(number);

	// ask questions
	for (int i = 0; i < numQuestions; i++) {
		char buffer[50] = "";

		// generate random number to test
		int testNum = rand() % MAX_NUMBER_FOR_TESTS;
		printf("\nWhat is ");
		printf("%d", testNum);
		printf(" in French?\n");

		char *number = malloc (100);
		// get the number, with size limit.
	  fgets(number, 100, stdin);

		// Remove trailing newline, if there. //
 		if ((strlen(number)>0) && (number[strlen (number) - 1] == '\n'))
		number[strlen (number) - 1] = '\0';

		// get correct answer by putting into buffer
		numbers(testNum, buffer);
		// check correct answer and input answer
		if (strcmp(number, buffer)==0) {
			printf("That's correct!\n");
			score++;
		} else {
			printf("That's incorrect! The correct answer is: ");
			printf("%s", buffer);
			printf("\n");
		}

		// reset buffer by clearing it
		memset(&buffer[0], 0, sizeof(buffer));
	}

	printf("The test is over. You scored %d out of %d!\n", score, numQuestions);
}

// turns all chars in array to uppercase
void upperCase(char a[]) {
	int i;
	for (i = 0; i < strlen(a); i++) {
		a[i] = toupper(a[i]);
	}
}

int main() {

	char choice[10];

	// switchboard
	printf("What would you like to know? Numbers, months or colours?\n");
	scanf("%s", choice);
	upperCase(choice);
	if(strcmp(choice, "NUMBERS")==0 || strcmp(choice, "N")==0) {
		int numCarryOn = 1;
		int i;
		while (numCarryOn) {
			printf("Please enter a number: ");
			scanf("%d", &i);
			char buffer[50];
			numbers(i, buffer);
			printf("%s\n", buffer);
			memset(&buffer[0], 0, sizeof(buffer));
			printf("Do you want to know any more numbers? Y/N\n");
			char yesno[3];
			scanf("%s", yesno);
			upperCase(yesno);
			if(strcmp(yesno, "YES")==0 || strcmp(yesno, "Y")==0) {
				numCarryOn = 1;
			} else {
				numCarryOn = 0;
				printf("Do you want to take a quick numbers test? Y/N\n");
				scanf("%s", yesno);
				upperCase(yesno);
				if(strcmp(yesno, "YES")==0 || strcmp(yesno, "Y")==0) {
					numberstest();
				}
			}
		}
	}
	else if (strcmp(choice, "MONTHS")==0 || strcmp(choice, "M") == 0) {
		int monCarryOn = 1;
		while (monCarryOn) {
			char buffer[15];
			char month[10];
			printf("Please enter a month: ");
			scanf("%s", month);
			months(month, buffer);
			printf("%s\n", buffer);
			memset(&buffer[0], 0, sizeof(buffer));
			printf("Do you want to know any more months? Y/N\n");
			char yesno[3];
			scanf("%s", yesno);
			upperCase(yesno);
			if (strcmp(yesno, "YES")== 0 || strcmp(yesno, "Y")==0) {
				monCarryOn = 1;
			} else {
				monCarryOn = 0;
				printf("Do you want to take a quick months test? Y/N\n");
				scanf("%s", yesno);
				upperCase(yesno);
				if (strcmp(yesno, "YES")== 0 || strcmp(yesno, "Y")==0) {
					monthstest();
				}
			}
		}
	}
	else if (strcmp(choice, "COLOURS")==0 || strcmp(choice, "C")==0) {
		int colCarryOn = 1;
		while (colCarryOn) {
			char buffer[15];
			char colour[10];
			printf("Please enter a colour: ");
			scanf("%s", colour);
			colours(colour, buffer);
			printf("%s\n", buffer);
			memset(&buffer[0], 0, sizeof(buffer));
			printf("Do you want to know any more colours? Y/N\n");
			char yesno[3];
			scanf("%s", yesno);
			upperCase(yesno);
			if (strcmp(yesno, "YES")== 0 || strcmp(yesno, "Y")==0) {
				colCarryOn = 1;
			} else {
				colCarryOn = 0;
				printf("Do you want to take a quick colours test? Y/N\n");
				scanf("%s", yesno);
				upperCase(yesno);
				if (strcmp(yesno, "YES")== 0 || strcmp(yesno, "Y")==0) {
					colourstest();
				}
			}
		}
	}
	else {
		printf("You have not chosen a category.\n");
	}

	// ends program successfully
	return 0;
}
