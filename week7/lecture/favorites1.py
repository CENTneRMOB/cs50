from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorites: ")

# rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = 'Mario'")
rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite)

# for row in rows:
#   print(row["n"])
print(rows)
row = rows[0]
print(row["n"])