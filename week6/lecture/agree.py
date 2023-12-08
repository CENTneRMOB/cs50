s = input("Do you agree? ")

s = s.lower()
if s in ["y", "yes"]:
  print("Agreed")
elif s in ["no", "n"]:
  print("Not agree")