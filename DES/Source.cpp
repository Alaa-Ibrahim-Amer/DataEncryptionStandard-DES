#include <iostream>
#include<math.h>
#include<string>
using namespace std;
string keys[16];
string LPT[16]; //left plane text
string RPT[16]; //right plane text



int intialper[64]{
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7};

int final_perm[64] = 
{40, 8, 48, 16, 56, 24, 64, 32,
 39, 7, 47, 15, 55, 23, 63, 31,
 38, 6, 46, 14, 54, 22, 62, 30,
 37, 5, 45, 13, 53, 21, 61, 29,
 36, 4, 44, 12, 52, 20, 60, 28,
 35, 3, 43, 11, 51, 19, 59, 27,
 34, 2, 42, 10, 50, 18, 58, 26,
 33, 1, 41, 9, 49, 17, 57, 25 };


string hexa_to_binary(string in)
{
	string out;
	for (int i = 0;i < in.length();i++)
	{
		if (in[i] == 'f' || in[i] == 'F')
			out += "1111";
		else if (in[i] == 'e' || in[i] == 'E')
			out += "1110";
		else if (in[i] == 'd' || in[i] == 'D')
			out += "1101";
		else if (in[i] == 'c' || in[i] == 'C')
			out += "1100";
		else if (in[i] == 'b' || in[i] == 'B')
			out += "1011";
		else if (in[i] == 'a' || in[i] == 'A')
			out += "1010";
		else if (in[i] == '9')
			out += "1001";
		else if (in[i] == '8')
			out += "1000";
		else if (in[i] == '7')
			out += "0111";
		else if (in[i] == '6')
			out += "0110";
		else if (in[i] == '5')
			out += "0101";
		else if (in[i] == '4')
			out += "0100";
		else if (in[i] == '3')
			out += "0011";
		else if (in[i] == '2')
			out += "0010";
		else if (in[i] == '1')
			out += "0001";
		else if (in[i] == '0')
			out += "0000";

	}

	return out;
}

string binary_to_hexa(string in)
{
	string out;
	int n = in.length();
	for (int i = 0;i < n;i+=4)
	{
		if (in.substr(i, 4) == "1111")
			out += "F";
		else if (in.substr(i, 4) == "1110")
			out += "E";
		else if (in.substr(i, 4) == "1101")
			out += "D";
		else if (in.substr(i, 4) == "1100")
			out += "C";
		else if (in.substr(i, 4) == "1011")
			out += "B";
		else if (in.substr(i, 4) == "1010")
			out += "A";
		else if (in.substr(i, 4) == "1001")
			out += "9";
		else if (in.substr(i, 4) == "1000")
			out += "8";
		else if (in.substr(i, 4) == "0111")
			out += "7";
		else if (in.substr(i, 4) == "0110")
			out += "6";
		else if (in.substr(i, 4) == "0101")
			out += "5";
		else if (in.substr(i, 4) == "0100")
			out += "4";
		else if (in.substr(i, 4) == "0011")
			out += "3";
		else if (in.substr(i, 4) == "0010")
			out += "2";
		else if (in.substr(i, 4) == "0001")
			out += "1";
		else if (in.substr(i, 4) == "0000")
			out += "0";
		else break;


	}

	return out;
}

string permution(string text, int n, int a[])
{
	string test = text;
	text = "";

	for (int j = 0;j < n;j++)
	{
		text += test[a[j] - 1];
	}
	return text;

}

string shifting(string key , int shiftBy)
{
	string test = "";
	for (int i = 0; i < shiftBy;i++)
	{
		for (int j = 1; j < 28;j++)
		{
			test += key[j];
		}
		test += key[0];
		key = test;
		test = "";
	}
	return key;
}

void key_generate(string key)
{
	string test ;
	string left_key;
	string right_key;

	int Parity_drop[56]{
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4 };

	int Key_compression[48]{
	 14, 17, 11, 24, 1, 5,
	 3, 28, 15, 6, 21, 10,					
	 23, 19, 12, 4, 26, 8,					
	 16, 7, 27, 20, 13, 2,					
	 41, 52, 31, 37, 47, 55,					
	 30, 40, 51, 45, 33, 48,
	 44, 49, 39, 56, 34, 53,					
	 46, 42, 50, 36, 29, 32						 				
	};

	int shift_by[16]{
	1,1,2,2,
	2,2,2,2,
	1,2,2,2,
	2,2,2,1	};


	key = permution(key,56,Parity_drop);
	
	left_key = key.substr(0, 28);
	right_key = key.substr(28, 28);

	

	for (int r = 0;r < 16;r++)
	{
		left_key = shifting(left_key, shift_by[r]);
		right_key = shifting(right_key, shift_by[r]);
		keys[r] = left_key + right_key;
		
		keys[r] = permution(keys[r], 48, Key_compression);

		//keys[r] = binary_to_hexa(keys[r]);
		//cout << keys[r]<<endl;
	}


	
	
	
}



string Round(string key, string text)
{
	string round_text;




	return round_text;
}

void encrypt(string key , string text)
{
	string x = text;
	for (int i = 0;i < 16;i++)
	{
		x = Round(keys[i],x);
	}
}
void decrypt(string key, string text)
{

}


int main()
{
	string type, key, planetext;

	cin >> type;
	cin >> key;
	cin >> planetext;

	key = hexa_to_binary(key);
	planetext = hexa_to_binary(planetext);

	if (type == "encrypt" || type == "Encrypt")
	{
		key_generate(key);
		encrypt(key,planetext);
		//print output
		planetext = binary_to_hexa(planetext);
		cout << "cipher: " + planetext << endl;
	}
	else if (type == "decrypt" || type == "Decrypt")
	{
		decrypt(key, planetext);
		//print output
		planetext = binary_to_hexa(planetext);
		cout << "plain: " + planetext << endl;

	}
	else cout << "Invalid operation";






}