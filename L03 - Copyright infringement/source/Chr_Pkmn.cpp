#include "../include/Chr_Pkmn.h"



// cTor
Chr_Pkmn::Chr_Pkmn(const str& pkmnType,
				   const vec2f& pos,
				   const vec2f& sprScale)
	:
		Chr						(), // pkmnType equals "blue", "green", "red" or "yellow" // Class inherits inits & other things from Chr cTor
		is_dead_				(false),
		rumble_dir_				(true),
		do_rumble_				(false),
		health_default_			(0.0f),
		health_current_			(0.0f),
		pow_slash_				(0.0f),
		pow_elemental_			(0.0f),
		eff_attack_				(0.0f),
		eff_defense_			(0.0f),
		attack_scaler_			(10.0f),
		rumble_lerped_			(0.0f),
		rumble_minmax_			(0.0f),
		rumble_scaling_			(0.0f),
		rumble_current_			(0.0f),
		pkmn_type_name_			(pkmnType)
{
	// Create sprite & set default values
	str tex_dir = "./assets/pkmn_.png";
	tex_dir.insert(14, pkmnType);
	set_tex(tex_dir);

	set_spr(get_tex());
	set_spr_origin(vec2f(spr_height_ * 0.5f, spr_widht_ * 0.5f));
	set_pos_default(pos);
	set_pos(pos);

	set_spr_scale(sprScale);
}



// dTor
Chr_Pkmn::~Chr_Pkmn()
{
	AUTO_DEL(pos_default_);
	AUTO_DEL(pos_);
	AUTO_DEL(spr_origin_);
	AUTO_DEL(spr_scale_);
	AUTO_DEL(tex_);
	AUTO_DEL(spr_);
}



// get_eff_defense
float Chr_Pkmn::get_eff_defense()
{
	return eff_defense_;
}



// get_pkmn_name
str& Chr_Pkmn::get_pkmn_type_name()
{
	return pkmn_type_name_;
}



// get_health
float Chr_Pkmn::get_health_current()
{
	return health_current_;
}



// get_health_default
float Chr_Pkmn::get_health_default()
{
	return health_default_;
}



// get_is_alive
bool Chr_Pkmn::get_is_dead()
{
	return is_dead_;
}



// get_attack_dmg
float Chr_Pkmn::get_attack_dmg(const unsigned short attackType, const float enemyEffDefense)
{
	float pow = attackType == 0 ? pow_slash_ : pow_elemental_;
	return ((pow * (eff_attack_ / enemyEffDefense)) / attack_scaler_) + 2;	// Simplified version of actual Pokemon attack formula
}



// set_attack_defense_vals
void Chr_Pkmn::set_stats(const float health,
						 const float powSlash,
						 const float powElemental,
						 const float effAttack,
						 const float effDefense)
{
	health_default_ = health;
	health_current_ = health_default_;
	pow_slash_		= powSlash;
	pow_elemental_	= powElemental;
	eff_attack_		= effAttack;
	eff_defense_	= effDefense;
}



// set_health
void Chr_Pkmn::set_health(const float health)
{
	health_current_ = health;
}



// set_is_alive
void Chr_Pkmn::set_is_dead(const bool isDead)
{
	is_dead_ = isDead;
	health_current_ = 0.0f;
	spr_->setTexture(*tex_spr_dead_);
}



// rumble
void Chr_Pkmn::rumble(const float minMax, const float scaling)
{
	do_rumble_		= true;
	rumble_minmax_	= minMax;
	rumble_scaling_	= scaling;
}



// do_dmg
void Chr_Pkmn::do_dmg(const float dmg)
{
	health_current_ -= dmg;
}



// update
void Chr_Pkmn::update(const float deltaT)
{
	// Rotations
	do_rotations(deltaT);

	// Rumble
	if (do_rumble_)
		do_rumble(deltaT);
}



// do_rotations
void Chr_Pkmn::do_rotations(const float deltaT)
{
	if (!is_dead_)	// Alive "animation"
	{
		if ((anim_spr_angle_ >= anim_rot_angle_max_) && anim_rot_dir_)
			anim_rot_dir_ = false;

		if ((anim_spr_angle_ < -anim_rot_angle_max_) && !anim_rot_dir_)
			anim_rot_dir_ = true;

		anim_spr_angle_ = anim_rot_dir_ ? anim_spr_angle_ + (anim_rot_spd_ * deltaT) :
			anim_spr_angle_ - (anim_rot_spd_ * deltaT);

		set_spr_rotation(anim_spr_angle_);
	}
	else			// Dead "animation"
	{
		if ((anim_scale_current_->x >= anim_scale_max_) && anim_scale_dir_)
			anim_scale_dir_ = false;

		if ((anim_scale_current_->x < anim_scale_min_) && !anim_scale_dir_)
			anim_scale_dir_ = true;

		auto scale_val = anim_scale_spd_ * deltaT;
		*anim_scale_current_ = anim_scale_dir_ ? vec2f(anim_scale_current_->x + scale_val, anim_scale_current_->y + scale_val)
			:
			vec2f(anim_scale_current_->x - scale_val, anim_scale_current_->y - scale_val);

		set_spr_scale(*anim_scale_current_);
	}
}



// do_rumble
void Chr_Pkmn::do_rumble(const float deltaT)
{
	// Wanted an excuse to use a lamda function as I never done it before
	auto lrpd = [](float current, float minMax, float scaling)
	{
		return (current * (1 - scaling)) + (minMax * scaling);
	};

	rumble_lerped_ = lrpd(rumble_lerped_, rumble_minmax_, (rumble_scaling_ * deltaT));
	rumble_current_ = rumble_lerped_;


	// Make lerped value flipflop betwen ngative & positive
	if (rumble_dir_)
	{
		rumble_dir_ = !rumble_dir_;
		rumble_current_ = rumble_lerped_;
	}
	else
	{
		rumble_dir_ = !rumble_dir_;
		rumble_current_ = rumble_lerped_ * -1.0f;
	}

	translate_pos(vec2f(rumble_current_, rumble_current_));

	if (rumble_current_ > rumble_minmax_ - 0.1f)
	{
		do_rumble_		= false;
		rumble_lerped_	= 0.0f;
		rumble_current_	= 0.0f;
		rumble_minmax_	= 0.0f;
		rumble_scaling_	= 0.0f;

		set_pos(get_pos_defualt());
	}
}