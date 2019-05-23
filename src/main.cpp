/*
(MinskyAuto)
	Автоматом Мінського називається математична машина, що є алгоритмічно еквівалентною машині Тьюрінга та Поста,
але більш наближена до реальної комп’ютерної програми. Вона складається з набору регістрів, що зберігають цілі числа та набору інструкцій,
які бувають 3 видів:
	а) кінець програми,
	б) до вказаного (за даним номером і) регістру додається 1 та робиться перехід на іншу інструкцію А (що задана своїм номером n),
	в) з вказаного регістру і віднімається 1 та робиться перехід на іншу інструкцію А(що задана своїм номером n),
		якщо значення цього регістру стає 0 або здійснюється перехід на іншу інструкцію В(що задана своїм номером m) в іншому випадку.

Створити наступні класи:

Клас Data: Рядок str, кількість байтів в даних num_bytes,
Методи класу: ініціалізація, введення/виведення даних read()/write(), обнулити дані set_zero(), додати до існуючих даних нові дані add_data(),
				замінити дані за номером байту change().

Клас Пам'ять (MemAuto) – складається з кількості регістрів (num_reg), вектору цілих значень цих регістрів (reg_list), cur_num .
Методи класу: ініціалізація регістрів 0-ми, запис даних в порожні регістри set_data (з класу Дані),
			  обнулити регістри () set_zero(), вивести вміст регістрів write(), додати до існуючих даних нові значення
			  (цілі та з класу Дані) add_data()…

Клас інструкція Instruction: перерахування Тип instr_type(stop=0,1,2), Номер регістру reg, Номер інструкції Instr1, Номер інструкції Instr2.
Методи класу: ініціалізація, введення інструкції read(), вивести номер регістру get_numreg(), отримати Instr1/Instr2 get_instr1()/get_instr2(), показати інструкцію write().

Клас Програма ProgList: список інструкцій в програмі plist[], кількість інструкцій num_instr.
Методи класу: ініціалізація, введення/виведення інструкцій read()/write(), видалити інструкції за номерами del_instr(int i), додати до існуючих нові інструкцій add_instr(), замінити інструкцію за її номером change(), базова перевірка коректності (вона повинна мати (1?) інструкцію типу stop, що є досяжною).

Клас АвтоматМінского MinskyAuto: складається з класу Пам'ять mem:MemAuto, класу Список Інструкцій plist: ProgList, номер поточної інструкції state…
Методи класу: ініціалізація, записати дані, додати дані, змінити дані, вивести стан регістрів, Записати список програм, додати інструкцію до списку,
				видалити команду зі списку, поміняти команду в списку, виконати програму за даним номером, виконати програму (починаючи з першої інструкції списку).
				*/


/*
# COPY REG A TO REG B USING REG C, AND CLEAR B

i-1 : DEC_JNZ B, i-1, i		-- clear B
i	: DEC_JNZ A, i+1, i+3	-- remove A, raise B and C
i+1 : INC_JMP B, i+2
i+2 : INC_JMP C, i
i+3 : DEC_JNZ B, i+4, i+5	-- remove B, raise A back
i+4 : INC_JMP A, i+3
i+5 : END
*/


#include "../headers/7Kovalenko.hpp"
#include "../headers/compiler.hpp"


using namespace std;


/*Program* source_to_program(char* path)
{
	CompiledSource* program_src = parse_file_to_instructions(path);

}*/

MinskyAutomata* compiled_src_to_auto(CompiledSource* cmp)
{
	MinskyAutomata *new_automaton = new MinskyAutomata(cmp->reg_amt);
	Program *new_program = new Program;
	new_program->read_append_instructions(cmp->instructions);
	for (int i = 0; i < cmp->reg_list.size(); i++)
	{
		new_automaton->set_n(i, cmp->reg_list[i]);
	}
	new_automaton->add_program(*new_program);
	return new_automaton;
}


int main(int argc, char **argv)
{
	/*MinskyAutomata *aut = new MinskyAutomata;
	Program *prog = new Program;
	int i = 1;
	int DEC_JNZ = Instruction::INS_DECJNZ;
	int INC_JMP = Instruction::INS_INCJMP;
	int END = Instruction::INS_END;
	// A = 0; B = 1; C = 2
	Instruction *cur_inst1 = new Instruction( 1, i - 1, DEC_JNZ, i - 1, i    );
	Instruction *cur_inst2 = new Instruction( 0, i,     DEC_JNZ, i + 1, i + 3);
	Instruction *cur_inst3 = new Instruction( 1, i + 1, INC_JMP, i + 2, -1   );
	Instruction *cur_inst4 = new Instruction( 2, i + 2, INC_JMP, i,	   -1    );
	Instruction *cur_inst5 = new Instruction( 1, i + 3, DEC_JNZ, i + 4, i + 5);
	Instruction *cur_inst6 = new Instruction( 0, i + 4, INC_JMP, i + 3, -1   );
	Instruction *cur_inst7 = new Instruction(-1, i + 5, END,    -1,     -1   );
	vector<Instruction*> vec;
	vec.push_back(cur_inst1);
	vec.push_back(cur_inst2);
	vec.push_back(cur_inst3);
	vec.push_back(cur_inst4);
	vec.push_back(cur_inst5);
	vec.push_back(cur_inst6);
	vec.push_back(cur_inst7);
	prog->read_append_instructions(vec);
	aut->add_program(*prog);
	aut->set_n(0, 3);
	vector<int> v;
	v = aut->get_regs();
	print_vector(v);
	aut->exec_program(0);
	v = aut->get_regs();
	print_vector(v);*/
	//vector<string> str_vec = parse_instruction("     abc def ghw      ");
	CompiledSource* cmp = 
		parse_file_to_instructions(
		(char *)"E:\\UserData\\CppScripts\\study_projs\\app2\\minsky_machine\\minsky_machine_programs\\prog1.txt");
	MinskyAutomata* aut = compiled_src_to_auto(cmp);
	aut->exec_program(0);
	vector<int> v = aut->get_regs();
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ' ';
	}
	return 0;
}