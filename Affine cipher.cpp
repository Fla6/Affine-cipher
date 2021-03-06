#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;


void extended_euclid(int a, int b, int *x, int *y, int *d)

/* calculates a * *x + b * *y = gcd(a, b) = *d */

{
	int q, r, x1, x2, y1, y2;
	if (b == 0)
	{
		*d = a, *x = 1, *y = 0;
		return;
	}
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0)
	{
		q = a / b, r = a - q * b;
		*x = x2 - q * x1, *y = y2 - q * y1;
		a = b, b = r;
		x2 = x1, x1 = *x, y2 = y1, y1 = *y;
	}
	*d = a, *x = x2, *y = y2;
}


int inverse(int a, int n)

/* computes the inverse of a modulo n */

{
	int d, x, y;
	extended_euclid(a, n, &x, &y, &d);
	if (d == 1) return x;
	return 0;
}



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

int alphabet = 52;

int main()
{
	int x, z;
	int a, b;
	int a1, b1, a2, b2;
	string cipher;
	cout << "1 - Affine encryption" << endl << "2 - Affine decryption" << endl  << "3 - Affine rekur encryption" << endl << "4 - Affine rekur decryption" << endl;
	cin >> x;
	char y[52] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

	if (x == 1)
	{
		ofstream fout("test1.1.txt");
		string path = "test1.0.txt";
		ifstream fin;
		fin.open(path);
		fin >> a;
		fin >> b;
		if (NOD(a, alphabet) != 1)
		{
			cout << "Error";
			return 0;
		}
		else
		{
			cout << "Key a is right" << endl;
		}
		if (b > 0 && b < alphabet - 1)
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
			cout << "File is not found!" << endl;
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
				for (int j = 0; j < alphabet; ++j)
				{
					if (str[i] == y[j])
					{
						z = positive_mod((a*j + b), alphabet);

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
		fout << a << " " << b;
		fout << cipher;
		fout.close();
	}

	if (x == 2)
	{
		ifstream fin1("test1.1.txt");
		fin1 >> a;
		fin1 >> b;
		if (!fin1.is_open())
		{
			cout << "File is not found!";
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
			int c = inverse(a, alphabet);
			if (a*c % alphabet == 1)
			{
				cout << "Key c is right" << endl;
			}
			else
			{
				cout << "Error, Key s is not right";
				return 0;
			}
			for (int i = 0; i < str1.size(); i++)
			{
				for (int j = 0; j < alphabet; ++j)
				{
					if (str1[i] == y[j])
					{
						z = positive_mod((c*(j - b)), alphabet);
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
		string path = "test2.0.txt";
		ifstream fin2;
		fin2.open(path);
		fin2 >> a1;
		fin2 >> b1;
		fin2 >> a2;
		fin2 >> b2;
		if (!fin2.is_open())
		{
			cout << "File is not found!";
		}
		else
		{
			string str2;
			int flag = 0;
			while (!fin2.eof())
			{
				getline(fin2, str2);
			}
			int arr[255];
			int brr[255];
			arr[0] = a1;
			arr[1] = a2;
			brr[0] = b1;
			brr[1] = b2;
			int clk = 0;
			for (int i = 0; i < str2.size(); i++)
			{
				for (int j = 0; j < alphabet; ++j)
				{
					if (str2[i] == y[j])
					{
						if (clk >= 2)
						{
							arr[clk] = positive_mod((arr[clk - 1] * arr[clk - 2]), alphabet);
							brr[clk] = positive_mod((brr[clk - 1] + brr[clk - 2]), alphabet);
						}
						z = positive_mod((arr[clk] * j + brr[clk]), alphabet);
						cipher += y[z];
						flag = 1;
						clk++;
						break;
					}
				}
				if (flag == 0)
					cipher += str2[i];
				flag = 0;
			}
			//cout << str2 << endl << cipher << endl;
		}
		fin2.close();
		ofstream fout2("test2.1.txt");
		fout2 << a1 << " " << b1 << endl << a2 << " " << b2 << endl << cipher << endl;
		//fout2 << "\n" << cipher << endl;
		fout2.close();
	}

	if (x == 4)
	{
		ifstream fin2("test2.1.txt");
		ofstream fout2("test2.3333.txt");
		fin2 >> a1 >> b1;
		fin2 >> a2 >> b2;
		if (!fin2.is_open())
		{
			cout << "File is not found!";
		}
		else
		{
			string str2;
			int flag = 0;
			while (!fin2.eof())
			{
				getline(fin2, str2);
			}
			int arr[255];
			int brr[255];
			int crr[255];

			crr[0] = inverse(a1, alphabet);
			crr[1] = inverse(a2, alphabet);
			arr[0] = inverse(a1, alphabet), alphabet;
			arr[1] = inverse(a2, alphabet), alphabet;
			brr[0] = b1;
			brr[1] = b2;
			//fout2 << a1 << " " << b1 << " " << endl;
			//fout2 << a2 << " " << b2 << " ";
			int clk = 0;
			for (int i = 0; i < str2.size(); i++)
			{
				for (int j = 0; j < alphabet; ++j)
				{
					if (str2[i] == y[j])
					{
						if (clk >= 2)
						{
							arr[clk] = positive_mod((arr[clk - 1] * arr[clk - 2]), alphabet);
							//cout << clk << " arr " << arr[clk - 1] << " * " << arr[clk - 2] << " = " << arr[clk] << endl;
							brr[clk] = positive_mod((brr[clk - 1] + brr[clk - 2]), alphabet);
							//cout << clk << " brr " << brr[clk - 1] << " + " << brr[clk - 2] << " = " << brr[clk] << endl;
							crr[clk] = inverse(arr[clk], alphabet);
						}
						z = positive_mod(arr[clk] * (j - brr[clk]), alphabet);
						//cout << ">>>" << z << endl;
						cipher += y[z];
						flag = 1;
						//cout << ">>>" << z << "   clk=" << clk << endl;
						clk++;
						break;
					}
				}
				if (flag == 0) {
					cipher += str2[i];
				}
				flag = 0;
				//cout << ">>>" << cipher << endl;
			}
			//cout << str2 << endl << cipher << endl;
		}
		fin2.close();
		fout2 << cipher;
		fout2.close();
	}

    return 0;
}

