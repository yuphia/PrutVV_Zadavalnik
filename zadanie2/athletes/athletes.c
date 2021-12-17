#include <stdio.h>
#include <stdlib.h>
#include "fileInput/fileInputTreatment.h"

struct Athlete
{
    int weight;
    int strength;
};

struct OlympicTeam
{
    Athlete* athletes;
    int amountOfAthletes;
};

size_t skipSpaces (char* str);
char* skipNumbers (char* str);
void swap (Athlete *xp, Athlete *yp);
void printAthletes (OlympicTeam team);
void sortAthletes (OlympicTeam olympicAthletes);
int cmpAthletes (Athlete a1, Athlete a2);

int main ()
{
    FILE* inputFile = fopen ("input.txt", "r");
    Text text = {};
    
    
    transitFileToLineArray (inputFile, &text);

    Athlete* athletes = (Athlete*) calloc (text.nLines, sizeof(Athlete));

    for (int i = 0; i < text.nLines; i++)
    {
        text.lines[i].line += skipSpaces (text.lines[i].line);
        sscanf (text.lines[i].line, "%d %d", &(athletes[i].weight), &(athletes[i].strength));
        if (athletes[i].weight > athletes[i].strength)
        {
            printf ("Weight > strength\n");
        }
    }

    OlympicTeam olympicAthletes = {athletes, (int)text.nLines};

    printAthletes (olympicAthletes);

    sortAthletes (olympicAthletes);

    printAthletes (olympicAthletes);

    freeArrayLines (text.lines);
    free (text.textArray);
    free (athletes);
    fclose (inputFile);
    return 0;
}

size_t skipSpaces (char* str)
{
    size_t thisSymbolPlace = 0;
    for (; thisSymbolPlace < sizeof(str); thisSymbolPlace++)
    {
        if (*(str + thisSymbolPlace) != ' ')
            return thisSymbolPlace;
    }

    return thisSymbolPlace;
}

char* skipNumbers (char* str)
{
    while (isdigit (*str))
    {
        str++;
    }
    return str;
}

void swap(Athlete *xp, Athlete *yp)
{
    Athlete temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void sortAthletes (OlympicTeam olympicAthletes)
{
    int i = 0, j = 0;

    for (i = 0; i < olympicAthletes.amountOfAthletes - 1; i++)     
        for (j = 0; j < olympicAthletes.amountOfAthletes - i - 1; j++)
        {
            if (cmpAthletes (olympicAthletes.athletes[j], olympicAthletes.athletes[j+1]) > 0)
                swap(olympicAthletes.athletes + j, olympicAthletes.athletes + j + 1);
        }
}

int cmpAthletes (Athlete a1, Athlete a2)
{
    if (a1.weight > a2.weight)
        return -1;
    else if (a1.weight < a2.weight)
        return 1;
    else 
    {
        if (a1.strength > a2.strength)
            return -1;
        else if (a1.strength < a2.strength)
            return 1;
        else 
            return 0;
    }
}


void printAthletes (OlympicTeam team)
{
    printf ("\n\nDumping the elemtnts\n");
    for (int i = 0; i < team.amountOfAthletes; i++)
    {
        printf ("weight = %5d strength = %5d\n", team.athletes[i].weight, team.athletes[i].strength);
    }

    printf ("Finished dumping the elements\n\n");
}

