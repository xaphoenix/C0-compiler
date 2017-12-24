string sw = "sw";
string lw = "lw";
string addi = "addi";
string jal = "jal";
string li = "li";
string add = "add";
string sub = "sub";
string mflo = "mflo";
string mult = "mult";
string divs = "div";
string xors = "xor";
string sltiu = "sltiu";
string j = "j";
string bne = "bne";
string la = "la";
string moves = "move";
string jr = "jr";
string slt = "slt";
string slti = "slti";
string syscall = "syscall";
string beq = "beq";

string sp = "$sp";
string ra = "$ra";
string t0 = "$t0";
string t1 = "$t1";
string t2 = "$t2";
string t3 = "$t3";
string t4 = "$t4";
string t5 = "$t5";
string t6 = "$t6";
string t7 = "$t7";
string a0 = "$a0";
string v0 = "$v0";

int start_flag = 0;



void toutput(string s1, int flag = 1)
{
	if (flag) cout << "\t";
	cout << s1 << endl;
}

void toutput(string s1, string s2, int flag = 1)
{
	if (flag) cout << "\t";
	cout << s1 << "\t" << s2 << endl;
}

void toutput(string s1, string s2, string s3, int flag = 1)
{
	if (flag) cout << "\t";
	cout << s1 << "\t" << s2 << ", " << s3 << endl;
}

void toutput(string s1, string s2, string s3, string s4, int flag = 1)
{
	if (flag) cout << "\t";
	cout << s1 << "\t" << s2 << ", " << s3 << ", " << s4 <<endl;
}

int check_at(string s)
{
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '@') flag = 1;
	return flag;
}
int check_lbrace(string s)
{
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '[') flag = 1;
	return flag;
}

map<string, string> str_addr;

string cut_func(string s)
{
	string tmp = "";
	for (int i = 11 ; i < s.size() - 7; i++)
		tmp = tmp + s[i];
	return tmp;
}

string cut_array1(string s)
{
	string tmp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '[') break;
		tmp = tmp + s[i];
	}
	return tmp;
}

string cut_array2(string s)
{
	string tmp = "";
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ']') break;
		if (flag) tmp = tmp + s[i];
		if (s[i] == '[') flag = 1;
	}
	return tmp;
}

string cut_array3(string s)
{
	string tmp = "";
	int flag = 0;
	for (int i = 0; i < s.size();i++)
	{
		if (flag) tmp = tmp + s[i];
		if (s[i] == ']') flag = 1;
	}
	return tmp;
}

string cut_string1(string s)
{
	string tmp = "";
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '@') break;
		else tmp = tmp + s[i];
	return tmp;
}

string cut_string2(string s)
{
	string tmp = "";
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '#') break;
		if (flag) tmp = tmp + s[i];
		if (s[i] == '@') flag = 1;
	}
	return tmp;
}

string cut_string3(string s)
{
	string tmp = "";
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '*') break;
		if (flag) tmp = tmp + s[i];
		if (s[i] == '#') flag = 1;
	}
	return tmp;
}

string cut_string4(string s)
{
	string tmp = "";
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (flag) tmp = tmp +s[i];
		if (s[i] == '*') flag = 1;
	}
	return tmp;
}

void tcode_init()
{
	toutput(".data", 0);
	for (int i = 0; i < mcode_num; i++)
	{
		mcode tmp = code[i];
		if (tmp.s[0][0] == '$')
		{
			string tmp1 = cut_string1(tmp.s[0]);
			string tmp2 = cut_string2(tmp.s[0]);
			insert_tmp_var(tmp2, tmp1);
		}
		if (tmp.s[1][0] == '\"')
		{
			toutput("str_" + num2string(str_num) + ": .asciiz " + tmp.s[1]);
			code[i].s[1] = "str_" + num2string(str_num);
			str_num++;
		}
	}
	for (int i = 0; i < mcode_num; i++)
	{
		for (int j = 0; j < 5; j++)
			if (code[i].s[j] != "")
			{
				if (code[i].s[j][0] == '$')
				{
					string tmp1 = cut_string1(code[i].s[j]);
					code[i].s[j] = tmp1 + "@1#" + tmp_addr[tmp1];
				}
				if (check_lbrace(code[i].s[j]))
				{
					string tmp1 = cut_array1(code[i].s[j]);
					string tmp2 = cut_array2(code[i].s[j]);
					string tmp2s = cut_string1(tmp2);
					string tmp3 = cut_array3(code[i].s[j]);
					if (tmp2[0] == '$')
					{
						code[i].s[j] = tmp1 + "[" + tmp2s + "@1#" + tmp_addr[tmp2s] + "]" + tmp3;
					}
				}
			}
	}
	toutput(".text", 0);
	toutput(li, sp, "0x7ffffffc");
	toutput(li, t0, num2string(func_size));
	toutput(sub, sp, sp, t0);
}

string func_label(string s)
{
	return "LABEL_func_" + num2string(funcTable[0][s].num) + "_begin";
}


void get_lv(string s, int lv)
{
	toutput(addi, t7, sp, num2string(func_size));
	int addr = -lv * 4;
	toutput(lw, s, num2string(addr) + "(" + t7 +")");
}

void get_reg(string t, string s)
{
	if (s[0] >= '0' && s[0] <= '9' || s[0] == '-')
	{
		toutput(li, t, s);
		return;
	}
	if (s[0] == '\'')
	{
		toutput(li, t, num2string((int)s[1]));
		return;
	}
	string tmp1 = cut_string1(s);
	string tmp2 = cut_string2(s);
	string tmp3 = cut_string3(s);
	int lv = string2num(tmp2);
	get_lv(t7, lv);
	toutput(lw, t, tmp3 + "(" + t7 + ")");
}
void tcode_print(mcode t)
{
	switch (t.type)
	{
		case FUNC:
		{
			break;
		}
		case PARA:
		{
			break;
		}
		case PUSH:
		{
			string x = t.s[1];
			get_reg(t0, x);
			toutput(sw, t0, "-" + num2string(push_addr) + "(" + sp + ")");
			push_addr += 4;
			break;
		}
		case CALL:
		{
			string x = t.s[1];
			string func = func_label(x);
			toutput(li, t0, "0x7ffffffc");
			toutput(sw, t0, "0(" + sp + ")");
			toutput(sw, sp, "-4(" + sp + ")");
			toutput(li, t0, num2string(funcTable[0][x].size));
			toutput(sub, sp, sp, t0);
			toutput(jal, func);
			push_addr = 16;
			break;
		}
		case RECALL:
		{
			string x = t.s[0];
			int lv = string2num(cut_string2(x));
			int addr = string2num(cut_string3(x));
			toutput(lw, t0, "-12(" + sp + ")");
			get_lv(t1, lv);
			toutput(sw, t0, num2string(addr) + "(" + t1 + ")");
			break;
		}
		case RET:
		{
			if (tcode_main)
			{
				toutput(li, v0, "10");
				toutput(syscall);
				break;
			}
			string x = t.s[1];
			if (x != "")
			{
				get_reg(t0, x);
				toutput(addi, t1, sp, num2string(func_size));
				toutput(sw, t0, "-12(" + t1 + ")");
			}
			toutput(addi, sp, sp, num2string(func_size));
			toutput(lw, ra, "-8(" + sp + ")");
			toutput(jr, ra);
			break;
		}
		case VAR:
		{
			break;
		}
		case CONST:
		{
			string x = t.s[2];
			int addr = string2num(cut_string3(x));
			int val = string2num(t.s[4]);
			toutput(li, t0, num2string(val));
			toutput(addi, t1, sp, num2string(func_size));
			toutput(sw, t0, num2string(addr) + "(" + t1 + ")");
			break;
		}
		case ASSIGN:
		{
			string x = t.s[0];
			int lv = string2num(cut_string2(x));
			int addr = string2num(cut_string3(x));
			get_reg(t0, t.s[2]);
			if (t.s[3] != "")
			{
				get_reg(t1, t.s[4]);
			}
			if (t.s[3] == "+") toutput(add, t2, t0, t1);
			else if (t.s[3] == "-") toutput(sub, t2, t0, t1);
			else if (t.s[3] == "*")
			{
				toutput(mult, t0, t1);
				toutput(mflo, t2);
			}
			else if (t.s[3] == "/")
			{
				toutput(divs, t0, t1);
				toutput(mflo, t2);
			}
			else if (t.s[3] == "")
			{
				toutput(moves, t2, t0);
			}
			get_lv(t3, lv);
			toutput(sw, t2, num2string(addr) + "(" + t3 + ")");
			break;
		}
		case LOGIC:
		{
			if (t.s[1] == "")
			{
				get_reg(t6, t.s[0]);
				break;
			}
			get_reg(t0, t.s[0]);
			get_reg(t1, t.s[2]);
			if (t.s[1] == "==")
			{
				toutput(xors, t2, t0, t1);
				toutput(sltiu, t6, t2, "1");
			}
			else if (t.s[1] == "<")
			{
				toutput(slt, t6, t0, t1);
			}
			else if (t.s[1] == ">")
			{
				toutput(slt, t6, t1, t0);
			}
			else if (t.s[1] == "<=")
			{
				toutput(sub, t2, t0, t1);
				toutput(slti, t6, t2, "1");
			}
			else if (t.s[1] == ">=")
			{
				toutput(sub, t2, t1, t0);
				toutput(slti, t6, t2, "1");
			}
			else
			{
				toutput(xors, t2, t0, t1);
				toutput(sltiu, t6, t2, "1");
				toutput(li, t2, "1");
				toutput(sub, t6, t2, t6);
			}
			break;
		}
		case GO:
		{
			if (t.s[0] == "GOTO") toutput(j, t.s[1]);
			else toutput(beq, t6, "$0", t.s[1]);
			break;
		}
		case LABEL:
		{
			toutput(t.s[0], 0);
			if (t.s[0][6] == 'f')
			{
				string id = label2func[t.s[0]];
				func_size = funcTable[0][id].size;
				if (id == "main") tcode_main = 1;
				toutput(addi, t0, sp, num2string(func_size));
				toutput(sw, ra, "-8(" + t0 + ")");
			} 
			break;
		}
		case SARRAY:
		{
			string x = t.s[0];
			int lv = string2num(cut_string2(cut_array3(x)));
			int addr = string2num(cut_string3(cut_array3(x)));
			get_reg(t0, t.s[2]);
			get_reg(t2, cut_array2(x));
			toutput(li, t3, "4");
			toutput(mult, t2, t3);
			toutput(mflo, t2); 
			get_lv(t1, lv);
			toutput(sub, t1, t1, t2);
			toutput(sw, t0, num2string(addr) + "(" + t1 + ")");
			break;
		}
		case LARRAY:
		{
			string x = t.s[2];
			int lv = string2num(cut_string2(cut_array3(x)));
			int addr = string2num(cut_string3(cut_array3(x)));
			get_reg(t2, cut_array2(x));
			toutput(li, t3, "4");
			toutput(mult, t2, t3);
			toutput(mflo, t2); 
			get_lv(t1, lv);
			toutput(sub, t1, t1, t2);
			toutput(lw, t0, num2string(addr) + "(" + t1 + ")");
			x = t.s[0];
			lv = string2num(cut_string2(x));
			addr = string2num(cut_string3(x));
			get_lv(t1, lv);
			toutput(sw, t0, num2string(addr) + "(" + t1 + ")");
			break;
		}
		case PRINT:
		{
			if (check_at(t.s[1]))
			{
				if (t.s[2] == "1")
				{
					get_reg(a0, t.s[1]);
					toutput(li, v0, "11");
					toutput(syscall);
				}
				else
				{
					get_reg(a0, t.s[1]);
					toutput(li, v0, "1");
					toutput(syscall);
				}
			}
			else
			{
				toutput(la, a0, t.s[1]);
				toutput(li, v0, "4");
				toutput(syscall);
			}
			break;
		}
		case SCAN:
		{
			string x = t.s[1];
			int lv = string2num(cut_string2(x));
			int addr = string2num(cut_string3(x));
			int type = string2num(cut_string4(x));
			get_lv(t3, lv);
			if (type == INT)
			{
				toutput(li, v0, "5");
				toutput(syscall);
			}
			else
			{
				toutput(li, v0, "12");
				toutput(syscall);
			}
			toutput(sw, v0, num2string(addr) + "(" + t3 + ")");
			break;
		}
	}
}


void tcode_output()
{
	for (int i = 0; i < mcode_num; i++)
	{
		if (code[i].type == LABEL && code[i].s[0][6] == 'f' && start_flag)
		{
			mcode tmp;
			tmp.type = RET;
			tmp.s[1] = "";
			tcode_print(tmp);
		}
		if (code[i].type == LABEL && !start_flag)
		{
			mcode tmp;
			tmp.type = CALL;
			tmp.s[1] = "main";
			tcode_print(tmp);
			start_flag = 1;
		}
		tcode_print(code[i]);
	}
}
