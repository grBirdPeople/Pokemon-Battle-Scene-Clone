#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../source/Common.cpp"

//class Chr_Player;
//class G_Frame;
class Manager;

using g_clock		= sf::Clock;
using g_event		= sf::Event;
using c_settings	= sf::ContextSettings;
using r_win			= sf::RenderWindow;



class App
{
public:
	App(const u_int winSizeX	= 640,
		const u_int winSizeY	= 360,
		const u_int fps			= 90,
		const str& title		= "No name");

	~App();

	void	set_aa				(const u_int aa);

	void	create_render_win	();

	void	handle_input		();
	void	update				();
	void	render				();
	void	run					();
	void	terminate			();

private:
	u_int		win_size_x_,
				win_size_y_,
				fps_,
				aa_;

	float		g_time_elapsed_total_,
				delta_t_;

	str			title_;

	c_settings*	c_setting_;		// AA
	g_clock*	g_clock_;		// Time
	g_event*	event_;			// Event handler
	r_win*		r_win_;			// Render window

	color*		color_bg_;

	Manager*	manager_;
};



// RGB's 4 color_bg_

// Actual GameBoy colors
// 154
// 164
// 0

// 22
// 73
// 02