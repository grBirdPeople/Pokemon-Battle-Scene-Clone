#include "../include/G_Frame_Battle.h"

#include <algorithm>
#include <iostream>

#include "../include/Chr_Cpu.h"
#include "../include/Chr_Player.h"
#include "../include/G_Frame_Fight.h"
#include "../include/G_Frame_Pkmn.h"
#include "../include/G_Frame_Start.h"
#include "../include/G_Menu.h"
#include "../include/Input.h"



//cTor
G_Frame_Battle::G_Frame_Battle(Manager& man)
	:
		txt_scale_menu_	(12),
		x_offset_		(22.5f),
		g_menu_			(new G_Menu)
{
	build_menu(man);
}


// dTor
G_Frame_Battle::~G_Frame_Battle()
{
	AUTO_DEL(g_menu_);
}



// build_select_menu
void G_Frame_Battle::build_menu(Manager& man)
{
	// Create menu text
	vec2f fight_select	(400.0f, 280.0f);
	vec2f pkmn_select	(400.0f, 300.0f);
	vec2f main_select	(400.0f, 330.0f);

	g_menu_->add_txt_obj("fight",	fight_select,	txt_scale_menu_,	"Fight");
	g_menu_->add_txt_obj("pkmn",	pkmn_select,	txt_scale_menu_,	"PkMn");
	g_menu_->add_txt_obj("run",		main_select,	10,					"Run");
	
	// Text for currently selected pkmn
	txt_player(man);
	txt_cpu(man);

	// Create cursor positions
	float y_offset = static_cast<float>(g_menu_->get_txt_obj("fight").getLocalBounds().height * 0.5);

	g_menu_->add_arrow_pos(vec2f(fight_select.x - x_offset_,	fight_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(pkmn_select.x - x_offset_,	pkmn_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(main_select.x - x_offset_,	main_select.y + y_offset));

	// Set cursor default pos
	g_menu_->set_arrow_pos(vec2f(fight_select.x - x_offset_, fight_select.y + y_offset));

	// Add border
	g_menu_->add_border(man.get_player_default_pos(), man.get_cpu_default_pos(), true);
}



// txt_player
void G_Frame_Battle::txt_player(Manager& man)
{
	// Text for currently player selected pkmn
	auto current	= man.get_player().get_current_pkmn();
	auto name_pkmn	= man.get_player().get_pkmn(current).get_pkmn_type_name();
	auto health		= man.get_player().get_pkmn(current).get_health_current();
	auto x_pos		= man.get_cpu_default_pos().x;
	auto y_pos		= man.get_player_default_pos().y;

	// Pkmn type name
	std::transform(name_pkmn.begin(), name_pkmn.end(), name_pkmn.begin(), ::toupper);
	g_menu_->add_txt_obj("player_pkmn_name", vec2f(x_pos, y_pos - 10.0f), txt_scale_menu_, name_pkmn, true);

	// Pkmn health
	str health_str = " / ";
	health_str.insert(0, std::to_string(static_cast<int>(health)));
	health_str.append(std::to_string(static_cast<int>(man.get_player().get_pkmn(current).get_health_default())));
	g_menu_->add_txt_obj("player_pkmn_hp", vec2f(x_pos, y_pos + 10.0f), txt_scale_menu_, health_str, true);
}



// txt_cpu
void G_Frame_Battle::txt_cpu(Manager& man)
{
	// Text for currently cpu selected pkmn
	auto current	= man.get_cpu().get_current_pkmn();
	auto name_pkmn	= man.get_cpu().get_pkmn(current).get_pkmn_type_name();
	auto health		= man.get_cpu().get_pkmn(current).get_health_current();
	auto x_pos		= man.get_player_default_pos().x;
	auto y_pos		= man.get_cpu_default_pos().y;

	// Pkmn type name
	std::transform(name_pkmn.begin(), name_pkmn.end(), name_pkmn.begin(), ::toupper);
	g_menu_->add_txt_obj("cpu_pkmn_name", vec2f(x_pos, y_pos - 10.0f), txt_scale_menu_, name_pkmn, true);

	// Pkmn health
	str health_str = " / ";
	health_str.insert(0, std::to_string(static_cast<int>(health)));
	health_str.append(std::to_string(static_cast<int>(man.get_player().get_pkmn(current).get_health_default())));
	g_menu_->add_txt_obj("cpu_pkmn_hp", vec2f(x_pos, y_pos + 10.0f), txt_scale_menu_, health_str, true);
}



// handle_input
G_Frame* G_Frame_Battle::handle_input(Manager& man)
{
	// Make so menus aren't all flipitiflopiti
	if (!Input::is_pressed(sf::Keyboard::Enter) && pressed_enter_)
		pressed_enter_ = false;

	// Do menu things like moving the cursor etc. etc.
	g_menu_->handle_input();



	// Check if a state switch should occur
	if (Input::is_pressed(sf::Keyboard::Enter) && !pressed_enter_)
	{
		pressed_enter_ = true;
		auto current = g_menu_->get_current_arrow_pos();

		// Fight
		if (current == e_BattleOp::FIGHT)
			return new G_Frame_Fight(man);

		// Pkmn select
		if (current == e_BattleOp::PKMN)
			return new G_Frame_Pkmn(man);

		// Main menu // MAYBE REMOVE OR CHANGE or not...
		if (current == e_BattleOp::BACK)
			return new G_Frame_Start(man);
	}

	// No state change, so return null
	return nullptr;
}



// update
void G_Frame_Battle::update(const float deltaT, Manager& man)
{
	// 3xA Animations
	auto p_pkmn = man.get_player().get_current_pkmn();
	man.get_player().get_pkmn_map()[p_pkmn]->update(deltaT);

	auto c_pkmn = man.get_cpu().get_current_pkmn();
	man.get_cpu().get_pkmn_map()[c_pkmn]->update(deltaT);
}



// render
void G_Frame_Battle::render(sf::RenderWindow& rWin, Manager& man)
{
	g_menu_->render(rWin);

	auto p_pkmn = man.get_player().get_current_pkmn();
	man.get_player().get_pkmn_map()[p_pkmn]->render(rWin);

	auto c_pkmn = man.get_cpu().get_current_pkmn();
	man.get_cpu().get_pkmn_map()[c_pkmn]->render(rWin);
}
