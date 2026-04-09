#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// #define MAX_SCORES 6
uint8_t rings = 0;
uint16_t* scores = NULL;
uint8_t counter=0;
uint16_t total_arrows = 0;
uint16_t max_score = 0;
uint16_t final_score = 0;
float accuracy = 0.0f;

// function prototypes
int ring10(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);
int ring6(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);
int ring5(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);

int main(void)
{
    printf(" \n"
        "   _____ ___________________  \n"
        "  /  _  \\\\______   \\_   ___ \\ \n"
        " /  /_\\  \\|       _/    \\  \\/ \n"
        "/    |    \\    |   \\     \\____\n"
        "\\____|__  /____|_  /\\______  / \n"
        "        \\/       \\/       \\/  \n"
        "                            v1.0\n   "
    );

    printf("\nThe Accuracy Calculator For Archery.\n");
    printf("\nPress 'Enter' To Begin!\n");

    getchar();

    printf("[?] How Many Rings Are There On The Target (5, 6, and 10)?\n");
    scanf("%hhu", &rings);

    // use malloc to grab the empty space big enough for the value of "rings"
    // use malloc cuz it can be over-written during runtime
    scores = (uint16_t*)malloc(rings * sizeof(uint16_t));

    if (scores == NULL)
    {
        printf("MALLOC Failed!\n");
        return 1;
    }
     
    printf("Memory Allocated!\n");

    // printf("%d\n", rings);
    // printf("Insert The Hits Seperated By Spaces (Outer -> Inner Ring): \n");
    printf("[!] Insert The Hits Ranging From The Outer -> Inner Rings\n");

    while (counter < rings)
    {
        printf("Ring %d: ", counter + 1);

        if (scanf("%hu", &scores[counter]) == 1) counter++;
        else 
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
        }
    }

    printf("\nAll Scores Saved!\n");

    // Clearance
    // printf("\033[H\033[J");

    if (rings == 5) ring5(&final_score, &total_arrows, &max_score);
    else if (rings == 6) ring6(&final_score, &total_arrows, &max_score);
    else ring10(&final_score, &total_arrows, &max_score);

    // for (int i=0; i < rings; i++)
    // {
    //     // Find Total Arrows
    //     total_arrows += scores[i];

    //     // Find Finalized Score
    //     final_score += scores[i] * (i + 1);
    // }
    
    // // Find Max Score
    // max_score = total_arrows * rings;
    
    // Find Accuracy
    if (max_score > 0)
    {
        accuracy = ((float)final_score / (float)max_score) * 100.0f;
    }

    printf("\nArrow Hits: %d\n", total_arrows);
    
    printf("\nMax Score: %d\n", max_score);
    
    printf("\nFinal Score: %d\n", final_score);
    
    printf("\nAccuracy: %.2f%%\n", accuracy);

    // STONE FREE!
    free(scores);
    
    getchar();
    getchar();
}

int ring10(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    for (int i=0; i < 10; i++)
    {
        // printf("%d", scores[i]);
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 1);
        // Find Max Score (10 = max score)
        *_max_score = *_arrows * 10; 
    }
}

int ring6(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    // loop all the items
    for (int i=0; i < 6; i++)
    {
        // printf("%d", scores[i]);
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 5);
        // Find Max Score (10 = max score)
        *_max_score = *_arrows * 10; 
    }
}

int ring5(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    for (int i=0; i < 5; i++)
    {
        // printf("%d", scores[i]);
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 1);
        // Find Max Score (10 = max score)
        *_max_score = *_arrows * 5; 
    }
}