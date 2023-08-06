s =  input("Greeting: ")
s = s.lower().strip()
if s.startswith("hello"):
    print("$0")
elif s.startswith("h"):
    print("$20")
else:
    print("$100")