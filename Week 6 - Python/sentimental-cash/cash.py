from cs50 import get_float


def main():
    # Prompt the user until the valid number
    while True:
        input = get_float("Change owed: ")
        if input > 0:
            break
    calculate_coins(input)


def calculate_coins(input):
    # Multiply all coins by 100
    quarters = 25
    dimes = 10
    nickels = 5
    pennies = 1

    # Assign all values to 0
    sum, nb_q, nb_d, nb_n, nb_p = 0, 0, 0, 0, 0

    # Multiply input by 100
    input *= 100

    # Calculate each coins in order until input is 0
    if input >= quarters:
        nb_q = int(input / quarters)
        input -= quarters * nb_q
    if input >= dimes:
        nb_d += int(input / dimes)
        input -= dimes * nb_d
    if input >= nickels:
        nb_n += int(input / nickels)
        input -= nickels * nb_n
    if input >= pennies:
        nb_p += int(input / pennies)

    # Calculate sum
    sum = nb_q + nb_d + nb_n + nb_p

    print(f"{sum}")


main()
