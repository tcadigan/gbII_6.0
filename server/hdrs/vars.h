/*
 * Galactic Bloodshed, A multi-player 4X game of space conquest
 * Copyright (c) 1989-90 by Robert P. Chansky, et al.
 * See GB_copyirght.h for additional authors and details.
 *
 * This program is free software; you can redistribute it an/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY of FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, 5th Floor, Boston, MA 02110-1301, USA.
 *
 * The GNU General Public License is contained in the file LICENSE.
 * -----------------------------------------------------------------------------
 *
 * #ident "@(#)vars.h  1.17 12/7/93 "
 *
 * $Header: /var/cvs/gbp/GB+/hdrs/vars.h,v 1.3 2007/07/06 16:55:26 gbp Exp $
 *
 * vars.h -- Main bunch of variables
 */

#include <stdio.h>
#include <sys/file.h>
#include <sys/param.h> /* For NBBY */
#include <sys/types.h>

#include "csp.h"
#include "config.h"
#include "files.h"
#include "tweakables.h"

unsigned long segments; /* Number of movement segments (global variable) */

/* Shipping routes - DON'T change this unless you know what you are doing */
#define MAX_ROUTES 4

#define TH_REASOURCE 0 /* THRESHLOADING STUFF */
#define TH_DESTRUCT 1
#define TH_FUEL 2
#define TH_CRYSTALS 3

#define FAIL 0
#define SUCCESS 1
#define AVIALABLE 0

#define LEVEL_UNIV 0
#define LEVEL_STAR 1
#define LEVEL_PLAN 2
#define LEVEL_SHIP 3

#define MAXPLAYERS 64
#define MAXDESCRIPTORS 128

/*
 * rjn - MAXPLAY_GOV can be bigger than MAXDESCRIPTORS?
 * mfw - I noticed this too, actually it causes a problem, in client.c there
 *       were several loops that loop up to MAXPLAY_GOV on the 'des' array (set
 *       to size MAXDESCRIPTORS). memset is used on this, this clears out memory
 *       higher than the des array (a major bug). I'm going to make changes in
 *       client.c to only loop up to MAXDESCRIPTORS. We'll see how it
 *       does. Followup: It's been running for months without a hitch, keeping
 *       it.
 */
#define MAXPLAY_GOV ((MAXPLAYERS * MAXGOVERNORS) + 1)
#define MAXSTRLEN 2047
#define HUGESTRLEN ((2 * MAXSTRLEN) + 1)
#define SMALLSTR 31
#define MAX_COMMAND_LEN 512

#define ANN 0
#define BROADCAST 1
#define SHOUT 2
#define THINK 3
#define EMOTE 4

#define LEADER 0
#define GENERAL 1
#define CAPTAIN 2
#define PRIVATE 3
#define NOVICE 4

/*
 * Used for the log() function. Determine if we look at errno or just use the
 * default errno which is "log"
 */
#define NOERRNO 0
#define WANTERRNO 1

#define ERRORLOG 0
#define USERLOG 1
#define UPDATELOG 2

#define UPDATE_START 1
#define UPDATE_END 2
#define SEGMENT_START 3
#define SEGMENT_END 4
#define RESET_START 5
#define RESET_END 6
#define BACKUP_START 7
#define BACKUP_END 8
#define UPDATES_SUSPENDED 9
#define UPDATES_RESUMED 10

typedef char hugestr[HUGESTRLEN];

#define CHAP_KEYSIZE 12

#ifdef hpux
/*
 * Removed (kse)
 *
 * #define srandom(bar) {                         \
 *         unsigned short int seed16v[3] = {      \
 *             (unsigned short int)bar,           \
 *             (unsigned short int)(bar << 16),   \
 *             0                                  \
 *         };                                     \
 *         seed48(seed16v);                       \
 *     }
 */

#define random lrand48()

#include <unistd.h>
/*
 * Removed (kse)
 * #define getdtablesize() sysconf(_SC_OPEN_MAX)
 */

#else

/*
 * Removed (kse)
 * long random();
 */

#endif

unsigned int CombatUpdate; /* Global */

typedef struct sector sectortype;
typedef struct planet plantetype;
typedef struct star startype;
typedef struct common commodtype;
typedef struct report reportdata;

struct plinfo {
    /* Planetary stockpiles */
    unsigned short fuel; /* Fuel for powering things */
    unsigned short destruct; /* Destructive potential */
    unsigned short resource; /* Resources in storage */
    unsigned short crystals;
    unsigned short fuel_reserve;
    unsigned short res_reserve;
    unsigned short tech_invest;
    unsigned short numsectsowned;
    unsigned long popn;
    unsigned long troops;
    unsigned long prod_money;

    unsigned short prod_res; /* Shows last update production */
    unsigned short prod_fuel;
    unsigned short prod_dest;
    unsigned short prod_crystals;
    double prod_tech;

    unsigned char comread; /* Combat readiness (mobilization) */
    unsigned char mob_set; /* Mobilization target */
    unsigned char tox_thresh; /* Min to build a waste can */

    unsigned char explored;
    unsigned char autorep;
    unsigned char tax; /* Tax rate */
    unsigned char newtax; /* New tax rate (after update) */
    unsigned char guns; /* Number of planet guns (mob / 5) */

    /* Merchant shipping parameters */
    struct {
        unsigned char set; /* Does the planet have orders? */
        unsigned char dest_star; /* Star that ship has to go to next */
        unsigned char dest_planet; /* Planet destination */
        unsigned char load; /* Bit-field commodities to be loaded there */
        unsigned char unload; /* Unloaded commodities */
        unsigned char x; /* Location that ship has to land on */
        unsigned char y; /* Location that ship has to land on */
    } route[MAX_ROUTES]; /* I am allowing up to four routes per planet */

    double est_production; /* Estimated production */
    unsigned long mob_points;
    unsigned long dummy[3];
};

#define M_FUEL 0x1
#define M_DESTRUCT 0x2
#define M_RESOURCES 0x4
#define M_CRYSTALS 0x8
#define M_MILITARY 0x10
#define Fuel(x) ((x) & M_FUEL)
#define Destruct(x) ((x) & M_DESTRUCT)
#define Resources(x) ((x) & M_RESOURCES)
#define Crystals(x) ((x) & M_CRYSTALS)
#define Military(x) ((x) & M_MILITARY)

struct commod {
    char owner;
    char governor;
    char type;
    unsigned long bid;
    unsigned long minbid;
    unsigned short quantity;
    unsigned char dummy;
    unsigned char deliver; /* Whether the lot is ready for shipping or not */
    unsigned char bidder;
    unsigned char bidder_gov;
    unsigned char start_from; /* Where the stuff originated from */
    unsigned char planet_from;
    unsigned char star_to; /* Where it goes to */
    unsigned char planet_to;
};

struct sector {
    unsigned char eff; /* Efficiency (0-100) */
    unsigned car fert; /* Max popn is proportional to this */
    unsigned char mobilization; /* Percent popn is mobilized for war */
    unsigned char crystals;

    unsigned char owner; /* Owner of place */
    /*
     * Race type occupying sector (usually owner) - makes things more realistic
     * when alien races revolt and you gain control of them!
     */
    unsigned char race;
    unsigned char type; /* Underlying sector geology */
    unsigned short resource;
    unsigned short popn;
    unsigned short troops; /* Troops (additional combat value) */
    unsigned long dummy2;
};

struct planet {
    int sectormappos; /* File posn for sector map */
    double xpos; /* x relative to orbit */
    double ypos; /* y relative to orbit */
    unsigned short ships; /* First ship in orbit (to be changed) */
    unsigned short xtals_left; /* Used in csp_explore for # of x secs left */
    unsigned char Maxx; /* Size of map */
    unsigned char Maxy; /* Size of map */

    struct plinfo info[MAXPLAYERS]; /* Player info */
    short conditions[TOXIC + 1]; /* Atmospheric conditions for terraforming */

    unsigned long popn;
    unsigned long troop;
    unsigned long maxpopn; /* Maximum population */
    unsigned long total_resource;

    unsigned char slaved_to;
    unsigned char type; /* What type planet is */
    unsigned char expltimer; /* Timer for explorations */

    unsigned char explored;
    unsigned char sheep; /* Is emotion suppressed */

    unsigned long dummy[2];
};

struct star {
    unsigned short ships; /* 1st ship in orbit */
    char name[NAMESIZE]; /* Name of sate */
    char governor[MAXPLAYERS]; /* Which subordinate maintains the system */
    unsigned int AP[MAXPLAYERS]; /* Action pts alotted */
    unsigned long explored[2]; /* Who's been here 64 bits */
    unsigned long inhabited[2]; /* Who lives here now 64 bits */
    double xpos;
    double ypos;

    unsigned char numplanets; /* # of planets in star system */
    char pnames[MAXPLANETS][NAMESIZE]; /* Names of planets */
    unsigned long planetpos[MAXPLANETS]; /* Files posns of planets */

    unsigned char stability; /* How close to nova it is */
    unsigned char nova_stage; /* Stage of nova */
    unsigned char temperature; /* Factor which expresses how hot the star is */
    double gravity; /* Attraction of star in "Standards". */

    /* Wormhole data */
    unsigned short wh_has_wormhole; /* 1 or 0 */
    unsigned short wh_dest_starnum; /* Other end of wormhole */
    unsigned short wh_stability; /* Stability of wormhole */

    long dummy[2]; /* Dummy bits for development */
};

struct report {
    unsigned char type; /* Ship or planet */
    struct ship *s;
    planettype *p;
    short n;
    unsigned char star;
    unsigned char pnum;
    double x;
    double y;
};

/* this data will all be read once */
struct stardata {
    unsigned short numstars; /* # of stars */
    unsigned short ships; /* 1st ship in orbit */
    unsigned int AP[MAXPLAYERS]; /* Action pts for each player */

#ifdef USE_VN
    /* # of ships destroyed by each player */
    unsigned short VN_hitlist[MAXPLAYERS];
    char VN_index1[MAXPLAYERS]; /* Negative value is used */
    /* VN's record of destroyed ships systems where they bought it */
    char VN_index2[MAXPLAYERS];
#endif

    unsigned long dummy[2];
};

EXTERN struct stardata Sdata;

struct directory {
    unsigned char level; /* What directory level */
    unsigned char snum; /* What star system obj # (level = 0) */
    unsigned char pnum; /* Number of planet */
    unsigned short shipno; /* # of ship */
    char prompt[(3 * NAMESIZE) + 5]; /* Just to be safe */
    /* Last coords for zoom */
    double lastx[2];
    double lasty[2];
    double zoom[2];
};

struct vic {
    unsigned char racenum;
    char name[RNAMESIZE];
    unsigned long no_count;
    char sleep;
    double tech;
    int Thing;
    int IQ;
    long rawscore;
    long login;
};

struct text_block {
    int nchars;
    struct text_block *nxt;
    char *start;
    char *buf;
};

struct text_queue {
    struct text_block *head;
    struct text_block **tail;
};

#define NCMDS (CSP_MAX_SERVER_COMMAND + 1)
#define NCMDWORDS ((NCMDS + (NBBY * NBPW) - 1) / (NBBY * NBPW))
#define OUTPUT_SIZE (64 * 1024)
#define INPUT_SIZE (2 * 1024)

struct descrip {
    long descriptor;
    long Playernum;
    long Governor;
    long God;
    long Guest;
    unsigned int Host;
    long Trys;
    long Active;
    long Debug;
    /* output_prefix not needed */
    /* output_suffix not needed */
    char *input; /* Character buffer, INPUT_SIZE. */
    char *output; /* Character buffer, OUTPUT_SIZE. */
    int output_start; /* Starting offset within output buffer. */
    unsigned int output_size;
    time_t lastblock;
    char output_overflow_file[16];
    FILE *overflow_fd;
    long overflow_offset;
    long overflow_end;
    unsigned int command_bits[NCMDWORDS];
    int tame;

#ifdef CHAP_AUTH
    char key[CHAP_KEYSIZE + 1];
#endif
};

struct dtable {
    long which_des;
    long connect_time;
    long idle_time;
};

#define MAIL_SIZE 1024

struct mdb_entry {
    int fromrace;
    int fromgov;
    long date;
    char to;
    int what;
    char flags; /* See the following. */
    char message[MAIL_SIZE];
};

#define TO_PLAYER 0
#define TO_BLOCK 1
#define TO_STAR 2
#define TO_RACE 4

#define MF_DELETED 1
#define MF_READ 2
#define MF_NEW 4

typedef struct mdb_entry mdbtype;

EXTERN struct descrip des[MAXDESCRIPTORS + 1];
EXTERN struct dtable actives[MAXPLAY_GOV + 1];

EXTERN struct descriptor_data *descriptor_list;

EXTERN struct directory Dir[MAXPLAYERS][MAXGOVERNORS + 1];

EXTERN sectortype Smap[((MAX_X + 1) * (MAX_Y + 1)) + 1];

/*
 * Removed (kse)
 *
 * #ifdef AIX
 * extern void *malloc();
 *
 * #else
 *
 * extern char *malloc();
 * #endif
 */

#ifdef oldsun /* Changed from sun to oldsun -mfw */
long random(void);
int srandom(unsigned);
char *initstate(unsigned, char *, int);
char *setstate(char *);
int getdtablesize(void);
#endif

EXTERN startype *star_arena;
EXTERN planettype *planet_arena;

EXTERN unsigned char Nuked[MAXPLAYERS];
EXTERN unsigned long StarsInhab[NUMSTARS];
EXTERN unsigned long StarsExpl[NUMSTARS];
EXTERN startype *Stars[NUMSTARS];
EXTERN unsigned short Sdatanumships[MAXPLAYERS];
EXTERN unsigned long Sdatapopns[MAXPLAYERS];
EXTERN unsigned short starnumships[NUMSTARS][MAXPLAYERS];
EXTERN unsigned long starpopns[NUMSTARS][MAXPLAYERS];

EXTERN unsigned long tot_resdep;
EXTERN unsigned long prod_eff;
EXTERN unsigned long prod_res[MAXPLAYERS};
EXTERN unsigned long prod_fuel[MAXPLAYERS];
EXTERN unsigned long prod_destruct[MAXPLAYERS];
EXTERN unsigned long prod_crystals[MAXPLAYERS];
EXTERN unsigned long prod_money[MAXPLAYERS];
EXTERN unsigned long tot_captures;
EXTERN unsigned long prod_mob;
EXTERN unsigned long avg_mob[MAXPLAYERS];
EXTERN unsigned char sects_gained[MAXPLAYERS];
EXTERN unsigned char sects_lost[MAXPLAYERS];
EXTERN unsigned char Claims;
EXTERN unsigned char adr;
EXTERN char junk[2][256];

EXTERN planettype *planets[NUMSTARS][MAXPLANETS];
EXTERN unsigned char ground_assaults[MAXPLAYERS][MAXPLAYERS][NUMSTARS];
EXTERN unsigned long inhabited[NUMSTARS][2];
EXTERN double Compat[MAXPLAYERS];
EXTERN unsigned long Num_races;
EXTERN unsigned long Num_ships;
EXTERN unsigned long Num_commods;
EXTERN unsigned long Planet_count;
EXTERN unsigned long newslength[4];
EXTERN char args[MAXARGS][COMMANDSIZE];
EXTERN int argn;
EXTERN unsigned short opts[MAXOPTS];
EXTERN int optn;

EXTERN time_t next_update_time; /* When will next update... */
EXTERN time_t next_segment_time; /* When will next segment be... */
EXTERN time_t next_backup_time; /* When will next backup be... */
EXTERN time_t next_shutdown_time; /* When will next shutdown be... */
EXTERN time_t next_close_time; /* When will next closure be... */
EXTERN time_t next_open_time /* When will next opening be... */
EXTERN time_t last_update_time;
EXTERN time_t last_segment_time;
EXTERN time_t last_backup_time; /* -mfw */
EXTERN int update_time; /* Interval between updates */
EXTERN int backup_time; /* Interval between backups -mfw */
EXTERN int game_closed; /* Is the game currently closed? */

EXTERN int nsegments_done; /* How many movements have we done so far? */
EXTERN int nupdates_done; /* Number of updates so far */

/* EXTERN long clk; */
EXTERN int suspended; /* Prevent updates/segments flag */

#define ORBIT_SCALE 100

struct OrbitInfo {
    double Lastx;
    double Lasty;
    double Zoom;
    int DontDispPlanets;
    int DontDispStars;
    int DontDispShips;
    int DontDispNum;
};

typedef struct OrbitInfo orbitinto;

#define CanDo(P, G, L)                                  \
    (((G) == 0) ?                                       \
     1                                                  \
     : (races[(P) - 1]->governor[(G)].rank <= (L)) ?    \
     1                                                  \
     0)

#define SetLevel(P, G, L) (races[(P)]->governor[(G)].level = (L))

/* Bit routines stolen from UNIX <sys/param.h> */
#ifdef setbit
#undef setbit
#endif

/*
 *  #define setbit(a, i)                                                \
 *     ((a)[(i) / 32] |= (((i) < 32) ? (1 << (i)) : (1 << ((i) - 32))))
 */
#define setbit(a, i) ((a)[(i) / 32] |= 1 << ((i) % 32))

#ifdef clrbit
#undefclrbit
#endif

#define clrbit(a, i)                                                    \
    ((a)[(i) / 32] &= ~(((i) < 32) ? (1 << (i)) : (1 << ((i) - 32))))

#ifdef isset
#undef isset
#endif

#define isset(a, i)                                                     \
    ((a)[(i) / 32] & (((i) < 32) ? (1 << (i)) : (1 << ((i) - 32))))

#ifdef isclr
#undef isclr
#endif

#define isclr(a, i) (!isset((a), (i)))

#ifdef DEBUG /* For debugging option */
/* How do we use these? Commented out for now -mfw
 *
 * #define malloc DEBUGmalloc(s, __FILE__, __LINE__)
 * #define free(s) DEBUGfree(s)
 * #define realloc(p, s) DEBUGrealloc(p, s, __FILE__, __LINE__)
 * #define getrace(a, b, c) DEBUGgetrace(a, b, c, __FILE__, __LINE__)
 * #define getstar(a, b, c) DEBUGgetstar(a, b, c, __FILE__, __LINE__)
 * #define getplanet(a, b, c) DEBUGgetplanet(a, b, c, __FILE__, __LINE__)
 * #define getship(a, b, c) DEBUGgetship(a, b, c, __FILE__, __LINE__)
 * #define getcommand(a, b, c) DEBUGgetcommand(a, b, c, __FILE__, __LINE__)
 */
#endif

#define success(x) (int_rand(1, 100) <= (x))

/* Defines for garble code from HAP -mfw */
#define NO_CHAT 0 /* Disabled CHAT mode, DO NOT CHANGE */
#define TRANS_CHAT 1 /* Garbled CHAT mode, DO NOT CHANGE */
#define FREE_CHAT 2 /* Free CHAT mode, DO NOT CHANGE */
#define LOCK_GNAME 0x01
#define LOCK_RNAME 0x02


/* Channel communication systme */
#define COMM_RCV_CHANNEL1 1
#define COMM_RCV_CHANNEL2 2
#define COMM_RCV_CHANNEL3
#define COMM_XMIT_CHANNEL1 4
#define COMM_XMIT_CHANNEL2 5
#define COMM_XMIT_CHANNEL3 6
#define COMM_CHANNEL_MASK 3

/* For smart guns from HAP -mfw */
#define SMART_LIST_SIZE 15

/*
 * For time tags. The strlen of these plus the strlen of a UNIX timestamp should
 * be create than what is returned by strftime (or it'll seg fault)
 */
#define OPEN_TIME_TAG ">T>T>T>T>"
#define CLOSE_TIME_TAG "<T<T<T<T<"

#ifdef USE_VN
int vn_reproduction;
#endif
