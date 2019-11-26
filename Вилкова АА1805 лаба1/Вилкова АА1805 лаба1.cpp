
//ЛАБОРАТОРНАЯ №2

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h> 

using namespace std;

struct Vopros {
	string question;
	int category;
	bool level;
};

struct test {
	int number;
	vector <Vopros> Qs;
};

void CreatMenu() {
	cout << "0- Выйти из программы\n1- Добавить вопрос в базу вопросов\n2- Вывести базу вопросов\n3- Отредактировать вопрос\n4- Cгенирировать билет\n5- Cохранить базу в файл\n6- Cчитать базу из файла\n7- Отсортировать базу" << endl;
	return;
}

int GetNumber(int min, int max) {
	int x;
    do {
		cout << "Введите верное значение" << endl;
		while (!(cin >> x)) {
			cout << "Введите верное значение" << endl;
			cin.clear();
			cin.ignore();
		}
	} while ( x < min || x > max ); 
	return x;
}

Vopros CreatTask(){
	Vopros v;
	cin.ignore();
	cout << "Question\n";
	getline(cin, v.question);
	cout << "Category (1-3)\n";
	v.category = GetNumber(1, 3);
	v.level = false;
	return v;
}

void OutputVopros (Vopros v){
	cout << "Question: " << v.question << endl;
	cout << "Category (1-3): " << v.category << endl;
	cout << "Level: " << v.level << endl;
	cout << endl;
}

void ChangeVopros(Vopros& v) {
	cout << "1-Отредактировать вопрос\n2-Изменить категорию\n3-Поменять сложность" << endl;
	int n; //Номер меню для изменения
	n = GetNumber(1, 3);
	switch (n)
	{
	case 1:
		cin.ignore();
		cout << "Ваш новый вопрос" << endl;
		getline(cin, v.question);
		break;

	case 2: 
		cout << "Так какая это категория?" << endl;
		v.category = GetNumber(1, 3);
		break;
	case 3:
		v.level = !v.level;
	}
	
}

void WriteToFile(const vector <Vopros>& DBase, string name) {
	ofstream fout(name);
	for (int i = 0; i < DBase.size(); i++)
	{
		fout << "Вопроc " << endl;
		fout << DBase[i].question << endl;
		fout << DBase[i].category << endl;
		fout << DBase[i].level << endl;
		fout << "" << endl;
	}
		
	fout.close();
}

void ReadOutFile(vector <Vopros>& Base, string name) {
	string NumberOfQuestion,st;
	ifstream fin(name);
	Vopros v;
	if (!fin.is_open()) 
		cout << "Файл не может быть открыт или не существует!\n";
	else {
		while (!fin.eof()) {
			getline(fin, NumberOfQuestion);
			getline(fin, v.question);
			fin >> v.category;
			fin >> v.level;
			fin >> st;
			Base.push_back(v);
		}
		cout << "Данные из файла записаны в базу\n" << endl;
	} 
	fin.close();
} 

test CreatBilet (int count, vector <Vopros>  Base) {
	test t;
	int j;
	while (t.Qs.size() != count-1) {
		j = rand() % Base.size();
		if (Base[j].level == 0) {
			t.Qs.push_back(Base[j]);
			Base.erase(Base.begin() + j);
		}
	};
	while (!(t.Qs.size() == count)) {
		j = rand() % Base.size();
		if (Base[j].level == 1 || Base[j].level == 0) {
			t.Qs.push_back(Base[j]);
			Base.erase(Base.begin() + j);
		};
	};
	return t;
}

bool IsBaseExist(const vector <Vopros>& DBase) {
	bool b = true;
	if (DBase.size() == 0) {
		cout << "База пуста. Нажмите 1, чтобы добавить\n" << endl;
		b = false;
	}
	return b;
}

void printTest1(const test& t,int i,int v)
{
	cout << "________________Вариант №" << i+1 << "________________" << endl;
	for (int k = 0; k < v; k++) {
		cout << k + 1 << ". " << t.Qs[k].question << "\nСложность: " << t.Qs[k].level << endl;
	}	
	cout << "___________________________________________\n" << endl;
}

void printTest2(const test& t, int i, int v)
{
	cout << "Контрольная работа\n" << "Вариант " << i + 1 << "\n" << endl;
	for (int k = 0; k < v; k++) {
		cout << k + 1 << ") " << t.Qs[k].question << "\nСложность: " << t.Qs[k].level << endl;
	}
	cout << "___________________________________________\n" << endl;
}

void printTest3(const test& t, int i, int v)
{
	cout << "Контрольная работа\n" << "Вариант " << i + 1 << "\n" << endl;
	for (int k = 0; k < v; k++) {
		cout << k + 1 << ". " << t.Qs[k].question << "\nСложность: " << t.Qs[k].level << endl;
	}
	cout << "Зав.кафедрой _________________\n" << endl;
}

template <typename T>
void Sort(vector <Vopros>& Base, T Vopros::* f)
{
	Vopros v;
	for (int i = 0; i < Base.size() - 1; i++)
		for (int j = 0; j < Base.size() - 1; j++)
			if (Base[j + 1].*f < Base[j].*f)
			{
				v = Base[j];
				Base[j] = Base[j + 1];
				Base[j + 1] = v;
			}
}

typedef void (*MyPrints)(const test&,int,int);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <Vopros> DBase;
	vector <test> BiletBase;
	while (1) {
		CreatMenu();
		switch (GetNumber(0,7))
		{
			case 0: 
				return 0;
			case 1: 
				DBase.push_back(CreatTask());
				break;	
			case 2: 
				if (!IsBaseExist(DBase)) {
					break;
				}
				else {
					for (int i = 0; i < DBase.size(); i++)
					{
						cout << "Вопрос " << i+1 << endl;
						OutputVopros(DBase[i]);
					}
				}
			    break;
			case 3: 
				int k;
				if (!IsBaseExist(DBase)) {
					break;
				}
				else {
					cout << "В базе " << DBase.size()<< " вопросов\n" << "Какой вопросик меняем?\n" << endl;
					  k = GetNumber(1, DBase.size()) - 1;
					  OutputVopros(DBase[k]);
					  ChangeVopros(DBase[k]);
			    }
				break;

			case 4:
				int number; //Кол-во вариантов
				int q; //Количество вопросов в билете
				int t;//Тип оформления билета
				if (!IsBaseExist(DBase)) {
					break;
				}
				else {
					MyPrints MPs[] = { printTest1, printTest2, printTest3 };
					cout << "Оформить контрольную по типу 1-3" << endl;
					t = GetNumber(1, 3);
					cout << "Какое количество вариантов(1-60)" << endl;
					number = GetNumber(1, 60);
					cout << "Количество вопросов в билете (1-5)" << endl;
					q = GetNumber(1, 5);
					switch (t){
						case 1:
							for (int j = 0; j < number; j++) {
								BiletBase.push_back(CreatBilet(q, DBase));
								MPs[t - 1](BiletBase[j], j, q);
								cout << " " << endl;
							};
							break;
						case 2:
							for (int j = 0; j < number; j++) {
								BiletBase.push_back(CreatBilet(q, DBase));
								MPs[t - 1](BiletBase[j], j, q);
								cout << " " << endl;
							};
							break;
						case 3:
							for (int j = 0; j < number; j++) {
								BiletBase.push_back(CreatBilet(q, DBase));
								MPs[t - 1](BiletBase[j], j, q);
								cout << " " << endl;
							};
							break;
					}
				}
				break;
			case 5:
				if (!IsBaseExist(DBase)) {
					break;
				}
				else {
					cout << "Введите имя файла"<<endl;
					string name;
					cin >> name;
				WriteToFile(DBase, name);
				}
				cout << "Файл cоздан\n" << endl;
				cout << "Для просмотра файла, откройте его в папке\n" << endl;
				break;
			case 6: {
				string name;
				cout << "Из какого файла считать базу?" << endl;
				cin >> name;
				ReadOutFile(DBase, name);
				break;
			}
				
			case 7:
				cout << "1-По сложности \n2-По категориям\n";
				if (GetNumber(1, 2) == 1) {
					Sort(DBase, &Vopros::level);
				}
				else {
					Sort(DBase, &Vopros::category);
				}
				break;

		}
	}
}