void check_const_introduction(int addr);
void check_const_declaration(int addr);
void check_variable_declaration(int type, int &addr);
void check_parameter_declaration(vector<pair<int,string> > &para, int &addr);
void check_func(int rflag, int &addr);
void check_statements(int pr);
void check_program(int addr);
void check_func_use(string id,int re);
void check_factor();
void check_item();
void check_expression();
void check_printf();
void check_scanf();
void check_condition(int pr);
void check_switch(int pr);
void check_case(int pr);
void check_casetable(int pr);
void check_default(int pr);
void check_if(int pr);
void check_while(int pr);


void check_const_declaration(int addr)
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
								insert_indent(INT, id, 1, string2num(now_string), addr);
								getsym();
							}
							else if (sym == plusy || sym == minusy)
							{
								int ff = 1;
								if (sym == minusy) ff = -1;
								getsym();
								if (sym == numsy)
								{
									insert_indent(INT, id, 1, ff * string2num(now_string), addr);
									getsym();
								}
								else
								{
									print_compile_error(9);
									insert_indent(INT, id, 1, 0, addr);
								}
							}
							else
							{
								print_compile_error(9);
								insert_indent(INT, id, 1, 0, addr);
							}
						}
						else
						{
							if (sym == chsy)
							{
								insert_indent(CHAR, id, 1, string2char(now_string), addr);
								getsym();
							}
							else
							{
								print_compile_error(11);
								insert_indent(CHAR, id, 1, '_', addr);
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
void check_const_introduction(int addr)
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
					else insert_indent(type, id, 0, 0, addr);
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
					insert_indent(type, id, 0, 0, addr);
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
void check_factor()
{
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
				check_expression();
				if (sym == rbracket) getsym();
				else print_compile_error(18);
				if (!exist_array(id, lv))
				{
					print_compile_error(26);
					skip(semicolon, rbrace);
				} 
			}
			else
			{
				if (exist_func(id, lv)) 
				{
					check_func_use(id, 1);
				}
				else if (!exist_indent(id, lv))
				{
					print_compile_error(26);
					skip(semicolon, rbrace);
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
		check_expression();
		if (sym == rparent) getsym();
		else print_compile_error(15);
	}
	else if (sym == numsy) getsym();
	else if (sym == plusy || sym == minusy)
	{
		int ff = 1;
		if (sym == minusy)  ff = -1;
		getsym();
		if (sym == numsy) getsym();
		else print_compile_error(16);
	}
	else if (sym == chsy) getsym();
	else
	{
		print_compile_error(27);
		skip(semicolon, rbrace); 
	}
		
	if (grammar_debug) printf("This is a factor!\n");
}
void check_item()
{
	check_factor();
	while (sym == timesy || sym == divsy)
	{
		getsym();
		check_factor();
	}
	if (grammar_debug) printf("This is a item!\n");
}
void check_expression()
{
	int ff = 1;
	if (sym == plusy || sym == minusy)
	{
		if (sym == minusy) ff = -1;
		getsym();
	}
	check_item();
	while (sym == plusy || sym == minusy)
	{
		getsym();
		check_item();
	}
	if (grammar_debug) printf("This is an expression!\n");
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
				check_expression();
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
}
void check_condition()
{
	check_expression();
	if (sym == lss || sym == leq || sym == gtr || sym == geq || sym == neq || sym == eql)
	{
		getsym();
		check_expression();
	}
	if (grammar_debug) printf("This is a condition!\n");
}
void check_if(int addr)
{
	if (sym == lparent) getsym();
	else print_compile_error(28);
	check_condition();
	if (sym == rparent) getsym();
	else print_compile_error(15);
	check_statements(addr);
	if (sym == elsesy) getsym();
	else print_compile_error(35);
	check_statements(addr);
	if (grammar_debug) printf("This is an if!\n");
}
void check_while(int addr)
{
	if (sym == lparent) getsym();
	else print_compile_error(28);
	check_condition();
	if (sym == rparent) getsym();
	else print_compile_error(15);
	check_statements(addr);
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
			if (exist_indent(id, lv)) 
			{
				indent_table tmp = find_indent(id, lv);
				if (tmp.con == 1) print_compile_error(37);
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
				if (exist_indent(id, lv)) 
				{
					indent_table tmp = find_indent(id, lv);
					if (tmp.con == 1) print_compile_error(37);
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
	}
	if (sym == rparent) getsym();
	else print_compile_error(15);
	if (sym == semicolon) getsym();
	else print_compile_error(10);
	if (grammar_debug) printf("This is a scanf!\n");
}
void check_printf()
{
	if (sym == lparent) getsym();
	else print_compile_error(29);
	if (sym == rparent) getsym();
	else if (sym == strsy)
	{
		getsym();
		if (sym == comma)
		{
			getsym();
			check_expression();
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
		else
		{
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
	}
	else 
	{
		check_expression();
		if (sym == rparent) getsym();
		else print_compile_error(15);
	}
	if (sym == semicolon) getsym();
	else print_compile_error(10);
	if (grammar_debug) printf("This is a printf!\n");
}
void check_case(int pr)
{
	if (sym == numsy) getsym();
	else if (sym == chsy) getsym();
	else if (sym == plusy || sym == minusy)
	{
		int ff = 1;
		if (sym == minusy) ff = -1;
		getsym();
		if (sym == numsy) getsym();
		else print_compile_error(33);
	}
	else print_compile_error(33);
	if (sym == colon) getsym();
	else print_compile_error(34);
	check_statements(pr);
}
void check_casetable(int pr)
{
	check_case(pr);
	while (sym == casesy) 
	{
		getsym();
		check_case(pr);
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
	if (sym == lparent) getsym();
	else print_compile_error(28);
	check_expression();
	if (sym == rparent) getsym();
	else print_compile_error(15);
	if (sym == lbrace) getsym();
	else print_compile_error(21);
	getsym();
	check_casetable(pr);
	if (sym == defaultsy) 
	{
		getsym();
		check_default(pr);
	}
	if (sym == rbrace) getsym();
	else print_compile_error(22);
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
			else if (exist_indent(id, lv))
			{
				getsym();
				if (sym == becomes) getsym();
				else print_compile_error(12);
				check_expression();
				if (sym == semicolon) getsym();
				else print_compile_error(10);
				indent_table tmp = find_indent(id, lv);
				if (tmp.con == 1) print_compile_error(37);
			}
			else
			{
				getsym();
				if (sym == lbracket) getsym();
				else print_compile_error(36);
				check_expression();
				if (sym == rbracket) getsym();
				else print_compile_error(17);
				if (sym == becomes) getsym();
				else print_compile_error(12);
				check_expression();
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
		if (pr == 0);
		else
		{
			if (sym == lparent) getsym();
			else print_compile_error(28);
			check_expression();
			if (sym == rparent) getsym();
			else print_compile_error(15);
		}
		if (sym == semicolon) getsym();
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
void check_func(int pr,int &addr)
{
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
	while (sym != rbrace)
		check_statements(pr);
	getsym();
	if (grammar_debug) printf("This is a function!\n");
}

void check_program(int addr)
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
					int tmp = 0;
					para.clear();
					level++;
					check_parameter_declaration(para, addr);
					level--;
					if (now == lparent && para.size() == 0)
					{
						if (level == 0 && id == "main");
						else print_compile_error(23);
					}
					insert_func(type, id, para, addr);
					level++;
					getsym();
					check_func(1, tmp);
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
					else insert_indent(type, id, 0, 0, addr);
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
						int tmp = 0;
						para.clear();
						level++;
						check_parameter_declaration(para, addr);
						level--;
						if (now == lparent && para.size() == 0 && id != "main") print_compile_error(23);
						insert_func(VOID, id, para, addr);
						level++;
						getsym();
						check_func(0, tmp);
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
					int tmp = 0;
					para.clear();
					level++;
					check_parameter_declaration(para, addr);
					level--;
					if (now == lparent && para.size() == 0)
					{
						if (level == 0 && id == "main");
						else print_compile_error(23);
					}
					insert_func(type , id, para, addr);
					level++;
					getsym();
					check_func(pr, tmp);
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
	if (grammar_debug) printf("This is a program!\n");
}
