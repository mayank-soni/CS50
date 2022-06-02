# Prints out the price of X bitcoin, where X is entered as a command-line argument. 
# Current price of bitcoin is obtained from CoinDesk API

import requests
from sys import argv, exit

# Error handling for command line arguments
if len(argv)!=2:
    exit("Incorrect usage. Correct input should be: 'python bitcoin.py number_bitcoin_required'")
try:
    bitcoin_wanted = float(argv[1])
except (TypeError, ValueError):
    exit("Please enter a numerical quantity of bitcoin")

# API call to get price of bitcoin + error handling
try:
    # Get price in USD, remove 1000s separators (','), and convert to float
    price = float(requests.get("https://api.coindesk.com/v1/bpi/currentprice.json").json()['bpi']['USD']['rate'].replace(',',''))
except requests.RequestException:
    exit("An error occured while accessing the CoinDesk API")
except requests.ConnectionError:
    exit("An connection error occured while accessing the CoinDesk API")
except requests.HTTPError:
    exit("A HTTP error occured while accessing the CoinDesk API")
except requests.TooManyRedirects:
    exit("Too many redirects occured while accessing the CoinDesk API")
except requests.Timeout:
    exit("The connection timed out while accessing the CoinDesk API")

print(f"${price*bitcoin_wanted:,.4f}")