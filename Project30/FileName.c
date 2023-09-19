#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int NUM;
int NUM1;
int table[11] = { 0 };

int min(int arr[], int size);
int max(int arr[], int size);
int judge(int elevator_now, int min_passenger, int max_passenger);
int sum(int arr1[], int size);
void suspend(int passenger[], int elevator_now, int elevator_target[], int staging[], int size);
void add(int arr[], int x);
void element_remove(int arr[], int size, int x);
void keyfloor(int elevator_now, int TIME);

int main() {
    int elevator_now;
    int passenger[11] = { 0 };
    int elevator_target[11] = { 0 };
    int staging[11] = { 0 };
    int SUM = 0;
    int TIME = 0;
    int NUMBER = 0;

    printf("Please enter the number of passengers:");
    scanf("%d", &NUMBER);
    printf("Please enter the floor where the elevator is:");
    scanf("%d", &elevator_now);
    printf("Please enter your floor where you are and where you want to go: \n");

    int i = 0;
    int x, y;
    while (i < NUMBER) {
        scanf("%d %d", &x, &y);
        table[i] = x;
        passenger[x] = 1;
        staging[x] = y;
        i++;
    }

    int min_passenger;
    int max_passenger;
    SUM = sum(table, NUMBER);
    NUM = 0;
    NUM1 = 0;

    for (i = 0; table[i] == 0; i++)
        printf("%d %d %d\n", elevator_now, TIME, NUM);

    while (SUM != 0) {
        min_passenger = min(table, NUMBER);
        max_passenger = max(table, NUMBER);

        int direction = judge(elevator_now, min_passenger, max_passenger);

        if (direction == 1) {
            while (elevator_now < max_passenger) {
                elevator_now++;
                suspend(passenger, elevator_now, elevator_target, staging, NUMBER);
                TIME++;
                keyfloor(elevator_now, TIME);
            }
        }
        else if (direction == -1) {
            while (elevator_now > min_passenger) {
                elevator_now--;
                suspend(passenger, elevator_now, elevator_target, staging, NUMBER);
                TIME++;
                keyfloor(elevator_now, TIME);
            }
        }
        SUM = sum(table, NUMBER);
    }
    return 0;
}

int min(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return min;
}

int max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int judge(int elevator_now, int min_passenger, int max_passenger) {
    int ret = 0;
    if (elevator_now > min_passenger && min_passenger != 0) {
        ret = -1;
    }
    else if (elevator_now < max_passenger) {
        ret = 1;
    }

    return ret;
}

int sum(int arr1[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + arr1[i];
    }
    return sum;
}

void suspend(int passenger[], int elevator_now, int elevator_target[], int staging[], int size) {
    if (passenger[elevator_now] == 1) {
        int x;
        NUM++;
        passenger[elevator_now] = 0;
        x = staging[elevator_now];
        elevator_target[staging[elevator_now]] = 1;
        element_remove(table, size, elevator_now);
        add(table, x);
    }

    if (elevator_target[elevator_now] == 1) {
        int x;
        NUM--;
        elevator_target[elevator_now] = 0;
        x = staging[elevator_now];
        element_remove(table, size, x);
    }
}

void add(int arr[], int x) {
    int size = sizeof(arr) / sizeof(arr[0]);
    arr[size] = x;
}

void element_remove(int arr[], int size, int x) {
    int j = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] != x) {
            arr[j] = arr[i];
            j++;
        }
    }
}

void keyfloor(int elevator_now, int TIME) {
    if (NUM != NUM1) {
        printf("%d %d %d\n", elevator_now, TIME, NUM);
    }
    NUM1 = NUM;
}
