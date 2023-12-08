# people = {
#   "Carter": "+1-5464-4334",
#   "David": "+1-7575-4355"
# }

# name = input("Name: ")
# if name in people:
#   print(f"Number: {people[name]}")

import csv

with open("phonebook.csv", "a") as file:

  name = input("Name: ")
  number = input("Number: ")

  # writer = csv.writer(file)
  # writer.writerow([name, number])

  writer = csv.DictWriter(file, fieldnames=["name", "number"])

  writer.writerow({"name": name, "number": number})

# file.close()