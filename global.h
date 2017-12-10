#define INT 0
#define CHAR 1
#define VOID 2


int grammar_debug = 0;

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
string now_string;  //now string content
string now_func;  // now function name
string sym;  // now symbol
string content[maxline]; // store all content of file

string fatal_msg[maxfatal_msg];
string compile_msg[maxcompile_msg];
string runtime_msg[maxruntime_msg];

int level;  // now level
int main_flag;
int error_flag;
char file_path[11000]="test.txt";
char file_tmp[maxcol + 10];

int push_addr = 16;
int func_size = 0;
int str_num;
int tcode_main;

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
	int flag = 0;
	if (num < 0)
	{
		flag = 1;
		num = abs(num);
	}
	while (num) s = (char)(num % 10 + '0') + s, num /= 10;
	if (s.size() == 0) s = "0";
	if (flag) s = "-" + s;
	return s;
}
int string2num(string s)
{
	if (s[0] == '\'')
	{
		return s[1];
	}
	int low = 0;
	int ff = 1;
	if (s[0] == '-') 
	{
		low = 1;
		ff = -1;
	}
	int res=0;
	int l=s.size();
	for (int i = low; i < l; i++)
	{
		res = res * 10 + (s[i] - '0');
	}
	return res * ff;
}
char string2char(string s)
{
	return s[0];
}
string num2char2string(int x)
{
	string tmp = "";
	char y = (char)x;
	return tmp + y;
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
