/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code Nerd Font Mono:size=12:style=Regular:antialias=true:autohint=true" };
static const char dmenufont[]       = "Fira Code Nerd Font Mono:size=12:style=Regular:antialias=true:autohint=true";
static const char col_bg[]          = "#32302f";
static const char col_fg[]          = "#d4be98";
static const char col_border[]      = "#d8a657";
static const char col_selborder[]   = "#ea6962";
static const char col_gray1[]				= "#222222";
static const char col_gray2[]				= "#444444";
static const char col_gray3[]				= "#bbbbbb";
static const char col_gray4[]				= "#eeeeee";
static const char col_cyan[]				= "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg,  col_border     },
	[SchemeSel]  = { col_bg, col_fg,  col_selborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,				NULL },
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
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        			function        argument */
	{ MODKEY,                       XK_Return, 			spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_uacute, 			incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_parenright,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY,					              XK_space, 			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY,  					            XK_q,      			killclient,     {0} },
	{ MODKEY,                       XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      			setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_i,      			setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      			setlayout,      {.v = &layouts[4]} },
	{ MODKEY,												XK_comma,	 			cyclelayout,		 {.i = -1 } },
	{ MODKEY,           						XK_period, 			cyclelayout,		 {.i = +1 } },
	{ MODKEY|ControlMask,           XK_space,  			setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  			togglefloating, {0} },
	{ MODKEY,                       XK_eacute, 			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_eacute, 			tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_plus,                   0)
	TAGKEYS(                        XK_ecaron,                 1)
	TAGKEYS(                        XK_scaron,                 2)
	TAGKEYS(                        XK_ccaron,                 3)
	TAGKEYS(                        XK_rcaron,                 4)
	TAGKEYS(                        XK_zcaron,                 5)
	TAGKEYS(                        XK_yacute,                 6)
	TAGKEYS(                        XK_aacute,                 7)
	TAGKEYS(                        XK_iacute,                 8)
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
