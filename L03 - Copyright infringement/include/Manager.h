#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../source/Common.cpp"

class App;
class Chr_Cpu;
class Chr_Player;
class G_Frame;

using flick_vec = std::vector<u_int>;


class Manager
{
public:
	 Manager(const vec2f p1DefaultPos,
			 const vec2f p2DefaultPos);
	~Manager();

	bool			get_winner_player		();
	Chr_Cpu&		get_cpu					();
	vec2f&			get_cpu_default_pos		();
	Chr_Player&		get_player				();
	vec2f&			get_player_default_pos	();
	unsigned short	get_starting_player		();

	void			set_winner				(const str& winner);			// Arg: "player" & "cpu"
	void			set_current_pkmn_type	(unsigned short pkmnType);
	void			set_starting_player		(unsigned short startingPlayer);

	void			create_screen_effects	(const u_int baseFlickVal,
											 const u_int incrementalFlickVal);
	void			do_screen_effect		(const float deltaT);
	void			create_player			();
	void			delete_player			();
	void			create_cpu				();
	void			delete_cpu				();

	void			handle_input			();
	void			update					(const float deltaT);
	void			render					(sf::RenderWindow& rWin);
	void			terminate				();

private:
	bool			winner_player_,
					winner_cpu_;

	unsigned short	starting_player_,
					current_pkmn_type_;

	vec2f*			p1_default_pos_;
	vec2f*			p2_default_pos_;

	sf::Texture*	screen_dist_tex_;
	sf::Texture*	screen_vig_tex_;
	sf::Sprite*		screen_dist_spr_;
	sf::Sprite*		screen_vig_spr_;

	App*			app_;
	Chr_Player*		p_;
	Chr_Cpu*		c_;
	G_Frame*		g_frame_;

	float			flick_time_,
					flick_time_current_;
	u_int			flick_current_;

	flick_vec		flicks_;
};
