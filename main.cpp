#include <random>

static const unsigned int c_numTests = 100000000;

int main(int argc, char** argv)
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> dist(1, 10);

    printf("Guess a number between 1 and 10.\n");
    printf("How often does guessing 5 win vs a random guess? %u trials each test.\n\n", c_numTests);

    // without wrap around
    {
        printf("Without wrap around...\n");
        int wins = 0;
        int ties = 0;
        int losses = 0;
        for (unsigned int i = 0; i < c_numTests; ++i)
        {
            int number = dist(rng);
            int randomGuess = dist(rng);

            int distanceFrom5 = abs(number - 5);
            int distanceFromRandomGuess = abs(number - randomGuess);

            if (distanceFrom5 < distanceFromRandomGuess)
                wins++;
            else if (distanceFrom5 == distanceFromRandomGuess)
                ties++;
            else
                losses++;
        }
        printf("Wins: %0.2f%%\n", 100.0f * float(wins) / float(c_numTests));
        printf("Ties: %0.2f%%\n", 100.0f * float(ties) / float(c_numTests));
        printf("Losses: %0.2f%%\n\n", 100.0f * float(losses) / float(c_numTests));
    }

    // with wrap around
    {
        printf("With wrap around...\n");
        int wins = 0;
        int ties = 0;
        int losses = 0;
        for (unsigned int i = 0; i < c_numTests; ++i)
        {
            int number = dist(rng);
            int randomGuess = dist(rng);

            int distanceFrom5 = abs(number - 5);
            if (distanceFrom5 > 5)
                distanceFrom5 = 10 - distanceFrom5;

            int distanceFromRandomGuess = abs(number - randomGuess);
            if (distanceFromRandomGuess > 5)
                distanceFromRandomGuess = 10 - distanceFromRandomGuess;

            if (distanceFrom5 < distanceFromRandomGuess)
                wins++;
            else if (distanceFrom5 == distanceFromRandomGuess)
                ties++;
            else
                losses++;
        }
        printf("Wins: %0.2f%%\n", 100.0f * float(wins) / float(c_numTests));
        printf("Ties: %0.2f%%\n", 100.0f * float(ties) / float(c_numTests));
        printf("Losses: %0.2f%%\n\n", 100.0f * float(losses) / float(c_numTests));
    }

    return 0;
}
