
#include <iostream>
#include <numeric>
#include <sstream>
#include <map>
#include <vector>
#include "automata.h"
#include "additional.h"

int main(){
	std::ofstream out("output.txt");
	if (!out.is_open()){
		std::cerr << "cannot find that file" << std::endl;
		return 0;
	}

	std::vector<char> symbols('z'-'a'+1);
	std::iota(symbols.begin(), symbols.end(), 'a');
	dm::alphabet<char> abc(symbols.begin(), symbols.end());

	dm::automaton<char> a(abc);
	a.add_transition("start", "middle1", 'c');
	a.add_transition("start", "middle2", 'c');
	a.add_transition("middle1", "finish", 'f');	
	a.add_transition("middle2", "finish", 'd');
	a.add_transition("finish", "dno1", 'b');
	a.add_transition("finish", "dno2", 'b');
	a.change_acceptance("finish", true);

	dm::automaton<char> b = a.determinize();

	b.export_data(out);
	

//	dm::automaton<char> b(a.determinize());

	out.close();
	return 0;
}
