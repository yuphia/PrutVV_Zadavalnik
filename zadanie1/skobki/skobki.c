#include "stdlib.h"
#include "stdio.h"

void syntaxError ();
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

    if (*(string) != '\0')
        syntaxError();
    else
        printf ("Bracket structure is ok\n");
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
            syntaxError();       
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
            syntaxError();       
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
            syntaxError();       
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
            syntaxError();       
            break;
        }
        string++;
    }
}

void syntaxError ()
{
    static int counter = 1;

    if (counter == 1)
        printf ("syntax error: Bracket structure is broken on symbol: %c\n", *string);

    counter++;
}