#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int day_Number(int day, int month, int year) {
    int dayNumber = 0, i;
    months[2] = checkLeap(year);
    for (i = 1; i < month; i++) {
        dayNumber += months[i];
    }
    dayNumber += day;
    
    for (i = 1; i < year; i++) {
        if (checkLeap(year) == 29) {
            dayNumber += 366;
        }
        else {
            dayNumber += 365;
        }
    }
    return dayNumber;
    
}

// display in year, month and days format

void displayFormat(int days) {
    int month, year;
    year = days / 365;
    days %= 365;
    month = days / 30;
    days %= 30;
    
    printf("Difference is %d years, %d months, %d days\n", year, month, days);
    
    
}

int main() {
    int day1, month1, year1, day2, year2, month2;
    
    // input first date
    
    printf("Enter First date: ");
    scanf("%d%d%d", &day1, &month1, &year1);
    
    //  input second date
    
    printf("Enter Second date: ");
    scanf("%d%d%d", &day2, &month2, &year2);
    
    int first = day_Number(day1, month1, year1);
    int second = day_Number(day2, month2, year2);
    int difference = abs(first - second); // finding absolute date difference
    
    displayFormat(difference);
    return 0;
    
}
