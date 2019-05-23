#include "../headers/7Kovalenko.hpp"


using namespace std;


Memory::Memory()
	: reg_amount(0)
	, reg_list()
{}

Memory::Memory(int reg_amt)
	: reg_amount(reg_amt)
	, reg_list(reg_amt)  // set a given size to avoid first reallocations (??) 
{}

void Memory::set_zero(int index) 
{
	if (!(0 <= index && index < reg_amount))
	{
		// trow exc
	}
	reg_list[index] = 0;
}

void Memory::set_n(int index, int n)
{
	reg_list[index] = n;
}

void Memory::show() 
{
	cout << "Registers data:" << endl;
	for (size_t i = 0; i < reg_list.size(); i++)
	{
		cout << "Reg: " << i << " val: " << reg_list[i] <<  endl;
	}
}

void Memory::add_reg() 
{
	reg_list.push_back(0);
	reg_amount++;
}

int Memory::get_reg(int index) const
{
	if (!(0 <= index && index < reg_amount))
	{
		// trow exc
	}
	return reg_list[index];
}

int Memory::get_reg_amount() const
{
	return reg_amount;
}

void Memory::inc_reg(int index) { reg_list[index]++; }

void Memory::dec_reg(int index) { reg_list[index]--; }

bool Memory::is_reg_zero(int index) { return reg_list[index] == 0; }

vector<int> Memory::get_regs() const { return reg_list; }




Instruction::Instruction()
	: reg_num(-1)
	, instr_num(0)
	, instr_type(INS_END)
	, left_arg(-1)
	, right_arg(-1)
{}

Instruction::Instruction(int reg_num, int instr_num, int new_instr_type, int new_left_arg, int new_right_arg) 
	: reg_num(reg_num)
	, instr_num(instr_num)
	, instr_type(-1)
	, left_arg(new_left_arg)
	, right_arg(new_right_arg)
{
	if (!(0 <= new_instr_type && new_instr_type <= 2))
	{
		// throw exc UNKNOWN INSTRUCTION TYPE
	}
	else
	{
		instr_type = new_instr_type;
	}
}

Instruction::Instruction(const Instruction& other)
	: reg_num(other.get_reg_num())
	, instr_num(other.get_instr_num())
	, instr_type(other.get_instr_type())
	, left_arg(other.get_left_arg())
	, right_arg(other.get_right_arg())
{}

int Instruction::get_instr_type() const { return instr_type; }

int Instruction::get_reg_num() const { return reg_num; }

int Instruction::get_instr_num() const { return instr_num; }

int Instruction::get_left_arg() const { return left_arg; }

int Instruction::get_right_arg() const { return right_arg; }

void Instruction::show() 
{
	switch (instr_type)
	{
	case INS_END:
		cout << "END" << endl;
		break;
	case INS_INCJMP:	// increment jump
		cout << "INC_JMP " << reg_num << ' ' << left_arg << endl;
		break;
	case INS_DECJNZ:	// decrement jump non-zero
		cout << "DEC_JNZ " << reg_num << ' ' << left_arg << ' ' << right_arg << endl;
		break;
	}
}

int Instruction::exec(Memory* mem)
/// executes self on given register list and returns next instruction index (-1 if instruction is end)
{
	switch (instr_type)
	{
	case INS_END:
	{
		return -1;
	}
	case INS_INCJMP:
	{
		mem->inc_reg(reg_num);
		return get_left_arg();
	}
	case INS_DECJNZ:
	{
		if (mem->is_reg_zero(reg_num))
			return get_right_arg();	// jump because zero
		mem->dec_reg(reg_num);
		return get_left_arg();		// jump in another direction
	}
	}
	return -1;
}



Program::Program()
	: instr_amt(0)
	, instr_list()
{}

Program::Program(size_t size)
	: instr_amt(size)
	, instr_list(size)
{}

Program::Program(const Program& other)
	: instr_amt(other.get_instr_amt())
	, instr_list(other.get_instr_lst())
{}

int Program::get_instr_amt() const { return instr_amt; }

vector<Instruction*> Program::get_instr_lst() const { return instr_list; }

void Program::read_append_instructions(vector<Instruction*>& new_instr_list) 
{
	for (size_t i = 0; i < new_instr_list.size(); i++)
	{
		instr_list.push_back(new_instr_list[i]);
	}
}

void Program::show() 
{
	for (size_t i = 0; i < instr_list.size(); i++)
	{
		instr_list[i]->show();
	}
}

void Program::del_instr(int i) 
{
	if (!(0 <= (size_t)i && i < instr_list.size()))
	{
		// throw INDEX ERROR
	}
	instr_list.erase(instr_list.begin() + i);
	instr_amt--;
}

void Program::add_instr(Instruction new_instr) 
{
	Instruction *copy = new Instruction(new_instr);	// CHECK WILL IT WORK!!!!!(seems like it is lul)
	instr_list.push_back(copy);
	instr_amt++;
}

void Program::change_inst(int i, Instruction new_instr) 
{
	Instruction *copy = new Instruction(new_instr);
	if (!(0 <= (size_t)i && i < instr_list.size()))
	{
		// throw INDEX ERROR
	}
	delete[] instr_list[i];
	instr_list[i] = copy;
}

bool Program::is_correct() 
{
	for (size_t i = 0; i < instr_list.size(); i++)
	{
		if (instr_list[i]->get_instr_type() == Instruction::INS_END)
		{
			return true;
		}
		return false;
	}
}





MinskyAutomata::MinskyAutomata()
	: program_lst()
	, mem(new Memory(10))
	, cur_program(0)
	, cur_state(0)
{}

MinskyAutomata::MinskyAutomata(int reg_amt)
	: program_lst()
	, mem(new Memory(reg_amt))
	, cur_program(0)
	, cur_state(0)
{}

void MinskyAutomata::add_program(Program new_program) 
{
	Program *copy = new Program(new_program);
	program_lst.push_back(copy);
}

void MinskyAutomata::del_program(int index) 
{
	if (index == cur_program)
	{
		cur_program = 0;
	}
	program_lst.erase(program_lst.begin() + index);
}

void MinskyAutomata::exec_program(int program_indx) 
{
	if (!(program_lst[program_indx]->is_correct()))
	{
		// throw SYNTAX ERROR
	}
	cur_program = program_indx;
	cur_state = 1;
	vector<Instruction*> instrs = program_lst[program_indx]->get_instr_lst();
	while (cur_state != -1)
	{
		cur_state = instrs[cur_state - 1]->exec(mem);
	}
}

vector<int> MinskyAutomata::get_regs() { return  mem->get_regs(); }

void MinskyAutomata::add_instruction_to_program(int program_indx, Instruction new_instr) 
{
	program_lst[program_indx]->add_instr(new_instr);
}

void MinskyAutomata::set_zero(int i)
{
	mem->set_zero(i);
}

void MinskyAutomata::set_n(int index, int n)
{
	mem->set_n(index, n);
}



