#pragma once
#include <string>
#include "Animation.h"


struct Character {
	std::string name;
	PlayerAnim anim;

	Character() {
		anim.addAnimation("STAND", Animation(0, 5, 0.25f, false));
		anim.addAnimation("WALK FRONT", Animation(5, 5, 0.25f, false));
		anim.addAnimation("WALK BACK", Animation(10, 5, 0.2f, false));
		anim.addAnimation("HURT FRONT", Animation(11, 1, 0.2f, false));
		anim.addAnimation("HURT BACK", Animation(12, 1, 0.2f, false));

		anim.play("STAND");
	}
};
#pragma once
	