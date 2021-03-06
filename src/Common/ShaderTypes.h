#ifndef SHADER_TYPES_H
#define SHADER_TYPES_H

/**
 * @brief All Shaders TOE can draw with.
 * 
 */

enum SHADERTYPE {
	NONE_SHADER				=-1,
	STANDARD_SHADER 		= 0,
	CARTOON_SHADER  		= 1,
	GHOST_SHADER    		= 2,
    WATER_SHADER    		= 3,
    TEXT_SHADER				= 4,
	TWOD_SHADER				= 5,
	PARTICLE_SHADER			= 6,
	SPRITE_SHADER 			= 7,
	BB_SHADER 				= 8,
	DISTORSION_SHADER 		= 9,
	FISHEYE_SHADER 			= 10,
	BARREL_SHADER 			= 11,
	SHADOW_SHADER			= 12,
	TWODTEXT_SHADER			= 13
};

#endif