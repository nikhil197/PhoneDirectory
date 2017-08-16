#pragma once
#include <string>

class Admin
{
private:
	std::string m_Name, m_Password;

public:
	static int adminCount;
	Admin();
	Admin(const std::string &name, const std::string &password);

	std::string getName() const;
	std::string getPass() const;

	void setName(const std::string &fname, const std::string &lname);
	void setPass(const std::string &pass);

	void writeToFile(std::fstream *file);

};