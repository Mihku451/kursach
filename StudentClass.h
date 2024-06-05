#pragma once
#include <iostream>
#include <Windows.h>
#include "ExamsResultsClass.h"
#include "ClassFileWraper.h"
#include "StudentNode.h"
#include "classCrypt.h"

class StudentClass 
{
public:

	static void addDefaultStudent(StudentNode* sn) {
		//sn->id = 0;

		strcpy_s(sn->surName, sizeof(sn->surName), "Ðóñàêîâ");
		strcpy_s(sn->name, sizeof(sn->name), "Àëåêñåé");
		strcpy_s(sn->middleName, sizeof(sn->middleName), "Ìèõàéëîâè÷");
		strcpy_s(sn->faculty, sizeof(sn->faculty), "10.05.04 Èíôîðìàöèîííî-àíàëèòè÷åñêèå ñèñòåìû áåçîïàñíîñòè");
		strcpy_s(sn->department, sizeof(sn->department), "Èíñòèòóò êèáåðáåçîïàñíîñòè è öèôðîâûõ òåõíîëîãèé");
		strcpy_s(sn->group, sizeof(sn->group), "ÁÈÑÎ-03-23");
		strcpy_s(sn->recordCardNumber, sizeof(sn->recordCardNumber), "20Á0857");
		sn->sex = true;
		sn->startYear = 2021;
		strcpy_s(sn->birthDateString, sizeof(sn->birthDateString), "27.12.1984");
		
		ExamsResultsClass* er = new ExamsResultsClass();
		er->add(0, "ßûêè ïðîãðàììèðîâàíèÿ 1", 5);
		er->add(0, "Ìàòåìàòèêà 1", 5);
		er->add(0, "Ôèçêóëüòóðà 1", true);
		er->add(1, "ßûêè ïðîãðàììèðîâàíèÿ 2", 5);
		er->add(1, "Ìàòåìàòèêà 2", 5);
		er->add(1, "Ôèçêóëüòóðà 2", true);
		for (int i = 0; i < sesCount; i++)
			for (int j = 0; j < namesCount; j++) {
				sn->examsRecordsData[i][j].isEmpty = er->data[i][j].isEmpty;
				if (sn->examsRecordsData[i][j].isEmpty)
				{
					sn->examsRecordsData[i][j].mark = 0;
					strcpy_s(sn->examsRecordsData[i][j].name, sizeof(sn->examsRecordsData[i][j].name), "");
				}
				else
				{
					sn->examsRecordsData[i][j].mark = er->data[i][j].mark;
					strcpy_s(sn->examsRecordsData[i][j].name, sizeof(sn->examsRecordsData[i][j].name), er->data[i][j].name);
				}
			}
		char firstLetter = sn->surName[0];
		if ((firstLetter >= 'À' && firstLetter <= 'Ï') || (firstLetter >= 'à' && firstLetter <= 'ï'))
		{
			sn->group_num = 1; // Ôàìèëèÿ âõîäèò â äèàïàçîí À-Ï
		}
		else
		{
			sn->group_num = 2; // Ôàìèëèÿ âõîäèò â äèàïàçîí Ð-ß
		}
		sn->next = NULL;
		delete er;
	}

	bool editSex() {
		ClassMenu* sexMenu = new ClassMenu();
		int resultSelectedItem = 1;
		const int exitItem = 3;
		sexMenu->addTitleItem("Âûáåðèòå ïîë: ");
		sexMenu->addItem("ìóæñêîé");
		sexMenu->addItem("æåíñêèé");
		while (resultSelectedItem != exitItem) {
			sexMenu->run();
			resultSelectedItem = sexMenu->getSelectedItem();
			switch (resultSelectedItem) {
			case 0:
				return true;
				resultSelectedItem = exitItem;
				break;
			case 1:
				return false;
				resultSelectedItem = exitItem;
				break;
			default:
				break;
			}
		}
	}

	void editStudent(StudentNode* sn)
	{
		ClassMenu* studDataMenu = new ClassMenu();
		int resultStudDataMenu = 1;
		const int exitStudDataMenu = 0;
		ClassEdit* ce = new  ClassEdit();
		ExamsResultsClass* erc = new ExamsResultsClass();
		studDataMenu->addItem("Âûõîä");   //0
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü ôàìèëèþ"); //1
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü èìÿ");   //2
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü îò÷åñòâî");   //3
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü èíñòèòóò");   //4
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü êàôåäðó");   //5
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü ãðóïïó");   //6
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü íîìåð çà÷åòíîé êíèæêè");   //7
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü ïîë");   //
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü ãîä ïîñòóïëåíèÿ â ÂÓÇ");   //8
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü äàòó ðîæäåíèÿ");   //9
		studDataMenu->addItem("Äîáàâèòü/èçìåíèòü îöåíêè");   //10
		int day, month, year;
		while (resultStudDataMenu != exitStudDataMenu) {
			studDataMenu->eraseTitle();
			studDataMenu->addTitleItem("Èçìåíåíèå/äîáàâëåíèå äàííûõ î ñòóäåíòå:");
			studDataMenu->addTitleItem("Ôàìèëèÿ: " + string(sn->surName) + " Èìÿ: " + string(sn->name) + " Îò÷åñòâî: " + string(sn->middleName));
			string sexString = "";
			if (sn->sex)
				sexString = "ìóæñêîé";
			else { sexString = "æåíñêèé"; }
			studDataMenu->addTitleItem("ïîë: " + sexString + " äàòà ðîæäåíèÿ: " + string(sn->birthDateString) + " ãîä ïîñòóïëåíèÿ:" + std::to_string(sn->startYear));
			studDataMenu->addTitleItem("Íîìåð çà÷åòíîé êíèæêè: " + string(sn->recordCardNumber) + " Ãðóïïà: " + string(sn->group));
			studDataMenu->addTitleItem("Èíñòèòóò: " + string(sn->faculty));
			studDataMenu->addTitleItem("Êàôåäðà: " + string(sn->department));
			studDataMenu->run();
			resultStudDataMenu = studDataMenu->getSelectedItem();
			string tmpString = "";
			char tmpchar;
			int year = 0;
			int startYear = 0;
			switch (resultStudDataMenu) {
			case 0:
				resultStudDataMenu = exitStudDataMenu;
				break;
			case 1:
				ce->setLabel("Ââåäèòå ôàìèëèþ. ");
				strcpy_s(sn->surName, sizeof(sn->surName), ce->setDataString(sn->surName).c_str());
				tmpchar = sn->surName[0];
				if ((tmpchar >= 'À' && tmpchar <= 'Ï') || (tmpchar >= 'à' && tmpchar <= 'ï')) {
					sn->group_num = 1;
				}
				else {
					sn->group_num = 2;
				}
				break;
			case 2:
				ce->setLabel("Ââåäèòå èìÿ. ");
				strcpy_s(sn->name, sizeof(sn->name), ce->setDataString(sn->name).c_str());
				break;
			case 3:
				ce->setLabel("Ââåäèòå îò÷åñòâî. ");
				strcpy_s(sn->middleName, sizeof(sn->middleName), ce->setDataString(sn->middleName).c_str());
				break;
			case 4:
				ce->setLabel("Ââåäèòå íàçâàíèå èíñòèòóòà. ");
				strcpy_s(sn->faculty, sizeof(sn->faculty), ce->setDataString(sn->faculty).c_str());
				break;
			case 5:
				ce->setLabel("Ââåäèòå íàçâàíèå êàôåäðû. ");
				strcpy_s(sn->department, sizeof(sn->department), ce->setDataString(sn->department).c_str());
				break;
			case 6:
				ce->setLabel("Ââåäèòå ãðóïïó. ");
				strcpy_s(sn->group, sizeof(sn->group), ce->setDataString(sn->group).c_str());
				break;
			case 7:
				ce->setLabel("Ââåäèòå íîìåð çà÷åòíîé êíèæêè. ");
				strcpy_s(sn->recordCardNumber, sizeof(sn->recordCardNumber), ce->setDataString(sn->recordCardNumber).c_str());
				break;
			case 8:
				ce->setLabel("Ââåäèòå ïîë. ");
				sn->sex = editSex();        ////
				break;
			case 9:
				ce->setLabel("Ââåäèòå ãîä ïîñòóïëåíèÿ â ÂÓÇ. ");
				startYear = ce->setDataInt(1996, 2023, 2023);
				//tmpString = sb->split(sn->birthDateString.c_str(), '.', 3);
				year = atoi(tmpString.c_str());
				if (year == 0)
					sn->startYear = startYear;
				else
				{
					if (startYear - year >= 15) {
						sn->startYear = startYear;
					}
					else
					{
						cout << "Îøèáêà ãîä ïîñòóïëåíèÿ â èíñòèòóò äîëæåí áûòü íà 15 ëåò áîëüøå ÷åì ãîä ðîæäåíèÿ";
						_getch();
					}
				}
				break;
			case 10:
				ce->setLabel("Ââåäèòå äåíü ðîæäåíèÿ. ");
				day = ce->setDataInt(1, 31, 31);
				ce->setLabel("Ââåäèòå ìåñÿö ðîæäåíèÿ. ");
				month = ce->setDataInt(1, 12, 12);
				ce->setLabel("Ââåäèòå ãîä ðîæäåíèÿ. ");
				year = ce->setDataInt(1900, 2014, 2004);
				if (sn->startYear < 1990) {
					cout << "Îøèáêà ãîä ïîñòóïëåíèÿ â èíñòèòóò äîëæåí áûòü íå ðàíåå 1990";
					_getch();
				}
				else
				{
					if (sn->startYear - year >= 13) {
						string tmpStr = to_string(day) + "." + to_string(month) + "." + to_string(year);
						strcpy_s(sn->birthDateString, sizeof(sn->birthDateString), tmpStr.c_str());
					}
					else
					{
						cout << "Îøèáêà ãîä ïîñòóïëåíèÿ â èíñòèòóò äîëæåí áûòü íà 13 ëåò áîëüøå ÷åì ãîä ðîæäåíèÿ";
						_getch();
					}
				}
				break;
			case 11:
				ce->setLabel("Ïðîñìîòðåòü/ èçìåíèòü îöåíêè.");
				for (int i = 0; i < sesCount; i++)
					for (int j = 0; j < namesCount; j++) {
						erc->data[i][j].isEmpty = sn->examsRecordsData[i][j].isEmpty;
						if (erc->data[i][j].isEmpty)
						{
							erc->data[i][j].mark = 0;
							strcpy_s(erc->data[i][j].name, sizeof(erc->data[i][j].name), "");
						}
						else
						{
							erc->data[i][j].mark = sn->examsRecordsData[i][j].mark;
							strcpy_s(erc->data[i][j].name, sizeof(erc->data[i][j].name), sn->examsRecordsData[i][j].name);
						}
					}
				erc->editExamsResults();
				for (int i = 0; i < sesCount; i++)
					for (int j = 0; j < namesCount; j++) {
						sn->examsRecordsData[i][j].isEmpty = erc->data[i][j].isEmpty;
						if (sn->examsRecordsData[i][j].isEmpty)
						{
							sn->examsRecordsData[i][j].mark = 0;
							strcpy_s(sn->examsRecordsData[i][j].name, sizeof(sn->examsRecordsData[i][j].name), "");
						}
						else
						{
							sn->examsRecordsData[i][j].mark = erc->data[i][j].mark;
							strcpy_s(sn->examsRecordsData[i][j].name, sizeof(sn->examsRecordsData[i][j].name), erc->data[i][j].name);
						}
					}

				break;
			default:
				break;
			}
		}
		delete erc;
		delete studDataMenu;
		delete ce;
	}


	double getAvrMarks(StudentNode* sn) {
		double sum = 0;
		double count = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				if (sn->examsRecordsData[i][j].isEmpty == false and sn->examsRecordsData[i][j].mark > 1) {
					sum = sum + sn->examsRecordsData[i][j].mark;
					count++;
				}
		double avr = 0;
		if (count > 0)
			avr = 1.00*sum / count;
		return avr;
	}
	int getGroupNum(StudentNode* sn) {
		char firstLetter = sn->surName[0];
		int num;
		if ((firstLetter >= 'À' && firstLetter <= 'Ï') || (firstLetter >= 'à' && firstLetter <= 'ï'))
		{
			num = 1; // Ôàìèëèÿ âõîäèò â äèàïàçîí À-Ï
		}
		else
		{
			num = 2; // Ôàìèëèÿ âõîäèò â äèàïàçîí Ð-ß
		}
		return num;
	}
	double getMarks45(StudentNode* sn) {
		double sum = 0;
		double count = 0;
		for (int i = 0; i < sesCount; i++)
			for (int j = 0; j < namesCount; j++)
				if (sn->examsRecordsData[i][j].isEmpty == false and sn->examsRecordsData[i][j].mark > 1) {
					count++;
					if (sn->examsRecordsData[i][j].mark > 3)
						sum++;
				}
		double proc = 0;
		if (count > 0)
			proc = sum / count;
		return proc;
	}

	//list
	struct StudentNode* myHead;
	int countItem = 0;

	StudentClass() {
		countItem = 0;
		myHead = NULL;
	}

	//Âèçóàëèçàöèÿ äëÿ äîáàâëåíèÿ è óäàëåíèÿ ýëåìåíòîâ â îäíîñâÿçíîì ñïèñêå.
	//https://www.cs.usfca.edu/~galles/visualization/StackLL.html

	void addItem()
	{
		struct StudentNode* newItem = new StudentNode();
		//newItem->StudentNode = data;
		addDefaultStudent(newItem);
		editStudent(newItem);
		if (countItem == 0)
			newItem->next = NULL;
		else
			newItem->next = myHead;
		myHead = newItem;
		countItem++;
	}

	void insertItem(int index) {
		if (not (index >= 0 and index <= countItem and countItem >= 0))
			return;
		if (index == 0) {
			addItem();
		}
		else
		{
			struct StudentNode* current = myHead;
			for (int i = 0; i < index - 1; i++) {
				current = current->next;
			}
			struct StudentNode* newItem = new StudentNode();
			//newItem->data = data;
			addDefaultStudent(newItem);
			editStudent(newItem);
			newItem->next = current->next;
			current->next = newItem;
			countItem++;
		}
	}

	void editItem(int index) {
		if (index >= 0 and index < countItem and countItem>0) {
			struct StudentNode* current = myHead;
			for (int i = 0; i < index; i++) {
				current = current->next;
				//cout << "+" << current->data;
			}
			//current->data = data;
			editStudent(current);
		}
		else {
			cout << endl << "Îøèáêà èíäåêñ íå â äèàïàçîíå";
		}
	}

	void deleteItem(int index) {
		if (index >= 0 and index < countItem and countItem>0) {
			struct StudentNode* current = myHead;
			struct StudentNode* old;
			if (index == 0) {
				old = myHead;
				myHead = current->next;
				delete old;
				countItem--;
			}
			else {
				int i = 0;
				while (current) {
					if (i == index - 1) {
						old = current->next->next;
						delete current->next;
						current->next = old;
						countItem--;
						break;
					}
					i++;
					current = current->next;
				}
			}
		}
	}

	void printMyList() {
		struct StudentNode* current = myHead;
		cout << endl;
		while (current) {
			//cout << " " << current->data;
			cout << " " << current->surName;
			current = current->next;
		}
	}

	//list

	StudentNode* getItem(int index) {
		struct StudentNode* current = myHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
			//cout << "+" << current->data;
		}
		return current;
	}



	//
	void mainMenu() {
		ClassMenu* mainMenu = new ClassMenu();
		mainMenu->addTitleItem("Ãëàâíîå ìåíþ");
		mainMenu->addItem("Ïðîñìîòðåòü ñïèñîê ñòóäåòîâ (óäàëèòü èëè èçìåíèòü äàííûå)"); //0
		mainMenu->addItem("Äîáàâèòü äàííûå î ñòóäåíòå â ÁÄ"); //1
		mainMenu->addItem("Çàãðóçèòü ñòóäåíòîâ èç ôàéëà ÁÄ"); //2
		mainMenu->addItem("Ñîõðàíèòü ÁÄ ñòóäåíòîâ â ôàéë"); //3
		mainMenu->addItem("Âûïîëíèòü âàðèàíò XX"); //4
		mainMenu->addItem("Âûõîä"); //5
		int resultSelectedItem = 0;
		int exitInt = 4;
		ClassMenu* studentsMenu = new ClassMenu();
		studentsMenu->addTitleItem("Ñïèñîê ñòóäåíòîâ");
		int resultStudentSelectedItem = 1;
		const int exitIntStudentMenu = 0;
		StudentNode* sn;
		StudentClass* st = new StudentClass();
		ClassMenu* delStudentsMenu = new ClassMenu();
		int curCount;
		ClassEdit* ce = new  ClassEdit();
		int startYear = 0;
		int endYear = 0;
		int year = 0;
		string firstPartString;
		//sort
		ClassCrypt* cc = new ClassCrypt();
		ClassFileWraper* cfw = new ClassFileWraper();
		strcpy_s(cfw->filename, sizeof(cfw->filename), "dataBinary1.txt");
		cfw->mode = true; // Binary     //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this->myHead = cfw->loadData();
		countItem = cfw->countItem;
		//sort
		while (resultSelectedItem != exitInt) {
			mainMenu->run();
			resultSelectedItem = mainMenu->getSelectedItem();
			switch (resultSelectedItem) {
			case 0:
				resultStudentSelectedItem = 1;
				while (resultStudentSelectedItem != exitIntStudentMenu) {
					studentsMenu->eraseItem();
					studentsMenu->addItem("Âûõîä");
					studentsMenu->addItem("Óäàëèòü äàííûå î ñòóäåíòå");
					struct StudentNode* current = myHead;
					while (current) {
						string tmpString = string(current->surName) + " " + string(current->name) + " " + string(current->middleName) + " " + string(current->birthDateString);
						studentsMenu->addItem(tmpString); //äîáàâèòü â ìåíþ ñòóäåíòîâ
						current = current->next;
					}
					studentsMenu->run();
					resultStudentSelectedItem = studentsMenu->getSelectedItem();
					//if (resultStudentSelectedItem == exitIntStudentMenu) {
					//	break;
					//}
					if (resultStudentSelectedItem == 1) //óäàëåíèå äàííûõ î ñòóäåíòå
					{
						delStudentsMenu->eraseAll();
						delStudentsMenu->addTitleItem("Âûáåðèòå ñòóäåíòà äëÿ óäàëåíèÿ äàííûõ");
						delStudentsMenu->addItem("Âûõîä");
						int resultDel = 1;
						const int exitDel = 0;
						struct StudentNode* current = myHead;
						while (current) {
							string tmpString = string(current->surName) + " " + string(current->name) + " " + string(current->middleName) + " " + string(current->birthDateString);
							delStudentsMenu->addItem(tmpString); //äîáàâèòü â ìåíþ ñòóäåíòîâ
							current = current->next;
						}
						while (resultDel != exitDel) {
							delStudentsMenu->run();
							resultDel = delStudentsMenu->getSelectedItem();
							if (resultDel == exitDel) {
								break;
							}
							else {
								int num = resultDel - 1;
								//sdb->DataBase.erase(std::next(sdb->DataBase.begin(), num));
								deleteItem(num);
								break;
							}
						}
					}
					if (resultStudentSelectedItem > 1)
					{
						int num = resultStudentSelectedItem - 2;
						editItem(num);
						//ìîæíî ñäåëàòü ïðîâåðêó åñòü ëè òàêàÿ åù¸ 
					}
				}
				//resultSelectedItem = exitInt;
				break;
			case 1: //Äîáàâèòü ñòóäåíòà
				addItem();
				break;
			case 2: //Çàãðóçèòü ñòóäåíòîâ èç ôàéëà ÁÄ
				//sort
				ce->setLabel("Ââåäèòå ïàðîëü ");
				strcpy_s(cc->password, sizeof(cc->password), ce->setDataString(cc->password).c_str());
				
				cc->Decrypt();
				_getch();
				this->myHead = cfw->loadData();  //todo delete memory leak
				countItem = cfw->countItem;
				break;
			case 3: //Ñîõðàíèòü ÁÄ ñòóäåíòîâ â ôàéë
				//sort
				
				cfw->saveData(myHead);
				ce->setLabel("Ââåäèòå ïàðîëü ");
				strcpy_s(cc->password, sizeof(cc->password), ce->setDataString(cc->password).c_str());
				cc->Crypt();
				_getch();
				break;
			case 4:
				
				//Âûïîëíèòü âàðèàíò XX
				//printAllSurName_Name_MName_bYaear_AvrMarks();
				processingAvrMarks_groupnum();
				//printAllSurName_Name_MName_bYaear_AvrMarks();
				sort();
				printAllSurName_Name_MName_bYaear_AvrMarks();
				_getch();
				finds();
				_getch();
				resultSelectedItem = 0;
				break;
			case 5:
				resultSelectedItem = exitInt;
				break;
			default:
				break;
			}
		}
		//_getch();
	}

	//sort
	void processingAvrMarks_groupnum() {
		struct StudentNode* current = myHead;
		while (current) {
			current->avrMark = getAvrMarks(current);
			current->group_num = getGroupNum(current);
			current = current->next;
		}
	}
	StudentNode* getElement(int ind) {
		struct StudentNode* current = myHead;
		for (int i = 0; i < ind; i++) {
			current = current->next;
		}
		return current;
	}
	void  copyDataElement(StudentNode* current, StudentNode* element) {
		strcpy_s(current->surName, sizeof(current->surName), element->surName);
		strcpy_s(current->name, sizeof(current->name), element->name);
		strcpy_s(current->middleName, sizeof(current->middleName), element->middleName);
		strcpy_s(current->faculty, sizeof(current->faculty), element->faculty);
		strcpy_s(current->department, sizeof(current->department), element->department);
		strcpy_s(current->group, sizeof(current->group), element->group);
		strcpy_s(current->recordCardNumber, sizeof(current->recordCardNumber), element->recordCardNumber);
		current->group_num = element->group_num;
		current->sex = element->sex;
		current->startYear = element->startYear;
		strcpy_s(current->birthDateString, sizeof(current->birthDateString), element->birthDateString);
		for (int i = 0; i < sesCount; i++)
			for (int j = 0; j < namesCount; j++) {
				current->examsRecordsData[i][j].isEmpty = element->examsRecordsData[i][j].isEmpty;
				if (current->examsRecordsData[i][j].isEmpty)
				{
					current->examsRecordsData[i][j].mark = 0;
					strcpy_s(current->examsRecordsData[i][j].name, sizeof(current->examsRecordsData[i][j].name), "");
				}
				else
				{
					current->examsRecordsData[i][j].mark = element->examsRecordsData[i][j].mark;
					strcpy_s(current->examsRecordsData[i][j].name, sizeof(current->examsRecordsData[i][j].name), element->examsRecordsData[i][j].name);
				}
			}
		current->avrMark = element->avrMark; //!!!!
	}
	void  setElement(int ind, StudentNode* element) {
		struct StudentNode* current = myHead;
		for (int i = 0; i < ind; i++) {
			current = current->next;
		}
		strcpy_s(current->surName, sizeof(current->surName), element->surName);
		strcpy_s(current->name, sizeof(current->name), element->name);
		strcpy_s(current->middleName, sizeof(current->middleName), element->middleName);
		strcpy_s(current->faculty, sizeof(current->faculty), element->faculty);
		strcpy_s(current->department, sizeof(current->department), element->department);
		strcpy_s(current->group, sizeof(current->group), element->group);
		strcpy_s(current->recordCardNumber, sizeof(current->recordCardNumber), element->recordCardNumber);
		current->sex = element->sex;
		current->startYear = element->startYear;
		strcpy_s(current->birthDateString, sizeof(current->birthDateString), element->birthDateString);
		for (int i = 0; i < sesCount; i++)
			for (int j = 0; j < namesCount; j++) {
				current->examsRecordsData[i][j].isEmpty = element->examsRecordsData[i][j].isEmpty;
				if (current->examsRecordsData[i][j].isEmpty)
				{
					current->examsRecordsData[i][j].mark = 0;
					strcpy_s(current->examsRecordsData[i][j].name, sizeof(current->examsRecordsData[i][j].name), "");
				}
				else
				{
					current->examsRecordsData[i][j].mark = element->examsRecordsData[i][j].mark;
					strcpy_s(current->examsRecordsData[i][j].name, sizeof(current->examsRecordsData[i][j].name), element->examsRecordsData[i][j].name);
				}
			}
		current->group_num = element->group_num;
		current->avrMark = element->avrMark; //!!!!
	}
	void sort() {
		//https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
		//https://www.geeksforgeeks.org/bubble-sort/
		int size = countItem;
		struct StudentNode* tmp1 = new StudentNode();
		struct StudentNode* tmp2 = new StudentNode();
		for (int i = 0; i < size; i++) {
			cout << endl << getElement(i)->surName;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1; j++) {
				if (getElement(j)->group_num > getElement(j + 1)->group_num) {
					copyDataElement(tmp1, getElement(j));
					copyDataElement(tmp2, getElement(j + 1));
					setElement(j + 1, tmp1);
					setElement(j, tmp2);
					//copyDataElement(tmp1, getElement(0));
					//copyDataElement(tmp2, getElement(3));
					//setElement(3, tmp1);
					//setElement(0, tmp2);
				}
				if (getElement(j)->group_num == getElement(j + 1)->group_num) {
					if (getElement(j)->avrMark > getElement(j + 1)->avrMark) {
						copyDataElement(tmp1, getElement(j));
						copyDataElement(tmp2, getElement(j + 1));
						setElement(j + 1, tmp1);
						setElement(j, tmp2);
					}
				}
			}
		}
	}
		
	void finds() {
		ClassMenu* findMenu = new ClassMenu();
		int resultSelectedItem = 1;
		const int exitItem = 3;
		findMenu->addTitleItem("Âûïîëíèòü ïðîâåðêó?");
		findMenu->addItem("äà");
		findMenu->addItem("íåò");
		string tmpstring;
		struct StudentNode* current = myHead;
		while (resultSelectedItem != exitItem) {
			findMenu->run();
			resultSelectedItem = findMenu->getSelectedItem();
			switch (resultSelectedItem) {
			case 0:
				cout << "ââåäèòå äàòó ðîæäåíèÿ";
				cin >> tmpstring;
				while (current) {
					if (tmpstring == current->birthDateString) {
						cout << string(current->surName) + " " + string(current->name) + " " + string(current->middleName);

				}
					current = current->next;
				}
				resultSelectedItem = exitItem;
				break;
			case 1:
				
				resultSelectedItem = exitItem;
				break;
			default:
				break;
			}
		}
	}
	void printAllSurName_Name_MName_bYaear_AvrMarks() {
		struct StudentNode* current = myHead;
		cout << endl;
		while (current) {
			//cout << " " << current->data;
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << current->group_num<<" ïîäãðóïïà " << string(current->surName) + " " + string(current->name) + " " + string(current->middleName) + " " + string(current->birthDateString) + " " << current->avrMark << endl;
			current = current->next;
		}
		//_getch();
	}
	//sort


};

