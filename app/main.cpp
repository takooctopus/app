#include<iostream>
#include "User.h"
#include <fstream>
#include<cassert>
#include"LinkedList.h"
#include "json\json.h"
using namespace std;
//将信息保存为JSON格式  
void writePremiumJson(LinkedList<Premium>* premiumLinkedList)
{
	//根节点  
	Json::Value root;
	//子节点  
	Json::Value partner;

	for (int i = 0; i < premiumLinkedList->GetLength(); i++)
	{
		partner["id"] = Json::Value(premiumLinkedList->GetValue(i)->getId());
		partner["name"] = Json::Value(premiumLinkedList->GetValue(i)->getName());
		partner["email"] = Json::Value(premiumLinkedList->GetValue(i)->getEmail());
		partner["password"] = Json::Value(premiumLinkedList->GetValue(i)->getPassword());
		root["premiums"].append(partner);

	}


	//直接输出  
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//缩进输出  
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//输出到文件  
	ofstream os;
	os.open("premium.json");
	os << sw.write(root);
	os.close();

}

bool addPremium(LinkedList<Premium>* premiumLinkedList)
{
	string name;
	string email;
	string password;
	string password2;
	bool validation;
	do
	{
		validation = true;
		cout << "please input name" << endl;
		cin >> name;
		cout << "please input email" << endl;
		cin >> email;
		cout << "please input password" << endl;
		cin >> password;
		cout << "please input password again" << endl;
		cin >> password2;
		//validation验证邮箱
		for (int i = 0; i < premiumLinkedList->GetLength(); i++)
		{
			cout << " name: " << premiumLinkedList->GetValue(i)->getName()
				<< " email: " << premiumLinkedList->GetValue(i)->getEmail()
				<< " password: " << premiumLinkedList->GetValue(i)->getPassword() << endl;
			if (email == premiumLinkedList->GetValue(i)->getEmail())
			{
				validation = false;
				break;
			}	
		}
		if (validation)
		{

		}
		else {
			cout << "email should not be same! choose another one!!! " << endl;
			continue;
		} 
		//validation 验证密码
		if (password != password2)
		{
			validation = false;
			cout << "password need to be same!!!!!" << endl;
			continue;
		}
	} while (!validation);

	Premium *premiumPointer = new Premium;
	premiumPointer->setId(premiumLinkedList->GetLength()+1);
	premiumPointer->setAllInfo(name,email,password);
	premiumLinkedList->Add(*premiumPointer);
	cout << "          Premium: id= "  <<premiumLinkedList->GetLength()<< "  " << premiumLinkedList->GetValue(premiumLinkedList->GetLength()-1)->getName() << " has been created" << endl;
	
	writePremiumJson(premiumLinkedList);
	return true;
}

bool editPremium()
{
	return true;
}

Premium* findPremium(LinkedList<Premium>* premiumLinkedList,string email)
{
	Premium* premium;
	for (int i = 0; i < premiumLinkedList->GetLength(); i++)
	{
		if (email == premiumLinkedList->GetValue(i)->getEmail())
		{
			premium = premiumLinkedList->GetValue(i);
			return premium;
		}	
	}
	return nullptr;
}

bool deletePremium(LinkedList<Premium>* premiumLinkedList)
{
	string email;
	cout << "please input email" << endl;
	cin >> email;
	Premium* premium = findPremium(premiumLinkedList, email);
	if (premium == nullptr)
	{
		cout << "there is no email!!!!!!" << endl;
		return false;
	}
	else {
		int id = premium->getId();
		cout << "====id=====" << id << endl;
		premiumLinkedList->Remove(premium->getId());
		for (int i = id; i < premiumLinkedList->GetLength(); i++)
		{
			premiumLinkedList->GetValue(i)->setId(i);
		}
	}
	//writePremiumJson(premiumLinkedList);
	return true;
}






bool checkAdmin(LinkedList<Admin>* adminLinkedList)
{
	string email;
	string password;
	cout << "请输入管理员邮箱" << endl;
	cin >> email;
	cout << "请输入管理员密码" << endl;
	cin >> password;
	for (int i = 0; i < adminLinkedList->GetLength(); i++)
	{
		cout << " name: " << adminLinkedList->GetValue(i)->getName()
			<< " email: " << adminLinkedList->GetValue(i)->getEmail()
			<< " password: " << adminLinkedList->GetValue(i)->getPassword() << endl;
		if ((email == adminLinkedList->GetValue(i)->getEmail()) && (password == adminLinkedList->GetValue(i)->getPassword()))
			return true;
	}
	return false;

}


//从文件中读取JSON  
void readAdminJson(LinkedList<Admin>* adminLinkedList)
{
	Json::Reader reader;
	Json::Value root;

	//从文件中读取，保证当前文件有test.json文件  
	ifstream in("admin.json", ios::binary);
	//in.open("test.json", ios::binary);  

	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}

	
	if (reader.parse(in, root))
	{
		Json::Value admins = root["admins"];
		for (int i = 0; i < admins.size(); i++)
		{
			Admin *adminPointer = new Admin;
			adminPointer->setAllInfo(admins[i]["name"].asString(), admins[i]["email"].asString(), admins[i]["password"].asString());
			adminLinkedList->Add(*adminPointer);
			cout << "          Admin: id= " << admins[i]["id"].asInt() << "  " << admins[i]["name"].asString() << " has been created" << endl;
		}
		cout << "Reading Admins Complete!" << endl;
		cout << "Length:  " << adminLinkedList->GetLength() << endl;
		cout << endl;
		cout << "================================================================================" << endl;
	}
	else
	{
		cout << "parse error\n" << endl;
	}

	in.close();
}

void readPremiumJson(LinkedList<Premium>* premiumLinkedList)
{
	Json::Reader reader;
	Json::Value root;

	//从文件中读取，保证当前文件有test.json文件  
	ifstream in("premium.json", ios::binary);
	//in.open("test.json", ios::binary);  

	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}


	if (reader.parse(in, root))
	{
		Json::Value premiums = root["premiums"];
		for (int i = 0; i < premiums.size(); i++)
		{
			Premium *premiumPointer = new Premium;
			premiumPointer->setId(i);
			cout << "======"<<i<<"======" << premiumPointer->getId() <<"===="<<premiumLinkedList->GetLength()<< endl;
			premiumPointer->setAllInfo(premiums[i]["name"].asString(), premiums[i]["email"].asString(), premiums[i]["password"].asString());
			premiumLinkedList->Add(*premiumPointer);
			cout << "          Premium: id= " << premiums[i]["id"].asInt() << "  " << premiums[i]["name"].asString() << " has been created" << endl;
		}
		cout << "Reading Premiums Complete!" << endl;
		cout << "Length:  " << premiumLinkedList->GetLength() << endl;
		cout << endl;
		cout << "================================================================================" << endl;
	}
	else
	{
		cout << "parse error\n" << endl;
	}

	in.close();
}


//从文件中读取JSON  
void readFileJson()
{
	Json::Reader reader;
	Json::Value root;

	//从文件中读取，保证当前文件有test.json文件  
	ifstream in("PersonalInfo.json", ios::binary);
	//in.open("test.json", ios::binary);  

	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}

	if (reader.parse(in, root))
	{
		//读取根节点信息  
		string name = root["name"].asString();
		int age = root["age"].asInt();
		bool sex_is_male = root["sex_is_male"].asBool();

		cout << "My name is " << name << endl;
		cout << "I'm " << age << " years old" << endl;
		cout << "I'm a " << (sex_is_male ? "man" : "woman") << endl;

		//读取子节点信息  
		string partner_name = root["partner"]["partner_name"].asString();
		int partner_age = root["partner"]["partner_age"].asInt();
		bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();

		cout << "My partner's name is " << partner_name << endl;
		cout << (partner_sex_is_male ? "he" : "she") << " is "
			<< partner_age << " years old" << endl;

		//读取数组信息  
		cout << "Here's my achievements:" << endl;
		for (unsigned int i = 0; i < root["achievement"].size(); i++)
		{
			string ach = root["achievement"][i].asString();
			cout << ach << '\t';
		}
		cout << endl;

		cout << "Reading Complete!" << endl;
	}
	else
	{
		cout << "parse error\n" << endl;
	}

	in.close();
}

//将信息保存为JSON格式  
void writeFileJson()
{
	//根节点  
	Json::Value root;

	//根节点属性  
	root["name"] = Json::Value("Mike Jiang");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//子节点  
	Json::Value partner;

	//子节点属性  
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//子节点挂到根节点上  
	root["partner"] = Json::Value(partner);

	//数组形式  
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//直接输出  
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//缩进输出  
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//输出到文件  
	ofstream os;
	os.open("demo.json");
	os << sw.write(root);
	os.close();

}
int main(int argc,char *argv[])
{
	/*User a;
	cout << a.getId() << endl;
	Admin b;
	cout << b.getId() << endl;
	Premium c;
	cout << c.getId() << endl;
	cout << c.getLocalEndTime().tm_mon <<endl;
	cout << c.isPremium() << endl;
	c.addEndTimeWithMonth();
	cout << c.getLocalEndTime().tm_mon << endl;
	cout << c.isPremium() << endl;*/
	
	cout << "================================================================================" << endl;
	cout << "只有管理员能够进入管理!!!" << endl;
	cout << "在最开始会load项目文件夹里面的admin.json和premium.json文件并且将其存入两个链表" << endl;
	cout << "edit 不做了= -= " << endl;
	cout << "================================================================================" << endl;
	int commandNumber;

	LinkedList<Admin> adminLinkedList;
	readAdminJson(&adminLinkedList);

	LinkedList<Premium> premiumLinkedList;
	readPremiumJson(&premiumLinkedList);
	
	bool isAdmin;
	string wannaExit = "no";
	do
	{
		isAdmin = checkAdmin(&adminLinkedList);
		if (!isAdmin)
		{
			cout << "wanna exit? (yes/no[default])" << endl;
			cin >> wannaExit;
			if (wannaExit == "yes" || wannaExit == "y") return 1;
		}
	} while (!isAdmin);
	do
	{
		cout << "================================================================================" << endl;
		cout << "Input order to get serve" << endl;
		cout << "时间匆忙，并没有做一些数据的验证工作与密码加密隐藏工作" << endl;
		cout << "最后所有对会员的改动会同步到premiun.json文件中" << endl;
		cout << "delete模块id有误" << endl;
		cout << "但是add模块是有用的！！！！" << endl;
		cout << "最后可以去源文件夹查看" << endl;
		cout << "使用了jsoncpp和一部分源码....." <<endl;
		cout << "    0 for exit " <<endl
			<< "    1 for addPremium " << endl << "    2 for editPremium" << endl
			<< "    3 for deletePremium" << endl << "    4 for getPremium" << endl;
		cout << "================================================================================" << endl;
		cin >> commandNumber;
		switch (commandNumber)
		{
		case 1: 
		{
			addPremium(&premiumLinkedList);
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			deletePremium(&premiumLinkedList);
			break;
		}
		case 4:
		{
			string email;
			Premium* a = findPremium(&premiumLinkedList,email);
			cout << a->getEmail();
			break;
		}
		default:
			writePremiumJson(&premiumLinkedList);
			break;
		}
	} while (commandNumber != 0);




	
	

	

	//readFileJson();
	//writeFileJson();
	return 0;
}