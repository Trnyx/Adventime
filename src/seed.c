/**
 * @file seed.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 31 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>





/**
 * @brief 
 * 
 * @param c 
 * @return unsigned int 
 */
unsigned int charToInt(char c) {
    return (int)c;
}



/**
 * @brief 
 * 
 * @param string 
 */
void reverse(char *string) {
    int i, j;
    char c;
 
    for (i = 0, j = strlen(string)-1; i<j; i++, j--) {
        c = string[i];
        string[i] = string[j];
        string[j] = c;
    }
}



/**
 * @brief 
 * 
 * @param n 
 * @param string 
 */
void myItoa(int n, char *string) {
    int i = 0, sign = n;

    if (sign < 0)
        n = -n;


    do {
        string[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);


    if (sign < 0) string[i++] = '-';
    string[i] = '\0';
        
    reverse(string);
}





/**
 * @brief 
 * 
 * @param string 
 * @return char* 
 */
char* convertionChaineEnChaineAscii(char *string) {
    char *seedString = calloc(strlen(string), sizeof(char));


    for (int i = 0; i < strlen(string); i++) {
        int ascii = charToInt(string[i]);
        
        char asciiString[3];
        myItoa(ascii, asciiString);

        strcat(seedString, asciiString);
    }


    return seedString;
}





/**
 * @brief 
 * 
 * @param string 
 */
long long int convertirEnSeed(char *string) {
    char* seedString = convertionChaineEnChaineAscii(string);

    const int seedInt = atoi(seedString);
    const long long int seedLonLongInt = atoll(seedString);


    free(seedString);


    if (seedLonLongInt > INT_MAX)
        return seedLonLongInt / seedInt;
    else return seedLonLongInt;
}