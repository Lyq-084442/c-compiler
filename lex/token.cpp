#include "token.h"
#include "lex.h"

regex_table::regex_table() :table{
	make_pair(std::regex(R"QWERTY(typedef)QWERTY"),token::toktypedef),
	make_pair(std::regex(R"QWERTY(void)QWERTY"),token::tokvoid),
	make_pair(std::regex(R"QWERTY(const)QWERTY"),token::tokconst),
	make_pair(std::regex(R"QWERTY(char)QWERTY"),token::tokchar),
	make_pair(std::regex(R"QWERTY(int)QWERTY"),token::tokint),
	make_pair(std::regex(R"QWERTY(unsigned)QWERTY"),token::tokunsigned),
	make_pair(std::regex(R"QWERTY(short)QWERTY"),token::tokshort),
	make_pair(std::regex(R"QWERTY(long)QWERTY"),token::toklong),
	make_pair(std::regex(R"QWERTY(float)QWERTY"),token::tokfloat),
	make_pair(std::regex(R"QWERTY(double)QWERTY"),token::tokdouble),
	make_pair(std::regex(R"QWERTY(sizeof)QWERTY"),token::toksizeof),
	make_pair(std::regex(R"QWERTY(struct)QWERTY"),token::tokstruct),
	make_pair(std::regex(R"QWERTY(enum)QWERTY"),token::tokenum),
	make_pair(std::regex(R"QWERTY(union)QWERTY"),token::tokunion),
	make_pair(std::regex(R"QWERTY(if)QWERTY"),token::tokif),
	make_pair(std::regex(R"QWERTY(else)QWERTY"),token::tokelse),
	make_pair(std::regex(R"QWERTY(do)QWERTY"),token::tokdo),
	make_pair(std::regex(R"QWERTY(for)QWERTY"),token::tokfor),
	make_pair(std::regex(R"QWERTY(while)QWERTY"),token::tokwhile),
	make_pair(std::regex(R"QWERTY(return)QWERTY"),token::tokreturn),
	make_pair(std::regex(R"QWERTY(goto)QWERTY"),token::tokgoto),
	make_pair(std::regex(R"QWERTY(switch)QWERTY"),token::tokswitch),
	make_pair(std::regex(R"QWERTY(case)QWERTY"),token::tokcase),
	make_pair(std::regex(R"QWERTY(default)QWERTY"),token::tokdefault),
	make_pair(std::regex(R"QWERTY(break)QWERTY"),token::tokbreak),
	make_pair(std::regex(R"QWERTY(continue)QWERTY"),token::tokcontinue),
	make_pair(std::regex(R"QWERTY(auto)QWERTY"),token::tokauto),
	make_pair(std::regex(R"QWERTY(extern)QWERTY"),token::tokextern),
	make_pair(std::regex(R"QWERTY(static)QWERTY"),token::tokstatic),
	make_pair(std::regex(R"QWERTY(pragma)QWERTY"),token::tokpragma),
	make_pair(std::regex(R"QWERTY(include)QWERTY"),token::tokinclude),
	make_pair(std::regex(R"QWERTY(define)QWERTY"),token::tokdefine),
	make_pair(std::regex(R"QWERTY(undef)QWERTY"),token::tokundef),
	make_pair(std::regex(R"QWERTY(ifdef)QWERTY"),token::tokifdef),
	make_pair(std::regex(R"QWERTY(elif)QWERTY"),token::tokelif),
	make_pair(std::regex(R"QWERTY(endif)QWERTY"),token::tokendif),
	make_pair(std::regex(R"QWERTY(-?[0-9]+((\.[0-9]+)([eE]-?[0-9]+)|(\.[0-9]+)|([eE]-?[0-9]+))[fF]?)QWERTY"),token::double_literal),
	make_pair(std::regex(R"QWERTY(-?(0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2})QWERTY"),token::int_literal),
	make_pair(std::regex(R"QWERTY('.')QWERTY"),token::char_literal),
	make_pair(std::regex(R"QWERTY(".*")QWERTY"),token::string_literal),
	make_pair(std::regex(R"QWERTY(<[a-zA-Z_\]+(\.[a-zA-Z_\]+)?>)QWERTY"),token::include_file),
	make_pair(std::regex(R"QWERTY([a-zA-Z_][0-9a-zA-Z_]*)QWERTY"),token::identifier),
	make_pair(std::regex(R"QWERTY(\+\+)QWERTY"),token::inc),
	make_pair(std::regex(R"QWERTY(--)QWERTY"),token::dec),
	make_pair(std::regex(R"QWERTY(\+=)QWERTY"),token::addass),
	make_pair(std::regex(R"QWERTY(-=)QWERTY"),token::subass),
	make_pair(std::regex(R"QWERTY(\*=)QWERTY"),token::mulass),
	make_pair(std::regex(R"QWERTY(/=)QWERTY"),token::divass),
	make_pair(std::regex(R"QWERTY(%=)QWERTY"),token::modass),
	make_pair(std::regex(R"QWERTY(<<=)QWERTY"),token::shlass),
	make_pair(std::regex(R"QWERTY(>>=)QWERTY"),token::shrass),
	make_pair(std::regex(R"QWERTY(\|=)QWERTY"),token::orass),
	make_pair(std::regex(R"QWERTY(&=)QWERTY"),token::andass),
	make_pair(std::regex(R"QWERTY(\^=)QWERTY"),token::xorass),
	make_pair(std::regex(R"QWERTY(==)QWERTY"),token::equal),
	make_pair(std::regex(R"QWERTY(\|\|)QWERTY"),token::lor),
	make_pair(std::regex(R"QWERTY(&&)QWERTY"),token::land),
	make_pair(std::regex(R"QWERTY(!=)QWERTY"),token::nequal),
	make_pair(std::regex(R"QWERTY(<=)QWERTY"),token::lequal),
	make_pair(std::regex(R"QWERTY(>=)QWERTY"),token::gequal),
	make_pair(std::regex(R"QWERTY(<<)QWERTY"),token::shl),
	make_pair(std::regex(R"QWERTY(>>)QWERTY"),token::shr),
	make_pair(std::regex(R"QWERTY(\.)QWERTY"),token::point),
	make_pair(std::regex(R"QWERTY(->)QWERTY"),token::arrow),
	make_pair(std::regex(R"QWERTY(\.{3})QWERTY"),token::tokellipsis),
	make_pair(std::regex(R"QWERTY(##)QWERTY"),token::hashhash),
	make_pair(std::regex(R"QWERTY(#)QWERTY"),token::hash),
	make_pair(std::regex(R"QWERTY(;)QWERTY"),token::semicolon),
	make_pair(std::regex(R"QWERTY(:)QWERTY"),token::colon),
	make_pair(std::regex(R"QWERTY(\?)QWERTY"),token::question),
	make_pair(std::regex(R"QWERTY(\{)QWERTY"),token::lbrace),
	make_pair(std::regex(R"QWERTY(\})QWERTY"),token::rbrace),
	make_pair(std::regex(R"QWERTY(\[)QWERTY"),token::lbracket),
	make_pair(std::regex(R"QWERTY(\])QWERTY"),token::rbracket),
	make_pair(std::regex(R"QWERTY(\()QWERTY"),token::lparenthesis),
	make_pair(std::regex(R"QWERTY(\))QWERTY"),token::rparenthesis),
	make_pair(std::regex(R"QWERTY(\+)QWERTY"),token::add),
	make_pair(std::regex(R"QWERTY(-)QWERTY"),token::sub),
	make_pair(std::regex(R"QWERTY(\*)QWERTY"),token::mul),
	make_pair(std::regex(R"QWERTY(/)QWERTY"),token::div),
	make_pair(std::regex(R"QWERTY(%)QWERTY"),token::mod),
	make_pair(std::regex(R"QWERTY(!)QWERTY"),token::not),
	make_pair(std::regex(R"QWERTY(~)QWERTY"),token::bnot),
	make_pair(std::regex(R"QWERTY(&)QWERTY"),token::band),
	make_pair(std::regex(R"QWERTY(\|)QWERTY"),token::bor),
	make_pair(std::regex(R"QWERTY(\^)QWERTY"),token::bxor),
	make_pair(std::regex(R"QWERTY(>)QWERTY"),token::greater),
	make_pair(std::regex(R"QWERTY(<)QWERTY"),token::less),
	make_pair(std::regex(R"QWERTY(=)QWERTY"),token::assign),
	make_pair(std::regex(R"QWERTY(,)QWERTY"),token::comma),
	make_pair(std::regex(R"QWERTY([\r\n\t\s]+)QWERTY"),token::whitespace)


} {}
token_name_type::token_name_type() {
	_name.emplace(token::toktypedef, "toktypedef");
	_name.emplace(token::tokvoid, "tokvoid");
	_name.emplace(token::tokconst, "tokconst");
	_name.emplace(token::tokchar, "tokchar");
	_name.emplace(token::tokint, "tokint");
	_name.emplace(token::tokunsigned, "tokunsigned");
	_name.emplace(token::tokshort, "tokshort");
	_name.emplace(token::toklong, "toklong");
	_name.emplace(token::tokfloat, "tokfloat");
	_name.emplace(token::tokdouble, "tokdouble");
	_name.emplace(token::toksizeof, "toksizeof");
	_name.emplace(token::tokstruct, "tokstruct");
	_name.emplace(token::tokenum, "tokenum");
	_name.emplace(token::tokunion, "tokunion");
	_name.emplace(token::tokif, "tokif");
	_name.emplace(token::tokelse, "tokelse");
	_name.emplace(token::tokdo, "tokdo");
	_name.emplace(token::tokfor, "tokfor");
	_name.emplace(token::tokwhile, "tokwhile");
	_name.emplace(token::tokreturn, "tokreturn");
	_name.emplace(token::tokgoto, "tokgoto");
	_name.emplace(token::tokswitch, "tokswitch");
	_name.emplace(token::tokcase, "tokcase");
	_name.emplace(token::tokdefault, "tokdefault");
	_name.emplace(token::tokbreak, "tokbreak");
	_name.emplace(token::tokcontinue, "tokcontinue");
	_name.emplace(token::tokauto, "tokauto");
	_name.emplace(token::tokextern, "tokextern");
	_name.emplace(token::tokstatic, "tokstatic");
	_name.emplace(token::tokpragma, "tokpragma");
	_name.emplace(token::tokinclude, "tokinclude");
	_name.emplace(token::tokdefine, "tokdefine");
	_name.emplace(token::tokundef, "tokundef");
	_name.emplace(token::tokifdef, "tokifdef");
	_name.emplace(token::tokelif, "tokelif");
	_name.emplace(token::tokendif, "tokendif");
	_name.emplace(token::double_literal, "double_literal");
	_name.emplace(token::int_literal, "int_literal");
	_name.emplace(token::char_literal, "char_literal");
	_name.emplace(token::string_literal, "string_literal");
	_name.emplace(token::include_file, "include_file");
	_name.emplace(token::identifier, "identifier");
	_name.emplace(token::inc, "inc");
	_name.emplace(token::dec, "dec");
	_name.emplace(token::addass, "addass");
	_name.emplace(token::subass, "subass");
	_name.emplace(token::mulass, "mulass");
	_name.emplace(token::divass, "divass");
	_name.emplace(token::modass, "modass");
	_name.emplace(token::shlass, "shlass");
	_name.emplace(token::shrass, "shrass");
	_name.emplace(token::orass, "orass");
	_name.emplace(token::andass, "andass");
	_name.emplace(token::xorass, "xorass");
	_name.emplace(token::equal, "equal");
	_name.emplace(token::lor, "lor");
	_name.emplace(token::land, "land");
	_name.emplace(token::nequal, "nequal");
	_name.emplace(token::lequal, "lequal");
	_name.emplace(token::gequal, "gequal");
	_name.emplace(token::shl, "shl");
	_name.emplace(token::shr, "shr");
	_name.emplace(token::point, "point");
	_name.emplace(token::arrow, "arrow");
	_name.emplace(token::tokellipsis, "tokellipsis");
	_name.emplace(token::hashhash, "hashhash");
	_name.emplace(token::hash, "hash");
	_name.emplace(token::semicolon, "semicolon");
	_name.emplace(token::colon, "colon");
	_name.emplace(token::question, "question");
	_name.emplace(token::lbrace, "lbrace");
	_name.emplace(token::rbrace, "rbrace");
	_name.emplace(token::lbracket, "lbracket");
	_name.emplace(token::rbracket, "rbracket");
	_name.emplace(token::lparenthesis, "lparenthesis");
	_name.emplace(token::rparenthesis, "rparenthesis");
	_name.emplace(token::add, "add");
	_name.emplace(token::sub, "sub");
	_name.emplace(token::mul, "mul");
	_name.emplace(token::div, "div");
	_name.emplace(token::mod, "mod");
	_name.emplace(token::not, "not");
	_name.emplace(token::bnot, "bnot");
	_name.emplace(token::band, "band");
	_name.emplace(token::bor, "bor");
	_name.emplace(token::bxor, "bxor");
	_name.emplace(token::greater, "greater");
	_name.emplace(token::less, "less");
	_name.emplace(token::assign, "assign");
	_name.emplace(token::comma, "comma");
	_name.emplace(token::whitespace, "whitespace");
}

token_name_type token_name;

std::vector<token_pair>
lex(std::string const& s) {
	static regex_table reg;
	std::vector<token_pair > res;
	auto it = s.begin();
	while (it != s.end()) {
		bool unsucc = true;
		for (auto& e : reg.table) {
			std::smatch m;
			if (std::regex_search(it, s.end(), m, e.first,
				std::regex_constants::match_continuous)) {
				std::string str = m[0].str();
				if (e.second != token::whitespace)res.emplace_back(e.second, str);
				//std::cerr << token_name[e.second] << " \"" << str <<"\""<< std::endl;
				it += str.size();
				unsucc = false; break;
			}
		}
		if (unsucc) {
			while (it != s.end())std::cout << *it++;
			throw("REJECTED!");
		}
	}
	for (auto m : res) {
		std::cerr << "{" << token_name[m.first] << " ,\"" << m.second << "\"},";
	}
	return res;
}