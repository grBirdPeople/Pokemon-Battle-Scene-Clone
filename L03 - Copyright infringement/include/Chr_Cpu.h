#pragma once

#include "Chr.h"
#include "Chr_Pkmn.h"



class Chr_Cpu : virtual public Chr
{
public:
			 Chr_Cpu(const vec2f& p1DefaultPos);
	virtual	~Chr_Cpu();

			bool						get_current_pkmn_died	();
			unsigned short				get_current_pkmn		();
			Chr_Pkmn&					get_pkmn				(short pkmn);
			std::map<short, Chr_Pkmn*>&	get_pkmn_map			();
	signed	short						get_pkmns_size			();

			void						set_current_pkmn_died	(const bool died);
			void						set_current_pkmn		(const unsigned short pkmnType);

			void						randomise_new_current_pkmn	();

	virtual void						update					(const float deltaT) override;

private:
				bool	current_pkmn_died_;

	signed		short	pkmns_size_;
	unsigned	short	current_pkmn_type_;

	std::vector<unsigned short>	m_pkmns_alive_;
	std::map<short, Chr_Pkmn*>	m_pkmn_;
};
