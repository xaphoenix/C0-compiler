void getch()  // get next character, update ch and now_string
{
	now_col++;
	while(now_col == all_col && now_row < all_row)
	{
		now_row++;
		now_col = 0;
		all_col = content[now_row].size();
	}
	if (now_row >= all_row)
	{
		//print_compile_error(0);
		//exit(0);
	}
	ch = content[now_row][now_col];
}

char lower(char x)
{
	if (x == '_') return x;
	if (x <= 'Z' && x >= 'A') return x - 'A' + 'a';
	return x;
}

bool isdigit(char x)
{
	if (x >= '0' && x <= '9') return 1;
	return 0;
}
bool isalpha(char x)
{
	if (x == '_') return 1;
	if (x >= 'a' && x <= 'z') return 1;
	if (x >= 'A' && x <= 'Z') return 1;
	return 0;
}
bool ischar(char x)
{
	if (x == '+') return 1;
	if (x == '-') return 1;
	if (x == '*') return 1;
	if (x == '/') return 1;
	if (isalpha(x)) return 1;
	if (isdigit(x)) return 1;
	return 0;
}
bool islegal(char x)
{
	if (x == 32 || x == 33) return 1;
	if (x >= 35 && x <= 126) return 1;
	return 0;
}
bool isblank(char x)
{
	if (x == ' ' || x == '\t' || x == '\n') return 1;
	return 0;
}
void getsym()
{
	sym_no++;
	while (isblank(ch)) getch();
	sym = ersy;
	switch (ch)
	{
		case '+' :
			now_string = "+";
			sym = plusy;
			getch();
			break;
		case '-' :
			now_string = "-";
			sym = minusy;
			getch();
			break;
		case '*' :
			now_string = "*";
			sym = timesy;
			getch();
			break;
		case '/' :
			now_string = "/";
			sym = divsy;
			getch();
			break;
		case '<' :
			getch();
			if (ch == '=')
			{
				now_string = "<=";
				sym = leq;
				getch();
				break;
			}
			else
			{
				now_string = "<";
				sym = lss;
				break;
			}
		case '>' :
			getch();
			if (ch == '=')
			{
				now_string = ">=";
				sym = geq;
				getch();
				break;
			}
			else
			{
				now_string = ">";
				sym = gtr;
				break;
			}
		case '!':
			getch();
			if (ch == '=')
			{
				now_string = "!=";
				sym = neq;
				getch();
				break;
			}
			else print_compile_error(6);
			break;
		case '=':
			getch();
			if (ch == '=')
			{
				now_string = "==";
				sym = eql;
				getch();
				break;
			}
			else
			{
				now_string = "=";
				sym = becomes;
				break;
			}
			break;
		case ',':
			now_string = ",";
			sym = comma;
			getch();
			break;
		case ';':
			now_string =";";
			sym = semicolon;
			getch();
			break;
		case ':':
			now_string =":";
			sym = colon;
			getch();
			break;
		case '[':
			now_string = "[";
			sym = lbracket;
			getch();
			break;
		case ']':
			now_string = "]";
			sym = rbracket;
			getch();
			break;
		case '(':
			now_string = "(";
			sym = lparent;
			getch();
			break;
		case ')':
			now_string = ")";
			sym = rparent;
			getch();
			break;
		case '{':
			now_string = "{";
			sym = lbrace;
			getch();
			break;
		case '}':
			now_string = "}";
			sym = rbrace;
			getch();
			break;
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			ch = lower(ch);
			now_string = ch;
			getch();
			while (isalpha(ch) || isdigit(ch)) 
			{
				ch = lower(ch);
				now_string = now_string + ch;
				getch();
			}
			if (key_word.count(now_string)) sym = key_word[now_string];
			else sym = ident;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			now_string = ch;
			getch();
			while (isdigit(ch)) now_string = now_string + ch, getch();
			sym = numsy;
			break;
		case '\'':
			getch();
			sym = chsy;
			if (ischar(ch))
			{
				char last = ch;
				getch();
				now_string = last;
				if (ch == '\'') getch();
				else now_string = last, print_compile_error(2);
			}
			else
			{
				now_string = "_";
				print_compile_error(1);
				char last = ch;
				getch();
				if (ch == '\'') getch();
				else now_string = last, print_compile_error(2);
			}
			break;
			
		case '\"':
			getch();
			sym = strsy;
			now_string = "";
			while (islegal(ch) && ch != '\"') now_string = now_string + ch, getch();
			if (ch != '\"') print_compile_error(3);
			getch();
			break;
				
		default:
			//print_compile_error(6);
			getch();
			break;
	}
}

void init_word()
{
	key_word["int"] = intsy;
	key_word["const"] = constsy;
	key_word["char"] = charsy;
	key_word["void"] = voidsy;
	key_word["main"] = mainsy;
	key_word["if"] = ifsy;
	key_word["else"] = elsesy;
	key_word["while"] = whilesy;
	key_word["switch"] = switchsy;
	key_word["case"] = casesy;
	key_word["default"] = defaultsy;
	key_word["scanf"] = scanfsy;
	key_word["printf"] = printfsy;
	key_word["return"] = returnsy;
}
	
void test_word()
{
	getch();
	while (1) getsym(),cout<<sym_no<<" "<<sym<<" "<<now_string<<endl;
}
void skip(string key)
{
	while (sym != key) getsym();
}
void skip(string key1, string key2)
{
	while (sym != key1 && sym != key2) getsym();
}

