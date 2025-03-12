#pragma once


#include "enemy.h"

class barrels : public enemy
{
	int def_x, def_y;
	const char ch = 'O';
	Direction last_dir{ 0, 0 };	// Direction before falling
	bool active = false;		//Active barrel or not 

	bool explode = false;
	int fall_counter = 0;

public:
	void draw() const {
		if (get_active()) { enemy::draw(ch); } //Draw only when active son wont draw again after explode
	}

	bool cycle_barrel();		//One cycle of barrel
	//return true if exploded 
	bool get_active() const { return active; }	//Checks if the barrel is active 
	void set_active(bool act) { active = act; explode = false;} //resets active and explode value
	bool b_is_on_platform() const;		//Checks if on platform
	void b_where_to_move();			//Initialize the direction before moving 
	void set_default_position() { x = def_x, y = def_y; }		//Initial state of barrel
	void set_default(int x_, int y_) { def_x = x_, def_y = y_; }

	void barrel_explode();
};

