# TODO

def main():
    while True:
        try:
            change = float(input("Change owed: "))
        except ValueError:
            continue
        if change > 0:
            break

    coins = 0
    change = int(change * 100)

    quarters = change // 25
    change %= 25

    dimes = change // 10
    change %= 10

    nickels = change // 5
    change %= 5

    print(quarters + dimes + nickels + change)

main()