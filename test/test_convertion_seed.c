#include <stdio.h>
#include <stdlib.h>
#include <string.h>






unsigned int charToInt(char c) {
    return (int)c;
}





void reverse(char *string) {
    int i, j;
    char c;
 
    for (i = 0, j = strlen(string)-1; i<j; i++, j--) {
        c = string[i];
        string[i] = string[j];
        string[j] = c;
    }
}



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





char* convertionSeed(char *string) {
    char *seedString = calloc(strlen(string), sizeof(char));

    for (int i = 0; i < strlen(string); i++) {
        int ascii = charToInt(string[i]);
        printf("\t%c => %i\n", string[i], ascii);
        
        char asciiString[3];
        myItoa(ascii, asciiString);

        strcat(seedString, asciiString);
    }


    return seedString;
}





void testSeed(char *string) {
    printf("Convertion de la chaine \"%s\"\n", string);


    char* seedString = convertionSeed(string);
    printf("SEED String : %s\n", seedString);


    long long int seedFinal;
    const long long int seedLonLongInt = atoll(seedString);
    printf("SEED lli : %lli\n", seedLonLongInt);


    if (seedLonLongInt > INT_MAX) {
        const int seedInt = atoi(seedString);
        printf("SEED int : %i\n", seedInt);
        seedFinal = seedLonLongInt / seedInt;
    }
    else {
        seedFinal = seedLonLongInt;
    }




    printf("SEED final : %lli\n", seedFinal);


    printf("\n");
    free(seedString);
}










int main(void) {

    printf("Le seed est la concaténation du code ascii des caractères données en entrée\n");
    printf("Exemple : \n");
    printf("\tChaine originale \"ABC\" (65 66 67)");
    printf("\tSeed obtenue : 656667");
    printf("\nLe nombre maximum pouvant être contenue dans un 'long long int' est : 9223372036854775807.\n");
    printf("Contrairement au 'int' le 'long long int' n'overflow pas et donc ne boucle pas dans les négatifs\n");
    printf("Pour cela, si le 'long long int' est supérieur à INT_MAX, nous divisons alors, pour la même chaine obtenue, le résultat 'int' au résultat 'long long int'\n");
    printf("\n");



    char string[] = "test";
    char stringOverflow[] = "bonjour";


    testSeed(string);
    testSeed(stringOverflow);


    
    return EXIT_SUCCESS;
}