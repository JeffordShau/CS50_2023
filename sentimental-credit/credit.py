# TODO
import sys

def main():
    creditString = input("Number: ")
    try:
        int(creditString)
    except ValueError:
        sys.exit("INVALID")

    # print("Length: ", len(creditString))
    # print("First Two: ", int(creditString[0:2]))

    if LuhnAlgo(creditString):
        if len(creditString) == 16 and int(creditString[0:2]) >= 51 and int(creditString[0:2]) <= 55:
            print("MASTERCARD\n")
        elif len(creditString) == 15 and (int(creditString[0:2]) == 34 or int(creditString[0:2]) == 37):
            print("AMEX\n")
        elif (len(creditString) == 13 or len(creditString) == 16) and int(creditString[0:1]) == 4:
            print("VISA\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")

def LuhnAlgo(creditString):
    sum = 0
    start = len(creditString) % 2
    for i in range(len(creditString)):
        if i % 2 == start:
            product = int(creditString[i:i+1]) * 2
            if product > 9:
                sum += (product % 10) + 1
            else:
                sum += product
        else:
            sum += int(creditString[i:i+1])

    # print(sum)

    return sum % 10 == 0

main()

