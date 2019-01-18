#pragma once

#include "Chr.h"



class Chr_Pkmn : virtual public Chr
{
public:
			 Chr_Pkmn	(const str& pkmnType,
						 const vec2f& pos,
						 const vec2f& sprScale);

	virtual ~Chr_Pkmn	();

			float	get_eff_defense		();
			str&	get_pkmn_type_name	();
			float	get_health_current	();
			float	get_health_default	();
			bool	get_is_dead			();
			float	get_attack_dmg		(const unsigned short attackType,
										 const float enemyEffDefense);

			void	set_stats			(const float health,
										 const float powSlash,
										 const float powElemental,
										 const float effAttack,
										 const float effDefense);

			void	set_health			(const float health);
			void	set_is_dead			(const bool isDead);

			void	rumble				(const float minMax,
										 const float scaling);
			void	do_dmg				(const float dmg);

	virtual void	update				(const float deltaT) override;

private:
			void	do_rotations		(const float deltaT);
			void	do_rumble			(const float deltaT);

private:
	bool	is_dead_,
			rumble_dir_,
			do_rumble_;

	float	health_default_,
			health_current_,
			pow_slash_,
			pow_elemental_,
			eff_attack_,
			eff_defense_,
			attack_scaler_;

	float	rumble_lerped_,
			rumble_minmax_,
			rumble_scaling_,
			rumble_current_;

	str		pkmn_type_name_;
};
