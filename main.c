#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//  compare between the dates passed as which one is greater(comes later)
int compare_dates(struct date d1, struct date d2)
{
    if(d1.y == d2.y)
    {
        if(d1.m == d2.m)
        {
            if(d1.d == d2.d)
                return 0;   //  both the dates are same
            else if(d1.d > d2.d)
                return -1;  //  d1 is greater than d2
            else if(d2.d > d1.d)
                return 1;   //  d2 is greater than d1
        }
        else if(d1.m > d2.m)
                return -1;  //  d1 is greater than d2
        else if(d2.m > d1.m)
                return 1;   //  d2 is greater than d1
    }
    else if(d1.y > d2.y)
        return -1;  //  d1 is greater than d2
    else if(d2.y > d1.y)
        return 1;   //  d2 is greater than d1
}

//  return the differnce in number of days
long dayDifference(struct date d1, struct date d2) 
{
    struct date lower, upper;
    int i;
    long day_number_lower = 0, day_number_upper = 0;

    switch(compare_dates(d1, d2))
    {
        case -1:
            upper = d1;
            lower = d2;
            break;
        case 0:
        case 1:
            upper = d2;
            lower = d1;
            break;
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

//  return differnce as years, months and days in a date structure
struct date format_date_diff(struct date d1, struct date d2)
{
    int diff = dayDifference(d1, d2);
    struct date upper, lower, d;

    d.y = d.m = d.d = 0;

    switch(compare_dates(d1, d2))
    {
        case -1:
            upper = d1;
            lower = d2;
            break;
        case 0:
        case 1:
            upper = d2;
            lower = d1;
            break;
    }

    while(diff > 31)
    {
        months[2] = checkLeap(lower.y);
        diff -= months[lower.m];
        lower.m++;

        if(lower.m == 13)
        {
            lower.m = 1;
            lower.y++;
        }

        d.m++;
    }

    d.y = d.m / 12;
    d.m = d.m %12;
    d.d = diff;

    months[2] = checkLeap(lower.y);
    d.m += d.d / months[lower.m];
    d.d %= months[lower.m];

    return d;
}


//  returns specific codes for each month: considering March as the start of the year
int month_code(int month)
{
    const int c[]={11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return c[month-1];
}

//  returns the day index number depending upon the date, month and year
//  read this: http://mathforum.org/dr.math/faq/faq.calendar.html
int day_index(struct date d)
{
    int y=d.y;
    if(d.m==1 || d.m==2)
        y--;    //  Jan and Feb treated as a part of the previous year

    //  the formula
    int f = (d.d + (((13*month_code(d.m))-1)/5) + (y%100) + ((y%100)/4) + ((y/100)/4) - 2*(y/100));
    int i = f % 7;

    if(i<0) //  if negative, adjust remainder
        i+=7;
    return i;
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
    diff_d = format_date_diff(d1, d2);

    printf("\nDifference is %d days OR %d years, %d months, %d days\n", diff_i, diff_d.y, diff_d.m, diff_d.d);

    return 0;
}