extern const char* g_snideText;
extern const char* g_reverandText;
extern const char* g_bentleyText;
extern const char* g_cookText;
extern const char* g_gabrielText;
extern const char* g_cynthiaText;
extern const char* g_professorText;
extern const char* g_doctorText;
extern const char* g_majorText;
extern const char* g_dingleText;

extern const int g_largeTextMap[];

extern const char* g_itemName[];
extern const char* g_colName[];
extern const char* g_iconName[];
extern const char* g_roomName[];
extern const char* g_KeyboardText[];
extern const char* g_KeyboardHit[];

void DrawChar(char c, int x, int y, bool sub);
void DrawText(const char* string, int x, int y, bool sub);
void DrawTextLarge(const char* string, int x, int y, bool sub);
void DrawCharLarge(char c, int x, int y, bool sub);
