/*
========================================================================

                           D O O M  R e t r o
         The classic, refined DOOM source port. For Windows PC.

========================================================================

  Copyright © 1993-2022 by id Software LLC, a ZeniMax Media company.
  Copyright © 2013-2022 by Brad Harding <mailto:brad@doomretro.com>.

  DOOM Retro is a fork of Chocolate DOOM. For a list of credits, see
  <https://github.com/bradharding/doomretro/wiki/CREDITS>.

  This file is a part of DOOM Retro.

  DOOM Retro is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the license, or (at your
  option) any later version.

  DOOM Retro is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOOM Retro. If not, see <https://www.gnu.org/licenses/>.

  DOOM is a registered trademark of id Software LLC, a ZeniMax Media
  company, in the US and/or other countries, and is used without
  permission. All other trademarks are the property of their respective
  holders. DOOM Retro is in no way affiliated with nor endorsed by
  id Software.

========================================================================
*/

#pragma once

#include "d_event.h"
#include "doomdef.h"
#include "doomtype.h"
#include "r_defs.h"

#define CONSOLESTRINGSMAX       256

#define CONSOLEFONTSTART        ' '
#define CONSOLEFONTEND          '~'
#define CONSOLEFONTSIZE         (CONSOLEFONTEND - CONSOLEFONTSTART + 1)

#define NOBOLDCOLOR             -1
#define NOBACKGROUNDCOLOR       -1

#define CONSOLEDOWNSIZE         28
#define CONSOLEUPSIZE           12

#define CONSOLEHEIGHT           ((gamestate != GS_TITLESCREEN ? SCREENHEIGHT / 2 : SCREENHEIGHT) - 5)

#define CONSOLELINES            (gamestate != GS_TITLESCREEN ? 13 : 27)
#define CONSOLETEXTX            (vid_widescreen ? 28 : 10)
#define CONSOLETEXTY            8
#define CONSOLETEXTMAXLENGTH    1024
#define CONSOLELINEHEIGHT       14

#define CONSOLESCROLLBARWIDTH   5
#define CONSOLESCROLLBARHEIGHT  (gamestate != GS_TITLESCREEN ? 173 : 369)
#define CONSOLESCROLLBARX       (SCREENWIDTH - CONSOLETEXTX - CONSOLESCROLLBARWIDTH)

#define CONSOLETEXTPIXELWIDTH   (SCREENWIDTH - CONSOLETEXTX * 2 - (scrollbardrawn ? CONSOLESCROLLBARWIDTH + 10 : 0))

#define CONSOLEINPUTX           CONSOLETEXTX
#define CONSOLEINPUTY           (CONSOLEHEIGHT - 16)

#define CONSOLEINPUTPIXELWIDTH  (SCREENWIDTH - CONSOLETEXTX - brandwidth - 2)

#define CONSOLETOP              0

#define OVERLAYTEXTX            (vid_widescreen ? 25 : 8)
#define OVERLAYTEXTY            (vid_widescreen ? 12 : 10)
#define OVERLAYLINEHEIGHT       14
#define OVERLAYSPACING          5

#define WARNINGWIDTH            13

#define EMPTYVALUE              "\"\""

#define stringize(text)         #text

#define BOLDTOGGLE              "\036"
#define BOLDTOGGLECHAR          '\036'
#define ITALICSTOGGLE           "\037"
#define ITALICSTOGGLECHAR       '\037'

#define BOLD(text)              BOLDTOGGLE text BOLDTOGGLE
#define ITALICS(text)           ITALICSTOGGLE text ITALICSTOGGLE
#define BOLDITALICS(text)       ITALICS(BOLD(text))

#if defined(_WIN32)
#define SDL_FILENAME            "SDL2.dll"
#define SDL_MIXER_FILENAME      "SDL2_mixer.dll"
#define SDL_IMAGE_FILENAME      "SDL2_image.dll"
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__HAIKU__)
#define SDL_FILENAME            "SDL2.so"
#define SDL_MIXER_FILENAME      "SDL2_mixer.so"
#define SDL_IMAGE_FILENAME      "SDL2_image.so"
#else
#define SDL_FILENAME            "SDL2"
#define SDL_MIXER_FILENAME      "SDL2_mixer"
#define SDL_IMAGE_FILENAME      "SDL2_image"
#endif

#define BINDLISTHEADER          "\tCONTROL\t+ACTION/COMMAND(S)"
#define CMDLISTHEADER           "\tCCMD\tDESCRIPTION"
#define CVARLISTHEADER          "\tCVAR\tVALUE\tDESCRIPTION"
#define MAPLISTHEADER           "\tMAP\tTITLE\tWAD"
#define MAPSTATSHEADER          "STAT\tVALUE"
#define PLAYERSTATSHEADER       "STAT\tCURRENT MAP\tTOTAL"
#define THINGLISTHEADER         "\tTHING\tPOSITION"

typedef enum
{
    inputstring,
    cheatstring,
    outputstring,
    dividerstring,
    warningstring,
    playermessagestring,
    headerstring,
    STRINGTYPES
} stringtype_t;

typedef struct
{
    char            string[1024];
    int             count;
    int             line;
    stringtype_t    stringtype;
    int             wrap;
    int             indent;
    boolean         bold;
    boolean         italics;
    patch_t         *header;
    int             tabs[3];
    int             tics;
    char            timestamp[9];
} console_t;

extern patch_t      *bindlist;
extern patch_t      *cmdlist;
extern patch_t      *cvarlist;
extern patch_t      *maplist;
extern patch_t      *mapstats;
extern patch_t      *playerstats;
extern patch_t      *thinglist;

extern console_t    *console;

extern boolean      consoleactive;
extern int          consoleheight;
extern int          consoledirection;

extern char         consoleinput[255];
extern int          consolestrings;
extern size_t       consolestringsmax;

extern int          caretpos;
extern int          selectstart;
extern int          selectend;

extern char         consolecheat[255];
extern char         consolecheatparm[3];
extern char         consolecmdparm[255];

extern boolean      scrollbardrawn;

typedef struct
{
    char            *input;
    int             caretpos;
    int             selectstart;
    int             selectend;
} undohistory_t;

typedef struct
{
    char            char1;
    char            char2;
    int             adjust;
} kern_t;

extern const kern_t kern[];
extern const kern_t altkern[];

typedef struct
{
    char            text[255];
    int             game;
} autocomplete_t;

extern autocomplete_t   autocompletelist[];

void C_Input(const char *string, ...);
void C_Cheat(const char *string);
void C_IntCVAROutput(const char *cvar, int value);
void C_PctCVAROutput(const char *cvar, int value);
void C_StrCVAROutput(const char *cvar, const char *string);
void C_Output(const char *string, ...);
boolean C_OutputNoRepeat(const char *string, ...);
void C_TabbedOutput(const int tabs[3], const char *string, ...);
void C_Header(const int tabs[3], patch_t *header, const char *string);
void C_Warning(const int minwarninglevel, const char *string, ...);
void C_PlayerMessage(const char *string, ...);
void C_PlayerObituary(const char *string, ...);
void C_AddConsoleDivider(void);
void C_Init(void);
void C_ShowConsole(void);
void C_HideConsole(void);
void C_HideConsoleFast(void);
void C_Drawer(void);
boolean C_ExecuteInputString(const char *input);
boolean C_ValidateInput(char *input);
boolean C_Responder(event_t *ev);
void C_PrintCompileDate(void);
void C_PrintSDLVersions(void);
void C_UpdateFPSOverlay(void);
void C_UpdateTimerOverlay(void);
void C_UpdatePathOverlay(void);
void C_UpdatePlayerStatsOverlay(void);
char *C_CreateTimeStamp(int index);
void C_ResetWrappedLines(void);
