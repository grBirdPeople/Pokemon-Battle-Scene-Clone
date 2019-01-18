#pragma once

#include "Chr.h"
#include "Chr_Pkmn.h"



class Chr_Player : virtual public Chr
{
public:
			 Chr_Player(const vec2f& p1DefaultPos);
	virtual	~Chr_Player();

			bool						get_current_pkmn_died	();
			unsigned short				get_current_pkmn		();
			Chr_Pkmn&					get_pkmn				(short pkmn);
			std::map<short, Chr_Pkmn*>&	get_pkmn_map			();
	signed	short						get_pkmns_size			();

			void						set_current_pkmn_died	(const bool died);
			void						set_current_pkmn		(const unsigned short pkmnType);

	virtual void						update					(const float deltaT) override;

private:
				bool	current_pkmn_died_;

	signed		short	pkmns_size_;
	unsigned	short	current_pkmn_type_;

	std::map<short, Chr_Pkmn*>	m_pkmn_;
};
