#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

#define DICTIONARY "dictionary.txt"
#define TEXT "text.txt"
#define MAX_WORD_LENGTH 20
#define MATCH_LIMIT 3
#define MAX_SUB_WORDS 10


short isPunc(char ch){                                      /* Determines if the char is punctuation or not */
    char punctuations[] = {'.',',',':',';','?','(',')','[',']','\"','\'','!','-','\\','/' };
    int i;
    for(i=0; i<15; i++)
    {
        if(punctuations[i] == ch)
            return TRUE;
    }
    return FALSE;
}


int split(char word[], char subWords[MAX_SUB_WORDS][MAX_WORD_LENGTH]) {                 /* splits the strings as word and punctuations */

    int len = strlen(word);
    int x = 0, y = 0;

    int i;
    for (i = 0; i < len; ++i) {
        if (isPunc(word[i])) {
            if (y != 0)
                subWords[x++][y] = '\0';

            y = 0;
            subWords[x][y] = word[i];
            subWords[x++][y + 1] = '\0';
            y = 0;
            if (i == len - 1)
                return x;
        } else {
            subWords[x][y++] = word[i];
            if (i == len - 1) {
                subWords[x][y] = '\0';
                return x + 1;
            }
        }
    }
}
  short isVovel(char ch){
    char vovels[] = {'a','o','u','e','i'};                                      /* Determines if the character is vovel or not */
      int i;
      for (i = 0; i < 5; ++i)
            if( ch == vovels[i] )
                return TRUE;

      return FALSE;
}

void find_best_correction(char word[], char dictionary[], int diffLimit){

    FILE* dict;

    int i,j;
    int matchCounter = 0, matchCounter2 = 0;
    char word2[MAX_WORD_LENGTH];
    char matches[MATCH_LIMIT][MAX_WORD_LENGTH];                                         /* All required variables */
    char matches2[MATCH_LIMIT][MAX_WORD_LENGTH];
    short leastDiff= 127;
    char bestMatch[MAX_WORD_LENGTH];

    dict = fopen(dictionary,"r");

    while (1)
    {
        if(fscanf(dict,"%s", word2) != EOF)
        {
            int i;
            int len = strlen(word);
            int difference = 0;                                                                 /* Travels all words in the dictionary one by one and calculates differences with the word
                                                                                                    *                               and returns best one */

            for(i=0; i<len; i++){
                if(word[i] != word2[i] && word[i]+'a'-'A' != word2[i] && word[i] != word2[i]+'a'-'A' )
                    difference++;
            }
            difference += abs( strlen(word2) - len );

            if(difference == 0 )
            {
                strcpy(word,word2);
                return;
            }
            if(difference <= diffLimit && matchCounter <= MATCH_LIMIT )
                for (i = 0; i <= matchCounter; ++i) {
                    if (strcmp(matches[i], word2) == 0)
                        break;
                    else if (i == matchCounter)
                    {
                        strcpy(matches[matchCounter++],word2);
                        break;
                    }
                }

        }

        else
            break;
    }

    if(matchCounter == 1) {
        strcpy(word, matches[0]);
        return;
    }
    if(matchCounter > 1) {
        for (i = 0; i < matchCounter; ++i) {
            int size = strlen(matches[i]);
            for (j = 0; j < size; ++j) {
                if (matches[i][j] != word[j] && !isVovel(word[j]) && isVovel(matches[i][j]))                        /* if there are more than 1 matches then looks for vovel situation */
                    strcpy(matches2[matchCounter2++], matches[i]);
            }
        }

        if (matchCounter2 == 1) {
            strcpy(word, matches2[0]);
            return;
        }
        if (matchCounter2 > 1){
            strcpy(word,matches2[1]);
            return;
        }
        if (matchCounter2 == 0) {                                                           /* if match is 1 then returns it */
            strcpy(word,matches[1]);
            return;
        }
    }

}


void fix(char text[], char dictionary[],int diffLimit){                     /* fix the text file according to the given difference limit */
    FILE* txt, *temp;
    char word[MAX_WORD_LENGTH];

    txt = fopen(text,"r");
    temp = fopen("temp","w");

    while (1)
    {
        if(fscanf(txt,"%s", word) != EOF)
        {
            char correctWord[MAX_WORD_LENGTH];
            char subWords[MAX_SUB_WORDS][MAX_WORD_LENGTH];
            int size = split(word,subWords);
            char subCorrect[MAX_WORD_LENGTH];

			int i;
            correctWord[0]='\0';

            for(i=0; i<size; i++){

                if(strlen(subWords[i]) != 1) {
                    char before[MAX_WORD_LENGTH];
                    strcpy(before,subWords[i]);
                    find_best_correction(subWords[i], dictionary,diffLimit);
                    if( before[0] > 64 && before[0] <91 && before[0]+32 == subWords[i][0] )                                   /*if its first letter is uppercase*/
                        subWords[i][0] = before[0];
                        strcat(correctWord,subWords[i]);
                }
                else
                    strcat(correctWord,subWords[i]);
            }

            printf("%s ",correctWord);                                                                  /* prints the string to the file and screen */
            fprintf(temp,"%s ",correctWord);
        }
        else
            break;
    }

    fclose(temp);
    temp = fopen("temp","r");
    txt = fopen(text,"w");

    while (fscanf(temp,"%s", word) != EOF)
    {                                                                                       /* corrects  the text file by rewriting*/
        fprintf(txt,"%s ",word);
    }
    remove("temp");

}

void fix_spelling_error(char* text, char* dictionary){
    fix(text,dictionary,1);
}

void fix_spelling_error2(char* text, char* dictionary){
    fix(text,dictionary,2);
}


int main() {


    fix_spelling_error(TEXT, DICTIONARY);


}
