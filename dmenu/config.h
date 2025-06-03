static const char *colors[SchemeLast][2] = {
    [SchemeNorm] = { "#cdd6f4", "#14141d" },
    [SchemeSel] = { "#1e1e2e", "#9c98d5" },
    [SchemeOut] = { "#000000", "#9c98d5" },
};

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int centered = 1;                    /* -c option; centers dmenu on screen */
static int min_width = 500;                /* minimum width when centered */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"JetBrainsMonoNL:size=14:antialias=true:hinting=true"
};
static const char *prompt      = "dmenu:";      /* -p  option; prompt to the left of input field */
static unsigned int lines      = 0;
static unsigned int columns    = 0;
/* -h option; minimum height of a menu line */
static unsigned int lineheight = 1;
static unsigned int min_lineheight = 20;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static const unsigned int border_width = 2;
