extern const char* g_snideText[];
extern const char* g_reverandText[];
extern const char* g_bentleyText[];
extern const char* g_cookText[];
extern const char* g_gabrielText[];
extern const char* g_cynthiaText[];
extern const char* g_professorText[];
extern const char* g_doctorText[];
extern const char* g_majorText[];
extern const char* g_dingleText[];

extern const int g_largeTextMap[];

extern const char* g_itemName[];
extern const char* g_colName[];

void DrawText(const char* string, int x, int y, bool sub);
void DrawTextLarge(const char* string, int x, int y, bool sub);
void DrawPixel(int x, int y, int colorIndex);
void DrawPixelDouble(int x, int y, int colorIndex);
void DrawLine(int x0, int y0, int x1, int y1, int colorIndex);
void DrawTime(CTime* pTime);
