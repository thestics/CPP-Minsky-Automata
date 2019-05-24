#include "../headers/compiler.hpp"


using namespace std;


CompiledSource::CompiledSource()
	: reg_amt(0)
	, reg_list(0)
{}


CompiledSource::CompiledSource(int new_reg_amt, vector<int> reg_vals)
	: reg_amt(new_reg_amt)
	, reg_list(reg_vals)
{}


void CompiledSource::append_instruction(Instruction *new_inst)
{
	Instruction *cpy = new Instruction(*new_inst);
	instructions.push_back(cpy);
}


vector<string> parse_line(string str_instruction)
{
	while (str_instruction[0] == ' ')
	{
		str_instruction = str_instruction.substr(1, str_instruction.size() - 1);
	}
	while (str_instruction[str_instruction.size() - 1] == ' ')
	{
		str_instruction = str_instruction.substr(0, str_instruction.size() - 2);
	}
	vector<string> splited;
	string cur;
	for (int i = 0; i < str_instruction.size(); i++)
	{
		if (str_instruction[i] != ' ')
		{
			cur += str_instruction[i];
		}
		else
		{
			splited.push_back(cur);
			cur.clear();
		}
	}
	splited.push_back(cur);
	return splited;
}


Instruction* parse_instruction(int i, string str_instruction)
{
	int reg_num, 
		instr_num, 
		instr_type, 
		left_arg, 
		right_arg;
	string instr_token;
	vector<string> splited = parse_line(str_instruction);
	instr_token = splited[0];
	if (instr_token == "END")
	{
		Instruction *res = new Instruction;
		return res;
	}
	else if (instr_token == "INC_JMP")
	{
		reg_num = stoi(splited[1]);
		instr_num = i;
		left_arg = stoi(splited[2]);
		right_arg = -1;
		Instruction *res = new Instruction(reg_num, instr_num, 1, left_arg, right_arg);
		return res;
	}
	else if (instr_token == "DEC_JNZ")
	{
		reg_num = stoi(splited[1]);
		instr_num = i;
		left_arg = stoi(splited[2]);
		right_arg = stoi(splited[3]);
		Instruction *res = new Instruction(reg_num, instr_num, 2, left_arg, right_arg);
		return res;
	}
	else
	{
		throw UnknownInstructionTypeError(1, "Unknown instruction type");
	}
}


CompiledSource* parse_file_to_instructions(char* filename)
{
	ifstream inpt;
	inpt.open(filename);
	int line_num = 1;
	CompiledSource *res = new CompiledSource;
	if (inpt.is_open())
	{
		inpt >> res->reg_amt;
		for (int i = 0; i < res->reg_amt; i++)
		{
			int cur;
			inpt >> cur;
			res->reg_list.push_back(cur);
		}
		string cur_row;
		while (!inpt.eof())
		{
			getline(inpt, cur_row);
			if (cur_row.empty())
				continue;
			Instruction* cur_instr = parse_instruction(line_num, cur_row);
			line_num++;
			res->instructions.push_back(cur_instr);
		}
	}
	return res;
}