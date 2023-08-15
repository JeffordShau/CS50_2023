from pyfiglet import Figlet
from sys import argv
import sys
import random

figlet = Figlet()
args = argv[1:]
print(args)

if len(args) == 0:
    random.seed()
    figlet.setFont(font=random.choice(figlet.getFonts()))
elif len(args) == 2:
    if args[0] == '-f' or args[0] == "--font":
        if args[1] in figlet.getFonts():
            figlet.setFont(font=args[1])
        else:
            sys.exit("Invalid usage")
    else:
        sys.exit("Invalid usage")
else:
    sys.exit("Invalid usage")


msg = input("Input: ")
print("Output: ")
print(figlet.renderText(msg))


