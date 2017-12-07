struct ident_table
{
	int type;  // int or char
	string id;  // name
	int con;  // const or not
	int val;  // value
	int size;  // space
	int addr;  // relatively address
};

struct array_table
{
	int type;  // int or char
	string id;  // name
	int upper;  // upper bound
	int size;  // space
	int addr;  // relatively address
};

struct func_table
{
	int type;  // int or char or void
	string id;  // name
	vector<pair<int,string> > para;  // parameter
	int size;  //  space
	int addr;  // relatively address
	int num;  // number
};
map<string, ident_table> idTable[maxlevel];
map<string, array_table> arrayTable[maxlevel];
map<string, func_table> funcTable[maxlevel];
map<string, string> tmp_addr;

void insert_ident(int type, string id, int con, int val, int &addr, int print = 1)
{
	if (level == 0 && id == "main")
	{
		print_compile_error(20);
		return;
	}
	if (print)
	{
		if (con) 
		{
			string tmp = "";
			if (val < 0) 
			{
				tmp = "-";
				val = abs(val);
			}
			tmp = tmp + num2string(val);
			if (type == INT) mcode_insert(CONST, "const", "int", id + "@" + num2string(level) + "#" + num2string(addr) + "*0", "=", tmp);
			else mcode_insert(CONST, "const", "char", id + "@" + num2string(level) + "#" + num2string(addr) + "*1", "=", "\'" + num2char2string(val) + "\'"); 
		}
		else
		{
			if (type == INT) mcode_insert(VAR, "var", "int", id + "@" + num2string(level) + "#" + num2string(addr) + "*0");
			else mcode_insert(VAR, "var", "char", id + "@" + num2string(level) + "#" + num2string(addr) + "*1");
		}
	}
	ident_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.con = con;
	tmp.val = val;
	if (type == CHAR) tmp.size = 4;
	else tmp.size = 4;
	tmp.addr = addr;
	addr -= tmp.size;
	idTable[level][id] = tmp;
}
void insert_array(int type, string id, int upper, int &addr)
{
	if (level == 0 && id == "main")
	{
		print_compile_error(20);
		return;
	}
	if (type == INT) mcode_insert(VAR, "var", "int", id, "[" + num2string(upper) + "]");
	else mcode_insert(VAR, "var", "char", id, "[" + num2string(upper) + "]");
	array_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.upper = upper;
	if (type == CHAR) tmp.size = upper * 4;
	else tmp.size = upper * 4;
	tmp.addr = addr;
	addr -= tmp.size;
	arrayTable[level][id] = tmp;
}
void insert_func(int type, string id, vector<pair<int, string> > para, int &addr)
{
	if (id == "main")
	{
		if (type != VOID) print_compile_error(18), type = VOID;
		if (para.size() != 0) print_compile_error(19), para.clear();
		main_flag = 1;
	}
	if (type == INT) mcode_insert(FUNC, "int", id+"()");
	else if (type == CHAR) mcode_insert(FUNC, "char", id+"()");
	else mcode_insert(FUNC, "void", id+"()");
	func_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.para = para;
	tmp.size = (level + 1) * 4 + 8;
	tmp.num = func_num;
	for (int i = 0; i < para.size(); i++)
		if (para[i].first == CHAR) 
		{
			tmp.size += 4;
			mcode_insert(PARA, "char", para[i].second);
		}
		else 
		{
			tmp.size += 4;
			mcode_insert(PARA, "int", para[i].second);
		}
	funcTable[level][id] = tmp;
}
void clear_table()
{
	idTable[level].clear();
	arrayTable[level].clear();
	funcTable[level].clear();
}
int exist_now_table(string id)
{
	if (idTable[level].count(id) || arrayTable[level].count(id) || funcTable[level].count(id)) return 1;
	return 0;
}		
int exist_ident(string id, int level)
{
	return idTable[level].count(id);
}
int exist_array(string id, int level)
{
	return arrayTable[level].count(id);
}
int exist_func(string id, int level)
{
	return funcTable[level].count(id);
}
ident_table find_ident(string id, int level)
{
	return idTable[level][id];
}
array_table find_array(string id, int level)
{
	return arrayTable[level][id];
}
func_table find_func(string id, int level)
{
	return funcTable[level][id];
}
int exist_table(string id)
{
	for (int i = level; i >= 0; i--)
		if (exist_ident(id, i) || exist_array(id, i) || exist_func(id, i)) return i;
	return -1;
}
void insert_tmp_var(string func, string id)
{
	func_table tmp = funcTable[0][func];
	tmp_addr[id] = num2string(tmp.addr);
	funcTable[0][func].addr -= 4;
	funcTable[0][func].size += 4;
}
