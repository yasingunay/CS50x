import csv
import requests


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


# Each row for reader:
# {'date': '2023-03-23', 'state': 'West Virginia', 'fips': '54', 'cases': '645710', 'deaths': '8132'}
# {'date': '2023-03-23', 'state': 'Wisconsin', 'fips': '55', 'cases': '2014524', 'deaths': '16485'}
# {'date': '2023-03-23', 'state': 'Wyoming', 'fips': '56', 'cases': '185800', 'deaths': '2014'}
# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    count = 0
    for row in reader:
        state = row["state"]
        date = row["date"]
        cases = int(row["cases"])

        if state not in previous_cases:
            previous_cases[state] = cases
            new_cases[state] = []
            new_cases[state].append(cases)
        else:
            new_case = cases - previous_cases[state]
            previous_cases[state] = cases

            if (len(new_cases[state])) >= 14:
                new_cases[state].pop(0)
            new_cases[state].append(new_case)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        this_week_cases = new_cases[state][7:]
        last_week_cases = new_cases[state][:7]
        avg_this = round(sum(this_week_cases) / 7)
        avg_last = round(sum(last_week_cases) / 7)

        diff = avg_this - avg_last

        if diff > 0:
            msg = "an increase"
        else:
            msg = "a decrese"
            diff = -diff

        # Check '0' division
        try:
            percent = round(100 * diff / avg_last)
        except ZeroDivisionError:
            raise ZeroDivisonError

        print(f"{state} had a 7-day average of {avg_this} and {msg} of {percent}%.")


main()
