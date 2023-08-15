import sys
from queue import Queue

def main():

    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }

    selection = list()
    total = 0

    while True:
        try:
            item = input("Item: ").strip().title()
            if item in menu:
                total += menu[item]
                print("Total: ${:.02f}".format(total))
        except EOFError:
            return 0
        except KeyError:
            sys.exit("Invalid key\n")

main()