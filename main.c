#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//  a date structure: used to hold any date data
struct date
{
    int d, m, y;
};

// declaration of month array
//  note: this is a non leap year's no. of days in a month list
int months[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

// checking leap year and returning required no. of days for February
int checkLeap(int year) 
{
    //  if leap year
    if((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        return 29;
    return 28;
}

// calculate in year, month and days format and return as a date structure
long dayDifference(struct date d1, struct date d2) 
{
    struct date lower, upper;
    int i;
    long day_number_lower = 0, day_number_upper = 0;

    if(d1.y > d2.y)
    {
        upper = d1;
        lower = d2;
    }
    else
    {
        upper = d2;
        lower = d1;
    }
    
    /*  calculating number of days for the upper year  */
    for (i = lower.y; i < upper.y; i++)
    {
        if (checkLeap(i) == 29)
            day_number_upper += 366;
        else
            day_number_upper += 365;
    }

    months[2] = checkLeap(upper.y);
    for (i = 1; i < upper.m; i++)
        day_number_upper += months[i];
    day_number_upper += upper.d;

    /*  calculating number of days for the lower year  */
    months[2] = checkLeap(lower.y);
    for (i = 1; i < lower.m; i++)
        day_number_lower += months[i];
    day_number_lower += lower.d;

    long diff = abs(day_number_upper - day_number_lower); // finding absolute date difference
    return diff;
}

//  returning day difference as a date structure
struct date format_date_diff(int diff)
{
    struct date d;
    int month, year;
    d.y = diff / 365;
    diff %= 365;
    d.m = diff / 30;
    diff %= 30;
    d.d = diff;

    return d;
}

int main(int argc, char const *argv[])
{
    struct date d1, d2;

    // input first date
    printf("Enter First date: ");
    scanf("%d%d%d", &d1.d, &d1.m, &d1.y);

    //  input second date
    printf("Enter Second date: ");
    scanf("%d%d%d", &d2.d, &d2.m, &d2.y);

    //  calculating difference
    struct date diff_d;
    long diff_i;
    diff_i = dayDifference(d1, d2);
    diff_d =format_date_diff(diff_i);

    printf("\nDifference is %d days OR %d years, %d months, %d days\n", diff_i, diff_d.y, diff_d.m, diff_d.d);

    return 0;
}
