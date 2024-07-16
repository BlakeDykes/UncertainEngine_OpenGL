#include "AnimNames.h"

const char* AnimNames::Stringify(AnimName name)
{
	switch (name)
	{
		
	// Claire
	case AnimName::S_CLAIRE_BASS:						return "Playing bass";
	case AnimName::S_CLAIRE_DANCE_HIGH_KICK:			return "High kick dancing";

	case AnimName::S_CLAIRE_FIST_PUMP:					return "Fist pumping";
	case AnimName::S_CLAIRE_IDLE_HAPPY_SWAY:			return "Idling";
	
	// ChickenBot
	case AnimName::S_CHICKENBOT_IDLE:					return "Idling";
	case AnimName::S_CHICKENBOT_WALK:					return "Walking";
	case AnimName::S_CHICKENBOT_RUN:					return "Running";
	case AnimName::S_CHICKENBOT_DIE_L:					return "Dying left";
	case AnimName::S_CHICKENBOT_DIE_R:					return "Dying right";
	case AnimName::S_CHICKENBOT_HIT_B:					return "Getting hit bottom";
	case AnimName::S_CHICKENBOT_HIT_F:					return "Getting Hit front";
	case AnimName::S_CHICKENBOT_HIT_L:					return "Getting Hit left";
	case AnimName::S_CHICKENBOT_HIT_R:					return "Dying right";
	case AnimName::S_CHICKENBOT_SHOT_D:					return "Shooting down";
	case AnimName::S_CHICKENBOT_SHOT_F:					return "Shooting front";
	case AnimName::S_CHICKENBOT_SHOT_U:					return "Shooting up";
	case AnimName::S_CHICKENBOT_SIDESTEP_L:				return "Sidestepping left";
	case AnimName::S_CHICKENBOT_SIDESTEP_R:				return "Sidestepping right";
	case AnimName::S_CHICKENBOT_TURN_L:					return "Turning left";
	case AnimName::S_CHICKENBOT_TURN_R:					return "Turning right";

	// Grandma
	case AnimName::S_GRANDMA_DANCE_BBOY_HH:				return "BBoy dancing";
	case AnimName::S_GRANDMA_DANCE_MACARENA:			return "Macarena dancing";
	case AnimName::S_GRANDMA_IDLE:						return "Idling";
	case AnimName::S_GRANDMA_CHEER:						return "Cheer";
	case AnimName::S_GRANDMA_RAP:						return "Rap";
	case AnimName::S_GRANDMA_VICTORY:					return "Victory!";

	// Knight
	case AnimName::S_KNIGHT_CLAP_SIT:					return "Sitting claping";
	case AnimName::S_KNIGHT_IDLE_HAPPY:					return "Happy Idling";
	case AnimName::S_KNIGHT_PIANO:						return "Playing piano";
	case AnimName::S_KNIGHT_IDLE_SIT:					return "Sitting Idle";
	case AnimName::S_KNIGHT_DANCE_SILLY:				return "Silly dancing";

	// Michelle
	case AnimName::S_MICHELLE_IDLE:						return "Idling";
	case AnimName::S_MICHELLE_CHEER:					return "Cheering";
	case AnimName::S_MICHELLE_REACT:					return "Reacting";
	case AnimName::S_MICHELLE_TALK:						return "Talking";
	case AnimName::S_MICHELLE_DANCE_MARA_STEP:			return "Maraschino Step Dancing";
	case AnimName::S_MICHELLE_DANCE_NSS_COMBO:			return "Northern Soul Spin Dancing";

	// Mouse
	case AnimName::S_MOUSE_DANCE_JAZZ:					return "High kick jazz dancing";
	case AnimName::S_MOUSE_DANCE_SALSA:					return "Salsa dancing";
	case AnimName::S_MOUSE_DANCE_SILLY:					return "Silly dancing";
	case AnimName::S_MOUSE_DANCE_TWERK:					return "Twerking";
	case AnimName::S_MOUSE_IDLE:						return "Idling";
	case AnimName::S_MOUSE_JOYFUL_JUMP:					return "Joyful jumping";
	case AnimName::S_MOUSE_RUN_GOOFY:					return "Goofy runing";
	case AnimName::S_MOUSE_WALK:						return "Walking";
	case AnimName::S_MOUSE_GUITAR:						return "Playing guitar";

	// Ninja
	case AnimName::S_NINJA_CHEER:						return "Cheering";
	case AnimName::S_NINJA_DANCE_FLAIR:					return "Flair dancing";
	case AnimName::S_NINJA_DANCE_HOUSE:					return "House dancing";
	case AnimName::S_NINJA_IDLE:						return "Idling";
	case AnimName::S_NINJA_PUSH_UP:						return "Push up";
	case AnimName::S_NINJA_JAM:							return "Jamming out";

	// Ortiz
	case AnimName::S_ORTIZ_CHEER:						return "Cheering";
	case AnimName::S_ORTIZ_DANCE:						return "Dancing";
	case AnimName::S_ORTIZ_JAM:							return "Jamming out";
	case AnimName::S_ORTIZ_DANCE_SWING:					return "Swing dancing";
	case AnimName::S_ORTIZ_IDLE:						return "Idling";

	// Paladin
	case AnimName::S_PALADIN_DANCE_HOKEY_POKEY:			return "Hokey pokey dancing";
	case AnimName::S_PALADIN_CHEER:						return "Cheering";
	case AnimName::S_PALADIN_DANCE_SILLY:				return "Silly dancing";
	case AnimName::S_PALADIN_IDLE_HAPPY:				return "Happy Idling";
	case AnimName::S_PALADIN_BASS:						return "Playing bass";

	// Pumpkin Hulk
	case AnimName::S_PUMPKIN_HULK_DANCE_HOKEY_POKEY:	return "Hokey pokey dancing";
	case AnimName::S_PUMPKIN_HULK_DRUMS:				return "Playing drums";
	case AnimName::S_PUMPKIN_HULK_EXCITED:				return "Excited dancing";
	case AnimName::S_PUMPKIN_HULK_IDLE:					return "Idling";
	case AnimName::S_PUMPKIN_HULK_IDLE_SIT:				return "SItting idle";
	case AnimName::S_PUMPKIN_HULK_FIST_PUMP_SITTING:	return "Sitting fist pump";

	// Vanguard
	case AnimName::S_VANGUARD_CHEER:					return "Cheering";
	case AnimName::S_VANGUARD_DANCE_SALSA_1:			return "Salsa dancing - pt1";
	case AnimName::S_VANGUARD_DANCE_SALSA_2:			return "Salsa dancing - pt2";
	case AnimName::S_VANGUARD_IDLE_HAPPY:				return "Happy idle";
	case AnimName::S_VANGUARD_JAM:						return "Jamming out";
	case AnimName::S_VANGUARD_SING:						return "Singing";


	// Zombie Girl
	case AnimName::S_ZOMBIE_GIRL_AGONIZE:				return "Agonizing";
	case AnimName::S_ZOMBIE_GIRL_CHEER:					return "Cheering";
	case AnimName::S_ZOMBIE_GIRL_DANCE_MARA_STEP:		return "Maraschino step dancing";
	case AnimName::S_ZOMBIE_GIRL_DANCE_YMCA:			return "YMCA dancing";
	case AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER:			return "Thriller idling";


	case AnimName::NULL_ANIM:							return "NULL";
	case AnimName::BLEND_ANIM:							return "BLEND";


	case AnimName::UNINITIALIZED:						return "Uninitialized";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* AnimNames::GetFileName(AnimName name)
{
	switch (name)
	{

	// Claire
	case AnimName::S_CLAIRE_BASS:						return "model_claire/Animation/anim_s_bass";
	case AnimName::S_CLAIRE_DANCE_HIGH_KICK:			return "model_claire/Animation/anim_s_dance_high_kick";
	case AnimName::S_CLAIRE_FIST_PUMP:					return "model_claire/Animation/anim_s_fist_pump";
	case AnimName::S_CLAIRE_IDLE_HAPPY_SWAY:			return "model_claire/Animation/anim_s_idle_happy_sway";

	// ChickenBot
	case AnimName::S_CHICKENBOT_IDLE:					return "model_chickenBot/Animation/anim_s_idle";
	case AnimName::S_CHICKENBOT_WALK:					return "model_chickenBot/Animation/anim_s_walk";
	case AnimName::S_CHICKENBOT_RUN:					return "model_chickenBot/Animation/anim_s_run";
	case AnimName::S_CHICKENBOT_DIE_L:					return "model_chickenBot/Animation/anim_s_die_l";
	case AnimName::S_CHICKENBOT_DIE_R:					return "model_chickenBot/Animation/anim_s_die_r";
	case AnimName::S_CHICKENBOT_HIT_B:					return "model_chickenBot/Animation/anim_s_hit_b";
	case AnimName::S_CHICKENBOT_HIT_F:					return "model_chickenBot/Animation/anim_s_hit_f";
	case AnimName::S_CHICKENBOT_HIT_L:					return "model_chickenBot/Animation/anim_s_hit_l";
	case AnimName::S_CHICKENBOT_HIT_R:					return "model_chickenBot/Animation/anim_s_hit_r";
	case AnimName::S_CHICKENBOT_SHOT_D:					return "model_chickenBot/Animation/anim_s_shot_d";
	case AnimName::S_CHICKENBOT_SHOT_F:					return "model_chickenBot/Animation/anim_s_shot_f";
	case AnimName::S_CHICKENBOT_SHOT_U:					return "model_chickenBot/Animation/anim_s_shot_u";
	case AnimName::S_CHICKENBOT_SIDESTEP_L:				return "model_chickenBot/Animation/anim_s_sidestep_l";
	case AnimName::S_CHICKENBOT_SIDESTEP_R:				return "model_chickenBot/Animation/anim_s_sidestep_r";
	case AnimName::S_CHICKENBOT_TURN_L:					return "model_chickenBot/Animation/anim_s_turn_l";
	case AnimName::S_CHICKENBOT_TURN_R:					return "model_chickenBot/Animation/anim_s_turn_r";
	
	// Grandma
	case AnimName::S_GRANDMA_CHEER:						return "model_grandma/Animation/anim_s_cheer";
	case AnimName::S_GRANDMA_DANCE_BBOY_HH:				return "model_grandma/Animation/anim_s_dance_bboy";
	case AnimName::S_GRANDMA_DANCE_MACARENA:			return "model_grandma/Animation/anim_s_dance_macarena";
	case AnimName::S_GRANDMA_IDLE:						return "model_grandma/Animation/anim_s_idle";
	case AnimName::S_GRANDMA_RAP:						return "model_grandma/Animation/anim_s_rap";
	case AnimName::S_GRANDMA_VICTORY:					return "model_grandma/Animation/anim_s_victory";

	// Knight
	case AnimName::S_KNIGHT_CLAP_SIT:					return "model_knight/Animation/anim_s_clap_sitting";
	case AnimName::S_KNIGHT_IDLE_HAPPY:					return "model_knight/Animation/anim_s_idle_happy";
	case AnimName::S_KNIGHT_PIANO:						return "model_knight/Animation/anim_s_piano";
	case AnimName::S_KNIGHT_IDLE_SIT:					return "model_knight/Animation/anim_s_idle_sit";
	case AnimName::S_KNIGHT_DANCE_SILLY:				return "model_knight/Animation/anim_s_dance_silly";

	// Michelle
	case AnimName::S_MICHELLE_CHEER:					return "model_michelle/Animation/anim_s_cheer";
	case AnimName::S_MICHELLE_IDLE:						return "model_michelle/Animation/anim_s_idle";
	case AnimName::S_MICHELLE_REACT:					return "model_michelle/Animation/anim_s_react";
	case AnimName::S_MICHELLE_TALK:						return "model_michelle/Animation/anim_s_talking";
	case AnimName::S_MICHELLE_DANCE_MARA_STEP:			return "model_michelle/Animation/anim_s_dance_mara_step";
	case AnimName::S_MICHELLE_DANCE_NSS_COMBO:			return "model_michelle/Animation/anim_s_dance_nss_combo";

	// Mouse
	case AnimName::S_MOUSE_DANCE_JAZZ:					return "model_mouse/Animation/anim_s_dance_jazz";
	case AnimName::S_MOUSE_DANCE_SALSA:					return "model_mouse/Animation/anim_s_dance_salsa";
	case AnimName::S_MOUSE_DANCE_SILLY:					return "model_mouse/Animation/anim_s_dance_silly";
	case AnimName::S_MOUSE_DANCE_TWERK:					return "model_mouse/Animation/anim_s_dance_twerk";
	case AnimName::S_MOUSE_IDLE:						return "model_mouse/Animation/anim_s_idle_happy";
	case AnimName::S_MOUSE_GUITAR:						return "model_mouse/Animation/anim_s_guitar";
	case AnimName::S_MOUSE_JOYFUL_JUMP:					return "model_mouse/Animation/anim_s_joyful_jump";
	case AnimName::S_MOUSE_RUN_GOOFY:					return "model_mouse/Animation/anim_s_run_goofy";
	case AnimName::S_MOUSE_WALK:						return "model_mouse/Animation/anim_s_walk";


	// Ninja
	case AnimName::S_NINJA_CHEER:						return "model_ninja/Animation/anim_s_cheering";
	case AnimName::S_NINJA_IDLE:						return "model_ninja/Animation/anim_s_idle";
	case AnimName::S_NINJA_JAM:							return "model_ninja/Animation/anim_s_jam";
	case AnimName::S_NINJA_PUSH_UP:						return "model_ninja/Animation/anim_s_push_up";
	case AnimName::S_NINJA_DANCE_FLAIR:					return "model_ninja/Animation/anim_s_dance_flair";
	case AnimName::S_NINJA_DANCE_HOUSE:					return "model_ninja/Animation/anim_s_dance_house";


	// Ortiz
	case AnimName::S_ORTIZ_CHEER:						return "model_ortiz/Animation/anim_s_cheer";
	case AnimName::S_ORTIZ_DANCE:						return "model_ortiz/Animation/anim_s_dance";
	case AnimName::S_ORTIZ_DANCE_SWING:					return "model_ortiz/Animation/anim_s_dance_swing";
	case AnimName::S_ORTIZ_IDLE:						return "model_ortiz/Animation/anim_s_idle";
	case AnimName::S_ORTIZ_JAM:							return "model_ortiz/Animation/anim_s_jam";

	// Paladin
	case AnimName::S_PALADIN_BASS:						return "model_paladin/Animation/anim_s_bass";
	case AnimName::S_PALADIN_CHEER:						return "model_paladin/Animation/anim_s_cheer";
	case AnimName::S_PALADIN_DANCE_HOKEY_POKEY:			return "model_paladin/Animation/anim_s_dance_hokey_pokey";
	case AnimName::S_PALADIN_DANCE_SILLY:				return "model_paladin/Animation/anim_s_dance_silly";
	case AnimName::S_PALADIN_IDLE_HAPPY:				return "model_paladin/Animation/anim_s_idle_happy";

	// Pumpkin Hulk
	case AnimName::S_PUMPKIN_HULK_DRUMS:				return "model_pumpkinHulk/Animation/anim_s_drums";
	case AnimName::S_PUMPKIN_HULK_DANCE_HOKEY_POKEY:	return "model_pumpkinHulk/Animation/anim_s_dance_hokey_pokey";
	case AnimName::S_PUMPKIN_HULK_EXCITED:				return "model_pumpkinHulk/Animation/anim_s_excited";
	case AnimName::S_PUMPKIN_HULK_IDLE:					return "model_pumpkinHulk/Animation/anim_s_idle";
	case AnimName::S_PUMPKIN_HULK_IDLE_SIT:				return "model_pumpkinHulk/Animation/anim_s_idle_sitting";
	case AnimName::S_PUMPKIN_HULK_FIST_PUMP_SITTING:	return "model_pumpkinHulk/Animation/anim_s_fist_pump_sitting";


	// Vanguard
	case AnimName::S_VANGUARD_CHEER:					return "model_vanguard/Animation/anim_s_cheer";
	case AnimName::S_VANGUARD_DANCE_SALSA_1:			return "model_vanguard/Animation/anim_s_dance_salsa_1";
	case AnimName::S_VANGUARD_DANCE_SALSA_2:			return "model_vanguard/Animation/anim_s_dance_salsa_2";
	case AnimName::S_VANGUARD_IDLE_HAPPY:				return "model_vanguard/Animation/anim_s_idle_happy";
	case AnimName::S_VANGUARD_JAM:						return "model_vanguard/Animation/anim_s_jam";
	case AnimName::S_VANGUARD_SING:						return "model_vanguard/Animation/anim_s_sing";

	// Zombie Girl
	case AnimName::S_ZOMBIE_GIRL_AGONIZE:				return "model_zombieGirl/Animation/anim_s_agonizing";
	case AnimName::S_ZOMBIE_GIRL_CHEER:					return "model_zombieGirl/Animation/anim_s_cheer";
	case AnimName::S_ZOMBIE_GIRL_DANCE_MARA_STEP:		return "model_zombieGirl/Animation/anim_s_dance_mara_step";
	case AnimName::S_ZOMBIE_GIRL_DANCE_YMCA:			return "model_zombieGirl/Animation/anim_s_dance_ymca";
	case AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER:			return "model_zombieGirl/Animation/anim_s_thriller_idle";


	case AnimName::BLEND_ANIM:						
	case AnimName::NULL_ANIM:
	case AnimName::UNINITIALIZED:
	default:
		// name not added to switch
		assert(false);
		return nullptr;
		break;
	}
}