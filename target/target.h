#pragma once
#include "../lex/lex.h"
#include "../parse/type.h"

struct target {
	lex_data const & data;//���ֱ�����������������
	symbols & sym;
	std::string dseg;
	std::string cseg_begin;
	std::string cseg;
	std::string cseg_end;
	std::map<int,std::string> id_name;
	void work();//����Ŀ�����
	void init_of_var(int id, int id_to_init);
	std::string name_of(int id, scope::handle_scope h_curr);//ͨ��id��ȡ��������
	target(lex_data const& d, symbols & sy);
	std::string assembly(){//���������
		return dseg + cseg_begin + cseg + cseg_end;
	}
};
