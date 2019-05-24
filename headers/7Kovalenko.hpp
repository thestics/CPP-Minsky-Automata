#ifndef __MINSKY_H__
#define __MINSKY_H__
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>


class Memory
{
public:
	Memory();
	Memory(int reg_amt);
	void set_zero(int);
	void set_n(int, int);
	int get_reg(int) const;
	std::vector<int> get_regs() const;
	void show();
	void add_reg();
	void inc_reg(int);
	void dec_reg(int);
	bool is_reg_zero(int);
	int get_reg_amount() const;
private:
	int reg_amount;
	std::vector<int> reg_list;
};


class Instruction
{
public:
	enum {INS_END, INS_INCJMP, INS_DECJNZ};
	Instruction();
	Instruction(const Instruction& other);
	Instruction(int, int, int, int, int);
	int get_reg_num() const;
	int get_instr_num() const;
	int get_instr_type() const;
	int get_left_arg() const;
	int get_right_arg() const;
	void show();
	int exec(Memory*);
private:
	int reg_num,		// affected register number
		instr_num,		// current instruction number
		instr_type,		// current instruction type
		left_arg,		// left argument of operation
		right_arg;		// right argument of operation
};


class Program
{
public:
	Program();
	Program(size_t);
	Program(const Program&);
	void read_append_instructions(std::vector<Instruction*>&);
	void show();
	void del_instr(int i);
	void add_instr(Instruction);
	void change_inst(int, Instruction);
	int get_instr_amt() const;
	std::vector<Instruction*> get_instr_lst() const;
	bool is_correct();
private:
	size_t instr_amt;
	std::vector<Instruction*> instr_list;
};


class MinskyAutomata
{
public:
	MinskyAutomata();
	MinskyAutomata(int);
	void add_program(Program);
	void del_program(int index);
	void exec_program(int);
	std::vector<int> get_regs();
	void add_instruction_to_program(int program_indx, Instruction);
	void set_zero(int);
	void set_n(int, int);
	Memory *mem;
private:
	std::vector<Program*> program_lst;
	int cur_program;
	int cur_state;
};

// project-specific exceptions

class UnknownInstructionTypeError : public exception
{
public:

	UnknownInstructionTypeError(int err_code, string details)
		: _err_code(err_code)
		, _details(details)
	{}

	virtual ~UnknownInstructionTypeError()
	{}

	virtual int get_err_code() const { return _err_code; }
	virtual string get_details() const { return _details; }

private:
	int _err_code;
	string _details;
};

class SyntaxError : public exception
{
public:

	SyntaxError(int err_code, string details)
		: _err_code(err_code)
		, _details(details)
	{}

	virtual ~SyntaxError()
	{}

	virtual int get_err_code() const { return _err_code; }
	virtual string get_details() const { return _details; }

private:
	int _err_code;
	string _details;
};

#endif