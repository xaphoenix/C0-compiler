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
#include"tcode.h"

int adsp = -16;
int main()
{
	init_read();
	init_word();
	//test_word();
	getch();
	check_program(adsp);
	//mcode_print();
	tcode_init();
	tcode_output();
	//mcode_print();
	return 0;
}
