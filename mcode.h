#define FUNC 0
#define PARA 1
#define PUSH 2
#define CALL 3
#define RECALL 4
#define RET 5
#define VAR 6
#define CONST 7
#define ASSIGN 8
#define LOGIC 9
#define GO 10
#define LABEL 11
#define SARRAY 12
#define LARRAY 13
#define PRINT 14
#define SCAN 15

struct mcode
{
	int type; // 0 - func; 1 - para; 2 - push; 3 - call; 4 - recall; 5 - ret; 
			  // 6 - var; 7 - const; 8 - assign; 9 - logic; 10 - go; 11 - label;
			  // 12 - sarray; 13 - larray; 14 - print; 15 - scan;
	string s[5];
	mcode()
	{
		type = 0;
		s[0]=s[1]=s[2]=s[3]=s[4]="";
	}
}code[maxcode];
int mcode_num;
int if_num;  // if counter
int while_num;  // while counter
int func_num;  // func counter
int switch_num;  // switch counter
int case_num;  // case counter
int val_num;  // value counter

map<string, string> label2func;

void mcode_insert(int type, string s0)
{
	if (error_flag) return;
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1)
{
	if (error_flag) return;
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2)
{
	if (error_flag) return;
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2, string s3)
{
	if (error_flag) return;
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	code[mcode_num].s[3] = s3;
	mcode_num++;
}

void mcode_insert(int type, string s0, string s1, string s2, string s3, string s4)
{
	if (error_flag) return;
	code[mcode_num].type = type;
	code[mcode_num].s[0] = s0;
	code[mcode_num].s[1] = s1;
	code[mcode_num].s[2] = s2;
	code[mcode_num].s[3] = s3;
	code[mcode_num].s[4] = s4;
	mcode_num++;
}

string tmp_var()
{
	return "$t" + num2string(val_num++) + "@" + now_func;
}

string if_else()
{
	return "LABEL_if_" + num2string(if_num) + "_else";
}

string if_end()
{
	return "LABEL_if_" + num2string(if_num++) + "_end";
}

string while_begin()
{
	return "LABEL_while_" + num2string(while_num) + "_begin";
}

string while_end()
{
	return "LABEL_while_" + num2string(while_num++) + "_end";
}

string switch_end()
{
	return "LABEL_switch_" + num2string(switch_num++) + "_end";
}

string case_end()
{
	return "LABEL_case_" + num2string(case_num++) + "_end";
}

string func_begin()
{
	return "LABEL_func_" + num2string(func_num++) + "_begin";
}

void mcode_print()
{
	for (int i = 0; i < mcode_num; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (code[i].s[j] == "") break;
			cout<< code[i].s[j] << " ";
		}
		cout<<endl;
	}
}

