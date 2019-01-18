#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../source/Common.cpp"
#include "Manager.h"



// Holds the different game screens/scenes & their corresponding logic 
class G_Frame
{
public:
	virtual ~G_Frame					();

	virtual G_Frame*	handle_input	(Manager& man)							= 0;
	virtual void		update			(const float deltaT, Manager& man)		= 0;
	virtual void		render			(sf::RenderWindow& rWin, Manager& man)	= 0;

protected:
	static bool	pressed_enter_;
};
