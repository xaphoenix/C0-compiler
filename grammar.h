void check_const_introduction(int &addr);
void check_const_declaration(int &addr);
void check_variable_declaration(int type, int &addr);
void check_parameter_declaration(vector<pair<int,string> > &para, int &addr);
void check_func(string id, int rflag, int &addr);
void check_statements(int pr);
void check_program(int &addr);
void check_func_use(string id,int re);
string check_factor();
string check_item();
string check_expression();
void check_printf();
void check_scanf();
void check_condition(int pr);
void check_switch(int pr);
void check_case(int pr);
void check_casetable(int pr);
void check_default(int pr);
void check_if(int pr);
void check_while(int pr);


void check_const_declaration(int &addr)
{
	string type;
	if (sym == intsy || sym == charsy)
	{
		type = sym;
		while (1)
		{
			getsym();
			if (sym == ident)
			{
				if (exist_now_table(now_string))
				{
					print_compile_error(8);
					skip(comma, semicolon);
				}
				else
				{
					string id = now_string;
					getsym();
					if (sym == becomes)
					{
						getsym();
						if (type == intsy)
						{
							if (sym == numsy)
							{
								insert_ident(INT, id, 1, string2num(now_string), addr);
								getsym();
							}
							else if (sym == plusy || sym == minusy)
							{
								int ff = 1;
								if (sym == minusy) ff = -1;
								getsym();
								if (sym == numsy)
								{
									insert_ident(INT, id, 1, ff * string2num(now_string), addr);
									getsym();
								}
								else
								{
									print_compile_error(9);
									insert_ident(INT, id, 1, 0, addr);
								}
							}
							else
							{
								print_compile_error(9);
								insert_ident(INT, id, 1, 0, addr);
							}
						}
						else
						{
							if (sym == chsy)
							{
								insert_ident(CHAR, id, 1, string2char(now_string), addr);
								getsym();
							}
							else
							{
								print_compile_error(11);
								insert_ident(CHAR, id, 1, '_', addr);
							}
						}
					}
					else
					{
						print_compile_error(12);
						skip(comma, semicolon);
					}
				}
			}
			else
			{
				print_compile_error(13);
				skip(comma, semicolon);
			}
			if (sym == semicolon)
			{
				getsym();
				break;
			}
			if (sym != comma) 
			{
				print_compile_error(10);
				break;
			}
		}
	}
	else
	{
		print_compile_error(7);
		skip(comma, semicolon);
	}
	if (grammar_debug) printf("This is a const_declaration!\n");
}
void check_const_introduction(int &addr)
{
	while (sym == constsy)
	{
		getsym();
		check_const_declaration(addr);
	}
	if (grammar_debug) printf("This is a const_introduction!\n");
}	

void check_variable_declaration(int type, int &addr)
{
	while (1)
	{
		if (sym == semicolon) break;
		if (sym == comma)
		{
			getsym();
			if (sym == ident)
			{
				string id = now_string;
				if (exist_now_table(now_string))
				{
					print_compile_error(8);
					skip(comma, semicolon);
				}
				else
				{
					getsym();
					if (sym == lbracket)
					{
						getsym();
						int size;
						if (sym == numsy)
						{
							size = string2num(now_string);
							getsym();
						}
						else
						{
							size = 0;
							print_compile_error(16);
						}
						if (sym == rbracket) getsym();
						else print_compile_error(17);
						insert_array(type, id, size, addr);
					}
					else insert_ident(type, id, 0, 0, addr);
				}
			}
			else
			{
				print_compile_error(13);
				skip(comma, semicolon);
			}
		}
		else
		{
			print_compile_error(10);
			break;
		}
	}
	if (sym == semicolon) getsym();
	else print_compile_error(10);
	if (grammar_debug) printf("This is a variable declaration!\n");
}
void check_parameter_declaration(vector<pair<int,string> > &para, int &addr)
{
	if (sym == lbrace) return;
	getsym();
	int num = 0;
	while (1)
	{
		int type;
		if (sym == rparent) break;
		if (sym == intsy || sym == charsy)
		{
			type = sym == intsy ? INT : CHAR;
			getsym();
			if (sym == ident)
			{
				string id = now_string;
				if (exist_now_table(id))
				{
					print_compile_error(8);
					skip(comma, rparent);
				}
				else
				{
					insert_ident(type, id, 0, 0, addr, 0);
					para.push_back(make_pair(type, id));
					getsym();
				}
			}
			else
			{
				print_compile_error(13);
				skip(comma, rparent);
			}
		}
		else
		{
			print_compile_error(7);
			skip(comma, rparent);
		}
		if (sym == rparent) break;
		if (sym == comma) 
		{
			getsym();
			continue;
		}
		else print_compile_error(15);
	}
	getsym();
	if (sym != lbrace) print_compile_error(21);
	if (grammar_debug) printf("This is a parameter declaration!\n");
}
string check_factor()
{
	string nvar = "";
	if (sym == ident)
	{
		string id = now_string;
		int lv = exist_table(id);
		if (lv != -1)
		{
			getsym();
			if (sym == lbracket)
			{
				getsym();
				string tvar = check_expression();
				if (sym == rbracket) getsym();
				else print_compile_error(18);
				if (!exist_array(id, lv))
				{
					print_compile_error(26);
					skip(semicolon, rbrace);
				}
				mcode_insert(LARRAY, nvar = tmp_var(), "=", id + "[" + tvar + "]" + "@" + num2string(lv) + "#" + num2string(find_array(id, lv).addr) + "*" + num2string(find_array(id, lv).type)) ;
			}
			else
			{
				if (exist_func(id, lv)) 
				{
					check_func_use(id, 1);
					nvar = tmp_var();
					mcode_insert(RECALL, nvar, "=", "ret");
				}
				else if (!exist_ident(id, lv))
				{
					print_compile_error(26);
					skip(semicolon, rbrace);
				}
				else
				{
					nvar = id + "@" + num2string(lv) + "#" + num2string(find_ident(id, lv).addr) + "*" + num2string(find_array(id, lv).type);
				}
			}
		}
		else
		{
			print_compile_error(25);
			skip(semicolon, rbrace);
		}
	}
	else if (sym == lparent)
	{
		getsym();
		nvar = check_expression();
		if (sym == rparent) getsym();
		else print_compile_error(15);
	}
	else if (sym == numsy) 
	{
		nvar = now_string;
		getsym();
	}
	else if (sym == plusy || sym == minusy)
	{
		int ff = 1;
		if (sym == minusy)  ff = -1;
		getsym();
		if (sym == numsy) 
		{
			nvar = now_string;
			if (ff == -1) nvar = "-" + nvar;
			getsym();
		}
		else print_compile_error(16);
	}
	else if (sym == chsy) 
	{
		nvar = "\'" + now_string + "\'";
		getsym();
	}
	else
	{
		print_compile_error(27);
		skip(semicolon, rbrace); 
	}
		
	if (grammar_debug) printf("This is a factor!\n");
	return nvar;
}
string check_item()
{
	string nvar = "";
	string tvar1, tvar2;
	nvar = tvar1 = check_factor();
	while (sym == timesy || sym == divsy)
	{
		string oper = sym;
		getsym();
		tvar2 = check_factor();
		nvar = tmp_var();
		if (oper == timesy) mcode_insert(ASSIGN, nvar, "=", tvar1, "*", tvar2);
		else mcode_insert(ASSIGN, nvar, "=", tvar1, "/", tvar2);
		tvar1 = nvar;
	}
	if (grammar_debug) printf("This is a item!\n");
	return nvar;
}
string check_expression()
{
	string nvar = "";
	string tvar1, tvar2;
	int ff = 1;
	if (sym == plusy || sym == minusy)
	{
		if (sym == minusy) ff = -1;
		getsym();
	}
	nvar = tvar1 = check_item();
	if (ff == -1)
	{
		nvar = tmp_var();
		mcode_insert(ASSIGN, nvar, "=", "0", "-", tvar1);
		tvar1 = nvar;
	}
	while (sym == plusy || sym == minusy)
	{
		string oper = sym;
		getsym();
		tvar2 = check_item();
		nvar = tmp_var();
		if (oper == plusy) mcode_insert(ASSIGN, nvar, "=", tvar1, "+", tvar2);
		else mcode_insert(ASSIGN, nvar, "=", tvar1, "-", tvar2);
		tvar1 = nvar;
	}
	if (grammar_debug) printf("This is an expression!\n");
	return nvar;
}

void check_func_use(string id, int re)
{
	int lv = exist_table(id);
	func_table tmp = find_func(id, lv);
	if (sym == lparent)
	{
		if (tmp.para.size() == 0) print_compile_error(29);
		else
		{
			getsym();
			for (int i = 0; i < tmp.para.size(); i++)
			{
				string tvar = check_expression();
				mcode_insert(PUSH, "push", tvar);
				if (i == tmp.para.size() - 1) break;
				if (sym == comma) getsym();
				else print_compile_error(32);
			}
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
	}
	else
	{
		if (tmp.para.size() != 0) print_compile_error(31);
	}
	if (re == 1 && tmp.type == VOID) print_compile_error(30);
	if (grammar_debug) printf("This is a func use!\n");
	mcode_insert(CALLL, "call", id);
}
void check_condition()
{
	string tvar1, tvar2;
	tvar1 = check_expression();
	if (sym == lss || sym == leq || sym == gtr || sym == geq || sym == neq || sym == eql)
	{
		string oper = now_string;
		getsym();
		tvar2 = check_expression();
		mcode_insert(LOGIC, tvar1, oper, tvar2);
	}
	else mcode_insert(LOGIC, tvar1);
	if (grammar_debug) printf("This is a condition!\n");
}
void check_if(int addr)
{
	string else_label = if_else(), end_label = if_end();
	if (sym == lparent) getsym();
	else print_compile_error(28);
	check_condition();
	mcode_insert(GO, "BZ", else_label);
	if (sym == rparent) getsym();
	else print_compile_error(15);
	check_statements(addr);
	mcode_insert(GO, "GOTO", end_label);
	mcode_insert(LABEL, else_label + ":");
	if (sym == elsesy) getsym();
	else print_compile_error(35);
	check_statements(addr);
	mcode_insert(LABEL, end_label + ":");
	if (grammar_debug) printf("This is an if!\n");
}
void check_while(int addr)
{
	string begin_label = while_begin(), end_label = while_end();
	if (sym == lparent) getsym();
	else print_compile_error(28);
	mcode_insert(LABEL, begin_label + ":");
	check_condition();
	mcode_insert(GO, "BZ", end_label);
	if (sym == rparent) getsym();
	else print_compile_error(15);
	check_statements(addr);
	mcode_insert(GO, "GOTO", begin_label);
	mcode_insert(LABEL, end_label + ":");
	if (grammar_debug) printf("This is a while!\n");
}
void check_scanf()
{
	if (sym == lparent) getsym();
	else print_compile_error(29);
	if (sym == ident)
	{
		string id = now_string;
		int lv = exist_table(id);
		if (lv == -1) 
		{
			print_compile_error(25);
			skip(comma, rparent);
		}
		else
		{
			if (exist_ident(id, lv)) 
			{
				ident_table tmp = find_ident(id, lv);
				if (tmp.con == 1) print_compile_error(37);
				mcode_insert(SCAN, "scanf", id + "@" + num2string(lv) + "#" + num2string(find_ident(id, lv).addr) + "*" + num2string(find_array(id, lv).type));
				getsym();
			}
			else
			{
				print_compile_error(27);
				skip(comma, rparent);
			}
		}
	}
	else
	{
		print_compile_error(13);
		skip(comma, rparent);
	}
	while (sym == comma)
	{
		getsym();
		if (sym == ident)
		{
			string id = now_string;
			int lv = exist_table(id);
			if (lv == -1) 
			{
				print_compile_error(25);
				skip(comma, rparent);
			}
			else
			{
				if (exist_ident(id, lv)) 
				{
					ident_table tmp = find_ident(id, lv);
					if (tmp.con == 1) print_compile_error(37);
					getsym();
					mcode_insert(SCAN, "scanf", id + "@" + num2string(lv) + "#" + num2string(find_ident(id, lv).addr) + "*" + num2string(find_array(id, lv).type));
				}
				else
				{
					print_compile_error(27);
					skip(comma, rparent);
				}
			}
		}
		else
		{
			print_compile_error(13);
			skip(comma, rparent);
		}
	}
	if (sym == rparent) getsym();
	else print_compile_error(15);
	if (sym == semicolon) getsym();
	else print_compile_error(10);
	if (grammar_debug) printf("This is a scanf!\n");
}
void check_printf()
{
	string tvar;
	if (sym == lparent) getsym();
	else print_compile_error(29);
	if (sym == rparent) 
	{
		mcode_insert(PRINT, "printf", "\"\\n\"");
		getsym();
	}
	else if (sym == strsy)
	{
		mcode_insert(PRINT, "printf", "\"" + now_string + "\"");
		getsym();
		if (sym == comma)
		{
			getsym();
			tvar = check_expression();
			if (sym == rparent) getsym();
			else print_compile_error(15);
			mcode_insert(PRINT, "printf", tvar);
		}
		else
		{
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
	}
	else 
	{
		tvar = check_expression();
		mcode_insert(PRINT, "printf", tvar);
		if (sym == rparent) getsym();
		else print_compile_error(15);
	}
	if (sym == semicolon) getsym();
	else print_compile_error(10);
	if (grammar_debug) printf("This is a printf!\n");
}
void check_case(int pr, string tvar1, string end_label)
{
	string tvar2 = "";
	string cend_label = case_end();
	if (sym == numsy) 
	{
		tvar2 = now_string;
		getsym();
	}
	else if (sym == chsy) 
	{
		tvar2 = now_string;
		getsym();
	}
	else if (sym == plusy || sym == minusy)
	{
		int ff = 1;
		if (sym == minusy) ff = -1;
		getsym();
		if (sym == numsy) 
		{
			tvar2 = now_string;
			if (ff == -1) tvar2 = "-" + tvar2;
			getsym();
		}
		else print_compile_error(33);
	}
	else print_compile_error(33);
	if (sym == colon) getsym();
	else print_compile_error(34);
	mcode_insert(LOGIC, tvar1, "==", tvar2);
	mcode_insert(GO, "BZ", cend_label);
	check_statements(pr);
	mcode_insert(GO, "GOTO", end_label);
	mcode_insert(LABEL, cend_label + ":");
}
void check_casetable(int pr, string tvar1, string end_label)
{
	check_case(pr, tvar1, end_label);
	while (sym == casesy) 
	{
		getsym();
		check_case(pr, tvar1, end_label);
	}
}
void check_default(int pr)
{
	if (sym == colon) getsym();
	else print_compile_error(34);
	check_statements(pr);
}
void check_switch(int pr)
{
	string end_label = switch_end();
	string tvar;
	if (sym == lparent) getsym();
	else print_compile_error(28);
	tvar = check_expression();
	if (sym == rparent) getsym();
	else print_compile_error(15);
	if (sym == lbrace) getsym();
	else print_compile_error(21);
	getsym();
	check_casetable(pr, tvar, end_label);
	if (sym == defaultsy) 
	{
		getsym();
		check_default(pr);
	}
	if (sym == rbrace) getsym();
	else print_compile_error(22);
	mcode_insert(LABEL, end_label + ":");
	if (grammar_debug) printf("This is a switch!\n");
}
void check_statements(int pr)
{
	if (sym == ident)
	{
		string id = now_string;
		int lv = exist_table(id);
		if (lv == -1)
		{
			print_compile_error(25);
			skip(semicolon, rbrace);
		}
		else
		{
			if (exist_func(id, lv))
			{
				getsym();
				check_func_use(id, 0);
				if (sym == semicolon) getsym();
				else print_compile_error(10);
			}
			else if (exist_ident(id, lv))
			{
				getsym();
				if (sym == becomes) getsym();
				else print_compile_error(12);
				string tvar= check_expression();
				mcode_insert(ASSIGN, id + "@" + num2string(lv) + "#" + num2string(find_ident(id, lv).addr) + "*" + num2string(find_array(id, lv).type), "=", tvar);
				if (sym == semicolon) getsym();
				else print_compile_error(10);
				ident_table tmp = find_ident(id, lv);
				if (tmp.con == 1) print_compile_error(37);
			}
			else
			{
				getsym();
				if (sym == lbracket) getsym();
				else print_compile_error(36);
				string tvar1 = check_expression();
				if (sym == rbracket) getsym();
				else print_compile_error(17);
				if (sym == becomes) getsym();
				else print_compile_error(12);
				string tvar2 = check_expression();
				mcode_insert(SARRAY, id + "[" + tvar1 + "]" + "@" + num2string(lv) + "#" + num2string(find_array(id, lv).addr) + "*" + num2string(find_array(id, lv).type), "=", tvar2);
				if (sym == semicolon) getsym();
				else print_compile_error(10);
			}
		}
	}
	else if (sym == ifsy)
	{
		getsym();
		check_if(pr);
	}
	else if (sym == whilesy)
	{
		getsym();
		check_while(pr);
	}
	else if (sym == switchsy)
	{
		getsym();
		check_switch(pr);
	}
	else if (sym == scanfsy)
	{
		getsym();
		check_scanf();
	}
	else if (sym == printfsy)
	{
		getsym();
		check_printf();
	}
	else if (sym == returnsy)
	{
		getsym();
		if (pr == 0)
		{
			mcode_insert(RET, "ret");
		}
		else
		{
			if (sym == lparent) getsym();
			else print_compile_error(28);
			string tvar = check_expression();
			mcode_insert(RET, "ret", tvar);
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
		if (sym == semicolon) 
		{
			getsym();
		}
		else print_compile_error(10);
		if (grammar_debug) printf("This is a return!\n");
	}
	else if (sym == lbrace)
	{
		getsym();
		while (sym != rbrace)
			check_statements(pr);
		if (sym == rbrace) getsym();
		else print_compile_error(22);
	}
	else if (sym == semicolon) getsym();
	else 
	{
		print_compile_error(24);
		skip(semicolon, rbrace);
	}
	if (grammar_debug) printf("This is a statements!\n");
}
void check_func(string id, int pr,int &addr)
{
	string begin_label = func_begin();
	mcode_insert(LABEL, begin_label + ":");
	label2func[begin_label + ":"] = id;
	if (sym == constsy) check_const_introduction(addr);
	while (1)
	{
		if (sym == intsy || sym == charsy)
		{
			int type = 0;
			if (sym == intsy) type = INT;
			else type = CHAR;
			sym = comma;
			check_variable_declaration(type, addr);
		}
		else break;
	}
	funcTable[level - 1][id].addr = addr;
	while (sym != rbrace)
		check_statements(pr);
	getsym();
	if (grammar_debug) printf("This is a function!\n");
}

void check_program(int &addr)
{
	string id;
	string ty;
	vector<pair<int,string> > para;
	getsym();
	if (sym == constsy) check_const_introduction(addr);
	while (1)
	{
		if (sym == intsy || sym == charsy)
		{
			int type;
			type = sym == intsy ? INT : CHAR;
			ty = sym;
			getsym();
			if (sym == ident || sym == mainsy)
			{
				id = now_string;
				getsym();
				if (sym == lparent || sym == lbrace) 
				{
					string now = sym;
					para.clear();
					level++;
					int tmp = -16;
					check_parameter_declaration(para, tmp);
					level--;
					if (now == lparent && para.size() == 0)
					{
						if (level == 0 && id == "main");
						else print_compile_error(23);
					}
					insert_func(type, id, para, tmp);
					level++;
					getsym();
					now_func = id;
					check_func(id, 1, tmp);
					clear_table();
					level--;
					break;
				}
				else 
				{
					if (sym == lbracket)
					{
						getsym();
						int size;
						if (sym == numsy)
						{
							size = string2num(now_string);
							getsym();
						}
						else
						{
							size = 0;
							print_compile_error(16);
						}
						getsym();
						if (sym == rbracket) getsym();
						else print_compile_error(17);
						insert_array(type, id, size, addr);
					}
					else insert_ident(type, id, 0, 0, addr);
					check_variable_declaration(type, addr); 
				} 
			}
			else
			{
				print_compile_error(13);
				skip(comma, semicolon);
			}
		}
		else
		{
			if (sym == voidsy)
			{
				getsym();
				if (sym == ident || sym == mainsy)
				{
					string id = now_string;
					getsym();
					if (sym == lparent || sym == lbrace) 
					{
						string now = sym;
						para.clear();
						level++;
						int tmp = -16;
						check_parameter_declaration(para, tmp);
						level--;
						if (now == lparent && para.size() == 0 && id != "main") print_compile_error(23);
						insert_func(VOID, id, para, tmp);
						level++;
						getsym();
						now_func = id;
						check_func(id, 0, tmp);
						clear_table();
						level--;
						break;
					}
					else print_compile_error(21);
				}
				else
				{
					print_compile_error(13);
					skip(comma, semicolon);
				}
				break;
			}
			else
			{
				print_compile_error(7);
				skip(comma, semicolon);
			}
		}
	}
	
	while (!main_flag)
	{
		int pr;
		if (sym == intsy || sym == charsy || sym == voidsy)
		{
			int type;
			if (sym == intsy) type = INT;
			else if (sym == charsy) type = CHAR;
			else type = VOID; 
			if (sym == voidsy) pr = 0;
			else pr = 1;
			getsym();
			if (sym == ident || sym == mainsy)
			{
				string id = now_string;
				getsym();
				if (sym == lparent || sym == lbrace) 
				{
					string now = sym;
					para.clear();
					level++;
					int tmp = -16;
					check_parameter_declaration(para, tmp);
					level--;
					if (now == lparent && para.size() == 0)
					{
						if (level == 0 && id == "main");
						else print_compile_error(23);
					}
					insert_func(type , id, para, tmp);
					level++;
					getsym();
					now_func = id;
					check_func(id, pr, tmp);
					clear_table();
					level--;
				}
				else print_compile_error(21);
			}
			else
			{
				print_compile_error(13);
				skip(comma, semicolon);
			}
		}
		else
		{
			print_compile_error(14);
			skip(comma, semicolon);
		}
	}
	func_size = abs(addr);
	if (grammar_debug) printf("This is a program!\n");
}
