#include "../include/Input.h"

unsigned short	Input::key_count_;
v_keys			Input::keys_;



// init_keys
void Input::init_keys()
{
	key_count_ = sf::Keyboard::KeyCount;

	for (std::size_t i = 0; i < key_count_; i++)
		keys_.push_back(false);
}


// clear_keys
void Input::clear_keys()
{
	for (std::size_t i = 0; i < key_count_; i++)
		keys_[i] = false;
}



// set_pressed
void Input::set_pressed(sf::Keyboard::Key key)
{
	keys_[key] = true;
}



// set_released
void Input::set_released(sf::Keyboard::Key key)
{
	keys_[key] = false;
}



// is_pressed
bool Input::is_pressed(sf::Keyboard::Key key)
{
	return keys_[key];
}