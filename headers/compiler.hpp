#ifndef __MINSKY_COMPILER_HPP__
#define __MINSKY_COMPILER_HPP__


#include "7Kovalenko.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>



class CompiledSource
{
public:
	CompiledSource();
	CompiledSource(int, std::vector<int>);
	void append_instruction(Instruction *new_instr);
	int reg_amt;
	std::vector<int> reg_list;
	std::vector<Instruction*> instructions;
};


Instruction* parse_instruction(std::string str_instruction);

CompiledSource* parse_file_to_instructions(char* filename);


#endif