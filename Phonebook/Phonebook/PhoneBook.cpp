#include <iostream>
#include <fstream>

using namespace std;

struct PhoneNumber
{
	char name[30];
	char phone[11];
}record;


void addContact();
void showContacts();
void searchContactByName();
void searchContactByNumber();
void updateContact();

int main() {

	char choice;
	while (1) {
	
		cout << "Choose an Option" << endl;
		cout << endl;
		cout << "A- ADD NEW CONTACT" << endl;
		cout << "B- SHOW ALL CONTACTS" << endl;
		cout << "C- SEARCH BY NAME" << endl;
		cout << "D- SEARCH BY NUMBER" << endl;
		cout << "E- UPDATE NUMBER" << endl;
		cin >> choice;
		cout<< endl;

		choice=toupper(choice);

		switch (choice)
		{
		case 'A':	addContact();				break;
		case 'B':	showContacts();				break;
		case 'C':	searchContactByName();		break;
		case 'D':	searchContactByNumber();	break;
		case 'E':	updateContact();			break;
		}


	}
}

void addContact() {

	
	ofstream addContact;

	addContact.open("Phonebook.dat", ios::binary | ios::app);
	if (!addContact) {
		cout << "File Opening Error" << endl;
	}

	cout << "ENTER NAME: ";
	cin >> record.name;
	cout << endl;

	cout << "ENTER Number: ";
	cin >> record.phone;
	cout << endl;

	addContact.write((char*)&record, sizeof(record));

	addContact.close();

}

void showContacts() {


	ifstream showContacts;

	showContacts.open("Phonebook.dat", ios::binary);
	if (!showContacts) {
		cout << "File Opening Error" << endl;
	}

	cout << "NAME          Number" << endl;


	while (showContacts) {

		showContacts.read((char*)&record, sizeof(record));

		if (!showContacts.eof()) {

			cout << record.name << "          " << record.phone << endl;
		}
	}
	showContacts.close();
}
void searchContactByNumber() {


	ifstream searchByNumber;
	bool flag=0;
	char number[15];

	searchByNumber.open("Phonebook.dat", ios::binary|ios::in|ios::out);
	
	cout << "Enter Number You Want To Find: ";
	cin >> number;
	cout << endl;
	searchByNumber.seekg(0, ios::beg);
	while (searchByNumber.read((char*)&record, sizeof(record))) {
		if (strcmp(record.phone, number) == 0) {
			flag = 1;
			cout << "NAME:   " << record.name << endl;
			break;
		}

	}

	if (flag == 0) {
		cout << "Contact Not Found!";
	}
}

void searchContactByName() {


	ifstream searchByName;
	bool flag = 0;
	char name[30];

	searchByName.open("Phonebook.dat", ios::binary | ios::in | ios::out);

	cout << "Enter Name You Want To Find: ";
	cin >> name;
	cout << endl;

	searchByName.seekg(0, ios::beg);
	while (searchByName.read((char*)&record, sizeof(record))) {
		if (strcmp(record.name, name) == 0) {
			flag = 1;
			cout << "Number:   " << record.phone << endl;
			break;
		}

	}

	if (flag == 0) {
		cout << "Contact Not Found!";
	}
}

void updateContact() {


	fstream updateContact;
	bool flag = 0;
	int i=0;
	char num[15];

	updateContact.open("Phonebook.dat", ios::binary | ios::in | ios::out);
	if (!updateContact) {
		cout << "File Opening Error" << endl;
	}

	cout << "Enter Number You Want To Update: ";
	cin >> num;
	cout << endl;

	updateContact.seekg(0, ios::beg);
	while (updateContact.read((char*)&record, sizeof(record))) {
		if (strcmp(record.phone, num) == 0) {
			flag = 1;
			cout <<"Name:  " << record.name << "          " << "Number:  " << record.phone << endl;
			i = (i) * sizeof(record);
			updateContact.seekp(i);
			cout << "Enter New Name: ";
			cin >> record.name;
			cout << endl;
			cout << "Enter New Number: ";
			cin >> record.phone;
			cout << endl;
			updateContact.write((char*)&record, sizeof(record));
			updateContact.close();

			break;
		}
		i++;

	}

	if (flag == 0) {
		cout << "Contact Not Found!";
	}
}