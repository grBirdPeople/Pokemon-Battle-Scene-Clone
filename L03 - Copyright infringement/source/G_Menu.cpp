#include "../include/G_Menu.h"

#include "../include/Input.h"



// cTor
G_Menu::G_Menu()
	:
		pressed_up_			(false),
		pressed_down_		(false),
		arrow_current_pos_	(0),
		arrow_tex_			(new sf::Texture),
		border_tex_			(new sf::Texture),
		arrow_spr_			(new sf::Sprite),
		border_c_spr_		(nullptr),
		border_p_spr_		(nullptr),
		arrow_pos_			(new vec2f),
		border_scale_		(new vec2f(2.5f, 2.5f)),
		border_pos_c_		(new vec2f()),
		border_pos_p_		(new vec2f()),
		font_txt_			(new font),
		color_txt_			(new sf::Color(22, 73, 02))
{
	// Menu arrow
	arrow_tex_->loadFromFile("./assets/menu_arrow.png");
	arrow_spr_->setTexture(*arrow_tex_);
	arrow_spr_->setOrigin(arrow_tex_->getSize().x * 0.5f, arrow_tex_->getSize().y * 0.5f);

	// Font
	font_txt_->loadFromFile("./assets/Pokemon_GB.ttf");

	// Menu border
	border_tex_->loadFromFile("./assets/menu_border.png");
}



// dTor
G_Menu::~G_Menu()
{
	AUTO_DEL(arrow_tex_);
	AUTO_DEL(border_tex_);
	AUTO_DEL(arrow_spr_);
	AUTO_DEL(border_p_spr_);
	AUTO_DEL(border_c_spr_);
	AUTO_DEL(arrow_pos_);
	AUTO_DEL(border_scale_);
	AUTO_DEL(border_pos_c_);
	AUTO_DEL(border_pos_p_);
	AUTO_DEL(font_txt_);
	AUTO_DEL(color_txt_);

	for (auto& i : v_a_pos_)
		AUTO_DEL(i);

	for (auto& i : m_txt_obj_)
		AUTO_DEL(i.second);
}



// get_arrow_spr
sf::Sprite& G_Menu::get_arrow_spr()
{
	return *arrow_spr_;
}



// get_border_spr_c
sf::Sprite& G_Menu::get_border_spr_c()
{
	return *border_c_spr_;
}



// get_border_spr_p
sf::Sprite& G_Menu::get_border_spr_p()
{
	return *border_p_spr_;
}




// get_current_arrow_pos
signed short G_Menu::get_current_arrow_pos()
{
	return arrow_current_pos_;
}



// get_txt_obj
txt& G_Menu::get_txt_obj(const str& txtObjName)
{
	return *m_txt_obj_[txtObjName];
}



// get_txt_obj_map
m_txt_obj& G_Menu::get_txt_obj_map()
{
	return m_txt_obj_;
}



// set_arrow_pos
void G_Menu::set_arrow_pos(const vec2f& screenPos)
{
	*arrow_pos_ = screenPos;
	arrow_spr_->setPosition(*arrow_pos_);
}



// add_arrow_pos
void G_Menu::add_arrow_pos(const vec2f& screenPos)
{
	v_a_pos_.push_back(new vec2f(screenPos));
}



// add_border
void G_Menu::add_border(const vec2f& p1DefaultPos,
						const vec2f& p2DefaultPos,
						const bool build1Pand2P)
{
	// 1st player
	border_p_spr_ = new sf::Sprite(*border_tex_);
	border_p_spr_->setOrigin(border_tex_->getSize().x * 0.5f, border_tex_->getSize().y * 0.5f);
	border_p_spr_->setScale(vec2f(-border_scale_->x, border_scale_->y));
	border_p_spr_->setPosition(p2DefaultPos.x - 30.0f, p1DefaultPos.y + 10.0f);

	// Cpu / 2nd player
	if (build1Pand2P)
	{
		border_c_spr_ = new sf::Sprite(*border_tex_);
		border_c_spr_->setOrigin(border_tex_->getSize().x * 0.5f, border_tex_->getSize().y * 0.5f);
		border_c_spr_->setScale(vec2f(*border_scale_));
		border_c_spr_->setPosition(p1DefaultPos.x + 30.0f, p2DefaultPos.y + 10.0f);
	}
}



// add_txt_obj
void G_Menu::add_txt_obj(const str& txtObjName,
						 const vec2f& screenPos,
						 const unsigned short charSize,
						 const str& txtString,
						 const bool	setOrigin)
{
	txt* obj = new sf::Text(txtString, *font_txt_, charSize);
	obj->setFillColor(*color_txt_);
	obj->setPosition(screenPos);

	if (setOrigin)
		obj->setOrigin(obj->getLocalBounds().width * 0.5f, obj->getLocalBounds().height * 0.5f);

	m_txt_obj_[txtObjName] = obj;
}



// handle_input
void G_Menu::handle_input()
{
	// Arrow pos next
	if (!pressed_down_)
	{
		if (Input::is_pressed(sf::Keyboard::Down))
		{
			pressed_down_ = true;
			++arrow_current_pos_;

			if (arrow_current_pos_ >= static_cast<signed short>(v_a_pos_.size()))
				arrow_current_pos_ = 0;

			set_arrow_pos(*v_a_pos_[arrow_current_pos_]);
		}
	}



	// Arrow pos prev
	if (!pressed_up_)
	{
		if (Input::is_pressed(sf::Keyboard::Up))
		{
			pressed_up_ = true;
			--arrow_current_pos_;

			if (arrow_current_pos_ < 0)
				arrow_current_pos_ = static_cast<signed short>(v_a_pos_.size() - 1);

			set_arrow_pos(*v_a_pos_[arrow_current_pos_]);
		}
	}



	// Reset dwon
	if (!Input::is_pressed(sf::Keyboard::Down) && pressed_down_)
		pressed_down_ = false;

	// Reset up
	if (!Input::is_pressed(sf::Keyboard::Up) && pressed_up_)
		pressed_up_ = false;
}



// update
void G_Menu::update(const float deltaT)
{}



// render
void G_Menu::render(sf::RenderWindow& rWin)
{
	if (border_c_spr_)
		rWin.draw(*border_c_spr_);

	if (border_p_spr_)
		rWin.draw(*border_p_spr_);

	for (auto itr = m_txt_obj_.begin(); itr != m_txt_obj_.end(); itr++)
		rWin.draw(*itr->second);

	rWin.draw(*arrow_spr_);
}
