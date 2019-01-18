#include "../include/Chr_Cpu.h"

#include <random>



// cTor
Chr_Cpu::Chr_Cpu(const vec2f& p1DefaultPos)
	:
		Chr						(),			// Class inherits inits & other things from Chr cTor
		current_pkmn_died_		(false),
		pkmns_size_				(-1),
		current_pkmn_type_		(0)
{
	// Make pocketmans
	std::map<unsigned short, str>	color{	{e_PkmnType::BLUE,		"blue"},
											{e_PkmnType::GREEN,		"green"},
											{e_PkmnType::RED,		"red"},
											{e_PkmnType::YELLOW,	"yellow"} };

	for (unsigned short i = e_PkmnType::BLUE; i != e_PkmnType::END; i++)
	{
		m_pkmn_[i] = new Chr_Pkmn(color[i], vec2f(p1DefaultPos.x, p1DefaultPos.y), vec2f(6.0f, 6.0f));
		m_pkmn_[i]->set_stats(96.0f + static_cast<float>(i), 50.0f, 1000.0f, 5.0f, 5.0f);

		++pkmns_size_;
	}
	
	// Weird thing which explanation I'm ashem of explaning
	// Used in set_current_pkmn_died()
	for (unsigned short i = 0; i < pkmns_size_ + 1; i++)
		m_pkmns_alive_.push_back(i);

	// Set new random pkmn
	randomise_new_current_pkmn();
}



// dTor
Chr_Cpu::~Chr_Cpu()
{
	AUTO_DEL(pos_);
	AUTO_DEL(spr_origin_);
	AUTO_DEL(spr_scale_);
	AUTO_DEL(tex_);
	AUTO_DEL(spr_);
}



// get_current_pkmn_died
bool Chr_Cpu::get_current_pkmn_died()
{
	return current_pkmn_died_;
}



// get_current_pkmn
unsigned short Chr_Cpu::get_current_pkmn()
{
	return current_pkmn_type_;
}



// get_pkmn
Chr_Pkmn& Chr_Cpu::get_pkmn(short pkmn)
{
	return *m_pkmn_[pkmn];
}


// get_pkmn_map
std::map<short, Chr_Pkmn*>& Chr_Cpu::get_pkmn_map()
{
	return m_pkmn_;
}



// get_pkmns_size
signed short Chr_Cpu::get_pkmns_size()
{
	return pkmns_size_;
}



// set_current_pkmn_died
void Chr_Cpu::set_current_pkmn_died(const bool died)
{
	current_pkmn_died_ = died;

	if (current_pkmn_died_)
	{
		for (size_t i = 0; i < m_pkmns_alive_.size(); i++)
		{
			if (m_pkmns_alive_[i] == get_current_pkmn())
				m_pkmns_alive_.erase(m_pkmns_alive_.begin() + i);
		}

		--pkmns_size_;
	}
}



// set_current_pkmn
void Chr_Cpu::set_current_pkmn(const unsigned short pkmnType)
{
	current_pkmn_type_ = pkmnType;
}



// randomise_current_pkmn
void Chr_Cpu::randomise_new_current_pkmn()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> ran(0, pkmns_size_);

	auto num = ran(mt);
	set_current_pkmn(m_pkmns_alive_[static_cast<unsigned short>(num)]);
}



// update
void Chr_Cpu::update(const float deltaT)
{}
