/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showsystray        = 1;     /* 0 means no systray */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "2", "4", "6", "8", "5", "7", "%" };

static const char *const autostart[] = {
	"~/Builds/dwm/status.sh", NULL,
	"emacs", NULL,
	"spotify", NULL,
	"chromium", NULL,
	NULL /* terminate */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title               tags mask     isfloating   monitor */
        { "Emacs",       NULL,       NULL,            1 << 0,        0,           -1},
	{ "Chromium",    NULL,       NULL,            1 << 1,        0,           -1},
        { "Spotify",     NULL,       NULL,            1 << 2,        0,           -1}
	
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "tabbed", "-c", "st", "-w", NULL };
static const char *emacscmd[]  = { "emacs", NULL };
static const char *qutebrowsercmd[]  = { "qutebrowser", NULL };
static const char *decreasevolcmd[]  = { "pactl", "--", "set-sink-volume", "0", "-10%", NULL };
static const char *increasevolcmd[]  = { "pactl", "--", "set-sink-volume", "0", "+10%", NULL };
static const char *decreasebrightnesscmd[]  = { "brightnessctl", "s", "10%-", NULL };
static const char *increasebrightnesscmd[]  = { "brightnessctl", "s", "+10%", NULL };
static const char *increaserednesscmd[]  = { "redshift", "-O", "2000", NULL };
static const char *resetrednesscmd[]  = { "redshift", "-x", NULL };
static const char *pavucontrolcmd[]  = { "pavucontrol", NULL };
static const char *suspendcmd[]  = { "systemctl", "suspend", NULL };
static const char *nnncmd[]  = { "alacritty", "-e", "nnn", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_u,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = qutebrowsercmd } },
	{ MODKEY,             		XK_asterisk,spawn,         {.v = increasevolcmd } },
	{ MODKEY,             		XK_equal,  spawn,          {.v = decreasevolcmd } },
	{ MODKEY,             	 	XK_v,      spawn,          {.v = pavucontrolcmd } },
	{ MODKEY,             	 	XK_braceright, spawn,      {.v = decreasebrightnesscmd } },
	{ MODKEY|ShiftMask,             XK_braceright, spawn,      {.v = resetrednesscmd } },
	{ MODKEY,             	 	XK_parenleft, spawn,       {.v = increasebrightnesscmd } },
	{ MODKEY,                       XK_backslash, spawn,       {.v = nnncmd } },
	{ MODKEY|ShiftMask,             XK_parenleft, spawn,       {.v = increaserednesscmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_s,	   spawn,          {.v = suspendcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_less,  focusmon,        {.i = -1 } },
	{ MODKEY,                       XK_greater, focusmon,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_parenright,             0) //2
	TAGKEYS(                        XK_plus,                   1) //4
	TAGKEYS(                        XK_bracketright,           2) //6
	TAGKEYS(                        XK_exclam,                 3) //8
	TAGKEYS(                        XK_braceleft,              4) //5  
	TAGKEYS(                        XK_bracketleft,            5) //7 
	TAGKEYS(                        XK_ampersand,              6) //% 
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

