# TODO
import math

def main():
    inputString = input("Text: ")

    sentences = 0
    letters = 0
    words = 1
    for char in inputString:
        if char == "!" or char == "." or char == "?":
            sentences += 1
        elif char == " ":
            words += 1
        elif char.isalpha():
            letters += 1

    grade = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8

    if grade > 16:
        print("Grade 16+\n")
    elif grade < 1:
        print("Before Grade 1\n")
    else:
        print(f"Grade {int(round(grade))}\n")

main()