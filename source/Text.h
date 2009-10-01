extern const char* g_characterText[];

extern const int g_largeTextMap[];

extern const char* g_characterName[];

extern const char* g_itemName[];
extern const char* g_itemExamine[];
extern const char* g_itemRead[];
extern const char* g_colName[];
extern const char* g_askAboutCharacter[];
extern const char* g_askAboutProfessorRandom[];
extern const char* g_askAboutMajorRandom[];
extern const char* g_iconName[];
extern const char* g_roomName[];
extern const char* g_enterRoomText[];
extern const char* g_KeyboardText[];
extern const char* g_KeyboardHit[];

void DrawChar(char c, int x, int y, bool sub);
void DrawString(const char* string, int x, int y, bool sub);
void DrawString(const char* string, int x, int y, int count, bool sub);
void DrawStringLarge(const char* string, int x, int y, bool sub);
void DrawCharLarge(char c, int x, int y, bool sub);
