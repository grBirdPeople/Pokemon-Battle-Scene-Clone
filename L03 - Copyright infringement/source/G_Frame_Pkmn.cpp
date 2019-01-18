#include "../include/G_Frame_Pkmn.h"

#include <iostream>

#include "../include/Chr_Cpu.h"
#include "../include/Chr_Player.h"
#include "../include/Chr_Pkmn.h"
#include "../include/G_Frame_Battle.h"
#include "../include/G_Menu.h"
#include "../include/Input.h"



//cTorsa
G_Frame_Pkmn::G_Frame_Pkmn(Manager& man)
	:
		txt_scale_			(12),
		x_offset_			(22.5f),
		current_pkmn_type_	(0),
		current_arrow_pos_	(e_PkmnType::BLUE),
		g_menu_				(new G_Menu)
{
	build_menu(man);
}



// dTor
G_Frame_Pkmn::~G_Frame_Pkmn()
{
	AUTO_DEL(g_menu_);
}



// build_menu
void G_Frame_Pkmn::build_menu(Manager& man)
{
	// Create text
	auto spr_origo	= man.get_player_default_pos();
	auto spr_wh		= man.get_player().get_pkmn(0).get_spr().getLocalBounds();
	auto spr_scale	= man.get_player().get_pkmn(0).get_spr().getScale();

	auto select_x	= static_cast<float>(spr_origo.x - ((spr_wh.width * 0.5) * spr_scale.x));
	auto select_y	= static_cast<float>(spr_origo.y - ((spr_wh.height * 0.5) * spr_scale.y) - 55.0f);

	vec2f select_select	(select_x, select_y);
	vec2f blue_select	(400.0f, 280.0f);
	vec2f green_select	(400.0f, 300.0f);
	vec2f red_select	(500.0f, 280.0f);
	vec2f yellow_select	(500.0f, 300.0f);
	vec2f back_select	(500.0f, 330.0f);

	g_menu_->add_txt_obj("select",	select_select,	12,			"Select your pocketman...");
	g_menu_->add_txt_obj("blue",	blue_select,	txt_scale_,	"Blue");
	g_menu_->add_txt_obj("green",	green_select,	txt_scale_,	"Green");
	g_menu_->add_txt_obj("red",		red_select,		txt_scale_,	"Red");
	g_menu_->add_txt_obj("yellow",	yellow_select,	txt_scale_,	"Yellow");
	g_menu_->add_txt_obj("back",	back_select,	10,			"Back");

	// Create cursor positions
	float y_offset = static_cast<float>(g_menu_->get_txt_obj("blue").getLocalBounds().height * 0.5);

	g_menu_->add_arrow_pos(vec2f(blue_select.x - x_offset_,		blue_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(green_select.x - x_offset_,	green_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(red_select.x - x_offset_,		red_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(yellow_select.x - x_offset_,	yellow_select.y + y_offset));
	g_menu_->add_arrow_pos(vec2f(back_select.x - x_offset_,		back_select.y + y_offset));

	// Set default pos
	g_menu_->set_arrow_pos(vec2f(blue_select.x - x_offset_, blue_select.y + y_offset));

	// Text for currently pkmn pointed to by menu cursor
	auto current	= man.get_player().get_current_pkmn();
	auto x_pos		= man.get_cpu_default_pos().x;
	auto y_pos		= man.get_player_default_pos().y;

	// Things for drawing currently pointed to pkmn name & health
	Chr_Pkmn* pkmn = nullptr;
	auto pos_x = man.get_cpu_default_pos().x;
	auto pos_y = man.get_player_default_pos().y;

	for (size_t i = 0; i < e_PkmnType::END; i++)
	{
		Chr_Pkmn* pkmn = &man.get_player().get_pkmn(static_cast<unsigned short>(i));

		auto name = pkmn->get_pkmn_type_name();
		auto name_upper = name;
		std::transform(name_upper.begin(), name_upper.end(), name_upper.begin(), ::toupper);
		g_menu_->add_txt_obj(name.append("_select"), vec2f(pos_x, pos_y - 10.0f), txt_scale_, name_upper, true);

		str health = " / ";
		health.insert(0, std::to_string(static_cast<int>(pkmn->get_health_current())));
		health.append(std::to_string(static_cast<int>(pkmn->get_health_default())));
		g_menu_->add_txt_obj(name.append("_select_hp"), vec2f(pos_x, pos_y + 10.0f), txt_scale_, health, true);
	}

	pkmn = nullptr;

	// Add border
	g_menu_->add_border(man.get_player_default_pos(), man.get_cpu_default_pos(), false);
}



// handle_input
G_Frame* G_Frame_Pkmn::handle_input(Manager& man)
{
	// Make so menus aren't all flipitiflopiti
	if (!Input::is_pressed(sf::Keyboard::Enter) && pressed_enter_)
		pressed_enter_ = false;

	// Do menu things like moving the cursor etc. etc.
	g_menu_->handle_input();
	current_arrow_pos_ = g_menu_->get_current_arrow_pos();	// There is only 4 pkmn's, so only draw if arrow pos points to something legit

	// Check if a state switch should occur
	if (Input::is_pressed(sf::Keyboard::Enter) && !pressed_enter_)
	{
			pressed_enter_ = true;

			if (current_arrow_pos_ != e_PkmnType::END)
			{
				// Set selected pkmn if it's alive
				if (!man.get_player().get_pkmn(current_arrow_pos_).get_is_dead())
				{
					man.get_player().set_current_pkmn(current_arrow_pos_);

					// Return to previous screen
					return new G_Frame_Battle(man);
				}
			}
			else
				return new G_Frame_Battle(man);
	}

	// No state change, so return null
	return nullptr;
}



// update
void G_Frame_Pkmn::update(const float deltaT, Manager& man)
{
	// 3xA Animations
	for (auto& i : man.get_player().get_pkmn_map())
		i.second->update(deltaT);
}



// render
void G_Frame_Pkmn::render(sf::RenderWindow& rWin, Manager& man)
{
	// Select txt
	rWin.draw(g_menu_->get_txt_obj("select"));

	// Draws border, name & health for the currently pointed to pkmn
	if (current_arrow_pos_ != e_PkmnType::END)
	{
		rWin.draw(g_menu_->get_border_spr_p());

		auto name = man.get_player().get_pkmn(current_arrow_pos_).get_pkmn_type_name();
		rWin.draw(g_menu_->get_txt_obj(name.append("_select")));
		rWin.draw(g_menu_->get_txt_obj(name.append("_select_hp")));

		rWin.draw(man.get_player().get_pkmn(current_arrow_pos_).get_spr());
	}

	// Draws menu cursor
	rWin.draw(g_menu_->get_arrow_spr());

	// a dumb way to draw the menu options
	for (auto& i : g_menu_->get_txt_obj_map())
	{
		if (i.first == "blue"	||
			i.first == "green"	||
			i.first == "red"	||
			i.first == "yellow"	||
			i.first == "back")
		{
			rWin.draw(*i.second);
		}
	}
}
