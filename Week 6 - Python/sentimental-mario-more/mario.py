def main():
    while True:
        user_input = input("Height: ")
        if user_input.isdigit():
            height = int(user_input)
            if height >= 1 and height <= 8:
                break
    print_hashes(height)


def print_hashes(height):
    for i in range(height):
        print((height - i - 1) * " ", end="")
        print((i + 1) * "#", end="")
        print("  ", end="")
        print((i + 1) * "#")


main()
