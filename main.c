#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  date structure
struct date
{
    int day, month, year;
};

// declaration of month array
int months[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

// checking leap year
int checkLeap(int year) {
    if((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))) {
        return 29;
    }
    return 28;
}

// returns days number
int day_Number(struct date d) {
    int dayNumber = 0, i;
    months[2] = checkLeap(d.year);
    for (i = 1; i < d.month; i++) {
        dayNumber += months[i];
    }
    dayNumber += d.day;

    for (i = 1; i < d.year; i++) {
        if (checkLeap(i) == 29) {
            dayNumber += 366;
        }
        else {
            dayNumber += 365;
        }
    }
    return dayNumber;
}

// calculate in year, month and days format and return as a date structure
struct date dayDifference(struct date d1, struct date d2) {
    int first = day_Number(d1);
    int second = day_Number(d2);
    int diff = abs(first - second); // finding absolute date difference

    struct date d;
    int month, year;
    d.year = diff / 365;
    diff %= 365;
    d.month = diff / 30;
    diff %= 30;
    d.day = diff;

    return d;
}

//  main function
int main() {
    struct date d1, d2;

    // input first date
    printf("Enter First date: ");
    scanf("%d%d%d", &d1.day, &d1.month, &d1.year);

    //  input second date
    printf("Enter Second date: ");
    scanf("%d%d%d", &d2.day, &d2.month, &d2.year);

    //  calculating difference
    struct date diff;
    diff = dayDifference(d1, d2);

    printf("\nDifference is %d years, %d months, %d days\n", diff.year, diff.month, diff.day);

    return 0;
}
