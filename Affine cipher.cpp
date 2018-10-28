// Affine cipher.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int NOD(int a, int b)
{
	while (b)
	{
		int c = a % b;
		a = b;
		b = c;
	}

	return a;
}


int main()
{
	int x, z;
	//int c = 21;
	//int a = 5;
	//int  b = 13;
	int a, b, c;
	string cipher;
	cout << "1 - Cipher a message" << endl << "2 - Decipher a message " << endl << "3 - End" << endl;
	cin >> x;
	char y[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };


	if (x == 1)
	{
		string path = "test.txt";
		ifstream fin;
		fin.open(path);
		fin >> a;
		fin >> b;
		fin >> c;
		if (NOD(a, 26) != 1)
		{
			cout << "Error";
			return 0;
		}
		else
		{
			cout << "Key a is right" << endl;
		}
		if (b > 0 && b < 25)
		{
			cout << "Key b is right" << endl;
		}
		else
		{
			cout << "Error";
			return 0;
		}
		if (!fin.is_open())
		{
			cout << "Error" << endl;
		}
		else
		{
			//cout << "File is open" << endl;
			string str;
			while (!fin.eof())
			{
				getline(fin, str);
				//cout << str << endl;
			}
			for (int i = 0; i < str.size(); i++)
			{
				for (int j = 0; j < 26; ++j)
				{
					if (str[i] == y[j])
					{
						z = (a*j + b) % 26;

						cipher += y[z];
					}
					else
					{
						cipher += str[i];
					}
				}
			}
			//cout << str << endl << cipher << endl;
		}
		fin.close();

		ofstream fout("test2.txt");
		fout << a << " " << b << " " << c << endl;
		fout << cipher;
		fout.close();
	}

	if (x == 2)
	{
		//cout << "please enter a message to decipher : ";
		//cin.ignore();
		//cin.getline(message, 1000);
		ifstream fin1("test2.txt");
		fin1 >> a;
		fin1 >> b;
		fin1 >> c;
		if (!fin1.is_open())
		{
			cout << "Error";
		}
		else
		{
			//cout << "File is open";
			string str1;
			while (!fin1.eof())
			{
				getline(fin1, str1);
			}
			for (int i = 0; i < str1.size(); i++)
			{
				for (int j = 0; j < 52; ++j)
				{
					if (str1[i] == y[j])
					{
						z = (c*(j - b)) % 26;
						cipher += y[z];
					}
				}

			}
			cout << str1 << endl << cipher << endl;
		}
		
	}
	if (x == 3)
		return 0;

    return 0;
}

