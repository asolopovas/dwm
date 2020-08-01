/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;        /* border pixel of windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 8;        /* systray spacing */
static const int systraypinningfailfirst = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;        /* 0 means no systray */
static const unsigned int gappih         = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv         = 5;        /* vert inner gap between windows */
static const unsigned int gappoh         = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps               = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const int focusonwheel            = 0;
static const char *fonts[]               = { 
  "monospace:pixelsize=14:antialias=true:autohint=true", 
  "JoyPixels:pixelsize=12:antialias=true:autohint=true"  
};
static char dmenufont[]                  = "monospace:size=14";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfgcolor[]                = "#bbbbbb";
static char selfgcolor[]                 = "#eeeeee";
static char selbordercolor[]             = "#005577";
static char selbgcolor[]                 = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  "#fff303"  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class                        instance    title       tags mask   isCentered   isfloating   isterminal   noswallow  monitor */
    { "St",                         NULL,       NULL,       0,          0,           0,           1,           0,         -1  },
    { "fzfmenu",                    NULL,       NULL,       0,          1,           1,           1,           0,         -1  },
    { "Gimp",                       NULL,       NULL,       1<<7,       0,           0,           0,           0,         -1  },
    { "Spotify",                    NULL,       NULL,       1<<2,       0,           0,           0,           0,          0  },
    /* Messengers  */
    { "ViberPC",                    NULL,       NULL,       1<<8,       0,           0,           0,           0,          1  },
    { "Skype",                      NULL,       NULL,       1<<8,       0,           0,           0,           0,          1  },
    { "TelegramDesktop",            NULL,       NULL,       1<<8,       0,           0,           0,           0,          1  },
    { "whatsapp-nativefier-d52542", NULL,       NULL,       1<<8,       0,           0,           0,           0,          1  },
    /* Productivity  */
    { "Ao",                         NULL,       NULL,       1<<7,       0,           0,           0,           0,         -1  },
    { "p3x-onenote",                NULL,       NULL,       1<<7,       0,           0,           0,           0,         -1  },
    /* System  */
    { "Nvidia-settings",            NULL,       NULL,       1<<7,       0,           1,           0,           0,          0  },
    { "Lxappearance",               NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "Blueman-manager",            NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "Psi",                        NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "Gpg-crypter",                NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "Lxappearance",               NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "stacer",                     NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    /* Various  */
    { "vlc",                        NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
    { "Image Lounge",               NULL,       NULL,       0,          0,           0,           0,           0,         -1  },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",    tile },         /* Default: Master on left, slaves on right */
    { "TTT",    bstack },       /* Master on top, slaves on bottom */

    { "[@]",    spiral },       /* Fibonacci spiral */
    { "[\\]",   dwindle },      /* Decreasing in size right and leftward */

    { "H[]",    deck },         /* Master on left, slaves in monocle-like mode on right */
    { "[M]",    monocle },      /* All windows on top of eachother */

    { "|M|",    centeredmaster },       /* Master in middle, slaves on sides */
    { ">M>",    centeredfloatingmaster },   /* Same but master floats */

    { "><>",    NULL },         /* no layout function means floating behavior */
    { NULL,     NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MOD1 Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD,                          XK_j,     ACTION##stack,  {.i = INC(+1) } }, \
    { MOD,                          XK_k,     ACTION##stack,  {.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]            = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]       = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
 /* modifier                      key                   function        argument */
    STACKKEYS(                  MODKEY,             focus)
    STACKKEYS(                  MODKEY|ShiftMask,   push)
    TAGKEYS(                    XK_1,                       0)
    TAGKEYS(                    XK_2,                       1)
    TAGKEYS(                    XK_3,                       2)
    TAGKEYS(                    XK_4,                       3)
    TAGKEYS(                    XK_5,                       4)
    TAGKEYS(                    XK_6,                       5)
    TAGKEYS(                    XK_7,                       6)
    TAGKEYS(                    XK_8,                       7)
    TAGKEYS(                    XK_9,                       8)

    // -------------------------------------------------
    // Layouts
    // -------------------------------------------------
    { MODKEY,                   XK_t,           setlayout,      {.v = &layouts[0] } },
    { MODKEY|ShiftMask,         XK_t,           setlayout,      {.v = &layouts[1] } },
    { MODKEY,                   XK_y,           setlayout,      {.v = &layouts[2] } },
    { MODKEY|ShiftMask,         XK_y,           setlayout,      {.v = &layouts[3] } },
    { MODKEY,                   XK_u,           setlayout,      {.v = &layouts[4] } },
    { MODKEY|ShiftMask,         XK_u,           setlayout,      {.v = &layouts[5] } },
    { MODKEY,                   XK_i,           setlayout,      {.v = &layouts[6] } },
    { MODKEY|ShiftMask,         XK_i,           setlayout,      {.v = &layouts[7] } },
    { MODKEY,                   XK_o,           incnmaster,     {.i = +1          } },
    { MODKEY|ShiftMask,         XK_o,           incnmaster,     {.i = -1          } },
    { MODKEY,                   XK_Tab,         view,           {0                } },
    { MODKEY,                   XK_q,           killclient,     {0                } },
    { MOD1|ShiftMask,           XK_q,           quit,           {0                } },
    { MODKEY,                   XK_backslash,   view,           {0                } },
    { MODKEY,                   XK_s,           togglesticky,   {0                } },
    { MODKEY|ShiftMask,         XK_d,           togglegaps,     {0                } },
    { MODKEY,                   XK_f,           togglefullscr,  {0                } },
    { MODKEY|ShiftMask,         XK_f,           setlayout   ,   {.v = &layouts[8] } },
    { MODKEY,                   XK_g,           shiftview,      {.i = -1          } },
    { MOD1,                     XK_h,           setmfact,       {.f = -0.05       } },
    { MOD1,                     XK_l,           setmfact,       {.f = +0.05       } },
    { MODKEY,                   XK_Return,      spawn,          {.v = termcmd     } },
    { MODKEY|ShiftMask,         XK_Return,      togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                   XK_semicolon,   shiftview,      {.i = 1           } },
    { MODKEY,                   XK_0,           view,           {.ui = ~0         } },
    { MODKEY|ShiftMask,         XK_0,           tag,            {.ui = ~0         } },

    // -------------------------------------------------
    // Software
    // -------------------------------------------------
    { MODKEY,                   XK_d,           spawn,          {.v = dmenucmd } },
    { MODKEY,                   XK_grave,       spawn,          SHCMD("dmenuunicode") },
    { MODKEY,                   XK_b,           spawn,          SHCMD("$BROWSER") },
    { MODKEY,                   XK_m,           spawn,          SHCMD("spotify") },
    { MODKEY,                   XK_x,           spawn,          SHCMD("$FILEMANAGER") },
    { MODKEY|ShiftMask,         XK_p,           spawn,          SHCMD("fzfmenu storm") },
    { MODKEY,                   XK_p,           spawn,          SHCMD("fzfmenu fzfst") },
    { MODKEY,                   XK_BackSpace,   spawn,          SHCMD("sysact") },
    { MODKEY,                   XK_minus,       spawn,          SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,         XK_minus,       spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                   XK_equal,       spawn,          SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,         XK_equal,       spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },

    // -------------------------------------------------
    // Monitor Navigation
    // -------------------------------------------------
    { MODKEY,                   XK_h,           focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,         XK_h,           tagmon,         {.i = -1 } },
    { MODKEY,                   XK_l,           focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,         XK_l,           tagmon,         {.i = +1 } },
    { MODKEY,                   XK_Left,        viewtoleft,     {0} },
    { MODKEY,                   XK_Right,       viewtoright,    {0} },
    { MODKEY|ShiftMask,         XK_Left,        tagtoleft,      {0} },
    { MODKEY|ShiftMask,         XK_Right,       tagtoright,     {0} },
    { MODKEY,                   XK_Page_Up,     shiftview,      { .i = -1 } },
    { MODKEY,                   XK_Page_Down,   shiftview,      { .i = 1 } },
    { MODKEY,                   XK_Insert,      spawn,          SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
    { MODKEY,                   XK_space,       zoom,           {0} },
    { MODKEY|ShiftMask,         XK_space,       togglefloating, {0} },

    // -------------------------------------------------
    // Media Buttons
    // -------------------------------------------------
    { 0, XK_Print,                 spawn,           SHCMD("flameshot gui") },
    { 0, XF86XK_AudioMute,         spawn,           SHCMD("lmc mute; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,  spawn,           SHCMD("lmc up; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,  spawn,           SHCMD("lmc down; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioPrev,         spawn,           SHCMD("playerctl previous") },
    { 0, XF86XK_AudioNext,         spawn,           SHCMD("playerctl next") },
    { 0, XF86XK_AudioPause,        spawn,           SHCMD("playerctl pause") },
    { 0, XF86XK_AudioPlay,         spawn,           SHCMD("playerctl play-pause") },
    { 0, XF86XK_AudioStop,         spawn,           SHCMD("playerctl stop") },
    { 0, XF86XK_AudioMedia,        spawn,           SHCMD("st -e ncmpcpp") },
    { 0, XF86XK_PowerOff,          spawn,           SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
    { 0, XF86XK_Calculator,        spawn,           SHCMD("st -e bc -l") },
    { 0, XF86XK_Sleep,             spawn,           SHCMD("sudo -A zzz") },
    { 0, XF86XK_WWW,               spawn,           SHCMD("$BROWSER") },
    { 0, XF86XK_DOS,               spawn,           SHCMD("st") },
    { 0, XF86XK_ScreenSaver,       spawn,           SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0, XF86XK_TaskPane,          spawn,           SHCMD("st -e htop") },
    { 0, XF86XK_Mail,              spawn,           SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
    { 0, XF86XK_MyComputer,        spawn,           SHCMD("st -e lf /") },
    // { 0, XF86XK_Battery,        spawn,           SHCMD("") },
    { 0, XF86XK_Launch1,           spawn,           SHCMD("xset dpms force off") },
    { 0, XF86XK_TouchpadToggle,    spawn,           SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOff,       spawn,           SHCMD("synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOn,        spawn,           SHCMD("synclient TouchpadOff=0") },
    { 0, XF86XK_MonBrightnessUp,   spawn,           SHCMD("xbacklight -inc 15") },
    { 0, XF86XK_MonBrightnessDown, spawn,           SHCMD("xbacklight -dec 15") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]           } },
    { ClkWinTitle,          0,              Button2,        zoom,           {0                          } },
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1                     } },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2                     } },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3                     } },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4                     } },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5                     } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0                          } },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0                          } },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0                          } },
    { ClkTagBar,            0,              Button1,        view,           {0                          } },
    { ClkTagBar,            0,              Button3,        toggleview,     {0                          } },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0                          } },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0                          } },
    { ClkTagBar,            0,              Button4,        shiftview,      {.i = -1                    } },
    { ClkTagBar,            0,              Button5,        shiftview,      {.i = 1                     } },
};
