struct mcode
{
	int type; // 0 - func; 1 - para; 2 - push; 3 - call; 4 - recall; 5 - ret; 
			  // 6 - var; 7 - const; 8 - assign; 9 - logic; 10 - go; 11 - label;
			  // 12 - sarray; 13 - larray; 14 - print; 15 - scan;
	string s[5];
}code[maxcode];
int mcode_num;

void mcode_insert(int type, string s0)
{
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1)
{
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2)
{
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2, string s3)
{
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	code[mcode_num].s[3] = s3;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2, string s3, string s4)
{
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	code[mcode_num].s[3] = s3;
	code[mcode_num].s[4] = s4;
	mcode_num++;
}

