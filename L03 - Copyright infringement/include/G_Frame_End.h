#pragma once

#include "G_Frame.h"

class G_Menu;



class G_Frame_End : virtual public G_Frame
{
public:
			 G_Frame_End				(Manager& man);
	virtual	~G_Frame_End				();

	void				build_menu		(const str& winner);

	virtual G_Frame*	handle_input	(Manager& man)							override;
	virtual void		update			(const float deltaT, Manager& man)		override;
	virtual void		render			(sf::RenderWindow& rWin, Manager& man)	override;

private:
	unsigned short	txt_scale_title_;
	unsigned short	txt_scale_menu_;
	float			x_offset_;

	G_Menu*			g_menu_;
};
