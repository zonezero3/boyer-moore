
#include <iostream>
#include <random>
#include <string>

#define MAX_CHAR_NUM 256
#define TEXT_LENGTH 1000000
#define PATTERN_LENGTH 10

//extern std::string random_string(std::string::size_type length);

int badChar[MAX_CHAR_NUM];
char text[TEXT_LENGTH];
char pattern[PATTERN_LENGTH];

int max(int a, int b) {return a > b ? a: b;}
std::string strText;
std::string strPat;


void zstrcpy(char *a, const char *b)
{
	int i = 0;
	while (b[i] != '\0')
	{
		a[i] = b[i];
		++i;
	}
	a[i] = '\0';
}

int zstrlen(const char* s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		++i;
	}
	return i;

}
void random_string(std::string::size_type txtlength, std::string::size_type patlength)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg1{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	thread_local static std::mt19937 rg2{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<int> distribution(0, txtlength - patlength - 1);

	std::string s;

	s.reserve(txtlength);

	while (txtlength--)
		s += chrs[pick(rg1)];

	zstrcpy(text, s.c_str());

	int patStart = distribution(rg2);

	for (int i = 0; i < patlength; ++i)
	{
		pattern[i] = text[patStart + i];
	}

}



void badCharPre(char *pattern, int patLength)
{
	for (register int i = 0; i < MAX_CHAR_NUM; ++i)
	{
		badChar[i] = -1;
	}

	for (register int i = 0; i < patLength; ++i)
	{
		badChar[pattern[i]] = i;
	}
}

void badCharRule(char *pattern, int patLength, char* text, int txtLength)
{
	int shift = 0;
	int j;
	while (shift <= txtLength-patLength)
	{
		j = patLength-1;
		while (j >= 0 && text[shift + j] == pattern[j])
			--j;

		if (j < 0)
		{
			std::cout << "MATCH AT " << shift << std::endl;
			shift += (shift + patLength <txtLength ? patLength - badChar[text[patLength]]:1);

		}
		else
		{
			shift += max(1, j - badChar[text[shift + j]]);
		}

	}
}

void main()
{
	random_string(TEXT_LENGTH,PATTERN_LENGTH);

	//zstrcpy(text, "jlkjasdfkljasafasdfdasfasfflkjsflABCfdsfasfsdfasd");
	//zstrcpy(pattern,"ABC");

	badCharPre(pattern, zstrlen(pattern));
	badCharRule(pattern, zstrlen(pattern), text, zstrlen(text));

}
