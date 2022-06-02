# This is a vending machine simulator. Coke bottles cost 50c and the vending machine only accepts 25c, 10c, and 5c coins
# Coke bottles not provided

remaining_amount = 50
while (remaining_amount > 0):
    print(f"Amount Due: {remaining_amount}")
    coin = int(input("Insert Coin: "))
    if coin in (5, 10, 25):
        remaining_amount -= coin

print(f"Change owed: {-1*remaining_amount}")