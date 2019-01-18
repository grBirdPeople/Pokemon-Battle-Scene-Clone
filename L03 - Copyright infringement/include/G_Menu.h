#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../source/Common.cpp"

using font			= sf::Font;
using txt			= sf::Text;
using v_a_pos		= std::vector<vec2f*>;
using m_txt_obj		= std::map<str, txt*>;


// Tool for building menus (text, cursor, borders), used by all G_Frame files
class G_Menu
{
public:
	G_Menu();
	~G_Menu();

	sf::Sprite&		get_arrow_spr			();
	sf::Sprite&		get_border_spr_c		();
	sf::Sprite&		get_border_spr_p		();
	signed short	get_current_arrow_pos	();
	txt&			get_txt_obj				(const str& txtObjName);
	m_txt_obj&		get_txt_obj_map			();

	void			set_arrow_pos			(const vec2f& screenPos);

	void			add_arrow_pos			(const vec2f& screenPos);
	void			add_border				(const vec2f& p1DefaultPos,
											 const vec2f& p2DefaultPos,
											 const bool build1Pand2P);

	void			add_txt_obj				(const str& txtObjName,
											 const vec2f& screenPos,
											 const unsigned short charSize,
											 const str& txtString,
											 const bool	setOrigin = false);

	void			handle_input			();
	void			update					(const float deltaT);
	void			render					(sf::RenderWindow& rWin);

private:
	bool			pressed_up_,
					pressed_down_;

	signed short	arrow_current_pos_;

	sf::Texture*	arrow_tex_;
	sf::Texture*	border_tex_;

	sf::Sprite*		arrow_spr_;
	sf::Sprite*		border_c_spr_;
	sf::Sprite*		border_p_spr_;

	vec2f*			arrow_pos_;
	vec2f*			border_scale_;
	vec2f*			border_pos_c_;
	vec2f*			border_pos_p_;

	color*			color_txt_;
	font*			font_txt_;

	v_a_pos			v_a_pos_;
	m_txt_obj		m_txt_obj_;
};
