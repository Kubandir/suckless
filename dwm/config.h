#include "./XF86keysym.h"
#include "./colorschemes/tokyonight.h"
#include "movestack.c"

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 18   /* icon size */
#define ICONSPACING 8 /* space between icon and title */
static const char *fonts[] = { "FiraCode Nerd Font:weight=bold:size=11:antialias=true:hinting=true", "Noto Sans CJK JP:weight=bold:size=9:antialias=true:hinting=true" };
static const char dmenufont[]       = "BigBlueTermPlus Nerd Font Mono:weight=Regular:size=11:antialias=true:hinting=true"; 
static const char *colors[][3]      = {
    [SchemeNorm] = { col_gray3, col_gray2, col_gray2 },
    [SchemeSel]  = { col_cyan, col_gray4,  col_cyan },
  [SchemeTitle]  = { col_title, col_gray4, col_gray4 },
};


static const char *tags[] = {
    "一",  // 1 (ichi)
    "二",  // 2 (ni)
    "三",  // 3 (san)
    "四",  // 4 (shi/yon)
    "五",  // 5 (go)
    "六",  // 6 (roku)
    "七",  // 7 (shichi/nana)
    "八",  // 8 (hachi)
    "九"   // 9 (kyuu)
};




static const Rule rules[] = {
{ "Paradox", NULL, NULL, 1 << 0, 1, -1 },
};

static const float mfact = 0.5;
static const int nmaster = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
{ "[]=",      spiral },    // Spiral tiling layout
{ "<><",       NULL },      // End of layouts array
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY, KEY, view, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask, KEY, tag, {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *dmenucmd[] = { "dmenu_run","-l", "6", "-g","1","-h", "32", "-fn", dmenufont, "-shb", "#9c98d5", "-shf","#585b70", "-nhb", "#14141d", "-nhf","#585b70" ,NULL };
static const char *termcmd[] = { "st", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };
static const char *thunarcmd[] = { "thunar", NULL };
static const char *slockcmd[] = { "slock", NULL };
static const char *codecmd[] = { "code", NULL };
static const char *flameshotcmd[] = { "/bin/sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };
static const char *brupcmd[] = { "/bin/sh", "-c", "/home/hoks/.config/suckless/dwm/scripts/brightnessnotifications.sh up", NULL };
static const char *brdowncmd[] = { "/bin/sh", "-c", "/home/hoks/.config/suckless/dwm/scripts/brightnessnotifications.sh down", NULL };
static const char *upvol[] = { "/bin/sh", "-c", "/home/hoks/.config/suckless/dwm/scripts/volumenotifications.sh up", NULL };
static const char *downvol[] = { "/bin/sh", "-c", "/home/hoks/.config/suckless/dwm/scripts/volumenotifications.sh down", NULL };
static const char *mutevol[] = { "/bin/sh", "-c", "/home/hoks/.config/suckless/dwm/scripts/volumenotifications.sh mute", NULL };

static const Key keys[] = {
{ MODKEY, XK_d, spawn, {.v = dmenucmd } },
{ MODKEY, XK_c, spawn, {.v = codecmd } },
{ MODKEY, XK_Return, spawn, {.v = termcmd } },
{ MODKEY, XK_s, spawn, {.v = firefoxcmd } },
{ MODKEY, XK_t, spawn, {.v = thunarcmd } },
{ MODKEY|ShiftMask, XK_l, spawn, {.v = slockcmd } },
{ MODKEY, XK_b, togglebar, {0} },
{ MODKEY, XK_f, fullscreen, {0} },
{ MODKEY|ShiftMask, XK_s, spawn, {.v = flameshotcmd } },
{ MODKEY|ShiftMask, XK_q, quit, {0} },
{ MODKEY, XK_q, killclient, {0} },
{ 0, XF86XK_MonBrightnessUp, spawn, {.v = brupcmd } },
{ 0, XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd } },
{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
{ 0, XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
{ 0, XF86XK_AudioMute, spawn, {.v = mutevol } },
TAGKEYS( XK_plus, 0)
TAGKEYS( XK_ecaron, 1)
TAGKEYS( XK_scaron, 2)
TAGKEYS( XK_ccaron, 3)
TAGKEYS( XK_rcaron, 4)
TAGKEYS( XK_zcaron, 5)
TAGKEYS( XK_yacute, 6)
TAGKEYS( XK_aacute, 7)
TAGKEYS( XK_iacute, 8)
{ MODKEY, XK_Left, focusstack, {.i = -1 } },
{ MODKEY, XK_Right, focusstack, {.i = +1 } },
{ MODKEY, XK_Up, focusstack, {.i = -1 } },
{ MODKEY, XK_Down, focusstack, {.i = +1 } },
{ MODKEY|ShiftMask, XK_Left, movestack, {.i = -1 } },
{ MODKEY|ShiftMask, XK_Right, movestack, {.i = +1 } },
{ MODKEY|ShiftMask, XK_Up, movestack, {.i = -1 } },
{ MODKEY|ShiftMask, XK_Down, movestack, {.i = +1 } },
};

static const Button buttons[] = {
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        zoom,           {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

