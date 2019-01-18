#pragma once

#include <vector>
#include <SFML/Window/Keyboard.hpp>

using v_keys	= std::vector<bool>;



class Input
{
public:
	static void	init_keys		();
	static void	clear_keys		();
	static void	set_pressed		(sf::Keyboard::Key key);
	static void	set_released	(sf::Keyboard::Key key);
	static bool	is_pressed		(sf::Keyboard::Key key);

private:
	static unsigned short	key_count_;
	static v_keys			keys_;
};
