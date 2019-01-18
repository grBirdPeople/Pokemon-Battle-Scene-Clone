#include "../include/Chr_Player.h"



// cTor
Chr_Player::Chr_Player(const vec2f& p1DefaultPos)
	:
		Chr						(),			// Class inherits inits & other things from Chr cTor
		current_pkmn_died_		(false),
		pkmns_size_				(-1),
		current_pkmn_type_		(0)
{
	// Make pocketmans
	std::map<unsigned short, str> color	{	{e_PkmnType::BLUE,		"blue"},
											{e_PkmnType::GREEN,		"green"},
											{e_PkmnType::RED,		"red"},
											{e_PkmnType::YELLOW,	"yellow"} };

	for (unsigned short i = e_PkmnType::BLUE; i != e_PkmnType::END; i++)
	{
		m_pkmn_[i] = new Chr_Pkmn(color[i], vec2f(p1DefaultPos.x, p1DefaultPos.y), vec2f(6.0f, 6.0f));
		m_pkmn_[i]->set_stats(96.0f + static_cast<float>(i), 50.0f, 500.0f, 5.0f, 5.0f);

		++pkmns_size_;
	}
}



// dTor
Chr_Player::~Chr_Player()
{
	AUTO_DEL(pos_);
	AUTO_DEL(spr_origin_);
	AUTO_DEL(spr_scale_);
	AUTO_DEL(tex_);
	AUTO_DEL(spr_);
}



// get_current_pkmn_died
bool Chr_Player::get_current_pkmn_died()
{
	return current_pkmn_died_;
}



// get_current_pkmn
unsigned short Chr_Player::get_current_pkmn()
{
	return current_pkmn_type_;
}



// get_pkmn
Chr_Pkmn& Chr_Player::get_pkmn(short pkmn)
{
	return *m_pkmn_[pkmn];
}


// get_pkmn_map
std::map<short, Chr_Pkmn*>& Chr_Player::get_pkmn_map()
{
	return m_pkmn_;
}



// get_pkmns_size
signed short Chr_Player::get_pkmns_size()
{
	return pkmns_size_;
}



// set_current_pkmn_died
void Chr_Player::set_current_pkmn_died(const bool died)
{
	current_pkmn_died_ = died;

	if (current_pkmn_died_)
		--pkmns_size_;
}



// set_current_pkmn
void Chr_Player::set_current_pkmn(const unsigned short pkmnType)
{
	current_pkmn_type_ = pkmnType;
}



// update
void Chr_Player::update(const float deltaT)
{}
