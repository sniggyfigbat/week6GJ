#pragma once

#include <array>

#include "consoleMaterial.h"
#include "gameObject.h"

#define uint unsigned int
#define usint unsigned short int

#define PI 3.1415927410125732421875f
#define RAD2DEG 180.0f/PI
#define DEG2RAD PI/180.0f

#define WORLD_X_METERS 60
#define WORLD_Y_METERS 30
#define WORLD_X_CHARS 360
#define WORLD_Y_CHARS 90

class Terrain : public GameObject
{
	// Four bits, used for actual game logic
	enum Function {
		Empty = 0,
		Full = 1,
		SlopeTR = 2,
		SlopeTL = 3,
		SlopeBL = 4,
		SlopeBR = 5,
		LeftSpike = 6,
		UpSpike = 7,
		RightSpike = 8,
		DownSpike = 9,
		AllFunction = 15
	};
	// Five bits, used for display chars.
	enum Form {
		EmptyBlock		= 0<<4,
		FullBlock		= 1<<4,
		ForwardSlash	= 2<<4,
		BackSlash		= 3<<4,
		LeftSpikeChar	= 4<<4,
		UpSpikeChar		= 5<<4,
		RightSpikeChar	= 6<<4,
		DownSpikeChar	= 7<<4,
		SmallRock		= 8<<4,
		BigRock			= 9<<4,
		PipeHorizontal	= 10<<4,	// ═
		PipeVertical	= 11<<4,	// ║
		PipeTRCorner	= 12<<4,	// ╗
		PipeBRCorner	= 13<<4,	// ╝
		PipeBLCorner	= 14<<4,	// ╚
		PipeTLCorner	= 15<<4,	// ╔
		PipeTjLeft		= 16<<4,	// ╣
		PipeTjUp		= 17<<4,	// ╩
		PipeTjRight		= 18<<4,	// ╠
		PipeTjDown		= 19<<4,	// ╦
		PipeCore		= 20<<4,	// ╬
		AllForm			= 31<<4
	};
	// Two bits, used for colour
	enum Colour {
		Green	= 0<<9,
		GreenD	= 1<<9,
		Grey	= 2<<9,
		GreyD	= 3<<9,
		isGrey	= 2<<9,
		AllColour = 3<<9
	};
private:
	ConsoleMaterial m_material;

	std::array<std::array<usint, WORLD_Y_CHARS>, WORLD_X_CHARS> m_world;

	// Box2d object
public:
	Terrain();
	~Terrain();

	void generateTerrain();
	void updateMaterial();

	bool getCharAt(float x, float y, usint * & out);

	inline const ConsoleMaterial & getMaterial() { return m_material; }

	void onKeyPress(int keyPress) override {};
	void onUpdate(float timestep) override {};
	void onDelete() override {};
};