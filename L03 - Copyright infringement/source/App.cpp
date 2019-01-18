#include "../include/App.h"

#include <iostream>

#include "../include/Manager.h"
#include "../include/Input.h"



// cTor
App::App(const u_int winSizeX,
		 const u_int winSizeY,
		 const u_int fps,
		 const str& title)
	:
		win_size_x_				(winSizeX),
		win_size_y_				(winSizeY),
		fps_					(fps),
		aa_						(16),
		g_time_elapsed_total_	(0.0f),
		title_					(title),
		g_clock_				(new sf::Clock),
		event_					(new sf::Event),
		r_win_					(new sf::RenderWindow),
		c_setting_				(new sf::ContextSettings),
		color_bg_				(new sf::Color(154, 164, 0))
{
	// What the method name says
	create_render_win();

	// Get keyboard
	Input::init_keys();

	// Arguments are player & enemy spawn pos (equals pokemon sprite battlescreen pos)
	// Some spacing/distance of gui items scales with these values 
	manager_ = new Manager(vec2f(220.0f, 200.0f), vec2f(420.0f, 80.0f));
}



// App
App::~App()
{
	AUTO_DEL(g_clock_);
	AUTO_DEL(event_);
	AUTO_DEL(r_win_);
	AUTO_DEL(c_setting_);
	AUTO_DEL(color_bg_);
}



// set_aa
void App::set_aa(const u_int aa)
{
	aa_ = aa;
}



// create_render_win
void App::create_render_win()
{
	c_setting_->antialiasingLevel = aa_;
	r_win_->create(sf::VideoMode(win_size_x_, win_size_y_), title_, sf::Style::Default, *c_setting_);
	r_win_->setFramerateLimit(fps_);
}



// handle_input
void App::handle_input()
{
	manager_->handle_input();
}



// update
void App::update()
{
	manager_->update(delta_t_);
}



// render
void App::render()
{
	r_win_->	clear(*color_bg_);
	manager_->	render(*r_win_);
	r_win_->	display();
}



// run
void App::run()
{
	// Time thing
	float t_last = g_clock_->getElapsedTime().asSeconds();

	// Game loop
	while (r_win_->isOpen())
	{
		while (r_win_->pollEvent(*event_))
		{
			switch (event_->type)
			{
			case sf::Event::KeyPressed:
				Input::set_pressed(event_->key.code);
				break;

			case sf::Event::KeyReleased:
				Input::set_released(event_->key.code);
				break;

			case sf::Event::Closed:
				r_win_->close();
				break;
			}
		}

		// More time things
		g_time_elapsed_total_	= g_clock_->getElapsedTime().asSeconds();
		delta_t_				= g_time_elapsed_total_ - t_last;
		t_last					= g_time_elapsed_total_;

		// Input
		handle_input();
		// Update
		update();
		// Render
		render();
	}
}



// terminate
void App::terminate()
{
	r_win_->close();
}
