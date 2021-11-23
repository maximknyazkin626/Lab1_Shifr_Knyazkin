#include <iostream>
#include "Knyazkin_project.h"

void	printMenu()
{
	cout << "1. Decrypt file\n"
		<< "2. Incrypt file\n"
		<< "0. Exit\n";
}

void	Crypt(int flag, string filename1, string filename2, string& key)
{
	int length = key.length();
	ifstream fin;
	ofstream fout;
	fin.open(filename1, ios::binary);
	fout.open(filename2, ios::binary);
	if (fin.is_open() && fout.is_open())
	{
		int i = 0;
		unsigned char incr;
		while (fin >> noskipws >> incr)
		{
			fout << (unsigned char)(incr + flag * key[i]);
			if (++i == length) i = 0;
		}
	}
}

vector<unsigned char>Read_file(string name_file)
{
	vector<unsigned char>text_symb;

	ifstream fin(name_file, ios::binary);
	if (fin.is_open())
	{
		vector<unsigned char> v((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
		text_symb = v;
		fin.close();
	}
	return text_symb;
}

int	main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	string	code_file, standart_file, decrypt_file, keyword;
	string	filename1, filename2, key;
	vector<unsigned char>code_text;
	vector<unsigned char>standart_text;
	vector<double>indexes_confidence;
	vector<vector<unsigned char>>table;
	map<double, unsigned char>	freq_standart;
	int	key_len;

	while (1)
	{
		printMenu();
		switch (GetCorrectNumber("Choose your action: ", 0, 2))
		{
		case 1:
		{
			while (1)
			{
				cout << "Enter code file: ";
				cin >> code_file;
				cout << "Enter standart file: ";
				cin >> standart_file;
				code_text = Read_file(code_file);//читаем зашифрованный файл
				standart_text = Read_file(standart_file);//читаем эталонный текст 
				indexes_confidence = index_of_confidence(code_text);//находим индекс соответствия зашифрованного текста
				cout << "Index confidence: \n" << indexes_confidence << "\n" << "Enter length of keyword: ";
				cin >> key_len;
				table = Create_table(key_len, code_text);//составляем таблицу частот
				freq_standart = Get_frequency_standart(standart_text);//частота совпадений букв эталонного текста
				keyword = Get_keyword(key_len, table, freq_standart);//получаем ключ
				cout << keyword << endl
					<< "Enter output file: ";
				cin >> decrypt_file;
				Crypt(-1, code_file, decrypt_file, keyword);
				if (!GetCorrectNumber("Change files? (0 - No, 1 - Yes): ", 0, 1))
					break;
			}
			break;
		}
		case 2:
		{
			cout << " Enter orig file: " << endl;
			cin >> filename1;
			cout << " Enter code file: " << endl;
			cin >> filename2;
			cout << " Enter key " << endl;
			cin >> key;
			Crypt(1, filename1, filename2, key);
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Input error!";
		}
		}
	}
}




