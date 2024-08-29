#include<iostream>
#include<cstring>
#include<limits>
using namespace std;
int c = 0;
int op;
int SoR = 0;
int client_sender;
int client_receiver;
class ATM {
private:
	char name[101];
	char card_number[11];
	double Amount;
public:
	void create_new_acc();
	void Print_acc_data();
	void Deposit(int);
	void Withdrawal(int);
	void Transfer(int, int);
	void Enter_Name();
	void Enter_cardnumber();
	void RepairName(char name[]);
	void Repaircard(char card[]);
	int getcard();
}client[100];
void ATM::Transfer(int send_clientnum, int recieve_clientnum)
{
	SoR = 3;
	if (client[send_clientnum].Amount == 0)//amount in sending account =0
	{
		cout << "\nCannot transfer, not enough money\nAmount : 0\n " << endl;

	}
	else
	{
	trans:
		double transfer;
		cout << "\nPlease enter the amount to be transferred: ";
		cin >> transfer;
		if (!cin)
		{
			cin.clear();
			cin.ignore(256, '\n');
			goto trans;
		}
		else if (transfer <= 0)
			goto trans;
		else if (client[send_clientnum].Amount < transfer * 1.015)
		{
			cout << "\nMaximum amount to be transfered : ";
			cout << client[send_clientnum].Amount * 0.985 << endl;
			goto trans;
		}
		else {
			client[send_clientnum].Amount -= transfer * 1.015;
			client[send_clientnum].Print_acc_data();
			client[recieve_clientnum].Amount += transfer * 0.985;
			client[recieve_clientnum].Print_acc_data();
		}


	}
}
void ATM::Withdrawal(int client_number) {
	double withdraw;
	if (client[client_number].Amount == 0)
	{
		cout << "\nNot enough money to be withdrawn\nAmount : " << client[client_number].Amount << endl;
	}
	else
	{
	draw:
		cout << "Please enter the amount to be withdrawn: ";
		cin >> withdraw;
		if (!cin)
		{
			cin.clear();
			cin.ignore(256, '\n');
			goto draw;
		}
		else if ((client[client_number].Amount - (withdraw * 1.03) < 0))
		{
			cout << "Not enough money to be withdrawn\nAmount : " << client[client_number].Amount;
			cout << "\nMaximum amount to be withdrawn : ";
			cout << client[client_number].Amount * 0.97 << endl;
			goto draw;
		}
		else {
			client[client_number].Amount -= withdraw * 1.03;
			client[client_number].Print_acc_data();
		}

	}
}
void ATM::Deposit(int client_number) {
	double depos;
label:
	cout << "\nPlease enter the amount to be deposited : ";
	cin >> depos;

	if (depos <= 0 || !cin)
	{
		cin.clear();
		cin.ignore(256, '\n');
		goto label;
	}

	else
	{
		client[client_number].Amount += depos * 1.01;
		client[client_number].Print_acc_data();
	}

}
int ATM::getcard() {
	int x = 0;
	int i;
	for (i = c; i >= 0; i--)
	{
		if ((i - 1 >= 0) && !((strcmp(client[c].card_number, client[i - 1].card_number)) != 0))
		{
			x = 1;
			break;
		}

	}
	if ((op == 2 || op == 4 || op == 3) && x == 1)
		return i - 1;
	else if (op == 1)
		return x;
}
void ATM::Enter_Name() {
	cout << "please enter the account name: ";
	cin.getline(name, 101);
	RepairName(name);
}
void ATM::Enter_cardnumber() {
	if (op == 3 && c > 0) {
		if (SoR == 0)
		{
			cout << "please enter the number of the sending account : ";
			cin.getline(card_number, 21);
			Repaircard(card_number);
			if (getcard() >= 0)
			{
				client_sender = getcard();
			}
			else
			{
				cout << "Card number not found\n";
				Enter_cardnumber();
			}
			SoR++;
		}
		if (SoR == 1)
		{
			cout << "please enter the number of the receiving account : ";
			cin.getline(card_number, 21);
			Repaircard(card_number);
			if (getcard() >= 0)
			{
				client_receiver = getcard();
			}
			else
			{
				cout << "Card number not found\n";
				Enter_cardnumber();
			}
			SoR++;
		}
		if (SoR == 2) {
			if (client_sender == client_receiver)
			{
				cout << "\nCannot transfer to the same account\n";
				SoR--;
				Enter_cardnumber();
			}
			else
				Transfer(client_sender, client_receiver);
		}

	}
	else {
		cout << "Please enter the account number(10 numbers each separated by space or without space): ";
		cin.getline(card_number, 21);
		Repaircard(card_number);
		if (op == 2 || op == 4) {
			if (op == 2 && (getcard() >= 0))
			{
				Deposit(getcard());
			}
			else if (op == 4 && (getcard() >= 0))
			{
				Withdrawal(getcard());
			}
			else
			{
				cout << "Card number not found\n";
				Enter_cardnumber();
			}

		}
	}
}
void ATM::RepairName(char name[]) {
	while (strlen(name) == 0)//ignoring pressing Enter immediately entering a name.
	{
		Enter_Name();
	}
	while (name[0] == ' ') //ignoring spaces in the first of client's name.
	{
		for (int i = 0; name[i]; i++)
			name[i] = name[i + 1];
	}
	if (strlen(name) <= 2 || name[0] == '\0' || name[1] == '\0') //no name contain 2 letters.
	{
		cout << "The name is too short !\n";
		Enter_Name();
	}
	if (1) {
		bool create = false;
		for (int i = 0; name[i] != '\0'; i++)//avoid numbers
		{
			if ((name[i] < '9' && name[i] > '0'))
			{
				cout << "Name cannot contain any numbers !\n";
				create = true;
				break;
			}
		}
		if (create)
			Enter_Name();
	}
	if (1) {
		bool create = false;
		for (int i = 0; name[i] != '\0'; i++)//avoid symbols.
		{
			if (!((name[i] == ' ') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')))
			{
				cout << "Name cannot contain any symbols !\n";
				create = true;
				break;
			}
		}
		if (create)
			Enter_Name();
	}
	for (int i = 0; name[i] != '\0'; i++) //avoid successive space among name letters.
	{
		if ((name[i] == name[i + 1]) && (name[i + 1] == ' '))
		{
			char temp[100];
			for (int j = i; name[j - 1]; j++)
			{
				temp[j] = name[j + 1];
				name[j + 1] = name[j];
				name[j] = temp[j];
			}
			i--;
		}
	}

}
void ATM::Repaircard(char card[]) {
	while (strlen(card) == 0)//ignoring pressing Enter immediately entering a card.
	{
		Enter_cardnumber();
	}
	int j = 0;
	for (int i = 0; card[i] != '\0'; i++) //Removes spaces in the card number
	{
		if (card[i] != ' ')
		{
			card[j++] = card[i];
		}
	}
	card[j] = '\0';
	while (card[0] == ' ') //ignoring spaces in the first of client's name.
	{
		for (int i = 0; card[i]; i++)
			card[i] = card[i + 1];
	}
	if (1) {
		bool create = false;
		for (int i = 0; card[i] != '\0'; i++)//avoid letters & symbols
		{
			if (!(card[i] <= '9' && card[i] >= '0'))
			{
				cout << "card number cannot contain symbols or letters !\n";
				create = true;
				break;
			}
		}
		if (create)
			Enter_cardnumber();
	}
	if (strlen(card) != 10) //no ncard contain lessthan 10 number.
	{
		cout << "The Card number consists of 10 numbers,\n";
		Enter_cardnumber();
	}
	if (1) //The card number cannot contain one number repeated 10 times
	{
		bool newcard;
		for (int i = 1; card[i]; i++) {
			if (card[0] == card[i])
				newcard = true;
			else
			{
				newcard = false;
				break;
			}

		}
		if (newcard) {
			cout << "The card number cannot contain one number repeated 10 times !\n";
			Enter_cardnumber();
		}

	}
	if (op == 1) {
		if (getcard())//check unique cardnumber
		{
			cout << "This card number is already taken\n";
			Enter_cardnumber();
		}
	}

}
void ATM::create_new_acc() {
	//Name.
	Enter_Name();
	Enter_cardnumber();
	Amount = 0;
}
void ATM::Print_acc_data() {
	cout << "Your name : " << name << endl;
	cout << "Your card number : " << card_number << endl;
	cout << "amount: " << Amount << endl;
}
int main() {
	bool flag = true;
	bool flag_2 = true;
	while (flag)
	{
	menu:
		cout << "1----Create new account" << endl << "2----Deposit" << endl << "3----transfer to another account" << endl << "4----withdrawal" << endl << "5----exit";
		cout << "\nPlease enter the number of operation: ";
	label:
		cin >> op;
		while ((op > 5 || op < 0 || (!cin)))
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\nPlease,Enter a number from 1 to 5 to select your operation : ";
			cin >> op;
		}

		if (c == 0 && op != 1 && op != 5)
		{
			cout << "You must create a new account first" << endl << "Please enter the number of operation:";
			goto label;
		}

		switch (op) {
		case 1:
		{
			cin.ignore();
			client[c].create_new_acc();
			client[c].Print_acc_data();
			c++;
			break;
		}
		case 2:
		{
			cin.ignore(256, '\n');
			client[c].Enter_cardnumber();
			break;
		}
		case 3:
		{
			SoR = 0;
			if (c == 1)//at least 2 account must be entered .
			{
				cout << "\nAt least 2 accounts must be entered to preform the transfer operation\n";
				goto menu;
			}
			cin.ignore(256, '\n');
			client[c].Enter_cardnumber();
			c++;
			client[c].Enter_cardnumber();
			c--;
			break;
		}
		case 4:
		{
			cin.ignore(256, '\n');
			client[c].Enter_cardnumber();
			break;
		}
		case 5:
			flag = false;
			break;
		default:
			break;
		}
	}
	return 0;
}