#include "../include/Manager.h"

#include "../include/App.h"
#include "../include/Chr_Cpu.h"
#include "../include/Chr_Player.h"
#include "../include/G_Frame_Battle.h"
#include "../include/G_Frame_Fight.h"
#include "../include/G_Frame_Pkmn.h"
#include "../include/G_Frame_Start.h"



// cTor
Manager::Manager(const vec2f p1DefaultPos,
				 const vec2f p12efaultPos)
	:
		winner_player_		(false),
		winner_cpu_			(false),
		starting_player_	(0),
		current_pkmn_type_	(0),
		p1_default_pos_		(new vec2f(p1DefaultPos)),
		p2_default_pos_		(new vec2f(p12efaultPos)),
		screen_dist_tex_	(new sf::Texture),
		screen_vig_tex_		(new sf::Texture),
		screen_dist_spr_	(new sf::Sprite),
		screen_vig_spr_		(new sf::Sprite),
		flick_time_			(1.0f / 60.0f),		// Some value based on "feel"
		flick_time_current_	(0.0f),
		flick_current_		(0)
{
	// Builds initial screen (main menu or whatever)
	g_frame_ = new G_Frame_Start(*this);
	// Build screen effects
	create_screen_effects(10, 3);
}



// dTor
Manager::~Manager()
{
	AUTO_DEL(p1_default_pos_);
	AUTO_DEL(p1_default_pos_);
	AUTO_DEL(screen_dist_tex_);
	AUTO_DEL(screen_vig_tex_);
	AUTO_DEL(screen_dist_spr_);
	AUTO_DEL(screen_vig_spr_);
	AUTO_DEL(p_);
	AUTO_DEL(c_);
	AUTO_DEL(g_frame_);
}



// get_winner_player
bool Manager::get_winner_player()
{
	return winner_player_;
}



// get_cpu
Chr_Cpu& Manager::get_cpu()
{
	return *c_;
}



// get_cpu_spawn_pos
vec2f& Manager::get_cpu_default_pos()
{
	return *p2_default_pos_;
}



// get_player
Chr_Player& Manager::get_player()
{
	return *p_;
}



// get_player_spawn_pos
vec2f& Manager::get_player_default_pos()
{
	return *p1_default_pos_;
}



// get_starting_player
unsigned short Manager::get_starting_player()
{
	return starting_player_;
}



// set_winner
void Manager::set_winner(const str& winner)
{
	if (winner == "player")
		winner_player_ = true;
	
	if (winner == "cpu")
		winner_cpu_ = true;
}



// set_current_pkmn_type_
void Manager::set_current_pkmn_type(unsigned short pkmnType)
{
	current_pkmn_type_ = pkmnType;
}



// set_starting_player
void Manager::set_starting_player(unsigned short startingPlayer)
{
	starting_player_ = startingPlayer;
}



// build_screen_effects
void Manager::create_screen_effects(const u_int baseFlickVal,
									const u_int incrementalFlickVal)
{
	// Distortion values
	u_int base = baseFlickVal - incrementalFlickVal;
	for (size_t i = 0; i < 4; i++)
	{
		base += incrementalFlickVal;
		flicks_.push_back(base);
	}

	// Distortion/scan lines
	screen_dist_tex_->loadFromFile("./assets/screen_effect.png");
	screen_dist_tex_->setSmooth(true);
	screen_dist_spr_->setTexture(*screen_dist_tex_);
	screen_dist_spr_->setColor(sf::Color(150, 150, 150, baseFlickVal));
	screen_dist_spr_->setScale(vec2f(0.90f, 0.90f));

	// Vignett
	screen_vig_tex_->loadFromFile("./assets/screen_vignett.png");
	screen_vig_tex_->setSmooth(true);
	screen_vig_spr_->setTexture(*screen_vig_tex_);
	screen_vig_spr_->setOrigin(screen_vig_tex_->getSize().x * 0.5f, screen_vig_tex_->getSize().y * 0.5f);
	screen_vig_spr_->setPosition(vec2f(640 * 0.5, 360 * 0.5));
	screen_vig_spr_->setColor(sf::Color(255, 255, 255, 150));
}



// do_flicker_effect
void Manager::do_screen_effect(const float deltaT)
{
	flick_time_current_ += deltaT;
	if (flick_time_current_ >= flick_time_)
	{
		flick_time_current_ = 0.0f;

		flick_current_ =	flick_current_ == flicks_[0] ? flicks_[2] :
							flick_current_ == flicks_[1] ? flicks_[3] :
							flick_current_ == flicks_[2] ? flicks_[1] :
														   flicks_[0];

		screen_dist_spr_->setColor(sf::Color(0, 0, 0, flick_current_));
	}
}



// create_player
void Manager::create_player()
{
	p_ = new Chr_Player(*p1_default_pos_);
}



// delete_player
void Manager::delete_player()
{
	AUTO_DEL(p_);
}



// create_cpu
void Manager::create_cpu()
{
	c_ = new Chr_Cpu(*p2_default_pos_);
}



// delete_cpu
void Manager::delete_cpu()
{
	AUTO_DEL(c_);
	app_ = nullptr;
}



// handle_input
void Manager::handle_input()
{
	auto switch_g_frame = g_frame_->handle_input(*this);	// Returns true if g_frame should change state
	if (switch_g_frame)
	{
		delete g_frame_;
		g_frame_ = switch_g_frame;
	}
}



// update
void Manager::update(const float deltaT)
{
	g_frame_->update(deltaT, *this);
	// Flickering & vignett effects
	do_screen_effect(deltaT);
}



// render
void Manager::render(sf::RenderWindow& rWin)
{
	g_frame_->render(rWin, *this);

	rWin.draw(*screen_dist_spr_);
	rWin.draw(*screen_vig_spr_);
}



// terminate
void Manager::terminate()
{
	app_->terminate();
}
