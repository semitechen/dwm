/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows (0 = borderless to maximize screen) */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=11", "monospace:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=11";
static const char col_gray1[]       = "#1a1b26";
static const char col_gray2[]       = "#24283b";
static const char col_gray3[]       = "#a9b1d6";
static const char col_gray4[]       = "#c0caf5";
static const char col_cyan[]        = "#7aa2f7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Tag bitmask definitions for dedicated apps */
#define TAG_TMUX     (1 << 0)  /* Tag 1: Terminal / tmux   (Super+d) */
#define TAG_AERC     (1 << 1)  /* Tag 2: aerc email        (Super+a) */
#define TAG_SPOTATUI (1 << 2)  /* Tag 3: spotatui music    (Super+s) */
#define TAG_IAMB     (1 << 3)  /* Tag 4: iamb chat         (Super+z) */
#define TAG_HELIUM   (1 << 4)  /* Tag 5: Helium browser    (Super+x) */
#define TAG_KICAD    (1 << 5)  /* Tag 6: KiCad EDA         (Super+q) */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "file_chooser",     NULL,       NULL,       0,            1,           -1 },
	{ "tmux",             NULL,       NULL,       TAG_TMUX,     0,           -1 },
	{ "aerc",             NULL,       NULL,       TAG_AERC,     0,           -1 },
	{ "spotatui",         NULL,       NULL,       TAG_SPOTATUI, 0,           -1 },
	{ "iamb",             NULL,       NULL,       TAG_IAMB,     0,           -1 },
	{ "helium",           NULL,       NULL,       TAG_HELIUM,   0,           -1 },
	{ "Helium",           NULL,       NULL,       TAG_HELIUM,   0,           -1 },
	{ "helium-browser",   NULL,       NULL,       TAG_HELIUM,   0,           -1 },
	{ "Helium-browser",   NULL,       NULL,       TAG_HELIUM,   0,           -1 },
	{ "kicad",            NULL,       NULL,       TAG_KICAD,    0,           -1 },
	{ "KiCad",            NULL,       NULL,       TAG_KICAD,    0,           -1 },
	{ "pcbnew",           NULL,       NULL,       TAG_KICAD,    0,           -1 },
	{ "eeschema",         NULL,       NULL,       TAG_KICAD,    0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 0 avoids gaps around terminal character grids to truly maximize screen */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* first entry is default: fullscreen monocle */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>

/* commands */
static const char *termcmd[] = { "kitty", "--single-instance", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *yazicmd[] = { "kitty", "--single-instance", "yazi", NULL };

/* Hardware controls (PipeWire volume & brightness for Framework 13) */
static const char *upvol[]      = { "wpctl", "set-volume", "-l", "1.5", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *downvol[]    = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *mutevol[]    = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *brightup[]   = { "brightnessctl", "set", "+5%", NULL };
static const char *brightdown[] = { "brightnessctl", "set", "5%-", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* Direct App / Tag Navigation */
	{ MODKEY,                       XK_d,      view,           {.ui = TAG_TMUX} },
	{ MODKEY,                       XK_a,      view,           {.ui = TAG_AERC} },
	{ MODKEY,                       XK_s,      view,           {.ui = TAG_SPOTATUI} },
	{ MODKEY,                       XK_z,      view,           {.ui = TAG_IAMB} },
	{ MODKEY,                       XK_x,      view,           {.ui = TAG_HELIUM} },
	{ MODKEY,                       XK_q,      view,           {.ui = TAG_KICAD} },

	/* Send focused window to App Tags */
	{ MODKEY|ShiftMask,             XK_d,      tag,            {.ui = TAG_TMUX} },
	{ MODKEY|ShiftMask,             XK_a,      tag,            {.ui = TAG_AERC} },
	{ MODKEY|ShiftMask,             XK_s,      tag,            {.ui = TAG_SPOTATUI} },
	{ MODKEY|ShiftMask,             XK_z,      tag,            {.ui = TAG_IAMB} },
	{ MODKEY|ShiftMask,             XK_x,      tag,            {.ui = TAG_HELIUM} },
	{ MODKEY|ShiftMask,             XK_q,      tag,            {.ui = TAG_KICAD} },

	/* Launchers */
	{ MODKEY,                       XK_space,  spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = yazicmd } },

	/* Window & Tag Control */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/* Hardware Keys (Volume & Brightness for Framework 13) */
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = mutevol } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brightdown } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* Numbered Tags (1-9) */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* Quit dwm */
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
