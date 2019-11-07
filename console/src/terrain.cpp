#include "terrain.h"

enum Diag {
	TL,
	TR,
	BR,
	BL
};

b2Vec2 adjust(const b2Vec2 & in, Diag dir) {
	b2Vec2 adj = b2Vec2(1.0f / 12.0f, 1.0f / 6.0f);
	adj.x = (dir == Diag::TL || dir == Diag::BL) ? -1.0f / 12.0f : 1.0f / 12.0f;
	adj.y = (dir == Diag::TL || dir == Diag::TR) ? -1.0f / 6.0f : 1.0f / 6.0f;
	return b2Vec2(adj);
}

void Terrain::updateLine(glm::vec2 startPoint)
{
	bool done = false;
	std::queue<b2Vec2> points;

	enum Paths {
		OnTop,
		SlopeBL,
		OnRight,
		SlopeTL,
		OnBottom,
		SlopeTR,
		OnLeft,
		SlopeBR
	};

	glm::ivec2 focus;
	Paths direction;

	bool found = false;
	for (uint y = 0; found == false && y < WORLD_Y_CHARS; y++) {
		usint typeOf = (m_world[0][y] & Function::AllFunction);
		if (typeOf != Function::Empty && typeOf != Function::LeftSpike && typeOf != Function::DownSpike) {
			focus.x = 0;
			focus.y = y;

			if (typeOf == Function::UpSpike || typeOf == Function::SlopeBR) {
				found = true;
				points.push(adjust(b2Vec2(0.0f, (y / 3.0f)), Diag::BL));
				direction = Paths::SlopeBR;
			}
			else if (typeOf == Function::RightSpike || typeOf == Function::SlopeBL) {
				found = true;
				points.push(adjust(b2Vec2(0.0f, (y / 3.0f)), Diag::TL));
				direction = Paths::SlopeBL;
			}
			else if (typeOf == Function::Full) {
				found = true;
				points.push(adjust(b2Vec2(0.0f, (y / 3.0f)), Diag::TL));
				direction = Paths::OnTop;
			}
		}
	}

	found = false;
	while (!found) {
				
		//switch () {};
	}
}

Terrain::Terrain(b2World * world) : m_b2world(world)
{
	m_material.setSize(glm::ivec2(WORLD_X_CHARS, WORLD_Y_CHARS));
	m_material.setCount(WORLD_X_CHARS * WORLD_Y_CHARS);
	m_material.setPosition(glm::ivec2(0, 0));

	char d[WORLD_X_CHARS * WORLD_Y_CHARS] = {0};
	m_material.setData(&d[0]);

	// Line setup
	b2BodyDef bodDef;
	bodDef.type = b2_staticBody;
	bodDef.position.SetZero();
	m_body = m_b2world->CreateBody(&bodDef);

	b2ChainShape edge;
	b2Vec2 vs[4];
	vs[0].Set(0.0f, 15.0f);
	vs[1].Set(10.0f, 25.0f);
	vs[2].Set(50.0f, 5.0f);
	vs[3].Set(60.0f, 15.0f);
	edge.CreateChain(vs, 4);
	
	b2FixtureDef fixDef;
	fixDef.friction = 0.2f;
	fixDef.restitution = 0.5f;
	fixDef.shape = &edge;
	m_body->CreateFixture(&fixDef);

	generateTerrain();
	updateMaterial();
}

Terrain::~Terrain()
{
}

void Terrain::generateTerrain()
{

	for (float x = 0.0f; x <= WORLD_X_METERS; x += 1.0f/6.0f) {
		float h = WORLD_Y_METERS - (10.0f * std::sin(x / 6.0f)) - 15.0f;
		float d = ((5.0f/3.0f) * std::cos(x / 6.0f)) * RAD2DEG;

		int t = ((int)std::abs(d) % 90);
		bool isSlope = (std::abs(45 - t) < 23);
		usint * surface = nullptr;
		bool changeOverInLevel = getCharAt(x, h, surface);
		
		for (float y = 0.0f; y <= WORLD_Y_METERS; y += 1.0f / 3.0f) {
			usint * current = nullptr;
			if (getCharAt(x, y, current)) {
				if (current == surface && isSlope) {
					if (d > 0) { *current = (usint)(Colour::Green | Form::ForwardSlash | Function::SlopeBR); }
					else {*current = (usint)(Colour::Green | Form::BackSlash | Function::SlopeBL); }
				}
				else if (y > h) { *current = (usint)(Colour::Green | Form::FullBlock | Function::Full); }
				else { *current = (usint)(Colour::Green | Form::EmptyBlock | Function::Empty); }
			}
		}
	}

	// Clean up slopes
	for (uint y = 0; y < WORLD_Y_CHARS; y++) {
		for (uint x = 0; x < WORLD_X_CHARS - 1; x++) {
			usint & current = m_world[x][y];
			usint & test = m_world[x + 1][y];
				if ((current & Function::AllFunction) == Function::SlopeBR) {
					usint typeCheck = (test & Function::AllFunction);
					if (typeCheck == Function::Empty || typeCheck == Function::UpSpike) { current = (Colour::Green | Form::UpSpikeChar | Function::UpSpike); }
					else if (typeCheck == Function::SlopeBR) { current = (Colour::Green | Form::EmptyBlock | Function::Empty); }
				}
		}

		for (uint x = WORLD_X_CHARS - 1; x > 0; x--) {
			usint & current = m_world[x][y];
			usint & test = m_world[x - 1][y];
			if ((current & Function::AllFunction) == Function::SlopeBL) {
				usint typeCheck = (test & Function::AllFunction);
				if (typeCheck == Function::Empty || typeCheck == Function::UpSpike) { current = (Colour::Green | Form::UpSpikeChar | Function::UpSpike); }
				else if (typeCheck == Function::SlopeBL) { current = (Colour::Green | Form::EmptyBlock | Function::Empty); }
			}
		}
	}
}

void Terrain::updateMaterial()
{
	char d[WORLD_X_CHARS * WORLD_Y_CHARS] = { 0 };

	usint j = 0;
	for (uint y = 0; y < WORLD_Y_CHARS; y++) {
		for (uint x = 0; x < WORLD_X_CHARS; x++) {
			usint & data = m_world[x][y];
			Function func = (Function)(data & (usint)Function::AllFunction);
			Form form = (Form)(data & (usint)Form::AllForm);
			Colour col = (Colour)(data & (usint)Colour::AllColour);

			Form desForm = Form::EmptyBlock;
			Colour desCol = Colour::GreyD;
			char out = ' ';
			switch (func){
			case (Function::Full):
				if (
					(form == Form::FullBlock) ||
					((usint)form >= (usint)Form::SmallRock)) {
					desForm = form;
				}
				else { form = Form::FullBlock; }

				switch (desForm) {
				case Form::SmallRock:
					out = 'o';
					break;
				case Form::BigRock:
					out = 'O';
					break;
				case Form::PipeHorizontal:
					out = char(205);
					break;
				case Form::PipeVertical:
					out = char(186);
					break;
				case Form::PipeTRCorner:
					out = char(187);
					break;
				case Form::PipeBRCorner:
					out = char(188);
					break;
				case Form::PipeBLCorner:
					out = char(200);
					break;
				case Form::PipeTLCorner:
					out = char(201);
					break;
				case Form::PipeTjLeft:
					out = char(185);
					break;
				case Form::PipeTjUp:
					out = char(202);
					break;
				case Form::PipeTjRight:
					out = char(204);
					break;
				case Form::PipeTjDown:
					out = char(203);
					break;
				case Form::PipeCore:
					out = char(206);
					break;
				case Form::FullBlock:
				default:
					out = char(219);
					break;
				}

				if (form == Form::FullBlock) { desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD; }
				else { desCol = (col & Colour::isGrey) ? Colour::Grey : Colour::Green; }
				break;
			case (Function::SlopeTR):
				desForm = Form::BackSlash;
				out = '\\';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::SlopeTL):
				desForm = Form::ForwardSlash;
				out = '/';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::SlopeBL):
				desForm = Form::BackSlash;
				out = '\\';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::SlopeBR):
				desForm = Form::ForwardSlash;
				out = '/';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::LeftSpike):
				desForm = Form::LeftSpikeChar;
				out = '<';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::UpSpike):
				desForm = Form::UpSpikeChar;
				out = 'A';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::RightSpike):
				desForm = Form::RightSpikeChar;
				out = '>';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::DownSpike):
				desForm = Form::DownSpikeChar;
				out = 'V';
				desCol = (col & Colour::isGrey) ? Colour::GreyD : Colour::GreenD;
				break;
			case (Function::Empty):
			default:
				break;
			}

			data = (usint)(desCol | desForm | func);
			d[j] = out;
			j++;
		}
	}

	m_material.setData(&d[0]);
}

bool Terrain::getCharAt(float x, float y, usint * & out)
{
	int xCoord = (int)std::round(x * 6.0f);
	int yCoord = (int)std::round(y * 3.0f);

	if (xCoord < 0 || yCoord < 0) { return false; }
	if (xCoord >= WORLD_X_CHARS || yCoord >= WORLD_Y_CHARS) { return false; }

	out = &m_world[xCoord][yCoord];
	return true;
}
