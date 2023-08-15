import csv
import requests
import sys
from queue import Queue

def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print(f"Alphabetical List of States: {sorted(new_cases.keys())}")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    prev_case = dict()

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in new_cases:
            new_cases[state] = Queue(14)
            prev_case[state] = cases
        else:
            new_case = cases - prev_case[state]
            prev_case[state] = cases

            if new_cases[state].full():
                new_cases[state].get()
            new_cases[state].put(new_case)

    for state in new_cases:
        new_cases[state] = list(new_cases[state].queue)

    # print(new_cases)
    return new_cases

    # new_cases = dict()
    # prev_case = dict()

    # for row in reader:
    #     state = row["state"]
    #     cases = int(row["cases"])

    #     if state not in new_cases:
    #         new_cases[state] = list()
    #         prev_case[state] = cases
    #     else:
    #         new_case = cases - prev_case[state]
    #         prev_case[state] = cases

    #         if len(new_cases[state]) >= 14:
    #             new_cases[state].pop(0)
    #         new_cases[state].append(new_case)

    # return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    # print(states)
    for state in states:
    #     if state not in new_cases:
    #         print(f"{state} not in NYTimes Covid Database\n")
    #         continue

        prev_week = sum(new_cases[state][:7])
        this_week = sum(new_cases[state][7:])

        try:
            percent_avg = (this_week - prev_week) / prev_week
        except ZeroDivisionError:
            print(
                f"Cannot Divide By Zero for {state}\n" +
                f"\tLast week total cases: {prev_week}\n" +
                f"\tThis week total cases: {this_week}\n"
            )
            continue

        if percent_avg > 0:
            print("{:} had a 7 day average of {:d} and a increase of {:.2%}\n".format(state, this_week, percent_avg))
        else:
            print("{:} had a 7 day average of {:d} and a decrease of {:.2%}\n".format(state, this_week, percent_avg))

main()