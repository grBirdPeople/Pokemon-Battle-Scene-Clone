#pragma once

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../source/Common.cpp"

using tex	= sf::Texture;
using spr	= sf::Sprite;



enum e_PkmnType
{
	BLUE = 0,
	GREEN,
	RED,
	YELLOW,
	END
};



// Abstarct base for Chr_Player & Chr_Pkmn
class Chr
{
public:
			 Chr							();
	virtual ~Chr							();

	static	tex*		init_tex			();

			vec2f&		get_pos_defualt();
			vec2f&		get_pos				();
			tex&		get_tex				();
			spr&		get_spr				();
			vec2f&		get_spr_scale		();

			void		set_pos_default		(const vec2f& pos);
			void		set_pos				(const vec2f& pos);
			void		set_tex				(const str& texDir);
			void		set_spr				(const tex& texture);
			void		set_spr_rotation	(const float angle);
			void		set_spr_scale		(const vec2f& factors);
			void		set_spr_origin		(const vec2f& origin);

			void		translate_pos		(const vec2f& pos);

	virtual void		update				(const float deltaT) = 0;	// Abstract
			void		render				(sf::RenderWindow& rWin);

protected:
			int		spr_widht_,
					spr_height_;

	static	bool	anim_rot_dir_;
	static	bool	anim_scale_dir_;

	static	float	anim_rot_spd_;
	static	float	anim_spr_angle_;
	static	float	anim_rot_angle_max_;
	static	float	anim_scale_spd_;
	static	float	anim_scale_min_;
	static	float	anim_scale_max_;

	static	vec2f*	anim_scale_current_;

			vec2f*	pos_default_;
			vec2f*	pos_;
			vec2f*	spr_origin_;
			vec2f*	spr_scale_;

			tex*	tex_;
	static	tex*	tex_spr_dead_;
			spr*	spr_;
};
