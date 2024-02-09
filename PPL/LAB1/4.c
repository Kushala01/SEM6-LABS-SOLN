#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char word[] = "HeLLO"; // The word to be manipulated
    int word_length = strlen(word);

    printf("Process %d: Original word: %s\n", rank, word);

    for (int i = 0; i < word_length; i++) {
    if (i == rank && isalpha(word[i])) {
        if (islower(word[i])) {
            word[i] = toupper(word[i]); // Toggle lowercase to uppercase
        } else if (isupper(word[i])) {
            word[i] = tolower(word[i]); // Toggle uppercase to lowercase
        }
        printf("Process %d: Toggled word: %s\n", rank, word);
        break; // Break out of loop after toggling one character
    }
}
    MPI_Finalize();
    return 0;
}