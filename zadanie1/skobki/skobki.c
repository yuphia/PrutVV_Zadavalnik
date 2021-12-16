#include "stdlib.h"
#include "stdio.h"

int syntaxError (int isPrinter);
void isStructureCorrect (char* str);
void getG (char* str);
void getN();
void getE();
void getD();
void getP();
void getT();

char* string = nullptr;

int main()
{
    char str[10000] = {};
    scanf ("%s", str);

    isStructureCorrect (str);

    return 0;
}

void isStructureCorrect (char* str)
{
    getG (str);
}

void getG (char* str)
{
    string = str;

    getE();

    int counter = syntaxError (0);

    if (*(string) != '\0')
    {
        printf ("bebrastructure");
        syntaxError(1);
    }
    else if (counter == 1)
        printf ("bracket structure is ok\n");
}

void getE ()
{
    while (*string == '{' || *string == '(' || *string == '[' || *string == '<')
    {
        getN ();
    
        getT ();

        getP ();

        getD ();
    }
}

void getN()
{   
    while (*string == '{')
    {
        string++;
        getE ();
        
        if (*string != '}')
        {
            syntaxError(1);       
            break;
        }
        string++;
    }
}

void getD()
{   
    while (*string == '(')
    {
        string++;
        getE ();
        
        if (*string != ')')
        {
            syntaxError(1);       
            break;
        }
        string++;
    }
}

void getT()
{   
    while (*string == '[')
    {
        string++;
        getE ();
        
        if (*string != ']')
        {
            syntaxError(1);       
            break;
        }
        string++;
    }
}

void getP()
{   
    while (*string == '<')
    {
        string++;
        getE ();
        
        if (*string != '>')
        {
            syntaxError(1);       
            break;
        }
        string++;
    }
}

int syntaxError (int isPrinter)
{
    static int counter = 1;

//    printf ("counter = %d\n", counter);

    if (counter == 1 && isPrinter != 0)
        printf ("syntax error: Bracket structure is broken on symbol: %c\n", *string);

    counter++;
    return counter-1;
}
