#define INT 0
#define CHAR 1
#define VOID 2

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

int grammar_debug = 1;

const int maxline = 600; // the maximum number of lines this compiler can compile
const int maxcol = 10000; // the maximum nubmer of column one line can contain
const int maxfatal_msg = 10; // the number of the kinds of fatal error 
const int maxcompile_msg = 100; // the number of the kinds of compile error
const int maxruntime_msg = 100; // the number of the kinds of runtime error
const int maxlevel = 400;  // the maximum number of level
const int maxupper = 10000000; // the maximum number of the number size of array
const int maxcode = 1000000;
char ch; // now character
int now_row = 0;  // now line
int now_col = -1;  // now column
int all_row;  // the number of lines in current file
int all_col;  // the number of column in current line
int sym_no;  // the no. of current sym
const int sp = 0x2ffc;
string now_string;  //now string content
string sym;  // now symbol
string content[maxline]; // store all content of file

string fatal_msg[maxfatal_msg];
string compile_msg[maxcompile_msg];
string runtime_msg[maxruntime_msg];

int level;  // now level
int main_flag;
int error_flag;
char file_path[11000]="15061176_test2.txt";
char file_tmp[maxcol + 10];

int if_num;  // if counter
int while_num;  // while counter
int func_num;  // func counter
int switch_num;  // switch counter
int case_num;  // case counter
int default_num;  // default counter
int val_num;  // value counter

map<string, string> key_word;
//symbol
string plusy = "PLUSY";  // +
string minusy = "MINUSY";  // -
string timesy = "TIMESY";  // *
string divsy = "DIVSY";  // /
string lss = "LSS"; // <
string leq = "LEQ"; // <=
string gtr = "GTR";  // >
string geq = "GEQ";  // >=
string neq = "NEQ";  // !=
string eql = "EQL";  // ==
string strsy = "STRSY"; // string
string chsy = "CHSY";  // char const
string constsy = "CONSTSY";  // const
string intsy = "INTSY";  // int
string charsy = "CHARSY";  // char
string becomes = "BECOMES";  // =
string numsy = "NUMSY";  // int const
string lbracket = "LBRACKET";  // [
string rbracket = "RBRACKET";  // ]
string lparent = "LPARENT";  // (
string rparent = "RPARENT";  // )
string lbrace = "LBRACE";  // {
string rbrace = "RBRACE";  // }
string voidsy = "VOIDSY";  // void
string mainsy = "MAINSY";  // main
string ifsy = "IFSY";  // if
string elsesy = "ELSESY";  // else
string whilesy = "WHILESY";  // while
string switchsy = "SWITCHSY";  // switch
string casesy = "CASESY";  // case
string defaultsy = "DEFAULTSY";  // default
string scanfsy = "SCANFSY";  // scanf
string printfsy = "PRINTFSY";  // printf
string returnsy = "RETURNSY";  // return
string semicolon = "SEMICOLON";  // ;
string comma = "COMMA";  // ,
string colon = "COLON";  // :
string ident = "IDENT";  // variable
string ersy = "ERSY";  // error


string num2string(int num)
{
	string s = "";
	while (num) s = (char)(num % 10 + '0') + s, num /= 10;
	if (s.size() == 0) s = "0";
	return s;
}
int string2num(string s)
{
	int res=0;
	int l=s.size();
	for (int i=0;i<l;i++)
	{
		res=res*10+(s[i]-'0');
	}
	return res;
}
char string2char(string s)
{
	return s[0];
}
string change_chars(char *s)
{
	string tmp="";
	int len=strlen(s);
	for (int i = 0; i < len; i++)
		tmp = tmp + s[i];
	return tmp;
}

void init_read()
{
	printf("please input your code location:");
	scanf("%s",file_path);
	FILE* f = fopen(file_path, "r");
	freopen("output.txt","w",stdout);
	for (int i = 0; i < maxline; i++)
	{
		if (fgets(file_tmp, maxcol, f)!=NULL)
		{
			 all_row = i + 1;
			 content[i] = change_chars(file_tmp);
		}
	}
	all_col = content[0].size();
}
