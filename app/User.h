#ifndef USER_H
#define USER_H
#include<iostream>
#include<ctime>

using namespace std;

class User
{
public:
	User();
	virtual ~User();
	void setName(string name) { this->name = name; }
	void setEmail(string email) { this->email = email; }
	void setPassword(string password) { this->password = password; }
	void setAllInfo(string, string, string);
	string getName() { return this->name; }
	string getEmail() { return this->email; }
	string getPassword() { return this->password; }
	virtual void setId(int i) { this->id = i; }
	virtual int getId() { return this->id; }
	void getAllInfo();
	static int getAmount() { return amountOfUser; }
	static int getNumberofUser() { return numberOfUser; }
private:
	int id;
	string name;
	string email;
	string password;

	static int amountOfUser;
	static int numberOfUser;

};

int User::amountOfUser = 0;
int User::numberOfUser = 0;

User::User()
{
	(this->numberOfUser)++;
	(this->amountOfUser)++;
	this->id = this->numberOfUser;
	cout << "People id= " << this->getId() << " had been created!" << endl;
}

User::~User()
{
	(this->numberOfUser)--;
	(this->amountOfUser)--;
	cout << "People id= " << this->getId() <<" had been destroyed!"<< endl;
}

void User::setAllInfo(string name, string email, string password)
{
	this->setName(name);
	this->setEmail(email);
	this->setPassword(password);
}


class Admin : public User
{
private:
	static int amountOfAdmin;
	static int numberOfAdmin;
public:
	bool addAmountOfAdmin() { amountOfAdmin++; return true; }
	bool addNumberOfAdmin() { numberOfAdmin++; return true; }
	Admin();
	~Admin();
};
Admin::Admin() : User() 
{
	cout << "Admin() function " << getId() <<endl; 
};
Admin::~Admin() {};



class Premium : public User
{
private:
	static int amountOfAdmin;
	static int numberOfAdmin;
	time_t endTime;
public:
	void setEndTime();
	tm getLocalEndTime();
	//void P() { tm ltm; localtime_s(&ltm, &endTime); cout << endTime << "   " << ltm.tm_mday << endl; }
	//tm P() { tm ltm; localtime_s(&ltm, &endTime); return ltm; }
	void addEndTimeWithMonth(int);
	int isPremium();
	Premium();
	~Premium();
};
Premium::Premium() : User() {setEndTime(); }
Premium::~Premium() {};
void Premium::setEndTime() 
{
	this->endTime = time(0); 
}
tm Premium::getLocalEndTime()
{
	tm localEndtime;
	localtime_s(&localEndtime, &endTime);
	return localEndtime;
}
void Premium::addEndTimeWithMonth(int numberOfMonth = 1)
{
	if (!this->isPremium())
	{
		this->endTime = time(0);
	}
	this->endTime = this->endTime + numberOfMonth*3600*24*30;
}
int Premium::isPremium()
{
	return (this->endTime > time(0));
}


#endif


