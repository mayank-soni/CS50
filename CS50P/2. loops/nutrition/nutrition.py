# Returns the number of calories in a serving of common fruit,
# as per https://www.fda.gov/media/76508/download

calories = {'apple': 130, 'avocado': 50, 'banana': 110, 'cantaloupe': 50,
            'grapefruit': 60, 'grapes': 90, 'honeydew': 50, 'kiwifruit': 90,
            'lemon': 15, 'lime': 20, 'nectarine': 60, 'orange': 80, 'peach': 60,
            'pear': 100, 'pineapple': 50, 'plums': 70, 'strawberries': 50,
            'sweet cherries': 100, 'tangerine': 50, 'watermelon': 80}
fruit = input("Item: ").lower().strip()
if fruit in calories:
    print(f"Calories: {calories[fruit]}")