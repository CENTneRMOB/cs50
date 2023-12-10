from cs50 import get_int

height = 0

while height < 1 or height > 8:
    height = get_int("Height: ")

i = height
while i > 0:
    spaces = i - 1
    hashes = height - spaces
    print(f"{' ' * spaces}{'#' * hashes}  {'#' * hashes}")
    i = spaces