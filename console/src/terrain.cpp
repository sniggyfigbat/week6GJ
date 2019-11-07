#include "terrain.h"

Terrain::Terrain()
{
	m_material.setSize(glm::ivec2(WORLD_X_CHARS, WORLD_Y_CHARS));
	m_material.setCount(WORLD_X_CHARS * WORLD_Y_CHARS);
	m_material.setPosition(glm::ivec2(0, 0));

	char d[WORLD_X_CHARS * WORLD_Y_CHARS] = {0};
	m_material.setData(&d[0]);

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
