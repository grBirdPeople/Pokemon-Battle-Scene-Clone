// Things that are commonly used among files

#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#define AUTO_DEL(x) delete x, x = nullptr

using color = sf::Color;
using str	= std::string;
using u_int	= unsigned int;
using vec2f = sf::Vector2f;
