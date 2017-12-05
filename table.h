struct indent_table
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
};
map<string,indent_table> idTable[maxlevel];
map<string,array_table> arrayTable[maxlevel];
map<string,func_table> funcTable[maxlevel];

void insert_indent(int type, string id, int con, int val, int &addr)
{
	if (level == 0 && id == "main")
	{
		print_compile_error(20);
		return;
	}
	indent_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.con = con;
	tmp.val = val;
	if (type == CHAR) tmp.size = 1;
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
	array_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.upper = upper;
	if (type == CHAR) tmp.size = upper;
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
	func_table tmp;
	tmp.type = type;
	tmp.id = id;
	tmp.para = para;
	tmp.size = 8;
	for (int i = 0; i < para.size(); i++)
		if (para[i].first == CHAR) tmp.size += 1;
		else tmp.size += 4;
	tmp.addr = addr;
	addr -= tmp.size;
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
int exist_indent(string id, int level)
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
indent_table find_indent(string id, int level)
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
		if (exist_indent(id, i) || exist_array(id, i) || exist_func(id, i)) return i;
	return -1;
}
