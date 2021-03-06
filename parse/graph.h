#pragma once
#include "../lex/lex.h"
#include "../basic/bin_tree.h"
#include "../error/error.h"
//

std::string get_name_of_now(int now, lex_data const & data);
std::string get_type_name(int now, lex_data const &data);

struct grammar {
	using product_reference = std::pair<int, int>;
	using production = std::vector<int>;
	bool ll1_table_product_cmp(product_reference const& a, product_reference const &b);
public:
	using semantic_action = std::function<void(int,int)>;
	using ll1_table_pred = std::pair<int, token>;
	using ll1_table_item = std::set<std::pair<int, int>,
		std::function<bool (grammar::product_reference const& , grammar::product_reference const &)>>;
	struct ll1_stack_element {
		int id;
		//int now;
		operator int()const { return id; }
		ll1_stack_element() = default;
		ll1_stack_element(int _id) :id(_id){}
		ll1_stack_element(ll1_stack_element&& rhs) = default;
		ll1_stack_element(ll1_stack_element const& rhs) = default;
		ll1_stack_element& operator= (ll1_stack_element const& rhs) = default;
	};

private:
	static std::string literals[];
	std::map<std::string, int> mp;
	const std::map < std::string, token > token_map;
	std::vector<std::string> rev_mp;
	std::map<std::string,semantic_action > action;
	std::map<int, std::vector<production>> productions;
	std::map<std::pair<int, int>, int> prod_index;
	std::map<int, std::set<int>> first_set;
	std::map<int, std::set<int>> follow_set;
	std::map<ll1_table_pred, ll1_table_item>ll1_table;
	int last_error_token, expected;
	template<class It>
	std::set<int> first_set_of_prod(It begin,It end) {
		std::set<int> ans;
		if(begin==end) {
			return { id_eps };
		}
		bool fucking_good = false;
		for (; begin != end;++begin) {
			bool good = true;
			if (is_semantic_action(*begin))continue;
			if (first_set[*begin].empty()) {
				continue;
			} else for (auto && x : first_set[*begin]) {
				if (x != id_eps) {
					ans.insert(x);
				} else { good = false; }
			}
			if (good) {
				fucking_good = true;
				break;
			}
		}
		if (!fucking_good)ans.insert(id_eps);
		return ans;
	}
	void cal_first();
	void cal_follow();
	int cal_prod_index(int S,production const& prod);
	/*std::set<int> first_set(int S, int prod) {
		for (auto &&Xi :productions[S][prod]) {
			if (first[Xi].empty())continue;
			if(first[Xi].size()==1&&first[Xi])
		}
	}*/
	void fill_ll1_table();
	ll1_table_item const* find_ll1(int top, token now) {
		auto it = ll1_table.find(std::make_pair(top, now));
		if (it != ll1_table.end())  return &it->second;
		return nullptr;
	}
	bool parse_ll1(lex_data const& data, 
		std::stack<ll1_stack_element> &sta, 
		int &now,int & now_id,int);
	
	int cnt;
	int get_tok(std::string const&s) {
		auto it = mp.find(s);
		if (it != mp.end())return it->second;
		rev_mp.push_back(s);
		mp.emplace(s, cnt++);
		return cnt - 1;
	}
	int get_tok(std::string const& s)const {
		auto it = mp.find(s);
		if (it != mp.end())return it->second;
		return -1;
	}
	void init(std::string const& s);
public:
	int id_eps, id_dummy, id_s,max_rec_cnt;
	std::string const& get_name(int t) const {
		return rev_mp[t];
	}
	grammar(std::string const& s);
	grammar(); 
	bool parse_ll1(lex_data const& data) {
		std::stack< ll1_stack_element> sta;
		sta.push(id_dummy);
		sta.push(id_s);
		max_rec_cnt = 0;
		int now = 0, now_act = 0; 
		bool result= parse_ll1(data, sta, now, now_act, 0);
		//std::cout << "MAX " << max_rec_cnt << std::endl;
		return result;
	}
	void debug();
	int add_symbol(std::string const& s) {
		int t = get_tok(s);
		productions[t].clear();
		return t;
	}
	void add_production(std::string const&s, std::vector<std::string> const&exp) {
		int S = get_tok(s);
		std::vector<int> vec;
		for (auto &&i : exp)vec.push_back(get_tok(i));
		productions[S].push_back(vec);
		prod_index[std::make_pair(S,productions[S].size()-1)]= cal_prod_index(S, vec);
	}
	
	void assign_action(std::string const& c, semantic_action &&act) {
		action.emplace(c, act);
	}

	void add_production(std::string const& s, std::initializer_list<std::string> && exp) {
		add_production(s, exp);
	}
	std::vector<std::vector<int>> const& operator[](std::string const&S)const {
		return this->operator[](get_tok(S));
	}
	std::vector<std::vector<int>> const& operator[](int S)const {
		static const std::vector<std::vector<int>> dummy;
		auto it = productions.find(S);
		if (it != productions.end())return it->second;
		return dummy;
	}
	token terminator(int i) const {
		return terminator(get_name(i));
	}
	bool is_terminator(int i) const {
		if (i == id_eps || i == id_dummy)return true;
		return is_terminator(get_name(i),false);
	}
	bool is_terminator(std::string const& s, bool outside_call=true) const {
		if (outside_call) {
			auto it = mp.find(s);
			if (it != mp.end())if (it->second == id_eps || it->second == id_dummy)return true;
		}
		if (s[0] == '\'')return true;
		return token_map.find(s) != token_map.end();
	}
	bool is_semantic_action(std::string const& s) const{
		return s.front() == '{';
	}
	bool is_semantic_action(int i) const{
		return is_semantic_action(get_name(i));
	}
	token terminator(std::string const&t) const {
		//std::cout << t << std::endl;
		auto it = token_map.find(t);
		if (it == token_map.end())return token::dummy;
		else return it->second;
	}

	void throw_last_error(lex_data& data) {
		std::string in_line = data.in_line_and_chr(last_error_token);
		in_line += " got '" + get_name_of_now(last_error_token, data) + "', expected ";
		in_line += get_name(expected);
		for(auto &&x:first_set[expected]) {
			if(id_eps==x) {
				for(auto &&y:follow_set[expected]) {
					in_line += get_name(y);
					in_line += " ";
				}
			} else {
				in_line += get_name(x);
				in_line += " ";
			}
		}
		throw parse_error(in_line);
	}
};