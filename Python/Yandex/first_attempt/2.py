import sys

ERA_DAY = 1
ERA_MONTH = 1
ERA_YEAR = 1970
ERA_WD = 3
DAYS_IN_A_WEEK = 7

MONTH_DAYS = {
    1 : 31,
    2: 28,
    3: 31,
    4: 30,
    5: 31,
    6: 30,
    7: 31,
    8: 31,
    9: 30,
    10: 31,
    11: 30,
    12: 31
}

MONTH_NAMES = {
    "January" : 1,
    "February": 2,
    "March": 3,
    "April": 4,
    "May": 5,
    "June": 6,
    "July": 7,
    "August": 8,
    "September": 9,
    "October": 10,
    "November": 11,
    "December": 12
}

DAYS_OF_A_WEEK = {
     0: "Monday",
     1: "Tuesday",
     2: "Wednesday",
     3: "Thursday",
     4: "Friday",
     5: "Saturday",
     6: "Sunday"
}

def is_leap(year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)

def years_addition(year):
    days = 0
    for iyear in range(ERA_YEAR, year):
        if is_leap(iyear):
            days += 366
        else:
            days += 365
    return days

def month_addition(year, month):
    days = 0
    if month > 2 and is_leap(year):
        days += 1
    for imonth in range(1, month):
        days += MONTH_DAYS[imonth]
    return days

def days_since_era(day, month, year):
    days = years_addition(year)
    days = month_addition(year, month)
    days += day
    days -= 1       # because of 1st January 1970
    return days

def day_of_the_week(day, month, year):
    day = (ERA_WD + days_since_era(day, month, year)) % DAYS_IN_A_WEEK
    return DAYS_OF_A_WEEK[day]

def get_dmy(string):
    lst = string.split()
    return int(lst[0]), MONTH_NAMES[lst[1]], int(lst[2])

def main(argv):
    input = open("input.txt")
    output = open("output.txt", "w")
    for line in input.readlines():
        if len(line) < 2:
            break
        day, month, year = get_dmy(line)
        day_name = day_of_the_week(day, month, year)
        output.write(day_name + "\n")

if __name__ == "__main__":
    sys.exit(main(sys.argv))


