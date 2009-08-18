#include "TDG.h"

const char* g_snideText[] =
{
	"INSPECTOR SNIDE:      ",
	"SCOTLAND YARD         ",
	"DETECTIVE PLAYED BY   ",
	"YOURSELF.             ",
	"                      "
};

const char* g_reverandText[] =
{
	"REVERAND WRINKLEBUM:  ",
	"LOCAL VICAR WHOSE     ",
	"WIFE DISSAPEARED IN   ",
	"MYSTERIOUS            ",
	"CIRCUMSTANCES         "
};

const char* g_bentleyText[] =
{
	"BENTLEY THE BUTLER:   ",
	"LIFELONG SERVANT TO   ",
	"THE MCFUNGUS FAMILY.  ",
	"EXHIBITS SLIGHTLY     ",
	"HOSTILE BEHAVIOR..    "
};

const char* g_cookText[] =
{
	"HILDA CRUMBLE:        ",
	"FAMILY COOK.          ",
	"NOTORIOUS FOR HER     ",
	"MACARONI  CHEESE.     ",
	"                      "
};



const char* g_gabrielText[] =
{
	"GABRIEL GASBAG:       ",
	"THE MAID. OBEDIENT    ",
	"AND AGREEABLE, BUT    ",
	"NOT VERY BRIGHT.      ",
	"                      "
};

const char* g_cynthiaText[] =
{
	"CYNTHIA SLUDGEBUCKET: ",
	"ARROGANT AND SELF     ",
	"CENTRED DAUGHTER OF   ",
	"THE MAJOR.            ",
	"                      "
};

const char* g_professorText[] =
{
	"PROFESSOR BULL:       ",
	"OLD FRIEND OF THE     ",
	"LATE MR. MCFUNGUS.    ",
	"SCATTERBRAINED AND    ",
	"COMPLETELY MAD.       "
};

const char* g_doctorText[] =
{
	"DOCTOR MORTEM:        ",
	"SHORTSIGHTED FAMILY   ",
	"DOCTOR.               ",
	"                      ",
	"                      "
};

const char* g_majorText[] =
{
	"MAJOR SLUDGEBUCKET:   ",
	"RETIRED MAJOR.        ",
	"DISTURBED BUT         ",
	"HARMLESS.             ",
	"                      "
};

const char* g_dingleText[] =
{
	"MR DINGLE:            ",
	"FAMILY SOLICITOR.     ",
	"HERE TO READ THE      ",
	"WILL.                 ",
	"                      "
};

const int g_snideHeadFrames[] = { FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK | FRAME_DOWN, FRAME_RIGHT, FRAME_UP, FRAME_LEFT, FRAME_DEAD };
const int g_snideBodyFrames[] = { FRAME_SPEAK | FRAME_DOWN, FRAME_DOWN, FRAME_DOWN, FRAME_DOWN, FRAME_RIGHT, FRAME_RIGHT, FRAME_RIGHT, FRAME_RIGHT, FRAME_UP, FRAME_UP, FRAME_UP, FRAME_UP, FRAME_LEFT, FRAME_LEFT, FRAME_LEFT, FRAME_LEFT, FRAME_DEAD };
const int g_reverendHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_reverendBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_bentleyHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_bentleyBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_cookHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_cookBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_gabrielHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_gabrielBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_cynthiaHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_cynthiaBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_professorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_professorBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_doctorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_doctorBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_majorHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const int g_majorBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const int g_dingleHeadFrames[] = { FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const int g_dingleBodyFrames[] = { FRAME_LEFT | FRAME_DOWN, FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
