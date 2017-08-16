#pragma once
#include <string>

class PhoneBookEntry
{
private:

	std::string m_Name;
	int m_zipCode;
	long long m_workPhone;
	long long m_homePhone;
	std::string m_address;
	bool isRemoved;

public:
	static int count;

	//Constuctors
	PhoneBookEntry();
	PhoneBookEntry(const std::string& name, const int& zipCode, const long long& workPhone, const long long& homePhone, const std::string& address);
	PhoneBookEntry(const std::string& name, const int& zipCode, const long long& homePhone, const std::string& address);

	virtual ~PhoneBookEntry();
	
	//Getters
	long long getWorkPhone();
	long long getHomePhone();
	std::string getName();
	int& getZipCode();
	bool IsRemoved();

	//Setters
	void setWorkPhone(long long &phone);
	void setHomePhone(long long &phone);
	void setAddress(std::string &address, int &zipCode);
	void setName(std::string &fname, std::string &lname);
	void setRemoved(bool removed);

	void showDetails();
	void writeToFile(std::fstream *file);
};