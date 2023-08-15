# TODO


def main():
    while True:
        try:
            height = int(input("Height: "))
        except ValueError:
            continue
        if height >= 1 and height <= 8:
            break

    printPyramid(height)


def printPyramid(height):
    whiteSpace = " "
    stairs = "#"
    for i in range(1, height + 1):
        print(whiteSpace * (height - i), end="")
        print(stairs * i, end="")
        print(whiteSpace * 2, end="")
        print(stairs * i)
        
main()