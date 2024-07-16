#include "ConeMesh.h"
#include "File.h"
#include "MeshFileHdr.h"
#include "BoundingSphere.h"

using namespace Uncertain;

#define WRITE_DATA_TO_FILE 0

#if WRITE_DATA_TO_FILE

Tri_index triList_cone[] =
{
		{0,   1,    2	},
		{3,   4,    5	},
		{6,   7,    8	},
		{9,   10,   11	},
		{12,  13,   14	},
		{15,  16,   17	},
		{18,  19,   20	},
		{21,  22,   23	},
		{24,  25,   26	},
		{27,  28,   29	},
		{30,  31,   32	},
		{33,  34,   35	},
		{36,  37,   38	},
		{39,  40,   41	},
		{42,  43,   44	},
		{45,  46,   47	},
		{48,  49,   50	},
		{51,  52,   53	},
		{54,  55,   56	},
		{57,  58,   59	},
		{60,  61,   62	},
		{63,  64,   65	},
		{66,  67,   68	},
		{69,  70,   71	},
		{72,  73,   74	},
		{75,  76,   77	},
		{78,  79,   80	},
		{81,  82,   83	},
		{84,  85,   86	},
		{87,  88,   89	},
		{90,  91,   92	},
		{93,  94,   95	},
		{96,  97,   98	},
		{99,  100,  101},
		{101, 102,  103 },
		{103, 104,  105 },
		{105, 106,  103 },
		{106, 96,   103 },
		{96,  107,  108 },
		{108, 109,  96 },
		{109, 110,  96 },
		{110, 111,  97 },
		{111, 112,  97 },
		{112, 113,  97 },
		{97,  114,  115 },
		{115, 116,  117 },
		{117, 118,  119 },
		{119, 120,  98 },
		{98,  121,  122},
		{122, 123,  124 },
		{124, 125,  99 },
		{125, 126,  99 },
		{126, 127,  99 },
		{99,  101,  103 },
		{97,  115,  98 },
		{115, 117,  98 },
		{117, 119,  98 },
		{98,  122,  99 },
		{122, 124,  99 },
		{99,  103,  96 },
		{96,  110,  97 },
		{99,  96,   98	}
};

Vert_xyz coneData_xyz[] =
{
{ 0.0f,			1.0f,		-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.195090f,	0.980785f,	-1.0f},
{ 0.195090f,	0.980785f, - 1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.382683f,	0.923880f,	-1.0f},
{ 0.382683f,	0.923880f,	-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.555570f,	0.831470f,	-1.0f},
{ 0.555570f,	0.831470f,	-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.707107f,	0.707107f,	-1.0f},
{ 0.707107f,	0.707107f,	-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.831470f,	0.555570f,	-1.0f},
{ 0.831470f,	0.555570f,	-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.923880f,	0.382683f,	-1.0f},
{ 0.923880f,	0.382683f,	-1.0f},
{ 0.0f,			0.0f,		 1.0f},
{ 0.980785f,	0.195090f,	-1.0f},
{ 0.980785f,	0.195090f,		-1.0f},
{ 0.0f,			0.0f, 1.0f},
{ 1.0f,			0.0f, -1.0f},
{ 1.0f,			0.0f, -1.0f},
{ 0.0f,			0.0f, 1.0f},
{ 0.980785f,	-0.195090f, -1.0f},
{ 0.980785f,	-0.195090f,-1.0f},
{ 0.0f,			 0.0f, 1.0f},
{ 0.923880f,	-0.382683f, -1.0f},
{ 0.923880f,	-0.382683f, -1.0f},
{ 0.0f,			 0.0f, 1.0f},
{ 0.831470f,	-0.555570f,-1.0f},
{ 0.831470f,	-0.555570f,-1.0f},
{ 0.0f,			0.0f, 1.0f},
{ 0.707107f,	-0.707107f, -1.0f},
{ 0.707107f,	-0.707107f, -1.0f},
{ 0.0f,			0.0f, 1.0f},
{ 0.555570f,	-0.831470f,-1.0f}		,
{ 0.555570f,	-0.831470f,-1.0f}		,
{ 0.0f,			0.0f, 1.0f}					,
{ 0.382683f,	-0.923880f, -1.0f}		,
{ 0.382683f,	-0.923880f,-1.0f}		,
{ 0.0f,			0.0f, 1.0f}					,
{ 0.195090f,	-0.980785f, -1.0f}		,
{ 0.195090f,	-0.980785f, -1.0f}		,
{ 0.0f,			0.0f, 1.0f}					,
{ -0.0f,		-1.0f, -1.0f}				,
{ -0.0f,		-1.0f, -1.0f}				,
{ 0.0f,			0.0f, 1.0f}					,
{ -0.195091f,	-0.980785f, -1.0f}		,
{ -0.195091f,	-0.980785f, -1.0f}		,
{ 0.0f,			0.0f, 1.0f}					,
{ -0.382684f,	-0.923879f, -1.0f}		,
{ -0.382684f,	-0.923879f, -1.0f}		,
{ 0.0f,			0.0f, 1.0f}					,
{ -0.555571f,	-0.831469f, -1.0f}		,
{ -0.555571f,	-0.831469f, -1.0f}		,
{ 0.0f,			 0.0f, 1.0f}					,
{ -0.707107f,	-0.707106f, -1.0f}		,
{ -0.707107f,	-0.707106f, -1.0f}		,
{ 0.0f,			 0.0f, 1.0f}					,
{ -0.831470f,	-0.555570f,-1.0f}		,
{ -0.831470f,	-0.555570f,-1.0f}		,
{ 0.0f,			 0.0f, 1.0f}					,
{ -0.923880f,-0.382683f, -1.0f}		,
{ -0.923880f,-0.382683f, -1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.980785f, -0.195089f, -1.0f}		,
{ -0.980785f, -0.195089f, -1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -1.0f, 0.000001f,-1.0f}			,
{ -1.0f, 0.000001f,-1.0f}			,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.980785f, 0.195091f,-1.0f}		,
{ -0.980785f, 0.195091f,-1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.923879f, 0.382684f, -1.0f}		,
{ -0.923879f, 0.382684f, -1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.831469f, 0.555571f,-1.0f}		,
{ -0.831469f, 0.555571f,-1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.707106f, 0.707108f, -1.0f}		,
{ -0.707106f, 0.707108f, -1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.555569f, 0.831470f,-1.0f}		,
{ -0.555569f, 0.831470f,-1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.382682f,0.923880f,-1.0f}		,
{ -0.382682f,0.923880f,-1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ -0.195089f, 0.980786f, -1.0f}		,
{ -0.195089f, 0.980786f, -1.0f}		,
{ 0.0f, 0.0f, 1.0f}					,
{ 0.0f, 1.0f, -1.0f}				,
{ 0.980785f, 0.195090f,-1.0f}			,
{ 0.195090f,-0.980785f, -1.0f}		,
{ -0.980785f, -0.195089f, -1.0f}		,
{ -0.195089f, 0.980786f, -1.0f}		,
{ 0.0f, 1.0f, -1.0f}				,
{ 0.195090f, 0.980785f, -1.0f}		,
{ 0.382683f, 0.923880f, -1.0f}		,
{ 0.555570f, 0.831470f, -1.0f}		,
{ 0.707107f, 0.707107f, -1.0f}			,
{ 0.831470f, 0.555570f, -1.0f}		,
{ 0.923880f, 0.382683f, -1.0f}		,
{ 1.0f, 0.0f, -1.0f}				,
{ 0.980785f, -0.195090f, -1.0f}		,
{ 0.923880f, -0.382683f, -1.0f}		,
{ 0.831470f, -0.555570f, -1.0f}		,
{ 0.707107f, -0.707107f, -1.0f}		,
{ 0.555570f, -0.831470f, -1.0f}		,
{ 0.382683f, -0.923880f, -1.0f}		,
{ -0.0f, -1.0f, -1.0f}				,
{ -0.195091f,-0.980785f, -1.0f}		,
{ -0.382684f, -0.923879f, -1.0f}		,
{ -0.555571f,-0.831469f, -1.0f}		,
{ -0.707107f, -0.707106f, -1.0f}		,
{ -0.831470f, -0.555570f, -1.0f}	,
{ -0.923880f, -0.382683f, -1.0f}		,
{ -1.0f, 0.000001f,-1.0f}			,
{ -0.980785f, 0.195091f,-1.0f}		,
{ -0.923879f, 0.382684f, -1.0f}		,
{ -0.831469f, 0.555571f,-1.0f}		,
{ -0.707106f, 0.707108f, -1.0f}		,
{ -0.555569f, 0.831470f, -1.0f}		,
{ -0.382682f,0.923880f, -1.0f}
};

Vert_uv coneData_uv[] =
{
	{ 0.250000f, 0.490000f},
	{ 0.250000f, 0.250000f},
	{ 0.296822f, 0.485388f},
	{ 0.296822f, 0.485388f},
	{ 0.250000f, 0.250000f},
	{ 0.341844f, 0.471731f},
	{ 0.341844f, 0.471731f},
	{ 0.250000f, 0.250000f},
	{ 0.383337f, 0.449553f},
	{ 0.383337f, 0.449553f},
	{ 0.250000f, 0.250000f},
	{ 0.419706f, 0.419706f},
	{ 0.419706f, 0.419706f},
	{ 0.250000f, 0.250000f},
	{ 0.449553f, 0.383337f},
	{ 0.449553f, 0.383337f},
	{ 0.250000f, 0.250000f},
	{ 0.471731f, 0.341844f},
	{ 0.471731f, 0.341844f},
	{ 0.250000f, 0.250000f},
	{ 0.485388f, 0.296822f},
	{ 0.485388f, 0.296822f},
	{ 0.250000f, 0.250000f},
	{ 0.490000f, 0.250000f},
	{ 0.490000f, 0.250000f},
	{ 0.250000f, 0.250000f},
	{ 0.485388f, 0.203178f},
	{ 0.485388f, 0.203178f},
	{ 0.250000f, 0.250000f},
	{ 0.471731f, 0.158156f},
	{ 0.471731f, 0.158156f},
	{ 0.250000f, 0.250000f},
	{ 0.449553f, 0.116663f},
	{ 0.449553f, 0.116663f},
	{ 0.250000f, 0.250000f},
	{ 0.419706f, 0.080294f},
	{ 0.419706f, 0.080294f},
	{ 0.250000f, 0.250000f},
	{ 0.383337f, 0.050447f},
	{ 0.383337f, 0.050447f},
	{ 0.250000f, 0.250000f},
	{ 0.341844f, 0.028269f},
	{ 0.341844f, 0.028269f},
	{ 0.250000f, 0.250000f},
	{ 0.296822f, 0.014612f},
	{ 0.296822f, 0.014612f},
	{ 0.250000f, 0.250000f},
	{ 0.250000f, 0.010000f},
	{ 0.250000f, 0.010000f},
	{ 0.250000f, 0.250000f},
	{ 0.203178f, 0.014612f},
	{ 0.203178f, 0.014612f},
	{ 0.250000f, 0.250000f},
	{ 0.158156f, 0.028269f},
	{ 0.158156f, 0.028269f},
	{ 0.250000f, 0.250000f},
	{ 0.116663f, 0.050447f},
	{ 0.116663f, 0.050447f},
	{ 0.250000f, 0.250000f},
	{ 0.080294f, 0.080294f},
	{ 0.080294f, 0.080294f},
	{ 0.250000f, 0.250000f},
	{ 0.050447f, 0.116663f},
	{ 0.050447f, 0.116663f},
	{ 0.250000f, 0.250000f},
	{ 0.028269f, 0.158156f},
	{ 0.028269f, 0.158156f},
	{ 0.250000f, 0.250000f},
	{ 0.014611f, 0.203179f},
	{ 0.014611f, 0.203179f},
	{ 0.250000f, 0.250000f},
	{ 0.010000f, 0.250000f},
	{ 0.010000f, 0.250000f},
	{ 0.250000f, 0.250000f},
	{ 0.014612f, 0.296822f},
	{ 0.014612f, 0.296822f},
	{ 0.250000f, 0.250000f},
	{ 0.028269f, 0.341844f},
	{ 0.028269f, 0.341844f},
	{ 0.250000f, 0.250000f},
	{ 0.050447f, 0.383337f},
	{ 0.050447f, 0.383337f},
	{ 0.250000f, 0.250000f},
	{ 0.080295f, 0.419706f},
	{ 0.080295f, 0.419706f},
	{ 0.250000f, 0.250000f},
	{ 0.116663f, 0.449553f},
	{ 0.116663f, 0.449553f},
	{ 0.250000f, 0.250000f},
	{ 0.158156f, 0.471731f},
	{ 0.158156f, 0.471731f},
	{ 0.250000f, 0.250000f},
	{ 0.203179f, 0.485389f},
	{ 0.203179f, 0.485389f},
	{ 0.250000f, 0.250000f},
	{ 0.250000f, 0.490000f},
	{ 0.985388f, 0.296822f},
	{ 0.796822f, 0.014612f},
	{ 0.514611f, 0.203179f},
	{ 0.703179f, 0.485389f},
	{ 0.750000f, 0.490000f},
	{ 0.796822f, 0.485388f},
	{ 0.841844f, 0.471731f},
	{ 0.883337f, 0.449553f},
	{ 0.919706f, 0.419706f},
	{ 0.949553f, 0.383337f},
	{ 0.971731f, 0.341844f},
	{ 0.990000f, 0.250000f},
	{ 0.985388f, 0.203178f},
	{ 0.971731f, 0.158156f},
	{ 0.949553f, 0.116663f},
	{ 0.919706f, 0.080294f},
	{ 0.883337f, 0.050447f},
	{ 0.841844f, 0.028269f},
	{ 0.750000f, 0.010000f},
	{ 0.703178f, 0.014612f},
	{ 0.658156f, 0.028269f},
	{ 0.616663f, 0.050447f},
	{ 0.580294f, 0.080294f},
	{ 0.550447f, 0.116663f},
	{ 0.528269f, 0.158156f},
	{ 0.510000f, 0.250000f},
	{ 0.514612f, 0.296822f},
	{ 0.528269f, 0.341844f},
	{ 0.550447f, 0.383337f},
	{ 0.580295f, 0.419706f},
	{ 0.616663f, 0.449553f},
	{ 0.658156f, 0.471731f}
};

Vert_NxNyNz coneData_nxnynz[] =
{

	{ 0.087754f,	  0.890977f,	 0.445488f},
	{ 0.087754f,	  0.890977f,	 0.445488f},
	{ 0.087754f,	  0.890977f,	 0.445488f},
	{ 0.259888f,	  0.856737f,	 0.445488f},
	{ 0.259888f,	  0.856737f,	 0.445488f}, 
	{ 0.259888f,	  0.856737f,	 0.445488f},
	{ 0.422036f,	  0.789573f,	 0.445488f},
	{ 0.422036f,	  0.789573f,	 0.445488f}, 
	{ 0.422036f,	  0.789573f,	 0.445488f},
	{ 0.567965f,	  0.692067f,	 0.445488f},
	{ 0.567965f,	  0.692067f,	 0.445488f}, 
	{ 0.567965f,	  0.692067f,	 0.445488f},
	{ 0.692067f,	  0.567965f,	 0.445488f},
	{ 0.692067f,	  0.567965f,	 0.445488f}, 
	{ 0.692067f,	  0.567965f,	 0.445488f},
	{ 0.789573f,	  0.422036f,	 0.445488f},
	{ 0.789573f,	  0.422036f,	 0.445488f}, 
	{ 0.789573f,	  0.422036f,	 0.445488f},
	{ 0.856737f,	  0.259888f,	 0.445488f},
	{ 0.856737f,	  0.259888f,	 0.445488f}, 
	{ 0.856737f,	  0.259888f,	 0.445488f},
	{ 0.890977f,	  0.087754f,	 0.445488f},
	{ 0.890977f,	  0.087754f,	 0.445488f}, 
	{ 0.890977f,	  0.087754f,	 0.445488f},
	{ 0.890977f,	 -0.087753f,	 0.445488f},
	{ 0.890977f,	 -0.087753f,	 0.445488f},
	{ 0.890977f,	 -0.087753f,	 0.445488f}, 
	{ 0.856737f,	 -0.259888f,	 0.445488f}, 
	{ 0.856737f,	 -0.259888f,	 0.445488f}, 
	{ 0.856737f,	 -0.259888f,	 0.445488f}, 
	{ 0.789573f,	 -0.422035f,	 0.445488f}, 
	{ 0.789573f,	 -0.422035f,	 0.445488f}, 
	{ 0.789573f,	 -0.422035f,	 0.445488f}, 
	{ 0.692067f,	 -0.567965f,	 0.445488f}, 
	{ 0.692067f,	 -0.567965f,	 0.445488f}, 
	{ 0.692067f,	 -0.567965f,	 0.445488f}, 
	{ 0.567965f,	 -0.692067f,	 0.445488f}, 
	{ 0.567965f,	 -0.692067f,	 0.445488f}, 
	{ 0.567965f,	 -0.692067f,	 0.445488f}, 
	{ 0.422036f,	 -0.789573f,	 0.445488f}, 
	{ 0.422036f,	 -0.789573f,	 0.445488f}, 
	{ 0.422036f,	 -0.789573f,	 0.445488f}, 
	{ 0.259888f,	 -0.856737f,	 0.445488f}, 
	{ 0.259888f,	 -0.856737f,	 0.445488f}, 
	{ 0.259888f,	 -0.856737f,	 0.445488f}, 
	{ 0.087753f,	 -0.890977f,	 0.445488f}, 
	{ 0.087753f,	 -0.890977f,	 0.445488f}, 
	{ 0.087753f,	 -0.890977f,	 0.445488f},
	{-0.087754f,	 -0.890977f,	 0.445488f},
	{-0.087754f,	 -0.890977f,	 0.445488f}, 
	{-0.087754f,	 -0.890977f,	 0.445488f},
	{-0.259889f,	 -0.856737f,	 0.445488f},
	{-0.259889f,	 -0.856737f,	 0.445488f}, 
	{-0.259889f,	 -0.856737f,	 0.445488f},
	{-0.422036f,	 -0.789573f,	 0.445488f},
	{-0.422036f,	 -0.789573f,	 0.445488f}, 
	{-0.422036f,	 -0.789573f,	 0.445488f},
	{-0.567965f,	 -0.692066f,	 0.445488f},
	{-0.567965f,	 -0.692066f,	 0.445488f}, 
	{-0.567965f,	 -0.692066f,	 0.445488f},
	{-0.692067f,	 -0.567964f,	 0.445488f},
	{-0.692067f,	 -0.567964f,	 0.445488f}, 
	{-0.692067f,	 -0.567964f,	 0.445488f},
	{-0.789574f,	 -0.422035f,	 0.445488f},
	{-0.789574f,	 -0.422035f,	 0.445488f}, 
	{-0.789574f,	 -0.422035f,	 0.445488f},
	{-0.856737f,	 -0.259887f,	 0.445488f},
	{-0.856737f,	 -0.259887f,	 0.445488f}, 
	{-0.856737f,	 -0.259887f,	 0.445488f},
	{-0.890977f,	 -0.087753f,	 0.445488f},
	{-0.890977f,	 -0.087753f,	 0.445488f}, 
	{-0.890977f,	 -0.087753f,	 0.445488f}, 
	{-0.890977f,	  0.087754f,	 0.445488f}, 
	{-0.890977f,	  0.087754f,	 0.445488f}, 
	{-0.890977f,	  0.087754f,	 0.445488f},
	{-0.856737f,	  0.259889f,	 0.445488f},
	{-0.856737f,	  0.259889f,	 0.445488f}, 
	{-0.856737f,	  0.259889f,	 0.445488f},
	{-0.789573f,	  0.422037f,	 0.445488f},
	{-0.789573f,	  0.422037f,	 0.445488f}, 
	{-0.789573f,	  0.422037f,	 0.445488f},
	{-0.692066f,	  0.567965f,	 0.445488f},
	{-0.692066f,	  0.567965f,	 0.445488f}, 
	{-0.692066f,	  0.567965f,	 0.445488f},
	{-0.567964f,	  0.692067f,	 0.445488f},
	{-0.567964f,	  0.692067f,	 0.445488f}, 
	{-0.567964f,	  0.692067f,	 0.445488f},
	{-0.422035f,	  0.789574f,	 0.445488f},
	{-0.422035f,	  0.789574f,	 0.445488f}, 
	{-0.422035f,	  0.789574f,	 0.445488f},
	{-0.259887f,	  0.856737f,	 0.445488f},
	{-0.259887f,	  0.856737f,	 0.445488f}, 
	{-0.259887f,	  0.856737f,	 0.445488f},
	{-0.087753f,	  0.890977f,	 0.445488f},
	{-0.087753f,	  0.890977f,	 0.445488f}, 
	{-0.087753f,	  0.890977f,	 0.445488f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{-0.000000f,	  0.000000f,	-1.000000f},
	{-0.000000f,	  0.000000f,	-1.000000f}, 
	{-0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	 -0.000000f,	-1.000000f},
	{ 0.000000f,	 -0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f},
	{ 0.000000f,	 -0.000000f,	-1.000000f},
	{ 0.000000f,	 -0.000000f,	-1.000000f},
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}, 
	{ 0.000000f,	  0.000000f,	-1.000000f}



};

#define CONE_DATA_NUM_VERTS (int)(sizeof(coneData_xyz)/sizeof(Vert_xyz));
#define CONE_TRILIST_NUM_TRIANGLES (int)(sizeof(triList_cone)/sizeof(Tri_index));

#endif // WRITE_DATA_TO_FILE


ConeMesh::ConeMesh(const char* const pMeshFileName)
	:Mesh(MeshName::CONE_MESH, new BoundingSphere())
{
	this->CreateVAO(pMeshFileName);
}

void ConeMesh::CreateVAO(const char* const pMeshFileName)
{
	assert(pMeshFileName);
	AZUL_UNUSED_VAR(pMeshFileName);

	// Create a VAO
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO);
	glBindVertexArray(this->VAO);

	// Create VBOs
	glGenBuffers(1, &this->VBO_Verts);
	assert(this->VBO_Verts != 0);

	glGenBuffers(1, &this->VBO_Norms);
	assert(this->VBO_Norms != 0);

	glGenBuffers(1, &this->VBO_Texts);
	assert(this->VBO_Texts != 0);

	glGenBuffers(1, &this->VBO_Index);
	assert(this->VBO_Index);

	File::Handle fh;
	File::Error ferror;

	MeshFileHdr meshHdr;

	//-----------------------------
	// Write data from file
	//-----------------------------

#if WRITE_DATA_TO_FILE

	this->NumVerts = CONE_DATA_NUM_VERTS;
	this->NumTris = CONE_TRILIST_NUM_TRIANGLES;

	strncpy_s(meshHdr.ObjName, MeshFileHdr::OBJECT_NAME_SIZE, EngineNames::Stringify(MeshName::CONE_MESH), _TRUNCATE);


	meshHdr.numVerts = this->NumVerts;
	meshHdr.vertexBufferOffset = 0;
	meshHdr.textsBufferOffset = 0;
	meshHdr.normsBufferOffset = 0;

	meshHdr.numTriList = this->NumTris;
	meshHdr.triListBufferdOffset = 0;


	ferror = File::Open(fh, pMeshFileName, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	// Write vert buffer
	ferror = File::Tell(fh, meshHdr.vertexBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, coneData_xyz, sizeof(Vert_xyz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write norm buffer
	ferror = File::Tell(fh, meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, coneData_nxnynz, sizeof(Vert_NxNyNz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write texture buffer
	ferror = File::Tell(fh, meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, coneData_uv, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write index buffer
	ferror = File::Tell(fh, meshHdr.triListBufferdOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, triList_cone, sizeof(Tri_index) * this->NumTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	MeshFileHdr meshHdr2;

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &meshHdr2, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	assert(memcmp(&meshHdr, &meshHdr2, sizeof(MeshFileHdr)) == 0);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

#endif

	//-----------------------------
	// Read data from file
	//-----------------------------
	ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	this->NumVerts = meshHdr.numVerts;
	this->NumTris = meshHdr.numTriList;

	// Create data buffers
	Vert_xyz* data_xyz = new Vert_xyz[(unsigned int)meshHdr.numVerts];
	assert(data_xyz);
	Vert_NxNyNz* data_nxnynz = new Vert_NxNyNz[(unsigned int)meshHdr.numVerts];
	assert(data_nxnynz);
	Vert_uv* data_uv = new Vert_uv[(unsigned int)meshHdr.numVerts];
	assert(data_uv);
	Tri_index* data_TriList = new Tri_index[(unsigned int)meshHdr.numVerts];
	assert(data_TriList);

	// Read verts from meshHdr into buffers
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.vertexBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_xyz, sizeof(Vert_xyz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_nxnynz, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_uv, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.triListBufferdOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_TriList, sizeof(Tri_index) * this->NumTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	//-----------------------------
	// Send data to GPU
	//-----------------------------

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->NumVerts), data_xyz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Norm data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_NxNyNz) * this->NumVerts), data_nxnynz, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv)* this->NumVerts), data_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->NumTris), data_TriList, GL_STATIC_DRAW);

	delete[] data_xyz;
	delete[] data_uv;
	delete[] data_nxnynz;
	delete[] data_TriList;
}

ConeMesh::~ConeMesh()
{
	// Remove dynamic
}