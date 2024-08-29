# BankingSystem
A banking program that interactively deals with the ATM user and provide different banking services.

This is a Data Structure 1st year university project for a simple banking system, dealing with ATMs.
It allows the user to create a new account, deposit, withdraw, transfer and print out details of each user's account. Each user has his name, and a unique card ID.

Some of the members in the class structure:

create_new_acc(): this member function is used to create a new account, entering the
name and the card number
Deposit(): this function adds the deposited amount to the money in the account + 1% of the
deposited amount added
Withdrawal(): this function withdraw money from the money in the account + 3% deduced
from the account
Transfer(): this function transfers money from a sending account to a receiving account,
deducing 1.5% from both accounts
Print_acc_data(): prints the account name, card number, and amount of money


Notes to consider:
- The maximum number of accounts is 100 accounts
- When depositing, an extra 1% of the depositing amount is added to the account
- When withdrawing, an extra 3% of the withdrawn amount is deduced from the account
- When transfering, each user has 1.5% deduced from each account

The program interactively deals with the ATM user, until the user requests to
terminate the program
