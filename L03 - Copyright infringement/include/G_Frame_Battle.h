#pragma once

#include "G_Frame.h"

class G_Menu;



class G_Frame_Battle : virtual public G_Frame
{
public:
			 G_Frame_Battle				(Manager& man);
	virtual	~G_Frame_Battle				();

			void		build_menu		(Manager& man);
			void		txt_player		(Manager& man);
			void		txt_cpu			(Manager& man);

	virtual	G_Frame*	handle_input	(Manager& man)							override;
	virtual void		update			(const float deltaT, Manager& man)		override;
	virtual void		render			(sf::RenderWindow& rWin, Manager& man)	override;

private:
	unsigned short	txt_scale_menu_,
					txt_scale_pkmn_;
	float			x_offset_;
	
	G_Menu*			g_menu_;

private:
	enum e_BattleOp
	{
		FIGHT,
		PKMN,
		BACK,
		END
	};
};
