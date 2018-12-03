#include "parse.h"
#include "graph.h"

parser::parser(lex_data const & d, grammar & g) :data(d) ,grm(g) {

#define _GRAMMAR_ASSIGN_ACT(str,code) \
	grm.assign_action(str, [&](int now)) code

}

bool parser::parse(grammar const& grm, int pro_s) {
	auto &exps = grm[pro_s];
	int right = now, has_eps = false;
	std::cout << grm.get_name(pro_s) << ": " << std::endl;
	for (auto&& exp : exps) {
		if (now >= data.lex_result.size())return true;
		std::cout << "-- \t";
		for (auto &&xi : exp) {
			std::cout << grm.get_name(xi) << " ";
		}
		std::cout << std::endl;
		int prev = now;
		bool good = true, sub_good = true, has_sub = false;
		if (exp.size() != 0) for (auto &&xi : exp) {
			
			if (grm.is_terminator(xi)) {
				std::cout << "-------T " << grm.get_name(xi) << " "
					<< token_name[grm.terminator(xi)] << " "
					<< token_name[data.get_token(now)] << std::endl;

				if (grm.terminator(xi) == data.get_token(now)) {
					std::cout << "-------SELECT "
						<< grm.get_name(xi) << " "
						<< token_name[data.get_token(now)] << " >>-" << now << std::endl;
					now++;
				} else {
					good = false;
					break;
					//return false;
				}
			} else if(!grm.is_semantic_action(xi)){
				has_sub = true;
				sub_good = sub_good&& parse(grm, xi);
			}
		}
		if (has_sub)good = good && sub_good;
		if (pro_s == grm.id_s) good = good && (now == data.lex_result.size());
		if (good)return true; else now = prev;
	}
	//if (pro_s == grm.id_s)return true;
	return false;
}