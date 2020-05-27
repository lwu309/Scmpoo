/* Allow unsafe CRT functions on Visual C++ 2005 and higher. */
#if _MSC_VER >= 1400
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define STRICT

#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#include <ShellAPI.h>

/* GetActiveWindow is made local to current thread in 32-bit Windows. The function of global scope is now GetForegroundWindow. */
#ifdef _WIN32
#define GetActiveWindow GetForegroundWindow
#endif

typedef struct spriteinfo {
    HBITMAP bitmaps[2];
    int x;
    int y;
    int width;
    int height;
} spriteinfo;

typedef struct resourceinfo {
    int resource;
    WORD flags;
    spriteinfo info;
} resourceinfo;

typedef struct windowinfo {
    HWND window;
    RECT rect;
    BYTE padding[66]; /* Unused. */
} windowinfo;

int word_9CF0 = 245; /* Palette search maximum index (unused). */
resourceinfo stru_9EE2[16] = { /* Resource list. */
    {101, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {102, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {103, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {104, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {105, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {106, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {107, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {108, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {109, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {110, 1, {{NULL, NULL}, 0, 0, 0, 0}},
    {111, 1, {{NULL, NULL}, 0, 0, 0, 0}}
};
resourceinfo stru_9FE2[16] = {0}; /* Resource list storing flipped images. */
WORD word_A15A[80] = { /* Normal action table (option "Gravity always on" disabled). */
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    13, 58, 15, 45,
    35, 53, 43, 47,
    45, 47, 49, 51
};
WORD word_A1FA[80] = { /* Normal action table (option "Gravity always on" enabled). */
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 11, 7, 7,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    11, 7, 17, 20,
    13, 58, 15, 65,
    35, 53, 43, 75,
    45, 47, 49, 51
};
WORD word_A29A[8] = { /* Special action table. */
    116, 121, 126, 147,
    128, 135, 142, 147
};
int word_A2AA = 1; /* Facing direction. 1 = left, -1 = right */
int word_A2AC = 1; /* Facing direction (sub). 1 = left, -1 = right */
WORD word_A2B4[6][8] = { /* Blink animations. */
    {7, 8, 7, 6, 7, 8, 7, 6},
    {32, 33, 32, 31, 32, 33, 32, 31},
    {74, 75, 74, 73, 74, 75, 74, 73},
    {79, 80, 79, 78, 79, 80, 79, 78},
    {82, 83, 82, 81, 82, 83, 82, 81},
    {35, 36, 35, 34, 35, 36, 35, 34}
};
WORD word_A314[2][4] = { /* Hang on window top edge animations. */
    {42, 43, 42, 44},
    {46, 47, 46, 47}
};
WORD word_A324[20] = { /* Collision animation with obsolete height offset. */
    62, 63, 63, 64, 64, 65, 65, 66, 66, 66,
    0, 10, 17, 21, 22, 21, 17, 10, 0, 0
};
WORD word_A34C[11] = { /* Yawn animation. */
    37, 38, 39, 39, 39, 38, 37, 3, 37, 3, 0
};
WORD word_A362[8] = { /* Baa animation. */
    71, 72, 71, 72, 71, 72, 3, 0
};
WORD word_A372[13] = { /* Sneeze animation. */
    107, 108, 109, 109, 3, 3, 3, 110, 111, 110, 111, 3, 0
};
WORD word_A38C[6] = { /* Amazed animation. */
    50, 51, 50, 51, 3, 0
};
WORD word_A398[35] = { /* Eat animation. */
    58, 150, 60, 61, 60, 61, 60, 61, 58, 151, 60, 61, 60, 61, 60, 61, 2, 58, 152, 60, 61, 60, 61, 60, 61, 58, 153, 60, 61, 60, 61, 60, 61, 3, 0
};
WORD word_A3DE[34] = { /* Burn animation. */
    134, 134, 134, 134, 134, 134, 134, 134, 135, 136, 137, 138, 137, 138, 137, 138, 137, 138, 137, 138, 139, 140, 141, 142, 143, 144, 145, 144, 145, 144, 145, 144, 145, 0
};
WORD word_A422[13] = { /* Roll over animation (not used). */
    3, 93, 99, 100, 99, 100, 99, 100, 99, 100, 95, 3, 0
};
WORD word_A43C[8] = { /* Get up animation (left). */
    48, 48, 48, 49, 13, 12, 3, 0
};
WORD word_A44C[8] = { /* Get up animation (right). */
    48, 48, 48, 49, 13, 14, 3, 0
};
WORD word_A45C[28] = { /* Merry 2 animation. */
    130, 130, 130, 130, 130, 129, 129, 128, 128, 127, 127, 127, 6, 6, 6, 6, 7, 8, 7, 6, 7, 8, 7, 6, 6, 6, 6, 0
};
WORD word_A494[5] = { /* Burn bathtub splash animation. */
    147, 148, 147, 146, 0
};
WORD word_A49E[55] = { /* Burn get out of bathtub animation. */
    169, 169, 169, 169, 169, 169, 169, 169, 170, 171, 170, 169, 170, 171, 170, 169, 169, 169, 169, 81, 81, 81, 81, 81, 81, 81, 81, 85, 85, 85, 85, 85, 85, 85, 85, 34, 34, 34, 34, 35, 36, 35, 34, 35, 36, 35, 34, 34, 34, 10, 10, 9, 9, 3, 0
};
WORD word_A50C[12] = { /* Blush animation. */
    3, 127, 128, 129, 130, 130, 130, 129, 128, 127, 127, 0
};
WORD word_A524[9] = { /* Roll animation. */
    119, 120, 121, 122, 123, 124, 125, 126, 0
};
WORD word_A536[8] = { /* Spin animation. 0-3: face, 4-7: back */
    3, 9, 10, 11, 2, 14, 13, 12
};
WORD word_A798 = 0; /* Has cursor position changed in current timer period? */
int word_A79A = 0; /* Cursor position with respect to screen, X-coordinate */
int word_A79C = 0; /* Cursor position with respect to screen, Y-coordinate */
WORD word_A79E = 0; /* Dragging Screen Mate window? */
WORD word_A7A0 = 0; /* Destroy Screen Mate window by right double-click? */
WORD word_A7A2 = 0; /* Unused. */
RECT stru_A7A4 = {0, 0, 0, 0}; /* Screen Mate window rectangle. */
WORD word_A7AC = 0; /* Not to clear window on WM_PAINT? */
POINT stru_A7B0 = {0, 0}; /* Current cursor position. */
WORD word_A7B4 = 0; /* Not to clear window on WM_PAINT? (sub) */
HBITMAP word_A7B6[2] = {NULL, NULL}; /* Double buffer. */
HBITMAP word_A7BA = NULL; /* Sprite render target. */
HBITMAP word_A7BC = NULL; /* Sprite colour image for current frame. */
HBITMAP word_A7BE = NULL; /* Sprite mask image for current frame. */
int word_A7C0 = 0; /* Sprite X-coordinate on resource image for current frame. */
int word_A7C2 = 0; /* Sprite Y-coordinate on resource image for current frame. */
int word_A7C8 = 0; /* Sprite X-coordinate on resource image for previous frame. */
int word_A7CA = 0; /* Sprite Y-coordinate on resource image for previous frame (unused). */
WORD word_A7D0 = 0; /* Current framebuffer index. */
WORD word_A7D2 = 0; /* 0 to render sprite; 1 to update window. */
WORD word_A7D4 = 0; /* Unused. */
HBITMAP word_A7D8 = NULL; /* Sprite colour image for previous frame. */
int word_A7DA = 0; /* Screen X-coordinate for current frame. */
int word_A7DC = 0; /* Screen Y-coordinate for current frame. */
int word_A7DE = 0; /* Sprite width for current frame. */
int word_A7E0 = 0; /* Sprite height for current frame. */
int word_A7E2 = 0; /* Update area rectangle X-coordinate for current frame. */
int word_A7E4 = 0; /* Update area rectangle Y-coordinate for current frame. */
int word_A7E6 = 0; /* Update area rectangle width for current frame. */
int word_A7E8 = 0; /* Update area rectangle height for current frame. */
int word_A7EA = 0; /* Update area rectangle X-coordinate for previous frame. */
int word_A7EC = 0; /* Update area rectangle Y-coordinate for previous frame. */
int word_A7EE = 0; /* Update area rectangle width for previous frame. */
int word_A7F0 = 0; /* Update area rectangle height for previous frame. */
int word_A7F2 = 0; /* Screen X-coordinate for previous frame. */
int word_A7F4 = 0; /* Screen Y-coordinate for previous frame. */
int word_A7F6 = 0; /* Sprite width for previous frame. */
int word_A7F8 = 0; /* Sprite height for previous frame. */
WORD word_A7FA = 0; /* Current frame rectangle and previous frame rectangle have no intersecion? (unused) */
WORD word_A7FC = 0; /* Is gravity enabled? */
WORD word_A7FE = 0; /* Is collision with visible window enabled? */
int word_A800 = 0; /* Current X-coordinate. */
int word_A802 = 0; /* Current Y-coordinate. */
int word_A804 = 0; /* Sprite index. */
int word_A806 = 0; /* Vertical speed. */
int word_A808 = 0; /* Horizontal speed. */
int word_A80C = 0; /* Y-coordinate memory. */
int word_A80E = 0; /* Current X-coordinate (sub). */
int word_A810 = 0; /* Current Y-coordinate (sub). */
int word_A812 = 0; /* Sprite index (sub). */
HWND word_A81C = NULL; /* Active window or window to land on. */
RECT stru_A81E = {0L, 0L, 0L, 0L}; /* Rectangle of active window or window to land on. */
int word_A826 = 0; /* Animation frame counter. */
int word_A828 = 0; /* Random duration period counter. */
int word_A82A = 0; /* Random case number for action. */
WORD word_A82C = 0; /* Unused. */
HGLOBAL word_A82E = NULL; /* Global handle for holding WAVE resource in memory. */
int word_A830 = 0; /* Current time hour. */
int word_A832 = 0; /* Remaining times for chime. */
DWORD dword_A834 = 0; /* Tick count. */
int word_A838 = 0; /* Time check period counter. */
int word_A83A = 0; /* Frame period counter. */
int word_A83C = 0; /* Target X-coordinate for window edge attachment. */
int word_A83E = 0; /* Target Y-coordinate for window edge attachment. */
WORD word_A840 = 0; /* Bounce when falling? */
int word_A842 = 0; /* Case number for fall action. */
int word_A844 = 0; /* Collision vertical speed (unused). */
int word_A846 = 0; /* Collision spin frame counter (unused). */
WORD word_A848 = 0; /* Collision animation frame index. */
int word_A84A = 0; /* Known instance list update period counter. */
HBITMAP word_A850[2] = {NULL, NULL}; /* Double buffer (sub). */
HBITMAP word_A854 = NULL; /* Sprite render target (sub). */
HBITMAP word_A856 = NULL; /* Sprite colour image for current frame (sub). */
HBITMAP word_A858 = NULL; /* Sprite mask image for current frame (sub). */
HBITMAP word_A85A = NULL; /* Fade out processed colour image (sub). */
HBITMAP word_A85C = NULL; /* Fade out processed mask image (sub). */
int word_A85E = 0; /* Sprite X-coordinate on resource image for current frame (sub). */
int word_A860 = 0; /* Sprite Y-coordinate on resource image for current frame (sub). */
int word_A866 = 0; /* Sprite X-coordinate on resource image for previous frame (sub). */
int word_A868 = 0; /* Sprite Y-coordinate on resource image for previous frame (sub) (unused). */
WORD word_A86E = 0; /* Current framebuffer index (sub). */
WORD word_A870 = 0; /* 0 to render sprite; 1 to update window (sub). */
WORD word_A872 = 0; /* Unused. */
HBITMAP word_A876 = NULL; /* Sprite colour image for previous frame (sub). */
int word_A878 = 0; /* Screen X-coordinate for current frame (sub). */
int word_A87A = 0; /* Screen Y-coordinate for current frame (sub). */
int word_A87C = 0; /* Sprite width for current frame (sub). */
int word_A87E = 0; /* Sprite height for current frame (sub). */
int word_A880 = 0; /* Update area rectangle X-coordinate for current frame (sub). */
int word_A882 = 0; /* Update area rectangle Y-coordinate for current frame (sub). */
int word_A884 = 0; /* Update area rectangle width for current frame (sub). */
int word_A886 = 0; /* Update area rectangle height for current frame (sub). */
int word_A888 = 0; /* Update area rectangle X-coordinate for previous frame (sub). */
int word_A88A = 0; /* Update area rectangle Y-coordinate for previous frame (sub). */
int word_A88C = 0; /* Update area rectangle width for previous frame (sub). */
int word_A88E = 0; /* Update area rectangle height for previous frame (sub). */
int word_A890 = 0; /* Screen X-coordinate for previous frame (sub). */
int word_A892 = 0; /* Screen Y-coordinate for previous frame (sub). */
int word_A894 = 0; /* Sprite width for previous frame (sub). */
int word_A896 = 0; /* Sprite height for previous frame (sub). */
WORD word_A898 = 0; /* Current frame rectangle and previous frame rectangle have no intersecion? (sub) (unused) */
WORD word_A8A0 = 0; /* State. */
spriteinfo stru_A8A2[512] = {{{NULL, NULL}, 0, 0, 0, 0}}; /* Sprite list. First 256 for left-facing sprites, last 256 for right-facing sprites. */
int word_C0A4 = 0; /* No mouse action consecutive period counter. */
UINT word_C0AC = 0U; /* Configuration: Chime */
WORD word_C0AE = 0; /* Screen Mate window on top of subwindow? (unused) */
HWND word_C0B0 = NULL; /* Self instance window handle. */
HBITMAP word_C0B2 = NULL; /* UFO beam render target. */
HBRUSH word_C0B4 = NULL; /* UFO beam paint colour brush. */
UINT word_C0B6 = 0U; /* Configuration: Always moving */
HBITMAP word_C0B8 = NULL; /* UFO beam colour rectangle image. */
WORD word_C0BA = 0; /* Remaining no-update periods after clearing windows. */
windowinfo stru_C0BC[32] = {{NULL, {0, 0, 0, 0}, {0}}}; /* Currently visible window list. */
WORD word_CA3C = 0; /* Prevent special actions? */
WORD word_CA3E = 0; /* Always on top? (unused) */
int word_CA40 = 0; /* Known instance count. */
UINT word_CA42 = 0U; /* Configuration: Gravity always on */
HBRUSH word_CA44 = NULL; /* UFO beam mask colour brush. */
int word_CA46 = 0; /* Fade out frame counter. */
int word_CA48 = 0; /* Unused. */
HPALETTE word_CA4A = NULL; /* Palette being used by window. */
int word_CA4C = 0; /* Unused. */
int word_CA4E = 0; /* Unused. */
int word_CA50 = 0; /* Screen width. */
int word_CA52 = 0; /* Screen height. */
WORD word_CA54 = 0; /* Temporarily holds sleep timeout action. */
WORD word_CA56 = 0; /* Not to clear subwindow? */
HINSTANCE word_CA58 = NULL; /* Current instance. */
UINT word_CA5A = 0U; /* Configuration: Cry */
int word_CA5C = 0; /* UFO beam height (sub). */
WORD word_CA5E = 0; /* Unused. */
HWND word_CA60[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; /* Known instance list. When no other instance exists, [8] is used to store subwindow handle. */
int word_CA72 = 0; /* UFO beam height. */
int word_CA74 = 0; /* Number of currently visible windows. */
WORD word_CA76 = 0; /* Sleeping after timeout? */
WORD word_CA78 = 0; /* Unused. */
#ifdef _WIN32
HWND ownerwindow = NULL;
#endif

void PASCAL sub_10(void FAR *, void FAR *);
int PASCAL sub_114(void FAR *, void FAR *, int);
void PASCAL sub_230(void FAR *, void FAR *);
#define sub_414(p) ((((BITMAPINFOHEADER FAR *)p)->biClrUsed == 0) ? ((DWORD)1 << ((BITMAPINFOHEADER FAR *)p)->biBitCount) : (((BITMAPINFOHEADER FAR *)p)->biClrUsed))
WORD sub_155A(void FAR *);
WORD sub_15B4(void FAR *);
HPALETTE sub_1658(HDC, void FAR *);
HPALETTE sub_1791(HDC, BYTE, BYTE, BYTE);
void sub_17FD(HDC, HPALETTE, HPALETTE, int);
WORD sub_1945(void FAR *);
void FAR * sub_19EC(void FAR *);
void sub_1A16(void FAR *, void FAR *, UINT);
int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
void sub_1DDC(void);
LRESULT CALLBACK sub_1DF3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK sub_2699(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK sub_27FF(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK sub_292A(HWND, UINT, WPARAM, LPARAM);
void sub_2A21(void);
void sub_2A96(void);
void sub_2ABF(HWND);
void sub_2B01(HWND, HWND);
BOOL sub_2B30(HDC, spriteinfo *, int, int);
void sub_2EEC(spriteinfo *);
void sub_2F36(void);
void sub_2FB7(LPCSTR, LPCSTR, UINT, LPCSTR);
void sub_2FF8(void);
BOOL sub_306A(HWND);
void sub_3119();
void sub_31A8(int, int, int);
void sub_3237(HWND);
void sub_3284(HWND);
void sub_3717(HWND);
void sub_399D(HWND, int, int, int, int);
BOOL sub_39D6(HWND);
int sub_3A36(int, int, int, int);
void sub_3B4C(HWND);
BOOL sub_3C20(HWND);
void sub_3D12(HWND);
void sub_3D5F(HWND);
void sub_3DA7(HWND);
void sub_3DF0(void);
int sub_3E7C(HWND *, int, int, int, int);
int sub_408C(HWND *, int, int, int, int);
int sub_419E(HWND, int, int, int, int);
void sub_4210(int, UINT, WORD);
void sub_428E(void);
void sub_42AA(LPCSTR);
void sub_42C8(int, UINT, WORD);
BOOL sub_42F3(HDC);
void sub_44ED(void);
void sub_4559(void);
void sub_4614(BOOL);
void sub_46D2(void);
void sub_46F7(void);
void sub_4807(int, int, int);
void sub_488C(int, int, int);
BOOL sub_48F3(HWND);
void sub_491D(HWND, LPRECT);
void sub_496F(int);
void sub_4B3B(void);
void sub_4C21(int, int, int);
int sub_4C91(int, int);
void sub_4CE1(void);
void sub_4CF8(void);
void sub_8FD7(int);
void sub_904A(WPARAM);
void sub_91CD(int, int);
BOOL sub_9200(HWND);
void sub_930F();
void sub_9350(int, int, int);
void sub_93DF(HWND);
void sub_9438(HWND);
BOOL sub_9A49(HWND);

/* Make mask bitmap image out of the first pixel (by simulating x86 assembly). */
void PASCAL sub_10(void FAR * arg_4, void FAR * arg_0)
{
#define ax (LOWORD(eax))
#define cx (LOWORD(ecx))
    BYTE var_2;
    WORD var_4;
    WORD var_6;
    BYTE stack[2 * sizeof(WORD)];
    BYTE * sp = stack + sizeof stack;
    DWORD eax = 0; /* xor eax, eax */
    BYTE al = 0;
    DWORD ebx;
    DWORD ecx = 0; /* xor ecx, ecx */
    WORD dx = 0; /* xor edx, edx */
    BYTE FAR * source = arg_0;
    BYTE FAR * destination = arg_4;
    eax = (WORD)sub_414(source); /* call sub_414 */
    sp -= sizeof(WORD); /* push ax */
    *(WORD *)sp = ax;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biSize */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    var_6 = LOWORD(eax); /* mov [bp+var_6], ax; var_6 = biWidth */
    *(DWORD FAR *)destination = eax; /* stosd; biWidth */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    ecx = eax; /* mov ecx, eax; ecx = biHeight */
    *(DWORD FAR *)destination = eax; /* stosd; biHeight */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 0x10001; /* mov eax, 10001h */
    *(DWORD FAR *)destination = eax; /* stosd; biPlanes = 1, biBitCount = 1 */
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biCompression */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd; biSizeImage */
    source += 4;
    var_4 = (var_6 + 31) / 32; /* mov ax, [bp+var_6]; add ax, 31; shr ax, 5; mov [bp+var_4], ax */
    eax = var_4 * 4 * cx; /* shl ax, 2; mul cx */
    *(DWORD FAR *)destination = eax; /* stosd; biSizeImage = ceil(biWidth, 32) * 4 * biHeight */
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biXPelsPerMeter */
    source += 4;
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biYPelsPerMeter */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 2; /* mov eax, 2 */
    *(DWORD FAR *)destination = eax; /* stosd; biClrUsed */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 2; /* mov eax, 2 */
    *(DWORD FAR *)destination = eax; /* stosd; biClrImportant */
    destination += 4;
    eax = *(WORD *)sp; /* pop ax */
    sp += sizeof(WORD);
    source += ax * sizeof(RGBQUAD); /* shl ax, 2; add si, ax */
    eax = 0x00FFFFFF; /* mov eax, 0FFFFFFh */
    *(DWORD FAR *)destination = eax; /* stosd */
    destination += 4;
    eax = 0; /* xor eax, eax */
    *(DWORD FAR *)destination = eax; /* stosd */
    destination += 4;
    var_2 = *source; /* mov al, [esi]; mov [bp+var_2], al; Read the first colour */
    do {
        sp -= sizeof(WORD); /* push cx */
        *(WORD *)sp = cx;
        dx = var_6; /* mov dx, [bp+var_6]; dx = biWidth */
        ecx = var_4; /* mov cx, [bp+var_4]; ceil(biWidth, 32) */
        do {
            sp -= sizeof(WORD); /* push cx */
            *(WORD *)sp = cx;
            ebx = 0; /* xor ebx, ebx */
            ecx = 8; /* mov cx, 8 */
            do {
                if ((short)dx > 0) { /* cmp dx, 0; jle short loc_F0 */
                    eax = (*(DWORD FAR *)source); /* lods dword ptr [esi] */
                    source += 4;
                    dx -= 4; /* sub dx, 4 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                } else { /* jmp short loc_F4 */
                    ebx <<= 4; /* shl ebx, 4 */
                }
            } while (--ecx != 0); /* loop loc_A4; 8 */
            eax = (DWORD)LOBYTE(LOWORD(ebx)) << 24 | (DWORD)HIBYTE(LOWORD(ebx)) << 16 | (DWORD)LOBYTE(HIWORD(ebx)) << 8 | (DWORD)HIBYTE(HIWORD(ebx)); /* mov eax, ebx; xchg al, ah; ror eax, 16; xchg al, ah */
            *(DWORD FAR *)destination = eax; /* stos dword ptr es:[edi] */
            destination += 4;
            ecx = *(WORD *)sp; /* pop cx */
            sp += sizeof(WORD);
        } while (--ecx != 0); /* loop loc_9D; ceil(biWidth, 32) */
        ecx = *(WORD *)sp; /* pop cx */
        sp += sizeof(WORD);
    } while (--ecx != 0); /* loop loc_96; biHeight */
#undef cx
#undef ax
}

/* Make mask bitmap image out of the specific colour index in the palette (by simulating x86 assembly) (unused). */
int PASCAL sub_114(void FAR * arg_6, void FAR * arg_2, int arg_0)
{
#define ax (LOWORD(eax))
#define bl (LOBYTE(LOWORD(ebx)))
#define cx (LOWORD(ecx))
    BYTE var_2;
    int var_4 = 0; /* mov [bp+var_4], 0 */
    WORD var_6;
    WORD var_8;
    BYTE stack[sizeof(WORD) + sizeof(BYTE FAR *)];
    BYTE * sp = stack + sizeof stack;
    DWORD eax = 0; /* xor eax, eax */
    BYTE al = 0;
    DWORD ebx;
    DWORD ecx = 0; /* xor ecx, ecx */
    WORD dx = 0; /* xor edx, edx */
    BYTE FAR * source = arg_2; /* lds si, [bp+arg_2] */
    BYTE FAR * destination = arg_6; /* les di, [bp+arg_6] */
    eax = (WORD)sub_414(source); /* call sub_414 */
    sp -= sizeof(WORD); /* push ax */
    *(WORD *)sp = ax;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biSize */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    var_8 = LOWORD(eax); /* mov [bp+var_8], ax; var_8 = biWidth */
    *(DWORD FAR *)destination = eax; /* stosd; biWidth */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    ecx = eax; /* mov ecx, eax; ecx = biHeight */
    *(DWORD FAR *)destination = eax; /* stosd; biHeight */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 0x10001; /* mov eax, 10001h */
    *(DWORD FAR *)destination = eax; /* stosd; biPlanes = 1, biBitCount = 1 */
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biCompression */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd; biSizeImage */
    source += 4;
    var_6 = (var_8 + 31) / 32; /* mov ax, [bp+var_8]; add ax, 31; shr ax, 5; mov [bp+var_6], ax */
    eax = var_6 * 4 * cx; /* shl ax, 2; mul cx */
    *(DWORD FAR *)destination = eax; /* stosd; biSizeImage = ceil(biWidth, 32) * 4 * biHeight */
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biXPelsPerMeter */
    source += 4;
    destination += 4;
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; biYPelsPerMeter */
    source += 4;
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 2; /* mov eax, 2 */
    *(DWORD FAR *)destination = eax; /* stosd; biClrUsed */
    destination += 4;
    eax = (*(DWORD FAR *)source); /* lodsd */
    source += 4;
    eax = 2; /* mov eax, 2 */
    *(DWORD FAR *)destination = eax; /* stosd; biClrImportant */
    destination += 4;
    sp -= sizeof(BYTE FAR *); /* push esi */
    *(BYTE FAR * *)sp = source;
    source += arg_0 * sizeof(RGBQUAD); /* mov ax, [bp+arg_0]; shl ax, 2; add si, ax */
    *(DWORD FAR *)destination = *(DWORD FAR *)source; /* movsd; Mask colour */
    source += 4;
    destination += 4;
    eax = 0; /* xor eax, eax */
    *(DWORD FAR *)destination = eax; /* stosd */
    destination += 4;
    source = *(BYTE FAR * *)sp; /* pop esi */
    sp += sizeof(BYTE FAR *);
    eax = *(WORD *)sp; /* pop ax */
    sp += sizeof(WORD);
    source += ax * sizeof(RGBQUAD); /* shl ax, 2; add si, ax */
    var_2 = LOBYTE(arg_0); /* mov ax, [bp+arg_0]; mov [bp+var_2], al; The specified colour */
    do {
        sp -= sizeof(WORD); /* push cx */
        *(WORD *)sp = cx;
        dx = var_8; /* mov dx, [bp+var_8]; dx = biWidth */
        ecx = var_6; /* mov cx, [bp+var_6]; ceil(biWidth, 32) */
        do {
            sp -= sizeof(WORD); /* push cx */
            *(WORD *)sp = cx;
            ebx = 0; /* xor ebx, ebx */
            ecx = 8; /* mov cx, 8 */
            do {
                if ((short)dx > 0) { /* cmp dx, 0; jle short loc_209 */
                    eax = (*(DWORD FAR *)source); /* lods dword ptr [esi] */
                    source += 4;
                    dx -= 4; /* sub dx, 4 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = LOBYTE(ax) == var_2 ? 1 : 0; /* cmp al, [bp+var_2]; setz al; */
                    ebx = ebx << 1 | (al == 0 ? 1 : 0); /* cmp al, 1; rcl ebx, 1 */
                    eax >>= 8; /* shr eax, 8 */
                    al = bl; /* mov al, bl */
                    al &= 0x0F; /* and al, 0Fh */
                    var_4 += al < 0x0F ? 1 : 0; /* cmp al, 0Fh; adc [bp+var_4], 0 */
                } else { /* jmp short loc_20D */
                    ebx <<= 4; /* shl ebx, 4 */
                }
            } while (--ecx != 0); /* loop loc_1B3; 8 */
            eax = (DWORD)LOBYTE(LOWORD(ebx)) << 24 | (DWORD)HIBYTE(LOWORD(ebx)) << 16 | (DWORD)LOBYTE(HIWORD(ebx)) << 8 | (DWORD)HIBYTE(HIWORD(ebx)); /* mov eax, ebx; xchg al, ah; ror eax, 16; xchg al, ah */
            *(DWORD FAR *)destination = eax; /* stos dword ptr es:[edi] */
            destination += 4;
            ecx = *(WORD *)sp; /* pop cx */
            sp += sizeof(WORD);
        } while (--ecx != 0); /* loop loc_1AC; ceil(biWidth, 32) */
        ecx = *(WORD *)sp; /* pop cx */
        sp += sizeof(WORD);
    } while (--ecx != 0); /* loop loc_1A5; biHeight */
    return var_4; /* mov ax, [bp+var_4]; Number of non-transparent blocks */
#undef cx
#undef bl
#undef ax
}

/* Decompress bitmap image. */
void PASCAL sub_230(void FAR * arg_4, void FAR * arg_0)
{
    BYTE FAR * source = arg_0;
    BYTE FAR * destination = arg_4;
    BYTE FAR * originalsource = NULL;
    BYTE FAR * originaldestination = NULL;
    WORD var_2 = (WORD)((BITMAPINFOHEADER FAR *)source)->biWidth;
    DWORD ebx = var_2 + 3 & (WORD)-4;
    LONG edx = ((BITMAPINFOHEADER FAR *)source)->biHeight;
    DWORD compression = ((BITMAPINFOHEADER FAR *)source)->biCompression;
    WORD bitcount = ((BITMAPINFOHEADER FAR *)source)->biBitCount;
    DWORD counter = ((BITMAPINFOHEADER FAR *)source)->biSize;
    BYTE bytebuffer[2] = {0, 0};
    for (; counter != 0; counter -= 1) {
        *destination++ = *source++;
    }
    ((BITMAPINFOHEADER FAR *)arg_4)->biCompression = BI_RGB;
    counter = sub_414(arg_0) * 4;
    for (; counter != 0; counter -= 1) {
        *destination++ = *source++;
    }
    if (compression == BI_RGB) {
        if (bitcount == 4) {
            ((BITMAPINFOHEADER FAR *)arg_4)->biBitCount = 8;
            if (((BITMAPINFOHEADER FAR *)arg_4)->biClrUsed == 0) {
                ((BITMAPINFOHEADER FAR *)arg_4)->biClrUsed = 16;
            }
            compression = edx;
            var_2 = (var_2 + 1) / 2 + 3 & -4;
            do {
                originalsource = source;
                originaldestination = destination;
                counter = ebx;
                do {
                    if ((counter & 1) == 0) {
                        bytebuffer[0] = *source++;
                        bytebuffer[1] = bytebuffer[0];
                        bytebuffer[0] >>= 4;
                    } else {
                        bytebuffer[0] = bytebuffer[1];
                        bytebuffer[0] &= 0x0F;
                    }
                    *destination++ = bytebuffer[0];
                } while (--counter != 0);
                destination = originaldestination + ebx;
                source = originalsource + var_2;
            } while (--compression != 0);
        } else {
            counter = ebx * edx;
            for (; counter != 0; counter -= 1) {
                *destination++ = *source++;
            }
        }
    } else if (compression == BI_RLE4) {
        ((BITMAPINFOHEADER FAR *)arg_4)->biBitCount = 8;
        if (((BITMAPINFOHEADER FAR *)arg_4)->biClrUsed == 0) {
            ((BITMAPINFOHEADER FAR *)arg_4)->biClrUsed = 16;
        }
        for (;;) {
            originaldestination = destination;
            for (;;) {
                bytebuffer[0] = *source++;
                bytebuffer[1] = *source++;
                if (bytebuffer[0] == 0) {
                    if (bytebuffer[1] == 0) {
                        destination = originaldestination + ebx;
                        break;
                    } else if (bytebuffer[1] == 1) {
                        return;
                    } else if (bytebuffer[1] == 2) {
                        bytebuffer[0] = *source++;
                        bytebuffer[1] = *source++;
                        if (bytebuffer[1] != 0) {
                            do {
                                destination += ebx;
                                originaldestination += ebx;
                            } while (bytebuffer[1] != 0);
                        }
                        destination += bytebuffer[0];
                    } else {
                        counter = bytebuffer[1];
                        do {
                            bytebuffer[0] = *source++;
                            bytebuffer[1] = *source++;
                            *destination++ = bytebuffer[0] >> 4;
                            if (--counter == 0) {
                                break;
                            }
                            *destination++ = bytebuffer[0] & 0x0F;
                            if (--counter == 0) {
                                break;
                            }
                            *destination++ = bytebuffer[1] >> 4;
                            if (--counter == 0) {
                                break;
                            }
                            *destination++ = bytebuffer[1] & 0x0F;
                        } while (--counter != 0);
                    }
                } else {
                    counter = bytebuffer[0] / 2;
                    for (; counter != 0; counter -= 1) {
                        *destination++ = bytebuffer[1] >> 4;
                        *destination++ = bytebuffer[1] & 0x0F;
                    }
                    if ((bytebuffer[0] & 1) != 0) {
                        *destination++ = bytebuffer[1] >> 4;
                    }
                }
            }
        }
    } else if (compression == BI_RLE8) {
        for (;;) {
            originaldestination = destination;
            for (;;) {
                bytebuffer[0] = *source++;
                bytebuffer[1] = *source++;
                if (bytebuffer[0] == 0) {
                    if (bytebuffer[1] == 0) {
                        destination = originaldestination + ebx;
                        break;
                    } else if (bytebuffer[1] == 1) {
                        return;
                    } else if (bytebuffer[1] == 2) {
                        bytebuffer[0] = *source++;
                        bytebuffer[1] = *source++;
                        if (bytebuffer[1] != 0) {
                            do {
                                destination += ebx;
                                originaldestination += ebx;
                            } while (bytebuffer[1] != 0);
                        }
                        destination += bytebuffer[0];
                    } else {
                        counter = bytebuffer[1];
                        do {
                            *destination++ = *source++;
                        } while (--counter != 0);
                        source += bytebuffer[1] & 1;
                    }
                } else {
                    do {
                        *destination++ = bytebuffer[1];
                    } while (--bytebuffer[0] != 0);
                }
            }
        }
    }
}

/* Get palette size. */
WORD sub_155A(void FAR * arg_0)
{
    DWORD FAR * var_4;
    WORD var_6;
    var_4 = arg_0;
    var_6 = sub_15B4(var_4);
    if (*var_4 == 12) {
        return var_6 * sizeof(RGBTRIPLE);
    } else {
        return var_6 * sizeof(RGBQUAD);
    }
}

/* Get number of colours in palette. */
WORD sub_15B4(void FAR * arg_0)
{
    WORD var_2;
    BITMAPINFOHEADER FAR * var_6;
    BITMAPCOREHEADER FAR * var_A;
    var_6 = arg_0;
    var_A = arg_0;
    if (var_6->biSize != 12) {
        if (var_6->biClrUsed != 0) {
            return (WORD)var_6->biClrUsed;
        }
        var_2 = var_6->biBitCount;
    } else {
        var_2 = var_A->bcBitCount;
    }
    switch (var_2) {
    case 1:
        return 2;
    case 4:
        return 16;
    case 8:
        return 256;
    default:
        return 0;
    }
}

/* Create palette based on given bitmap image. */
HPALETTE sub_1658(HDC arg_0, void FAR * arg_2)
{
    const BYTE FAR * var_4;
    HPALETTE var_6;
    LOGPALETTE * var_8;
    int var_A;
    int var_C;
    if ((GetDeviceCaps(arg_0, RASTERCAPS) & RC_PALETTE) == 0) {
        var_A = 256;
    } else {
        var_A = arg_2 != NULL ? ((BITMAPINFOHEADER FAR *)arg_2)->biClrUsed != 0 ? (int)(((BITMAPINFOHEADER FAR *)arg_2)->biClrUsed) : (1 << ((BITMAPINFOHEADER FAR *)arg_2)->biBitCount) : GetDeviceCaps(arg_0, SIZEPALETTE);
    }
    var_8 = (LOGPALETTE *)LocalAlloc(LPTR, (var_A + 2) * sizeof(PALETTEENTRY));
    var_8->palVersion = 0x0300;
    var_8->palNumEntries = (WORD)var_A;
    if (arg_2 != NULL) {
        var_4 = (BYTE FAR *)arg_2 + ((BITMAPINFOHEADER FAR *)arg_2)->biSize;
        for (var_C = 0; var_C < var_A; var_C += 1) {
            var_8->palPalEntry[var_C].peRed = var_4[2];
            var_8->palPalEntry[var_C].peGreen = var_4[1];
            var_8->palPalEntry[var_C].peBlue = var_4[0];
            var_8->palPalEntry[var_C].peFlags = 0;
            var_4 += sizeof(PALETTEENTRY);
        }
    } else {
        GetSystemPaletteEntries(arg_0, 0U, var_A, var_8->palPalEntry);
    }
    var_6 = CreatePalette(var_8);
    LocalFree(var_8);
    return var_6;
}

/* Create mask palette based on given RGB values. */
HPALETTE sub_1791(HDC arg_0, BYTE arg_2, BYTE arg_3, BYTE arg_4)
{
    const BYTE FAR * var_4;
    HPALETTE var_6;
    LOGPALETTE * var_8;
    var_8 = (LOGPALETTE *)LocalAlloc(LPTR, 12U);
    var_8->palVersion = 0x0300;
    var_8->palNumEntries = 1;
    var_8->palPalEntry[0].peRed = arg_2;
    var_8->palPalEntry[0].peGreen = arg_3;
    var_8->palPalEntry[0].peBlue = arg_4;
    var_8->palPalEntry[0].peFlags = 0;
    var_4/* += 4 */;
    var_6 = CreatePalette(var_8);
    LocalFree(var_8);
    return var_6;
}

/* Set palette entries based on another palette with nearest colours (unused). */
void sub_17FD(HDC arg_0, HPALETTE arg_2, HPALETTE arg_4, int arg_6)
{
    PALETTEENTRY * var_2;
    PALETTEENTRY * var_4;
    int var_6;
    int var_8;
    COLORREF var_C;
    COLORREF var_10;
    int var_12;
    if ((GetDeviceCaps(arg_0, RASTERCAPS) & RC_PALETTE) == 0) {
        return;
    }
    var_6 = GetDeviceCaps(arg_0, SIZEPALETTE);
    if (var_6 == 0) {
        var_6 = 256;
    }
    var_2 = (PALETTEENTRY *)LocalAlloc(LPTR, arg_6 * sizeof(PALETTEENTRY));
    var_4 = (PALETTEENTRY *)LocalAlloc(LPTR, var_6 * sizeof(PALETTEENTRY));
    GetPaletteEntries(arg_4, 0U, arg_6, var_2);
    GetPaletteEntries(arg_2, 0U, var_6, var_4);
    for (var_8 = 0; var_8 < arg_6; var_8 += 1) {
        var_C = *(COLORREF *)&var_2[var_8];
        var_12 = GetNearestPaletteIndex(arg_2, var_C);
        var_10 = *(COLORREF *)&var_4[var_12];
        if (var_10 != var_C) {
            if (var_12 < 10 || var_12 > word_9CF0) {
                if (word_9CF0 < 10) {
                    break;
                } else {
                    var_12 = word_9CF0--;
                }
            }
            *(COLORREF *)&var_4[var_12] = var_C;
        }
    }
    SetPaletteEntries(arg_2, 0U, var_6, var_4);
    LocalFree(var_4);
    LocalFree(var_2);
}

/* Get colour index of first pixel. */
WORD sub_1945(void FAR * arg_0)
{
    BYTE FAR * var_4;
    BYTE var_6;
    var_4 = sub_19EC(arg_0);
    var_6 = *var_4++;
    switch (((BITMAPINFOHEADER FAR *)arg_0)->biCompression) {
    case BI_RGB:
        if (((BITMAPINFOHEADER FAR *)arg_0)->biBitCount == 4) {
            var_6 >>= 4;
        }
        break;
    case BI_RLE8:
        if (var_6 == 0) {
            var_4 += 1;
        }
        var_6 = *var_4;
        break;
    case BI_RLE4:
        if (var_6 == 0) {
            var_4 += 1;
        }
        var_6 = *var_4 >> 4;
        break;
    default:
        break;
    }
    return var_6;
}

/* Get pointer to pixel bits in bitmap image. */
void FAR * sub_19EC(void FAR * arg_0)
{
    return (void FAR *)((BYTE FAR *)arg_0 + *(WORD FAR *)arg_0 + ((BITMAPINFOHEADER FAR *)arg_0)->biClrUsed * sizeof(RGBQUAD));
}

/* Flip bitmap image. arg_8 contains 1: Flip horizontally, arg_8 contains 2: Flip vertically */
void sub_1A16(void FAR * arg_0, void FAR * arg_4, UINT arg_8)
{
    BYTE FAR * var_4;
    BYTE FAR * var_8;
    BYTE FAR * var_C;
    int var_E;
    int var_10;
    int var_12;
    int var_14;
    LONG var_18;
    var_4 = arg_0;
    var_8 = arg_4;
    var_C = sub_19EC(arg_4);
    while (var_C > var_8) {
        *var_4++ = *var_8++;
    }
    var_E = ((BITMAPINFOHEADER FAR *)arg_4)->biBitCount == 4 ? (int)(-(((BITMAPINFOHEADER FAR *)arg_4)->biWidth % 8) & 7) : (int)(-(((BITMAPINFOHEADER FAR *)arg_4)->biWidth % 4) & 3);
    var_10 = ((BITMAPINFOHEADER FAR *)arg_4)->biBitCount == 4 ? (int)(((BITMAPINFOHEADER FAR *)arg_4)->biWidth + var_E) / 2 : (int)(((BITMAPINFOHEADER FAR *)arg_4)->biWidth + var_E);
    if ((arg_8 & 2) != 0) {
        var_C += (((BITMAPINFOHEADER FAR *)arg_4)->biHeight - 1) * var_10;
    }
    if ((arg_8 & 1) != 0) {
        var_18 = ((BITMAPINFOHEADER FAR *)arg_4)->biBitCount == 4 ? ((BITMAPINFOHEADER FAR *)arg_4)->biWidth / 2 : ((BITMAPINFOHEADER FAR *)arg_4)->biWidth;
        var_C += var_18 - 1;
    }
    for (var_12 = 0; ((BITMAPINFOHEADER FAR *)arg_4)->biHeight > var_12; var_12 += 1) {
        var_8 = var_C;
        if (((BITMAPINFOHEADER FAR *)arg_4)->biBitCount == 4) {
            if ((arg_8 & 1) != 0) {
                for (var_14 = 0; var_14 < var_10; var_14 += 1) {
                    *var_4 = *var_8 >> 4 & 0x0F | *var_8 << 4;
                    var_8 -= 1;
                    var_4 += 1;
                }
            } else {
                for (var_14 = 0; var_14 < var_10; var_14 += 1) {
                    *var_4++ = *var_8++;
                }
            }
        } else {
            if ((arg_8 & 1) != 0) {
                for (var_14 = 0; var_14 < var_10; var_14 += 1) {
                    *var_4++ = *var_8--;
                }
            } else {
                for (var_14 = 0; var_14 < var_10; var_14 += 1) {
                    *var_4++ = *var_8++;
                }
            }
        }
        var_18 = (arg_8 & 2) != 0 ? -var_10 : var_10;
        var_C += var_18;
    }
}

/* WinMain function. */
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND var_2;
    MSG var_14;
    WNDCLASS var_2E;
    if (hPrevInstance == NULL) {
        var_2E.style = CS_DBLCLKS;
        var_2E.lpfnWndProc = sub_1DF3;
        var_2E.cbClsExtra = 0;
        var_2E.cbWndExtra = 8;
        var_2E.hInstance = hInstance;
        var_2E.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(100));
        var_2E.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(106));
        var_2E.hbrBackground = NULL;
        var_2E.lpszMenuName = NULL;
        var_2E.lpszClassName = "ScreenMatePoo";
        if (RegisterClass(&var_2E) == 0) {
            return 0;
        }
    }
    if (hPrevInstance == NULL) {
        var_2E.style = CS_DBLCLKS;
        var_2E.lpfnWndProc = sub_2699;
        var_2E.cbClsExtra = 0;
        var_2E.cbWndExtra = 0;
        var_2E.hInstance = hInstance;
        var_2E.hIcon = NULL;
        var_2E.hCursor = LoadCursor(NULL, IDC_ARROW);
        var_2E.hbrBackground = NULL;
        var_2E.lpszMenuName = NULL;
        var_2E.lpszClassName = "ScreenMatePooSub";
        if (RegisterClass(&var_2E) == 0) {
            return 0;
        }
    }
    word_CA58 = hInstance;
    if (FindWindow("ScreenMatePoo", "Screen Mate") != NULL) {
        word_CA3C = 1;
    }
#ifdef _WIN32
    /* In 32-bit Windows, popup window is now in the taskbar by default. Additional code is needed to hide the popup window from taskbar while keeping it in the Alt+Tab list. */
    var_2E.style = 0;
    var_2E.lpfnWndProc = DefWindowProc;
    var_2E.cbClsExtra = 0;
    var_2E.cbWndExtra = 0;
    var_2E.hInstance = hInstance;
    var_2E.hIcon = NULL;
    var_2E.hCursor = NULL;
    var_2E.hbrBackground = NULL;
    var_2E.lpszMenuName = NULL;
    var_2E.lpszClassName = "ScreenMatePooOwner";
    if (RegisterClass(&var_2E) == 0) {
        return 0;
    }
    /* Create a hidden owner top-level window to hide visible windows from taskbar. */
    ownerwindow = CreateWindowEx(0L, "ScreenMatePooOwner", NULL, 0L, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
    if (ownerwindow == NULL) {
        return 0;
    }
    /* Set the visible window to be owned by the hidden top-level window. */
    var_2 = CreateWindowEx(0L, "ScreenMatePoo", "Screen Mate", WS_POPUP, 0, 0, 0, 0, ownerwindow, NULL, hInstance, NULL);
#else
    var_2 = CreateWindowEx(0L, "ScreenMatePoo", "Screen Mate", WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
#endif
    if (var_2 == NULL) {
        return 0;
    }
    ShowWindow(var_2, nShowCmd);
    UpdateWindow(var_2);
    while (GetMessage(&var_14, NULL, 0U, 0U)) {
        TranslateMessage(&var_14);
        DispatchMessage(&var_14);
    }
#ifdef _WIN32
    DestroyWindow(ownerwindow);
#endif
    return (int)var_14.wParam;
}

/* Set cursor position changed flag (unused). */
void sub_1DDC(void)
{
    word_A798 = 1;
}

/* Window procedure. */
LRESULT CALLBACK sub_1DF3(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC var_2;
    void FAR * var_6;
    HGLOBAL var_8;
    HRSRC var_A;
    void FAR * var_E;
    int var_10;
    int var_12;
    RECT var_1A;
    POINT var_1E;
    char var_122[260];
    POINT var_126;
    UINT var_128;
    FARPROC proc;
    LPWINDOWPOS windowpos;
#ifdef _WIN32
    HANDLE user32;
#endif
    switch (uMsg) {
    case WM_CREATE:
        if (!sub_3C20(hWnd)) {
            MessageBox(hWnd, "Screen Mate‚ÍÅ‘å‚WŒÂ‚Ü‚Å‚Å‚·", "Screen Mate", MB_ICONHAND | MB_OK);
            return -1;
        }
#ifdef _WIN32
        /* Additional code that allows drag-and-drop across different privileges in Windows Vista and higher. */
        user32 = GetModuleHandle("user32.dll");
        if (user32 != NULL) {
            BOOL (WINAPI * changewindowmessagefilterex)(HWND, UINT, DWORD, LPVOID) = (BOOL (WINAPI *)(HWND, UINT, DWORD, LPVOID))GetProcAddress(user32, "ChangeWindowMessageFilterEx");
            if (changewindowmessagefilterex != NULL) {
                changewindowmessagefilterex(hWnd, 0x0049, 1, NULL); /* WM_COPYGLOBALDATA */
                changewindowmessagefilterex(hWnd, 0x004A, 1, NULL); /* WM_COPYDATA */
                changewindowmessagefilterex(hWnd, WM_DROPFILES, 1, NULL);
            }
        }
#endif
        DragAcceptFiles(hWnd, TRUE);
        word_C0B0 = hWnd;
        sub_2F36();
        if (word_CA3E != 0) {
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
        var_2 = GetDC(hWnd);
        var_A = FindResource(word_CA58, MAKEINTRESOURCE(101), RT_BITMAP);
        var_8 = LoadResource(word_CA58, var_A);
        var_6 = LockResource(var_8);
        var_E = (void FAR *)((BYTE FAR *)var_6 + *(WORD FAR *)var_6 + sub_155A(var_6));
        word_CA4A = sub_1658(var_2, var_6);
        FreeResource(var_8);
        SelectPalette(var_2, word_CA4A, FALSE);
        RealizePalette(var_2);
        if (!sub_42F3(var_2)) {
            MessageBox(hWnd, "ƒƒ‚ƒŠ‚ª•s‘«‚µ‚Ä‚¢‚Ü‚·", "Screen Mate", MB_ICONHAND | MB_OK);
            ReleaseDC(hWnd, var_2);
            return -1;
        }
        ReleaseDC(hWnd, var_2);
        if (!sub_306A(hWnd)) {
            MessageBox(hWnd, "ƒƒ‚ƒŠ‚ª•s‘«‚µ‚Ä‚¢‚Ü‚·", "Screen Mate", MB_ICONHAND | MB_OK);
            return -1;
        }
        SetTimer(hWnd, 1U, 108U, NULL);
        break;
    case WM_DROPFILES:
        if (word_CA60[8] == NULL) {
            if (DragQueryFile((HDROP)wParam, 0U, var_122, 260U) != 0U) {
                sub_42AA(var_122);
                sub_8FD7(4);
            }
        }
        DragFinish((HDROP)wParam);
        break;
    case WM_USER + 1:
        switch (lParam) {
        case 0x202:
        case 0x205:
            if (word_C0AE != 0) {
                if (word_CA60[8] != NULL) {
                    sub_2ABF(word_CA60[8]);
                }
                sub_2ABF(hWnd);
            } else {
                sub_2ABF(hWnd);
                if (word_CA60[8] != NULL) {
                    sub_2ABF(word_CA60[8]);
                }
            }
            sub_2ABF(hWnd);
            *(HMENU *)var_122 = CreatePopupMenu();
            AppendMenu(*(HMENU *)var_122, 0U, 101U, "Screen Mate‚ÌÝ’è...");
            AppendMenu(*(HMENU *)var_122, 0U, IDCANCEL, "Screen Mate‚ÌI—¹");
            GetCursorPos(&var_126);
            TrackPopupMenu(*(HMENU *)var_122, 0U, var_126.x, var_126.y, 0, hWnd, NULL);
            DestroyMenu(*(HMENU *)var_122);
            return 0;
        default:
            break;
        }
        return 0;
    case WM_WINDOWPOSCHANGING:
        windowpos = (LPWINDOWPOS)lParam;
        if (word_A7A2 != 0) {
            windowpos = (LPWINDOWPOS)lParam;
        }
        windowpos->flags |= SWP_NOCOPYBITS;
        word_A7AC = 1;
        return 0;
    case WM_WINDOWPOSCHANGED:
        return 0;
    case WM_TIMER:
        if (word_C0BA != 0) {
            word_C0BA -= 1;
            return 0;
        }
        if (word_C0B6 == 0) {
            GetCursorPos(&var_1E);
            if (stru_A7B0.x != var_1E.x || stru_A7B0.y != var_1E.y) {
                stru_A7B0.x = var_1E.x;
                stru_A7B0.y = var_1E.y;
                word_A798 = 1;
            }
            if (word_CA76 != 0) {
                if (word_A798 != 0) {
                    word_CA76 = 0;
                    word_C0A4 = 0;
                    sub_8FD7(0);
                }
            } else {
                if (word_A798 != 0) {
                    word_A798 = 0;
                    word_C0A4 = 0;
                } else {
                    if (word_C0A4++ > 300) {
                        sub_8FD7(3);
                    }
                }
            }
        }
        word_A7AC = 0;
        word_C0B0 = hWnd;
        sub_4CF8();
        sub_3284(hWnd);
        sub_3717(hWnd);
        word_A7A2 = 1;
        return 0;
    case WM_USER:
        if (wParam == 1) {
            sub_3D5F((HWND)lParam);
        }
        if (wParam == 2) {
            sub_3DA7((HWND)lParam);
        }
        return 0;
    case WM_PAINT:
        if (word_A7AC != 0) {
            word_A7AC = 0;
            ValidateRect(hWnd, NULL);
            return 0;
        }
        sub_3237(hWnd);
        ValidateRect(hWnd, NULL);
        return 0;
        GetWindowRect(hWnd, &var_1A);
        if (stru_A7A4.top == var_1A.top && stru_A7A4.bottom == var_1A.bottom && stru_A7A4.left == var_1A.left && stru_A7A4.right == var_1A.right) {
            sub_3237(hWnd);
            ValidateRect(hWnd, NULL);
            return 0;
        }
        GetWindowRect(hWnd, &stru_A7A4);
        ValidateRect(hWnd, NULL);
        return 0;
        break;
    case WM_QUIT:
        return 0;
    case WM_COMMAND:
        switch (wParam) {
        case 101U:
            SendMessage(hWnd, WM_USER + 2, 0, 0);
            break;
        case IDCANCEL:
            DestroyWindow(hWnd);
            return 0;
            break;
        default:
            break;
        }
        break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        if (word_CA60[8] != NULL) {
            break;
        }
        if (word_A79E != 0) {
            break;
        }
        SetCapture(hWnd);
        GetWindowRect(hWnd, &var_1A);
        word_A79A = (short)LOWORD(lParam) + var_1A.left;
        word_A79C = (short)HIWORD(lParam) + var_1A.top;
        word_A79E = 1;
        sub_8FD7(1);
        sub_3284(hWnd);
        sub_3717(hWnd);
        break;
    case WM_MOUSEMOVE:
        if (word_A79E == 0) {
            break;
        }
        GetWindowRect(hWnd, &var_1A);
        var_10 = (short)LOWORD(lParam) + var_1A.left;
        var_12 = (short)HIWORD(lParam) + var_1A.top;
        if (word_A79A == var_10 && word_A79C == var_12) {
            break;
        }
        sub_91CD(var_10 - word_A79A, var_12 - word_A79C);
        word_A79A = var_10;
        word_A79C = var_12;
        sub_3284(hWnd);
        sub_3717(hWnd);
        break;
    case WM_RBUTTONUP:
        if (word_A7A0 != 0) {
            DestroyWindow(hWnd);
            break;
        }
    case WM_LBUTTONUP:
        if (word_A79E != 0) {
            GetWindowRect(hWnd, &var_1A);
            var_10 = (short)LOWORD(lParam) + var_1A.left;
            var_12 = (short)HIWORD(lParam) + var_1A.top;
            sub_91CD(var_10 - word_A79A, var_12 - word_A79C);
            sub_8FD7(0);
            if (uMsg == WM_RBUTTONUP) {
                sub_8FD7(2);
            }
            sub_3284(hWnd);
            sub_3717(hWnd);
            ReleaseCapture();
            word_A79E = 0;
        }
        break;
    case WM_RBUTTONDBLCLK:
        word_A7A0 = 1;
        break;
    case WM_LBUTTONDBLCLK:
    case WM_USER + 2:
        *(WORD *)var_122 = word_CA3E;
        var_128 = word_CA42;
        word_C0B0 = hWnd;
        if ((HIBYTE(GetKeyState(VK_SHIFT)) & 0x80) != 0 && (HIBYTE(GetKeyState(VK_CONTROL)) & 0x80) != 0) {
            proc = MakeProcInstance((FARPROC)sub_292A, word_CA58);
            DialogBox(word_CA58, MAKEINTRESOURCE(108), hWnd, (DLGPROC)proc);
        } else {
            proc = MakeProcInstance((FARPROC)sub_27FF, word_CA58);
            DialogBox(word_CA58, MAKEINTRESOURCE(107), hWnd, (DLGPROC)proc);
        }
        FreeProcInstance(proc);
        sub_3237(hWnd);
        if (*(WORD *)var_122 != word_CA3E) {
            if (word_CA3E != 0) {
                SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
            } else {
                SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
            }
        }
        if (var_128 != word_CA42 && word_CA42 != 0) {
            sub_8FD7(2);
        }
        break;
    case WM_DESTROY:
        sub_3D12(hWnd);
        if (word_CA60[8] != NULL) {
            sub_2A96();
        }
        KillTimer(hWnd, 1U);
        sub_428E();
        sub_3119((WORD)0);
        sub_44ED();
        DeleteObject(word_CA4A);
        DragAcceptFiles(hWnd, FALSE);
        PostQuitMessage(0);
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/* Window procedure (sub). */
LRESULT CALLBACK sub_2699(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LPWINDOWPOS var_4;
    switch (uMsg) {
    case WM_CREATE:
        if (!sub_9200(hWnd)) {
            DestroyWindow(hWnd);
            return 1;
        }
        SetTimer(hWnd, 1U, 108U, NULL);
        break;
    case WM_WINDOWPOSCHANGING:
        var_4 = (LPWINDOWPOS)lParam;
        var_4->flags |= SWP_NOCOPYBITS;
        word_A7B4 = 1;
        return 0;
    case WM_WINDOWPOSCHANGED:
        return 0;
    case WM_TIMER:
        word_A7B4 = 0;
        sub_9438(hWnd);
        if (!sub_9A49(hWnd)) {
            word_CA3C = 1;
            sub_4CE1();
        }
        return 0;
    case WM_PAINT:
        if (word_A7B4 != 0) {
            word_A7B4 = 0;
            ValidateRect(hWnd, NULL);
            return 0;
        }
        sub_93DF(hWnd);
        ValidateRect(hWnd, NULL);
        return 0;
    case WM_ERASEBKGND:
        return 0;
    case WM_DESTROY:
        sub_930F(0);
        KillTimer(hWnd, 1U);
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/* Configuration window callback. */
BOOL CALLBACK sub_27FF(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, 1001, BM_SETCHECK, (WPARAM)word_C0AC, 0);
        SendDlgItemMessage(hDlg, 1002, BM_SETCHECK, (WPARAM)word_CA5A, 0);
        SendDlgItemMessage(hDlg, 1003, BM_SETCHECK, (WPARAM)word_C0B6, 0);
        SendDlgItemMessage(hDlg, 1004, BM_SETCHECK, (WPARAM)word_CA42, 0);
        return TRUE;
    case WM_COMMAND:
        if (wParam == IDRETRY) {
            WinHelp(hDlg, "Scmpoo16.hlp", HELP_INDEX, 0L);
            return TRUE;
        }
        if (wParam == IDOK) {
            word_C0AC = IsDlgButtonChecked(hDlg, 1001);
            word_CA5A = IsDlgButtonChecked(hDlg, 1002);
            word_C0B6 = IsDlgButtonChecked(hDlg, 1003);
            word_CA42 = IsDlgButtonChecked(hDlg, 1004);
            sub_2FF8();
        }
        if (wParam == IDABORT) {
            DestroyWindow(word_C0B0);
        }
        if (wParam == IDOK || wParam == IDCANCEL || wParam == IDABORT) {
            EndDialog(hDlg, (int)wParam);
        }
        break;
    default:
        break;
    }
    return FALSE;
}

/* Debug window callback. */
BOOL CALLBACK sub_292A(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:
        CheckRadioButton(hDlg, 1002, 1019, 1002);
        return TRUE;
    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL) {
            EndDialog(hDlg, (int)wParam);
        }
        if (wParam >= 1002 && wParam <= 1031 && IsDlgButtonChecked(hDlg, (int)wParam) != 0U) {
            sub_904A(wParam - 1002);
        }
        switch (wParam) {
        case 1032:
            sub_91CD(0, -20);
            break;
        case 1033:
            sub_91CD(0, 20);
            break;
        case 1034:
            sub_91CD(-20, 0);
            break;
        case 1035:
            sub_91CD(20, 0);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return FALSE;
}

/* Create subwindow. */
void sub_2A21(void)
{
    if (word_CA60[8] != NULL) {
        return;
    }
#ifdef _WIN32
    /* Set the visible window to be owned by the hidden top-level window. */
    word_CA60[8] = CreateWindowEx(0L, "ScreenMatePooSub", "ScreenMate Sub", WS_POPUP, 0, 0, 0, 0, ownerwindow, NULL, word_CA58, NULL);
#else
    word_CA60[8] = CreateWindowEx(0L, "ScreenMatePooSub", "ScreenMate Sub", WS_POPUP, 0, 0, 0, 0, NULL, NULL, word_CA58, NULL);
#endif
    if (word_CA60[8] != NULL) {
        ShowWindow(word_CA60[8], SW_SHOWNA);
        UpdateWindow(word_CA60[8]);
    } else {
        word_CA3C = 1;
        sub_4CE1();
    }
}

/* Destroy subwindow. */
void sub_2A96(void)
{
    if (word_CA60[8] != NULL) {
        DestroyWindow(word_CA60[8]);
        word_CA60[8] = NULL;
    }
}

/* Place window to topmost position. */
void sub_2ABF(HWND arg_0)
{
    if (word_CA3E == 0) {
        SetWindowPos(arg_0, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
        SetWindowPos(arg_0, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    }
}

/* Place a window on top of another. */
void sub_2B01(HWND arg_0, HWND arg_2)
{
    if (word_CA3E == 0) {
        SetWindowPos(arg_0, arg_2, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    }
}

/* Load resource image, generate (flipped) colour and mask images, store handles into sprite info structure. */
BOOL sub_2B30(HDC arg_0, spriteinfo * arg_2, int arg_4, int arg_6)
{
    void FAR * var_4;
    void FAR * var_8;
    void FAR * var_C;
    void FAR * var_10;
    void FAR * var_14;
    HGLOBAL var_16;
    HGLOBAL var_18;
    HGLOBAL var_1A;
    var_16 = NULL;
    var_18 = NULL;
    var_1A = NULL;
    var_16 = LoadResource(word_CA58, FindResource(word_CA58, MAKEINTRESOURCE(arg_4), RT_BITMAP));
    var_C = LockResource(var_16);
    if (var_16 == NULL) {
        return FALSE;
    }
    arg_2->x = 0;
    arg_2->y = 0;
    arg_2->width = *(int FAR *)((BYTE FAR *)var_C + 4);
    arg_2->height = *(int FAR *)((BYTE FAR *)var_C + 8);
    if (arg_6 < 0) {
        var_18 = GlobalAlloc(GMEM_MOVEABLE, 65535);
        if (var_18 == NULL) {
            goto loc_2EB2;
        }
        var_10 = GlobalLock(var_18);
        if (arg_6 < -1) {
            var_1A = GlobalAlloc(GMEM_MOVEABLE, 65535);
            if (var_1A == NULL) {
                goto loc_2EB2;
            }
            var_14 = GlobalLock(var_1A);
            sub_230(var_14, var_C);
            if (arg_6 == -2) {
                sub_1A16(var_10, var_14, 2U);
            } else {
                sub_1A16(var_10, var_14, 1U);
            }
            GlobalFree(var_1A);
            var_1A = NULL;
        } else {
            sub_230(var_10, var_C);
        }
        var_4 = (void FAR *)((BYTE FAR *)var_10 + *(WORD FAR *)var_10 + sub_155A(var_10));
        var_8 = (void FAR *)((BYTE FAR *)var_10 + *(WORD FAR *)var_10 + sub_1945(var_10) * sizeof(RGBQUAD));
        *(DWORD FAR *)var_8 = 0;
        arg_2->bitmaps[0] = CreateDIBitmap(arg_0, var_10, CBM_INIT, var_4, var_10, DIB_RGB_COLORS);
        if (arg_2->bitmaps[0] == NULL) {
            goto loc_2EB2;
        }
        sub_10(var_10, var_10);
        var_4 = (void FAR *)((BYTE FAR *)var_10 + *(WORD FAR *)var_10 + sub_155A(var_10));
        arg_2->bitmaps[1] = CreateDIBitmap(arg_0, var_10, CBM_INIT, var_4, var_10, DIB_RGB_COLORS);
        if (arg_2->bitmaps[1] == NULL) {
            goto loc_2EB2;
        }
        FreeResource(var_16);
        var_16 = NULL;
        GlobalFree(var_18);
        var_18 = NULL;
        return TRUE;
    } else {
        var_4 = (void FAR *)((BYTE FAR *)var_C + *(WORD FAR *)var_C + sub_155A(var_C));
        arg_2->bitmaps[0] = CreateDIBitmap(arg_0, var_C, CBM_INIT, var_4, var_C, DIB_RGB_COLORS);
        if (arg_2->bitmaps[0] == NULL) {
            goto loc_2EB2;
        }
        FreeResource(var_16);
        var_16 = NULL;
        if (arg_6 == 0) {
            arg_2->bitmaps[1] = NULL;
            return TRUE;
        }
        var_16 = LoadResource(word_CA58, FindResource(word_CA58, MAKEINTRESOURCE(arg_6), RT_BITMAP));
        var_C = LockResource(var_16);
        if (var_16 == NULL) {
            goto loc_2EB2;
        }
        arg_2->x = 0;
        arg_2->y = 0;
        arg_2->width = *(int FAR *)((BYTE FAR *)var_C + 4);
        arg_2->height = *(int FAR *)((BYTE FAR *)var_C + 8);
        var_4 = (void FAR *)((BYTE FAR *)var_C + *(WORD FAR *)var_C + sub_155A(var_C));
        arg_2->bitmaps[1] = CreateDIBitmap(arg_0, var_C, CBM_INIT, var_4, var_C, DIB_RGB_COLORS);
        if (arg_2->bitmaps[1] == NULL) {
            goto loc_2EB2;
        }
        FreeResource(var_16);
        return TRUE;
    }
loc_2EB2:
    if (var_16 != NULL) {
        FreeResource(var_16);
    }
    if (var_18 != NULL) {
        GlobalFree(var_18);
    }
    if (var_1A != NULL) {
        GlobalFree(var_1A);
    }
    return FALSE;
}

/* Release sprite images. */
void sub_2EEC(spriteinfo * arg_0)
{
    if (arg_0->bitmaps[0] != NULL) {
        DeleteObject(arg_0->bitmaps[0]);
    }
    if (arg_0->bitmaps[1] != NULL) {
        DeleteObject(arg_0->bitmaps[1]);
    }
    arg_0->bitmaps[0] = NULL;
    arg_0->bitmaps[1] = NULL;
}

/* Read configuration from file. */
void sub_2F36(void)
{
    word_CA78 = 1;
    word_CA3E = 0;
    word_C0AC = 0U;
    word_CA5A = 0U;
    word_CA5A = GetPrivateProfileInt("Stray", "Sound", 0, "scmate.ini");
    word_C0AC = GetPrivateProfileInt("Stray", "Alarm", 0, "scmate.ini");
    word_C0B6 = GetPrivateProfileInt("Stray", "NoSleep", 0, "scmate.ini");
    word_CA42 = GetPrivateProfileInt("Stray", "GForce", 1, "scmate.ini");
}

/* Save individual configuration to file. */
void sub_2FB7(LPCSTR arg_0, LPCSTR arg_4, UINT arg_8, LPCSTR arg_A)
{
    char var_28[40];
    wsprintf(var_28, "%u", arg_8);
    WritePrivateProfileString(arg_0, arg_4, var_28, arg_A);
}

/* Save configurations to file. */
void sub_2FF8(void)
{
    sub_2FB7("Stray", "Sound", word_CA5A, "scmate.ini");
    sub_2FB7("Stray", "Alarm", word_C0AC, "scmate.ini");
    sub_2FB7("Stray", "NoSleep", word_C0B6, "scmate.ini");
    sub_2FB7("Stray", "GForce", word_CA42, "scmate.ini");
}

/* Initialize bitmaps. */
BOOL sub_306A(HWND arg_0)
{
    HDC var_2;
    var_2 = GetDC(arg_0);
    word_A7B6[0] = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A7B6[0] == NULL) {
        goto loc_3104;
    }
    word_A7B6[1] = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A7B6[1] == NULL) {
        goto loc_3104;
    }
    word_A7BA = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A7BA == NULL) {
        goto loc_3104;
    }
    word_CA4C = 0;
    word_CA4E = 0;
    word_CA50 = GetSystemMetrics(SM_CXSCREEN);
    word_CA52 = GetSystemMetrics(SM_CYSCREEN);
    ReleaseDC(arg_0, var_2);
    return TRUE;
loc_3104:
    ReleaseDC(arg_0, var_2);
    return FALSE;
}

/* Release bitmaps. */
void sub_3119()
{
    DeleteObject(word_A7B6[0]);
    DeleteObject(word_A7B6[1]);
    DeleteObject(word_A7BA);
    if (word_C0B4 != NULL) {
        DeleteObject(word_C0B4);
        word_C0B4 = NULL;
    }
    if (word_CA44 != NULL) {
        DeleteObject(word_CA44);
        word_CA44 = NULL;
    }
    if (word_C0B2 != NULL) {
        DeleteObject(word_C0B2);
        word_C0B2 = NULL;
    }
    if (word_C0B8 != NULL) {
        DeleteObject(word_C0B8);
        word_C0B8 = NULL;
    }
}

/* Update window position and sprite to be actually used. */
void sub_31A8(int arg_0, int arg_2, int arg_4)
{
    word_A7DA = arg_0;
    word_A7DC = arg_2;
    word_A7BC = stru_A8A2[arg_4].bitmaps[0];
    word_A7BE = stru_A8A2[arg_4].bitmaps[1];
    word_A7C0 = stru_A8A2[arg_4].x;
    word_A7C2 = stru_A8A2[arg_4].y;
    word_A7DE = stru_A8A2[arg_4].width;
    word_A7E0 = stru_A8A2[arg_4].height;
}

/* Clear window. */
void sub_3237(HWND arg_0)
{
    word_A7F2 = 0;
    word_A7F4 = 0;
    word_A7F6 = 0;
    word_A7F8 = 0;
    MoveWindow(arg_0, 0, 0, 0, 0, TRUE);
    word_A7D4 = 1;
    word_C0BA = 1;
    word_A7D8 = NULL;
}

/* Render sprite with double buffering. */
void sub_3284(HWND arg_0)
{
    HDC var_2;
    HDC var_4;
    HDC var_6;
    int var_C;
    int var_E;
    int var_10;
    int var_12;
    int var_14;
    int var_16;
    int var_18;
    int var_1A;
    int var_1C;
    int var_1E;
    if (word_A7D2 != 0) {
        return;
    }
    if (word_A7F2 == word_A7DA && word_A7F4 == word_A7DC && word_A7D8 == word_A7BC && word_A7C8 == word_A7C0 && word_CA72 == 0) {
        return;
    }
    word_A7D0 ^= 1;
    var_2 = GetDC(NULL);
    SelectPalette(var_2, word_CA4A, FALSE);
    var_4 = CreateCompatibleDC(var_2);
    var_6 = CreateCompatibleDC(var_2);
    SelectPalette(var_6, word_CA4A, FALSE);
    SelectPalette(var_4, word_CA4A, FALSE);
    var_16 = max(word_A7DA, word_A7F2);
    var_14 = max(word_A7DC, word_A7F4);
    var_12 = min(word_A7DE + word_A7DA, word_A7F6 + word_A7F2) - var_16;
    var_10 = min(word_A7DC + word_A7E0, word_A7F4 + word_A7F8) - var_14;
    if (var_12 <= 0 || var_10 <= 0) {
        word_A7FA = 1;
        if (word_A7D4 != 0) {
            word_A7D4 = 0;
        }
        word_A7E2 = word_A7DA;
        word_A7E4 = word_A7DC;
        word_A7E6 = word_A7DE;
        word_A7E8 = word_A7E0;
        SelectObject(var_4, word_A7B6[word_A7D0]);
        BitBlt(var_4, 0, 0, word_A7E6, word_A7E8, var_2, word_A7E2, word_A7E4, SRCCOPY);
    } else {
        word_A7FA = 0;
        word_A7E2 = min(word_A7DA, word_A7F2);
        word_A7E4 = min(word_A7DC, word_A7F4);
        word_A7E6 = max(word_A7DE + word_A7DA, word_A7F6 + word_A7F2) - word_A7E2;
        word_A7E8 = max(word_A7DC + word_A7E0, word_A7F4 + word_A7F8) - word_A7E4;
        SelectObject(var_4, word_A7B6[word_A7D0]);
        BitBlt(var_4, 0, 0, word_A7E6, word_A7E8, var_2, word_A7E2, word_A7E4, SRCCOPY);
        var_1E = max(word_A7E2, word_A7EA);
        var_1C = max(word_A7E4, word_A7EC);
        var_1A = min(word_A7E6 + word_A7E2, word_A7EE + word_A7EA) - var_1E;
        var_18 = min(word_A7E4 + word_A7E8, word_A7EC + word_A7F0) - var_1C;
        var_16 = max(0, var_1E - word_A7E2);
        var_14 = max(0, var_1C - word_A7E4);
        var_E = max(0, var_1E - word_A7EA);
        var_C = max(0, var_1C - word_A7EC);
        if (var_1A > 0 && var_18 > 0) {
            SelectObject(var_6, word_A7B6[LOBYTE(word_A7D0) - 0xFF & 1]);
            BitBlt(var_4, var_16, var_14, var_1A, var_18, var_6, var_E, var_C, SRCCOPY);
        }
    }
    if (word_A7BC != NULL) {
        SelectObject(var_6, word_A7BA);
        BitBlt(var_6, 0, 0, word_A7E6, word_A7E8, var_4, 0, 0, SRCCOPY);
        var_16 = max(0, word_A7DA - word_A7E2);
        var_14 = max(0, word_A7DC - word_A7E4);
        if (word_A7BE != NULL) {
            SelectObject(var_4, word_A7BE);
            BitBlt(var_6, var_16, var_14, word_A7DE, word_A7E0, var_4, word_A7C0, word_A7C2, SRCAND);
            SelectObject(var_4, word_A7BC);
            BitBlt(var_6, var_16, var_14, word_A7DE, word_A7E0, var_4, word_A7C0, word_A7C2, SRCPAINT);
        } else {
            SelectObject(var_4, word_A7BC);
            BitBlt(var_6, var_16, var_14, word_A7DE, word_A7E0, var_4, word_A7C0, word_A7C2, SRCCOPY);
        }
        word_A7D2 = 1;
        word_CA5E = 1;
        MoveWindow(arg_0, word_A7E2, word_A7E4, word_A7E6, word_A7E8 + word_CA72, TRUE);
        word_CA5E = 0;
    }
    DeleteDC(var_4);
    DeleteDC(var_6);
    word_A7EA = word_A7E2;
    word_A7EC = word_A7E4;
    word_A7EE = word_A7E6;
    word_A7F0 = word_A7E8;
    word_A7F2 = word_A7DA;
    word_A7F4 = word_A7DC;
    word_A7F6 = word_A7DE;
    word_A7F8 = word_A7E0;
    word_A7D8 = word_A7BC;
    word_A7C8 = word_A7C0;
    word_A7CA = word_A7C2;
    ReleaseDC(NULL, var_2);
}

/* Render UFO beam (if any) and present render targets onto window. */
void sub_3717(HWND arg_0)
{
    HDC var_2;
    HDC var_4;
    RECT var_C;
    HDC var_E;
#ifdef WIN32
    HDC screen;
#endif
    if (word_A7D2 == 0) {
        return;
    }
    word_A7D2 = 0;
    var_2 = GetDC(arg_0);
    SelectPalette(var_2, word_CA4A, FALSE);
    RealizePalette(var_2);
    var_4 = CreateCompatibleDC(var_2);
    SelectPalette(var_4, word_CA4A, FALSE);
    SelectObject(var_4, word_A7BA);
    BitBlt(var_2, 0, 0, word_A7E6, word_A7E8, var_4, 0, 0, SRCCOPY);
    if (word_CA72 != 0) {
        if (word_C0B8 == NULL) {
            word_C0B8 = CreateCompatibleBitmap(var_2, 40, word_CA52 * 4 / 5);
            if (word_C0B8 == NULL) {
                goto loc_398B;
            }
        }
        if (word_C0B2 == NULL) {
            word_C0B2 = CreateCompatibleBitmap(var_2, 40, word_CA52 * 4 / 5);
            if (word_C0B2 == NULL) {
                goto loc_398B;
            }
        }
        if (word_CA44 == NULL) {
            word_CA44 = CreateSolidBrush(RGB(255, 255, 0));
        }
        if (word_C0B4 == NULL) {
            word_C0B4 = CreateSolidBrush(RGB(128, 128, 0));
        }
        var_E = CreateCompatibleDC(var_2);
        SelectObject(var_E, word_C0B2);
#ifdef _WIN32
        /* Screen contents with height of only 40 pixels can be captured from window device context on Windows 10. Capture directly from screen instead. */
        screen = GetDC(NULL);
        BitBlt(var_E, 0, 0, 40, word_CA72, screen, word_A7E2, word_A7E4 + 40, SRCCOPY);
        ReleaseDC(NULL, screen);
#else
        BitBlt(var_E, 0, 0, 40, word_CA72, var_2, 0, 40, SRCCOPY);
#endif
        var_C.left = 0;
        var_C.top = 0;
        var_C.right = 40;
        var_C.bottom = word_CA72;
        SelectObject(var_4, word_C0B8);
        FillRect(var_4, &var_C, word_CA44);
        BitBlt(var_E, 0, 0, 40, word_CA72, var_4, 0, 0, SRCAND);
        FillRect(var_4, &var_C, word_C0B4);
        BitBlt(var_E, 0, 0, 40, word_CA72, var_4, 0, 0, SRCPAINT);
        BitBlt(var_2, 0, 40, 40, word_CA72, var_E, 0, 0, SRCCOPY);
        DeleteDC(var_E);
        DeleteDC(var_4);
    } else {
        if (word_C0B4 != NULL) {
            DeleteObject(word_C0B4);
            word_C0B4 = NULL;
        }
        if (word_CA44 != NULL) {
            DeleteObject(word_CA44);
            word_CA44 = NULL;
        }
        if (word_C0B2 != NULL) {
            DeleteObject(word_C0B2);
            word_C0B2 = NULL;
        }
        if (word_C0B8 != NULL) {
            DeleteObject(word_C0B8);
            word_C0B8 = NULL;
        }
        DeleteDC(var_4);
    }
    ReleaseDC(arg_0, var_2);
    return;
loc_398B:
    ReleaseDC(arg_0, var_2);
}

/* Unused. */
void sub_399D(HWND arg_0, int arg_2, int arg_4, int arg_6, int arg_8)
{
    MoveWindow(arg_0, arg_2, arg_4, arg_6, arg_8, FALSE);
    MoveWindow(arg_0, 0, 0, 0, 0, TRUE);
}

/* Find if a window has a match in known instance list. */
BOOL sub_39D6(HWND arg_0)
{
    int var_2;
    if (word_CA40 == 0) {
        return FALSE;
    }
    for (var_2 = 0; var_2 < 8; var_2 += 1) {
        if (word_CA60[var_2] == arg_0 && word_CA60[var_2] != NULL) {
            return TRUE;
        }
    }
    return FALSE;
}

/* Find X-coordinate of possible collision with other instances. Return zero when no collision detected. */
int sub_3A36(int arg_0, int arg_2, int arg_4, int arg_6)
{
    int var_2;
    int var_4;
    int var_6;
    int var_8;
    int var_A;
    for (var_2 = 0; var_2 < 8; var_2 += 1) {
        if (word_CA60[var_2] != NULL) {
            var_4 = (short)GetWindowWord(word_CA60[var_2], 0);
            var_8 = (short)GetWindowWord(word_CA60[var_2], 2);
            var_6 = var_4 + 40;
            var_A = var_8 + 40;
            if (var_6 == 0) {
                continue;
            }
            if ((var_8 <= arg_4 && var_A > arg_4 || var_8 < arg_6 && var_A > arg_6) && var_6 > arg_0 && var_6 <= arg_2 && arg_2 > arg_0) {
                return var_6;
            }
            if ((var_8 <= arg_4 && var_A > arg_4 || var_8 < arg_6 && var_A > arg_6) && var_4 >= arg_2 && var_4 < arg_0 && arg_2 < arg_0) {
                return var_4;
            }
        }
    }
    return 0;
}

/* Populate known instance list by searching for visible windows with name match. */
void sub_3B4C(HWND arg_0)
{
    HWND var_2;
    UINT var_4;
    int var_6;
    int var_8;
    char var_48[64];
    for (var_6 = 0; var_6 < 8; var_6 += 1) {
        word_CA60[var_6] = NULL;
    }
    var_2 = GetDesktopWindow();
    var_4 = GW_CHILD;
    var_6 = 0;
    var_8 = 0;
    while ((var_2 = GetWindow(var_2, var_4)) != NULL && var_6 < 64) {
        var_4 = GW_HWNDNEXT;
        if (var_2 == arg_0) {
            continue;
        }
        if ((GetWindowLong(var_2, GWL_STYLE) & WS_VISIBLE) != 0) {
            GetWindowText(var_2, var_48, 16);
            if (lstrcmp(var_48, "Screen Mate") == 0) {
                word_CA60[var_8] = var_2;
                var_8 += 1;
                if (var_8 > 8) {
                    return;
                }
            }
            var_6 += 1;
        }
    }
    word_CA40 = var_8;
}

/* Populate known instance list by searching for visible windows with name match, then notify other instances of self creation. */
BOOL sub_3C20(HWND arg_0)
{
    HWND var_2;
    UINT var_4;
    int var_6;
    int var_8;
    char var_48[64];
    var_2 = GetDesktopWindow();
    var_4 = GW_CHILD;
    var_6 = 0;
    var_8 = 0;
    while ((var_2 = GetWindow(var_2, var_4)) != NULL && var_6 < 64) {
        var_4 = GW_HWNDNEXT;
        if (var_2 == arg_0) {
            continue;
        }
        if ((GetWindowLong(var_2, GWL_STYLE) & WS_VISIBLE) != 0) {
            GetWindowText(var_2, var_48, 16);
            if (lstrcmp(var_48, "Screen Mate") == 0) {
                word_CA60[var_8] = var_2;
                var_8 += 1;
                if (var_8 > 8) {
                    return FALSE;
                }
            }
            var_6 += 1;
        }
    }
    word_CA40 = var_8;
    word_CA48 = var_8;
    for (var_6 = 0; var_6 < word_CA40; var_6 += 1) {
        SendMessage(word_CA60[var_6], WM_USER, (WPARAM)1, (LPARAM)arg_0);
    }
    return TRUE;
}

/* Notify other instances of self destruction. */
void sub_3D12(HWND arg_0)
{
    int var_2;
    for (var_2 = 0; var_2 < 8; var_2 += 1) {
        if (word_CA60[var_2] != NULL) {
            SendMessage(word_CA60[var_2], WM_USER, (WPARAM)2, (LPARAM)arg_0);
        }
    }
}

/* Add window into known instance list. */
void sub_3D5F(HWND arg_0)
{
    int var_2;
    for (var_2 = 0; var_2 < 8; var_2 += 1) {
        if (word_CA60[var_2] == NULL) {
            word_CA40 += 1;
            word_CA60[var_2] = arg_0;
            break;
        }
    }
}

/* Remove window from known instance list. */
void sub_3DA7(HWND arg_0)
{
    int var_2;
    for (var_2 = 0; var_2 < 8; var_2 += 1) {
        if (word_CA60[var_2] == arg_0) {
            word_CA40 -= 1;
            word_CA60[var_2] = NULL;
            break;
        }
    }
}

/* Populate known visible window list. */
void sub_3DF0(void)
{
    HWND var_2;
    UINT var_4;
    int var_6;
    var_2 = GetDesktopWindow();
    var_4 = GW_CHILD;
    var_6 = 0;
    while ((var_2 = GetWindow(var_2, var_4)) != NULL && var_6 < 32) {
        var_4 = GW_HWNDNEXT;
        if (var_2 == word_C0B0) {
            continue;
        }
        if ((GetWindowLong(var_2, GWL_STYLE) & WS_VISIBLE) != 0) {
            GetWindowRect(var_2, &stru_C0BC[var_6].rect);
            stru_C0BC[var_6].window = var_2;
            var_6 += 1;
        }
    }
    word_CA74 = var_6;
}

/* Find X-coordinate of possible collision with which visible window. */
int sub_3E7C(HWND * arg_0, int arg_2, int arg_4, int arg_6, int arg_8)
{
    int var_2;
    int var_4;
    RECT var_C;
    for (var_2 = 0; var_2 < word_CA74; var_2 += 1) {
        if (arg_8 > arg_6) {
            if (stru_C0BC[var_2].rect.right >= arg_6 && stru_C0BC[var_2].rect.right < arg_8 && stru_C0BC[var_2].rect.top < arg_2 && stru_C0BC[var_2].rect.bottom > arg_4) {
                for (var_4 = 0; var_4 < var_2; var_4 += 1) {
                    if (stru_C0BC[var_4].rect.top <= arg_2 && stru_C0BC[var_4].rect.bottom >= arg_4 && stru_C0BC[var_4].rect.left <= arg_6 && stru_C0BC[var_4].rect.right >= arg_8) {
                        break;
                    }
                }
                if (var_4 == var_2) {
                    if (IsWindow(stru_C0BC[var_2].window)) {
                        GetWindowRect(stru_C0BC[var_2].window, &var_C);
                        if (stru_C0BC[var_2].rect.right == var_C.right) {
                            *arg_0 = stru_C0BC[var_2].window;
                            return stru_C0BC[var_2].rect.right;
                        }
                    }
                }
            }
        } else {
            if (stru_C0BC[var_2].rect.left <= arg_6 && stru_C0BC[var_2].rect.left > arg_8 && stru_C0BC[var_2].rect.top < arg_2 && stru_C0BC[var_2].rect.bottom > arg_4) {
                for (var_4 = 0; var_4 < var_2; var_4 += 1) {
                    if (stru_C0BC[var_4].rect.top <= arg_2 && stru_C0BC[var_4].rect.bottom >= arg_4 && stru_C0BC[var_4].rect.left <= arg_6 && stru_C0BC[var_4].rect.right >= arg_8) {
                        break;
                    }
                }
                if (var_4 == var_2) {
                    if (IsWindow(stru_C0BC[var_2].window)) {
                        GetWindowRect(stru_C0BC[var_2].window, &var_C);
                        if (stru_C0BC[var_2].rect.left == var_C.left) {
                            *arg_0 = stru_C0BC[var_2].window;
                            return stru_C0BC[var_2].rect.left;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* Find Y-coordinate of possible landing top edge of which visible window. */
int sub_408C(HWND * arg_0, int arg_2, int arg_4, int arg_6, int arg_8)
{
    int var_2;
    int var_4;
    for (var_2 = 0; var_2 < word_CA74; var_2 += 1) {
        if (stru_C0BC[var_2].rect.top <= arg_2 && stru_C0BC[var_2].rect.top > arg_4 && stru_C0BC[var_2].rect.left < arg_8 && stru_C0BC[var_2].rect.right > arg_6 && stru_C0BC[var_2].rect.top > 10) {
            for (var_4 = 0; var_4 < var_2; var_4 += 1) {
                if (stru_C0BC[var_4].rect.left <= arg_6 && stru_C0BC[var_4].rect.right >= arg_8 && stru_C0BC[var_4].rect.top <= arg_4 && stru_C0BC[var_4].rect.bottom >= arg_2) {
                    break;
                }
            }
            if (var_4 == var_2) {
                *arg_0 = stru_C0BC[var_2].window;
                return stru_C0BC[var_2].rect.top;
            }
        }
    }
    if (arg_2 >= word_CA52 && arg_4 <= word_CA52) {
        *arg_0 = NULL;
        return word_CA52;
    }
    return 0;
}

/* Get window top Y-coordinate if it is possible to land on the window. */
int sub_419E(HWND arg_0, int arg_2, int arg_4, int arg_6, int arg_8)
{
    RECT var_8;
    if (IsWindow(arg_0)) {
        GetWindowRect(arg_0, &var_8);
        if (var_8.top <= arg_2 && var_8.top > arg_4 && var_8.left < arg_8 && var_8.right > arg_6) {
            return var_8.top;
        }
    }
    if (arg_2 > word_CA52) {
        return -1;
    }
    return 0;
}

/* Play sound by resource ID and additional flags. */
void sub_4210(int arg_0, UINT arg_2, WORD arg_4)
{
    LPCSTR lpszSoundName;
    if (word_A82E != NULL) {
        sndPlaySound(NULL, SND_SYNC);
        GlobalUnlock(word_A82E);
        FreeResource(word_A82E);
        word_A82E = NULL;
    }
    word_A82E = LoadResource(word_CA58, FindResource(word_CA58, MAKEINTRESOURCE(arg_0), "WAVE"));
    lpszSoundName = LockResource(word_A82E);
    sndPlaySound(lpszSoundName, arg_2 | (SND_ASYNC | SND_MEMORY));
}

/* Stop playing sound. */
void sub_428E(void)
{
    sndPlaySound(NULL, SND_SYNC);
}

/* Play sound by name. */
void sub_42AA(LPCSTR lpszSoundName)
{
    sndPlaySound(lpszSoundName, SND_ASYNC);
}

/* Play sound by resource ID and additional flags (when option "Cry" enabled). */
void sub_42C8(int arg_0, UINT arg_2, WORD arg_4)
{
    if (word_CA5A != 0U) {
        sub_4210(arg_0, arg_2, arg_4);
    }
}

/* Generate sprites from loaded resource images. */
BOOL sub_42F3(HDC arg_0)
{
    int var_2;
    int var_4;
    for (var_2 = 0; var_2 < 16; var_2 += 1) {
        if (stru_9EE2[var_2].resource == 0) {
            break;
        }
        if (!sub_2B30(arg_0, &stru_9EE2[var_2].info, stru_9EE2[var_2].resource, -1)) {
            return FALSE;
        }
        if (!sub_2B30(arg_0, &stru_9FE2[var_2].info, stru_9EE2[var_2].resource, -3)) {
            return FALSE;
        }
        for (var_4 = 0; var_4 < 16; var_4 += 1) {
            stru_A8A2[var_2 * 16 + var_4].bitmaps[0] = stru_9EE2[var_2].info.bitmaps[0];
            stru_A8A2[var_2 * 16 + var_4].bitmaps[1] = stru_9EE2[var_2].info.bitmaps[1];
            stru_A8A2[var_2 * 16 + var_4].width = 40;
            stru_A8A2[var_2 * 16 + var_4].height = 40;
            stru_A8A2[var_2 * 16 + var_4].x = var_4 * 40;
            stru_A8A2[var_2 * 16 + var_4].y = 0;
            stru_A8A2[var_2 * 16 + var_4 + 256].bitmaps[0] = stru_9FE2[var_2].info.bitmaps[0];
            stru_A8A2[var_2 * 16 + var_4 + 256].bitmaps[1] = stru_9FE2[var_2].info.bitmaps[1];
            stru_A8A2[var_2 * 16 + var_4 + 256].width = 40;
            stru_A8A2[var_2 * 16 + var_4 + 256].height = 40;
            stru_A8A2[var_2 * 16 + var_4 + 256].x = (15 - var_4) * 40;
            stru_A8A2[var_2 * 16 + var_4 + 256].y = 0;
        }
    }
    return TRUE;
}

/* Release resource images. */
void sub_44ED(void)
{
    int var_2;
    for (var_2 = 0; var_2 < 16; var_2 += 1) {
        if (stru_9EE2[var_2].resource == 0) {
            break;
        }
        sub_2EEC(&stru_9EE2[var_2].info);
        if (stru_9EE2[var_2].flags == 1) {
            sub_2EEC(&stru_9FE2[var_2].info);
        }
    }
}

/* Turn around when approaching screen border or otherwise with 1/20 probability.  */
void sub_4559(void)
{
    if (word_A2AA > 0 && word_A800 < 0) {
        word_A8A0 = 24;
    }
    if (word_A2AA < 0 && word_CA50 - stru_A8A2[word_A804].width < word_A800) {
        word_A8A0 = 24;
    }
    if (word_A2AA > 0 && word_CA50 - stru_A8A2[word_A804].width > word_A800 && rand() % 20 == 0) {
        word_A8A0 = 24;
    }
    if (word_A2AA < 0 && word_A800 > 0 && rand() % 20 == 0) {
        word_A8A0 = 24;
    }
}

/* Flag-controlled collision and turn around. */
void sub_4614(BOOL arg_0)
{
    if (word_A7FC == 0) {
        if (word_A2AA > 0 && word_A800 < 0) {
            word_A8A0 = 30;
        }
        if (word_A2AA < 0 && word_CA50 - stru_A8A2[word_A804].width < word_A800) {
            word_A8A0 = 30;
        }
    }
    if (arg_0) {
        if (word_A2AA > 0 && word_CA50 - 80 > word_A800 && rand() % 20 == 0) {
            word_A8A0 = 24;
        }
        if (word_A2AA < 0 && word_A800 > 40 && rand() % 20 == 0) {
            word_A8A0 = 24;
        }
    }
}

/* Switch to standing sprite after certain frames. */
void sub_46D2(void)
{
    if (word_A826-- <= 0) {
        word_A8A0 = 42;
    }
}

/* Process chime. */
void sub_46F7(void)
{
    struct tm * var_2;
    time_t var_6;
    DWORD var_A;
    int var_C;
    if (word_A832 != 0) {
        var_A = GetTickCount();
        if (dword_A834 + 1000 < var_A) {
            dword_A834 = var_A;
            word_A832 -= 1;
            if (word_A832 != 0) {
                sub_4210(108, 0U, 0);
            } else if (word_CA76 != 0) {
                word_A8A0 = 113;
            } else {
                word_A8A0 = 1;
            }
        }
    } else {
        if (word_A838++ < 10) {
            return;
        }
        word_A838 = 0;
        time(&var_6);
        var_2 = localtime(&var_6);
        var_C = var_2->tm_hour % 12;
        if (var_C == 0) {
            var_C = 12;
        }
        if (var_2->tm_min == 0 && var_C != word_A830) {
            sub_2A96();
            dword_A834 = 0;
            word_A830 = var_C;
            word_A832 = word_A830 + 1;
            word_A8A0 = 81;
        }
    }
}

/* Update window position and sprite to be painted. */
void sub_4807(int arg_0, int arg_2, int arg_4)
{
    SetWindowWord(word_C0B0, 0, (short)word_A800);
    SetWindowWord(word_C0B0, 2, (short)word_A802);
    if (arg_4 >= 9 && arg_4 <= 14) {
        sub_31A8(arg_0, arg_2, arg_4);
    } else if (word_A2AA > 0) {
        sub_31A8(arg_0, arg_2, arg_4);
    } else {
        sub_31A8(arg_0, arg_2, arg_4 + 256);
    }
}

/* Update window position and sprite to be painted (sub). */
void sub_488C(int arg_0, int arg_2, int arg_4)
{
    if (arg_4 >= 9 && arg_4 <= 14) {
        sub_9350(arg_0, arg_2, arg_4);
    } else if (word_A2AC > 0) {
        sub_9350(arg_0, arg_2, arg_4);
    } else {
        sub_9350(arg_0, arg_2, arg_4 + 256);
    }
}

/* Return TRUE if the window handle is NULL or if the handle contains an existing window. */
BOOL sub_48F3(HWND arg_0)
{
    if (arg_0 == NULL) {
        return TRUE;
    } else {
        return IsWindow(arg_0);
    }
}

/* Get window rect. If the window handle is NULL, get a screen rect located right under the current screen. */
void sub_491D(HWND arg_0, LPRECT arg_2)
{
    if (arg_0 == NULL) {
        arg_2->left = 0;
        arg_2->right = word_CA50;
        arg_2->top = word_CA52;
        arg_2->bottom = word_CA52 * 2;
    } else {
        GetWindowRect(arg_0, arg_2);
    }
}

/* Process when out of screen view or at different positions on top of visible window. */
void sub_496F(int arg_0)
{
    RECT var_8;
    if (word_A7FC == 0) {
        return;
    }
    if (word_A81C != NULL) {
        if (!sub_48F3(word_A81C)) {
            if (arg_0 == 2) {
                word_A8A0 = 94;
            } else {
                word_A8A0 = 102;
            }
            return;
        }
        sub_491D(word_A81C, &var_8);
        if (var_8.top > stru_A81E.top || word_A800 + 40 < var_8.left || var_8.right < word_A800) {
            if (arg_0 == 2) {
                word_A8A0 = 94;
            } else {
                word_A8A0 = 102;
            }
            return;
        }
        if (var_8.top < stru_A81E.top) {
            word_A802 = var_8.top - stru_A8A2[word_A804].height;
            stru_A81E.top = var_8.top;
            stru_A81E.bottom = var_8.bottom;
            stru_A81E.left = var_8.left;
            stru_A81E.right = var_8.right;
            sub_4807(word_A800, word_A802, word_A804);
            return;
        }
        if (arg_0 == 1) {
            if (word_A800 + 8 < var_8.left && word_A2AA > 0) {
                word_A8A0 = 105;
                word_A800 = var_8.left - 10;
                return;
            }
            if (word_A800 + 32 >= var_8.right && word_A2AA < 0) {
                word_A8A0 = 105;
                word_A800 = var_8.right - 30;
                return;
            }
            if (rand() % 20 - 1 == 0 && word_CA52 - word_A802 > 100) {
                word_A8A0 = 104;
                return;
            }
        }
        if (arg_0 == 2) {
            if (word_A800 + 32 < var_8.left || word_A800 + 8 > var_8.right) {
                word_A8A0 = 94;
                return;
            }
        }
    }
    if (stru_A8A2[word_A804].width + word_A800 < 0 || word_A800 > word_CA50) {
        word_A8A0 = 0;
        return;
    }
}

/* Process when climbing up side of a window. */
void sub_4B3B(void)
{
    RECT var_8;
    if (word_A7FC == 0) {
        return;
    }
    if (word_A81C != NULL) {
        if (!sub_48F3(word_A81C)) {
            word_A8A0 = 102;
            return;
        }
        sub_491D(word_A81C, &var_8);
        if (var_8.right < stru_A81E.right && word_A2AA > 0 || var_8.left > stru_A81E.left && word_A2AA < 0) {
            word_A8A0 = 102;
            return;
        }
        if (var_8.right > stru_A81E.right && word_A2AA > 0 || var_8.left < stru_A81E.left && word_A2AA < 0) {
            if (word_A2AA > 0) {
                word_A800 = var_8.right + 10;
            } else {
                word_A800 = var_8.left - 50;
            }
            sub_4807(word_A800, word_A802, word_A804);
            word_A8A0 = 102;
            return;
        }
    }
}

/* Detect collision with other instances, action controlled by a flag. */
void sub_4C21(int arg_0, int arg_2, int arg_4)
{
    if (arg_2 < arg_0) {
        arg_0 += 40;
        arg_2 = arg_0 - 80;
    } else {
        arg_2 = arg_0 + 80;
    }
    if (sub_3A36(arg_0, arg_2, word_A802, word_A802 + 40) != 0) {
        if (arg_4 == 1) {
            word_A8A0 = 24;
        }
        if (arg_4 == 2) {
            word_A8A0 = 30;
        }
    }
}

/* Detect collision with other instances and find X-coordinate. */
int sub_4C91(int arg_0, int arg_2)
{
    if (arg_2 < arg_0) {
        arg_0 += 40;
        arg_2 = arg_0 - 80;
    } else {
        arg_2 = arg_0 + 80;
    }
    return sub_3A36(arg_0, arg_2, word_A802, word_A802 + 40);
}

/* Reinitialize state. */
void sub_4CE1(void)
{
    word_A8A0 = 0;
}

/* Process state change on each timer expiration. */
void sub_4CF8(void)
{
    int var_2;
    int var_4;
    HWND var_6;
    HWND var_8;
    RECT var_10;
    POINT var_14;
    if (word_A84A++ > 100) {
        sub_3B4C(word_C0B0);
        word_A84A = 0;
    }
    if (word_C0AC != 0) {
        sub_46F7();
    }
loc_4D33:
    switch (word_A8A0) {
    case 0:
        word_A7FC = 0;
        srand((unsigned int)GetTickCount());
        word_A800 = -80;
        word_A802 = -80;
        word_A8A0 = 1;
    case 1:
        word_A844 = 0;
        if (word_CA42 != 0U) {
            word_A8A0 = 2;
            goto loc_4D33;
        }
        word_CA72 = 0;
        sub_2A96();
        if (word_CA54 != 0) {
            word_A8A0 = word_CA54;
            word_CA54 = 0;
            break;
        }
        if (rand() % 20 == 5 && word_A7FC == 0) {
            word_A8A0 = 85;
            break;
        }
        if (rand() % 40 == 5 && word_A7FC == 0 && word_CA3C == 0) {
            word_A8A0 = 4;
            break;
        }
        word_A8A0 = word_A15A[rand() % 80];
        if (word_A800 > word_CA50 || word_A800 < -40 || word_A802 < -40 || word_A802 > word_CA52) {
            if ((rand() & 1) == 0) {
                word_A2AA = 1;
                word_A800 = word_CA50 + word_CA4C;
                word_A802 = rand() % (word_CA52 - 64) + word_CA4E;
            } else {
                word_A2AA = -1;
                word_A800 = -40;
                word_A802 = rand() % (word_CA52 - 64) + word_CA4E;
            }
            word_A8A0 = 11;
        }
        break;
    case 2:
        word_A7FC = 1;
        word_CA72 = 0;
        sub_2A96();
        if (word_CA54 != 0) {
            word_A8A0 = word_CA54;
            word_CA54 = 0;
            break;
        }
        word_A8A0 = word_A1FA[rand() % 80];
        if (word_A800 > word_CA50 || word_A800 < -40 || word_A802 < -40 || word_A802 > word_CA52) {
            if (rand() % 10 == 0 && word_CA3C == 0) {
                word_A8A0 = 6;
                break;
            }
            word_A81C = GetActiveWindow();
            if (word_A81C == word_C0B0 || word_A81C == word_CA60[8] || word_A81C == NULL || sub_39D6(word_A81C)) {
                word_A8A0 = 3;
                goto loc_4D33;
            }
            sub_491D(word_A81C, &stru_A81E);
            if (stru_A81E.top < 10) {
                word_A8A0 = 3;
                goto loc_4D33;
            }
            word_A800 = (rand() % stru_A81E.right - stru_A81E.left) / 3 + (stru_A81E.right - stru_A81E.left) / 2 + stru_A81E.left - 20;
            word_A802 = -40;
            word_A840 = 0;
            word_A806 = 0;
            word_A808 = 0;
            word_A842 = rand() % 2;
            word_A8A0 = 92;
            if (rand() % 3 == 0) {
                word_A8A0 = 3;
                goto loc_4D33;
            }
        }
        break;
    case 3:
        word_A7FC = 1;
        word_A800 = rand() % (word_CA50 - 40);
        word_A802 = -(rand() % 20 - (-40));
        word_A840 = 0;
        word_A806 = 0;
        word_A808 = 0;
        word_A842 = rand() % 2;
        if (rand() % 3 == 0) {
            sub_2ABF(word_C0B0);
        }
        word_A8A0 = 97;
        break;
    case 153:
        break;
    case 154:
        break;
    case 4:
        if (word_CA50 / 2 - 20 > word_A800) {
            word_A2AA = 1;
        } else {
            word_A2AA = -1;
        }
        word_A804 = 4;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 5;
        break;
    case 5:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A800 < -40 || word_A800 > word_CA50) {
            word_A8A0 = 6;
        }
        break;
    case 6:
        word_A8A0 = word_A29A[rand() % 8];
        break;
    case 7:
        word_A7FE = 0;
        if ((rand() & 1) == 0) {
            word_A7FE = 1;
        }
        if (word_A7FE != 0) {
            sub_3DF0();
        }
        word_A804 = 4;
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 = rand() % 10 + 10;
        word_A8A0 = 8;
        break;
    case 8:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A7FE != 0) {
            if (word_A2AA > 0) {
                var_2 = sub_3E7C(&var_6, word_A802, word_A802 + 40, -(word_A2AA * 16 - word_A800), word_A800);
            } else {
                var_2 = sub_3E7C(&var_6, word_A802, word_A802 + 40, -(word_A2AA * 16 - word_A800) + 40, word_A800 + 40);
            }
            if (var_2 != 0) {
                if (word_A2AA > 0) {
                    word_A800 = var_2;
                } else {
                    word_A800 = var_2 - 40;
                }
                sub_4807(word_A800, word_A802, word_A804);
                word_A8A0 = 30;
                break;
            }
        }
        if (word_A82C == 0) {
            word_A800 -= word_A2AA * 16;
        }
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (rand() % 50 == 0 && word_A7FC != 0) {
            word_A8A0 = 9;
        }
        sub_4614(TRUE);
        sub_46D2();
        sub_496F(2);
        sub_4C21(-(word_A2AA * 16 - word_A800), word_A2AA * 16 + word_A800, 2);
        break;
    case 9:
        word_A806 = -11;
        word_A808 = -(word_A2AA * 8);
        word_A80C = word_A802;
        word_A8A0 = 10;
    case 10:
        word_A800 += word_A808;
        word_A802 += word_A806;
        word_A806 += 2;
        if (word_A806 >= -1 && word_A806 <= 1) {
            word_A804 = 23;
        } else if (word_A806 < -1) {
            word_A804 = 30;
        } else {
            word_A804 = 24;
        }
        if (word_A80C <= word_A802) {
            word_A802 = word_A80C;
            word_A8A0 = 7;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_4614(FALSE);
        sub_4C21(word_A808 + word_A800, word_A800 - word_A808, 2);
        if (word_A8A0 == 30 && word_A80C != word_A802) {
            word_A844 = word_A802 - word_A80C;
        }
        break;
    case 11:
        word_A7FE = 0;
        if ((word_A7FC & !(rand() & 1)) != 0) {
            word_A7FE = 1;
        }
        if (word_A7FE != 0) {
            sub_3DF0();
        }
        word_A826 = rand() % 10 + 10;
        word_A804 = 2;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 12;
        break;
    case 12:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A7FE != 0) {
            if (word_A2AA > 0) {
                var_2 = sub_3E7C(&var_6, word_A802, word_A802 + 40, -(word_A2AA * 6 - word_A800), word_A800);
            } else {
                var_2 = sub_3E7C(&var_6, word_A802, word_A802 + 40, -(word_A2AA * 6 - word_A800) + 40, word_A800 + 40);
            }
            if (var_2 != 0) {
                if (word_A2AA > 0) {
                    word_A800 = var_2;
                } else {
                    word_A800 = var_2 - 40;
                }
                word_A81C = var_6;
                sub_491D(word_A81C, &stru_A81E);
                word_A83E = stru_A81E.top - 12;
                word_A7FC = 1;
                word_A83C = word_A800;
                word_A804 = 30;
                sub_2B01(word_C0B0, word_A81C);
                word_A8A0 = 89;
                break;
            }
        }
        if (word_A82C == 0) {
            word_A800 -= word_A2AA * 6;
        }
        word_A804 = word_A804 == 2 ? 3 : 2;
        sub_4807(word_A800, word_A802, word_A804);
        sub_4559();
        sub_46D2();
        sub_496F(1);
        sub_4C21(-(word_A2AA * 6 - word_A800), word_A2AA * 6 + word_A800, 1);
        break;
    case 13:
        word_A82A = rand() % 2;
        word_A826 = rand() % 4 + 4;
        if (word_A82A != 0) {
            word_A804 = 88;
        } else {
            word_A804 = 86;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 14;
        break;
    case 14:
        if (word_A83A++ < 3) {
            break;
        }
        word_A83A = 0;
        if (word_A82C == 0) {
            word_A800 -= word_A2AA * 6;
        }
        if (word_A82A != 0) {
            word_A804 = word_A804 == 88 ? 89 : 88;
        } else {
            word_A804 = word_A804 == 86 ? 87 : 86;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_4559();
        sub_46D2();
        sub_496F(1);
        break;
    case 15:
        word_A82A = rand() % 2;
        word_A826 = rand() % 3 + 3;
        if (word_A82A != 0) {
            word_A804 = 54;
        } else {
            word_A804 = 52;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 16;
        break;
    case 16:
        if (word_A83A++ < 3) {
            break;
        }
        word_A83A = 0;
        if (word_A82A != 0) {
            word_A804 = word_A804 == 54 ? 55 : 54;
        } else {
            word_A804 = word_A804 == 52 ? 53 : 52;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_4559();
        sub_46D2();
        sub_496F(0);
        break;
    case 17:
        word_A804 = 6;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 18;
        break;
    case 18:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 += 1;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A804 == 8) {
            word_A804 = 0;
            word_A8A0 = 19;
            word_A826 = rand() % 8 + 8;
        }
        sub_496F(0);
        break;
    case 19:
        if (word_A83A++ < 4) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A804 == 0 ? 1 : 0;
        sub_4807(word_A800, word_A802, word_A804);
        sub_46D2();
        sub_496F(0);
        break;
    case 20:
        word_A82A = rand() % 3;
        if (word_A82A == 0) {
            word_A804 = 6;
        } else if (word_A82A == 1) {
            word_A804 = 31;
        } else {
            word_A804 = 73;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 21;
        word_A83A = rand() % 15 + rand() % 15;
        sub_496F(0);
        break;
    case 21:
        sub_496F(0);
        if (word_A83A-- > 0) {
            break;
        }
        word_A8A0 = 22;
        word_A826 = 0;
        break;
    case 22:
        word_A804 = word_A2B4[word_A82A][word_A826];
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 7) {
            word_A8A0 = 23;
            word_A83A = rand() % 15 + rand() % 15;
        }
        sub_496F(0);
        break;
    case 23:
        sub_496F(0);
        if (word_A83A-- > 0) {
            break;
        }
        word_A8A0 = 1;
        break;
    case 24:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        if ((rand() & 1) != 0) {
            word_A82A = 0;
        } else {
            word_A82A = 1;
        }
        word_A8A0 = 25;
        word_A826 = 0;
        break;
    case 25:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A82A != 0) {
            if (word_A2AA > 0) {
                word_A804 = word_A826 + 9;
            } else {
                word_A804 = 11 - word_A826;
            }
        } else {
            if (word_A2AA > 0) {
                word_A804 = word_A826 + 12;
            } else {
                word_A804 = 14 - word_A826;
            }
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 2) {
            word_A2AA = -word_A2AA;
            word_A8A0 = 26;
        }
        sub_496F(0);
        break;
    case 26:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 1;
        sub_496F(0);
        break;
    case 27:
        word_A806 = -10;
        word_A808 = word_A2AA * 8;
        word_A80C = word_A802;
        word_A848 = 0;
        word_A8A0 = 28;
    case 28:
        word_A800 += word_A808;
        word_A802 += word_A806;
        word_A806 += 2;
        word_A804 = word_A324[word_A848];
        word_A848 += 1;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A804 == 64) {
            word_A842 = 3;
            word_A8A0 = 99;
            break;
        }
        break;
    case 29:
        word_A83A = 0;
        word_A826 = 0;
        word_A82A = 0;
        if ((rand() & 7) == 0) {
            word_A82A = 1;
        }
        if (rand() % 5 == 0) {
            word_A82A = 2;
        }
        word_A8A0 = 32;
        if (word_A82A != 0) {
            word_A8A0 = 34;
        }
        goto loc_4D33;
    case 30:
        if (word_A7FC != 0) {
            word_A8A0 = 27;
            goto loc_4D33;
        } else {
            word_A8A0 = 24;
            goto loc_4D33;
        }
        word_A83A = 0;
        word_A826 = 0;
        word_A82A = 0;
        if ((rand() & 7) == 0) {
            word_A82A = 1;
        }
        if (rand() % 5 == 0) {
            word_A82A = 2;
        }
        word_A8A0 = 31;
    case 31:
        sub_4C21(word_A2AA * 10 + word_A800, word_A800, 2);
        if (word_A8A0 == 30) {
            if (word_A826 != 0) {
                word_A844 -= word_A324[word_A826 + 9];
            }
            break;
        }
        word_A804 = word_A324[word_A826];
        sub_4807(word_A800, word_A802 - word_A324[word_A826 + 10], word_A804);
        word_A826 += 1;
        if (word_A82A != 0 && word_A804 == 66) {
            if (word_A844 != 0) {
                word_A802 -= word_A844;
                word_A800 += word_A2AA * 10;
                sub_4807(word_A800, word_A802, word_A804);
            }
            word_A846 = 3;
            word_A8A0 = 34;
            break;
        }
        if (word_A826 > 8) {
            word_A8A0 = 32;
            break;
        }
        word_A800 += word_A2AA * 10;
        break;
    case 32:
        sub_496F(0);
        if (word_A83A++ < 8) {
            break;
        }
        word_A83A = 0;
        word_A2AA = -word_A2AA;
        word_A804 = 93;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 33;
        break;
    case 33:
        sub_496F(0);
        if (word_A83A++ < 15) {
            break;
        }
        word_A83A = 0;
        word_A8A0 = 1;
        break;
    case 34:
        word_A800 += word_A2AA * 8;
        if (word_A804 == 70) {
            word_A804 = 63;
        } else {
            word_A804 += 1;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A82A == 2 && word_A804 == 70) {
            word_A8A0 = 69;
            break;
        }
        if (word_A800 > word_CA50 || word_A800 < -40) {
            word_A8A0 = 1;
        }
        sub_4C21(word_A2AA * 8 + word_A800, -(word_A2AA * 8 - word_A800), 2);
        if (word_A8A0 == 30) {
            if (word_A846-- > 0) {
                word_A2AA = -word_A2AA;
                word_A8A0 = 34;
            } else {
                word_A8A0 = 34;
            }
        }
        sub_496F(2);
        break;
    case 35:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 37;
        word_A826 = 0;
        break;
    case 36:
        break;
    case 37:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A2AA > 0) {
            word_A804 = word_A826 + 12;
        } else {
            word_A804 = 14 - word_A826;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 1) {
            word_A804 = 103;
            word_A8A0 = 38;
        }
        sub_496F(0);
        break;
    case 38:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        sub_4807(word_A800, word_A802, word_A804);
        word_A804 += 1;
        if (word_A804 > 104) {
            word_A826 = 0;
            word_A8A0 = 39;
            break;
        }
        sub_496F(0);
        break;
    case 39:
        if (word_A826 == 0) {
            if (word_A83A++ < 10) {
                break;
            }
            word_A83A = 0;
        } else {
            if (word_A83A++ < 1) {
                break;
            }
            word_A83A = 0;
        }
        if (word_A826 <= 8 || word_A826 >= 12 && word_A826 <= 12) {
            word_A804 = word_A804 == 105 ? 106 : 105;
        } else {
            word_A804 = 104;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ > 15) {
            word_A8A0 = 40;
            word_A804 = 104;
        }
        sub_496F(0);
        break;
    case 40:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        sub_4807(word_A800, word_A802, word_A804);
        if (--word_A804 < 103) {
            word_A826 = 0;
            word_A8A0 = 41;
            break;
        }
        sub_496F(0);
        break;
    case 41:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A2AA > 0) {
            word_A804 = 13 - word_A826;
        } else {
            word_A804 = word_A826 + 13;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 1) {
            word_A8A0 = 42;
        }
        sub_496F(0);
        break;
    case 42:
        sub_496F(0);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 1;
        word_A826 = 0;
        break;
    case 43:
        sub_42C8(109, 0U, 0);
        word_A826 = 0;
        word_A8A0 = 44;
    case 44:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A34C[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 45:
        sub_42C8(108, 0U, 0);
        word_A826 = 0;
        word_A8A0 = 46;
    case 46:
        if (word_A83A++ < 0) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A362[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 47:
        word_A826 = 0;
        word_A8A0 = 48;
    case 48:
        if (word_A83A++ < 0) {
            break;
        }
        word_A83A = 0;
        if (word_A826 == 2) {
            sub_42C8(110, 0U, 0);
        }
        word_A804 = word_A372[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 49:
        word_A826 = 0;
        word_A8A0 = 50;
    case 50:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A38C[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 51:
        word_A826 = 0;
        word_A8A0 = 52;
    case 52:
        if (word_A83A++ < 0) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A804 == 56 ? 57 : 56;
        if (word_A826++ > 30) {
            word_A804 = 3;
            word_A8A0 = 1;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 53:
        word_A826 = 0;
        word_A8A0 = 54;
        sub_2A21();
        word_A2AC = word_A2AA;
        word_A810 = word_A802;
        word_A812 = 149;
        if (word_A2AA > 0) {
            word_A80E = word_A800 - 40;
        } else {
            word_A80E = word_A800 + 40;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        word_C0AE = 1;
        sub_2B01(word_CA60[8], word_C0B0);
        break;
    case 54:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A398[word_A826];
        word_A826 += 1;
        if (word_A804 == 2) {
            word_A800 -= word_A2AA * 8;
            sub_4807(word_A800, word_A802, word_A804);
            break;
        }
        if (word_A804 >= 149 && word_A804 <= 153) {
            word_A812 = word_A804;
            if (word_A812 == 153) {
                word_A812 = 173;
            }
            sub_488C(word_A80E, word_A810, word_A812);
            word_A804 = word_A398[word_A826];
            word_A826 += 1;
        }
        if (word_A804 == 0) {
            sub_2A96();
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 55:
        break;
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 6;
        word_A804 = 2;
        sub_4807(word_A800, word_A802, word_A804);
        sub_4559();
        sub_46D2();
        sub_496F(1);
        sub_4C21(-(word_A2AA * 6 - word_A800), word_A2AA * 6 + word_A800, 1);
        word_A8A0 = 54;
        break;
    case 56:
        word_A826 = 0;
        word_A8A0 = 57;
    case 57:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A398[word_A826];
        word_A826 += 1;
        if (word_A804 >= 149 && word_A804 <= 153) {
            word_A804 = word_A398[word_A826];
            word_A826 += 1;
        }
        if (word_A826 >= 16) {
            word_A8A0 = 42;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 58:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 59;
        word_A826 = 0;
        break;
    case 59:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A2AA > 0) {
            word_A804 = word_A826 + 9;
        } else {
            word_A804 = 11 - word_A826;
        }
        word_A826 += 1;
        if (word_A826 > 2) {
            word_A804 = 34;
            word_A83A = -10;
            word_A8A0 = 60;
            word_A826 = 0;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 60:
        if (word_A83A++ < 0) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A2B4[5][word_A826];
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 7) {
            word_A826 = 0;
            word_A8A0 = 61;
            word_A83A = -5;
        }
        sub_496F(0);
        break;
    case 61:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A2AA > 0) {
            word_A804 = 10 - word_A826;
        } else {
            word_A804 = word_A826 + 10;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 1) {
            word_A8A0 = 42;
        }
        sub_496F(0);
        break;
    case 64:
        break;
    case 65:
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 = 0;
        word_A8A0 = 66;
        break;
    case 66:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A826 == 0) {
            if (word_A2AA > 0) {
                word_A804 = 9;
            } else {
                word_A804 = 11;
            }
        } else {
            word_A804 = 10;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ > 0) {
            word_A8A0 = 67;
            word_A828 = (rand() % 4 + 4) * 8;
            word_A826 = 0;
            break;
        }
        sub_496F(0);
        break;
    case 67:
        if (--word_A826 < 0) {
            word_A826 = 79;
        }
        word_A800 -= word_A2AA * 8;
        word_A804 = word_A524[word_A826 % 8];
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A2AA > 0 && word_A800 < 0) {
            word_A8A0 = 30;
        }
        if (word_A2AA < 0 && word_CA50 - stru_A8A2[word_A804].width < word_A800) {
            word_A8A0 = 30;
        }
        if (--word_A828 <= 0) {
            word_A8A0 = 68;
            word_A826 = 0;
        }
        sub_496F(2);
        sub_4C21(-(word_A2AA * 8 - word_A800), word_A2AA * 8 + word_A800, 2);
        break;
    case 68:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A826 == 1) {
            if (word_A2AA > 0) {
                word_A804 = 9;
            } else {
                word_A804 = 11;
            }
        } else if (word_A826 == 0) {
            word_A804 = 10;
        } else {
            word_A804 = 3;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ > 1) {
            word_A8A0 = 1;
            break;
        }
        sub_496F(0);
        break;
    case 62:
        word_A8A0 = 63;
        word_A826 = 0;
        break;
    case 63:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A50C[word_A826];
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        sub_496F(0);
        break;
    case 75:
        word_A826 = rand() % 8 + 8;
        word_A828 = word_A826;
        word_A804 = 131;
        if (word_A2AA > 0) {
            word_A804 = 12;
        } else {
            word_A804 = 14;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 76;
        break;
    case 76:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 = 13;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 77;
        break;
    case 77:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A804 == 131 ? 132 : 131;
        word_A802 -= 8;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826-- <= 0) {
            word_A826 = word_A828;
            word_A8A0 = 78;
        }
        break;
    case 78:
        word_A804 = 133;
        word_A802 += 8;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826-- <= 0) {
            word_A8A0 = 79;
        }
        break;
    case 79:
        if (word_A83A++ < 10) {
            break;
        }
        word_A83A = 0;
        word_A8A0 = 80;
        word_A826 = 3;
        break;
    case 80:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A2AA > 0) {
            word_A804 = word_A43C[word_A826];
            word_A826 += 1;
        } else {
            word_A804 = word_A44C[word_A826];
            word_A826 += 1;
        }
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 69:
        word_A83A = 0;
        word_A826 = 0;
        word_A8A0 = 70;
    case 70:
        if (word_A2AA > 0) {
            word_A804 = word_A536[word_A826 % 8];
        } else {
            word_A804 = word_A536[(word_A826 + 4) % 8];
        }
        if (word_A804 == 2) {
            word_A804 = 3;
            if (word_A2AA > 0) {
                word_A2AA = -word_A2AA;
                sub_4807(word_A800, word_A802, word_A804);
                word_A2AA = -word_A2AA;
            } else {
                sub_4807(word_A800, word_A802, word_A804);
            }
        } else if (word_A804 == 3) {
            if (word_A2AA < 0) {
                word_A2AA = -word_A2AA;
                sub_4807(word_A800, word_A802, word_A804);
                word_A2AA = -word_A2AA;
            } else {
                sub_4807(word_A800, word_A802, word_A804);
            }
        } else {
            sub_4807(word_A800, word_A802, word_A804);
        }
        if (word_A826++ >= 16) {
            word_A804 = 70;
            sub_4807(word_A800, word_A802, word_A804);
            word_A8A0 = 71;
        }
        sub_496F(0);
        break;
    case 71:
        sub_496F(0);
        if (word_A83A++ < 14) {
            break;
        }
        word_A83A = 0;
        word_A804 = 96;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 72;
        break;
    case 72:
        sub_496F(0);
        if (word_A83A++ < 30) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 1;
        break;
    case 73:
        word_A826 = 0;
        word_A8A0 = 74;
    case 74:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A422[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        sub_496F(0);
        break;
    case 81:
        word_A804 = 4;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 82;
        break;
    case 82:
        word_A83A = 0;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 83:
        break;
    case 84:
        word_A8A0 = 0;
        break;
    case 85:
        word_A81C = GetActiveWindow();
        if (word_A81C == word_C0B0 || word_A81C == word_CA60[8] || word_A81C == NULL || sub_39D6(word_A81C)) {
            word_A8A0 = 1;
            break;
        }
        sub_491D(word_A81C, &stru_A81E);
        if (stru_A81E.top < 10) {
            word_A8A0 = 1;
            break;
        }
        if (word_A2AA > 0 && stru_A81E.right < word_A800 && stru_A81E.top < word_A802 && word_A802 + 40 < stru_A81E.bottom || word_A2AA < 0 && word_A800 + 40 < stru_A81E.left && stru_A81E.top < word_A802 && word_A802 + 40 < stru_A81E.bottom) {
            word_A8A0 = 87;
            break;
        }
        word_A83C = (rand() % stru_A81E.right - stru_A81E.left) / 3 + (stru_A81E.right - stru_A81E.left) / 2 + stru_A81E.left - 20;
        word_A83E = stru_A81E.top - 40;
        if (word_CA50 / 2 - 20 > word_A800) {
            word_A2AA = 1;
        } else {
            word_A2AA = -1;
        }
        word_A804 = 4;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 86;
        break;
    case 86:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A800 < -40 || word_A800 > word_CA50) {
            if (!sub_48F3(word_A81C)) {
                word_A8A0 = 1;
                break;
            }
            if (rand() % 3 == 0) {
                word_A8A0 = 3;
                goto loc_4D33;
            }
            word_A840 = 0;
            word_A8A0 = 92;
            word_A7FC = 1;
            word_A800 = word_A83C;
            word_A802 = -40;
            word_A806 = 0;
            word_A808 = 0;
            word_A842 = rand() % 2;
            if (word_A842 != 0) {
                word_A808 = -(word_A2AA * 3);
            }
            sub_2B01(word_C0B0, word_A81C);
        }
        break;
    case 87:
        sub_2B01(word_C0B0, word_A81C);
        if (word_A2AA > 0) {
            word_A83C = stru_A81E.right;
            word_A83E = stru_A81E.top;
        } else {
            word_A83C = stru_A81E.left - 40;
            word_A83E = stru_A81E.top;
        }
        word_A8A0 = 88;
    case 88:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        if (word_A83C >= word_A800 && word_A2AA > 0 || word_A83C <= word_A800 && word_A2AA < 0) {
            if (!sub_48F3(word_A81C)) {
                word_A8A0 = 1;
                break;
            }
            sub_491D(word_A81C, &var_10);
            if (var_10.left == stru_A81E.left && var_10.right == stru_A81E.right && var_10.top < word_A802 && word_A802 + 40 < var_10.bottom) {
                word_A83E = var_10.top - 12;
                word_A7FC = 1;
                word_A800 = word_A83C;
                word_A804 = 30;
                word_A8A0 = 89;
                break;
            } else {
                word_A8A0 = 1;
                break;
            }
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 89:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        sub_4807(word_A800, word_A802, word_A804);
        word_A802 -= 6;
        word_A804 = word_A804 == 15 ? 16 : 15;
        if (word_A83E >= word_A802) {
            word_A8A0 = 90;
            break;
        }
        sub_4B3B();
        break;
    case 90:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 8;
        word_A802 = word_A83E - 20;
        word_A804 = 76;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 91;
        break;
    case 91:
        if (word_A83A++ < 2) {
            break;
        }
        word_A83A = 0;
        word_A800 += word_A2AA * -24;
        word_A802 -= 8;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 11;
        break;
    case 92:
        word_A806 += 4;
        word_A80C = word_A802;
        word_A800 += word_A808;
        word_A802 += word_A806;
        if ((var_4 = sub_419E(word_A81C, stru_A8A2[word_A804].height + word_A802, stru_A8A2[word_A804].height + word_A80C, word_A800, stru_A8A2[word_A804].width + word_A800)) != 0) {
            if (var_4 == -1) {
                sub_4807(word_A800, word_A802, word_A804);
                word_A8A0 = 0;
                break;
            }
            word_A802 = var_4 - stru_A8A2[word_A804].height;
            if (word_A806 < 64 && word_A840 == 0 || word_A806 < 8) {
                SetWindowPos(word_C0B0, word_A81C, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
                word_A840 = 0;
                word_A826 = 0;
                word_A8A0 = 93;
                if (word_A806 < 36) {
                    word_A804 = 49;
                    word_A83A = -4;
                } else {
                    if ((rand() & 3) == 0) {
                        word_A804 = 48;
                    } else {
                        word_A804 = 42;
                    }
                    word_A83A = -12;
                }
                sub_4807(word_A800, word_A802, word_A804);
                break;
            } else {
                word_A806 = word_A806 * 2 / -3;
                word_A840 = 1;
            }
        }
        if (word_A842 != 0) {
            word_A804 = word_A804 == 4 ? 5 : 4;
        } else {
            word_A804 = 42;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 93:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A842 != 0) {
            word_A8A0 = 11;
            word_A804 = 2;
            break;
        }
        if (word_A826 == 0) {
            word_A804 = 13;
        } else if (word_A826 == 1) {
            if (word_A2AA > 0) {
                word_A804 = 12;
            } else {
                word_A804 = 14;
            }
        } else if (word_A826 == 2) {
            word_A804 = 3;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ >= 2) {
            word_A8A0 = 11;
        }
        break;
    case 94:
        word_A7FC = 1;
        word_A806 = 0;
        word_A808 = -(word_A2AA * 8);
        word_A842 = 1;
        word_A8A0 = 99;
        goto loc_4D33;
    case 95:
        word_A7FC = 1;
        word_A806 = 0;
        word_A808 = -(word_A2AA * 3);
        word_A842 = 1;
        word_A8A0 = 99;
        goto loc_4D33;
    case 96:
        word_A7FC = 1;
        word_A806 = 0;
        word_A808 = 0;
        word_A842 = 0;
        word_A8A0 = 99;
        goto loc_4D33;
    case 97:
        word_A7FC = 1;
        word_A806 = 0;
        word_A808 = 0;
        word_A842 = 1;
        word_A8A0 = 99;
        goto loc_4D33;
    case 98:
        word_A7FC = 1;
        word_A806 = 0;
        word_A808 = 0;
        word_A842 = 2;
        word_A8A0 = 99;
        goto loc_4D33;
    case 99:
        sub_3DF0();
        word_A806 += 4;
        word_A80C = word_A802;
        word_A800 += word_A808;
        word_A802 += word_A806;
        if (word_A80C > word_CA52) {
            sub_4807(word_A800, word_A802, word_A804);
            word_A8A0 = 0;
            break;
        }
        if ((var_4 = sub_408C(&word_A81C, stru_A8A2[word_A804].height + word_A802, stru_A8A2[word_A804].height + word_A80C, word_A800, stru_A8A2[word_A804].width + word_A800)) != 0) {
            if (!sub_48F3(word_A81C)) {
                sub_4807(word_A800, word_A802, word_A804);
                word_A8A0 = 0;
                break;
            }
            sub_491D(word_A81C, &stru_A81E);
            word_A802 = var_4 - stru_A8A2[word_A804].height;
            if (word_A842 == 3) {
                word_A804 = 66;
                sub_4807(word_A800, word_A802, word_A804);
                word_A8A0 = 29;
                break;
            }
            if (word_A806 < 64 && word_A840 == 0 || word_A806 < 8) {
                if (word_A81C != NULL) {
                    SetWindowPos(word_C0B0, word_A81C, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
                }
                word_A840 = 0;
                word_A826 = 0;
                word_A8A0 = 100;
                if (word_A806 < 36) {
                    word_A804 = 49;
                    word_A83A = -4;
                } else {
                    if ((rand() & 3) == 0) {
                        word_A804 = 48;
                    } else {
                        word_A804 = 42;
                    }
                    word_A83A = -10;
                }
                if (word_A842 == 2) {
                    if (word_A806 < 36) {
                        word_A804 = 41;
                    } else {
                        word_A804 = 45;
                    }
                }
                sub_4807(word_A800, word_A802, word_A804);
                break;
            } else {
                if ((rand() & 7) == 0 && word_A840 == 0) {
                    word_A840 = 0;
                    word_A826 = 0;
                    word_A8A0 = 100;
                    word_A804 = 48;
                    word_A83A = -12;
                    if (word_A842 == 2) {
                        word_A804 = 45;
                    }
                    sub_4807(word_A800, word_A802, word_A804);
                    break;
                }
                word_A806 = word_A806 * 2 / -3;
                word_A840 = 1;
            }
        }
        if (word_A842 == 2) {
            word_A804 = word_A804 == 40 ? 41 : 40;
        } else if (word_A842 == 1) {
            word_A804 = word_A804 == 4 ? 5 : 4;
        } else if (word_A842 == 0) {
            word_A804 = 42;
        } else {
            word_A804 = word_A324[word_A848];
            word_A848 += 1;
            if (word_A804 == 66) {
                word_A848 -= 1;
            }
        }
        if (word_A842 == 3 && sub_4C91(word_A800, word_A800 - word_A808) != 0) {
            word_A2AA = -word_A2AA;
            word_A8A0 = 30;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 100:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A842 == 1) {
            word_A8A0 = 11;
            word_A804 = 2;
            break;
        }
        if (word_A842 == 2) {
            word_A826 = 0;
            word_A8A0 = 101;
            break;
        }
        if (word_A826 == 0) {
            word_A804 = 13;
        } else if (word_A826 == 1) {
            if (word_A2AA > 0) {
                word_A804 = 12;
            } else {
                word_A804 = 14;
            }
        } else if (word_A826 == 2) {
            word_A804 = 3;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ >= 2) {
            word_A8A0 = 11;
        }
        break;
    case 101:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A826 == 0) {
            word_A804 = 31;
            word_A83A = -8;
        } else if (word_A826 == 2) {
            word_A804 = 3;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ >= 6) {
            word_A8A0 = 11;
        }
        break;
    case 102:
        sub_428E();
        word_A826 = 6;
        word_A804 = 3;
        word_A82A = 0;
        if (rand() % 3 == 0) {
            word_A82A = 1;
        }
        word_A8A0 = 103;
    case 103:
        if (word_A82A != 0) {
            word_A804 = word_A804 == 50 ? 51 : 50;
        } else {
            word_A804 = word_A804 == 4 ? 5 : 4;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826-- <= 0) {
            word_A8A0 = 97;
        }
        break;
    case 104:
        word_A842 = 0;
        word_A8A0 = 106;
        goto loc_4D33;
    case 105:
        word_A842 = 1;
        word_A8A0 = 106;
        goto loc_4D33;
    case 106:
        if (word_A842 == 0) {
            var_14.x = word_A800;
            var_14.y = word_A802 + 39;
            *(HWND *)&var_10 = WindowFromPoint(var_14);
            var_14.x = word_A800 + 39;
            var_8 = WindowFromPoint(var_14);
            if (*(HWND *)&var_10 == word_C0B0 && var_8 == word_C0B0) {
                sub_2ABF(word_C0B0);
            } else if (*(HWND *)&var_10 == word_C0B0) {
                sub_2B01(word_C0B0, var_8);
            } else {
                sub_2B01(word_C0B0, *(HWND *)&var_10);
            }
            word_A804 = 81;
        } else {
            word_A804 = 78;
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 107;
        word_A826 = 0;
        break;
    case 107:
        word_A804 = word_A2B4[4 - word_A842][word_A826];
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 7) {
            if (word_A842 != 0) {
                if ((rand() & 1) == 0) {
                    word_A8A0 = 111;
                } else {
                    word_A8A0 = 109;
                }
            } else {
                if ((rand() & 1) == 0) {
                    word_A8A0 = 111;
                } else {
                    word_A8A0 = 108;
                }
            }
        }
        break;
    case 108:
        if (word_A83A++ < 10) {
            break;
        }
        word_A83A = 0;
        word_A804 = 3;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 1;
        break;
    case 109:
        word_A808 = -(word_A2AA * 14);
        word_A804 = 23;
        word_A800 += word_A808;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 95;
        word_A826 = 0;
        break;
    case 110:
        word_A800 += word_A808;
        word_A808 += word_A2AA;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826++ > 3) {
            word_A8A0 = 95;
        }
        break;
    case 111:
        if (word_A842 != 0) {
            word_A800 += word_A2AA * -26;
            word_A802 += 35;
            word_A2AA = -word_A2AA;
        } else {
            word_A82A = rand() % 2;
            if (word_A82A != 0) {
                word_A802 += 36;
            } else {
                word_A802 += 20;
            }
        }
        word_A826 = 0;
        word_A8A0 = 112;
    case 112:
        if (word_A826 == 0) {
            if (word_A83A++ < 10) {
                break;
            }
            word_A83A = 0;
        } else {
            if (word_A83A++ < 1) {
                break;
            }
            word_A83A = 0;
        }
        if (word_A842 != 0) {
            word_A804 = word_A804 == 40 ? 41 : 40;
        } else {
            word_A804 = word_A314[word_A82A][word_A826 % 4];
        }
        sub_4807(word_A800, word_A802, word_A804);
        word_A826 += 1;
        if (word_A826 > 12) {
            if (word_A842 != 0) {
                word_A8A0 = 98;
            } else {
                word_A8A0 = 96;
            }
        }
        break;
    case 113:
        word_CA76 = 1;
        word_A804 = 6;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 114;
        break;
    case 114:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A804 += 1;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A804 == 8) {
            word_A804 = 0;
            word_A8A0 = 115;
        }
        sub_496F(0);
        break;
    case 115:
        sub_496F(0);
        if (word_A83A++ < 4) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A804 == 0 ? 1 : 0;
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 116:
        word_A800 = word_CA50;
        word_A802 = word_CA52 * 7 / 8;
        word_A804 = 4;
        word_A2AA = 1;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 117;
        break;
    case 117:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_CA50 / 2 - 20 >= word_A800) {
            word_A8A0 = 118;
        }
        break;
    case 118:
        sub_2A21();
        word_A2AC = -1;
        word_A80E = -40;
        word_A810 = word_CA52 / 8;
        word_A812 = 154;
        word_A826 = 0;
        word_A8A0 = 119;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 119:
        if (word_A826 != 0) {
            word_A804 = word_A2B4[2][word_A826];
            sub_4807(word_A800, word_A802, word_A804);
            word_A826 += 1;
            if (word_A826 > 7) {
                word_A826 = 0;
            }
        } else {
            word_A804 = 73;
            sub_4807(word_A800, word_A802, word_A804);
            if (rand() % 20 == 0) {
                word_A826 = 1;
            }
        }
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A80E -= word_A2AC * 16;
        word_A812 = word_A812 == 154 ? 155 : 154;
        sub_488C(word_A80E, word_A810, word_A812);
        if (word_A80E > word_A800) {
            word_A2AA = -1;
            sub_4807(word_A800, word_A802, word_A804);
        }
        if (word_A80E > word_CA50) {
            sub_2A96();
            word_A8A0 = 120;
        }
        break;
    case 120:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A800 > word_CA50) {
            word_A8A0 = 1;
        }
        break;
    case 121:
        word_A800 = word_CA50;
        word_A802 = word_CA52 * 7 / 8;
        word_A804 = 4;
        word_A2AA = 1;
        sub_2A21();
        word_A2AC = -1;
        word_A80E = -40;
        word_A810 = word_CA52 * 7 / 8;
        word_A812 = 154;
        sub_4807(word_A800, word_A802, word_A804);
        sub_488C(word_A80E, word_A810, word_A812);
        word_A8A0 = 122;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 122:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        word_A80E -= word_A2AC * 16;
        word_A812 = word_A812 == 154 ? 155 : 154;
        if (word_A800 - word_A80E <= 46) {
            word_A800 = word_CA50 / 2 + 3;
            word_A80E = word_CA50 / 2 - 43;
            word_A804 = 3;
            word_A812 = 157;
            sub_4807(word_A800, word_A802, word_A804);
            sub_488C(word_A80E, word_A810, word_A812);
            word_A826 = 0;
            word_A8A0 = 123;
        } else {
            sub_4807(word_A800, word_A802, word_A804);
            sub_488C(word_A80E, word_A810, word_A812);
        }
        break;
    case 123:
        if (word_A83A++ < 3) {
            break;
        }
        word_A83A = 0;
        word_A804 = word_A826 + 127;
        word_A826 += 1;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A826 >= 4) {
            word_A8A0 = 124;
        }
        break;
    case 124:
        if (word_A83A++ < 4) {
            break;
        }
        word_A83A = 0;
        word_CA46 += 1;
        if (word_CA46 > 8) {
            sub_2A96();
            word_A826 = 0;
            word_A8A0 = 125;
        }
        break;
    case 125:
        word_A804 = word_A45C[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A8A0 = 1;
            break;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 126:
        word_A800 = word_CA50;
        word_A802 = word_CA52 * 7 / 8;
        word_A804 = 4;
        word_A2AA = 1;
        sub_2A21();
        word_A2AC = 1;
        word_A80E = word_CA50 + 46;
        word_A810 = word_CA52 * 7 / 8;
        word_A812 = 154;
        sub_4807(word_A800, word_A802, word_A804);
        sub_488C(word_A80E, word_A810, word_A812);
        word_A8A0 = 127;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 127:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        word_A80E -= word_A2AC * 16;
        word_A812 = word_A812 == 154 ? 155 : 154;
        if (word_A80E < -40) {
            sub_2A96();
            word_A8A0 = 1;
        } else {
            sub_4807(word_A800, word_A802, word_A804);
            sub_488C(word_A80E, word_A810, word_A812);
        }
        break;
    case 128:
        word_A800 = word_CA50;
        word_A802 = word_CA52 * 7 / 8;
        word_A804 = 4;
        word_A2AA = 1;
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 129;
        break;
    case 129:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_CA50 / 2 - 20 >= word_A800) {
            word_A8A0 = 130;
        }
        break;
    case 130:
        sub_2A21();
        word_A2AC = -1;
        word_A80E = -40;
        word_A810 = word_CA52 / 8;
        word_A812 = 158;
        word_A826 = 0;
        word_A8A0 = 131;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 131:
        if (word_A826 != 0) {
            word_A804 = word_A2B4[2][word_A826];
            sub_4807(word_A800, word_A802, word_A804);
            word_A826 += 1;
            if (word_A826 > 7) {
                word_A826 = 0;
            }
        } else {
            word_A804 = 73;
            sub_4807(word_A800, word_A802, word_A804);
            if (rand() % 20 == 0) {
                word_A826 = 1;
            }
        }
        word_A80E -= word_A2AC * 16;
        if (word_A812 == 161) {
            word_A812 = 158;
        } else {
            word_A812 += 1;
        }
        if (word_A80E > word_A800) {
            word_A80E = word_A800;
            word_A812 = 162;
            word_A8A0 = 132;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 132:
        word_A804 = 73;
        sub_4807(word_A800, word_A802, word_A804);
        word_CA5C += 40;
        if (word_A802 - word_A810 - 40 <= word_CA5C) {
            word_CA5C = word_A802 - word_A810 - 40;
            word_CA5C -= 20;
            word_A8A0 = 133;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A812 == 165) {
            word_A812 = 162;
        } else {
            word_A812 += 1;
        }
        break;
    case 133:
        word_CA5C -= 20;
        if (word_CA5C <= 0) {
            word_CA5C = 0;
            word_A802 = word_A810 + 40;
            word_A8A0 = 134;
            word_A804 = word_A804 == 4 ? 5 : 4;
            sub_4807(word_A800, word_A802, word_A804);
            word_A812 = 158;
            sub_488C(word_A80E, word_A810, word_A812);
            break;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        word_A804 = word_A804 == 4 ? 5 : 4;
        word_A802 -= 20;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A812 == 165) {
            word_A812 = 162;
        } else {
            word_A812 += 1;
        }
        break;
    case 134:
        word_A800 = -80;
        sub_4807(word_A800, word_A802, word_A804);
        word_A80E -= word_A2AC * 16;
        if (word_A812 == 161) {
            word_A812 = 158;
        } else {
            word_A812 += 1;
        }
        if (word_A80E > word_CA50) {
            sub_2A96();
            sub_428E();
            word_A8A0 = 1;
            break;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 135:
        word_A810 = word_CA52 * 7 / 8;
        word_A2AA = -1;
        word_A800 = -40;
        word_A802 = word_CA52 / 8;
        word_A804 = 158;
        word_A826 = 0;
        word_A8A0 = 136;
        break;
    case 136:
        word_A800 -= word_A2AA * 16;
        if (word_A804 == 161) {
            word_A804 = 158;
        } else {
            word_A804 += 1;
        }
        if (word_CA50 / 2 - 20 < word_A800) {
            word_A800 = word_CA50 / 2 - 20;
            word_A804 = 162;
            word_A8A0 = 137;
        }
        sub_4807(word_A800, word_A802, word_A804);
        break;
    case 137:
        word_CA72 += 40;
        if (word_A810 - word_A802 - 40 <= word_CA72) {
            word_CA72 = word_A810 - word_A802 - 40;
            word_A8A0 = 138;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A804 == 165) {
            word_A804 = 162;
        } else {
            word_A804 += 1;
        }
        break;
    case 138:
        if (word_A83A++ < 4) {
            break;
        }
        word_A83A = 0;
        sub_2A21();
        word_A80E = word_A800;
        word_A812 = 167;
        sub_488C(word_A80E, word_A810, word_A812);
        sub_4807(word_A800, word_A802, word_A804);
        word_A8A0 = 139;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 139:
        if (word_CA72 != 0) {
            word_CA72 -= 40;
            if (word_CA72 <= 0) {
                word_A804 = 158;
                word_CA72 = 0;
            }
            if (word_A804 == 165) {
                word_A804 = 162;
            } else {
                word_A804 += 1;
            }
        } else {
            word_A800 -= word_A2AA * 16;
            if (word_A804 == 161) {
                word_A804 = 158;
            } else {
                word_A804 += 1;
            }
        }
        if (word_A800 > word_CA50) {
            word_A8A0 = 140;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A812 = word_A812 == 167 ? 168 : 167;
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 140:
        word_A812 = 166;
        sub_488C(word_A80E, word_A810, word_A812);
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_CA46 += 1;
        if (word_CA46 > 8) {
            sub_2A96();
            sub_428E();
            word_A8A0 = 1;
        }
        break;
    case 141:
        break;
    case 142:
        word_A800 = -80;
        word_A802 = word_CA52 / 8;
        sub_4807(word_A800, word_A802, word_A804);
        sub_2A21();
        word_A2AC = -1;
        word_A80E = -40;
        word_A810 = word_CA52 * 7 / 8;
        word_A812 = 158;
        word_A826 = 0;
        word_A8A0 = 143;
        word_C0AE = 0;
        sub_2ABF(word_C0B0);
        sub_2ABF(word_CA60[8]);
        break;
    case 143:
        word_A80E -= word_A2AC * 16;
        if (word_A812 == 161) {
            word_A812 = 158;
        } else {
            word_A812 += 1;
        }
        if (word_CA52 / 8 < word_A80E) {
            word_A80E = word_CA52 / 8;
            word_A800 = word_CA50;
            word_A802 = word_A810;
            word_A804 = 4;
            word_A2AA = 1;
            word_A8A0 = 144;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 144:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        if (word_A812 == 161) {
            word_A812 = 158;
        } else {
            word_A812 += 1;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        word_A800 -= word_A2AA * 16;
        word_A804 = word_A804 == 4 ? 5 : 4;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A80E + 40 >= word_A800) {
            word_A800 = -80;
            sub_4807(word_A800, word_A802, word_A804);
            word_A8A0 = 145;
        }
        break;
    case 145:
        word_A810 -= 40;
        if (word_A812 == 161) {
            word_A812 = 158;
        } else {
            word_A812 += 1;
        }
        if (word_A810 < -40) {
            sub_2A96();
            sub_428E();
            word_A8A0 = 1;
            break;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 146:
        break;
    case 147:
        sub_2A21();
        word_CA56 = 1;
        word_A2AC = 1;
        word_A812 = 146;
        word_A826 = 0;
        word_A800 = word_CA50;
        word_A802 = -40;
        word_A2AA = 1;
        word_A808 = word_CA50 / -96;
        word_A806 = word_CA52 / 96;
        word_A80E = word_A808 * 92 + word_CA50;
        word_A810 = word_A806 * 92 - 20;
        word_A8A0 = 148;
        word_C0AE = 1;
        sub_2ABF(word_CA60[8]);
        sub_2ABF(word_C0B0);
    case 148:
        if (word_A83A++ < 0) {
            break;
        }
        word_A83A = 0;
        sub_488C(word_A80E, word_A810, word_A812);
        word_A800 += word_A808;
        word_A802 += word_A806;
        word_A804 = word_A3DE[word_A826 / 3];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A826 -= 1;
        }
        if (word_A804 == 0 || word_A804 == 144 || word_A804 == 145) {
            word_A804 = word_A804 == 144 ? 145 : 144;
        }
        if (word_A804 == 137 || word_A804 == 138) {
            word_A804 = word_A804 == 137 ? 138 : 137;
        }
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A80E + 10 > word_A800 || word_A810 + 20 < word_A802) {
            word_A826 = 0;
            word_A8A0 = 149;
            word_A804 = 173;
            sub_4807(word_A800, word_A802, word_A804);
            break;
        }
        break;
    case 149:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 = -80;
        sub_4807(word_A800, word_A802, word_A804);
        word_A812 = word_A494[word_A826];
        word_A826 += 1;
        if (word_A812 == 0) {
            word_A800 = word_A80E;
            word_A802 = word_A810;
            word_A826 = 0;
            sub_42C8(108, 0U, 0);
            word_A8A0 = 150;
            break;
        }
        sub_488C(word_A80E, word_A810, word_A812);
        break;
    case 150:
        word_A804 = 169;
        word_A804 = word_A49E[word_A826];
        word_A826 += 1;
        if (word_A804 == 0) {
            word_A804 = 3;
            word_A8A0 = 151;
            break;
        }
        if (word_A804 >= 81 && word_A804 <= 83) {
            sub_4807(word_A800, word_A802 - 20, word_A804);
        } else {
            sub_4807(word_A800, word_A802, word_A804);
        }
        break;
    case 151:
        if (word_A83A++ < 1) {
            break;
        }
        word_A83A = 0;
        word_A800 -= word_A2AA * 6;
        word_A804 = word_A804 == 2 ? 3 : 2;
        sub_4807(word_A800, word_A802, word_A804);
        if (word_A800 < -40) {
            sub_2A96();
            word_A8A0 = 1;
            break;
        }
        break;
    case 152:
        break;
    default:
        break;
    }
}

/* Environment-affected action change, controlled by a flag. */
void sub_8FD7(int arg_0)
{
    switch (arg_0) {
    case 0:
        word_A8A0 = 1;
        if (word_A7FC != 0) {
            word_A8A0 = 97;
        }
        break;
    case 1:
        word_A8A0 = 81;
        break;
    case 2:
        word_A8A0 = 97;
        break;
    case 3:
        word_CA54 = 113;
        break;
    case 4:
        word_A8A0 = 56;
        break;
    default:
        break;
    }
}

/* Process debug window action change. */
void sub_904A(WPARAM arg_0)
{
    word_CA72 = 0;
    sub_428E();
    sub_2A96();
    switch (arg_0) {
    case 0:
        word_A8A0 = 1;
        break;
    case 1:
        word_A8A0 = 7;
        break;
    case 2:
        word_A8A0 = 11;
        break;
    case 3:
        word_A8A0 = 13;
        break;
    case 4:
        word_A8A0 = 15;
        break;
    case 5:
        word_A8A0 = 17;
        break;
    case 6:
        word_A8A0 = 20;
        break;
    case 7:
        word_A8A0 = 24;
        break;
    case 8:
        word_A8A0 = 30;
        break;
    case 9:
        word_A8A0 = 35;
        break;
    case 10:
        word_A8A0 = 43;
        break;
    case 11:
        word_A8A0 = 45;
        break;
    case 12:
        word_A8A0 = 49;
        break;
    case 13:
        word_A8A0 = 51;
        break;
    case 14:
        word_A8A0 = 53;
        break;
    case 15:
        word_A8A0 = 58;
        break;
    case 16:
        word_A8A0 = 47;
        break;
    case 17:
        word_A8A0 = 147;
        break;
    case 18:
        word_A8A0 = 116;
        break;
    case 19:
        word_A8A0 = 121;
        break;
    case 20:
        word_A8A0 = 126;
        break;
    case 21:
        word_A8A0 = 128;
        break;
    case 22:
        word_A8A0 = 135;
        break;
    case 23:
        word_A8A0 = 142;
        break;
    case 24:
        word_A8A0 = 65;
        break;
    case 25:
        word_A8A0 = 62;
        break;
    case 26:
        word_A8A0 = 75;
        break;
    case 27:
        word_A8A0 = 96;
        break;
    case 28:
        word_A8A0 = 9;
        break;
    case 29:
        word_A8A0 = 69;
        break;
    default:
        break;
    }
}

/* Move window by offset. */
void sub_91CD(int arg_0, int arg_2)
{
    word_A800 += arg_0;
    word_A802 += arg_2;
    sub_4807(word_A800, word_A802, word_A804);
}

/* Initialize bitmaps (sub). */
BOOL sub_9200(HWND arg_0)
{
    HDC var_2;
    var_2 = GetDC(arg_0);
    word_A850[0] = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A850[0] == NULL) {
        goto loc_92FA;
    }
    word_A850[1] = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A850[1] == NULL) {
        goto loc_92FA;
    }
    word_A854 = CreateCompatibleBitmap(var_2, 100, 100);
    if (word_A854 == NULL) {
        goto loc_92FA;
    }
    word_A85A = CreateCompatibleBitmap(var_2, 40, 40);
    if (word_A85A == NULL) {
        goto loc_92FA;
    }
    word_A85C = CreateCompatibleBitmap(var_2, 40, 40);
    if (word_A85C == NULL) {
        goto loc_92FA;
    }
    word_CA4C = 0;
    word_CA4E = 0;
    word_CA50 = GetSystemMetrics(SM_CXSCREEN);
    word_CA52 = GetSystemMetrics(SM_CYSCREEN);
    ReleaseDC(arg_0, var_2);
    word_CA46 = 0;
    word_CA5C = 0;
    word_CA56 = 0;
    word_A890 = 0;
    word_A892 = 0;
    word_A894 = 0;
    word_A896 = 0;
    return TRUE;
loc_92FA:
    ReleaseDC(arg_0, var_2);
    return FALSE;
}

/* Release bitmaps (sub). */
void sub_930F()
{
    DeleteObject(word_A85C);
    DeleteObject(word_A85A);
    DeleteObject(word_A850[0]);
    DeleteObject(word_A850[1]);
    DeleteObject(word_A854);
}

/* Update window position and sprite to be actually used (sub). */
void sub_9350(int arg_0, int arg_2, int arg_4)
{
    word_A878 = arg_0;
    word_A87A = arg_2;
    word_A856 = stru_A8A2[arg_4].bitmaps[0];
    word_A858 = stru_A8A2[arg_4].bitmaps[1];
    word_A85E = stru_A8A2[arg_4].x;
    word_A860 = stru_A8A2[arg_4].y;
    word_A87C = stru_A8A2[arg_4].width;
    word_A87E = stru_A8A2[arg_4].height;
}

/* Clear window (sub). */
void sub_93DF(HWND arg_0)
{
    if (word_CA56 != 0) {
        return;
    }
    word_A890 = 0;
    word_A892 = 0;
    word_A894 = 0;
    word_A896 = 0;
    MoveWindow(arg_0, 0, 0, 0, 0, TRUE);
    word_A872 = 1;
    word_C0BA = 1;
    word_A876 = NULL;
}

/* Render sprite with double buffering (with fade out effect) (sub). */
void sub_9438(HWND arg_0)
{
    HDC var_2;
    HDC var_4;
    HDC var_6;
    int var_C;
    int var_E;
    int var_10;
    int var_12;
    int var_14;
    int var_16;
    int var_18;
    int var_1A;
    int var_1C;
    int var_1E;
    if (word_A870 != 0) {
        return;
    }
    if (word_A890 == word_A878 && word_A892 == word_A87A && word_A876 == word_A856 && word_A866 == word_A85E && word_CA46 == 0 && word_CA5C == 0) {
        return;
    }
    word_A86E ^= 1;
    var_2 = GetDC(NULL);
    SelectPalette(var_2, word_CA4A, FALSE);
    var_4 = CreateCompatibleDC(var_2);
    var_6 = CreateCompatibleDC(var_2);
    SelectPalette(var_6, word_CA4A, FALSE);
    SelectPalette(var_4, word_CA4A, FALSE);
    var_16 = max(word_A878, word_A890);
    var_14 = max(word_A87A, word_A892);
    var_12 = min(word_A87C + word_A878, word_A894 + word_A890) - var_16;
    var_10 = min(word_A87A + word_A87E, word_A892 + word_A896) - var_14;
    if (var_12 <= 0 || var_10 <= 0) {
        word_A898 = 1;
        if (word_A872 != 0) {
            word_A872 = 0;
        }
        word_A880 = word_A878;
        word_A882 = word_A87A;
        word_A884 = word_A87C;
        word_A886 = word_A87E;
        SelectObject(var_4, word_A850[word_A86E]);
        BitBlt(var_4, 0, 0, word_A884, word_A886, var_2, word_A880, word_A882, SRCCOPY);
    } else {
        word_A898 = 0;
        word_A880 = min(word_A878, word_A890);
        word_A882 = min(word_A87A, word_A892);
        word_A884 = max(word_A87C + word_A878, word_A894 + word_A890) - word_A880;
        word_A886 = max(word_A87A + word_A87E, word_A892 + word_A896) - word_A882;
        SelectObject(var_4, word_A850[word_A86E]);
        BitBlt(var_4, 0, 0, word_A884, word_A886, var_2, word_A880, word_A882, SRCCOPY);
        var_1E = max(word_A880, word_A888);
        var_1C = max(word_A882, word_A88A);
        var_1A = min(word_A884 + word_A880, word_A88C + word_A888) - var_1E;
        var_18 = min(word_A882 + word_A886, word_A88A + word_A88E) - var_1C;
        var_16 = max(0, var_1E - word_A880);
        var_14 = max(0, var_1C - word_A882);
        var_E = max(0, var_1E - word_A888);
        var_C = max(0, var_1C - word_A88A);
        if (var_1A > 0 && var_18 > 0) {
            SelectObject(var_6, word_A850[LOBYTE(word_A86E) - 0xFF & 1]);
            BitBlt(var_4, var_16, var_14, var_1A, var_18, var_6, var_E, var_C, SRCCOPY);
        }
    }
    if (word_A856 != NULL) {
        SelectObject(var_6, word_A854);
        BitBlt(var_6, 0, 0, word_A884, word_A886, var_4, 0, 0, SRCCOPY);
        var_16 = max(0, word_A878 - word_A880);
        var_14 = max(0, word_A87A - word_A882);
        if (word_A858 != NULL) {
            if (word_CA46 != 0) {
                if (word_CA46 == 1) {
                    SelectObject(var_4, word_A858);
                    SelectObject(var_6, word_A85C);
                    BitBlt(var_6, 0, 0, 40, 40, var_4, word_A85E, word_A860, SRCCOPY);
                    SelectObject(var_4, word_A856);
                    SelectObject(var_6, word_A85A);
                    BitBlt(var_6, 0, 0, 40, 40, var_4, word_A85E, word_A860, SRCCOPY);
                }
                SelectObject(var_4, word_A85C);
                SelectObject(var_6, stru_A8A2[172].bitmaps[0]);
                BitBlt(var_4, word_CA46 - 1, word_CA46 - 1, 41 - word_CA46, 40, var_6, stru_A8A2[172].x, 0, SRCPAINT);
                SelectObject(var_4, word_A85A);
                SelectObject(var_6, stru_A8A2[172].bitmaps[1]);
                BitBlt(var_4, word_CA46 - 1, word_CA46 - 1, 41 - word_CA46, 40, var_6, stru_A8A2[172].x, 0, SRCAND);
                SelectObject(var_6, word_A854);
                SelectObject(var_4, word_A85C);
                BitBlt(var_6, var_16, var_14, word_A87C, word_A87E, var_4, 0, 0, SRCAND);
                SelectObject(var_4, word_A85A);
                BitBlt(var_6, var_16, var_14, word_A87C, word_A87E, var_4, 0, 0, SRCPAINT);
            } else {
                SelectObject(var_4, word_A858);
                BitBlt(var_6, var_16, var_14, word_A87C, word_A87E, var_4, word_A85E, word_A860, SRCAND);
                SelectObject(var_4, word_A856);
                BitBlt(var_6, var_16, var_14, word_A87C, word_A87E, var_4, word_A85E, word_A860, SRCPAINT);
            }
        } else {
            SelectObject(var_4, word_A856);
            BitBlt(var_6, var_16, var_14, word_A87C, word_A87E, var_4, word_A85E, word_A860, SRCCOPY);
        }
        word_A870 = 1;
        word_CA5E = 1;
        MoveWindow(arg_0, word_A880, word_A882, word_A884, word_A886 + word_CA5C, TRUE);
        word_CA5E = 0;
    }
    DeleteDC(var_4);
    DeleteDC(var_6);
    word_A888 = word_A880;
    word_A88A = word_A882;
    word_A88C = word_A884;
    word_A88E = word_A886;
    word_A890 = word_A878;
    word_A892 = word_A87A;
    word_A894 = word_A87C;
    word_A896 = word_A87E;
    word_A876 = word_A856;
    word_A866 = word_A85E;
    word_A868 = word_A860;
    ReleaseDC(NULL, var_2);
}

/* Render UFO beam (if any) and present render targets onto window (sub). */
BOOL sub_9A49(HWND arg_0)
{
    HDC var_2;
    HDC var_4;
    RECT var_C;
    HDC var_E;
#ifdef _WIN32
    HDC screen;
#endif
    if (word_A870 == 0) {
        return TRUE;
    }
    word_A870 = 0;
    var_2 = GetDC(arg_0);
    SelectPalette(var_2, word_CA4A, FALSE);
    RealizePalette(var_2);
    var_4 = CreateCompatibleDC(var_2);
    SelectPalette(var_4, word_CA4A, FALSE);
    SelectObject(var_4, word_A854);
    BitBlt(var_2, 0, 0, word_A884, word_A886, var_4, 0, 0, SRCCOPY);
    if (word_CA5C != 0) {
        if (word_C0B8 == NULL) {
            word_C0B8 = CreateCompatibleBitmap(var_2, 40, word_CA52 * 4 / 5);
            if (word_C0B8 == NULL) {
                goto loc_9CC3;
            }
        }
        if (word_C0B2 == NULL) {
            word_C0B2 = CreateCompatibleBitmap(var_2, 40, word_CA52 * 4 / 5);
            if (word_C0B2 == NULL) {
                goto loc_9CC3;
            }
        }
        if (word_CA44 == NULL) {
            word_CA44 = CreateSolidBrush(RGB(255, 255, 0));
        }
        if (word_C0B4 == NULL) {
            word_C0B4 = CreateSolidBrush(RGB(128, 128, 0));
        }
        var_E = CreateCompatibleDC(var_2);
        SelectObject(var_E, word_C0B2);
#ifdef _WIN32
        /* Screen contents with height of only 40 pixels can be captured from window device context on Windows 10. Capture directly from screen instead. */
        screen = GetDC(NULL);
        BitBlt(var_E, 0, 0, 40, word_CA5C, screen, word_A880, word_A882 + 40, SRCCOPY);
        ReleaseDC(NULL, screen);
#else
        BitBlt(var_E, 0, 0, 40, word_CA5C, var_2, 0, 40, SRCCOPY);
#endif
        var_C.left = 0;
        var_C.top = 0;
        var_C.right = 40;
        var_C.bottom = word_CA5C;
        SelectObject(var_4, word_C0B8);
        FillRect(var_4, &var_C, word_CA44);
        BitBlt(var_E, 0, 0, 40, word_CA5C, var_4, 0, 0, SRCAND);
        FillRect(var_4, &var_C, word_C0B4);
        BitBlt(var_E, 0, 0, 40, word_CA5C, var_4, 0, 0, SRCPAINT);
        BitBlt(var_2, 0, 40, 40, word_CA5C, var_E, 0, 0, SRCCOPY);
        DeleteDC(var_E);
        DeleteDC(var_4);
    } else {
        if (word_C0B4 != NULL) {
            DeleteObject(word_C0B4);
            word_C0B4 = NULL;
        }
        if (word_CA44 != NULL) {
            DeleteObject(word_CA44);
            word_CA44 = NULL;
        }
        if (word_C0B2 != NULL) {
            DeleteObject(word_C0B2);
            word_C0B2 = NULL;
        }
        if (word_C0B8 != NULL) {
            DeleteObject(word_C0B8);
            word_C0B8 = NULL;
        }
        DeleteDC(var_4);
    }
    ReleaseDC(arg_0, var_2);
    return TRUE;
loc_9CC3:
    ReleaseDC(arg_0, var_2);
    DestroyWindow(arg_0);
    return FALSE;
}
