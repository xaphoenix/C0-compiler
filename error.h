string now_position()
{
	string s = "Line " + num2string(now_row) + ", Col " + num2string(now_col) + ": ";
	return s;
}
void print_fatal_error(int no)
{
	
}
void print_compile_error(int no)
{
	compile_msg[0] = "Error. Expected more characters at the end of file.";
	compile_msg[1] = "Error. " + now_position() + "Illegal character in single colon.";
	compile_msg[2] = "Error. " + now_position() + "Unpair single colon.";
	compile_msg[3] = "Error. " + now_position() + "Illegal character in double colon.";
	compile_msg[4] = "Error. " + now_position() + "Unpair double colon.";
	compile_msg[5] = "Error. " + now_position() + "Illegal character in file.";
	compile_msg[6] = "Error. " + now_position() + "Illegal symbol in file.";
	compile_msg[7] = "Error. " + now_position() + "Illegal symbol when expected int or char.";
	compile_msg[8] = "Error. " + now_position() + "Identifier redefined.";
	compile_msg[9] = "Error. " + now_position() + "Illegal symbol when expected a const integer.";
	compile_msg[10] = "Error. " + now_position() + "Illegal symbol when expected a semicolon";
	compile_msg[11] = "Error. " + now_position() + "Illegal symbol when expected a const char.";
	compile_msg[12] = "Error. " + now_position() + "Illegal symbol when expected an equality sign.";
	compile_msg[13] = "Error. " + now_position() + "Illegal symbol when expected an identifier.";
	compile_msg[14] = "Error. " + now_position() + "Illegal symbol when expected int or char or void.";
	compile_msg[15] = "Error. " + now_position() + "Illegal symbol when expected right parent.";
	compile_msg[16] = "Error. " + now_position() + "Illegal symbol when expected unsigned integer.";
	compile_msg[17] = "Error. " + now_position() + "Illegal symbol when expected right bracket.";
	compile_msg[18] = "Error. " + now_position() + "Expected void before main function.";
	compile_msg[19] = "Error. " + now_position() + "Expected none parameter in main function.";
	compile_msg[20] = "Error. " + now_position() + "Illegal declaration with main.";
	compile_msg[21] = "Error. " + now_position() + "Illegal symbol when expected left brace.";
	compile_msg[22] = "Error. " + now_position() + "Illegal symbol when expected right brace.";
	compile_msg[23] = "Error. " + now_position() + "Expected parameter in function.";
	compile_msg[24] = "Error. " + now_position() + "Illegal statements.";
	compile_msg[25] = "Error. " + now_position() + "Unknown identifier.";
	compile_msg[26] = "Error. " + now_position() + "Identifier type wrong.";
	compile_msg[27] = "Error. " + now_position() + "Unknown factor.";
	compile_msg[28] = "Error. " + now_position() + "Illegal symbol when expected left parent.";
	compile_msg[29] = "Error. " + now_position() + "Unexpected left parent.";
	compile_msg[30] = "Error. " + now_position() + "Illegal type of function.";
	compile_msg[31] = "Error. " + now_position() + "Illegal utlization of para-function.";
	compile_msg[32] = "Error. " + now_position() + "Illegal symbol when expected comma.";
	compile_msg[33] = "Error. " + now_position() + "Illegal symbol when expected cosntant.";
	compile_msg[34] = "Error. " + now_position() + "Illegal symbol when expected colon.";
	compile_msg[35] = "Error. " + now_position() + "Illegal symbol when expected else.";
	compile_msg[36] = "Error. " + now_position() + "Illegal symbol when expected left bracket.";
	compile_msg[37] = "Error. " + now_position() + "Illegal assignment to a const variable.";
	cout<<compile_msg[no]<<endl;
}

