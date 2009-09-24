extern const char* g_characterText[];

extern const int g_largeTextMap[];

extern const char* g_characterName[];

extern const char* g_itemName[];
extern const char* g_itemDescription[];
extern const char* g_itemText[];
extern const char* g_colName[];
extern const char* g_iconName[];
extern const char* g_roomName[];
extern const char* g_enterRoomText[];
extern const char* g_KeyboardText[];
extern const char* g_KeyboardHit[];

void DrawChar(char c, int x, int y, bool sub);
void DrawText(const char* string, int x, int y, bool sub);
void DrawText(const char* string, int x, int y, int count, bool sub);
void DrawTextLarge(const char* string, int x, int y, bool sub);
void DrawCharLarge(char c, int x, int y, bool sub);
