#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// #define MAX_SCORES 6
uint8_t rings = 0;
uint8_t counter=0;
uint8_t misses=0;
uint16_t* scores = NULL;
uint16_t total_arrows = 0;
uint16_t max_score = 0;
uint16_t final_score = 0;
float accuracy = 0.0f;
const char* rating;

int scanf_result;

// function prototypes
void ring10(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);
void ring6(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);
void ring5(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score);

int main(void)
{
    printf(" \n\033[1;31m"
        "   _____ __________  _____   \n"
        "  /  _  \\\\______   \\/  _  \\  \n"
        " /  /_\\  \\|     ___/  /_\\  \\ \n"
        "/    |    \\    |  /    |    \\\n"
        "\\____|__  /____|  \\____|__  /\n"
        "        \\/                \\/ \n"
        "                            \033[0m v1.0\n   ");

    printf("\n \033[1;31m[ ARCHERY PERFORMANCE ANALYTICS ]\033[0m\n");
    printf(" ----------------------------------------\n");
    printf(" Use this tool to track precision across\n");
    printf(" 5, 6, and 10-ring target configurations.\n");
    printf(" ----------------------------------------\n");
    printf("\n \033[1;37mPress 'Enter' to Begin\033[0m");

    // printf("\nThe Accuracy Calculator For Archery.\n");
    // printf("\nPress 'Enter' to begin!\n");

    getchar();

    // Clearance
    printf("\033[H\033[J");

    do 
    {
        printf("[\033[1;33m?\033[0m] Target Configuration (5, 6, or 10)?\n> ");
        scanf_result = scanf("%hhu", &rings);
        printf("\n");
        if (scanf_result != 1 || (rings != 5 && rings != 6 && rings != 10))
        {
            printf("[\033[1;31m!\033[0m] Invalid choice. Please try again.\n");

            while (getchar() != '\n');
        }

    } while (scanf_result != 1 || (rings != 5 && rings != 6 && rings != 10));

    do
    {
        printf("[\033[1;33m?\033[0m] Total Missed Arrows?\n> ");
        scanf_result = scanf("%hhu", &misses);
        printf("\n");
        if (scanf_result != 1)
        {
            printf("[\033[1;31m!\033[0m] Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
        }

    } while (scanf_result != 1 );

    // use malloc to grab the empty space big enough for the value of "rings"
    // use malloc cuz it can be over-written during runtime
    scores = (uint16_t*)malloc(rings * sizeof(uint16_t));

    if (scores == NULL)
    {
        printf("[\033[1;31m!\033[0m] Memory Allocation Failed!\n");
        return 1;
    }
     
    // printf("Memory Allocated!\n");

    printf("[\033[1;33m?\033[0m] Input Hits (Outer to Inner)\n");

    while (counter < rings)
    {
        printf("Ring %d: ", counter + 1);

        if (scanf("%hu", &scores[counter]) == 1) counter++;
        else 
        {
            printf("[\033[1;31m!\033[0m] Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
        }
    }

    // printf("\nAll Scores Saved!\n");

    // Clearance
    printf("\033[H\033[J");

    // Add Misses To Total Arrow Count
    total_arrows += misses;

    if (rings == 5) ring5(&final_score, &total_arrows, &max_score);
    else if (rings == 6) ring6(&final_score, &total_arrows, &max_score);
    else if (rings == 10) ring10(&final_score, &total_arrows, &max_score);
    else
    {
        printf("[\033[1;31m!\033[0m] Unsupported ring count! Exiting.\n");
        free(scores);
        return 1;
    }

    // Find Accuracy
    if (max_score > 0)
    {
        accuracy = ((float)final_score / (float)max_score) * 100.0f;
    }

    if (accuracy >= 90) rating = "Marksman";
    else if (accuracy >= 75) rating = "Proficient";
    else if (accuracy >= 50) rating = "Needs Practice";
    else rating = "Get a Coach";

    printf("\n\033[1;32m==========================================\033[0m\n");
    printf("           PERFORMANCE SUMMARY            \n");
    printf("\033[1;32m==========================================\033[0m\n");
    printf("  %-20s : %u\n", "Total Arrows Shot", total_arrows);
    // printf("  %-20s : %u\n", "Total Arrows Shot", total_arrows);
    printf("  %-20s : %u\n", "Missed Arrows", misses);
    printf("  %-20s : %u / %u\n", "Final Score", final_score, max_score);
    printf("------------------------------------------\n");
    printf("  %-20s : \033[1;33m%.2f%%\033[0m\n", "Accuracy Rating", accuracy);
    printf("  %-20s : %s\n", "Rank", rating);
    printf("\033[1;32m==========================================\033[0m\n");

    // printf("[$] FINAL RESULT \n");

    // printf("\nArrow Hits: %d\n", total_arrows);
    
    // printf("\nMax Score: %d\n", max_score);
    
    // printf("\nFinal Score: %d\n", final_score);
    
    // printf("\nAccuracy: %.2f%%\n", accuracy);

    // STONE FREE!
    free(scores);
    
    getchar();
    getchar();
}

void ring10(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    for (int i=0; i < rings; i++)
    {
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 1);
    }
    // Find Max Score (10 = max score)
    *_max_score = *_arrows * 10;
}

void ring6(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    // loop all the items
    for (int i=0; i < rings; i++)
    {
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 5);
    }
    // Find Max Score (10 = max score)
    *_max_score = *_arrows * 10;
}

void ring5(uint16_t* _score, uint16_t* _arrows, uint16_t* _max_score)
{
    for (int i=0; i < rings; i++)
    {
        // Find Total Arrows
        *_arrows += scores[i];
        // Find Final Score
        *_score += scores[i] * (i + 6); // 6, 7, 8, 9, 10                                                             
    }
    // Find Max Score (10 = max score)
    *_max_score = *_arrows * 10;
}