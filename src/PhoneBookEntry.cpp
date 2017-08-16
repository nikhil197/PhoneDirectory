#include <iostream>
#include <fstream>
#include "PhoneBookEntry.h"

int PhoneBookEntry::count = 0;

//Constructors
PhoneBookEntry::PhoneBookEntry()
{
	m_zipCode = -1;
	m_workPhone = -1;
	m_homePhone = -1;
	isRemoved = false;
}

PhoneBookEntry::PhoneBookEntry(const std::string& name, const int& zipCode, const long long & workPhone, const long long& homePhone, const std::string& address)
{
	m_Name = name;
	m_zipCode = zipCode;
	m_workPhone = workPhone;
	m_homePhone = homePhone;
	m_address = address;
	isRemoved = false;
	count++;
}

PhoneBookEntry::PhoneBookEntry(const std::string &name, const int & zipCode, const long long & homePhone, const std::string & address)
{
	m_Name = name;
	m_zipCode = zipCode;
	m_homePhone = homePhone;
	m_workPhone = -1;
	m_address = address;
	isRemoved = false;
	count++;
}

PhoneBookEntry::~PhoneBookEntry()
{
	m_Name = m_address = "";
	m_zipCode = -1;
	m_workPhone = -1;
	m_homePhone = -1;
	isRemoved = true;
}


//Setters
void PhoneBookEntry::setWorkPhone(long long &phone)
{
	m_workPhone = phone;
}

void PhoneBookEntry::setHomePhone(long long &phone)
{
	m_homePhone = phone;
}

void PhoneBookEntry::setName(std::string &fname, std::string &lname)
{
	m_Name = fname + " " + lname;
}

void PhoneBookEntry::setAddress(std::string &address, int &zipCode)
{
	m_address = address;
	m_zipCode = zipCode;
}

void PhoneBookEntry::setRemoved(bool removed)
{
	isRemoved = true;
}

//Getters
long long PhoneBookEntry::getHomePhone()
{
	return m_homePhone;
}

std::string PhoneBookEntry::getName()
{
	return m_Name;
}

long long PhoneBookEntry::getWorkPhone()
{
	return m_workPhone;
}

int& PhoneBookEntry::getZipCode()
{
	return m_zipCode;
}

bool PhoneBookEntry::IsRemoved()
{
	return isRemoved;
}


void PhoneBookEntry::writeToFile(std::fstream *file)
{
	*file << m_Name << std::endl;
	*file << m_homePhone << " " << m_workPhone << std::endl;
	*file << m_zipCode;
	*file << m_address << std::endl;
}

void PhoneBookEntry::showDetails()
{
	
	std::cout << "Name:  " << m_Name << std::endl;
	std::cout << "Address: " << m_address << std::endl;
	std::cout << "ZipCode: " << m_zipCode << std::endl;
	std::cout << "Phone Numbers: " << std::endl;
	std::cout << "\tWork -> " << m_workPhone;
	std::cout << "\tHome -> " << m_homePhone;
}