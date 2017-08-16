#include <iostream>
#include <fstream>
#include "Admin.h"

Admin::Admin()
{
	m_Name = "";
	m_Password = "";
}

int Admin::adminCount = 0;

Admin::Admin(const std::string &name, const std::string &password)
{
	m_Password = password;
	m_Name = name;
	adminCount++;
}

//Getters
std::string Admin::getName() const 
{
	return m_Name;
}

std::string Admin::getPass() const
{
	return m_Password;
}

//Setters
void Admin::setName(const std::string &fname, const std::string &lname)
{
	m_Name = fname + " " + lname;
}

void Admin::setPass(const std::string &pass)
{
	m_Password = pass;
}

void Admin::writeToFile(std::fstream *file)
{
	*file << m_Name << std::endl;
	*file << m_Password << std::endl;
}