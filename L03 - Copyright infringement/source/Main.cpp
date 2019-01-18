// If it doesn't compile and gives error LNK1112, switching system bit to x86 (the dropdown directly left of run button) might solve it.
// Sometimes inputs are missed because of the very low framerate (15 fps), its very bad & authentic & good

#include "../include/App.h"

// Init thing
u_int win_size_x = 640, win_size_y = 360, frames_ps = 15;
str g_title = "PocketMans";



int main()
{
	App app(win_size_x, win_size_y, frames_ps, g_title);
	app.run();
}
