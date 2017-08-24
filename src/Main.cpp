#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

#include "PhoneBookEntry.h"
#include "Admin.h"

std::deque<std::string> que;
std::vector<PhoneBookEntry> entries(1);
std::vector<Admin> admins(1);

//Utility Functions
bool compareStrings(std::string& str1, std::string& str2)
{
	int len1 = str1.length();
	int len2 = str2.length();
	if (len1 != len2)
		return false;
	for (int i = 0; i < len1; i++) {
		if (str1[i] != str2[i])
			return false;
	}

	return true;
}

bool isContained(std::string &name, std::string &str)
{
	if (str.length() == name.length())
		return compareStrings(name, str);
	else if(str.length() > name.length()){
		int len = name.length();
		for (int i = 0; i < len; i++)
			if (str[i] != name[i])
				return false;
		return true;
	}

	return false;

}

void addLog(std::string log)
{
	if (que.size() == 10)
		que.pop_front();
	if (compareStrings(log, que.back()))
		return;
	que.push_back(log);
}

void printLog()
{
	std::cout << "\t Recent Searches: " << std::endl;
	for (unsigned int i = 0; i < que.size(); i++)
		std::cout << "\t\t " << que[i] << std::endl;

	std::cout << std::endl;
}

//Searching Functions
void searchByZipCode(int &zipCode)
{
	std::cout << "Entries by the zip code " << zipCode << ": " << std::endl;
	for (const auto &i : entries) {
		if (i.getZipCode() == zipCode) {
			i.showDetails();
			std::cout << std::endl;
			addLog(i.getName() + " " + std::to_string(zipCode) + " " + std::to_string(i.getHomePhone()));
		}
	}

	std::cout << "No Entry By that name" << std::endl;
}

void searchByName(std::string &name)
{
	std::cout << "Entries: " << std::endl;
	for (const auto &i : entries) {
		if (isContained(name, i.getName())) {
			i.showDetails();
			std::cout << std::endl;
			addLog(i.getName() + " " + std::to_string(i.getZipCode()) + " " + std::to_string(i.getHomePhone()));
			return;
		}
	}

	std::cout << "No Entry By that name" << std::endl;
}

void searchByNumber(long long int &phone)
{
	std::cout << "Entry: " << std::endl;
	for (const auto &i : entries) {
		if (i.getHomePhone() == phone || i.getWorkPhone() == phone) {
			i.showDetails();
			addLog(i.getName() + " " + std::to_string(i.getZipCode()) + " " + std::to_string(phone));
			return;
		}
	}

	std::cout << "No such number exists in the directory." << std::endl << std::endl;
}

PhoneBookEntry* searchEntry(std::string& name, int &zipCode)
{

	for (int i = 0; i < PhoneBookEntry::count; i++) {
		//std::cout << entries[i].getName() << " " << entries[i].getZipCode() << std::endl;
		if (!name.compare(entries[i].getName()) && entries[i].getZipCode() == zipCode && !entries[i].IsRemoved())
			return &entries[i];
	}

	return NULL;
}

Admin* searchAdmin(std::string &name, std::string &password)
{
	for (int i = 0; i < Admin::adminCount; i++) {
		if (!name.compare(admins[i].getName()) && !password.compare(admins[i].getPass()))
			return &admins[i];
	}

	return NULL;
}


//Modification Functions
void addNewContact()
{
	std::string fname, lname, address;
	int zipCode;
	long long home;

	std::cout << "\nEnter first name: ";
	std::getline(std::cin, fname);
	std::getline(std::cin, fname);
	std::cout << "\nEnter last name: ";
	std::getline(std::cin, lname);
	std::cout << "Enter the Zip Code: ";
	std::cin >> zipCode;
	std::cout << "Enter the phone number: ";
	std::cin >> home;
	std::cout << "Enter the address: ";
	std::getline(std::cin, address);
	std::getline(std::cin, address);

	PhoneBookEntry entry(fname + " " + lname, zipCode, home, address);
	entries.resize(PhoneBookEntry::count);
	entries[PhoneBookEntry::count - 1] = entry;

	std::cout << "The Contact has been successfully added to the directory" << std::endl;

}

void addNewPhone()
{
	std::string name;
	int zipCode;
	long long phone;
	std::cout << "Enter the name: ";
	std::getline(std::cin, name);
	std::cout << "Enter the Zip Code: ";
	std::cin >> zipCode;

	PhoneBookEntry *entry = searchEntry(name, zipCode);
	if (entry == NULL) {
		std::cout << "No Such Entry Exists" << std::endl;
		return;
	}
	else
	{
		std::cout << "Enter the new phone number: ";
		std::cin >> phone;
		if ((*entry).getWorkPhone() != -1)
			std::cout << "The previous number has ben replaced.";

		(*entry).setWorkPhone(phone);
	}

	std::cout << "\n\n\t Changes were made successfully" << std::endl;
}

void changeAddress()
{
	std::string name, address;
	int zipCode;
	std::cout << "Enter the name: ";
	std::getline(std::cin, name);
	std::getline(std::cin, name);

	std::cout << "Enter the zipCode: ";
	std::cin >> zipCode;

	PhoneBookEntry *entry = searchEntry(name, zipCode);
	if (entry == NULL) {
		std::cout << "No Such entry exists." << std::endl;
		return;
	}
	else
	{
		std::cout << "Enter the new Zip Code: ";
		std::cin >> zipCode;
		std::cout << "Enter the new address: ";
		std::getline(std::cin, address);
		(*entry).setAddress(address, zipCode);
	}
	std::cout << "Changes were made successfully" << std::endl;
}

void deleteContact()
{
	std::string name;
	int zipCode;
	std::cout << "Enter the name: ";
	std::getline(std::cin, name);
	std::getline(std::cin, name);

	std::cout << "Enter the zipCode: ";
	std::cin >> zipCode;

	PhoneBookEntry *entry = searchEntry(name, zipCode);
	if (entry == NULL) {
		std::cout << "No such entry exists." << std::endl;
		return;
	}
	else
	{
		(*entry).setRemoved(true);
		PhoneBookEntry::count--;
	}
}

void readFromFile()
{
	std::fstream file("PhoneEntries.txt", std::ios::in | std::ios::out);

	file >> PhoneBookEntry::count;
	entries.resize(PhoneBookEntry::count);
	for (int i = 0; i < PhoneBookEntry::count; i++) {
		std::string fname, lname, address;
		int zipCode;
		long long work, home;
		file >> fname >> lname;
		file >> home >> work;
		file >> zipCode;
		std::getline(file, address);
		entries[i].setAddress(address, zipCode);
		entries[i].setWorkPhone(work);
		entries[i].setHomePhone(home);
		entries[i].setName(fname, lname);
	}

	file.close();
	
	file.open("Admins.txt", std::ios::in | std::ios::out);
	file >> Admin::adminCount;
	admins.resize(Admin::adminCount);
	for (int i = 0; i < Admin::adminCount; i++) {
		std::string fname, lname, pass;
		file >> fname >> lname;
		file >> pass;
		admins[i].setName(fname, lname);
		admins[i].setPass(pass);
	}

	file.close();

	file.open("log.txt", std::ios::in | std::ios::out);
	while (!file.eof()) {
		std::string log;
		std::getline(file, log);
		que.push_back(log);
	}

	file.close();
}

void writeToFile()
{
	std::fstream file("PhoneEntries.txt", std::ios::in | std::ios::out | std::ios::trunc);
	file << PhoneBookEntry::count << std::endl;

	for (int i = 0; i < PhoneBookEntry::count; i++) {
		if (!entries[i].IsRemoved()) {
			entries[i].writeToFile(&file);
		}
	}

	file.close();

	file.open("Admins.txt", std::ios::in | std::ios::out | std::ios::trunc);
	file << Admin::adminCount << std::endl;

	for (int i = 0; i < Admin::adminCount; i++) {
		admins[i].writeToFile(&file);
	}
	
	file.close();

	file.open("log.txt", std::ios::in | std::ios::out);
	while (!que.empty()) {
		file << que.back() << std::endl;
		que.pop_back();
	}
}

int main()
{
	bool running = true;
	readFromFile();

	std::cout << "\n\n \t Nikhil's Phone Directory\n" << std::endl;
	std::cout << "A. Go to Admin's Menu\t B. Go to User's Menu" << std::endl;
	char ch = std::cin.get();
	fflush(stdin);

	while (running) {

		//Admin's Menu
		if (ch == 'A' || ch == 'a') {
			system("CLS");
			std::cout << "\n\n \t Nikhil's Phone Directory\n" << std::endl;
			std::cout << "\tAdmin's Menu" << std::endl;
			std::string name, password;
			std::cout << "Enter your Details: " << std::endl;
			std::cout << "Name: ";
			std::getline(std::cin, name);
			std::getline(std::cin, name);
			std::cout << "PassWord: ";
			std::getline(std::cin, password);

			Admin *admin = searchAdmin(name, password);

			if (admin != NULL) {
				system("CLS");
				std::cout << "\n\n \t Nikhil's Phone Directory\n" << std::endl;
				std::cout << "\tAdmin's Menu" << std::endl;
				std::cout << "\n\tHello " << (*admin).getName() << std::endl;
				std::cout << "\t1. Enter a new Contact.\t\t\t2. Enter a phone number to an existing contact\n";
				std::cout << "\t3. Change the Address of an entry.\t4. Delete a contact\n";
				short che;
				std::cin >> che;
				system("CLS");
				std::cout << "\n\n \t Nikhil's Phone Directory\n" << std::endl;
				std::cout << "\tHello " << (*admin).getName() << std::endl;
				switch (che)
				{
				case 1:
					addNewContact();
					break;
					
				case 2:
					addNewPhone();
					break;

				case 3:
					changeAddress();
					break;

				case 4:
					deleteContact();
					break;
				
				}

				std::cout << "\n\t 1. Go to Admin's Menu\t2. Exit" << std::endl;
				std::cin >> che;
				if (che == 1)
					continue;
				else
					running = false;

			}
			else {
				std::cout << "The Admin credentials do not match" << std::endl;
				running = false;
			}

		}

		//User's Menu
		else {
			system("CLS");
			std::cout << "\n\n \t Nikhil's Phone Directory\n" << std::endl;
			std::cout << "\tUser's Menu" << std::endl << std::endl;
			
			printLog();
			
			std::cout << "\t1. Search by Name or Character\t2. Search by Zip Code" << std::endl;
			std::cout << "\t3. Search a Particular entry\t4. Search using phone number." << std::endl;
			short che;
			std::cin >> che;
			std::string name;
			PhoneBookEntry *entry;
			int zipCode;
			long long int phone;
			switch (che) {
			case 1:
				std::cout << "Enter the name: ";
				std::getline(std::cin, name);
				std::getline(std::cin, name);
				searchByName(name);
				break;
			case 2:
				std::cout << "Enter the zip code: ";
				std::cin >> zipCode;
				searchByZipCode(zipCode);
				break;

			case 3:
				std::cout << "Enter the name:  ";
				std::getline(std::cin, name);
				std::getline(std::cin, name);
				std::cout << "Enter the zipCode:  ";
				std::cin >> zipCode;
				entry = searchEntry(name, zipCode);
				if (entry != NULL) {
					std::cout << "\n\tThe Phone Directory Matching the given details" << std::endl;
					(*entry).showDetails();
					addLog(name + " " + std::to_string(zipCode) + " " + std::to_string(entry->getHomePhone()));
				}
				else
					std::cout << "There is no entry in the directory by that name.";
				break;

			case 4:
				std::cout << "Enter the phone number: ";
				std::cin >> phone;
				searchByNumber(phone);
				break;
			}
			std::cout << "\n\n\t 1. Go to User's Menu\t2. Exit" << std::endl;
			std::cin >> che;
			if (che == 1)
				continue;
			else
				running = false;

		}
	} 

	writeToFile();

	system("PAUSE");
	return 0;
}