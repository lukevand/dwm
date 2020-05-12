/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus-9" };
static const char dmenufont[]       = "monospace-9";
static const char col_gray1[]       = "gray9"; // dark
static const char col_gray2[]       = "#444444"; // light
static const char col_gray3[]       = "#bbbbbb"; // white
static const char col_gray4[]       = "#eeeeee"; // very white
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4  },
};

/* tagging */
#define WWW 1
#define EMACS 2
#define VID 3
#define DOC 4
#define DL 5
#define PIC 6
static const char *tags[] = { "u", "w", "3", "m", "z", "d", "s", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       PIC,            1,           -1 },
	{ "NULL",     NULL,       "Event Tester",       0,            1,           -1 },
	{ "Pavucontrol",     NULL,       NULL,       0,            1,           -1 },
	{ "Nm-connection-editor",     NULL,       NULL,       0,            1,           -1 },
	{ "kmines",    NULL,	 NULL,		1,	      1,	   -1 },

    // java
	{ "tutorial2.Exterminator",     NULL,       NULL,       1,            1,           -1 },
	{ "reserve.Reserve",     NULL,       NULL,       1,            1,           -1 },
	{ "lab1-ParticleMain",     NULL,       NULL,       1,            1,           -1 },
	/* { "application.Main",     NULL,       NULL,       1,            1,           -1 }, */

	/* (u)rxvt/terminal */
	{ "st-256color",   NULL,       NULL,	      1, 0, -1 },
	{ "st-256color",   "float",       NULL,	      1, 1, -1 },

	{ "URxvt",   NULL,	 NULL,		1, 0, -1 },
	{ "stterm-256color",   NULL,	   NULL,	  1, 0, -1 },
	/* (w)eb */
	{ "Firefox", NULL,	 NULL,		1 << WWW,	      0,	   -1 },
	{ "firefox", NULL,	 NULL,		1 << WWW,	      0,	   -1 },
	{ "Chromium", NULL,	 NULL,		1 << WWW,	      0,	   -1 },
	{ "IceCat", NULL,	 NULL,		1 << WWW,	      0,	   -1 },
	{ "qutebrowser", NULL,	 NULL,		1 << WWW,	      0,	   -1 },
	{ "Tor Browser", NULL,	 NULL,		1 << 7,	      1,	   -1 },

	{ "Eclipse", NULL,	 NULL,		1 << EMACS,	      0,	   -1 },

	/* { "Emacs",   NULL,       NULL,          1 << EMACS, 0, -1 }, */
	{ "Qemu-system-x86_64",   NULL,       NULL,          1 << EMACS, 0, -1 },
	{ "zoom",   NULL,       NULL,          1 << EMACS, 0, -1 },
	{ "jetbrains-pycharm-ce", NULL,	 NULL,		1 << EMACS,	      0,	   -1 },
	{ "jetbrains-idea-ce", NULL,	 NULL,		1 << EMACS,	      0,	   -1 },
	/* (m)pv */
	{ "mpv",     NULL,	 NULL,		1 << VID, 0, -1 },
	/* (z)athura (docs)*/
	{ "Zathura", NULL,	 NULL,		1 << DOC, 0, -1 },

	/* (d)ownloads */
	{ "qBittorrent", NULL, NULL,		1 << DL, 0, -1 },
	{ "Transmission-gtk", NULL, NULL,	1 << DL, 0, -1 },
	{ "transmission", NULL, NULL,		1 << DL, 0, -1 },
	{ "discord", NULL, NULL,		1 << DL, 0, -1 },

	/* (s)xiv/pictures */
	{ "Sxiv",    NULL, NULL, 1 << PIC, 0, -1 },
	{ "feh", NULL, NULL, 1 << PIC, 0, -1 },
	{ "MComix", NULL, NULL, 1 << PIC, 0, -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "stterm", "-f", dmenufont, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_semicolon,      spawn,          {.v = dmenucmd } },
	// { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_e,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_o, zoom,           {0} },
	// { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,             XK_space,  togglefloating, {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

        TAGKEYS(                        XK_u,                      0)
        TAGKEYS(                        XK_w,                      WWW)
        TAGKEYS(                        XK_m,                      VID)
        TAGKEYS(                        XK_z,                      DOC)
        TAGKEYS(                        XK_d,                      DL)
        TAGKEYS(                        XK_s,                      PIC)


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
	{ ClkTagBar,            0,              Button1,        toggleview,           {0} },
	{ ClkTagBar,            0,              Button3,        view,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

