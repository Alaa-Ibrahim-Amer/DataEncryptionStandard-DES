#include <iostream>
#include<math.h>
#include<string>
#include<vector>
using namespace std;

#ifdef __GNUC__
# define __rdtsc __builtin_ia32_rdtsc
#else
# include<intrin.h>
#endif

typedef unsigned long long u64;


string keys[16];
u64 keys_64[16];
u64 Left_p; //left plane text
u64 Right_p; //right plane text



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

//for the key its slow function as they use strings
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
		keys_64[r] = stoull(keys[r], nullptr, 2);
		
	}


	
	
	
}

//for decryption
void key_generate_(string key)
{
	string test;
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
	2,2,2,1 };


	key = permution(key, 56, Parity_drop);

	left_key = key.substr(0, 28);
	right_key = key.substr(28, 28);

	string keys_[16];
	

	for (int r = 0;r < 16;r++)
	{
		left_key = shifting(left_key, shift_by[r]);
		right_key = shifting(right_key, shift_by[r]);
		keys[r] = left_key + right_key;

		keys[r] = permution(keys[r], 48, Key_compression);
		keys_ [r]= keys[r];
		
	}
	
	for (int r = 0;r < 16;r++)
	{
		
		keys[r] = keys_[15 - r];
		keys_64[r] = stoull(keys[r], nullptr, 2);

	}




}


u64 permution(u64 in, int n, int a[],int m)
{
	u64 out = 0;
	for (int i = 0;i < n;++i)

		out |= (in >> (m - a[n - 1 - i]) & 1) << i;
	return out;
}

u64 ED_box(u64 right , u64 key) {
	int ED [48] = { 
	32, 1, 2, 3, 4, 5, 4, 5,
	6, 7, 8, 9, 8, 9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32, 1 };

	right = permution(right,48,ED,32);
	printf("ed_box: %016llX\n", right);
	right = key ^ right;
	//printf("xor: %016llX\n", right);
	
	return right;
}
u64 D_box(u64 a) {
	int per[32] = { 16, 7, 20, 21,
				   29, 12, 28, 17,
				   1, 15, 23, 26,
				   5, 18, 31, 10,
				   2, 8, 24, 14,
				   32, 27, 3, 9,
				   19, 13, 30, 6,
				   22, 11, 4, 25 };

	a = permution(a,32,per,32);
	//printf("d-box: %016llX\n", a);
	return a;
}




u64 S_box(u64 a)
{
	int s [ ]= { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 ,
						 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 ,

						 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 ,
					 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 ,
						2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 ,
						 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 ,
						 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 ,
						 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };
	u64 val = 0;
	int* box ;
	for (int i = 0; i < 8; i++) {
		
		box = s + (i * 64);
		u64 idx = a >> (7 - i) * 6 & 0x3F;//get the index
		
		idx = idx >> 1 & 15 | (idx & 1) << 4 | idx & 0x20;
		val |=(u64) box[idx ]<< (7 - i) * 4;
		
	}
	
	return val;
}
//right_p is used
void Round(u64 key)
{
	u64 test;
	test = ED_box(Right_p,key);
	//printf("ed_box: %016llX\n", test);
	
	test = S_box(test);

	test = D_box (test);

	Left_p = test ^ Left_p;

}

u64 encrypt(u64 key , u64 text)
{

	//intial permutation
	text = permution(text, 64, intialper,64);
	u64 x = text;




	Left_p = (text >> 32) & 0xffffffff;
	Right_p= text & 0xffffffff;
	
	for (int i = 0;i < 16;i++)
	{
		

		Round(keys_64[i]);
		u64 left = Left_p;
		u64 right = Right_p;

		if (i != 15)
		{
			Right_p = left;
			Left_p = right;
		}
	}
	
	//text = Left_p + Right_p;
	text =( Left_p << 32) | Right_p;

	text = permution(text, 64, final_perm,64);
	return text;
}


int main()//int argc, char** argv)
{
//if (argc == 4)
	//{
	string type;
	string key1, planetext1;
	u64 key, planetext;
	cin >> type;
	cin >> planetext1 ;
	cin >>key1;
	
		
		key1 = hexa_to_binary(key1); //for the key generation function
		

		//decimal output
		planetext = stoull(planetext1,nullptr,16);
		key = stoull(key1, nullptr, 2);
		

		

		if (type == "encrypt" || type == "Encrypt")
		{
			key_generate(key1);
			

			long long t1 = __rdtsc();
			
			planetext = encrypt(key, planetext);
			
			long long t2 = __rdtsc();

			printf("cipher: %016llX\n", planetext);
			
			printf("Cycles: %lld\n", t2 - t1);
		
		}
		else if (type == "decrypt" || type == "Decrypt")
		{

			key_generate_(key1);

		
			long long t1 = __rdtsc();

			planetext = encrypt(key, planetext);

			long long t2 = __rdtsc();
			
			printf("plain: %016llX\n", planetext);
			printf("Cycles: %lld\n", t2 - t1);
		

		}
		else cout << "Invalid operation";



		return 0;
	
}