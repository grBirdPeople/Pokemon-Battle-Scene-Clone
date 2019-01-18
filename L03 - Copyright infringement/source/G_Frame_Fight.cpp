#include "../include/G_Frame_Fight.h"

#include <iostream>

#include "../include/Chr_Cpu.h"
#include "../include/Chr_Player.h"
#include "../include/G_Frame_Battle.h"
#include "../include/G_Frame_End.h"
#include "../include/G_Frame_Pkmn.h"
#include "../include/G_Menu.h"
#include "../include/Input.h"



//cTor
G_Frame_Fight::G_Frame_Fight(Manager& man)
	:
		p1_turn_					(true),
		atk_type_					(true),
		input_enabled_				(true),
		logic_player_updated_		(false),
		logic_cpu_updated_			(false),
		current_arrow_pos_			(e_FightOpt::END),
		txt_scale_menu_				(12),
		x_offset_arrow_				(22.5f),
		rumble_minMax_spr_			(6.0),
		rumble_scaling_spr_			(6.0f),
		frame_delay_player_			(0.0f),
		frame_delay_player_current_	(0.75f),
		frame_delay_player_default_	(0.75f),
		frame_delay_cpu_			(0.0f),
		frame_delay_cpu_current_	(0.5f),
		frame_delay_cpu_default_	(0.5f),
		frame_delay_death_			(1.5),
		current_update_				(&G_Frame_Fight::update_p1),
		g_menu_						(new G_Menu)
{
	build_menu(man);

	// Set which player that starts. A zero equals player 1, a one equals...
	current_update_ = man.get_starting_player() == 0 ? nullptr : &G_Frame_Fight::update_cpu;
}



// dTor
G_Frame_Fight::~G_Frame_Fight()
{
	AUTO_DEL(g_menu_);
}



// build_menu
void G_Frame_Fight::build_menu(Manager& man)
{
	// Create text
	vec2f normal_select		(400.0f, 280.0f);
	vec2f special_select	(400.0f, 300.0f);
	vec2f back_select		(400.0f, 330.0f);

	g_menu_->add_txt_obj("slash",		normal_select,		txt_scale_menu_,	"Slash");
	g_menu_->add_txt_obj("elemental",	special_select,		txt_scale_menu_,	"Elemental");
	g_menu_->add_txt_obj("back",		back_select,		10,					"Back");

	// Text for currently selected pkmn
	txt_player(man);
	txt_cpu(man);

	// Create cursor positions
	float y_offset = static_cast<float>(g_menu_->get_txt_obj("slash").getLocalBounds().height * 0.5);

	g_menu_->add_arrow_pos(vec2f(normal_select.x - x_offset_arrow_,	normal_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(special_select.x - x_offset_arrow_,	special_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(back_select.x - x_offset_arrow_,		back_select.y + y_offset));

	// Set cursor default pos
	g_menu_->set_arrow_pos(vec2f(normal_select.x - x_offset_arrow_, normal_select.y + y_offset));

	// Add border
	g_menu_->add_border(man.get_player_default_pos(), man.get_cpu_default_pos(), true);
}



// txt_player
void G_Frame_Fight::txt_player(Manager& man)
{
	// Text for currently player selected pkmn
	auto current	= man.get_player().get_current_pkmn();
	auto name		= man.get_player().get_pkmn(current).get_pkmn_type_name();
	auto health		= man.get_player().get_pkmn(current).get_health_current();
	auto x_pos		= man.get_cpu_default_pos().x;
	auto y_pos		= man.get_player_default_pos().y;

	// Pkmn type name
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	g_menu_->add_txt_obj("player", vec2f(x_pos, y_pos - 10.0f), txt_scale_menu_, name, true);

	// Pkmn health
	str health_str = " / ";
	health_str.insert(0, std::to_string(static_cast<int>(health)));
	health_str.append(std::to_string(static_cast<int>(man.get_player().get_pkmn(current).get_health_default())));
	g_menu_->add_txt_obj("player_pkmn_hp", vec2f(x_pos, y_pos + 10.0f), txt_scale_menu_, health_str, true);
}



// txt_cpu
void G_Frame_Fight::txt_cpu(Manager& man)
{
	// Text for currently cpu selected pkmn
	auto current	= man.get_cpu().get_current_pkmn();
	auto name_pkmn	= man.get_cpu().get_pkmn(current).get_pkmn_type_name();
	auto health		= man.get_cpu().get_pkmn(current).get_health_current();
	auto x_pos		= man.get_player_default_pos().x;
	auto y_pos		= man.get_cpu_default_pos().y;

	// Pkmn type name
	std::transform(name_pkmn.begin(), name_pkmn.end(), name_pkmn.begin(), ::toupper);
	g_menu_->add_txt_obj("cpu", vec2f(x_pos, y_pos - 10.0f), txt_scale_menu_, name_pkmn, true);

	// Pkmn health
	str health_str = " / ";
	health_str.insert(0, std::to_string(static_cast<int>(health)));
	health_str.append(std::to_string(static_cast<int>(man.get_player().get_pkmn(current).get_health_default())));
	g_menu_->add_txt_obj("cpu_pkmn_hp", vec2f(x_pos, y_pos + 10.0f), txt_scale_menu_, health_str, true);
}



// handle_input
G_Frame* G_Frame_Fight::handle_input(Manager& man)
{
	// Make so menus aren't all flipitiflopiti
	if (!Input::is_pressed(sf::Keyboard::Enter) && pressed_enter_)
		pressed_enter_ = false;



	// Takes away player control
	if (input_enabled_)
	{
		// Currently selected player/cpu pkmn died in battle, return to pkmn select scene or end screen
		// Player pkmn died
		if (man.get_player().get_current_pkmn_died())
		{
			if (man.get_player().get_pkmns_size() > -1)		// All pkmns are dead
			{
				man.get_player().set_current_pkmn_died(false);
				return new G_Frame_Pkmn(man);
			}
			else
			{
				man.set_winner("cpu");
				return new G_Frame_End(man);
			}
		}

		// Cpu pkmn has died
		if (man.get_cpu().get_current_pkmn_died())
		{
			if (man.get_cpu().get_pkmns_size() > -1)		// Some pkmn is alive
			{
				man.get_cpu().set_current_pkmn_died(false);
				man.get_cpu().randomise_new_current_pkmn();

				auto current = man.get_cpu().get_current_pkmn();
				auto name_pkmn = man.get_cpu().get_pkmn(current).get_pkmn_type_name();
				std::transform(name_pkmn.begin(), name_pkmn.end(), name_pkmn.begin(), ::toupper);
				g_menu_->get_txt_obj("cpu").setString(name_pkmn);
				update_txt(1, man);
			}
			else
			{
				man.set_winner("player");
				return new G_Frame_End(man);
			}
		}



		// Do menu things like moving the cursor etc. etc.
		g_menu_->handle_input();



		// Get the players chosen selection
		if (Input::is_pressed(sf::Keyboard::Enter) && !pressed_enter_)
		{
			pressed_enter_ = true;
			input_enabled_ = false;		// Is true after cpu made its turn
			current_arrow_pos_ = g_menu_->get_current_arrow_pos();

			// Set & run player update method
			if (current_arrow_pos_ != e_FightOpt::BACK)
				current_update_ = &G_Frame_Fight::update_p1;
		}



		// Back to main battle menu
		if (current_arrow_pos_ == e_FightOpt::BACK)
			return new G_Frame_Battle(man);
	}



	// No state/scene change, so return null
	return nullptr;
}



// update
void G_Frame_Fight::update(const float deltaT, Manager& man)
{
	// Runs this class current update, either human or cpu (the actual game logic for player 1 or 2)
	// Is null before the human player choses an action, which is set in the handle_input() method
	if (current_update_)
		(this->*current_update_)(deltaT, man);

	// 3xA animations (think guilty geard x3rd quality)
	auto p_pkmn = man.get_player().get_current_pkmn();
	man.get_player().get_pkmn_map()[p_pkmn]->update(deltaT);

	auto c_pkmn = man.get_cpu().get_current_pkmn();
	man.get_cpu().get_pkmn_map()[c_pkmn]->update(deltaT);
}



// update_p1
void G_Frame_Fight::update_p1(const float deltaT, Manager& man)
{
	if (!logic_player_updated_)	// "Pauses" the gameplay for a while. Reason: So the cpu doesn't imediately do it's thing
	{
		auto pkmn_this		= man.get_player().get_current_pkmn();
		auto pkmn_enemy		= man.get_cpu().get_current_pkmn();
		auto enemy_defense	= man.get_cpu().get_pkmn(pkmn_enemy).get_eff_defense();
		float dmg			= 0.0f;



		// Slash attack
		if (current_arrow_pos_ == e_FightOpt::SLASH)
			dmg = man.get_player().get_pkmn_map()[pkmn_this]->get_attack_dmg(e_FightOpt::SLASH, enemy_defense);

		// Elemental attack
		if (current_arrow_pos_ == e_FightOpt::ELEMENTAL)
			dmg = man.get_player().get_pkmn_map()[pkmn_this]->get_attack_dmg(e_FightOpt::ELEMENTAL, enemy_defense);

		// Reset what the menu arrow is pointing to
		current_arrow_pos_ = e_FightOpt::END;



		// Shake enemy sprite
		man.get_cpu().get_pkmn(pkmn_enemy).rumble(rumble_minMax_spr_, rumble_scaling_spr_);

		// Update health of enemy
		man.get_cpu().get_pkmn(pkmn_enemy).do_dmg(dmg);

		// If cpu pkmn health is 0 or less
		if (man.get_cpu().get_pkmn(pkmn_enemy).get_health_current() <= 0.0f)
		{
			man.get_cpu().get_pkmn(pkmn_enemy).set_health(0.0f);
			man.get_cpu().get_pkmn(pkmn_enemy).set_spr_rotation(0.0f);
			man.get_cpu().get_pkmn(pkmn_enemy).set_is_dead(true);
			man.get_cpu().set_current_pkmn_died(true);

			frame_delay_player_current_ = frame_delay_death_;
		}

		// Update displayed health of enemy
		update_txt(1, man);



		// Do not enter this block until next turn
		logic_player_updated_ = true;
	}
	

	// "Pause" game progress for a while, then change update which update method to run
	frame_delay_player_ += deltaT;
	if ((frame_delay_player_ >= frame_delay_player_current_) &&
		logic_player_updated_)
	{
		logic_player_updated_		= false;
		frame_delay_player_current_	= frame_delay_player_default_;
		frame_delay_player_			= 0.0f;

		// If enemy died, bypass upcoming enemy turn, else go to main update
		if (!man.get_cpu().get_current_pkmn_died())
		{
			current_update_ = &G_Frame_Fight::update_cpu;
		}
		else
		{
			input_enabled_	= true;
			current_update_	= nullptr;
		}
	}
}



// update_p2
void G_Frame_Fight::update_cpu(const float deltaT, Manager& man)
{
	if (!logic_cpu_updated_)	// "Pauses" the gameplay for a while. Reason: So the cpu doesn't imediately do it's thing
	{
		auto pkmn_this		= man.get_cpu().get_current_pkmn();
		auto pkmn_enemy		= man.get_player().get_current_pkmn();
		auto enemy_defense	= man.get_player().get_pkmn(pkmn_enemy).get_eff_defense();
		float dmg			= 0.0f;



		// Deep learning AI
		if (atk_type_)
		{
			atk_type_ = !atk_type_;
			dmg = man.get_cpu().get_pkmn_map()[pkmn_this]->get_attack_dmg(e_FightOpt::SLASH, enemy_defense);
		}
		else
		{
			atk_type_ = !atk_type_;
			dmg = man.get_cpu().get_pkmn_map()[pkmn_this]->get_attack_dmg(e_FightOpt::ELEMENTAL, enemy_defense);
		}



		// Shake enemy sprite
		man.get_player().get_pkmn(pkmn_enemy).rumble(rumble_minMax_spr_, rumble_scaling_spr_);

		// Update health of player
		man.get_player().get_pkmn(pkmn_enemy).do_dmg(dmg);

		// If player pkmn health is 0 or less
		if (man.get_player().get_pkmn(pkmn_enemy).get_health_current() <= 0.0f)
		{
			man.get_player().get_pkmn(pkmn_enemy).set_health(0.0f);
			man.get_player().get_pkmn(pkmn_enemy).set_spr_rotation(0.0f);
			man.get_player().get_pkmn(pkmn_enemy).set_is_dead(true);
			man.get_player().set_current_pkmn_died(true);

			frame_delay_cpu_current_ = frame_delay_death_;
		}

		// Update displayed health of player
		update_txt(0, man);



		// Do not enter this block until next turn
		logic_cpu_updated_ = true;
	}



	// "Pause" game progress for a while, then change update which update method to run
	frame_delay_cpu_ += deltaT;
	if ((frame_delay_cpu_ >= frame_delay_cpu_current_) &&
		logic_cpu_updated_)
	{
		logic_cpu_updated_			= false;
		frame_delay_cpu_current_	= frame_delay_cpu_default_;
		frame_delay_cpu_			= 0.0f;
		input_enabled_				= true;

		// Makes the program wait for human input before running any more updates
		// Pointer is re-pointed in handle_input()
		current_update_ = nullptr;
	}
}



// update_txt
void G_Frame_Fight::update_txt(const signed short playerType, Manager& man)
{
	if (playerType == 0)
	{
		auto pkmn = man.get_player().get_current_pkmn();
		str health = " / ";
		health.insert(0, std::to_string(static_cast<int>(man.get_player().get_pkmn(pkmn).get_health_current())));
		health.append(std::to_string(static_cast<int>(man.get_player().get_pkmn(pkmn).get_health_default())));
		g_menu_->get_txt_obj("player_pkmn_hp").setString(health);
	}
	else if (playerType == 1)
	{
		auto pkmn = man.get_cpu().get_current_pkmn();
		str health = " / ";
		health.insert(0, std::to_string(static_cast<int>(man.get_cpu().get_pkmn(pkmn).get_health_current())));
		health.append(std::to_string(static_cast<int>(man.get_cpu().get_pkmn(pkmn).get_health_default())));
		g_menu_->get_txt_obj("cpu_pkmn_hp").setString(health);
	}
}



// render
void G_Frame_Fight::render(sf::RenderWindow& rWin, Manager& man)
{
	g_menu_->render(rWin);

	auto p_pkmn = man.get_player().get_current_pkmn();
	man.get_player().get_pkmn_map()[p_pkmn]->render(rWin);

	auto c_pkmn = man.get_cpu().get_current_pkmn();
	man.get_cpu().get_pkmn_map()[c_pkmn]->render(rWin);
}
