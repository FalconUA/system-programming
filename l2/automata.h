#ifndef __FINITE_AUTOMATA_H__
#define __FINITE_AUTOMATA_H__

#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include "additional.h"

namespace __check_operator_existance {
	struct no_eq {};
	struct no_lt {};
	struct no_pp {};
	template <typename T, typename Arg> no_lt operator< (const T&, const Arg&);
	template <typename T, typename Arg> no_eq operator== (const T&, const Arg&); 
	template <typename T, typename Arg> no_pp operator++ (const T&); 

	template <typename T, typename Arg = T>
	struct __smaller_exists { 
		enum { value = !std::is_same<decltype(*(T*)(0) < *(Arg*)(0)), no_lt>::value };
	};
	template <typename T, typename Arg = T>
	struct __equal_exists {
		enum { value = !std::is_same<decltype(*(T*)(0) == *(Arg*)(0)), no_eq>::value };
	};
	template <typename T>
	struct __increasement_exists {
		enum { value = !std::is_same<decltype( (*(T*)(0))++ ), no_pp>::value };
	};
};

namespace dm {

	template<typename symbol>
	class alphabet {
	protected:
		std::map<symbol, size_t> character;		

	public:
		alphabet() = delete;

		template <class forward_it>
		alphabet(forward_it a, forward_it z){
			for (forward_it it = a; it != z; it++)
				character.insert(std::pair<symbol, size_t>(*it, character.size()));	
		}

		alphabet(symbol a, symbol z){
			static_assert(__check_operator_existance::__increasement_exists<symbol>::value, 
				"Class 'set' requires its template type to have an implementation of 'operator==' method.");
			for (symbol i = a; i != z; i++)
				character.insert(std::pair<symbol, size_t>(i, character.size()));
		}


		std::vector<symbol> dump(){
			std::vector<symbol> result;
			for (typename std::map<symbol, size_t>::iterator it = character.begin(); 
					it != character.end(); it++)
				result.push_back(it->first);					
			return result;
		}

		size_t operator[] (symbol c){ return character[c]; }
		size_t size(){ return character.size(); };
	};

	template<typename symbol>
	class automaton;

	template<typename symbol>
	class nondeterministic_state {
	private:
		bool acceptable;
		size_t state_index = 0;
		std::string state_name = "";
		alphabet<symbol>& abc; 
		std::vector<std::vector<nondeterministic_state<symbol>*>> transition;	

	public:
		nondeterministic_state() = delete;
		nondeterministic_state(
				alphabet<symbol>& a, std::string name, size_t index, bool is_acceptable): 
				abc(a), state_name(name), state_index(index), acceptable(is_acceptable) {
			std::vector<nondeterministic_state<symbol>*> empty(0);
			transition.resize(abc.size(), std::vector<nondeterministic_state<symbol>*>(0));
		}		

		std::string name(){ return state_name; };
		bool add_transition(symbol c, nondeterministic_state<symbol>* state){
			std::vector<nondeterministic_state<symbol>*>& t = transition[abc[c]];
			for (int i=0; i<t.size(); i++)
				if (t[i]->index() == state->index() && t[i]->name() == state->name())
					return false;				
			t.push_back(state);
			return true;
		}
		bool is_acceptable(){ return acceptable; }
		std::vector<std::string> operator() (symbol c){
			std::vector<std::string> state_list;
			for (typename std::vector<nondeterministic_state<symbol>*>::iterator 
					it = transition[abc[c]].begin(); it != transition[abc[c]].end(); it++)
				state_list.push_back((*it)->state_name);
			return state_list;
		}
		size_t index(){ return state_index; };

		friend class automaton<symbol>;
		friend automaton<symbol> determinize(automaton<symbol>& a);
	};

	template<typename symbol>
	class automaton {
	private:
		alphabet<symbol>& abc;
		std::string entry;
		std::map<std::string, char> current_state;
		std::map<std::string, nondeterministic_state<symbol>> state;
	public:
		automaton() = delete;
		automaton(const automaton<symbol>& a): 
			abc(a.abc), current_state(a.current_state), state(a.state), entry(a.entry) {}

		automaton(alphabet<symbol>& a, std::string entry_name = "start"): abc(a), entry(entry_name) {
			add_state(entry);
			current_state[entry] = 1;
		}

		void reset(){
			current_state.clear();
			current_state[entry] = 1;
		}

		bool add_state(std::string state_name, bool acceptable=false){
			if (state.find(state_name) != state.end())
				return false;
			size_t newstate_index = state.size();
			state.insert(std::pair<std::string, nondeterministic_state<symbol>>(state_name, 
						nondeterministic_state<symbol>(abc, state_name, newstate_index, acceptable)));
		}

		bool change_acceptance(std::string state_name, bool acceptable){
			typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
				it = state.find(state_name);

			if (it == state.end())
				return false;

			it->second.acceptable = acceptable;
		}

		bool is_acceptable(){
			for (typename std::map<std::string, char>::iterator
				   	it = this->current_state.begin(); it != this->current_state.end(); it++){
				typename std::map<std::string, nondeterministic_state<symbol>>::iterator
					el = state.find(it->first);
				if (el != state.end())
					if (el->second.is_acceptable())
						return true;
			}
			return false;
		}

		bool add_transition(std::string state_a, std::string state_b, symbol c){
			typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
				it_a = state.find(state_a);
			typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
				it_b = state.find(state_b);

			if (it_a == state.end()){
				add_state(state_a);
				it_a = state.find(state_a);
			}
			
			if (it_b == state.end()){			
				add_state(state_b);
				it_b = state.find(state_b);
			}

			return it_a->second.add_transition(c, &it_b->second);
//			if (state.find(state_a) != state.end() && state.find(state_b) != state.end())
//				return state[state_a].add_transition(&state[state_b], c);
			return false;
		}

		template <class forward_it>
		bool add_transition(std::string state_a, std::string state_b, 
				forward_it a, forward_it z) {
			bool success = true;
			for (forward_it it = a; it != z; it++)
				success = success && add_transition(state_a, state_b, *it);
		}

		bool transition(symbol c){
			std::map<std::string, char> new_state;
			for (typename std::map<std::string, char>::iterator 
					it = current_state.begin(); it != current_state.end(); it++){
				typename std::map<std::string, nondeterministic_state<symbol>>::iterator
					el = state.find(it->first);
//				if (el != state.end())
//					std::cerr << "true!" << std::endl;

				std::vector<nondeterministic_state<symbol>*>& tran = el->second.transition[abc[c]];
				for (int i=0; i<tran.size(); i++)
					new_state[tran[i]->name()] = 1;
			}
			current_state = new_state;
			return is_acceptable();
		}

		bool operator() (symbol c){
			return transition(c);
		}

		automaton determinize(){	
			std::vector<std::string> id_map(state.size());
			for (typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
					it = this->state.begin(); it != this->state.end(); it++){
				id_map[it->second.index()] = it->first;	
			}
			std::vector<symbol> alphabet_dump = this->abc.dump();

			std::vector<size_t> state_list;
			typename std::map<std::string, nondeterministic_state<symbol>>::iterator start = 
				this->state.find(entry);
			//assert(start != this->state.end());

			state_list.push_back(start->second.index());

			// DFS
			std::string entry_state = finite_additional::state_code(state_list);
			automaton result(this->abc, entry_state);
			if (start->second.is_acceptable())
				result.change_acceptance(entry_state, true);

			std::map<std::string, bool> visited;
			visited[entry_state] = true;

			std::stack<std::string> dfs;
			dfs.push(entry_state);

			while (!dfs.empty()){
				std::string from_state = dfs.top();
				dfs.pop();

				std::vector<size_t> from_state_ids = finite_additional::state_from_code(from_state);

				for (typename std::vector<symbol>::iterator it = alphabet_dump.begin(); 
						it != alphabet_dump.end(); it++){

					state_list.clear();
					bool next_is_acceptable = false;
			
					std::vector<size_t> state_grid(this->state.size(), 0);
					for (size_t i=0; i<from_state_ids.size(); i++){
						std::string tmp_name = id_map[from_state_ids[i]];

						typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
							tmp_state = this->state.find(tmp_name);
						//assert(start != this->state.end());

						std::vector<nondeterministic_state<symbol>*>& tran =
							tmp_state->second.transition[abc[*it]];
						for (size_t j=0; j<tran.size(); j++){
							state_grid[tran[j]->index()] = 1;
							next_is_acceptable = next_is_acceptable || tran[j]->is_acceptable();
						}
					}

					for (size_t i=0; i<state_grid.size(); i++)
						if (state_grid[i] == 1)
							state_list.push_back(i);

					std::string next_state = finite_additional::state_code(state_list);

					if (state_list.size() != 0){
						result.add_transition(from_state, next_state, *it);
						if (next_is_acceptable)
							result.change_acceptance(next_state, true);
					
						if (visited.find(next_state) == visited.end()) {
							visited[next_state] = true;
							dfs.push(next_state);
						}
					}
				}
			}
			return result;
		}

		void export_data(std::ostream& output){
			std::vector<symbol> alphabet_dump = this->abc.dump();
			for (int i=0; i<alphabet_dump.size(); i++)
				output << alphabet_dump[i] << " ";
			output << std::endl;

			output << this->entry << std::endl;
			for (typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
					it = this->state.begin(); it != this->state.end(); it++)
				if (it->second.is_acceptable())
					output << it->first << " ";
			output << std::endl;

			for (typename std::map<std::string, nondeterministic_state<symbol>>::iterator 
					it = this->state.begin(); it != this->state.end(); it++)
				for (int i=0; i<alphabet_dump.size(); i++){
					std::vector<nondeterministic_state<symbol>*> tran =
						it->second.transition[abc[alphabet_dump[i]]];
					for (int j=0; j<tran.size(); j++)
						output << it->first << " " << tran[j]->name() << " " << 
							alphabet_dump[i] << std::endl;
				}
		}

	};

	void import_data(std::istream& input){}
};


#endif
