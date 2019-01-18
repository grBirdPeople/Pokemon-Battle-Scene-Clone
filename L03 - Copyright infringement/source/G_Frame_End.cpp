#include "../include/G_Frame_End.h"

#include "../include/Chr_Player.h"
#include "../include/G_Frame_Start.h"
#include "../include/G_Menu.h"
#include "../include/Input.h"



// cTor
G_Frame_End::G_Frame_End(Manager& man)
	:
		txt_scale_title_	(30),
		txt_scale_menu_		(15),
		x_offset_			(80.0f),
		g_menu_				(new G_Menu)
{
	build_menu(man.get_winner_player() ? "You win!!!" : "You loose...");
}



// dTor
G_Frame_End::~G_Frame_End()
{
	AUTO_DEL(g_menu_);
}



// build_menu
void G_Frame_End::build_menu(const str& winner)
{
	// Create text
	vec2f title_pos	(320.0f, 130.0f);
	vec2f start_pos	(320.0f, 170.0f);
	vec2f end_pos	(320.0f, 190.0f);

	g_menu_->add_txt_obj("winLoose",	title_pos,	txt_scale_menu_,	winner,			true);
	g_menu_->add_txt_obj("main",		start_pos,	11,					"Main menu",	true);
	g_menu_->add_txt_obj("quit",		end_pos,	11,					"Quit",			true);

	// Create arrow positions
	g_menu_->add_arrow_pos(vec2f(start_pos.x - x_offset_,	start_pos.y));
	g_menu_->add_arrow_pos(vec2f(end_pos.x - x_offset_,		end_pos.y));

	g_menu_->set_arrow_pos(vec2f(start_pos.x - x_offset_,	start_pos.y));
}



// handle_input
G_Frame* G_Frame_End::handle_input(Manager & man)
{
	// Make so menus aren't all flipitiflopiti
	if (!Input::is_pressed(sf::Keyboard::Enter) && pressed_enter_)
		pressed_enter_ = false;

	// Do menu things
	g_menu_->handle_input();



	// Check if a state switch should occur
	if (Input::is_pressed(sf::Keyboard::Enter) && !pressed_enter_) // 0 equals start (see above cTor for adding arrow pos to vector ((bad solution, will fix when / if time))
	{
		pressed_enter_ = true;

		if (g_menu_->get_current_arrow_pos() == 0)
			return new G_Frame_Start(man);

		if (g_menu_->get_current_arrow_pos() == 1)
			man.terminate();
	}



	// No state change, so return null
	return nullptr;
}



// update
void G_Frame_End::update(const float deltaT, Manager & man)
{}



// render
void G_Frame_End::render(sf::RenderWindow& rWin, Manager & man)
{
	g_menu_->render(rWin);
}
