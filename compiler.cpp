#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<vector>
#include<bitset>

using namespace std;
#include"global.h"
#include"error.h"
#include"word.h"
#include"mcode.h"
#include"table.h"
#include"grammar.h"

int adsp;
int main()
{
	init_read();
	init_word();
	//test_word();
	getch();
	check_program(adsp);
	mcode_print();
	return 0;
}
