from datetime import date
import sys

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

def get_dmy(string):
    lst = string.split()
    return int(lst[0]), MONTH_NAMES[lst[1]], int(lst[2])

def main(argv):
    inputs = open("input.txt")
    outputs = open("output.txt", "w")
    days = []
    for line in inputs.readlines():
        day, month, year = get_dmy(line)
        dtm = date(year, month, day)
        days.append(dtm.strftime("%A"))
    outputs.write("\n".join(days))
    inputs.close()
    outputs.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))

