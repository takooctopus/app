#include<iostream>
#include "User.h"
#include <fstream>
#include<cassert>
#include"LinkedList.h"
#include "json\json.h"
using namespace std;
//����Ϣ����ΪJSON��ʽ  
void writePremiumJson(LinkedList<Premium>* premiumLinkedList)
{
	//���ڵ�  
	Json::Value root;
	//�ӽڵ�  
	Json::Value partner;

	for (int i = 0; i < premiumLinkedList->GetLength(); i++)
	{
		partner["id"] = Json::Value(premiumLinkedList->GetValue(i)->getId());
		partner["name"] = Json::Value(premiumLinkedList->GetValue(i)->getName());
		partner["email"] = Json::Value(premiumLinkedList->GetValue(i)->getEmail());
		partner["password"] = Json::Value(premiumLinkedList->GetValue(i)->getPassword());
		root["premiums"].append(partner);

	}


	//ֱ�����  
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//�������  
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//������ļ�  
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
		//validation��֤����
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
		//validation ��֤����
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
	cout << "���������Ա����" << endl;
	cin >> email;
	cout << "���������Ա����" << endl;
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


//���ļ��ж�ȡJSON  
void readAdminJson(LinkedList<Admin>* adminLinkedList)
{
	Json::Reader reader;
	Json::Value root;

	//���ļ��ж�ȡ����֤��ǰ�ļ���test.json�ļ�  
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

	//���ļ��ж�ȡ����֤��ǰ�ļ���test.json�ļ�  
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


//���ļ��ж�ȡJSON  
void readFileJson()
{
	Json::Reader reader;
	Json::Value root;

	//���ļ��ж�ȡ����֤��ǰ�ļ���test.json�ļ�  
	ifstream in("PersonalInfo.json", ios::binary);
	//in.open("test.json", ios::binary);  

	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}

	if (reader.parse(in, root))
	{
		//��ȡ���ڵ���Ϣ  
		string name = root["name"].asString();
		int age = root["age"].asInt();
		bool sex_is_male = root["sex_is_male"].asBool();

		cout << "My name is " << name << endl;
		cout << "I'm " << age << " years old" << endl;
		cout << "I'm a " << (sex_is_male ? "man" : "woman") << endl;

		//��ȡ�ӽڵ���Ϣ  
		string partner_name = root["partner"]["partner_name"].asString();
		int partner_age = root["partner"]["partner_age"].asInt();
		bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();

		cout << "My partner's name is " << partner_name << endl;
		cout << (partner_sex_is_male ? "he" : "she") << " is "
			<< partner_age << " years old" << endl;

		//��ȡ������Ϣ  
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

//����Ϣ����ΪJSON��ʽ  
void writeFileJson()
{
	//���ڵ�  
	Json::Value root;

	//���ڵ�����  
	root["name"] = Json::Value("Mike Jiang");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//�ӽڵ�  
	Json::Value partner;

	//�ӽڵ�����  
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//�ӽڵ�ҵ����ڵ���  
	root["partner"] = Json::Value(partner);

	//������ʽ  
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//ֱ�����  
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//�������  
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//������ļ�  
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
	cout << "ֻ�й���Ա�ܹ��������!!!" << endl;
	cout << "���ʼ��load��Ŀ�ļ��������admin.json��premium.json�ļ����ҽ��������������" << endl;
	cout << "edit ������= -= " << endl;
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
		cout << "ʱ���æ����û����һЩ���ݵ���֤����������������ع���" << endl;
		cout << "������жԻ�Ա�ĸĶ���ͬ����premiun.json�ļ���" << endl;
		cout << "deleteģ��id����" << endl;
		cout << "����addģ�������õģ�������" << endl;
		cout << "������ȥԴ�ļ��в鿴" << endl;
		cout << "ʹ����jsoncpp��һ����Դ��....." <<endl;
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