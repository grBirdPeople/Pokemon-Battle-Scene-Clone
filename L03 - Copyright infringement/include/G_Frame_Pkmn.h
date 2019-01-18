#pragma once

#include "G_Frame.h"

class G_Menu;



class G_Frame_Pkmn : virtual public G_Frame
{
public:
			 G_Frame_Pkmn				(Manager& man);
	virtual	~G_Frame_Pkmn				();

			void		build_menu		(Manager& man);

	virtual	G_Frame*	handle_input	(Manager& man)							override;
	virtual void		update			(const float deltaT, Manager& man)		override;
	virtual void		render			(sf::RenderWindow& rWin, Manager& man)	override;

private:
	unsigned short	txt_scale_;
	float			x_offset_;

	unsigned short	current_pkmn_type_,
					current_arrow_pos_;

	G_Menu*			g_menu_;
};
