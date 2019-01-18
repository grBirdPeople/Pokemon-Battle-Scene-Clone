#pragma once

#include "G_Frame.h"

class G_Frame_Fight;
class G_Menu;

using up_ptr = void(G_Frame_Fight::*)(const float deltaT, Manager& man);

#include "Chr.h"



class G_Frame_Fight: virtual public G_Frame
{
public:
			 G_Frame_Fight				(Manager& man);
	virtual	~G_Frame_Fight				();

			void		build_menu		(Manager& man);
			void		txt_player		(Manager& man);
			void		txt_cpu			(Manager& man);

	virtual	G_Frame*	handle_input	(Manager& man)									override;
	virtual void		update			(const float deltaT, Manager& man)				override;
			void		update_p1		(const float deltaT, Manager& man);
			void		update_cpu		(const float deltaT, Manager& man);
			void		update_txt		(const signed short playerType, Manager& man);
	virtual void		render			(sf::RenderWindow& rWin, Manager& man)			override;

private:
				bool	p1_turn_,
						atk_type_,					// Temp var for which attack the cpu will do.. might have evolved to permanent though...
						input_enabled_,
						logic_player_updated_,
						logic_cpu_updated_;

	signed		short	current_arrow_pos_;
	unsigned	short	txt_scale_menu_;

				float	x_offset_arrow_;

				float	rumble_minMax_spr_,
						rumble_scaling_spr_;

				float	frame_delay_player_,
						frame_delay_player_current_,
						frame_delay_player_default_,
						frame_delay_cpu_,
						frame_delay_cpu_current_,
						frame_delay_cpu_default_,
						frame_delay_death_;

				up_ptr	current_update_;
				G_Menu*	g_menu_;

private:
	// Represents choice in the menu for this frame/scene
	enum e_FightOpt
	{
		SLASH,
		ELEMENTAL,
		BACK,
		END
	};
};
