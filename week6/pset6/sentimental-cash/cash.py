from cs50 import get_float
from math import floor

coins = [25, 10, 5, 1]
change = 0

while change < 0.01:
    change = get_float("Change owed: ") * 100

result = int(change)
count = 0

while result != 0:
    for coin in coins:
        if result >= coin:
            div = floor(result / coin)
            count += div
            result -= div * coin

print(count)
