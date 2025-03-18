#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_numbers(int* arr, int min, int max);
int count_matches(int* arr, int* win);

int main() {
    int win[6] = {1, 12, 15, 30, 42, 43};
    int arr[6];
    srand(time(NULL));

    while (1) {
        generate_random_numbers(arr, 1, 49);
        int match_count = count_matches(arr, win);

        printf("%d matches: ", match_count);
        if (match_count < 6) {
            printf("Did not win\n");
        } else {
            printf("You Won!!!\n");
            break;
        }
    }

    return 0;
}

void generate_random_numbers(int* arr, int min, int max) {
    for (int i = 0; i < 6; i++) {
        int num;
        int unique;
        do {
            unique = 1;
            num = rand() % (max - min + 1) + min;
            for (int j = 0; j < i; j++) {
                if (arr[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        arr[i] = num;
    }
}

int count_matches(int* arr, int* win) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (win[i] == arr[j]) {
                count++;
            }
        }
    }
    return count;
}
