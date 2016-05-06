#include <new>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define ASIZ 26
#define FRCR 'A'

void initLetterArrays (char *a, char *b) {
	a[0] = FRCR; b[0] = FRCR;
	for (int i=1; i < ASIZ; i++) {
		a[i] = a[i-1] + 1;
		b[i] = a[i];
	}
}

void printLetterArrays (char *a, char *b) {
	cout << endl << endl;
	for (int i=0; i < ASIZ; i++) cout << a[i] << " ";
	cout << endl << endl;
	for (int i=0; i < ASIZ; i++) cout << b[i] << " ";
	cout << endl << endl;
}

void shiftLetterArrayB (char *b, string aa) {
	char temp;
	for (unsigned int i=0; i < aa.length(); i++) {
		temp = b[0];
		for (int j=0; j < (ASIZ-1); j++) b[j] = b[j+1];
		b[(ASIZ-1)] = temp;
	}
}

void revShiftLetterArrayB (char *b, string aa) {
	char temp;
	for (unsigned int i=0; i < aa.length(); i++) {
		temp = b[(ASIZ-1)];
		for (int j=(ASIZ-1); j > 0; j--) b[j] = b[j-1];
		b[0] = temp;
	}
}


string encrypto (char *a, char *b, string aa, string bb, string crypt) {
	ofstream txtout;
	int ind = 0;
	reverse(aa.begin(), aa.end());
	txtout.open("encrypted.txt", ios::out);
	if (txtout.is_open()) {
		txtout << aa << endl;
		for (unsigned int i=0; i < bb.length(); i++) {
			ind = bb.at(i) - FRCR;
			shiftLetterArrayB(b, aa);
			//printLetterArrays(a, b);
			//cout << "B @ " << ind << ": " << a[ind] << endl;
			
				 if (bb.at(i) == '\n')					{crypt += '\n';}//		txtout << '\n'; }
			else if (bb.at(i) == ' ' )					{crypt += ' ';}//		txtout << ' ';}
			else if (bb.at(i) < FRCR || bb.at(i) > 'Z')	{crypt += bb.at(i);}// txtout << bb.at(i);}
			else 										{crypt += b[ind];}//	txtout << b[ind];}
		}
	}
	reverse(crypt.begin(), crypt.end());
	txtout << crypt;
	return crypt;
}

string decrypto (char *a, char *b, string aa, string bb, string crypt) {
	ofstream txtout;
	int ind = 0;
	reverse(bb.begin(), bb.end());
	txtout.open("decrypted.txt", ios::out);
	if (txtout.is_open()) {
		txtout << aa << endl;
		for (unsigned int i=0; i < bb.length(); i++) {
			ind = bb.at(i) - FRCR;
			revShiftLetterArrayB(b, aa);
			//printLetterArrays(a, b);
			//cout << "B @ " << ind << ": " << a[ind] << endl;
			
				 if (bb.at(i) == '\n')					{crypt += '\n';}//		txtout << '\n'; }
			else if (bb.at(i) == ' ' )					{crypt += ' ';}//		txtout << ' ';}
			else if (bb.at(i) < FRCR || bb.at(i) > 'Z')	{crypt += bb.at(i);}//  txtout << bb.at(i);}
			else										{crypt += b[ind];}//	txtout << b[ind];}
		}
	}
	txtout << crypt;
	return crypt;
}

string strInit (string strToInit) {
	for (unsigned int i=0; i < strToInit.length(); i++)
		strToInit.at(i) = toupper(strToInit.at(i));
	return strToInit;
}

//string strInitPTR (string *strToInit) {
//	string s = *strToInit;
//	for (unsigned int i=0; i < s.length(); i++)
//		s.at(i) = toupper(s.at(i));
//	return s;
//}

void menu(int * selection) {
	system("cls");
	cout << "~~~MENU~~~" << endl << endl
		 << "What would you like to do?" << endl
		 << " 1) Encrypt & save" << endl
		 << " 2) Decrypt from file & save" << endl
		 << " 3) Encrypt from file & save" << endl
		 << " 4) Exit" << endl
		 << endl;
	cin >> *selection;
	fflush(stdin);
	cout << endl;

	while (!(*selection >= 1 && *selection <= 4)) {
		cout << "Please only enter 1-4." << endl;
		*selection = 0;
		fflush(stdin);
		cin >> *selection;
		cout << endl;
	}
}


int main () {
	char* abc = new char [ASIZ];
	char* abc2 = new char [ASIZ];
	int* selection = new int;
	string crypt(""), c1("");
	string* c2 = new string;
	ifstream txtin, decIn;
	initLetterArrays(abc, abc2);
	
	do {
		initLetterArrays(abc, abc2);
		menu(selection);
		switch (*selection) {
			case 1:
				system("CLS");
				cout << "Key:\n";
				getline(cin, c1, '\n'); c1 = strInit(c1);
				cout << endl << "Crypto: (endl = ~)\n";
				getline(cin, *c2, '~'); *c2 = strInit(*c2);
				crypt = encrypto(abc, abc2, strInit(c1), strInit(*c2), crypt);
				cout << crypt;
				getchar();
				crypt.assign("");
				c1.assign("");
				*c2 = "";
				break;

			case 2:
				system("CLS");
				txtin.open("encrypted.txt", ios::in);
				if (txtin.is_open()) {
					getline(txtin, c1, '\n');
					reverse(c1.begin(), c1.end());
						getline(txtin, *c2, '~');
						crypt = decrypto(abc, abc2, strInit(c1), strInit(*c2), crypt);
						cout << crypt;
						crypt.assign("");
						c1.assign("");
						*c2 = "";
					txtin.close();
				} else cout << "Error opening file!" << endl;
				getchar();
				break;
			case 3:
				system("CLS");
				decIn.open("decrypted.txt", ios::in);
				if (decIn.is_open()) {
					getline(decIn, c1, '\n');
						getline(decIn, *c2, '~');
						crypt = encrypto(abc, abc2, strInit(c1), strInit(*c2), crypt);
						cout << crypt;
						crypt.assign("");
						c1.assign("");
						*c2 = "";
					decIn.close();
				} else cout << "Error opening file!" << endl;
				getchar();
				break;
			case 4:
				break;
			default:
				cout << "ERROR LOL";
				break;
		}
	} while (*selection != 4);
	
	
	cout << "Thank you for using this program\nPress any key to exit..." << endl;
	getchar();
}
