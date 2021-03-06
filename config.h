/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 4;       /* vertical padding of bar */
static const int sidepad            = 4;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12" };
static const char norm_fg[] = "#9191cb";
static const char norm_bg[] = "#0c0923";
static const char norm_border[] = "#65658e";
 
static const char sel_fg[] = "#9191cb";
static const char sel_bg[] = "#141043";
static const char sel_border[] = "#9191cb";

 
 
static const char *colors[][3]      = {
	    /*               fg           bg         border                         */
	    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
	        [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,     NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "[M]",      monocle },
        { "[@]",      spiral },
        { "[\\]",     dwindle },
        { "H[]",      deck },
        { "TTT",      bstack },
        { "===",      bstackhoriz },
        { "HHH",      grid },
        { "###",      nrowgrid },
        { "---",      horizgrid },
        { ":::",      gaplessgrid },
        { "|M|",      centeredmaster },
        { ">M>",      centeredfloatingmaster },
        { "><>",      NULL },    /* no layout function means floating behavior */
        { NULL,       NULL },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          SHCMD("st") }, 
	{ MODKEY,                       XK_r,      spawn,          SHCMD("st -e vifm") }, 
	{ MODKEY,                       XK_a,      spawn,          SHCMD("st -e pulsemixer") }, 
	{ MODKEY,                       XK_b,      spawn,          SHCMD("chromium") }, 
	{ 0,                            XK_Print,  spawn,          SHCMD("sh ~/Scripts/screenshot") }, 
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_plus,   incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ Mod1Mask,                     XK_1,      setlayout,      {.v = &layouts[0]} },
	{ Mod1Mask,                     XK_2,      setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask,                     XK_3,      setlayout,      {.v = &layouts[3]} },
	{ Mod1Mask,                     XK_4,      setlayout,      {.v = &layouts[5]} },
	{ Mod1Mask,                     XK_5,      setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,                     XK_6,      setlayout,      {.v = &layouts[4]} },
	{ Mod1Mask,                     XK_7,      setlayout,      {.v = &layouts[6]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_s,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_s,      toggletag,      {.ui = ~0 } },
//	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
//	TAGKEYS(                        XK_5,                      4)
//	TAGKEYS(                        XK_6,                      5)
//	TAGKEYS(                        XK_7,                      6)
//	TAGKEYS(                        XK_8,                      7)
//	TAGKEYS(                        XK_9,                      8)
	{ ControlMask|Mod1Mask,         XK_d,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

