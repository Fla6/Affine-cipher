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


int positive_mod(int i, int n)
{
	return (i % n + n) % n;
}

int main()
{
	int x, z;
	int a, b, c;
	int a1, b1, a2, b2, c1, c2;
	string cipher;
	cout << "1 - Cipher a message" << endl << "2 - Decipher a message " << endl  << "3 - Affine rekur cipher" << endl << "4 - Affine rekur decipher" << endl;
	cin >> x;
	char y[52] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };


	if (x == 1)
	{
		string path = "test1.0.txt";
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
			}
			int flag = 0;
			for (int i = 0; i < str.size(); i++)
			{
				for (int j = 0; j < 52; ++j)
				{
					if (str[i] == y[j])
					{
						z = (a*j + b) % 26;

						cipher += y[z];
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					cipher += str[i];
				flag = 0;
			}
			//cout << str << endl << cipher << endl;
		}
		fin.close();

		ofstream fout("test1.1.txt");
		fout << a << " " << b << " " << c << endl;
		fout << cipher;
		fout.close();
	}

	if (x == 2)
	{
		ifstream fin1("test1.1.txt");
		fin1 >> a;
		fin1 >> b;
		fin1 >> c;
		if (a*c % 26 == 1)
		{
			cout << "Key c is right" << endl;
		}
		else
		{
			cout << "Error";
			return 0;
		}
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
			int flag = 0;
			for (int i = 0; i < str1.size(); i++)
			{
				for (int j = 0; j < 52; ++j)
				{
					if (str1[i] == y[j])
					{
						z = positive_mod((c*(j - b)), 26);
						cipher += y[z];
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					cipher += str1[i];
				flag = 0;
			}
			//cout << str1 << endl << cipher << endl;
		}
		fin1.close();
		ofstream fout1("test1.3.txt");
		fout1 << cipher;
		fout1.close();
	}
	if (x == 3)
	{
		ifstream fin2("test2.0.txt");
		fin2 >> a1 >> b1 >> c1;
		fin2 >> a2 >> b2 >> c2;
		if (!fin2.is_open())
		{
			cout << "Error";
		}
		else
		{
			string str2;
			while (!fin2.eof())
			{
				getline(fin2, str2);
			}
			a[0] = a1;
			a[1] = a2;
			b[0] = b1;
			b[1] = b2;
			for (int s = 2; s < 26; s++)
			{
				a[s] = a[s - 2] * a[s - 1];
				b[s] = b[s - 2] * b[s - 1];
			}
			for (int i = 0; i < str2.size(); i++)
			{
				for (int j = 0; j < 52; ++j)
				{
					if (str2[i] == y[j])
					{
						z = a[i] * j + b[i];
						cipher += y[z];

					}
				}
			}
		}
	}

    return 0;
}

