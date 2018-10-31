/*
 
 ##CALENDAR APPLICATION PROJECT FOR 1ST SEMESTER##
 
 ##DEVELOPERS##
 
 Kinjal Raykarmakar - Section: F, Roll no: 7, Email: kinjalrk2k@gmail.com, GitHub: https://github.com/Kinjalrk2k
 Somsubhra Das - Section: F, Roll no: 8, Email: das.somsubhra1@gmail.com, GitHub: https://github.com/Somsubhra1
 
 ##DESCRIPTION##
 
 This is an user interactive application which helps the user to:
 
 1. find the difference between two dates
 2. find the day of the week for any given date
 3. View calendar for a month
 4. View calendar for a year
 
 The application includes date validity checking, leap year checking.
 
 ##GITHUB LINK FOR THE APPLICATION##
 
 https://github.com/Calendar-Application/Calendar-2
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//  a date structure: used to hold any date data
struct date
{
    int d, m, y;
};

// declaration of month array
//  note: this is a non leap year's no. of days in a month list
int months[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int daysOfMonth[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *month_name[]= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char *daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// function prototype declarations:
int checkLeap(int);
int isValid(struct date);
int compare_dates(struct date, struct date);
long dayDifference(struct date, struct date);
struct date format_date_diff(struct date, struct date);
int month_code(int);
int day_index(struct date);
void monthView(void);
void yearView(void);
int getFirstDayIndex(int year);


// MAIN FUNCTION

int main()
{
    int choice;
    char *weekDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; // declaration of week array
    int index;
    
    // continue running application without automatically stopping
    while (1) {
        printf("1: Find difference between two dates \n2: Find the day of the week for a given date\n");
        printf("3. View month \n4. View Year\n0: Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        struct date d1, d2;
        printf("\n");
        
        // menu options:
        switch(choice) {
            case 1:
                // input first date
                printf("Enter First date: ");
                scanf("%d%d%d", &d1.d, &d1.m, &d1.y);
                
                //  input second date
                printf("Enter Second date: ");
                scanf("%d%d%d", &d2.d, &d2.m, &d2.y);
                
                //checking validity of dates:
                if (isValid(d1) == 0 || isValid(d2) == 0) {
                    printf("Date invalid");
                    break;
                }
                
                //  calculating difference
                struct date diff_d;
                long diff_i;
                diff_i = dayDifference(d1, d2);
                diff_d = format_date_diff(d1, d2);
                
                // displaying output:
                if (diff_d.d && diff_d.y == 0 && diff_d.m == 0) {
                    printf("\nDifference is %ld days", diff_i);
                }
                else {
                    printf("\nDifference is %ld days OR ", diff_i);
                    if (diff_d.y) {
                        printf("%d years ", diff_d.y);
                    }
                    if (diff_d.m) {
                        printf("%d months ", diff_d.m);
                    }
                    if (diff_d.d) {
                        printf("%d days", diff_d.d);
                    }
                }
                break;
                
            case 2:
                // input date
                printf("Enter date: ");
                scanf("%d%d%d", &d1.d, &d1.m, &d1.y);
                
                //checking validity of date
                if (isValid(d1) == 0) {
                    printf("Date invalid");
                    break;
                }
                index = day_index(d1); // getting the index of the day of week
                printf("%s", weekDays[index]);
                
                break;
            case 3:
                monthView();
                break;
                
            case 4:
                yearView();
                break;
                
            case 0:
                printf("Exiting program....");
                printf("\n\n");
                return 0;
                
                // default case
            default:
                printf("Wrong choice!");
                
        }
        printf("\n\n");
        
    }
    return 0;
}

// checking leap year and returning required no. of days for February
int checkLeap(int year)
{
    //  if leap year
    if((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        return 29;
    return 28;
}

//date validity check
int isValid(struct date d1) {
    months[2] = checkLeap(d1.y);
    if(d1.m < 1 || d1.m > 12 || d1.d < 1 || d1.d > months[d1.m] || d1.y < 1 || d1.y > 9999) {
        return 0;
    }
    return 1;
    
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
    
    long diff = labs(day_number_upper - day_number_lower); // finding absolute date difference
    return diff;
}

//  return differnce as years, months and days in a date structure
struct date format_date_diff(struct date d1, struct date d2)
{
    int diff = (int)dayDifference(d1, d2);
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

// prints the whole calendar for a year

void yearView() {
    int year;
    printf("Enter year: ");
    scanf("%d",&year);
    
    months[2] = checkLeap(year);
    
    if(year < 1 || year > 9999) {
        printf("Invalid year..\n");
        return;
    }
    
    int firstDayIndex = getFirstDayIndex(year);
    
    int monthIndex, daysOfWeekIndex, weekDayIndex, daysIndex;
    for (monthIndex = 0; monthIndex < 12; monthIndex++) {
        
        printf("\n\n");
        int spaces = (int) (51 - strlen(month_name[monthIndex]) - 11)/2;
        int i;
        for(i = 0; i<spaces; i++)
            printf(" ");
        printf("** %d %s **\n\n",year, month_name[monthIndex]);
        
        for (daysOfWeekIndex = 0; daysOfWeekIndex < 7; daysOfWeekIndex++) {
            printf("%s\t", daysOfWeek[daysOfWeekIndex]);
        }
        
        printf("\n");
        
        for(weekDayIndex = 0; weekDayIndex <= firstDayIndex - 1; weekDayIndex++) {
            
            printf("\t ");
        }
        
        for (daysIndex = 1; daysIndex <= daysOfMonth[monthIndex]; daysIndex++) {
            
            printf("%d\t ", daysIndex);
            weekDayIndex++;
            
            if (weekDayIndex > 6) {
                
                printf("\n");
                weekDayIndex = 0;
            }
            
            firstDayIndex = weekDayIndex;
        }
    }
}

// prints the whole calendar for a month

void monthView() {
    int year, month;
    printf("Enter year: ");
    scanf("%d",&year);
    printf("Enter month number: ");
    scanf("%d", &month);
    
    months[2] = checkLeap(year);
    
    if(month < 1 || month > 12 || year < 1 || year > 9999) {
        printf("Invalid month or year..\n");
        return;
    }
    
    int firstDayIndex = getFirstDayIndex(year);
    
    printf("\n\n");
    int spaces = (int) (51 - strlen(month_name[month - 1]) - 11)/2;
    int i;
    for(i = 0; i<spaces; i++)
        printf(" ");
    printf("** %d %s **\n\n",year, month_name[month - 1]);
    
    int monthIndex, daysOfWeekIndex, weekDayIndex, daysIndex;
    for (monthIndex = 0; monthIndex < month; monthIndex++) {
        
        if (monthIndex == month - 1) {
            for (daysOfWeekIndex = 0; daysOfWeekIndex < 7; daysOfWeekIndex++) {
                
                printf("%s\t", daysOfWeek[daysOfWeekIndex]);
            }
            printf("\n");
        }
        
        for(weekDayIndex = 0; weekDayIndex <= firstDayIndex - 1; weekDayIndex++) {
            if (monthIndex == month - 1) {
                printf("\t ");
            }
            
        }
        
        for (daysIndex = 1; daysIndex <= daysOfMonth[monthIndex]; daysIndex++) {
            if (monthIndex == month - 1) {
                printf("%d\t ", daysIndex);
            }
            
            weekDayIndex++;
            
            if (weekDayIndex > 6) {
                if (monthIndex == month - 1) {
                    printf("\n");
                }
                
                weekDayIndex = 0;
            }
            
            firstDayIndex = weekDayIndex;
        }
    }
}

// returns the index of first day of a year

int getFirstDayIndex(int year){
    
    int day = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
    return day;
}
