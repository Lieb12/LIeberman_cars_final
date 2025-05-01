#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// directional rows/columns
const static int north[3] = {12, 31, 40};
const static int south[3] = {21, 30, 49};
const static int east[2]  = {1, 9};
const static int west[2]  = {8, 16};

// delay between ticks in milliseconds
const int delay = 250;

char grid[50][256];

typedef struct {
    int x;
    int y;
    char dir;
} Car;

//places car on the grid with
void PlaceCar(Car *car, int x, int y) {
    car->x = x;
    car->y = y;
    car->dir = ' ';
}

int inArray(const int *arr, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return 1;
    }
    return 0;
}

void GetDirection(Car *car) {
    int options[4][2];
    int count = 0;

    if (inArray(north, 3, car->x) && car->y > 1)
        options[count][0] = car->x, options[count++][1] = car->y - 1;

    if (inArray(south, 3, car->x) && car->y < 16)
        options[count][0] = car->x, options[count++][1] = car->y + 1;

    if (inArray(east, 2, car->y) && car->x < 49)
        options[count][0] = car->x + 1, options[count++][1] = car->y;

    if (inArray(west, 2, car->y) && car->x > 12)
        options[count][0] = car->x - 1, options[count++][1] = car->y;

    if (count == 1) {
        car->x = options[0][0];
        car->y = options[0][1];
    } else if (count > 1) {
        int pick = rand() % count;
        car->x = options[pick][0];
        car->y = options[pick][1];
    }
}

void PrintGrid(Car cars[], int carCount) {
    FILE *f = fopen("grid_v2.txt", "r");
    if (!f) return;

    char temp[50][256];
    int lines = 0;
    while (fgets(temp[lines], 256, f)) lines++;
    fclose(f);
    printf("\n");

    for (int i = 0; i < carCount; i++) {
        int x = cars[i].x;
        int y = cars[i].y;
        if (y >= 0 && y < lines && x >= 0 && x < strlen(temp[y]))
            temp[y][x] = 'O';
    }

    system("cls");

    for (int i = 0; i < lines; i++) {
        printf("%s", temp[i]);
    }
}

int main() {
    srand(time(NULL));

    Car car1, car2, car3, car4, car5;
    PlaceCar(&car1, 12, 2);  // 16th and Montgomery
    PlaceCar(&car2, 12, 17); //16th and Oxford
    PlaceCar(&car3, 31, 3);  //Broad and Montgomery
    PlaceCar(&car4, 40, 10); // 13th and Cecil
    PlaceCar(&car5, 21, 9);  // 15th and CEcil

    Car cars[] = {car1, car2, car3, car4, car5};

    while (1) {
        for (int i = 0; i < 5; i++) {
            GetDirection(&cars[i]);
        }
        PrintGrid(cars, 5);
        usleep(delay * 1000);
    }

    return 0;
}