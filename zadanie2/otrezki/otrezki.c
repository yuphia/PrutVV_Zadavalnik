#include "stdio.h"
#include "stdlib.h"

struct Segment
{
    int x1;
    int x2;
};

void printSegments (Segment* segments, int amountOfSegments);
void coverTheSegment (Segment* segments, int amountOfSegments);

int main()
{
    int amountOfSegments = 0;
    scanf ("%d", &amountOfSegments);

    if (amountOfSegments <= 0)
        return 1;

    Segment* theSegments = (Segment*) calloc (amountOfSegments, sizeof(Segment));

    for (int i = 0; i < amountOfSegments; i++)
        scanf ("%d %d", &(theSegments[i].x1), &(theSegments[i].x2));

    coverTheSegment (theSegments, amountOfSegments);

    return 0;
}

void printSegments (Segment* segments, int amountOfSegments)
{
    printf ("\n\nDumping the segments\n");
    for (int i = 0; i < amountOfSegments; i++)
    {
        if (i != amountOfSegments - 1)
            printf ("[%d, %d] V ", segments[i].x1, segments[i].x2);
        else
            printf ("[%d, %d]\n", segments[i].x1, segments[i].x2);
    }
}

void coverTheSegment (Segment* segments, int amountOfSegments)
{
    Segment *suitableSegments = (Segment*) calloc (1, sizeof (Segment));

    int size = 1, lowX1 = 0, highX2 = 0, targetSum = 10000, runThrough = 0;

    for (int sum = 0; sum < targetSum; sum+=highX2)
    {
        if (runThrough != 0)
        {
            suitableSegments = (Segment*)realloc (suitableSegments, (size+1)*sizeof(Segment));
            size++;
        }

        for (int i = 0; i < amountOfSegments; i++)
        {
            if (segments[i].x1 <= lowX1 && segments[i].x2 > highX2 && suitableSegments)
            {           
                suitableSegments[size-1].x1 = segments[i].x1;
                highX2 = suitableSegments[size-1].x2 = segments[i].x2;
            }
        }
        lowX1 = highX2;
        runThrough++;        
    }

    printSegments (suitableSegments, size);
}