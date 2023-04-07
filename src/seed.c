/**
 * @file seed.c
 *
 * @brief Module 
 *
 * @author Clément Hibon
 * @date 31 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>





/**
 * @brief Converti un caractère en int (code ascii)
 * 
 * @param c Le caractère à convertir
 * @return Le code ascii du caractère
 */
unsigned int charToInt(char c) {
    return (int)c;
}



/**
 * @brief Inverse une chaine de caractères
 * 
 * @param string La chaine de caractères à inverser
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
 * @brief Fonction convertissant un nombre en chaine de caractères
 * 
 * Une fonction itoa existe déjà mais aucune référence vers celle ci est fait lors de la compilation
 * 
 * @param n Le nombre à convertir
 * @param string La chaine de caractère finale
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
 * @brief Convertie une chaine de caractère en une chaine de caractère contenant le code ascii des caractère de la première chaine
 * 
 * @param string La chaine à convertir
 * @return La chaine de caractère ascii
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
 * @brief Converti une chaine de caractère en long long int
 * 
 * @param string La chaine de caractère à convertir
 * 
 * @return Un nombre correspondant à la chaine donnée en paramètre
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