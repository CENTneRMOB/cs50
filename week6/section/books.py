import csv
books = []

# # Add three books to your shelf
# for i in range(3):
#   book = dict()
#   book["title"] = input("Title: ").strip().capitalize()
#   book["author"] = input("Author: ")

#   books.append(book)

# print(books)

# Add three books to your shelf from books.csv
with open("books.csv") as file:
  # text = file.read()
  # print(text)
  file_reader = csv.DictReader(file)
  for book in file_reader:
    print(book)