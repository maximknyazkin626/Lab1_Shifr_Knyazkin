#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printmenu() {
    cout << "1.Encrypt " << endl;
    cout << "2.Decrypt" << endl;
    cout << "0.Exit" << endl;
}

void crypt(int koef) {
    int k = 0; /// отвечает за порядок символов в ключе
    unsigned char ch, key, x;  
    ifstream filein;
    ofstream fileout;
    string filename_1, filename_2, keyword;
    cout << "Enter the filename\n";
    cin >> filename_1;
    cout << "Enter the keyword\n";
    cin >> keyword;
    cout << "Enter the new filename\n";
    cin >> filename_2;
    filein.open(filename_1, ios::binary);
    fileout.open(filename_2, ios::binary);
    if (filein.is_open())
        while (true)
        {
            ch = filein.get();
            if (filein.eof()) break; /// если кончились символы в тексте
            key = keyword[k];
            k++;
            if (k == keyword.size()) k = 0;
            x = ch + koef * key;
            fileout << x;
        }
    filein.close();
    fileout.close();
}

int main()
{
    int choice;
    do
    {
        printmenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            crypt(1);
            break;
        }
        case 2: {
            crypt(-1);
            break;
        }
              return 0;
        }
        if (choice != 0)
            system("pause");
    } while (choice != 0);
    return 0;
}
