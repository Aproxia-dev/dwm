/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  	 = 2;        /* border pixel of windows */
static const unsigned int snap      	 = 32;       /* snap pixel */
static const unsigned int gappih    	 = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    	 = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    	 = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    	 = 40;       /* vert outer gap between windows and screen edge */
static       int smartgaps          	 = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        	 = 0;     /* 0 means no systray */
static const int showbar            	 = 1;     /* 0 means no bar */
static const int topbar             	 = 1;     /* 0 means bottom bar */
static const char buttonbar[]       	 = "";
static const char *fonts[]          	 = { "Fira Code Nerd Font Mono:size=10:style=Regular:antialias=true:autohint=true", "Twemoji:size=10:style=Regular:antialias=true:autohint=true" };
static const char col_borsel[]      	 = "#c9cbff";
static const char col_bornorm[]     	 = "#575268";
static const char col_barbg[]       	 = "#1e1e2e";
static const char col_barfg[]       	 = "#d9e0ee";
static const char col_barlbg[]      	 = "#302D41";
static const char col_barcool[]     	 = "#f5c2e7";

static const char *colors[][3]      = {
        /*                 fg           bg           border      */
        [SchemeNorm]   =  { col_barfg,   col_barbg,   col_bornorm },
        [SchemeSel]    =  { col_barbg,   col_barcool, col_borsel  },
        [SchemeTitle]  =  { col_barcool, col_barlbg,  col_barfg   },
        [SchemeButton] =  { col_barcool, col_barbg,  col_barfg   },
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
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
        { "|M|",      centeredmaster },
	{ "HHH",      grid },
	{ "===",      bstackhoriz },
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
#define TERMINAL "kitty"
#define STATUSBAR "dwmblocks"

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_b,                   togglebar,      {0} },
        { MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
        { MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_dead_acute,          incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_equal,               incnmaster,     {.i = -1 } },  
	{ MODKEY,              		XK_uacute,      	incrigaps,      {.i = +1 } },
	{ MODKEY,    			XK_parenright,      	incrigaps,      {.i = -1 } },
	{ MODKEY,              		XK_uring,      		incrogaps,      {.i = +1 } },
	{ MODKEY,    			XK_section,      	incrogaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,           	XK_uacute,      	incrihgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    		XK_parenright,      	incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,         	XK_uacute,      	incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,    	XK_parenright,      	incrivgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,           	XK_uring,      		incrohgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    		XK_section,      	incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,         	XK_uring,      		incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,    	XK_section,      	incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_dead_diaeresis,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_dead_diaeresis,      defaultgaps,    {0} },
	{ MODKEY,                       XK_q,                   killclient,     {0} },
        { MODKEY,                       XK_t,                   setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_y,                   setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_u,                   setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_i,                   setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_o,                   setlayout,      {.v = &layouts[4]} },
        { MODKEY,                       XK_space,               zoom,           {0} },
        { MODKEY|ControlMask,           XK_space,               setlayout,      {.v = &layouts[5]} },
        { MODKEY|ShiftMask,             XK_space,               togglefloating, {0} },
        { MODKEY,                       XK_ecaron,              view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_ecaron,              tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,               focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,              focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,               tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period,              tagmon,         {.i = +1 } },
        TAGKEYS(                        XK_plus,                   0)
        TAGKEYS(                        XK_ecaron,                 1)
        TAGKEYS(                        XK_scaron,                 2)
        TAGKEYS(                        XK_ccaron,                 3)
        TAGKEYS(                        XK_rcaron,                 4)
        TAGKEYS(                        XK_zcaron,                 5)
        TAGKEYS(                        XK_yacute,                 6)
        TAGKEYS(                        XK_aacute,                 7)
        TAGKEYS(                        XK_iacute,                 8)    
        { MODKEY|ShiftMask,             XK_x,			   quit,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,            0,              Button1,        spawn,          SHCMD("rofi -show drun") },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button3,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

