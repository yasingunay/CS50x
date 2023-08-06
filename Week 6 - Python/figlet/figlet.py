import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

if len(sys.argv) == 1:
    s = input("Input: ")
    print("Output: ")
    fonts = figlet.getFonts()
    figlet.setFont(font=random.choice(fonts))
    print(figlet.renderText(s))

elif len(sys.argv) == 3:
    fonts = figlet.getFonts()
    if (sys.argv[1] == "-f" or sys.argv[1] == "--font") and sys.argv[2] in fonts:
        s = input("Input: ")
        figlet.setFont(font=sys.argv[2])
        print("Output: ")
        print(figlet.renderText(s))

    else:
        print("Invalid usage")
        sys.exit(1)


else:
      print("Invalid usage")
      sys.exit(1)

