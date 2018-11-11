
#include <iostream>
#include <stdio.h>

#define NO_OF_CHARS 256

int zstrlen(const char* str)
{
	register int i = 0;

	while (str[i] != '\0')
		++i;
	return i;
}

void badChar(const char* pat, int m, char badArr[NO_OF_CHARS])
{
	for (int i = 0; i < NO_OF_CHARS; ++i)
		badArr[i] = -1;

	for (int i = 0; i < m; ++i)
	{
		badArr[pat[i] - 'A'] = i;
	}
}

void search(const char* txt, const char* pat)
{
	int m,n;
	n = zstrlen(txt);
	m = zstrlen(pat);
	char badArr[NO_OF_CHARS];

	badChar(pat, m, badArr);

	int s = 0;
	int j;

	while (s<=(n-m))
	{
		j = m - 1;
		while (j >= 0 && pat[j] == txt[s + j])
			--j;

		if (j < 0)
		{
			std::cout << "Pattern Match at " << s << std::endl;
			return;
		}
		else
		{
			if (badArr[txt[s + j] - 'A'] == -1)
			{
				s += m-j;
			}
			else
			{
				int a= j - badArr[txt[s + j] - 'A'];
				if (a > 1)
					s += a;
				else
					s += 1;
			}

		}
	}
}


int main()
{
	char txt[] = "ABAASDFGHJKLGHJKLKJHGFDFGHJIUYTRERTYUIOIHGCVBNMNGFDSDHYJKJHGFGHJKLLKJZXCVBNMAABCD";
	char pat[] = "ABC";
	search(txt, pat);
	return 0;
}
