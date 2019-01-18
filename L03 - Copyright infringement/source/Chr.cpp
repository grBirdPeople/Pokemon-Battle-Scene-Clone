#include "../include/Chr.h"



bool	Chr::anim_rot_dir_			= true;
bool	Chr::anim_scale_dir_		= true;
float	Chr::anim_spr_angle_		= 0.0f;
float	Chr::anim_rot_spd_			= 20.0f;
float	Chr::anim_rot_angle_max_	= 7.0f;
float	Chr::anim_scale_spd_		= 1.25f;
float	Chr::anim_scale_min_		= 4.0f;
float	Chr::anim_scale_max_		= 5.0f;
vec2f*	Chr::anim_scale_current_	= new vec2f(5.0f, 5.0f);

// Texture is shared by all pkmns
tex* Chr::tex_spr_dead_ = init_tex();

// cTor
Chr::Chr()
	:
		spr_widht_	(0),
		spr_height_	(0),
		pos_default_(new vec2f),
		pos_		(new vec2f),
		spr_origin_	(new vec2f),
		spr_scale_	(new vec2f),
		tex_		(new tex),
		spr_		(new spr)
{}



// dTor
Chr::~Chr()
{
	//AUTO_DEL(anim_scale_current_);	// If active, if app is exited and re-enterd from in game, data won't exist, game crashes
	//AUTO_DEL(tex_spr_dead_);			// If active, if app is exited and re-enterd from in game manu, sprite won't exist, no sprite is drawn
}



// init_tex
tex* Chr::init_tex()
{
	tex* texture = new tex;
	texture->loadFromFile("./assets/pkmn_dead.png");

	return texture;
}



// get_pos_defualt
vec2f& Chr::get_pos_defualt()
{
	return *pos_default_;
}



// get_pos
vec2f& Chr::get_pos()
{
	return *pos_;
}



// get_tex
tex& Chr::get_tex()
{
	return *tex_;
}



// get_spr
spr& Chr::get_spr()
{
	return *spr_;
}



// get_spr_scale
vec2f& Chr::get_spr_scale()
{
	return *spr_scale_;
}



// set_pos_default
void Chr::set_pos_default(const vec2f& pos)
{
	*pos_default_ = pos;
}



// overload
void Chr::set_pos(const vec2f& pos)
{
	*pos_ = pos;
	spr_->setPosition(*pos_);
}



// set_tex
void Chr::set_tex(const str& texDir)
{
	tex_->loadFromFile(texDir);
}



// set_spr
void Chr::set_spr(const tex& texture)
{
	spr_->setTexture(texture);

	spr_widht_ = spr_->getTextureRect().width;
	spr_height_ = spr_->getTextureRect().height;
}



// set_spr_rotation
void Chr::set_spr_rotation(const float angle)
{
	anim_spr_angle_ = angle;
	spr_->setRotation(angle);
}



// overload
void Chr::set_spr_origin(const vec2f& origin)
{
	*spr_origin_ = origin;
	spr_->setOrigin(*spr_origin_);
}



// overload
void Chr::set_spr_scale(const vec2f& factors)
{
	spr_->setScale(factors);
	*spr_scale_ = factors;
}



// overload
void Chr::translate_pos(const vec2f& pos)
{
	*pos_ = *pos_ + pos;
	spr_->setPosition(*pos_);
}



// render
void Chr::render(sf::RenderWindow& rWin)
{
	rWin.draw(*spr_);
}
