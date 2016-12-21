#ifndef __ADDITIONAL_HPP__
#define __ADDITIONAL_HPP__

#include <algorithm>
#include <assert.h>
#include <iostream>

namespace finite_additional {
	std::string state_code(std::vector<size_t>& states){

		size_t length = *(std::max_element(states.begin(), states.end()));
		std::string s(length+1, '0');
		for (size_t i = 0; i < states.size(); i++)
			s[states[i]] = '1';
/*
		if (states.size() > 0){
		for (int i=0; i<states.size(); i++)
			std::cerr << states[i] << " ";		
		std::cerr << "-- " <<  s << std::endl;
		}
*/
		return s;
	}

	std::vector<size_t> state_from_code(std::string s){
		std::vector<size_t> states;
		for (size_t i = 0; i < s.length(); i++)
			if (s[i] == '1')
				states.push_back(i);
		return states;
	}

};


#endif
