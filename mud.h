/****************************************************************************
 *                           STAR WARS REALITY 1.0                          *
 *--------------------------------------------------------------------------*
 * Star Wars Reality Code Additions and changes from the Smaug Code         *
 * copyright (c) 1997, 1998 by Sean Cooper                                  *
 * -------------------------------------------------------------------------*
 * Starwars and Starwars Names copyright (c) Lucasfilm Ltd.                 *
 *--------------------------------------------------------------------------*
 * SMAUG 1.0 (C) 1994, 1995, 1996 by Derek Snider                           *
 * SMAUG code team: Thoric, Altrag, Blodkai, Narn, Haus,                    *
 * Scryn, Rennard, Swordbearer, Gorog, Grishnakh and Tricops                *
 * ------------------------------------------------------------------------ *
 * Merc 2.1 Diku Mud improvments copyright (C) 1992, 1993 by Michael        *
 * Chastain, Michael Quan, and Mitchell Tse.                                *
 * Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,          *
 * Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.     *
 * ------------------------------------------------------------------------ *
 *                            Main mud header file                          *
 ****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <sys/cdefs.h>
#include <sys/time.h>

#ifndef __cplusplus
typedef unsigned char bool;
#endif

typedef int ch_ret;
typedef int obj_ret;

#define args( list )			list

#ifdef __cplusplus
#define DECLARE_DO_FUN( fun )    extern "C" { DO_FUN    fun; } DO_FUN fun##_mangled
#define DECLARE_SPEC_FUN( fun )  extern "C" { SPEC_FUN  fun; } SPEC_FUN fun##_mangled
#define DECLARE_SPELL_FUN( fun ) extern "C" { SPELL_FUN fun; } SPELL_FUN fun##_mangled
#else
#define DECLARE_DO_FUN( fun )     DO_FUN    fun; DO_FUN fun##_mangled
#define DECLARE_SPEC_FUN( fun )   SPEC_FUN  fun; SPEC_FUN fun##_mangled
#define DECLARE_SPELL_FUN( fun )  SPELL_FUN fun; SPELL_FUN fun##_mangled
#endif

/*
* Short scalar types.
* Diavolo reports AIX compiler has bugs with short types.
*/
#if !defined(FALSE)
#define FALSE 0
#endif

#if !defined(TRUE)
#define TRUE 1
#endif

#if !defined(BERR)
#define BERR 255
#endif

#define KEY( literal, field, value )   \
   if ( !str_cmp( word, (literal) ) )     \
{                                      \
   (field) = (value);                  \
   fMatch = TRUE;                      \
   break;                              \
}

/*
* Structure types.
*/
typedef struct affect_data AFFECT_DATA;
typedef struct area_data AREA_DATA;
typedef struct auction_data AUCTION_DATA; /* auction data */
typedef struct ban_data BAN_DATA;
typedef struct extracted_char_data EXTRACT_CHAR_DATA;
typedef struct char_data CHAR_DATA;
typedef struct hunt_hate_fear HHF_DATA;
typedef struct fighting_data FIGHT_DATA;
typedef struct descriptor_data DESCRIPTOR_DATA;
typedef struct exit_data EXIT_DATA;
typedef struct extra_descr_data EXTRA_DESCR_DATA;
typedef struct help_data HELP_DATA;
typedef struct mob_index_data MOB_INDEX_DATA;
typedef struct note_data NOTE_DATA;
typedef struct board_data BOARD_DATA;
typedef struct obj_data OBJ_DATA;
typedef struct obj_index_data OBJ_INDEX_DATA;
typedef struct pc_data PC_DATA;
typedef struct reset_data RESET_DATA;
typedef struct room_index_data ROOM_INDEX_DATA;
typedef struct shop_data SHOP_DATA;
typedef struct repairshop_data REPAIR_DATA;
typedef struct time_info_data TIME_INFO_DATA;
typedef struct hour_min_sec HOUR_MIN_SEC;
typedef struct weather_data WEATHER_DATA;
typedef struct bounty_data BOUNTY_DATA;
typedef struct planet_data PLANET_DATA;
typedef struct guard_data GUARD_DATA;
typedef struct space_data SPACE_DATA;
typedef struct clan_data CLAN_DATA;
typedef struct senate_data SENATE_DATA;
typedef struct ship_data SHIP_DATA;
typedef struct missile_data MISSILE_DATA;
typedef struct mob_prog_data MPROG_DATA;
typedef struct mob_prog_act_list MPROG_ACT_LIST;
typedef struct editor_data EDITOR_DATA;
typedef struct teleport_data TELEPORT_DATA;
typedef struct timer_data TIMER;
typedef struct system_data SYSTEM_DATA;
typedef struct smaug_affect SMAUG_AFF;
typedef struct who_data WHO_DATA;
typedef struct skill_type SKILLTYPE;
typedef struct social_type SOCIALTYPE;
typedef struct cmd_type CMDTYPE;
typedef struct killed_data KILLED_DATA;
typedef struct wizent WIZENT;
typedef struct specfun_list SPEC_LIST;
typedef struct extended_bitvector EXT_BV;
typedef struct group_data GROUP_DATA;
typedef struct loot_data LOOT_DATA;
typedef struct threat_data THREAT_DATA;
typedef struct queue_timers QTIMER;
typedef struct cooldown_data CD_DATA;
typedef struct discipline_data DISC_DATA;
typedef struct factor_data FACTOR_DATA;
typedef struct stat_boost STAT_BOOST;
typedef struct teach_data TEACH_DATA;
typedef struct quest_data QUEST_DATA;
typedef struct player_quest PLAYER_QUEST;
typedef struct available_quest AV_QUEST;
typedef struct pre_quest PRE_QUEST;
typedef struct item_material ITEM_MATERIAL;
typedef struct pool_data POOL_DATA;
/*
* Function types.
*/
typedef void DO_FUN( CHAR_DATA * ch, const char *argument );
typedef bool SPEC_FUN( CHAR_DATA * ch );
typedef ch_ret SPELL_FUN( int sn, int level, CHAR_DATA * ch, void *vo );

#define DUR_CONV	23.333333333333333333333333
#define HIDDEN_TILDE	'*'

#define BV00		(1 <<  0)
#define BV01		(1 <<  1)
#define BV02		(1 <<  2)
#define BV03		(1 <<  3)
#define BV04		(1 <<  4)
#define BV05		(1 <<  5)
#define BV06		(1 <<  6)
#define BV07		(1 <<  7)
#define BV08		(1 <<  8)
#define BV09		(1 <<  9)
#define BV10		(1 << 10)
#define BV11		(1 << 11)
#define BV12		(1 << 12)
#define BV13		(1 << 13)
#define BV14		(1 << 14)
#define BV15		(1 << 15)
#define BV16		(1 << 16)
#define BV17		(1 << 17)
#define BV18		(1 << 18)
#define BV19		(1 << 19)
#define BV20		(1 << 20)
#define BV21		(1 << 21)
#define BV22		(1 << 22)
#define BV23		(1 << 23)
#define BV24		(1 << 24)
#define BV25		(1 << 25)
#define BV26		(1 << 26)
#define BV27		(1 << 27)
#define BV28		(1 << 28)
#define BV29		(1 << 29)
#define BV30		(1 << 30)
#define BV31		(1 << 31)
/* 32 USED! DO NOT ADD MORE! SB */

/*
* String and memory management parameters.
*/
#define MAX_KEY_HASH		 2048
#define MAX_STRING_LENGTH	12288 /* buf */
#define MAX_INPUT_LENGTH	 2024 /* arg */
#define MAX_INBUF_SIZE		 2024

#define HASHSTR   /* use string hashing */

#define	MAX_LAYERS		 8 /* maximum clothing layers */
#define MAX_NEST	       100  /* maximum container nesting */

#define MAX_KILLTRACK		20 /* track mob vnums killed */

/*
* Game parameters.
* Increase the max'es if you add more of something.
* Adjust the pulse numbers to suit yourself.
*/
#define MAX_EXP_WORTH	       500000
#define MIN_EXP_WORTH		   25

#define MAX_REXITS		   20 /* Maximum exits allowed in 1 room */
#define MAX_SKILL		  276
#define MAX_ABILITY		    8
#define MAX_RACE		   17
#define MAX_NPC_RACE		   91
#define MAX_LEVEL		  105
#define MAX_CLASS_LEVEL           150
#define MAX_CLAN		   50
#define MAX_PLANET		  100
#define MAX_SHIP                 1000
#define MAX_BOUNTY                255
#define MAX_GOV                   255

#define	MAX_HERB		   20

#define LEVEL_HERO		   (MAX_LEVEL - 5)
#define LEVEL_IMMORTAL		   (MAX_LEVEL - 4)
#define LEVEL_SUPREME		   MAX_LEVEL
#define LEVEL_INFINITE		   (MAX_LEVEL - 1)
#define LEVEL_ETERNAL		   (MAX_LEVEL - 1)
#define LEVEL_IMPLEMENTOR	   (MAX_LEVEL - 1)
#define LEVEL_SUB_IMPLEM	   (MAX_LEVEL - 1)
#define LEVEL_ASCENDANT		   (MAX_LEVEL - 2)
#define LEVEL_GREATER		   (MAX_LEVEL - 2)
#define LEVEL_GOD		   (MAX_LEVEL - 2)
#define LEVEL_LESSER		   (MAX_LEVEL - 3)
#define LEVEL_TRUEIMM		   (MAX_LEVEL - 3)
#define LEVEL_DEMI		   (MAX_LEVEL - 3)
#define LEVEL_SAVIOR		   (MAX_LEVEL - 3)
#define LEVEL_CREATOR		   (MAX_LEVEL - 3)
#define LEVEL_ACOLYTE		   (MAX_LEVEL - 4)
#define LEVEL_NEOPHYTE		   (MAX_LEVEL - 4)
#define LEVEL_AVATAR		   (MAX_LEVEL - 5)

#include "hotboot.h"

#define LEVEL_LOG		    LEVEL_LESSER
#define LEVEL_HIGOD		    LEVEL_GOD

#define PULSE_PER_SECOND	    4
#define PULSE_MINUTE              ( 60 * PULSE_PER_SECOND)
#define PULSE_VIOLENCE		  (  3 * PULSE_PER_SECOND)
#define PULSE_MOBILE		  (  4 * PULSE_PER_SECOND)
#define PULSE_TICK		  ( 70 * PULSE_PER_SECOND)
#define PULSE_AREA		  ( 60 * PULSE_PER_SECOND)
#define PULSE_AUCTION             ( 10 * PULSE_PER_SECOND)
#define PULSE_SPACE               ( 10 * PULSE_PER_SECOND)
#define PULSE_TAXES               ( 60 * PULSE_MINUTE)

/* 
 * Stuff for area versions --Shaddai
 */
#define HAS_SPELL_INDEX     -1

/*
Old Smaug area version identifiers:

Version 1: Stock 1.4a areas.
Version 2: Skipped - Probably won't ever see these, but originated from Smaug 1.8.
Version 3: Stock 1.8 areas.
*/

// This value has been reset due to the new KEY/Value based area format.
// It will not conflict with the above former area file versions.
#define AREA_VERSION_WRITE 1

/*
* Command logging types.
*/
typedef enum
{
   LOG_NORMAL, LOG_ALWAYS, LOG_NEVER, LOG_BUILD, LOG_HIGH, LOG_COMM, LOG_ALL
} log_types;

/* short cut crash bug fix provided by gfinello@mail.karmanet.it*/
typedef enum
{
   relMSET_ON, relOSET_ON
} relation_type;

typedef struct rel_data REL_DATA;

struct rel_data
{
   void *Actor;
   void *Subject;
   REL_DATA *next;
   REL_DATA *prev;
   relation_type Type;
};

/*
* Return types for move_char, damage, greet_trigger, etc, etc
* Added by Thoric to get rid of bugs
*/
typedef enum
{
   rNONE, rCHAR_DIED, rVICT_DIED, rBOTH_DIED, rCHAR_QUIT, rVICT_QUIT,
   rBOTH_QUIT, rSPELL_FAILED, rOBJ_SCRAPPED, rOBJ_EATEN, rOBJ_EXPIRED,
   rOBJ_TIMER, rOBJ_SACCED, rOBJ_QUAFFED, rOBJ_USED, rOBJ_EXTRACTED,
   rOBJ_DRUNK, rCHAR_IMMUNE, rVICT_IMMUNE, rCHAR_AND_OBJ_EXTRACTED = 128,
   rERROR = 255
} ret_types;

/* Echo types for echo_to_all */
#define ECHOTAR_ALL	0
#define ECHOTAR_PC	1
#define ECHOTAR_IMM	2

/* defines for new do_who */
#define WT_MORTAL 0
#define WT_IMM    2
#define WT_AVATAR 1
#define WT_NEWBIE 3

/*
 * Defines for extended bitvectors
 */
#ifndef INTBITS
#define INTBITS 32
#endif
#define XBM             31 /* extended bitmask   ( INTBITS - 1 )  */
#define RSV             5  /* right-shift value  ( sqrt(XBM+1) )  */
#define XBI             4  /* integers in an extended bitvector   */
#define MAX_BITS        XBI * INTBITS
/*
 * Structure for extended bitvectors -- Thoric
 */
struct extended_bitvector
{
   unsigned int bits[XBI];
};



#include "dns.h"
#include "color.h"
#ifdef IMC
#include "imc.h"
#endif

/*
 * Creating a timer that is queued and runs every pulse of the CPU
 * Basically, this is giving us more accuracy in our ability to generate
 * and reduce cooldowns without dragging too much on the processing %
 *-Davenge
 */
struct queue_timers
{
   QTIMER *next;
   QTIMER *prev;
   CHAR_DATA *timer_ch;
   int type;
};


/*
 * Quest Structure for Global Outline for a Quest -Davenge
 */
typedef enum
{
   QUEST_TYPE_ONETIME, QUEST_TYPE_REPEATABLE, MAX_QUESTTYPE
} quest_type;


struct quest_data
{
   QUEST_DATA *next; /* For navigating the global linked list of quests */
   QUEST_DATA *prev;
   int id;
   const char *name;
   const char *description;
   int level_req; /* Required level */
   int type; /* see types below */
   PRE_QUEST *first_prequest;
   PRE_QUEST *last_prequest;
};

/*
 * Quest Structure for a Players Individual Quest -Davenge
 */

struct player_quest
{
   PLAYER_QUEST *next; /* For navigating the linked list within' the CHAR_DATA */
   PLAYER_QUEST *prev;
   QUEST_DATA *quest; /* This points to the global quest_data that contains the quests name */
   int stage;
   int times_completed;
   const char *progress;
};

#define QUEST_UNSTARTED            0
#define QUEST_START                1
#define QUEST_COMPLETE             -1
#define QUEST_COMPLETE_REPEATABLE  -2
#define QUEST_COMMAND_LEVEL        103

struct available_quest
{
   AV_QUEST *next;
   AV_QUEST *prev;
   QUEST_DATA *quest;
};

struct pre_quest
{
   PRE_QUEST *next;
   PRE_QUEST *prev;
   QUEST_DATA *quest;
};


/*
 * Need a way to tell what timer the queue timer is cast to
 * -Davenge
 */

#define COMBAT_LAG_TIMER    0
#define COOLDOWN_TIMER      1
#define AFFECT_TIMER        2
#define TIMER_TIMER         3
#define COMBAT_ROUND        4
#define AI_TIMER            5

struct cooldown_data
{
   CD_DATA *next;
   CD_DATA *prev;
   const char *message;
   int sn;
   double time_remaining;
};

struct teach_data
{
   TEACH_DATA *next;
   TEACH_DATA *prev;
   int disc_id;
   int credits;

};

/*
* do_who output structure -- Narn
*/
struct who_data
{
   WHO_DATA *prev;
   WHO_DATA *next;
   const char *text;
   int type;
};

/*
* Site ban structure.
*/
struct ban_data
{
   BAN_DATA *next;
   BAN_DATA *prev;
   const char *name;
   int level;
   const char *ban_time;
};


/*
* Time and weather stuff.
*/
typedef enum
{
   SUN_DARK, SUN_RISE, SUN_LIGHT, SUN_SET
} sun_positions;

typedef enum
{
   SKY_CLOUDLESS, SKY_CLOUDY, SKY_RAINING, SKY_LIGHTNING
} sky_conditions;

struct time_info_data
{
   int hour;
   int day;
   int month;
   int year;
};

struct hour_min_sec
{
   int hour;
   int min;
   int sec;
   int manual;
};

struct weather_data
{
   int mmhg;
   int change;
   int sky;
   int sunlight;
};


/*
* Structure used to build wizlist
*/
struct wizent
{
   WIZENT *next;
   WIZENT *last;
   const char *name;
   short level;
};


/*
* Connected state for a channel.
*/
typedef enum
{
   CON_GET_NAME = -99,
   CON_GET_OLD_PASSWORD, CON_CONFIRM_NEW_NAME,
   CON_GET_NEW_PASSWORD, CON_CONFIRM_NEW_PASSWORD,
   CON_GET_NEW_SEX, CON_GET_NEW_BUILD, CON_GET_NEW_CLASS, CON_READ_MOTD,
   CON_GET_NEW_RACE, CON_GET_EMULATION, CON_GET_MSP,
   CON_ROLL_STATS, CON_STATS_OK,
   CON_GET_WANT_RIPANSI, CON_TITLE, CON_PRESS_ENTER,
   CON_WAIT_1, CON_WAIT_2, CON_WAIT_3,
   CON_ACCEPTED, CON_GET_PKILL, CON_READ_IMOTD,
   CON_COPYOVER_RECOVER, CON_PLAYING = 0, CON_EDITING
} connection_types;

/*
* Character substates
*/
typedef enum
{
   SUB_NONE, SUB_PAUSE, SUB_PERSONAL_DESC, SUB_OBJ_SHORT, SUB_OBJ_LONG,
   SUB_OBJ_EXTRA, SUB_MOB_LONG, SUB_MOB_DESC, SUB_ROOM_DESC, SUB_ROOM_EXTRA,
   SUB_ROOM_EXIT_DESC, SUB_WRITING_NOTE, SUB_MPROG_EDIT, SUB_HELP_EDIT,
   SUB_WRITING_MAP, SUB_PERSONAL_BIO, SUB_REPEATCMD, SUB_RESTRICTED,
   /*
   * timer types ONLY below this point 
   */
   SUB_TIMER_DO_ABORT = 128, SUB_TIMER_CANT_ABORT
} char_substates;

/*
* Descriptor (channel) structure.
*/
struct descriptor_data
{
   DESCRIPTOR_DATA *next;
   DESCRIPTOR_DATA *prev;
   DESCRIPTOR_DATA *snoop_by;
   CHAR_DATA *character;
   CHAR_DATA *original;
   struct mccp_data *mccp; /* Mud Client Compression Protocol */
   bool can_compress;
   const char *host;
   const char *hostip;
   int port;
   int descriptor;
   short connected;
   short idle;
   short lines;
   short scrlen;
   bool fcommand;
   char inbuf[MAX_INBUF_SIZE];
   char incomm[MAX_INPUT_LENGTH];
   char inlast[MAX_INPUT_LENGTH];
   int repeat;
   char *outbuf;
   unsigned long outsize;
   int outtop;
   char *pagebuf;
   unsigned long pagesize;
   int pagetop;
   const char *pagepoint;
   char pagecmd;
   char pagecolor;
   int newstate;
   unsigned char prevcolor;
   int ifd;
   pid_t ipid;
};

/*
* Attribute bonus structures.
*/
struct str_app_type
{
   short tohit;
   short todam;
   short carry;
   short wield;
};

struct int_app_type
{
   short learn;
};

struct wis_app_type
{
   short practice;
};

struct dex_app_type
{
   short defensive;
};

struct con_app_type
{
   short hitp;
   short shock;
};

struct cha_app_type
{
   short charm;
};

struct lck_app_type
{
   short luck;
};

struct frc_app_type
{
   short force;
};

/* ability classes */

#define ABILITY_NONE		-1
#define COMBAT_ABILITY 		0
#define PILOTING_ABILITY	1
#define ENGINEERING_ABILITY	2
#define HUNTING_ABILITY		3
#define SMUGGLING_ABILITY	4
#define DIPLOMACY_ABILITY	5
#define LEADERSHIP_ABILITY	6
#define FORCE_ABILITY		7

/* the races */
#define RACE_HUMAN	    0
#define RACE_WOOKIEE		1
#define RACE_TWI_LEK		2
#define RACE_RODIAN		3
#define RACE_HUTT		4
#define RACE_MON_CALAMARI	5
#define RACE_NOGHRI		6
#define RACE_GAMORREAN		7
#define RACE_JAWA		8
#define RACE_ADARIAN            9
#define RACE_EWOK              10
#define RACE_VERPINE           11
#define RACE_DEFEL             12
#define RACE_TRANDOSHAN        13
#define RACE_CHADRA_FAN        14
#define RACE_DUINUOGWUIN       16   /* big mistake was causing mass chaos */
#define RACE_QUARREN           15


/*
* Languages -- Altrag
*/
#define LANG_COMMON      BV00 /* Human base language */
#define LANG_WOOKIEE     BV01
#define LANG_TWI_LEK     BV02
#define LANG_RODIAN      BV03
#define LANG_HUTT        BV04
#define LANG_MON_CALAMARI   BV05
#define LANG_NOGHRI      BV06
#define LANG_EWOK        BV07
#define LANG_ITHORIAN    BV08
#define LANG_GOTAL       BV09
#define LANG_DEVARONIAN  BV10
#define LANG_DROID       BV11
#define LANG_SPIRITUAL   BV12
#define LANG_MAGICAL     BV13
#define LANG_GAMORREAN   BV14
#define LANG_GOD         BV15
#define LANG_ANCIENT     BV16
#define LANG_JAWA        BV17
#define LANG_CLAN	 BV18
#define LANG_ADARIAN	 BV19
#define LANG_VERPINE	 BV20
#define LANG_DEFEL       BV21
#define LANG_TRANDOSHAN  BV22
#define LANG_CHADRA_FAN  BV23
#define LANG_QUARREN     BV24
#define LANG_DUINUOGWUIN BV25
#define LANG_UNKNOWN        0 /* Anything that doesnt fit a category */
#define VALID_LANGS    ( LANG_COMMON | LANG_WOOKIEE | LANG_TWI_LEK | LANG_RODIAN  \
   | LANG_HUTT | LANG_MON_CALAMARI | LANG_NOGHRI | LANG_GAMORREAN \
   | LANG_JAWA | LANG_ADARIAN | LANG_EWOK | LANG_VERPINE | LANG_DEFEL \
   | LANG_TRANDOSHAN | LANG_CHADRA_FAN | LANG_QUARREN | LANG_DUINUOGWUIN)
/*  26 Languages */

/*
* TO types for act.
*/
#define TO_ROOM		    0
#define TO_NOTVICT	    1
#define TO_VICT		    2
#define TO_CHAR		    3
#define TO_GROUP            4

#define INIT_WEAPON_CONDITION    12
#define MAX_ITEM_IMPACT		 30

/*
* Help table types.
*/
struct help_data
{
   HELP_DATA *next;
   HELP_DATA *prev;
   short level;
   const char *keyword;
   const char *text;
};



/*
* Shop types.
*/
#define MAX_TRADE	 5

struct shop_data
{
   SHOP_DATA *next;  /* Next shop in list    */
   SHOP_DATA *prev;  /* Previous shop in list   */
   int keeper; /* Vnum of shop keeper mob */
   short buy_type[MAX_TRADE]; /* Item types shop will buy   */
   short profit_buy; /* Cost multiplier for buying */
   short profit_sell;   /* Cost multiplier for selling   */
   short open_hour;  /* First opening hour      */
   short close_hour; /* First closing hour      */
};

#define MAX_FIX		3
#define SHOP_FIX	1
#define SHOP_RECHARGE	2

struct repairshop_data
{
   REPAIR_DATA *next;   /* Next shop in list    */
   REPAIR_DATA *prev;   /* Previous shop in list   */
   int keeper; /* Vnum of shop keeper mob */
   short fix_type[MAX_FIX];   /* Item types shop will fix   */
   short profit_fix; /* Cost multiplier for fixing */
   short shop_type;  /* Repair shop type     */
   short open_hour;  /* First opening hour      */
   short close_hour; /* First closing hour      */
};


/* Mob program structures */
struct act_prog_data
{
   struct act_prog_data *next;
   void *vo;
};

struct mob_prog_act_list
{
   MPROG_ACT_LIST *next;
   const char *buf;
   CHAR_DATA *ch;
   OBJ_DATA *obj;
   void *vo;
};

struct mob_prog_data
{
   MPROG_DATA *next;
   int type;
   bool triggered;
   int resetdelay;
   const char *arglist;
   const char *comlist;
   bool fileprog;
};

extern bool MOBtrigger;

/* race dedicated stuff */
struct race_type
{
   char race_name[16];  /* Race name         */
   EXT_BV affected;  /* Default affect bitvectors  */
   short str_plus;   /* Str bonus/penalty    */
   short dex_plus;   /* Dex      "        */
   short wis_plus;   /* Wis      "        */
   short int_plus;   /* Int      "        */
   short con_plus;   /* Con      "        */
   short cha_plus;   /* Cha      "        */
   short lck_plus;   /* Lck       "       */
   short frc_plus;   /* Frc       "       */
   short hit;
   short mana;
   short resist;
   short suscept;
   int class_restriction;  /* Flags for illegal classes  */
   int language;  /* Default racial language      */
};

typedef enum {
   BUILD_STRONG, BUILD_RUGGED, BUILD_LEAN, BUILD_INTELLECTUAL, BUILD_WISE, MAX_STATBUILD
} stat_enum;

struct stat_build
{
   char build_name[30];
   EXT_BV affected;
   short str_plus;
   short dex_plus;
   short wis_plus;
   short int_plus;
   short con_plus;
   short cha_plus;
   short agi_plus;
   short hit;
   short mana;
   short move;
};

typedef enum
{
   CLAN_PLAIN, CLAN_CRIME, CLAN_GUILD, CLAN_SUBCLAN
} clan_types;

typedef enum
{ SHIP_CIVILIAN, SHIP_REPUBLIC, SHIP_IMPERIAL, MOB_SHIP } ship_types;
typedef enum
{ SHIP_DOCKED, SHIP_READY, SHIP_BUSY, SHIP_BUSY_2, SHIP_BUSY_3, SHIP_REFUEL,
SHIP_LAUNCH, SHIP_LAUNCH_2, SHIP_LAND, SHIP_LAND_2, SHIP_HYPERSPACE, SHIP_DISABLED, SHIP_FLYING
} ship_states;
typedef enum
{ MISSILE_READY, MISSILE_FIRED, MISSILE_RELOAD, MISSILE_RELOAD_2, MISSILE_DAMAGED } missile_states;
typedef enum
{ FIGHTER_SHIP, MIDSIZE_SHIP, CAPITAL_SHIP, SHIP_PLATFORM, CLOUD_CAR, OCEAN_SHIP, LAND_SPEEDER, WHEELED, LAND_CRAWLER,
WALKER
} ship_classes;
typedef enum
{ CONCUSSION_MISSILE, PROTON_TORPEDO, HEAVY_ROCKET, HEAVY_BOMB } missile_types;

typedef enum
{ GROUP_CLAN, GROUP_COUNCIL, GROUP_GUILD } group_types;

#define LASER_DAMAGED    -1
#define LASER_READY       0

struct space_data
{
   SPACE_DATA *next;
   SPACE_DATA *prev;
   SHIP_DATA *first_ship;
   SHIP_DATA *last_ship;
   MISSILE_DATA *first_missile;
   MISSILE_DATA *last_missile;
   PLANET_DATA *first_planet;
   PLANET_DATA *last_planet;
   const char *filename;
   const char *name;
   const char *star1;
   const char *star2;
   const char *planet1;
   const char *planet2;
   const char *planet3;
   const char *location1a;
   const char *location2a;
   const char *location3a;
   const char *location1b;
   const char *location2b;
   const char *location3b;
   const char *location1c;
   const char *location2c;
   const char *location3c;
   int xpos;
   int ypos;
   int s1x;
   int s1y;
   int s1z;
   int s2x;
   int s2y;
   int s2z;
   int doc1a;
   int doc2a;
   int doc3a;
   int doc1b;
   int doc2b;
   int doc3b;
   int doc1c;
   int doc2c;
   int doc3c;
   int p1x;
   int p1y;
   int p1z;
   int p2x;
   int p2y;
   int p2z;
   int p3x;
   int p3y;
   int p3z;
   int gravitys1;
   int gravitys2;
   int gravityp1;
   int gravityp2;
   int gravityp3;
   int p1_low;
   int p1_high;
   int p2_low;
   int p2_high;
   int p3_low;
   int p3_high;
   int crash;
};

struct bounty_data
{
   BOUNTY_DATA *next;
   BOUNTY_DATA *prev;
   const char *target;
   long int amount;
};

struct guard_data
{
   GUARD_DATA *next;
   GUARD_DATA *prev;
   GUARD_DATA *next_on_planet;
   GUARD_DATA *prev_on_planet;
   CHAR_DATA *mob;
   ROOM_INDEX_DATA *reset_loc;
   PLANET_DATA *planet;
};

struct senate_data
{
   SENATE_DATA *next;
   SENATE_DATA *prev;
   const char *name;
};

struct planet_data
{
   PLANET_DATA *next;
   PLANET_DATA *prev;
   PLANET_DATA *next_in_system;
   PLANET_DATA *prev_in_system;
   GUARD_DATA *first_guard;
   GUARD_DATA *last_guard;
   SPACE_DATA *starsystem;
   AREA_DATA *first_area;
   AREA_DATA *last_area;
   const char *name;
   const char *filename;
   long base_value;
   CLAN_DATA *governed_by;
   int population;
   bool flags;
   float pop_support;
   LOOT_DATA *first_loot;
   LOOT_DATA *last_loot;
};

#define PLANET_NOCAPTURE  BV00

struct clan_data
{
   CLAN_DATA *next;  /* next clan in list       */
   CLAN_DATA *prev;  /* previous clan in list      */
   CLAN_DATA *next_subclan;
   CLAN_DATA *prev_subclan;
   CLAN_DATA *first_subclan;
   CLAN_DATA *last_subclan;
   CLAN_DATA *mainclan;
   const char *filename;   /* Clan filename        */
   const char *name; /* Clan name            */
   const char *description;   /* A brief description of the clan  */
   const char *leader;  /* Head clan leader        */
   const char *number1; /* First officer        */
   const char *number2; /* Second officer       */
   int pkills; /* Number of pkills on behalf of clan  */
   int pdeaths;   /* Number of pkills against clan */
   int mkills; /* Number of mkills on behalf of clan  */
   int mdeaths;   /* Number of clan deaths due to mobs   */
   short clan_type;  /* See clan type defines      */
   short members; /* Number of clan members     */
   int board;  /* Vnum of clan board         */
   int storeroom; /* Vnum of clan's store room     */
   int guard1; /* Vnum of clan guard type 1     */
   int guard2; /* Vnum of clan guard type 2     */
   int patrol1;   /* vnum of patrol */
   int patrol2;   /* vnum of patrol */
   int trooper1;  /* vnum of reinforcements */
   int trooper2;  /* vnum of elite troopers */
   long int funds;
   int spacecraft;
   int vehicles;
   int jail;
   const char *tmpstr;
};

struct ship_data
{
   SHIP_DATA *next;
   SHIP_DATA *prev;
   SHIP_DATA *next_in_starsystem;
   SHIP_DATA *prev_in_starsystem;
   SHIP_DATA *next_in_room;
   SHIP_DATA *prev_in_room;
   ROOM_INDEX_DATA *in_room;
   SPACE_DATA *starsystem;
   const char *filename;
   const char *name;
   const char *home;
   const char *description;
   const char *owner;
   const char *pilot;
   const char *copilot;
   const char *dest;
   short type;
   short ship_class;
   short comm;
   short sensor;
   short astro_array;
   short hyperspeed;
   int hyperdistance;
   short realspeed;
   short currspeed;
   short shipstate;
   short statet0;
   short statet1;
   short statet2;
   short missiletype;
   short missilestate;
   short missiles;
   short maxmissiles;
   short torpedos;
   short maxtorpedos;
   short rockets;
   short maxrockets;
   short lasers;
   short tractorbeam;
   short manuever;
   bool bayopen;
   bool hatchopen;
   bool autorecharge;
   bool autotrack;
   bool autospeed;
   float vx, vy, vz;
   float hx, hy, hz;
   float jx, jy, jz;
   int maxenergy;
   int energy;
   int shield;
   int maxshield;
   int hull;
   int maxhull;
   int cockpit;
   int turret1;
   int turret2;
   int location;
   int lastdoc;
   int shipyard;
   int entrance;
   int hanger;
   int engineroom;
   int firstroom;
   int lastroom;
   int navseat;
   int pilotseat;
   int coseat;
   int gunseat;
   long collision;
   SHIP_DATA *target0;
   SHIP_DATA *target1;
   SHIP_DATA *target2;
   SPACE_DATA *currjump;
   short chaff;
   short maxchaff;
   short chaff_released;
   bool autopilot;
};

struct missile_data
{
   MISSILE_DATA *next;
   MISSILE_DATA *prev;
   MISSILE_DATA *next_in_starsystem;
   MISSILE_DATA *prev_in_starsystem;
   SPACE_DATA *starsystem;
   SHIP_DATA *target;
   SHIP_DATA *fired_from;
   const char *fired_by;
   short missiletype;
   short age;
   int speed;
   int mx, my, mz;
};


struct tourney_data
{
   int open;
   int low_level;
   int hi_level;
};

/*
* Data structure for notes.
*/
struct note_data
{
   NOTE_DATA *next;
   NOTE_DATA *prev;
   const char *sender;
   const char *date;
   const char *to_list;
   const char *subject;
   int voting;
   const char *yesvotes;
   const char *novotes;
   const char *abstentions;
   const char *text;
};

struct board_data
{
   BOARD_DATA *next; /* Next board in list         */
   BOARD_DATA *prev; /* Previous board in list     */
   NOTE_DATA *first_note;  /* First note on board        */
   NOTE_DATA *last_note;   /* Last note on board         */
   const char *note_file;  /* Filename to save notes to     */
   const char *read_group; /* Can restrict a board to a       */
   const char *post_group; /* council, clan, guild etc        */
   const char *extra_readers; /* Can give read rights to players */
   const char *extra_removers;   /* Can give remove rights to players */
   int board_obj; /* Vnum of board object       */
   short num_posts;  /* Number of notes on this board   */
   short min_read_level;   /* Minimum level to read a note     */
   short min_post_level;   /* Minimum level to post a note    */
   short min_remove_level; /* Minimum level to remove a note  */
   short max_posts;  /* Maximum amount of notes allowed */
   int type;   /* Normal board or mail board? */
};


/*
* An affect.
*/
struct affect_data
{
   AFFECT_DATA *next;
   AFFECT_DATA *prev;
   CHAR_DATA *from; /* which player isthis from */
   POOL_DATA *from_pool;
   int affect_type; /* buff or enfeeb*/
   short type; /* sn, if its from a skill */
   double duration;
   short location; /* str, dex, agi, etc */
   int modifier;
   EXT_BV bitvector; /* for "aff_"s */
   int factor_id; /* what factor generated this affect */
   int apply_type; /* join, override */
};

#define AFFECT_BUFF 0
#define AFFECT_ENFEEBLE 1

/*
* A SMAUG spell
*/
struct smaug_affect
{
   SMAUG_AFF *next;
   SMAUG_AFF *prev;
   const char *duration;
   short location;
   const char *modifier;
   EXT_BV bitvector;
};

/***************************************************************************
*                                                                         *
*                   VALUES OF INTEREST TO AREA BUILDERS                   *
*                   (Start of section ... start here)                     *
*                                                                         *
***************************************************************************/

/*
* Well known mob virtual numbers.
* Defined in #MOBILES.
*/
#define MOB_VNUM_ANIMATED_CORPSE   5
#define MOB_VNUM_POLY_WOLF	   10
#define MOB_VNUM_STORMTROOPER	20
#define MOB_VNUM_IMP_GUARD	21
#define MOB_VNUM_NR_GUARD	22
#define MOB_VNUM_NR_TROOPER	23
#define MOB_VNUM_MERCINARY	24
#define MOB_VNUM_BOUNCER	25
#define MOB_VNUM_SUPERMOB 3

/*
* ACT bits for mobs.
* Used in #MOBILES.
*/
#define ACT_IS_NPC		 BV00 /* Auto set for mobs */
#define ACT_SENTINEL		 BV01 /* Stays in one room */
#define ACT_SCAVENGER		 BV02 /* Picks up objects  */
#define ACT_AGGRESSIVE		 BV05 /* Attacks PC's      */
#define ACT_STAY_AREA		 BV06 /* Won't leave area  */
#define ACT_WIMPY		 BV07 /* Flees when hurt   */
#define ACT_PET			 BV08 /* Auto set for pets */
#define ACT_TRAIN		 BV09 /* Can train PC's */
#define ACT_PRACTICE		 BV10 /* Can practice PC's */
#define ACT_IMMORTAL		 BV11 /* Cannot be killed  */
#define ACT_DEADLY		 BV12 /* Has a deadly poison  */
#define ACT_POLYSELF		 BV13
#define ACT_META_AGGR		 BV14 /* Extremely aggressive */
#define ACT_GUARDIAN		 BV15 /* Protects master   */
#define ACT_RUNNING		 BV16 /* Hunts quickly  */
#define ACT_NOWANDER		 BV17 /* Doesn't wander */
#define ACT_MOUNTABLE		 BV18 /* Can be mounted */
#define ACT_MOUNTED		 BV19 /* Is mounted     */
#define ACT_SCHOLAR              BV20  /* Can teach languages  */
#define ACT_SECRETIVE		 BV21 /* actions aren't seen  */
#define ACT_POLYMORPHED		 BV22 /* Mob is a ch    */
#define ACT_MOBINVIS		 BV23 /* Like wizinvis  */
#define ACT_NOASSIST		 BV24 /* Doesn't assist mobs  */
#define ACT_NOKILL               BV25  /* Mob can't die */
#define ACT_DROID                BV26  /* mob is a droid */
#define ACT_NOCORPSE             BV27
#define ACT_PROTOTYPE		 BV30 /* A prototype mob   */
/* 20 acts */

/* bits for vip flags */

#define VIP_CORUSCANT           BV00
#define VIP_KASHYYYK          	BV01
#define VIP_RYLOTH            	BV02
#define VIP_RODIA             	BV03
#define VIP_NAL_HUTTA           BV04
#define VIP_MON_CALAMARI       	BV05
#define VIP_HONOGHR             BV06
#define VIP_GAMORR              BV07
#define VIP_TATOOINE            BV08
#define VIP_ADARI           	BV09
#define VIP_BYSS		BV10
#define VIP_ENDOR		BV11
#define VIP_ROCHE		BV12
#define VIP_AF_EL		BV13
#define VIP_TRANDOSH		BV14
#define VIP_CHAD		BV15

/* player wanted bits */

#define WANTED_MON_CALAMARI   	VIP_MON_CALAMARI
#define WANTED_CORUSCANT   	VIP_CORUSCANT
#define WANTED_ADARI   		VIP_ADARI
#define WANTED_RODIA   		VIP_RODIA
#define WANTED_RYLOTH   	VIP_RYLOTH
#define WANTED_GAMORR   	VIP_GAMORR
#define WANTED_TATOOINE   	VIP_TATOOINE
#define WANTED_BYSS   		VIP_BYSS
#define WANTED_NAL_HUTTA   	VIP_NAL_HUTTA
#define WANTED_KASHYYYK   	VIP_KASHYYYK
#define WANTED_HONOGHR   	VIP_HONOGHR
#define WANTED_ENDOR		BV11
#define WANTED_ROCHE		BV12
#define WANTED_AF_EL		BV13
#define WANTED_TRANDOSH		BV14
#define WANTED_CHAD		BV15

/*
* Bits for 'affected_by'.
* Used in #MOBILES.
*/
typedef enum
{
   AFF_NONE = 0, AFF_BLIND, AFF_INVISIBLE, AFF_DETECT_EVIL, AFF_DETECT_INVIS,
   AFF_DETECT_MAGIC, AFF_DETECT_HIDDEN, AFF_WEAKEN, AFF_SANCTUARY,
   AFF_FAERIE_FIRE, AFF_INFRARED, AFF_CURSE, AFF_FLAMING, AFF_POISON,
   AFF_PROTECT, AFF_PARALYSIS, AFF_SNEAK, AFF_HIDE, AFF_SLEEP, AFF_CHARM,
   AFF_FLYING, AFF_PASS_DOOR, AFF_FLOATING, AFF_TRUESIGHT, AFF_DETECTTRAPS,
   AFF_SCRYING, AFF_FIRESHIELD, AFF_SHOCKSHIELD, AFF_HAUS1, AFF_ICESHIELD,
   AFF_POSSESS, AFF_BERSERK, AFF_AQUA_BREATH, MAX_AFF
} aff_bits;

typedef enum
{
   STAT_HIT, STAT_MAXHIT, STAT_MANA, STAT_MAXMANA, STAT_MOVE, STAT_MAXMOVE,
   STAT_ALIGN, STAT_BARENUMDIE, STAT_BARESIZEDIE, STAT_DAMROLL, STAT_MAGICATTACK,
   STAT_DEFENSE, STAT_MAGICDEFENSE, STAT_HASTEFROMEQ, STAT_HASTEFROMMAGIC, STAT_HASTEFROMSKILL,
   STAT_THREAT, STAT_PERMSTR, STAT_PERMDEX, STAT_PERMCON, STAT_PERMINT, STAT_PERMWIS,
   STAT_PERMAGI, STAT_STRENGTH, STAT_DEXTERITY, STAT_CONSTITUTION, STAT_INTELLIGENCE, STAT_WISDOM, STAT_AGILITY,
   STAT_RES_ALL, STAT_RES_PHYSICAL, STAT_RES_ELEMENTAL, STAT_RES_FIRE, STAT_RES_WATER,
   STAT_RES_EARTH, STAT_RES_ELECTRICITY, STAT_RES_WIND, STAT_RES_ENERGY, STAT_RES_DARKENERGY,
   STAT_RES_BLUNT, STAT_RES_PIERCING, STAT_RES_SLASHING, STAT_PEN_ALL, STAT_PEN_PHYSICAL,
   STAT_PEN_ELEMENTAL, STAT_PEN_FIRE, STAT_PEN_WATER, STAT_PEN_EARTH, STAT_PEN_ELECTRICITY,
   STAT_PEN_WIND, STAT_PEN_ENERGY, STAT_PEN_DARKENERGY, STAT_PEN_BLUNT, STAT_PEN_PIERCING,
   STAT_PEN_SLASHING, STAT_DTYPE_ALL, STAT_DTYPE_PHYSICAL, STAT_DTYPE_ELEMENTAL,
   STAT_DTYPE_FIRE, STAT_DTYPE_WATER, STAT_DTYPE_EARTH, STAT_DTYPE_ELECTRICITY,
   STAT_DTYPE_WIND, STAT_DTYPE_ENERGY, STAT_DTYPE_DARKENERGY, STAT_DTYPE_BLUNT,
   STAT_DTYPE_PIERCING, STAT_DTYPE_SLASHING, STAT_WEPNUMDIE,  STAT_WEPSIZEDIE,
   STAT_WEPPLUS, STAT_POTENCY, STAT_COOLDOWNS, STAT_RANGE, STAT_DURATIONS,
   STAT_REGEN, STAT_REFRESH, STAT_DBL_ATTACK, STAT_CRITCHANCE, STAT_CRITDAM,
   STAT_DODGE, STAT_PARRY, STAT_COUNTER, STAT_BLOCK, STAT_PHASE, STAT_COMBODMG,
   STAT_CHARMEDDMG, STAT_CHARMEDDEF, STAT_FEEDBACKPOTENCY, STAT_GRAVITY, STAT_HITROLL,
   STAT_ARMOR, STAT_EVASION, STAT_CHARISMA, STAT_PERMCHA, STAT_LUCK, STAT_GOLD, STAT_BAREPLUS,
   STAT_SPEED, STAT_DAMPLUS, MAX_STATTYPE
} stat_types;

/* 31 aff's (1 left.. :P) */
/* make that none - ugh - time for another field? :P */
/*
* Resistant Immune Susceptible flags
*/
#define RIS_FIRE		  BV00
#define RIS_COLD		  BV01
#define RIS_ELECTRICITY		  BV02
#define RIS_ENERGY		  BV03
#define RIS_BLUNT		  BV04
#define RIS_PIERCE		  BV05
#define RIS_SLASH		  BV06
#define RIS_ACID		  BV07
#define RIS_POISON		  BV08
#define RIS_DRAIN		  BV09
#define RIS_SLEEP		  BV10
#define RIS_CHARM		  BV11
#define RIS_HOLD		  BV12
#define RIS_NONMAGIC		  BV13
#define RIS_PLUS1		  BV14
#define RIS_PLUS2		  BV15
#define RIS_PLUS3		  BV16
#define RIS_PLUS4		  BV17
#define RIS_PLUS5		  BV18
#define RIS_PLUS6		  BV19
#define RIS_MAGIC		  BV20
#define RIS_PARALYSIS		  BV21
/* 21 RIS's*/

typedef enum
{
   DAM_ALL, DAM_PHYSICAL, DAM_ELEMENTAL, DAM_FIRE, DAM_WATER,
   DAM_EARTH, DAM_ELECTRICITY, DAM_WIND, DAM_ENERGY, DAM_DARKENERGY,
   DAM_BLUNT, DAM_PIERCE, DAM_SLASH, MAX_DAMTYPE
} damage_types;

typedef enum
{
   QUALITY_COMMON, QUALITY_UNCOMMON, QUALITY_RARE, QUALITY_CRAFTED,
   QUALITY_HQ, MAX_QUALITYTYPE
} quality_types;

typedef enum
{
   LOOT_SET, LOOT_RANDOM, LOOT_GOLD, MAX_LOOTTYPE
} loot_types;

/*
* Attack types
*/
#define ATCK_BITE		  BV00
#define ATCK_CLAWS	  BV01
#define ATCK_TAIL		  BV02
#define ATCK_STING	  BV03
#define ATCK_PUNCH	  BV04
#define ATCK_KICK		  BV05
#define ATCK_TRIP		  BV06
#define ATCK_BACKSTAB	  BV10

/*
* Defense types
*/
#define DFND_PARRY	  BV00
#define DFND_DODGE	  BV01
#define DFND_DISARM	  BV19
#define DFND_GRIP		  BV21

/*
* Body parts
*/
#define PART_HEAD		  BV00
#define PART_ARMS		  BV01
#define PART_LEGS		  BV02
#define PART_HEART		  BV03
#define PART_BRAINS		  BV04
#define PART_GUTS		  BV05
#define PART_HANDS		  BV06
#define PART_FEET		  BV07
#define PART_FINGERS		  BV08
#define PART_EAR		  BV09
#define PART_EYE		  BV10
#define PART_LONG_TONGUE	  BV11
#define PART_EYESTALKS		  BV12
#define PART_TENTACLES		  BV13
#define PART_FINS		  BV14
#define PART_WINGS		  BV15
#define PART_TAIL		  BV16
#define PART_SCALES		  BV17
/* for combat */
#define PART_CLAWS		  BV18
#define PART_FANGS		  BV19
#define PART_HORNS		  BV20
#define PART_TUSKS		  BV21
#define PART_TAILATTACK		  BV22
#define PART_SHARPSCALES	  BV23
#define PART_BEAK		  BV24

#define PART_HAUNCH		  BV25
#define PART_HOOVES		  BV26
#define PART_PAWS		  BV27
#define PART_FORELEGS		  BV28
#define PART_FEATHERS		  BV29

/*
* Autosave flags
*/
#define SV_DEATH		  BV00
#define SV_KILL			  BV01
#define SV_PASSCHG		  BV02
#define SV_DROP			  BV03
#define SV_PUT			  BV04
#define SV_GIVE			  BV05
#define SV_AUTO			  BV06
#define SV_ZAPDROP		  BV07
#define SV_AUCTION		  BV08
#define SV_GET			  BV09
#define SV_RECEIVE		  BV10
#define SV_IDLE			  BV11
#define SV_BACKUP		  BV12

/*
* Pipe flags
*/
#define PIPE_TAMPED		  BV01
#define PIPE_LIT		  BV02
#define PIPE_HOT		  BV03
#define PIPE_DIRTY		  BV04
#define PIPE_FILTHY		  BV05
#define PIPE_GOINGOUT		  BV06
#define PIPE_BURNT		  BV07
#define PIPE_FULLOFASH		  BV08

/*
* Skill/Spell flags	The minimum BV *MUST* be 11!
*/
#define SF_WATER		  BV11
#define SF_EARTH		  BV12
#define SF_AIR			  BV13
#define SF_ASTRAL		  BV14
#define SF_AREA			  BV15   /* is an area spell      */
#define SF_DISTANT		  BV16   /* affects something far away  */
#define SF_REVERSE		  BV17
#define SF_SAVE_HALF_DAMAGE	  BV18   /* save for half damage     */
#define SF_SAVE_NEGATES		  BV19   /* save negates affect      */
#define SF_ACCUMULATIVE		  BV20   /* is accumulative    */
#define SF_RECASTABLE		  BV21   /* can be refreshed      */
#define SF_NOSCRIBE		  BV22   /* cannot be scribed     */
#define SF_NOBREW		  BV23   /* cannot be brewed      */
#define SF_GROUPSPELL		  BV24   /* only affects group members  */
#define SF_OBJECT		  BV25   /* directed at an object   */
#define SF_CHARACTER		  BV26   /* directed at a character  */
#define SF_SECRETSKILL		  BV27   /* hidden unless learned   */
#define SF_PKSENSITIVE		  BV28   /* much harder for plr vs. plr   */
#define SF_STOPONFAIL		  BV29   /* stops spell on first failure */

typedef enum
{ SS_NONE, SS_POISON_DEATH, SS_ROD_WANDS, SS_PARA_PETRI,
SS_BREATH, SS_SPELL_STAFF
} save_types;

#define ALL_BITS		INT_MAX
#define SDAM_MASK		ALL_BITS & ~(BV00 | BV01 | BV02)
#define SACT_MASK		ALL_BITS & ~(BV03 | BV04 | BV05)
#define SCLA_MASK		ALL_BITS & ~(BV06 | BV07 | BV08)
#define SPOW_MASK		ALL_BITS & ~(BV09 | BV10)

typedef enum
{ SD_NONE, SD_FIRE, SD_COLD, SD_ELECTRICITY, SD_ENERGY, SD_ACID,
SD_POISON, SD_DRAIN
} spell_dam_types;

typedef enum
{ SA_NONE, SA_CREATE, SA_DESTROY, SA_RESIST, SA_SUSCEPT,
SA_DIVINATE, SA_OBSCURE, SA_CHANGE
} spell_act_types;

typedef enum
{ SP_NONE, SP_MINOR, SP_GREATER, SP_MAJOR } spell_power_types;

typedef enum
{ SC_NONE, SC_LUNAR, SC_SOLAR, SC_TRAVEL, SC_SUMMON,
SC_LIFE, SC_DEATH, SC_ILLUSION
} spell_class_types;

/*
* Sex.
* Used in #MOBILES.
*/
typedef enum
{ SEX_NEUTRAL, SEX_MALE, SEX_FEMALE } sex_types;

typedef enum
{
   TRAP_TYPE_POISON_GAS = 1, TRAP_TYPE_POISON_DART, TRAP_TYPE_POISON_NEEDLE,
   TRAP_TYPE_POISON_DAGGER, TRAP_TYPE_POISON_ARROW, TRAP_TYPE_BLINDNESS_GAS,
   TRAP_TYPE_SLEEPING_GAS, TRAP_TYPE_FLAME, TRAP_TYPE_EXPLOSION,
   TRAP_TYPE_ACID_SPRAY, TRAP_TYPE_ELECTRIC_SHOCK, TRAP_TYPE_BLADE,
   TRAP_TYPE_SEX_CHANGE
} trap_types;

#define MAX_TRAPTYPE		   TRAP_TYPE_SEX_CHANGE

#define TRAP_ROOM      		   BV00
#define TRAP_OBJ	      	   BV01
#define TRAP_ENTER_ROOM		   BV02
#define TRAP_LEAVE_ROOM		   BV03
#define TRAP_OPEN		   BV04
#define TRAP_CLOSE		   BV05
#define TRAP_GET		   BV06
#define TRAP_PUT		   BV07
#define TRAP_PICK		   BV08
#define TRAP_UNLOCK		   BV09
#define TRAP_N			   BV10
#define TRAP_S			   BV11
#define TRAP_E	      		   BV12
#define TRAP_W	      		   BV13
#define TRAP_U	      		   BV14
#define TRAP_D	      		   BV15
#define TRAP_EXAMINE		   BV16
#define TRAP_NE			   BV17
#define TRAP_NW			   BV18
#define TRAP_SE			   BV19
#define TRAP_SW			   BV20

/*
* Well known object virtual numbers.
* Defined in #OBJECTS.
*/
#define OBJ_VNUM_MONEY_ONE	      2
#define OBJ_VNUM_MONEY_SOME	      3

#define OBJ_VNUM_DROID_CORPSE        9
#define OBJ_VNUM_CORPSE_NPC	     10
#define OBJ_VNUM_CORPSE_PC	     11
#define OBJ_VNUM_SEVERED_HEAD	     12
#define OBJ_VNUM_TORN_HEART	     13
#define OBJ_VNUM_SLICED_ARM	     14
#define OBJ_VNUM_SLICED_LEG	     15
#define OBJ_VNUM_SPILLED_GUTS	     16
#define OBJ_VNUM_BLOOD		     17
#define OBJ_VNUM_BLOODSTAIN	     18
#define OBJ_VNUM_SCRAPS		     19

#define OBJ_VNUM_MUSHROOM	     20
#define OBJ_VNUM_LIGHT_BALL	     21
#define OBJ_VNUM_SPRING		     22

#define OBJ_VNUM_SLICE		     24
#define OBJ_VNUM_SHOPPING_BAG	     25

#define OBJ_VNUM_FIRE		     30
#define OBJ_VNUM_TRAP		     31
#define OBJ_VNUM_PORTAL		     32

#define OBJ_VNUM_BLACK_POWDER	     33
#define OBJ_VNUM_SCROLL_SCRIBING     34
#define OBJ_VNUM_FLASK_BREWING       35
#define OBJ_VNUM_NOTE		     36

/* Academy eq */
#define OBJ_VNUM_SCHOOL_MACE	  10315
#define OBJ_VNUM_SCHOOL_DAGGER	  10312
#define OBJ_VNUM_SCHOOL_SWORD	  10313
#define OBJ_VNUM_SCHOOL_VEST	  10308
#define OBJ_VNUM_SCHOOL_SHIELD	  10310
#define OBJ_VNUM_SCHOOL_BANNER    10311
#define OBJ_VNUM_SCHOOL_DIPLOMA   10321

#define OBJ_VNUM_BLASTECH_E11     50

/*
* Item types.
* Used in #OBJECTS.
*/
typedef enum
{
   ITEM_NONE, ITEM_LIGHT, ITEM_SCROLL, ITEM_WAND, ITEM_STAFF, ITEM_WEAPON,
   ITEM_FIREWEAPON, ITEM_MISSILE, ITEM_TREASURE, ITEM_ARMOR, ITEM_POTION,
   ITEM_WORN, ITEM_FURNITURE, ITEM_TRASH, ITEM_OLDTRAP, ITEM_CONTAINER,
   ITEM_NOTE, ITEM_DRINK_CON, ITEM_KEY, ITEM_FOOD, ITEM_MONEY, ITEM_PEN,
   ITEM_BOAT, ITEM_CORPSE_NPC, ITEM_CORPSE_PC, ITEM_FOUNTAIN, ITEM_PILL,
   ITEM_BLOOD, ITEM_BLOODSTAIN, ITEM_SCRAPS, ITEM_PIPE, ITEM_HERB_CON,
   ITEM_HERB, ITEM_INCENSE, ITEM_FIRE, ITEM_BOOK, ITEM_SWITCH, ITEM_LEVER,
   ITEM_PULLCHAIN, ITEM_BUTTON, ITEM_DIAL, ITEM_RUNE, ITEM_RUNEPOUCH,
   ITEM_MATCH, ITEM_TRAP, ITEM_MAP, ITEM_PORTAL, ITEM_PAPER,
   ITEM_TINDER, ITEM_LOCKPICK, ITEM_SPIKE, ITEM_DISEASE, ITEM_OIL, ITEM_FUEL,
   ITEM_SHORT_BOW, ITEM_LONG_BOW, ITEM_CROSSBOW, ITEM_AMMO, ITEM_QUIVER,
   ITEM_SHOVEL, ITEM_SALVE, ITEM_RAWSPICE, ITEM_LENS, ITEM_CRYSTAL, ITEM_DURAPLAST,
   ITEM_BATTERY, ITEM_TOOLKIT, ITEM_DURASTEEL, ITEM_OVEN, ITEM_MIRROR,
   ITEM_CIRCUIT, ITEM_SUPERCONDUCTOR, ITEM_COMLINK, ITEM_MEDPAC, ITEM_FABRIC,
   ITEM_RARE_METAL, ITEM_MAGNET, ITEM_THREAD, ITEM_SPICE, ITEM_SMUT, ITEM_DEVICE, ITEM_SPACECRAFT,
   ITEM_GRENADE, ITEM_LANDMINE, ITEM_GOVERNMENT, ITEM_DROID_CORPSE, ITEM_BOLT, ITEM_CHEMICAL
} item_types;


#define MAX_ITEM_TYPE		     ITEM_CHEMICAL
/*
* Extra flags.
* Used in #OBJECTS.
*/
#define ITEM_GLOW		BV00
#define ITEM_HUM		BV01
#define ITEM_DARK		BV02
#define ITEM_HUTT_SIZE		BV03
#define ITEM_CONTRABAND		BV04
#define ITEM_INVIS		BV05
#define ITEM_MAGIC		BV06
#define ITEM_NODROP		BV07
#define ITEM_BLESS		BV08
#define ITEM_ANTI_GOOD		BV09
#define ITEM_ANTI_EVIL		BV10
#define ITEM_ANTI_NEUTRAL	BV11
#define ITEM_NOREMOVE		BV12
#define ITEM_INVENTORY		BV13
#define ITEM_ANTI_SOLDIER	BV14
#define ITEM_ANTI_THIEF	        BV15
#define ITEM_ANTI_HUNTER	BV16
#define ITEM_ANTI_JEDI  	BV17
#define ITEM_SMALL_SIZE		BV18
#define ITEM_LARGE_SIZE		BV19
#define ITEM_DONATION		BV20
#define ITEM_CLANOBJECT		BV21
#define ITEM_ANTI_CITIZEN	BV22
#define ITEM_ANTI_SITH  	BV23
#define ITEM_ANTI_PILOT	        BV24
#define ITEM_HIDDEN		BV25
#define ITEM_POISONED		BV26
#define ITEM_COVERING		BV27
#define ITEM_DEATHROT		BV28
#define ITEM_BURRIED		BV29  /* item is underground */
#define ITEM_PROTOTYPE		BV30
#define ITEM_HUMAN_SIZE         BV31

/* Magic flags - extra extra_flags for objects that are used in spells */
#define ITEM_RETURNING		BV00
#define ITEM_BACKSTABBER  	BV01
#define ITEM_BANE		BV02
#define ITEM_LOYAL		BV03
#define ITEM_HASTE		BV04
#define ITEM_DRAIN		BV05
#define ITEM_LIGHTNING_BLADE  	BV06

/* Blaster settings - only saves on characters */
#define BLASTER_NORMAL          0
#define BLASTER_HALF		2
#define BLASTER_FULL            5
#define BLASTER_LOW		1
#define	BLASTER_STUN		3
#define BLASTER_HIGH            4

/* Weapon Types */
typedef enum
{
   WEAPON_NONE, WEAPON_VIBRO_AXE, WEAPON_VIBRO_BLADE,
   WEAPON_LIGHTSABER, WEAPON_WHIP, WEAPON_CLAW, WEAPON_BLASTER,
   WEAPON_BLUDGEON, WEAPON_BOWCASTER, WEAPON_FORCE_PIKE, MAX_WEAPON
} weapon_types;

/* Lever/dial/switch/button/pullchain flags */
#define TRIG_UP			BV00
#define TRIG_UNLOCK		BV01
#define TRIG_LOCK		BV02
#define TRIG_D_NORTH		BV03
#define TRIG_D_SOUTH		BV04
#define TRIG_D_EAST		BV05
#define TRIG_D_WEST		BV06
#define TRIG_D_UP		BV07
#define TRIG_D_DOWN		BV08
#define TRIG_DOOR		BV09
#define TRIG_CONTAINER		BV10
#define TRIG_OPEN		BV11
#define TRIG_CLOSE		BV12
#define TRIG_PASSAGE		BV13
#define TRIG_OLOAD		BV14
#define TRIG_MLOAD		BV15
#define TRIG_TELEPORT		BV16
#define TRIG_TELEPORTALL	BV17
#define TRIG_TELEPORTPLUS	BV18
#define TRIG_DEATH		BV19
#define TRIG_CAST		BV20
#define TRIG_FAKEBLADE		BV21
#define TRIG_RAND4		BV22
#define TRIG_RAND6		BV23
#define TRIG_TRAPDOOR		BV24
#define TRIG_ANOTHEROOM		BV25
#define TRIG_USEDIAL		BV26
#define TRIG_ABSOLUTEVNUM	BV27
#define TRIG_SHOWROOMDESC	BV28
#define TRIG_AUTORETURN		BV29

#define TELE_SHOWDESC		BV00
#define TELE_TRANSALL		BV01
#define TELE_TRANSALLPLUS	BV02

/* drug types */
#define SPICE_GLITTERSTIM        0
#define SPICE_CARSANUM           1
#define SPICE_RYLL               2
#define SPICE_ANDRIS             3

/* crystal types */
#define GEM_NON_ADEGEN          0
#define GEM_KATHRACITE		1
#define GEM_RELACITE		2
#define GEM_DANITE		3
#define GEM_MEPHITE		4
#define GEM_PONITE		5
#define GEM_ILLUM               6
#define GEM_CORUSCA             7

/*
* Wear flags.
* Used in #OBJECTS.
*/
#define ITEM_TAKE		BV00
#define ITEM_WEAR_FINGER	BV01
#define ITEM_WEAR_NECK		BV02
#define ITEM_WEAR_BODY		BV03
#define ITEM_WEAR_HEAD		BV04
#define ITEM_WEAR_LEGS		BV05
#define ITEM_WEAR_FEET		BV06
#define ITEM_WEAR_HANDS		BV07
#define ITEM_WEAR_ARMS		BV08
#define ITEM_WEAR_SHIELD	BV09
#define ITEM_WEAR_ABOUT		BV10
#define ITEM_WEAR_WAIST		BV11
#define ITEM_WEAR_WRIST		BV12
#define ITEM_WIELD		BV13
#define ITEM_HOLD		BV14
#define ITEM_DUAL_WIELD		BV15
#define ITEM_WEAR_EARS		BV16
#define ITEM_WEAR_EYES		BV17
#define ITEM_MISSILE_WIELD	BV18
#define MAX_ITEM_WEAR           19

/*
* Apply types (for affects).
* Used in #OBJECTS.
*/
typedef enum
{
   APPLY_NONE = 0, APPLY_STR, APPLY_DEX, APPLY_INT, APPLY_WIS, APPLY_CON, APPLY_AGI,
   APPLY_SEX, APPLY_NULL, APPLY_LEVEL, APPLY_AGE, APPLY_HEIGHT, APPLY_WEIGHT,
   APPLY_MANA, APPLY_HIT, APPLY_MOVE, APPLY_GOLD, APPLY_EXP, APPLY_EVASION,
   APPLY_HITROLL, APPLY_DAMROLL, APPLY_SAVING_POISON, APPLY_SAVING_ROD,
   APPLY_SAVING_PARA, APPLY_SAVING_BREATH, APPLY_SAVING_SPELL, APPLY_CHA,
   APPLY_AFFECT, APPLY_RESISTANT, APPLY_IMMUNE, APPLY_SUSCEPTIBLE,
   APPLY_WEAPONSPELL, APPLY_LCK, APPLY_BACKSTAB, APPLY_PICK, APPLY_TRACK,
   APPLY_STEAL, APPLY_SNEAK, APPLY_HIDE, APPLY_PALM, APPLY_DETRAP, APPLY_DODGE,
   APPLY_PEEK, APPLY_SCAN, APPLY_GOUGE, APPLY_SEARCH, APPLY_MOUNT, APPLY_DISARM,
   APPLY_KICK, APPLY_PARRY, APPLY_BASH, APPLY_STUN, APPLY_PUNCH, APPLY_CLIMB,
   APPLY_GRIP, APPLY_SCRIBE, APPLY_BREW, APPLY_WEARSPELL, APPLY_REMOVESPELL,
   APPLY_EMOTION, APPLY_MENTALSTATE, APPLY_STRIPSN, APPLY_REMOVE, APPLY_DIG,
   APPLY_FULL, APPLY_THIRST, APPLY_DRUNK, APPLY_BLOOD, APPLY_ARMOR, APPLY_THREAT,
   APPLY_PEN_ALL, APPLY_PEN_PHYSICAL, APPLY_PEN_ELEMENTAL, APPLY_PEN_FIRE,
   APPLY_PEN_WATER, APPLY_PEN_EARTH, APPLY_PEN_ELECTRICITY, APPLY_PEN_WIND,
   APPLY_PEN_ENERGY, APPLY_PEN_DARKENERGY, APPLY_PEN_BLUNT, APPLY_PEN_PIERCING,
   APPLY_PEN_SLASHING, APPLY_RES_ALL, APPLY_RES_PHYSICAL, APPLY_RES_ELEMENTAL,
   APPLY_RES_FIRE, APPLY_RES_WATER, APPLY_RES_EARTH, APPLY_RES_ELECTRICITY,
   APPLY_RES_WIND, APPLY_RES_ENERGY, APPLY_RES_DARKENERGY, APPLY_RES_BLUNT,
   APPLY_RES_PIERCING, APPLY_RES_SLASHING, APPLY_DTYPE_ALL, APPLY_DTYPE_PHYSICAL,
   APPLY_DTYPE_ELEMENTAL, APPLY_DTYPE_FIRE, APPLY_DTYPE_WATER, APPLY_DTYPE_EARTH,
   APPLY_DTYPE_ELECTRICITY, APPLY_DTYPE_WIND, APPLY_DTYPE_ENERGY,
   APPLY_DTYPE_DARKENERGY, APPLY_DTYPE_BLUNT, APPLY_DTYPE_PIERCING,
   APPLY_DTYPE_SLASHING, APPLY_HASTEFROMEQ, APPLY_HASTEFROMMAGIC, APPLY_HASTEFROMSKILL,
   APPLY_DBL_ATTACK, APPLY_SPEED, APPLY_BARENUMDIE, APPLY_BARESIZEDIE,
   APPLY_DAMPLUS, APPLY_WEPNUMDIE, APPLY_WEPSIZEDIE, APPLY_WEPPLUS, APPLY_DAMTYPE,
   MAX_APPLY_TYPE
} apply_types;

#define REVERSE_APPLY		   1000

/*
* Values for containers (value[1]).
* Used in #OBJECTS.
*/
#define CONT_CLOSEABLE		      1
#define CONT_PICKPROOF		      2
#define CONT_CLOSED		      4
#define CONT_LOCKED		      8

/*
* Well known room virtual numbers.
* Defined in #ROOMS.
*/
#define ROOM_VNUM_LIMBO		      2
#define ROOM_VNUM_POLY		      3
#define ROOM_VNUM_CHAT		  32144
#define ROOM_VNUM_TEMPLE	  32144
#define ROOM_VNUM_ALTAR		  32144
#define ROOM_VNUM_SCHOOL	  10429
#define ROOM_AUTH_START		  10300
#define ROOM_START_HUMAN            211
#define ROOM_START_WOOKIEE        28600
#define ROOM_START_TWILEK         32148
#define ROOM_START_RODIAN         32148
#define ROOM_START_HUTT           32148
#define ROOM_START_MON_CALAMARIAN 21069
#define ROOM_START_NOGHRI          1015
#define ROOM_START_GAMORREAN      28100
#define ROOM_START_JAWA           31819
#define ROOM_START_ADARIAN        29000
#define ROOM_START_EWOK           32148
#define ROOM_START_VERPINE        32148
#define ROOM_START_DEFEL          32148
#define ROOM_START_TRANDOSHAN     32148
#define ROOM_START_CHADRA_FAN     32148
#define ROOM_START_DUINUOGWUIN    32148
#define ROOM_START_QUARREN        21069
#define ROOM_START_IMMORTAL         100
#define ROOM_LIMBO_SHIPYARD          45
#define ROOM_DEFAULT_CRASH        28025

#define ROOM_PLUOGUS_QUIT         32148

#define ROOM_SHUTTLE_BUS           32140 /*PLUOGUS*/
#define ROOM_SHUTTLE_BUS_2         32410 /*TOCCA*/
#define ROOM_CORUSCANT_SHUTTLE     199
#define ROOM_SENATE_SHUTTLE      10197
#define ROOM_CORUSCANT_TURBOCAR    226
/*
* Room flags.           Holy cow!  Talked about stripped away..
* Used in #ROOMS.       Those merc guys know how to strip code down.
*			 Lets put it all back... ;)
*/
#define ROOM_DARK		BV00
/* BV01 now reserved for track  BV01  and hunt */
#define ROOM_NO_MOB		BV02
#define ROOM_INDOORS		BV03
#define ROOM_CAN_LAND		BV04
#define ROOM_CAN_FLY		BV05
#define ROOM_NO_DRIVING 	BV06
#define ROOM_NO_MAGIC		BV07
#define ROOM_BANK		BV08
#define ROOM_PRIVATE		BV09
#define ROOM_SAFE		BV10
#define ROOM_SOLITARY		BV11
#define ROOM_PET_SHOP		BV12
#define ROOM_NO_RECALL		BV13
#define ROOM_DONATION		BV14
#define ROOM_NODROPALL		BV15
#define ROOM_SILENCE		BV16
#define ROOM_LOGSPEECH		BV17
#define ROOM_NODROP		BV18
#define ROOM_CLANSTOREROOM	BV19
#define ROOM_PLR_HOME		BV20
#define ROOM_EMPTY_HOME 	BV21
#define ROOM_TELEPORT		BV22
#define ROOM_HOTEL      	BV23
#define ROOM_NOFLOOR		BV24
#define ROOM_REFINERY           BV25
#define ROOM_FACTORY            BV26
#define ROOM_R_RECRUIT          BV27
#define ROOM_E_RECRUIT          BV28
#define ROOM_SPACECRAFT         BV29
#define ROOM_PROTOTYPE	     	BV30
#define ROOM_AUCTION            BV31
/*
* Directions.
* Used in #ROOMS.
*/
typedef enum
{
   DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST, DIR_UP, DIR_DOWN,
   DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHEAST, DIR_SOUTHWEST, DIR_SOMEWHERE
} dir_types;

#define MAX_DIR			DIR_SOUTHWEST  /* max for normal walking */
#define DIR_PORTAL		DIR_SOMEWHERE  /* portal direction    */


/*
* Exit flags.
* Used in #ROOMS.
*/
#define EX_ISDOOR		  BV00
#define EX_CLOSED		  BV01
#define EX_LOCKED		  BV02
#define EX_SECRET		  BV03
#define EX_SWIM			  BV04
#define EX_PICKPROOF		  BV05
#define EX_FLY			  BV06
#define EX_CLIMB		  BV07
#define EX_DIG			  BV08
#define EX_RES1                   BV09 /* are these res[1-4] important? */
#define EX_NOPASSDOOR		  BV10
#define EX_HIDDEN		  BV11
#define EX_PASSAGE		  BV12
#define EX_PORTAL 		  BV13
#define EX_RES2			  BV14
#define EX_RES3			  BV15
#define EX_xCLIMB		  BV16
#define EX_xENTER		  BV17
#define EX_xLEAVE		  BV18
#define EX_xAUTO		  BV19
#define EX_RES4	  		  BV20
#define EX_xSEARCHABLE		  BV21
#define EX_BASHED                 BV22
#define EX_BASHPROOF              BV23
#define EX_NOMOB		  BV24
#define EX_WINDOW		  BV25
#define EX_xLOOK		  BV26
#define MAX_EXFLAG		  26

/*
* Sector types.
* Used in #ROOMS.
*/
typedef enum
{
   SECT_INSIDE, SECT_CITY, SECT_FIELD, SECT_FOREST, SECT_HILLS, SECT_MOUNTAIN,
   SECT_WATER_SWIM, SECT_WATER_NOSWIM, SECT_UNDERWATER, SECT_AIR, SECT_DESERT,
   SECT_DUNNO, SECT_OCEANFLOOR, SECT_UNDERGROUND, SECT_MAX
} sector_types;

/*
* Equpiment wear locations.
* Used in #RESETS.
*/
typedef enum
{
   WEAR_NONE = -1, WEAR_LIGHT = 0, WEAR_FINGER_L, WEAR_FINGER_R, WEAR_NECK_1,
   WEAR_NECK_2, WEAR_BODY, WEAR_HEAD, WEAR_LEGS, WEAR_FEET, WEAR_HANDS,
   WEAR_ARMS, WEAR_SHIELD, WEAR_ABOUT, WEAR_WAIST, WEAR_WRIST_L, WEAR_WRIST_R,
   WEAR_WIELD, WEAR_HOLD, WEAR_DUAL_WIELD, WEAR_EARS, WEAR_EYES,
   WEAR_MISSILE_WIELD, MAX_WEAR
} wear_locations;

#define MAX_HITLOC 14

/* Board Types */
typedef enum
{ BOARD_NOTE, BOARD_MAIL } board_types;

/* Auth Flags */
#define FLAG_WRAUTH		      1
#define FLAG_AUTH		      2

/***************************************************************************
*                                                                         *
*                   VALUES OF INTEREST TO AREA BUILDERS                   *
*                   (End of this section ... stop here)                   *
*                                                                         *
***************************************************************************/

/*
* Conditions.
*/
typedef enum
{
   COND_DRUNK, COND_FULL, COND_THIRST, COND_BLOODTHIRST, MAX_CONDS
} conditions;

/*
* Positions.
*/
typedef enum
{
   POS_DEAD, POS_MORTAL, POS_INCAP, POS_STUNNED, POS_SLEEPING, POS_RESTING,
   POS_SITTING, POS_FIGHTING, POS_STANDING, POS_MOUNTED, POS_SHOVE, POS_DRAG
} positions;

/*
* ACT bits for players.
*/
#define PLR_IS_NPC		      BV00  /* Don't EVER set.   */
#define PLR_BOUGHT_PET		      BV01
#define PLR_SHOVEDRAG		      BV02
#define PLR_AUTOEXIT		      BV03
#define PLR_AUTOLOOT		      BV04
#define PLR_AUTOSAC                   BV05
#define PLR_BLANK		      BV06
#define PLR_OUTCAST 		      BV07
#define PLR_BRIEF		      BV08
#define PLR_COMBINE		      BV09
#define PLR_PROMPT		      BV10
#define PLR_TELNET_GA		      BV11

#define PLR_HOLYLIGHT		   BV12
#define PLR_WIZINVIS		   BV13
#define PLR_ROOMVNUM		   BV14

#define	PLR_SILENCE		   BV15
#define PLR_NO_EMOTE		   BV16
#define PLR_ATTACKER    	   BV17
#define PLR_NO_TELL		   BV18
#define PLR_LOG			   BV19
#define PLR_DENY		   BV20
#define PLR_FREEZE		   BV21
#define PLR_KILLER    	           BV22
/*
#define PLR_    	           BV23
*/
#define PLR_LITTERBUG	           BV24
#define PLR_ANSI	           BV25
#define PLR_SOUND	           BV26
#define PLR_NICE	           BV27
#define PLR_FLEE	           BV28
#define PLR_AUTOGOLD               BV29
#define PLR_AUTOMAP                BV30
#define PLR_AFK                    BV31

/* Bits for pc_data->flags. */
#define PCFLAG_R1                  BV00
/*
#define PCFLAG_                    BV01     extra flag
*/
#define PCFLAG_UNAUTHED		   BV02
#define PCFLAG_NORECALL            BV03
#define PCFLAG_NOINTRO             BV04
#define PCFLAG_GAG		   BV05
#define PCFLAG_RETIRED             BV06
#define PCFLAG_GUEST               BV07
#define PCFLAG_NOSUMMON		   BV08
#define PCFLAG_PAGERON		   BV09
#define PCFLAG_NOTITLE             BV10
#define PCFLAG_ROOM                BV11

typedef enum
{
   TIMER_NONE, TIMER_RECENTFIGHT, TIMER_SHOVEDRAG, TIMER_DO_FUN,
   TIMER_APPLIED, TIMER_PKILLED, TIMER_SKILL_FUN
} timer_types;

struct timer_data
{
   TIMER *prev;
   TIMER *next;
   DO_FUN *do_fun;
   int value;
   short type;
   double count;
};


/*
* Channel bits.
*/
#define	CHANNEL_AUCTION		   BV00
#define	CHANNEL_CHAT		   BV01
#define	CHANNEL_QUEST		   BV02
#define	CHANNEL_IMMTALK		   BV03
#define	CHANNEL_MUSIC		   BV04
#define	CHANNEL_ASK		   BV05
#define	CHANNEL_SHOUT		   BV06
#define	CHANNEL_YELL		   BV07
#define CHANNEL_MONITOR		   BV08
#define CHANNEL_LOG		   BV09
#define CHANNEL_104		   BV10
#define CHANNEL_CLAN		   BV11
#define CHANNEL_BUILD		   BV12
#define CHANNEL_105		   BV13
#define CHANNEL_AVTALK		   BV14
#define CHANNEL_PRAY		   BV15
#define CHANNEL_COUNCIL 	   BV16
#define CHANNEL_GUILD              BV17
#define CHANNEL_COMM		   BV18
#define CHANNEL_TELLS		   BV19
#define CHANNEL_ORDER              BV20
#define CHANNEL_NEWBIE             BV21
#define CHANNEL_WARTALK            BV22
#define CHANNEL_OOC                BV23
#define CHANNEL_SHIP               BV24
#define CHANNEL_SYSTEM             BV25
#define CHANNEL_SPACE              BV26
#define CHANNEL_103		   BV27

#define CHANNEL_CLANTALK	   CHANNEL_CLAN

/* Area defines - Scryn 8/11
*
*/
#define AREA_DELETED		   BV00
#define AREA_LOADED                BV01

/* Area flags - Narn Mar/96 */
#define AFLAG_NOPKILL               BV00
#define AFLAG_PROTOTYPE             BV01

#define MAX_PC_SKILL   50
#define MAX_NPC_SKILL  20
#define MAX_SKILL_SLOT 30
#define MAX_DISCIPLINE 8
#define MAX_EQUIPPED_DISCIPLINE 5

#define DISC_TYPES     0
#define DISC_FACTORS   1

/*
* Prototype for a mob.
* This is the in-memory version of #MOBILES.
*/
struct mob_index_data
{
   MOB_INDEX_DATA *next;
   MOB_INDEX_DATA *next_sort;
   SPEC_FUN *spec_fun;
   SPEC_FUN *spec_2;
   SHOP_DATA *pShop;
   REPAIR_DATA *rShop;
   MPROG_DATA *mudprogs;
   EXT_BV progtypes;
   const char *player_name;
   const char *short_descr;
   const char *long_descr;
   const char *description;
   const char *spec_funname;
   const char *spec_funname2;
   int vnum;
   short count;
   short killed;
   short sex;
   short level;
   int act;
   EXT_BV affected_by;
   short alignment;
   short mobthac0;   /* Unused */
   short evasion;
   short armor;
   short hitnodice;
   short hitsizedice;
   short hitplus;
   short damnodice;
   short damsizedice;
   short damplus;
   short numattacks;
   int gold;
   int exp;
   int xflags;
   int resistant;
   int immune;
   int susceptible;
   int attacks;
   int defenses;
   int speaks;
   int speaking;
   short position;
   short defposition;
   short height;
   short weight;
   short race;
   short hitroll;
   short damroll;
   short perm_str;
   short perm_int;
   short perm_wis;
   short perm_dex;
   short perm_con;
   short perm_cha;
   short perm_lck;
   short perm_frc;
   short perm_agi;
   short saving_poison_death;
   short saving_wand;
   short saving_para_petri;
   short saving_breath;
   short saving_spell_staff;
   int vip_flags;
   EXT_BV damtype;
   short penetration[MAX_DAMTYPE];
   short resistance[MAX_DAMTYPE];
   short damtype_potency[MAX_DAMTYPE];
   short dodge;
   short parry;
   LOOT_DATA *first_loot;
   LOOT_DATA *last_loot;
   double round;
   int haste;
   double tspeed; /* thought speed, how often a mob thinks */
   int npc_skills[MAX_NPC_SKILL];
   TEACH_DATA *first_teach;
   TEACH_DATA *last_teach;
   AV_QUEST *first_available_quest;
   AV_QUEST *last_available_quest;
};

struct loot_data
{
   LOOT_DATA *next;
   LOOT_DATA *prev;
   int type;
   int vnum;
   int percent;
   int amount;
};

struct threat_data
{
   THREAT_DATA *next;
   THREAT_DATA *prev;
   CHAR_DATA *angry_at;
   CHAR_DATA *angered;
   int constant;
   int fickle;
};

struct hunt_hate_fear
{
   const char *name;
   CHAR_DATA *who;
};

struct fighting_data
{
   CHAR_DATA *who;
   int xp;
   short align;
   short duration;
   short timeskilled;
};

struct extracted_char_data
{
   EXTRACT_CHAR_DATA *next;
   CHAR_DATA *ch;
   ROOM_INDEX_DATA *room;
   ch_ret retcode;
   bool extract;
};



/*
* One character (PC or NPC).
* (Shouldn't most of that build interface stuff use substate, dest_buf,
* spare_ptr and tempnum?  Seems a little redundant)
*/
struct char_data
{
   CHAR_DATA *next;
   CHAR_DATA *prev;
   CHAR_DATA *next_in_room;
   CHAR_DATA *prev_in_room;
   CHAR_DATA *master;
   CHAR_DATA *leader;
   FIGHT_DATA *fighting;
   CHAR_DATA *reply;
   CHAR_DATA *switched;
   CHAR_DATA *mount;
   HHF_DATA *hunting;
   HHF_DATA *fearing;
   HHF_DATA *hating;
   SPEC_FUN *spec_fun;
   SPEC_FUN *spec_2;
   const char *spec_funname;
   const char *spec_funname2;
   MPROG_ACT_LIST *mpact;
   int mpactnum;
   unsigned short mpscriptpos;
   MOB_INDEX_DATA *pIndexData;
   DESCRIPTOR_DATA *desc;
   AFFECT_DATA *first_affect;
   AFFECT_DATA *last_affect;
   NOTE_DATA *pnote;
   NOTE_DATA *comments;
   OBJ_DATA *first_carrying;
   OBJ_DATA *last_carrying;
   ROOM_INDEX_DATA *in_room;
   ROOM_INDEX_DATA *was_in_room;
   ROOM_INDEX_DATA *was_sentinel;
   ROOM_INDEX_DATA *plr_home;
   PC_DATA *pcdata;
   DO_FUN *last_cmd;
   DO_FUN *prev_cmd; /* mapping */
   void *dest_buf;
   void *dest_buf_2;
   void *spare_ptr;
   int tempnum;
   EDITOR_DATA *editor;
   TIMER *first_timer;
   TIMER *last_timer;
   const char *name;
   const char *short_descr;
   const char *long_descr;
   const char *description;
   short num_fighting;
   short substate;
   short sex;
   short race;
   short top_level;
   short skill_level[MAX_ABILITY];
   short trust;
   int played;
   time_t logon;
   time_t save_time;
   short timer;
   short wait;
   short hit;
   short max_hit;
   short mana;
   short max_mana;
   short move;
   short max_move;
   short numattacks;
   int gold;
   long experience[MAX_ABILITY];
   int act;
   EXT_BV affected_by;
   int carry_weight;
   int carry_number;
   int xflags;
   int resistant;
   int immune;
   int susceptible;
   int attacks;
   int defenses;
   int speaks;
   int speaking;
   short saving_poison_death;
   short saving_wand;
   short saving_para_petri;
   short saving_breath;
   short saving_spell_staff;
   short alignment;
   short barenumdie;
   short baresizedie;
   short wepnumdie;
   short wepsizedie;
   short mobthac0;
   short hitroll;
   short damroll;
   short hitplus;
   short damplus;
   short wepplus;
   short position;
   short defposition;
   short height;
   short weight;
   short armor; //Global Armor Apply
   short evasion; //Chance to Evade
   short wimpy;
   int deaf;
   short perm_str;
   short perm_int;
   short perm_wis;
   short perm_dex;
   short perm_con;
   short perm_cha;
   short perm_lck;
   short perm_frc;
   short perm_agi;
   short mod_str;
   short mod_int;
   short mod_wis;
   short mod_dex;
   short mod_con;
   short mod_cha;
   short mod_lck;
   short mod_frc;
   short mod_agi;
   short mental_state;  /* simplified */
   short emotional_state;  /* simplified */
   int retran;
   int regoto;
   short mobinvis;   /* Mobinvis level SB */
   int vip_flags;
   short backup_wait;   /* reinforcements */
   int backup_mob;   /* reinforcements */
   short was_stunned;
   const char *mob_clan;   /* for spec_clan_guard.. set by postguard */
   GUARD_DATA *guard_data;
   short main_ability;
   short colors[MAX_COLORS];
   int home_vnum; /* hotboot tracker */
   int resetvnum;
   int resetnum;
   EXT_BV damtype;
   short penetration[MAX_DAMTYPE];
   short resistance[MAX_DAMTYPE];
   short damtype_potency[MAX_DAMTYPE];
   short parry;
   short dodge;
   GROUP_DATA *in_group;
   GROUP_DATA *group_invite;
   int threat;
   SKILLTYPE *casting_skill;
   CHAR_DATA *skill_target;
   CD_DATA *first_cooldown;
   CD_DATA *last_cooldown;
   double round;
   double next_round; /* next combat round, when? */
   int haste_from_item;
   int haste_from_skill;
   int haste_from_spell;
   int mob_haste;
   double tspeed; /* mob thought speed */
   int fom; /* Mob Frame of Mind */
   double next_thought; /* when a mob will have its next thought */
   SKILLTYPE *pc_skills[MAX_PC_SKILL];
   SKILLTYPE *skill_slots[MAX_SKILL_SLOT];
   int top_sn;
   DISC_DATA *equipped_disciplines[MAX_EQUIPPED_DISCIPLINE];
   DISC_DATA *known_disciplines[MAX_DISCIPLINE];
   FACTOR_DATA *first_factor; /* Available factors that can be used on skills */
   FACTOR_DATA *last_factor;
   EXT_BV avail_targettypes;
   EXT_BV avail_damtypes;
   EXT_BV avail_costtypes;
   EXT_BV avail_skilltypes;
   EXT_BV avail_skillstyles;
   int stat_build;
   PLAYER_QUEST *first_pquest;
   PLAYER_QUEST *last_pquest;
   short dbl_attack;
};

#define PC_BASE_HP 200
#define PC_BASE_MOVE 0
#define PC_BASE_MANA 0

typedef enum
{
   FOM_IDLE, FOM_FIGHTING, FOM_HUNTING, MAX_FOM
} f_o_ms;

#define MAX_GROUP  6
#define BASE_ROUND 2 /* seconds */

struct group_data
{
   CHAR_DATA *leader;
   CHAR_DATA *members[MAX_GROUP];
   int member_count;
};

struct killed_data
{
   int vnum;
   char count;
};

/*
* Data which only PC's have.
*/
struct pc_data
{
   CLAN_DATA *clan;
   AREA_DATA *area;
   const char *homepage;
   const char *clan_name;
   const char *pwd;
   const char *email;
   const char *bamfin;
   const char *bamfout;
   const char *rank;
   const char *title;
   const char *bestowments;   /* Special bestowed commands     */
   int flags;  /* Whether the player is deadly and whatever else we add.      */
   int pkills; /* Number of pkills on behalf of clan */
   int pdeaths;   /* Number of times pkilled (legally)  */
   int mkills; /* Number of mobs killed         */
   int mdeaths;   /* Number of deaths due to mobs       */
   int illegal_pk;   /* Number of illegal pk's committed   */
   long int outcast_time;  /* The time at which the char was outcast */
   long int restore_time;  /* The last time the char did a restore all */
   int r_range_lo; /* room range */
   int r_range_hi;
   int m_range_lo; /* mob range  */
   int m_range_hi;
   int o_range_lo; /* obj range  */
   int o_range_hi;
   short wizinvis;   /* wizinvis level */
   short min_snoop;  /* minimum snoop level */
   short condition[MAX_CONDS];
   short learned[MAX_SKILL];
   KILLED_DATA killed[MAX_KILLTRACK];
   short quest_number;  /* current *QUEST BEING DONE* DON'T REMOVE! */
   short quest_curr; /* current number of quest points */
   int quest_accum;  /* quest points accumulated in players life */
   int auth_state;
   time_t release_date; /* Auto-helling.. Altrag */
   const char *helled_by;
   const char *bio;  /* Personal Bio */
   const char *authed_by;  /* what crazy imm authed this name ;) */
   SKILLTYPE *special_skills[5]; /* personalized skills/spells */
   const char *prompt;  /* User config prompts */
   const char *subprompt;  /* Substate prompt */
   short pagerlen;   /* For pager (NOT menus) */
   bool openedtourney;
   short addiction[10];
   short drug_level[10];
   int wanted_flags;
   long bank;
#ifdef IMC
   IMC_CHARDATA *imcchardata;
#endif
   bool hotboot;  /* hotboot tracker */
};



/*
* Liquids.
*/
#define LIQ_WATER        0
#define LIQ_MAX		19

struct liq_type
{
   const char *liq_name;
   const char *liq_color;
   short liq_affect[3];
};



/*
* Extra description data for a room or object.
*/
struct extra_descr_data
{
   EXTRA_DESCR_DATA *next; /* Next in list                     */
   EXTRA_DESCR_DATA *prev; /* Previous in list                 */
   const char *keyword; /* Keyword in look/examine          */
   const char *description;   /* What to see                      */
};

struct item_material
{
   ITEM_MATERIAL *next;
   ITEM_MATERIAL *prev;
   OBJ_INDEX_DATA *object;
   int amount;
};

struct pool_data
{
   POOL_DATA *next;
   POOL_DATA *prev;
   int id;
   int location;
   int minstat;
   int maxstat;
   int minlevel;
   int maxlevel;
   int rules[MAX_ITEM_WEAR];

};

/*
* Prototype for an object.
*/
struct obj_index_data
{
   OBJ_INDEX_DATA *next;
   OBJ_INDEX_DATA *next_sort;
   EXTRA_DESCR_DATA *first_extradesc;
   EXTRA_DESCR_DATA *last_extradesc;
   AFFECT_DATA *first_affect;
   AFFECT_DATA *last_affect;
   MPROG_DATA *mudprogs;   /* objprogs */
   EXT_BV progtypes; /* objprogs */
   const char *name;
   const char *short_descr;
   const char *description;
   const char *action_desc;
   int vnum;
   short level;
   short item_type;
   int extra_flags;
   int magic_flags;  /*Need more bitvectors for spells - Scryn */
   int wear_flags;
   short count;
   short weight;
   int cost;
   int value[6];
   int serial;
   short layers;
   int rent;   /* Unused */
   EXT_BV damtype;
   ITEM_MATERIAL *first_material;
   ITEM_MATERIAL *last_material;
   EXT_BV temper;
   double speed;
   EXT_BV quality;
   int max_pool;
};


/*
* One object.
*/
struct obj_data
{
   OBJ_DATA *next;
   OBJ_DATA *prev;
   OBJ_DATA *next_content;
   OBJ_DATA *prev_content;
   OBJ_DATA *first_content;
   OBJ_DATA *last_content;
   OBJ_DATA *in_obj;
   CHAR_DATA *carried_by;
   EXTRA_DESCR_DATA *first_extradesc;
   EXTRA_DESCR_DATA *last_extradesc;
   AFFECT_DATA *first_affect;
   AFFECT_DATA *last_affect;
   OBJ_INDEX_DATA *pIndexData;
   ROOM_INDEX_DATA *in_room;
   const char *armed_by;
   const char *name;
   const char *short_descr;
   const char *description;
   const char *action_desc;
   short item_type;
   short mpscriptpos;
   int extra_flags;
   int magic_flags;  /*Need more bitvectors for spells - Scryn */
   int wear_flags;
   int blaster_setting;
   MPROG_ACT_LIST *mpact;  /* mudprogs */
   int mpactnum;  /* mudprogs */
   short wear_loc;
   short weight;
   int cost;
   short level;
   short timer;
   int value[6];
   short count;   /* support for object grouping */
   int serial; /* serial number         */
   int room_vnum; /* hotboot tracker */
   EXT_BV damtype;
   ITEM_MATERIAL *first_material;
   ITEM_MATERIAL *last_material;
   EXT_BV temper;
   double speed;
   EXT_BV quality;
   int max_pool;
};


/*
* Exit data.
*/
struct exit_data
{
   EXIT_DATA *prev;  /* previous exit in linked list  */
   EXIT_DATA *next;  /* next exit in linked list   */
   EXIT_DATA *rexit; /* Reverse exit pointer    */
   ROOM_INDEX_DATA *to_room;  /* Pointer to destination room   */
   const char *keyword; /* Keywords for exit or door  */
   const char *description;   /* Description of exit     */
   int vnum;   /* Vnum of room exit leads to */
   int rvnum;  /* Vnum of room in opposite dir  */
   int exit_info; /* door states & other flags  */
   int key; /* Key vnum       */
   short vdir; /* Physical "direction"    */
   short distance;   /* how far to the next room   */
};



/*
* Reset commands:
*   '*': comment
*   'M': read a mobile
*   'O': read an object
*   'P': put object in object
*   'G': give object to mobile
*   'E': equip object to mobile
*   'H': hide an object
*   'B': set a bitvector
*   'T': trap an object
*   'D': set state of door
*   'R': randomize room exits
*   'S': stop (end of list)
*/

/*
* Area-reset definition.
*/
struct reset_data
{
   RESET_DATA *next;
   RESET_DATA *prev;
   RESET_DATA *first_reset;
   RESET_DATA *last_reset;
   RESET_DATA *next_reset;
   RESET_DATA *prev_reset;
   char command;
   int extra;
   int arg1;
   int arg2;
   int arg3;
   bool sreset;
};

/* Constants for arg2 of 'B' resets. */
#define BIT_RESET_DOOR			0
#define BIT_RESET_OBJECT		1
#define BIT_RESET_MOBILE		2
#define BIT_RESET_ROOM			3
#define BIT_RESET_TYPE_MASK		0xFF  /* 256 should be enough */
#define BIT_RESET_DOOR_THRESHOLD	8
#define BIT_RESET_DOOR_MASK		0xFF00   /* 256 should be enough */
#define BIT_RESET_SET			BV30
#define BIT_RESET_TOGGLE		BV31
#define BIT_RESET_FREEBITS	  0x3FFF0000   /* For reference */

/*
* Area definition.
*/
struct area_data
{
   AREA_DATA *next;
   AREA_DATA *prev;
   AREA_DATA *next_sort;
   AREA_DATA *prev_sort;
   AREA_DATA *next_sort_name; /* Used for alphanum. sort */
   AREA_DATA *prev_sort_name; /* Ditto, Fireblade */
   PLANET_DATA *planet;
   AREA_DATA *next_on_planet;
   AREA_DATA *prev_on_planet;
   ROOM_INDEX_DATA *first_room;
   ROOM_INDEX_DATA *last_room;
   const char *name;
   const char *filename;
   int flags;
   short version;
   short status;  /* h, 8/11 */
   short age;
   short nplayer;
   short reset_frequency;
   int low_r_vnum;
   int hi_r_vnum;
   int low_o_vnum;
   int hi_o_vnum;
   int low_m_vnum;
   int hi_m_vnum;
   int low_soft_range;
   int hi_soft_range;
   int low_hard_range;
   int hi_hard_range;
   const char *author;  /* Scryn */
   const char *resetmsg;   /* Rennard */
   short max_players;
   int mkills;
   int mdeaths;
   int pkills;
   int pdeaths;
   int gold_looted;
   int illegal_pk;
   int high_economy;
   int low_economy;
   LOOT_DATA *first_loot;
   LOOT_DATA *last_loot;
};

/*
* Used to keep track of system settings and statistics		-Thoric
*/
struct system_data
{
   int maxplayers;   /* Maximum players this boot   */
   int alltimemax;   /* Maximum players ever   */
   const char *time_of_max;   /* Time of max ever */
   bool NO_NAME_RESOLVING; /* Hostnames are not resolved  */
   bool DENY_NEW_PLAYERS;  /* New players cannot connect  */
   bool WAIT_FOR_AUTH;  /* New players must be auth'ed */
   short read_all_mail; /* Read all player mail(was 54) */
   short read_mail_free;   /* Read mail for free (was 51) */
   short write_mail_free;  /* Write mail for free(was 51) */
   short take_others_mail; /* Take others mail (was 54)   */
   short muse_level; /* Level of muse channel */
   short think_level;   /* Level of think channel LEVEL_HIGOD */
   short build_level;   /* Level of build channel LEVEL_BUILD */
   short log_level;  /* Level of log channel LEVEL LOG */
   short level_modify_proto;  /* Level to modify prototype stuff LEVEL_LESSER */
   short level_override_private; /* override private flag */
   short level_mset_player;   /* Level to mset a player */
   short stun_plr_vs_plr;  /* Stun mod player vs. player */
   short stun_regular;  /* Stun difficult */
   short dam_plr_vs_plr;   /* Damage mod player vs. player */
   short dam_plr_vs_mob;   /* Damage mod player vs. mobile */
   short dam_mob_vs_plr;   /* Damage mod mobile vs. player */
   short dam_mob_vs_mob;   /* Damage mod mobile vs. mobile */
   short level_getobjnotake;  /* Get objects without take flag */
   short level_forcepc; /* The level at which you can use force on players. */
   short max_sn;  /* Max skills */
   const char *guild_overseer;   /* Pointer to char containing the name of the */
   const char *guild_advisor; /* guild overseer and advisor. */
   int save_flags;   /* Toggles for saving conditions */
   short save_frequency;   /* How old to autosave someone */
   void *dlHandle;
};


/*
* Room type.
*/
struct room_index_data
{
   ROOM_INDEX_DATA *next;
   ROOM_INDEX_DATA *next_sort;
   CHAR_DATA *first_person;
   CHAR_DATA *last_person;
   OBJ_DATA *first_content;
   OBJ_DATA *last_content;
   EXTRA_DESCR_DATA *first_extradesc;
   EXTRA_DESCR_DATA *last_extradesc;
   AREA_DATA *area;
   EXIT_DATA *first_exit;
   EXIT_DATA *last_exit;
   SHIP_DATA *first_ship;
   SHIP_DATA *last_ship;
   RESET_DATA *first_reset;
   RESET_DATA *last_reset;
   RESET_DATA *last_mob_reset;
   RESET_DATA *last_obj_reset;
   ROOM_INDEX_DATA *next_aroom; /* Rooms within an area */
   ROOM_INDEX_DATA *prev_aroom;
   const char *name;
   const char *description;
   int vnum;
   int room_flags;
   MPROG_ACT_LIST *mpact;  /* mudprogs */
   int mpactnum;  /* mudprogs */
   MPROG_DATA *mudprogs;   /* mudprogs */
   short mpscriptpos;
   EXT_BV progtypes; /* mudprogs */
   short light;
   short sector_type;
   int tele_vnum;
   short tele_delay;
   short tunnel;  /* max people that will fit */
};

/*
* Delayed teleport type.
*/
struct teleport_data
{
   TELEPORT_DATA *next;
   TELEPORT_DATA *prev;
   ROOM_INDEX_DATA *room;
   short timer;
};

/*
* Types of skill numbers.  Used to keep separate lists of sn's
* Must be non-overlapping with spell/skill types,
* but may be arbitrary beyond that.
*/
#define TYPE_UNDEFINED               -1
#define TYPE_HIT                     1000 /* allows for 1000 skills/spells */
#define TYPE_HERB		     2000   /* allows for 1000 attack types  */
#define TYPE_PERSONAL		     3000   /* allows for 1000 herb types    */

/*
*  Target types.
*/
typedef enum
{
   TAR_IGNORE, TAR_CHAR_OFFENSIVE, TAR_CHAR_DEFENSIVE, TAR_CHAR_SELF,
   TAR_OBJ_INV, TAR_CHAR_ANY, TAR_AOE_FRIENDLY, TAR_AOE_ENEMY, TAR_AOE_ENEMYGROUP,
   TAR_CHAR_UNSET, TAR_CHAR_MAX
} target_types;

typedef enum
{
   SKILL_UNKNOWN, SKILL_SPELL, SKILL_SKILL, SKILL_WEAPON, SKILL_TONGUE,
   SKILL_HERB, SKILL_PASSIVE, SKILL_UNSET, MAX_SKILLTYPE
} skill_types;

typedef enum
{
   STYLE_HEALING, STYLE_DAMAGE, STYLE_BUFF, STYLE_ENFEEBLE,
   STYLE_REDIRECT, STYLE_CLEANSE, STYLE_SUMMON, STYLE_POLYMORPH,
   STYLE_UNSET, STYLE_MAX
} style_types;

struct timerset
{
   int num_uses;
   struct timeval total_time;
   struct timeval min_time;
   struct timeval max_time;
};

/*
* Skills include spells as a particular case.
*/
struct skill_type
{
   const char *name; /* Name of skill     */
   SPELL_FUN *spell_fun;   /* Spell pointer (for spells) */
   const char *spell_fun_name;   /* Spell function name - Trax */
   DO_FUN *skill_fun;      /* Skill pointer (for skills) */
   const char *skill_fun_name;   /* Skill function name - Trax */
   short target;  /* Legal targets     */
   short minimum_position; /* Position for caster / user */
   short slot; /* Slot for #OBJECT loading   */
   short min_mana;   /* Minimum mana used    */
   short beats;   /* Rounds required to use skill  */
   const char *noun_damage;   /* Damage message    */
   const char *msg_off; /* Wear off message     */
   short guild;   /* Which guild the skill belongs to */
   short min_level;  /* Minimum level to be able to cast */
   short type; /* Spell/Skill/Weapon/Tongue  */
   int flags;  /* extra stuff       */
   const char *hit_char;   /* Success message to caster  */
   const char *hit_vict;   /* Success message to victim  */
   const char *hit_room;   /* Success message to room */
   const char *miss_char;  /* Failure message to caster  */
   const char *miss_vict;  /* Failure message to victim  */
   const char *miss_room;  /* Failure message to room */
   const char *die_char;   /* Victim death msg to caster */
   const char *die_vict;   /* Victim death msg to victim */
   const char *die_room;   /* Victim death msg to room   */
   const char *imm_char;   /* Victim immune msg to caster   */
   const char *imm_vict;   /* Victim immune msg to victim   */
   const char *imm_room;   /* Victim immune msg to room  */
   const char *dice; /* Dice roll         */
   int value;  /* Misc value        */
   char saves; /* What saving spell applies  */
   char difficulty;  /* Difficulty of casting/learning */
   AFFECT_DATA *first_affect;  /* Spell affects, if any   */
   AFFECT_DATA *last_affect;
   const char *components; /* Spell components, if any   */
   const char *teachers;   /* Skill requires a special teacher */
   char participants;   /* # of required participants */
   struct timerset userec; /* Usage record         */
   int alignment; /* for jedi powers */
   short min_move;
   short min_hp;
   short style;
   double base_roll_boost;
   STAT_BOOST *first_statboost;
   STAT_BOOST *last_statboost;
   EXT_BV damtype;
   EXT_BV cost;
   int charge;
   int threat;
   int cooldown;
   const char *cdmsg;
   FACTOR_DATA *first_factor; /* What factors are set on the skill */
   FACTOR_DATA *last_factor;
};

struct stat_boost
{
   STAT_BOOST *next;
   STAT_BOOST *prev;
   int from_id;
   int location;
   double modifier;
};


struct discipline_data
{
   DISC_DATA *next;
   DISC_DATA *prev;
   FACTOR_DATA *first_factor;
   FACTOR_DATA *last_factor;
   AFFECT_DATA *first_affect;
   AFFECT_DATA *last_affect;
   const char *name;
   int id;
   int min_level;
   int hit_gain;
   int move_gain;
   int mana_gain;
   /* Resuable Types */
   EXT_BV cost;
   EXT_BV skill_type;
   EXT_BV skill_style;
   EXT_BV damtype;
   EXT_BV target_type;
};

struct factor_data
{
   DISC_DATA *owner;
   FACTOR_DATA *next;
   FACTOR_DATA *prev;
   int id;
   int factor_type;
   int location;
   EXT_BV affect;
   double modifier;
   int apply_type;
   double duration;
};

typedef enum
{
   APPLY_FACTOR, STAT_FACTOR, BASEROLL_FACTOR, MAX_FACTOR
} factor_types;

typedef enum
{
   SKILLTYPE_TYPE, STYLE_TYPE, COST_TYPE, DAMTYPE_TYPE, TARGET_TYPE, MAX_TYPE
} skilltype_types;

typedef enum
{
   COST_HP, COST_MANA, COST_MOVE, MAX_COST
} cost_types;

typedef enum
{
   APPLY_JOIN_SELF, APPLY_JOIN_TARGET, APPLY_OVERRIDE_SELF, APPLY_OVERRIDE_TARGET, NO_APPLY, MAX_APPLYTYPE
} applytype_types;
struct auction_data
{
   OBJ_DATA *item;   /* a pointer to the item */
   CHAR_DATA *seller;   /* a pointer to the seller - which may NOT quit */
   CHAR_DATA *buyer; /* a pointer to the buyer - which may NOT quit */
   int bet; /* last bet - or 0 if noone has bet anything */
   short going;   /* 1,2, sold */
   short pulse;   /* how many pulses (.25 sec) until another call-out ? */
   int starting;
};


/*
* These are skill_lookup return values for common skills and spells.
*/
extern short gsn_starfighters;
extern short gsn_midships;
extern short gsn_capitalships;
extern short gsn_weaponsystems;
extern short gsn_navigation;
extern short gsn_shipsystems;
extern short gsn_tractorbeams;
extern short gsn_shipmaintenance;
extern short gsn_spacecombat;
extern short gsn_spacecombat2;
extern short gsn_spacecombat3;

extern short gsn_reinforcements;
extern short gsn_postguard;

extern short gsn_addpatrol;
extern short gsn_eliteguard;
extern short gsn_specialforces;
extern short gsn_jail;
extern short gsn_smalltalk;
extern short gsn_propeganda;
extern short gsn_bribe;
extern short gsn_seduce;
extern short gsn_masspropeganda;
extern short gsn_gather_intelligence;

extern short gsn_torture;
extern short gsn_snipe;
extern short gsn_throw;
extern short gsn_disguise;
extern short gsn_mine;
extern short gsn_grenades;
extern short gsn_first_aid;

extern short gsn_beg;
extern short gsn_makeblade;
extern short gsn_makejewelry;
extern short gsn_makeblaster;
extern short gsn_makelight;
extern short gsn_makecomlink;
extern short gsn_makegrenade;
extern short gsn_makelandmine;
extern short gsn_makearmor;
extern short gsn_makeshield;
extern short gsn_makecontainer;
extern short gsn_gemcutting;
extern short gsn_lightsaber_crafting;
extern short gsn_spice_refining;

extern short gsn_detrap;
extern short gsn_backstab;
extern short gsn_circle;
extern short gsn_dodge;
extern short gsn_hide;
extern short gsn_peek;
extern short gsn_pick_lock;
extern short gsn_scan;
extern short gsn_sneak;
extern short gsn_steal;
extern short gsn_gouge;
extern short gsn_track;
extern short gsn_search;
extern short gsn_dig;
extern short gsn_mount;
extern short gsn_bashdoor;
extern short gsn_berserk;
extern short gsn_hitall;
extern short gsn_pickshiplock;
extern short gsn_hijack;

extern short gsn_disarm;
extern short gsn_enhanced_damage;
extern short gsn_kick;
extern short gsn_parry;
extern short gsn_rescue;
extern short gsn_second_attack;
extern short gsn_third_attack;
extern short gsn_dual_wield;


extern short gsn_aid;

/* used to do specific lookups */
extern short gsn_first_spell;
extern short gsn_first_skill;
extern short gsn_first_weapon;
extern short gsn_first_tongue;
extern short gsn_top_sn;

/* spells */
extern short gsn_blindness;
extern short gsn_charm_person;
extern short gsn_aqua_breath;
extern short gsn_invis;
extern short gsn_mass_invis;
extern short gsn_poison;
extern short gsn_sleep;
extern short gsn_possess;
extern short gsn_fireball; /* for fireshield  */
extern short gsn_lightning_bolt; /* for shockshield */

/* newer attack skills */
extern short gsn_punch;
extern short gsn_bash;
extern short gsn_stun;

extern short gsn_poison_weapon;
extern short gsn_climb;

extern short gsn_blasters;
extern short gsn_force_pikes;
extern short gsn_bowcasters;
extern short gsn_lightsabers;
extern short gsn_vibro_blades;
extern short gsn_flexible_arms;
extern short gsn_talonous_arms;
extern short gsn_bludgeons;

extern short gsn_grip;

/* languages */
extern short gsn_common;
extern short gsn_wookiee;
extern short gsn_twilek;
extern short gsn_rodian;
extern short gsn_hutt;
extern short gsn_mon_calamari;
extern short gsn_noghri;
extern short gsn_gamorrean;
extern short gsn_jawa;
extern short gsn_adarian;
extern short gsn_ewok;
extern short gsn_verpine;
extern short gsn_defel;
extern short gsn_trandoshan;
extern short gsn_chadra_fan;
extern short gsn_quarren;
extern short gsn_duinduogwuin;

// Utility macros.
int umin( int check, int ncheck );
int umax( int check, int ncheck );
int urange( int mincheck, int check, int maxcheck );

#define UMIN( a, b )      ( umin( (a), (b) ) )
#define UMAX( a, b )      ( umax( (a), (b) ) )
#define URANGE(a, b, c )  ( urange( (a), (b), (c) ) )
#define LOWER( c )        ( (c) >= 'A' && (c) <= 'Z' ? (c) + 'a' - 'A' : (c) )
#define UPPER( c )        ( (c) >= 'a' && (c) <= 'z' ? (c) + 'A' - 'a' : (c) )

#define IS_SET(flag, bit)	((flag) & (bit))
#define SET_BIT(var, bit)	((var) |= (bit))
#define REMOVE_BIT(var, bit)	((var) &= ~(bit))
#define TOGGLE_BIT(var, bit)	((var) ^= (bit))

/*
 * Macros for accessing virtually unlimited bitvectors.         -Thoric
 *
 * Note that these macros use the bit number rather than the bit value
 * itself -- which means that you can only access _one_ bit at a time
 *
 * This code uses an array of integers
 */

/*
 * The functions for these prototypes can be found in misc.c
 * They are up here because they are used by the macros below
 */
bool ext_is_empty args( ( EXT_BV * bits ) );
void ext_clear_bits args( ( EXT_BV * bits ) );
int ext_has_bits args( ( EXT_BV * var, EXT_BV * bits ) );
bool ext_same_bits args( ( EXT_BV * var, EXT_BV * bits ) );
void ext_set_bits args( ( EXT_BV * var, EXT_BV * bits ) );
void ext_remove_bits args( ( EXT_BV * var, EXT_BV * bits ) );
void ext_toggle_bits args( ( EXT_BV * var, EXT_BV * bits ) );

/*
 * Here are the extended bitvector macros:
 */
#define xIS_SET(var, bit)       ((var).bits[(bit) >> RSV] & 1 << ((bit) & XBM))
#define xSET_BIT(var, bit)      ((var).bits[(bit) >> RSV] |= 1 << ((bit) & XBM))
#define xSET_BITS(var, bit)     (ext_set_bits(&(var), &(bit)))
#define xREMOVE_BIT(var, bit)   ((var).bits[(bit) >> RSV] &= ~(1 << ((bit) & XBM)))
#define xREMOVE_BITS(var, bit)  (ext_remove_bits(&(var), &(bit)))
#define xTOGGLE_BIT(var, bit)   ((var).bits[(bit) >> RSV] ^= 1 << ((bit) & XBM))
#define xTOGGLE_BITS(var, bit)  (ext_toggle_bits(&(var), &(bit)))
#define xCLEAR_BITS(var)        (ext_clear_bits(&(var)))
#define xIS_EMPTY(var)          (ext_is_empty(&(var)))
#define xHAS_BITS(var, bit)     (ext_has_bits(&(var), &(bit)))
#define xSAME_BITS(var, bit)    (ext_same_bits(&(var), &(bit)))


/*
* Memory allocation macros.
*/
#define CREATE(result, type, number)                                    \
   do                                                                      \
{                                                                       \
   if (!((result) = (type *) calloc ((number), sizeof(type))))          \
{                                                                    \
   perror("malloc failure");                                         \
   fprintf(stderr, "Malloc failure @ %s:%d\n", __FILE__, __LINE__ ); \
   abort();                                                          \
}                                                                    \
} while(0)

#define RECREATE(result,type,number)                                    \
   do                                                                      \
{                                                                       \
   if(!((result) = (type *)realloc((result), sizeof(type) * (number)))) \
{                                                                    \
   perror("realloc failure");                                        \
   fprintf(stderr, "Realloc failure @ %s:%d\n", __FILE__, __LINE__); \
   abort();                                                          \
}                                                                    \
} while(0)

#define DISPOSE(point)                      \
   do                                          \
{                                           \
   if( (point) )                            \
{                                        \
   free( (void*)(point) );		    \
   (point) = NULL;                       \
}                                        \
} while(0)

#ifdef HASHSTR
#define STRALLOC(point)		str_alloc((point))
#define QUICKLINK(point)	quick_link((point))
#define STRFREE(point)                          \
   do                                              \
{                                               \
   if((point))                                  \
{                                            \
   if( str_free((point)) == -1 )             \
   bug( "&RSTRFREEing bad pointer: %s, line %d", __FILE__, __LINE__ ); \
   (point) = NULL;                           \
}                                            \
} while(0)
#else
#define STRALLOC(point)		str_dup((point))
#define QUICKLINK(point)	str_dup((point))
#define STRFREE(point)		DISPOSE((point))
#endif

/* double-linked list handling macros -Thoric */
/* Updated by Scion 8/6/1999 */
#define LINK(link, first, last, next, prev) \
   do                                          \
{                                           \
   if ( !(first) )                          \
{                                        \
   (first) = (link);                     \
   (last) = (link);                      \
}                                        \
   else                                     \
   (last)->next = (link);                \
   (link)->next = NULL;                     \
   if ((first) == (link))                   \
   (link)->prev = NULL;                  \
   else                                     \
   (link)->prev = (last);                \
   (last) = (link);                         \
} while(0)

#define INSERT(link, insert, first, next, prev) \
   do                                              \
{                                               \
   (link)->prev = (insert)->prev;               \
   if ( !(insert)->prev )                       \
   (first) = (link);                         \
   else                                         \
   (insert)->prev->next = (link);            \
   (insert)->prev = (link);                     \
   (link)->next = (insert);                     \
} while(0)

#define UNLINK(link, first, last, next, prev)   \
   do                                              \
{                                               \
   if ( !(link)->prev )                         \
{                                            \
   (first) = (link)->next;                   \
   if ((first))                              \
   (first)->prev = NULL;                  \
}                                            \
   else                                         \
{                                            \
   (link)->prev->next = (link)->next;        \
}                                            \
   if ( !(link)->next )                         \
{                                            \
   (last) = (link)->prev;                    \
   if((last))                                \
   (last)->next = NULL;                   \
}                                            \
   else                                         \
{                                            \
   (link)->next->prev = (link)->prev;        \
}                                            \
} while(0)

#define CHECK_LINKS(first, last, next, prev, type)		\
   do {								\
   type *ptr, *pptr = NULL;					\
   if ( !(first) && !(last) )					\
   break;							\
   if ( !(first) )						\
{								\
   bug( "CHECK_LINKS: last with NULL first!  %s.",		\
   __STRING(first) );					\
   for ( ptr = (last); ptr->prev; ptr = ptr->prev );		\
   (first) = ptr;						\
}								\
   else if ( !(last) )						\
{								\
   bug( "CHECK_LINKS: first with NULL last!  %s.",		\
   __STRING(first) );					\
   for ( ptr = (first); ptr->next; ptr = ptr->next );		\
   (last) = ptr;						\
}								\
   if ( (first) )						\
{								\
   for ( ptr = (first); ptr; ptr = ptr->next )			\
{								\
   if ( ptr->prev != pptr )					\
{								\
   bug( "CHECK_LINKS(%s): %p:->prev != %p.  Fixing.",	\
   __STRING(first), ptr, pptr );			\
   ptr->prev = pptr;					\
}								\
   if ( ptr->prev && ptr->prev->next != ptr )		\
{								\
   bug( "CHECK_LINKS(%s): %p:->prev->next != %p.  Fixing.",\
   __STRING(first), ptr, ptr );			\
   ptr->prev->next = ptr;					\
}								\
   pptr = ptr;						\
}								\
   pptr = NULL;						\
}								\
   if ( (last) )							\
{								\
   for ( ptr = (last); ptr; ptr = ptr->prev )			\
{								\
   if ( ptr->next != pptr )					\
{								\
   bug( "CHECK_LINKS (%s): %p:->next != %p.  Fixing.",	\
   __STRING(first), ptr, pptr );			\
   ptr->next = pptr;					\
}								\
   if ( ptr->next && ptr->next->prev != ptr )		\
{								\
   bug( "CHECK_LINKS(%s): %p:->next->prev != %p.  Fixing.",\
   __STRING(first), ptr, ptr );			\
   ptr->next->prev = ptr;					\
}								\
   pptr = ptr;						\
}								\
}								\
   } while(0)


#define ASSIGN_GSN(gsn, skill)					\
   do								\
{								\
   if ( ((gsn) = skill_lookup((skill))) == -1 )		\
   fprintf( stderr, "ASSIGN_GSN: Skill %s not found.\n",	\
   (skill) );					\
} while(0)

#define CHECK_SUBRESTRICTED(ch)					\
   do								\
{								\
   if ( (ch)->substate == SUB_RESTRICTED )			\
{								\
   send_to_char( "You cannot use this command from within another command.\r\n", ch );	\
   return;							\
}								\
} while(0)


/*
* Character macros.
*/
#define IS_NPC(ch)		(IS_SET((ch)->act, ACT_IS_NPC))
#define IS_IMMORTAL(ch)		(get_trust((ch)) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)		(get_trust((ch)) >= LEVEL_HERO)
#define IS_AFFECTED(ch, sn)	(xIS_SET((ch)->affected_by, (sn)))
#define HAS_BODYPART(ch, part)	((ch)->xflags == 0 || IS_SET((ch)->xflags, (part)))

#define IS_GOOD(ch)		((ch)->alignment >= 350)
#define IS_EVIL(ch)		((ch)->alignment <= -350)
#define IS_NEUTRAL(ch)		(!IS_GOOD(ch) && !IS_EVIL(ch))

#define IS_AWAKE(ch)		((ch)->position > POS_SLEEPING)
#define GET_EVASION(ch)		((ch)->evasion + evasion_from_agi((ch)) )
#define GET_ARMOR(ch)           ((ch)->armor + armor_from_con((ch)) )
#define GET_HITROLL(ch)		((ch)->hitroll + hitroll_from_dex((ch)) )
#define GET_DAMROLL(ch)		((ch)->damroll + damroll_from_str((ch))  )

#define IS_OUTSIDE(ch)		(!IS_SET(				    \
   (ch)->in_room->room_flags,		    \
   ROOM_INDOORS) && !IS_SET(               \
   (ch)->in_room->room_flags,              \
   ROOM_SPACECRAFT) )

#define IS_DRUNK(ch, drunk)     (number_percent() < \
   ( (ch)->pcdata->condition[COND_DRUNK] \
   * 2 / (drunk) ) )

#define IS_CLANNED(ch)		(!IS_NPC((ch))				    \
   && (ch)->pcdata->clan			    )

#define WAIT_STATE(ch, npulse)	((ch)->wait = UMAX((ch)->wait, (npulse)))


#define EXIT(ch, door)		( get_exit( (ch)->in_room, door ) )

#define CAN_GO(ch, door)	(EXIT((ch),(door))			 \
   && (EXIT((ch),(door))->to_room != NULL)  \
   && !IS_SET(EXIT((ch), (door))->exit_info, EX_CLOSED))

#define IS_VALID_SN(sn)		( (sn) >=0 && (sn) < MAX_SKILL		     \
   && skill_table[(sn)]			     \
   && skill_table[(sn)]->name )

#define IS_VALID_HERB(sn)	( (sn) >=0 && (sn) < MAX_HERB		     \
   && herb_table[(sn)]			     \
   && herb_table[(sn)]->name )

#define SPELL_FLAG(skill, flag)	( IS_SET((skill)->flags, (flag)) )
#define SPELL_DAMAGE(skill)	( ((skill)->flags     ) & 7 )
#define SPELL_ACTION(skill)	( ((skill)->flags >> 3) & 7 )
#define SPELL_CLASS(skill)	( ((skill)->flags >> 6) & 7 )
#define SPELL_POWER(skill)	( ((skill)->flags >> 9) & 3 )
#define SET_SDAM(skill, val)	( (skill)->flags =  ((skill)->flags & SDAM_MASK) + ((val) & 7) )
#define SET_SACT(skill, val)	( (skill)->flags =  ((skill)->flags & SACT_MASK) + (((val) & 7) << 3) )
#define SET_SCLA(skill, val)	( (skill)->flags =  ((skill)->flags & SCLA_MASK) + (((val) & 7) << 6) )
#define SET_SPOW(skill, val)	( (skill)->flags =  ((skill)->flags & SPOW_MASK) + (((val) & 3) << 9) )

/* Retired and guest imms. */
#define IS_RETIRED(ch) (ch->pcdata && IS_SET(ch->pcdata->flags,PCFLAG_RETIRED))
#define IS_GUEST(ch) (ch->pcdata && IS_SET(ch->pcdata->flags,PCFLAG_GUEST))

/* RIS by gsn lookups. -- Altrag.
Will need to add some || stuff for spells that need a special GSN. */

#define IS_FIRE(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_FIRE )
#define IS_COLD(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_COLD )
#define IS_ACID(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_ACID )
#define IS_ELECTRICITY(dt)	( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_ELECTRICITY )
#define IS_ENERGY(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_ENERGY )

#define IS_DRAIN(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_DRAIN )

#define IS_POISON(dt)		( IS_VALID_SN(dt) &&			     \
   SPELL_DAMAGE(skill_table[(dt)]) == SD_POISON )


#define NOT_AUTHED(ch)		(!IS_NPC(ch) && ch->pcdata->auth_state <= 3  \
   && IS_SET(ch->pcdata->flags, PCFLAG_UNAUTHED) )

#define IS_WAITING_FOR_AUTH(ch) (!IS_NPC(ch) && ch->desc		     \
   && ch->pcdata->auth_state == 1		     \
   && IS_SET(ch->pcdata->flags, PCFLAG_UNAUTHED) )

/*
* Object macros.
*/
#define CAN_WEAR(obj, part)	(IS_SET((obj)->wear_flags,  (part)))
#define IS_OBJ_STAT(obj, stat)	(IS_SET((obj)->extra_flags, (stat)))

/*
* Description macros.
*/
#define PERS(ch, looker)	( can_see( (looker), (ch) ) ?		\
   ( IS_NPC(ch) ? (ch)->short_descr	\
   : (ch)->name ) : "someone" )

#define log_string( txt )	( log_string_plus( (txt), LOG_NORMAL, LEVEL_LOG ) )

/*
* Structure for a command in the command lookup table.
*/
struct cmd_type
{
   CMDTYPE *next;
   const char *name;
   DO_FUN *do_fun;
   const char *fun_name;
   short position;
   short level;
   short log;
   struct timerset userec;
};

/*
* Structure for a social in the socials table.
*/
struct social_type
{
   SOCIALTYPE *next;
   const char *name;
   const char *char_no_arg;
   const char *others_no_arg;
   const char *char_found;
   const char *others_found;
   const char *vict_found;
   const char *char_auto;
   const char *others_auto;
};

struct specfun_list
{
   SPEC_LIST *next;
   SPEC_LIST *prev;
   const char *name;
};

/*
* Global constants.
*/
extern time_t last_restore_all_time;
extern time_t boot_time;   /* this should be moved down */
extern HOUR_MIN_SEC *set_boot_time;
extern struct tm *new_boot_time;
extern time_t new_boot_time_t;
extern bool mud_down;
extern bool DONT_UPPER;
extern FILE *fpArea;
extern char strArea[MAX_INPUT_LENGTH];

extern const struct str_app_type str_app[26];
extern const struct int_app_type int_app[26];
extern const struct wis_app_type wis_app[26];
extern const struct dex_app_type dex_app[26];
extern const struct con_app_type con_app[26];
extern const struct cha_app_type cha_app[26];
extern const struct lck_app_type lck_app[26];
extern const struct frc_app_type frc_app[26];

extern const struct race_type race_table[MAX_RACE];
extern const struct stat_build stat_table[MAX_STATBUILD];
extern const struct liq_type liq_table[LIQ_MAX];
extern const char *const attack_table[13];
extern const char *const ability_name[MAX_ABILITY];

extern const char *const factor_names[MAX_FACTOR];
extern const char *const skilltype_names[MAX_TYPE];
extern const char *const cost_type[MAX_COST];
extern const char *const applytypes_type[MAX_APPLYTYPE];

extern const char *const target_type[TAR_CHAR_MAX];
extern const char *const style_type[STYLE_MAX];
extern const char *const skill_tname[MAX_SKILLTYPE];
extern short const movement_loss[SECT_MAX];
extern const char *const dir_name[];
extern const char *const where_name[];
extern const short rev_dir[];
extern const int trap_door[];
extern const char *const r_flags[];
extern const char *const w_flags[];
extern const char *const o_flags[];
extern const char *const a_flags[MAX_AFF];
extern const char *const o_types[];
extern const char *const a_types[MAX_APPLY_TYPE];
extern const char *const act_flags[];
extern const char *const planet_flags[];
extern const char *const weapon_table[13];
extern const char *const spice_table[];
extern const char *const plr_flags[];
extern const char *const pc_flags[];
extern const char *const trap_flags[];
extern const char *const ris_flags[];
extern const char *const trig_flags[];
extern const char *const part_flags[];
extern const char *const npc_race[];
extern const char *const defense_flags[];
extern const char *const attack_flags[];
extern const char *const area_flags[];
extern const char *const wear_locs[];
extern int const lang_array[];
extern const char *const lang_names[];
extern const char *const lang_names_save[];
extern const char *sector_name[SECT_MAX];
extern const char *const d_type[MAX_DAMTYPE];
extern const char *const q_type[MAX_QUALITYTYPE];
extern const char *const l_type[MAX_LOOTTYPE];
extern const char *const d_type_score[MAX_DAMTYPE];
extern const char *const frames_of_mind[MAX_FOM];
extern const char *const quest_types[MAX_QUESTTYPE];
/*
* Global variables.
*/
extern int numobjsloaded;
extern int nummobsloaded;
extern int physicalobjects;
extern int num_descriptors;
extern struct system_data sysdata;
extern int top_sn;
extern int top_vroom;
extern int top_herb;

extern CMDTYPE *command_hash[126];

extern SKILLTYPE *skill_table[MAX_SKILL];
extern SOCIALTYPE *social_index[27];
extern CHAR_DATA *cur_char;
extern ROOM_INDEX_DATA *cur_room;
extern bool cur_char_died;
extern ch_ret global_retcode;
extern SKILLTYPE *herb_table[MAX_HERB];

extern int cur_obj;
extern int cur_obj_serial;
extern bool cur_obj_extracted;
extern obj_ret global_objcode;

extern HELP_DATA *first_help;
extern HELP_DATA *last_help;
extern SHOP_DATA *first_shop;
extern SHOP_DATA *last_shop;
extern REPAIR_DATA *first_repair;
extern REPAIR_DATA *last_repair;
extern SPEC_LIST *first_specfun;
extern SPEC_LIST *last_specfun;
extern BAN_DATA *first_ban;
extern BAN_DATA *last_ban;
extern CHAR_DATA *first_char;
extern CHAR_DATA *last_char;
extern DESCRIPTOR_DATA *first_descriptor;
extern DESCRIPTOR_DATA *last_descriptor;
extern BOARD_DATA *first_board;
extern BOARD_DATA *last_board;
extern OBJ_DATA *first_object;
extern OBJ_DATA *last_object;
extern CLAN_DATA *first_clan;
extern CLAN_DATA *last_clan;
extern GUARD_DATA *first_guard;
extern GUARD_DATA *last_guard;
extern SHIP_DATA *first_ship;
extern SHIP_DATA *last_ship;
extern SPACE_DATA *first_starsystem;
extern SPACE_DATA *last_starsystem;
extern PLANET_DATA *first_planet;
extern PLANET_DATA *last_planet;
extern SENATE_DATA *first_senator;
extern SENATE_DATA *last_senator;
extern BOUNTY_DATA *first_bounty;
extern BOUNTY_DATA *last_bounty;
extern BOUNTY_DATA *first_disintigration;
extern BOUNTY_DATA *last_disintigration;
extern AREA_DATA *first_area;
extern AREA_DATA *last_area;
extern AREA_DATA *first_build;
extern AREA_DATA *last_build;
extern AREA_DATA *first_asort;
extern AREA_DATA *last_asort;
extern AREA_DATA *first_bsort;
extern AREA_DATA *last_bsort;
extern AREA_DATA *first_area_name;  /*alphanum. sort */
extern AREA_DATA *last_area_name;   /* Fireblade */
extern TELEPORT_DATA *first_teleport;
extern TELEPORT_DATA *last_teleport;
extern OBJ_DATA *extracted_obj_queue;
extern EXTRACT_CHAR_DATA *extracted_char_queue;
extern OBJ_DATA *save_equipment[MAX_WEAR][MAX_LAYERS];
extern CHAR_DATA *quitting_char;
extern CHAR_DATA *loading_char;
extern CHAR_DATA *saving_char;
extern OBJ_DATA *all_obj;
extern THREAT_DATA *first_threat;
extern THREAT_DATA *last_threat;
extern QUEST_DATA *first_quest;
extern QUEST_DATA *last_quest;
extern POOL_DATA *first_pool;
extern POOL_DATA *last_pool;
extern QTIMER *first_qtimer;
extern QTIMER *last_qtimer;
extern DISC_DATA *first_discipline;
extern DISC_DATA *last_discipline;

extern time_t current_time;
extern bool fLogAll;
extern char log_buf[];
extern TIME_INFO_DATA time_info;
extern WEATHER_DATA weather_info;

extern AUCTION_DATA *auction;
extern struct act_prog_data *mob_act_list;

/*
* Command functions.
* Defined in act_*.c (mostly).
*/
DECLARE_DO_FUN( do_remloot );
DECLARE_DO_FUN( do_addloot );
DECLARE_DO_FUN( do_learn );
DECLARE_DO_FUN( do_discipline );
DECLARE_DO_FUN( do_dset );
DECLARE_DO_FUN( do_skills );
DECLARE_DO_FUN( do_skillcraft );
DECLARE_DO_FUN( do_skill );
DECLARE_DO_FUN( do_showthreat );
DECLARE_DO_FUN( do_setmssp );
DECLARE_DO_FUN( do_setplanet );
DECLARE_DO_FUN( do_makeplanet );
DECLARE_DO_FUN( do_planets );
DECLARE_DO_FUN( do_teach );
DECLARE_DO_FUN( do_gather_intelligence );
DECLARE_DO_FUN( do_add_patrol );
DECLARE_DO_FUN( do_special_forces );
DECLARE_DO_FUN( do_jail );
DECLARE_DO_FUN( do_elite_guard );
DECLARE_DO_FUN( do_smalltalk );
DECLARE_DO_FUN( do_propeganda );
DECLARE_DO_FUN( do_bribe );
DECLARE_DO_FUN( do_seduce );
DECLARE_DO_FUN( do_mass_propeganda );
DECLARE_DO_FUN( do_copyship );
DECLARE_DO_FUN( do_sound );
DECLARE_DO_FUN( do_autopilot );
DECLARE_DO_FUN( do_allspeeders );
DECLARE_DO_FUN( do_speeders );
DECLARE_DO_FUN( do_suicide );
DECLARE_DO_FUN( do_gain );
DECLARE_DO_FUN( do_train );
DECLARE_DO_FUN( do_beg );
DECLARE_DO_FUN( do_bank );
DECLARE_DO_FUN( do_hijack );
DECLARE_DO_FUN( do_pickshiplock );
DECLARE_DO_FUN( do_shiptalk );
DECLARE_DO_FUN( do_clone );
DECLARE_DO_FUN( do_systemtalk );
DECLARE_DO_FUN( do_spacetalk );
DECLARE_DO_FUN( do_hail );
DECLARE_DO_FUN( do_allships );
DECLARE_DO_FUN( do_newclan );
DECLARE_DO_FUN( do_appoint );
DECLARE_DO_FUN( do_demote );
DECLARE_DO_FUN( do_empower );
DECLARE_DO_FUN( do_capture );
DECLARE_DO_FUN( do_arm );
DECLARE_DO_FUN( do_chaff );
DECLARE_DO_FUN( do_clan_donate );
DECLARE_DO_FUN( do_clan_withdraw );
DECLARE_DO_FUN( do_fly );
DECLARE_DO_FUN( do_drive );
DECLARE_DO_FUN( do_bomb );
DECLARE_DO_FUN( do_setblaster );
DECLARE_DO_FUN( do_ammo );
DECLARE_DO_FUN( do_takedrug );
DECLARE_DO_FUN( do_use );
DECLARE_DO_FUN( do_enlist );
DECLARE_DO_FUN( do_resign );
DECLARE_DO_FUN( do_pluogus );
DECLARE_DO_FUN( do_tractorbeam );
DECLARE_DO_FUN( do_makearmor );
DECLARE_DO_FUN( do_makejewelry );
DECLARE_DO_FUN( do_makegrenade );
DECLARE_DO_FUN( do_makelandmine );
DECLARE_DO_FUN( do_makelight );
DECLARE_DO_FUN( do_makecomlink );
DECLARE_DO_FUN( do_makeshield );
DECLARE_DO_FUN( do_makecontainer );
DECLARE_DO_FUN( do_gemcutting );
DECLARE_DO_FUN( do_reinforcements );
DECLARE_DO_FUN( do_postguard );
DECLARE_DO_FUN( do_torture );
DECLARE_DO_FUN( do_snipe );
DECLARE_DO_FUN( do_throw );
DECLARE_DO_FUN( do_disguise );
DECLARE_DO_FUN( do_mine );
DECLARE_DO_FUN( do_first_aid );
DECLARE_DO_FUN( do_makeblade );
DECLARE_DO_FUN( do_makeblaster );
DECLARE_DO_FUN( do_makelightsaber );
DECLARE_DO_FUN( do_makespice );
DECLARE_DO_FUN( do_closebay );
DECLARE_DO_FUN( do_openbay );
DECLARE_DO_FUN( do_autotrack );
DECLARE_DO_FUN( do_jumpvector );
DECLARE_DO_FUN( do_reload );
DECLARE_DO_FUN( do_radar );
DECLARE_DO_FUN( do_buyship );
DECLARE_DO_FUN( do_buyhome );
DECLARE_DO_FUN( do_clanbuyship );
DECLARE_DO_FUN( do_sellship );
DECLARE_DO_FUN( do_autorecharge );
DECLARE_DO_FUN( do_openhatch );
DECLARE_DO_FUN( do_closehatch );
DECLARE_DO_FUN( do_status );
DECLARE_DO_FUN( do_info );
DECLARE_DO_FUN( do_hyperspace );
DECLARE_DO_FUN( do_target );
DECLARE_DO_FUN( do_fire );
DECLARE_DO_FUN( do_calculate );
DECLARE_DO_FUN( do_recharge );
DECLARE_DO_FUN( do_repairship );
DECLARE_DO_FUN( do_refuel );
DECLARE_DO_FUN( do_addpilot );
DECLARE_DO_FUN( do_rempilot );
DECLARE_DO_FUN( do_trajectory );
DECLARE_DO_FUN( do_accelerate );
DECLARE_DO_FUN( do_launch );
DECLARE_DO_FUN( do_land );
DECLARE_DO_FUN( do_leaveship );
DECLARE_DO_FUN( do_setstarsystem );
DECLARE_DO_FUN( do_makestarsystem );
DECLARE_DO_FUN( do_starsystems );
DECLARE_DO_FUN( do_showstarsystem );
DECLARE_DO_FUN( skill_notfound );
DECLARE_DO_FUN( do_aassign );
DECLARE_DO_FUN( do_addbounty );
DECLARE_DO_FUN( do_vassign );
DECLARE_DO_FUN( do_advance );
DECLARE_DO_FUN( do_affected );
DECLARE_DO_FUN( do_afk );
DECLARE_DO_FUN( do_aid );
DECLARE_DO_FUN( do_allow );
DECLARE_DO_FUN( do_ansi );
DECLARE_DO_FUN( do_answer );
DECLARE_DO_FUN( do_apply );
DECLARE_DO_FUN( do_appraise );
DECLARE_DO_FUN( do_areas );
DECLARE_DO_FUN( do_aset );
DECLARE_DO_FUN( do_ask );
DECLARE_DO_FUN( do_astat );
DECLARE_DO_FUN( do_at );
DECLARE_DO_FUN( do_auction );
DECLARE_DO_FUN( do_authorize );
DECLARE_DO_FUN( do_avtalk );
DECLARE_DO_FUN( do_backstab );
DECLARE_DO_FUN( do_balzhur );
DECLARE_DO_FUN( do_bamfin );
DECLARE_DO_FUN( do_bamfout );
DECLARE_DO_FUN( do_ban );
DECLARE_DO_FUN( do_bash );
DECLARE_DO_FUN( do_bashdoor );
DECLARE_DO_FUN( do_beep );
DECLARE_DO_FUN( do_berserk );
DECLARE_DO_FUN( do_bestow );
DECLARE_DO_FUN( do_bestowarea );
DECLARE_DO_FUN( do_bio );
DECLARE_DO_FUN( do_bite );
DECLARE_DO_FUN( do_board );
DECLARE_DO_FUN( do_boards );
DECLARE_DO_FUN( do_bodybag );
DECLARE_DO_FUN( do_bounties );
DECLARE_DO_FUN( do_brandish );
DECLARE_DO_FUN( do_brew );
DECLARE_DO_FUN( do_bset );
DECLARE_DO_FUN( do_bstat );
DECLARE_DO_FUN( do_bug );
DECLARE_DO_FUN( do_bury );
DECLARE_DO_FUN( do_buy );
DECLARE_DO_FUN( do_cast );
DECLARE_DO_FUN( do_cedit );
DECLARE_DO_FUN( do_channels );
DECLARE_DO_FUN( do_chat );
DECLARE_DO_FUN( do_ooc );
DECLARE_DO_FUN( do_check_vnums );
DECLARE_DO_FUN( do_circle );
DECLARE_DO_FUN( do_clans );
DECLARE_DO_FUN( do_ships );
DECLARE_DO_FUN( do_clantalk );
DECLARE_DO_FUN( do_claw );
DECLARE_DO_FUN( do_climb );
DECLARE_DO_FUN( do_close );
DECLARE_DO_FUN( do_cmdtable );
DECLARE_DO_FUN( do_cmenu );
DECLARE_DO_FUN( do_commands );
DECLARE_DO_FUN( do_comment );
DECLARE_DO_FUN( do_compare );
DECLARE_DO_FUN( do_compress );
DECLARE_DO_FUN( do_config );
DECLARE_DO_FUN( do_consider );
DECLARE_DO_FUN( do_senate );
DECLARE_DO_FUN( do_addsenator );
DECLARE_DO_FUN( do_remsenator );
DECLARE_DO_FUN( do_credits );
DECLARE_DO_FUN( do_cset );
DECLARE_DO_FUN( do_deny );
DECLARE_DO_FUN( do_description );
DECLARE_DO_FUN( do_destro );
DECLARE_DO_FUN( do_destroy );
DECLARE_DO_FUN( do_detrap );
DECLARE_DO_FUN( do_devote );
DECLARE_DO_FUN( do_dig );
DECLARE_DO_FUN( do_disarm );
DECLARE_DO_FUN( do_disconnect );
DECLARE_DO_FUN( do_dismount );
DECLARE_DO_FUN( do_dmesg );
DECLARE_DO_FUN( do_down );
DECLARE_DO_FUN( do_drag );
DECLARE_DO_FUN( do_drink );
DECLARE_DO_FUN( do_drop );
DECLARE_DO_FUN( do_diagnose );
DECLARE_DO_FUN( do_east );
DECLARE_DO_FUN( do_eat );
DECLARE_DO_FUN( do_echo );
DECLARE_DO_FUN( do_emote );
DECLARE_DO_FUN( do_empty );
DECLARE_DO_FUN( do_enter );
DECLARE_DO_FUN( do_equipment );
DECLARE_DO_FUN( do_examine );
DECLARE_DO_FUN( do_exits );
DECLARE_DO_FUN( do_feed );
DECLARE_DO_FUN( do_fill );
DECLARE_DO_FUN( do_fixchar );
DECLARE_DO_FUN( do_flee );
DECLARE_DO_FUN( do_foldarea );
DECLARE_DO_FUN( do_follow );
DECLARE_DO_FUN( do_for );
DECLARE_DO_FUN( do_force );
DECLARE_DO_FUN( do_forceclose );
DECLARE_DO_FUN( do_fquit );   /* Gorog */
DECLARE_DO_FUN( do_form_password );
DECLARE_DO_FUN( do_freeze );
DECLARE_DO_FUN( do_get );
DECLARE_DO_FUN( do_give );
DECLARE_DO_FUN( do_glance );
DECLARE_DO_FUN( do_gold );
DECLARE_DO_FUN( do_goto );
DECLARE_DO_FUN( do_gouge );
DECLARE_DO_FUN( do_group );
DECLARE_DO_FUN( do_grub );
DECLARE_DO_FUN( do_gtell );
DECLARE_DO_FUN( do_guilds );
DECLARE_DO_FUN( do_guildtalk );
DECLARE_DO_FUN( do_hedit );
DECLARE_DO_FUN( do_hell );
DECLARE_DO_FUN( do_help );
DECLARE_DO_FUN( do_hide );
DECLARE_DO_FUN( do_hitall );
DECLARE_DO_FUN( do_hlist );
DECLARE_DO_FUN( do_holylight );
DECLARE_DO_FUN( do_homepage );
DECLARE_DO_FUN( do_hset );
DECLARE_DO_FUN( do_i103 );
DECLARE_DO_FUN( do_i104 );
DECLARE_DO_FUN( do_i105 );
DECLARE_DO_FUN( do_ide );
DECLARE_DO_FUN( do_idea );
DECLARE_DO_FUN( do_immortalize );
DECLARE_DO_FUN( do_immtalk );
DECLARE_DO_FUN( do_induct );
DECLARE_DO_FUN( do_installarea );
DECLARE_DO_FUN( do_instaroom );
DECLARE_DO_FUN( do_instazone );
DECLARE_DO_FUN( do_inventory );
DECLARE_DO_FUN( do_invis );
DECLARE_DO_FUN( do_kick );
DECLARE_DO_FUN( do_kill );
DECLARE_DO_FUN( do_languages );
DECLARE_DO_FUN( do_last );
DECLARE_DO_FUN( do_leave );
DECLARE_DO_FUN( do_level );
DECLARE_DO_FUN( do_light );
DECLARE_DO_FUN( do_list );
DECLARE_DO_FUN( do_litterbug );
DECLARE_DO_FUN( do_loadarea );
DECLARE_DO_FUN( do_loadup );
DECLARE_DO_FUN( do_lock );
DECLARE_DO_FUN( do_log );
DECLARE_DO_FUN( do_look );
DECLARE_DO_FUN( do_low_purge );
DECLARE_DO_FUN( do_mailroom );
DECLARE_DO_FUN( do_make );
DECLARE_DO_FUN( do_makeboard );
DECLARE_DO_FUN( do_makeclan );
DECLARE_DO_FUN( do_makeship );
DECLARE_DO_FUN( do_makeguild );
DECLARE_DO_FUN( do_makerepair );
DECLARE_DO_FUN( do_makeshop );
DECLARE_DO_FUN( do_makewizlist );
DECLARE_DO_FUN( do_memory );
DECLARE_DO_FUN( do_mcreate );
DECLARE_DO_FUN( do_mdelete );
DECLARE_DO_FUN( do_mfind );
DECLARE_DO_FUN( do_minvoke );
DECLARE_DO_FUN( do_mlist );
DECLARE_DO_FUN( do_mount );
DECLARE_DO_FUN( do_mset );
DECLARE_DO_FUN( do_mstat );
DECLARE_DO_FUN( do_murde );
DECLARE_DO_FUN( do_murder );
DECLARE_DO_FUN( do_music );
DECLARE_DO_FUN( do_mwhere );
DECLARE_DO_FUN( do_name );
DECLARE_DO_FUN( do_newbiechat );
DECLARE_DO_FUN( do_newbieset );
DECLARE_DO_FUN( do_newzones );
DECLARE_DO_FUN( do_noemote );
DECLARE_DO_FUN( do_noresolve );
DECLARE_DO_FUN( do_north );
DECLARE_DO_FUN( do_northeast );
DECLARE_DO_FUN( do_northwest );
DECLARE_DO_FUN( do_notell );
DECLARE_DO_FUN( do_notitle );
DECLARE_DO_FUN( do_noteroom );
DECLARE_DO_FUN( do_ocreate );
DECLARE_DO_FUN( do_odelete );
DECLARE_DO_FUN( do_ofind );
DECLARE_DO_FUN( do_ogrub );
DECLARE_DO_FUN( do_oinvoke );
DECLARE_DO_FUN( do_oldscore );
DECLARE_DO_FUN( do_olist );
DECLARE_DO_FUN( do_open );
DECLARE_DO_FUN( do_opentourney );
DECLARE_DO_FUN( do_order );
DECLARE_DO_FUN( do_orders );
DECLARE_DO_FUN( do_ordertalk );
DECLARE_DO_FUN( do_oset );
DECLARE_DO_FUN( do_ostat );
DECLARE_DO_FUN( do_ot );
DECLARE_DO_FUN( do_outcast );
DECLARE_DO_FUN( do_owhere );
DECLARE_DO_FUN( do_pager );
DECLARE_DO_FUN( do_pardon );
DECLARE_DO_FUN( do_password );
DECLARE_DO_FUN( do_peace );
DECLARE_DO_FUN( do_pick );
DECLARE_DO_FUN( do_poison_weapon );
DECLARE_DO_FUN( do_pose );
DECLARE_DO_FUN( do_practice );
DECLARE_DO_FUN( do_prompt );
DECLARE_DO_FUN( do_pull );
DECLARE_DO_FUN( do_punch );
DECLARE_DO_FUN( do_purge );
DECLARE_DO_FUN( do_push );
DECLARE_DO_FUN( do_put );
DECLARE_DO_FUN( do_qpset );
DECLARE_DO_FUN( do_quaff );
DECLARE_DO_FUN( do_quest );
DECLARE_DO_FUN( do_qui );
DECLARE_DO_FUN( do_quit );
DECLARE_DO_FUN( do_rank );
DECLARE_DO_FUN( do_rat );
DECLARE_DO_FUN( do_rdelete );
DECLARE_DO_FUN( do_reboo );
DECLARE_DO_FUN( do_reboot );
DECLARE_DO_FUN( do_recall );
DECLARE_DO_FUN( do_recho );
DECLARE_DO_FUN( do_recite );
DECLARE_DO_FUN( do_redit );
DECLARE_DO_FUN( do_regoto );
DECLARE_DO_FUN( do_remove );
DECLARE_DO_FUN( do_rent );
DECLARE_DO_FUN( do_repair );
DECLARE_DO_FUN( do_repairset );
DECLARE_DO_FUN( do_repairshops );
DECLARE_DO_FUN( do_repairstat );
DECLARE_DO_FUN( do_reply );
DECLARE_DO_FUN( do_report );
DECLARE_DO_FUN( do_rescue );
DECLARE_DO_FUN( do_rest );
DECLARE_DO_FUN( do_reset );
DECLARE_DO_FUN( do_resetship );
DECLARE_DO_FUN( do_restore );
DECLARE_DO_FUN( do_restoretime );
DECLARE_DO_FUN( do_restrict );
DECLARE_DO_FUN( do_retire );
DECLARE_DO_FUN( do_retran );
DECLARE_DO_FUN( do_return );
DECLARE_DO_FUN( do_revert );
DECLARE_DO_FUN( do_rip );
DECLARE_DO_FUN( do_rlist );
DECLARE_DO_FUN( do_rset );
DECLARE_DO_FUN( do_rstat );
DECLARE_DO_FUN( do_sacrifice );
DECLARE_DO_FUN( do_save );
DECLARE_DO_FUN( do_savearea );
DECLARE_DO_FUN( do_say );
DECLARE_DO_FUN( do_scan );
DECLARE_DO_FUN( do_score );
DECLARE_DO_FUN( do_scribe );
DECLARE_DO_FUN( do_search );
DECLARE_DO_FUN( do_sedit );
DECLARE_DO_FUN( do_sell );
DECLARE_DO_FUN( do_set_boot_time );
DECLARE_DO_FUN( do_setclan );
DECLARE_DO_FUN( do_setship );
DECLARE_DO_FUN( do_shops );
DECLARE_DO_FUN( do_shopset );
DECLARE_DO_FUN( do_shopstat );
DECLARE_DO_FUN( do_shout );
DECLARE_DO_FUN( do_shove );
DECLARE_DO_FUN( do_showclan );
DECLARE_DO_FUN( do_showship );
DECLARE_DO_FUN( do_shutdow );
DECLARE_DO_FUN( do_shutdown );
DECLARE_DO_FUN( do_silence );
DECLARE_DO_FUN( do_sit );
DECLARE_DO_FUN( do_sla );
DECLARE_DO_FUN( do_slay );
DECLARE_DO_FUN( do_sleep );
DECLARE_DO_FUN( do_slice );
DECLARE_DO_FUN( do_slist );
DECLARE_DO_FUN( do_slookup );
DECLARE_DO_FUN( do_smoke );
DECLARE_DO_FUN( do_sneak );
DECLARE_DO_FUN( do_snoop );
DECLARE_DO_FUN( do_sober );
DECLARE_DO_FUN( do_socials );
DECLARE_DO_FUN( do_south );
DECLARE_DO_FUN( do_southeast );
DECLARE_DO_FUN( do_southwest );
DECLARE_DO_FUN( do_speak );
DECLARE_DO_FUN( do_split );
DECLARE_DO_FUN( do_sset );
DECLARE_DO_FUN( do_stand );
DECLARE_DO_FUN( do_starttourney );
DECLARE_DO_FUN( do_steal );
DECLARE_DO_FUN( do_sting );
DECLARE_DO_FUN( do_stun );
DECLARE_DO_FUN( do_switch );
DECLARE_DO_FUN( do_tail );
DECLARE_DO_FUN( do_tamp );
DECLARE_DO_FUN( do_tell );
DECLARE_DO_FUN( do_time );
DECLARE_DO_FUN( do_timecmd );
DECLARE_DO_FUN( do_title );
DECLARE_DO_FUN( do_track );
DECLARE_DO_FUN( do_transfer );
DECLARE_DO_FUN( do_trust );
DECLARE_DO_FUN( do_typo );
DECLARE_DO_FUN( do_unfoldarea );
DECLARE_DO_FUN( do_unhell );
DECLARE_DO_FUN( do_unlock );
DECLARE_DO_FUN( do_unsilence );
DECLARE_DO_FUN( do_up );
DECLARE_DO_FUN( do_users );
DECLARE_DO_FUN( do_value );
DECLARE_DO_FUN( do_visible );
DECLARE_DO_FUN( do_vnums );
DECLARE_DO_FUN( do_vsearch );
DECLARE_DO_FUN( do_wake );
DECLARE_DO_FUN( do_wartalk );
DECLARE_DO_FUN( do_wear );
DECLARE_DO_FUN( do_weather );
DECLARE_DO_FUN( do_west );
DECLARE_DO_FUN( do_where );
DECLARE_DO_FUN( do_who );
DECLARE_DO_FUN( do_whois );
DECLARE_DO_FUN( do_wimpy );
DECLARE_DO_FUN( do_wizhelp );
DECLARE_DO_FUN( do_wizlist );
DECLARE_DO_FUN( do_wizlock );
DECLARE_DO_FUN( do_yell );
DECLARE_DO_FUN( do_zap );
DECLARE_DO_FUN( do_zones );

/* mob prog stuff */
DECLARE_DO_FUN( do_mpauth );
DECLARE_DO_FUN( do_mp_progress );
DECLARE_DO_FUN( do_mp_advancequest );
DECLARE_DO_FUN( do_mp_completequest );
DECLARE_DO_FUN( do_mp_close_passage );
DECLARE_DO_FUN( do_mp_damage );
DECLARE_DO_FUN( do_mp_restore );
DECLARE_DO_FUN( do_mp_open_passage );
DECLARE_DO_FUN( do_mp_practice );
DECLARE_DO_FUN( do_mp_slay );
DECLARE_DO_FUN( do_mpadvance );
DECLARE_DO_FUN( do_mpasound );
DECLARE_DO_FUN( do_mpat );
DECLARE_DO_FUN( do_mpdream );
DECLARE_DO_FUN( do_mp_deposit );
DECLARE_DO_FUN( do_mp_withdraw );
DECLARE_DO_FUN( do_mpecho );
DECLARE_DO_FUN( do_mpechoaround );
DECLARE_DO_FUN( do_mpechoat );
DECLARE_DO_FUN( do_mpedit );
DECLARE_DO_FUN( do_mrange );
DECLARE_DO_FUN( do_opedit );
DECLARE_DO_FUN( do_orange );
DECLARE_DO_FUN( do_rpedit );
DECLARE_DO_FUN( do_mpforce );
DECLARE_DO_FUN( do_mpinvis );
DECLARE_DO_FUN( do_mpgoto );
DECLARE_DO_FUN( do_mpjunk );
DECLARE_DO_FUN( do_mpkill );
DECLARE_DO_FUN( do_mpmload );
DECLARE_DO_FUN( do_mpnothing );
DECLARE_DO_FUN( do_mpoload );
DECLARE_DO_FUN( do_mppurge );
DECLARE_DO_FUN( do_mpstat );
DECLARE_DO_FUN( do_opstat );
DECLARE_DO_FUN( do_rpstat );
DECLARE_DO_FUN( do_mptransfer );
DECLARE_DO_FUN( do_mpapply );
DECLARE_DO_FUN( do_mpapplyb );
DECLARE_DO_FUN( do_mppkset );
DECLARE_DO_FUN( do_mpgain );

/*
* Spell functions.
* Defined in magic.c.
*/
DECLARE_SPELL_FUN( spell_null );
DECLARE_SPELL_FUN( spell_notfound );
DECLARE_SPELL_FUN( spell_acid_blast );
DECLARE_SPELL_FUN( spell_animate_dead );
DECLARE_SPELL_FUN( spell_astral_walk );
DECLARE_SPELL_FUN( spell_blindness );
DECLARE_SPELL_FUN( spell_burning_hands );
DECLARE_SPELL_FUN( spell_call_lightning );
DECLARE_SPELL_FUN( spell_cause_critical );
DECLARE_SPELL_FUN( spell_cause_light );
DECLARE_SPELL_FUN( spell_cause_serious );
DECLARE_SPELL_FUN( spell_change_sex );
DECLARE_SPELL_FUN( spell_charm_person );
DECLARE_SPELL_FUN( spell_chill_touch );
DECLARE_SPELL_FUN( spell_colour_spray );
DECLARE_SPELL_FUN( spell_control_weather );
DECLARE_SPELL_FUN( spell_create_food );
DECLARE_SPELL_FUN( spell_create_water );
DECLARE_SPELL_FUN( spell_cure_blindness );
DECLARE_SPELL_FUN( spell_cure_poison );
DECLARE_SPELL_FUN( spell_curse );
DECLARE_SPELL_FUN( spell_detect_poison );
DECLARE_SPELL_FUN( spell_dispel_evil );
DECLARE_SPELL_FUN( spell_dispel_magic );
DECLARE_SPELL_FUN( spell_dream );
DECLARE_SPELL_FUN( spell_earthquake );
DECLARE_SPELL_FUN( spell_enchant_weapon );
DECLARE_SPELL_FUN( spell_energy_drain );
DECLARE_SPELL_FUN( spell_faerie_fire );
DECLARE_SPELL_FUN( spell_faerie_fog );
DECLARE_SPELL_FUN( spell_farsight );
DECLARE_SPELL_FUN( spell_fireball );
DECLARE_SPELL_FUN( spell_flamestrike );
DECLARE_SPELL_FUN( spell_gate );
DECLARE_SPELL_FUN( spell_knock );
DECLARE_SPELL_FUN( spell_harm );
DECLARE_SPELL_FUN( spell_identify );
DECLARE_SPELL_FUN( spell_invis );
DECLARE_SPELL_FUN( spell_know_alignment );
DECLARE_SPELL_FUN( spell_lightning_bolt );
DECLARE_SPELL_FUN( spell_locate_object );
DECLARE_SPELL_FUN( spell_magic_missile );
DECLARE_SPELL_FUN( spell_mist_walk );
DECLARE_SPELL_FUN( spell_pass_door );
DECLARE_SPELL_FUN( spell_plant_pass );
DECLARE_SPELL_FUN( spell_poison );
DECLARE_SPELL_FUN( spell_polymorph );
DECLARE_SPELL_FUN( spell_possess );
DECLARE_SPELL_FUN( spell_recharge );
DECLARE_SPELL_FUN( spell_remove_curse );
DECLARE_SPELL_FUN( spell_remove_invis );
DECLARE_SPELL_FUN( spell_remove_trap );
DECLARE_SPELL_FUN( spell_shocking_grasp );
DECLARE_SPELL_FUN( spell_sleep );
DECLARE_SPELL_FUN( spell_smaug );
DECLARE_SPELL_FUN( spell_solar_flight );
DECLARE_SPELL_FUN( spell_summon );
DECLARE_SPELL_FUN( spell_teleport );
DECLARE_SPELL_FUN( spell_ventriloquate );
DECLARE_SPELL_FUN( spell_weaken );
DECLARE_SPELL_FUN( spell_word_of_recall );
DECLARE_SPELL_FUN( spell_acid_breath );
DECLARE_SPELL_FUN( spell_fire_breath );
DECLARE_SPELL_FUN( spell_frost_breath );
DECLARE_SPELL_FUN( spell_gas_breath );
DECLARE_SPELL_FUN( spell_lightning_breath );
DECLARE_SPELL_FUN( spell_spiral_blast );
DECLARE_SPELL_FUN( spell_scorching_surge );
DECLARE_SPELL_FUN( spell_helical_flow );
DECLARE_SPELL_FUN( spell_transport );
DECLARE_SPELL_FUN( spell_portal );

DECLARE_SPELL_FUN( spell_ethereal_fist );
DECLARE_SPELL_FUN( spell_spectral_furor );
DECLARE_SPELL_FUN( spell_hand_of_chaos );
DECLARE_SPELL_FUN( spell_disruption );
DECLARE_SPELL_FUN( spell_sonic_resonance );
DECLARE_SPELL_FUN( spell_mind_wrack );
DECLARE_SPELL_FUN( spell_mind_wrench );
DECLARE_SPELL_FUN( spell_revive );
DECLARE_SPELL_FUN( spell_sulfurous_spray );
DECLARE_SPELL_FUN( spell_caustic_fount );
DECLARE_SPELL_FUN( spell_acetum_primus );
DECLARE_SPELL_FUN( spell_galvanic_whip );
DECLARE_SPELL_FUN( spell_magnetic_thrust );
DECLARE_SPELL_FUN( spell_quantum_spike );
DECLARE_SPELL_FUN( spell_black_hand );
DECLARE_SPELL_FUN( spell_black_fist );
DECLARE_SPELL_FUN( spell_black_lightning );
DECLARE_SPELL_FUN( spell_midas_touch );

DECLARE_SPELL_FUN( spell_suggest );
DECLARE_SPELL_FUN( spell_cure_addiction );

/*
* Data files used by the server.
*
* AREA_LIST contains a list of areas to boot.
* All files are read in completely at bootup.
* Most output files (bug, idea, typo, shutdown) are append-only.
*
* The NULL_FILE is held open so that we have a stream handle in reserve,
*   so players can go ahead and telnet to all the other descriptors.
* Then we close it whenever we need to open a file (e.g. a save file).
*/
#define PLAYER_DIR	"../player/"   /* Player files         */
#define BACKUP_DIR	"../backup/"   /* Backup Player files    */
#define GOD_DIR		"../gods/"  /* God Info Dir         */
#define BOARD_DIR	"../boards/"   /* Board data dir    */
#define CLAN_DIR	"../clans/" /* Clan data dir     */
#define SHIP_DIR        "../space/"
#define SPACE_DIR       "../space/"
#define PLANET_DIR      "../planets/"
#define GUARD_DIR       "../planets/"
#define GUILD_DIR       "../guilds/"   /* Guild data dir               */
#define BUILD_DIR       "../building/" /* Online building save dir     */
#define SYSTEM_DIR	"../system/"   /* Main system files    */
#define PROG_DIR	"../mudprogs/" /* MUDProg files     */
#define CORPSE_DIR	"../corpses/"  /* Corpses        */
#define AREA_LIST	"area.lst"  /* List of areas     */
#define BAN_LIST        "ban.lst"   /* List of bans                 */
#define CLAN_LIST	"clan.lst"  /* List of clans     */
#define SHIP_LIST       "ship.lst"
#define PLANET_LIST      "planet.lst"
#define SPACE_LIST      "space.lst"
#define BOUNTY_LIST     "bounty.lst"
#define DISINTIGRATION_LIST	"disintigration.lst"
#define SENATE_LIST	"senate.lst"   /* List of senators     */
#define GUILD_LIST      "guild.lst" /* List of guilds               */
#define GUARD_LIST	"guard.lst"
#define BOARD_FILE	"boards.txt"   /* For bulletin boards   */
#define SHUTDOWN_FILE	"shutdown.txt" /* For 'shutdown'  */
#define RIPSCREEN_FILE	SYSTEM_DIR "mudrip.rip"
#define RIPTITLE_FILE	SYSTEM_DIR "mudtitle.rip"
#define ANSITITLE_FILE	SYSTEM_DIR "mudtitle.ans"
#define ASCTITLE_FILE	SYSTEM_DIR "mudtitle.asc"
#define BOOTLOG_FILE	SYSTEM_DIR "boot.txt"   /* Boot up error file  */
#define BUG_FILE		SYSTEM_DIR "pbugs.txt"  /* For player usable 'bug' command */
#define IDEA_FILE	SYSTEM_DIR "ideas.txt"  /* For 'idea'       */
#define TYPO_FILE	SYSTEM_DIR "typos.txt"  /* For 'typo'       */
#define LOG_FILE	SYSTEM_DIR "log.txt" /* For talking in logged rooms */
#define WIZLIST_FILE	SYSTEM_DIR "WIZLIST" /* Wizlist       */
#define WHO_FILE	SYSTEM_DIR "WHO"  /* Who output file  */
#define WEBWHO_FILE	SYSTEM_DIR "WEBWHO"  /* WWW Who output file */
#define SKILL_FILE	SYSTEM_DIR "skills.dat" /* Skill table   */
#define HERB_FILE	SYSTEM_DIR "herbs.dat"  /* Herb table       */
#define SOCIAL_FILE	SYSTEM_DIR "socials.dat"   /* Socials       */
#define COMMAND_FILE	SYSTEM_DIR "commands.dat"  /* Commands      */
#define DISCIPLINE_FILE SYSTEM_DIR "disciplines.dat"
#define QUEST_FILE      SYSTEM_DIR "quest.dat" /* Quests, duh */
#define POOL_FILE       SYSTEM_DIR "pool.dat" /* Pools, duh */
#define USAGE_FILE	SYSTEM_DIR "usage.txt"  /* How many people are on
* every half hour - trying to
* determine best reboot time */

/*
* Our function prototypes.
* One big lump ... this is every function in Merc.
*/
#define CD	CHAR_DATA
#define MID	MOB_INDEX_DATA
#define OD	OBJ_DATA
#define OID	OBJ_INDEX_DATA
#define RID	ROOM_INDEX_DATA
#define SF	SPEC_FUN
#define BD	BOARD_DATA
#define CL	CLAN_DATA
#define EDD	EXTRA_DESCR_DATA
#define RD	RESET_DATA
#define ED	EXIT_DATA
#define	ST	SOCIALTYPE
#define SK	SKILLTYPE
#define SH      SHIP_DATA

/* act_comm.c */
void sound_to_room( ROOM_INDEX_DATA * room, const char *argument );
bool circle_follow args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void add_follower args( ( CHAR_DATA * ch, CHAR_DATA * master ) );
void stop_follower args( ( CHAR_DATA * ch ) );
void die_follower args( ( CHAR_DATA * ch ) );
bool is_same_group args( ( CHAR_DATA * ach, CHAR_DATA * bch ) );
void send_rip_screen args( ( CHAR_DATA * ch ) );
void send_rip_title args( ( CHAR_DATA * ch ) );
void send_ansi_title args( ( CHAR_DATA * ch ) );
void send_ascii_title args( ( CHAR_DATA * ch ) );
void to_channel args( ( const char *argument, int channel, const char *verb, short level ) );
void talk_auction args( ( char *argument ) );
bool knows_language args( ( CHAR_DATA * ch, int language, CHAR_DATA * cch ) );
bool can_learn_lang args( ( CHAR_DATA * ch, int language ) );
int countlangs args( ( int languages ) );
const char *translate args( ( CHAR_DATA * ch, CHAR_DATA * victim, const char *argument ) );
const char *obj_short( OBJ_DATA * obj );

/* act_info.c */
int get_door( const char *arg );
char *format_obj_to_char args( ( OBJ_DATA * obj, CHAR_DATA * ch, bool fShort ) );
void show_list_to_char args( ( OBJ_DATA * list, CHAR_DATA * ch, bool fShort, bool fShowNothing ) );
void spit_dash( CHAR_DATA *ch, int num_dash, short color );

/* act_move.c */
ROOM_INDEX_DATA *generate_exit( ROOM_INDEX_DATA * in_room, EXIT_DATA ** pexit );
void clear_vrooms( void );
ED *find_door( CHAR_DATA * ch, const char *arg, bool quiet );
ED *get_exit args( ( ROOM_INDEX_DATA * room, short dir ) );
ED *get_exit_to args( ( ROOM_INDEX_DATA * room, short dir, int vnum ) );
ED *get_exit_num args( ( ROOM_INDEX_DATA * room, short count ) );
ch_ret move_char args( ( CHAR_DATA * ch, EXIT_DATA * pexit, int fall ) );
void teleport( CHAR_DATA * ch, int room, int flags );
short encumbrance args( ( CHAR_DATA * ch, short move ) );
bool will_fall args( ( CHAR_DATA * ch, int fall ) );
int wherehome args( ( CHAR_DATA * ch ) );

/* act_obj.c */

obj_ret damage_obj args( ( OBJ_DATA * obj ) );
short get_obj_resistance args( ( OBJ_DATA * obj ) );
void save_clan_storeroom args( ( CHAR_DATA * ch, CLAN_DATA * clan ) );
void obj_fall args( ( OBJ_DATA * obj, bool through ) );

/* act_wiz.c */
void close_area args( ( AREA_DATA * pArea ) );
RID *find_location( CHAR_DATA * ch, const char *arg );
void echo_to_room( short AT_COLOR, ROOM_INDEX_DATA * room, const char *argument );
void echo_to_all( short AT_COLOR, const char *argument, short tar );
void get_reboot_string args( ( void ) );
struct tm *update_time args( ( struct tm * old_time ) );
void free_social args( ( SOCIALTYPE * social ) );
void add_social args( ( SOCIALTYPE * social ) );
void free_command args( ( CMDTYPE * command ) );
void unlink_command args( ( CMDTYPE * command ) );
void add_command args( ( CMDTYPE * command ) );

/* boards.c */
void load_boards args( ( void ) );
BD *get_board args( ( OBJ_DATA * obj ) );
void free_note args( ( NOTE_DATA * pnote ) );

/* build.c */
void RelCreate( relation_type, void *, void * );
void RelDestroy( relation_type, void *, void * );
const char *flag_string( int bitvector, const char *const flagarray[] );
const char *ext_flag_string( EXT_BV * bitvector, const char *const flagarray[] );
int get_dir( const char *txt );
char *strip_cr( const char *str );
#define VCHECK_ROOM 0
#define VCHECK_OBJ 1
#define VCHECK_MOB 2
bool is_valid_vnum( int vnum, short type );
#define start_editing( ch, data ) \
        start_editing_nolimit( ch, data, MAX_STRING_LENGTH )
void    start_editing_nolimit   args( ( CHAR_DATA *ch, char *data, int max_size ) );
void stop_editing args( ( CHAR_DATA * ch ) );
void edit_buffer args( ( CHAR_DATA * ch, char *argument ) );
const char *copy_buffer( CHAR_DATA * ch );
bool can_rmodify args( ( CHAR_DATA * ch, ROOM_INDEX_DATA * room ) );
bool can_omodify args( ( CHAR_DATA * ch, OBJ_DATA * obj ) );
bool can_mmodify args( ( CHAR_DATA * ch, CHAR_DATA * mob ) );
bool can_medit args( ( CHAR_DATA * ch, MOB_INDEX_DATA * mob ) );
void free_reset args( ( AREA_DATA * are, RESET_DATA * res ) );
void free_area args( ( AREA_DATA * are ) );
void assign_area args( ( CHAR_DATA * ch ) );
EDD *SetRExtra( ROOM_INDEX_DATA * room, const char *keywords );
bool DelRExtra( ROOM_INDEX_DATA * room, const char *keywords );
EDD *SetOExtra( OBJ_DATA * obj, const char *keywords );
bool DelOExtra( OBJ_DATA * obj, const char *keywords );
EDD *SetOExtraProto( OBJ_INDEX_DATA * obj, const char *keywords );
bool DelOExtraProto( OBJ_INDEX_DATA * obj, const char *keywords );
void fold_area( AREA_DATA * tarea, const char *filename, bool install );
int get_otype( const char *type );
int get_aflag( const char *flag );
int get_damtype( const char *type );
int get_qualitytype( const char *type );
int get_loottype( const char *type );
int get_trapflag( const char *flag );
int get_atype( const char *type );
int get_npc_race( const char *type );
int get_wearloc( const char *type );
int get_exflag( const char *flag );
int get_rflag( const char *flag );
int get_mpflag( const char *flag );
int get_oflag( const char *flag );
int get_areaflag( const char *flag );
int get_wflag( const char *flag );
int get_actflag( const char *flag );
int get_vip_flag( const char *flag );
int get_wanted_flag( const char *flag );
int get_pcflag( const char *flag );
int get_plrflag( const char *flag );
int get_risflag( const char *flag );
int get_trigflag( const char *flag );
int get_partflag( const char *flag );
int get_attackflag( const char *flag );
int get_defenseflag( const char *flag );
int get_langflag( const char *flag );
int get_langnum( const char *flag );
int get_langnum_save( const char *flag );
int get_secflag( const char *flag );
int get_npc_position( const char *position );
int get_npc_sex( const char *sex );
void smush_tilde( char *str );
void fwrite_loot_data( FILE *fpout, LOOT_DATA * loot );
void fwrite_skill_data( FILE *fpout, MOB_INDEX_DATA * pMobIndex );
void fwrite_fuss_affect( FILE * fp, AFFECT_DATA * paf );
void save_quests( void );
void fwrite_quest( FILE *fp, QUEST_DATA *quest );
void list_mob_quest( CHAR_DATA *ch, CHAR_DATA *victim );
void show_mob_quest( CHAR_DATA *ch, CHAR_DATA *victim, const char *argument );
void accept_mob_quest( CHAR_DATA *ch, CHAR_DATA *victim, const char *argument );
const char *get_status( CHAR_DATA *ch, QUEST_DATA *quest );
PLAYER_QUEST *create_player_quest( CHAR_DATA *ch, QUEST_DATA *quest );
AV_QUEST *create_available_quest( CHAR_DATA *ch, CHAR_DATA *victim, QUEST_DATA *quest );
int get_quest_type( const char *type );
void create_quest( CHAR_DATA *ch, const char *argument );
void change_quest_name( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void change_quest_description( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void change_quest_level( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void change_quest_type( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void add_prequest( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void rem_prequest( CHAR_DATA *ch, QUEST_DATA *quest, const char *argument );
void delete_quest( CHAR_DATA *ch, QUEST_DATA *quest );
void save_pools( void );
void fwrite_pool( FILE *fp, POOL_DATA *pool );
void create_pool( CHAR_DATA *ch, const char *argument );
void list_pools( CHAR_DATA *ch, const char *argument );
void display_pool( CHAR_DATA *ch, POOL_DATA *pool );
void delete_pool( POOL_DATA *pool );

/* clans.c */
CL *get_clan( const char *name );
void load_clans args( ( void ) );
void save_clan args( ( CLAN_DATA * clan ) );
void load_senate args( ( void ) );
void save_senate args( ( void ) );
PLANET_DATA *get_planet( const char *name );
void load_planets args( ( void ) );
void save_planet args( ( PLANET_DATA * planet ) );
long get_taxes args( ( PLANET_DATA * planet ) );

/* bounty.c */
BOUNTY_DATA *get_disintigration( const char *target );
void load_bounties args( ( void ) );
void save_bounties args( ( void ) );
void save_disintigrations args( ( void ) );
void remove_disintigration args( ( BOUNTY_DATA * bounty ) );
void claim_disintigration args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_disintigration args( ( CHAR_DATA * victim ) );

/* space.c */
SH *get_ship( const char *name );
void load_ships args( ( void ) );
void save_ship args( ( SHIP_DATA * ship ) );
void load_space args( ( void ) );
void save_starsystem args( ( SPACE_DATA * starsystem ) );
SPACE_DATA *starsystem_from_name( const char *name );
SPACE_DATA *starsystem_from_vnum args( ( int vnum ) );
SHIP_DATA *ship_from_obj args( ( int vnum ) );
SHIP_DATA *ship_from_entrance args( ( int vnum ) );
SHIP_DATA *ship_from_hanger args( ( int vnum ) );
SHIP_DATA *ship_from_cockpit args( ( int vnum ) );
SHIP_DATA *ship_from_navseat args( ( int vnum ) );
SHIP_DATA *ship_from_coseat args( ( int vnum ) );
SHIP_DATA *ship_from_pilotseat args( ( int vnum ) );
SHIP_DATA *ship_from_gunseat args( ( int vnum ) );
SHIP_DATA *ship_from_turret args( ( int vnum ) );
SHIP_DATA *ship_from_engine args( ( int vnum ) );
SHIP_DATA *ship_from_pilot( const char *name );
SHIP_DATA *get_ship_here( const char *name, SPACE_DATA * starsystem );
void showstarsystem args( ( CHAR_DATA * ch, SPACE_DATA * starsystem ) );
void update_space args( ( void ) );
void recharge_ships args( ( void ) );
void move_ships args( ( void ) );
void update_bus args( ( void ) );
void update_traffic args( ( void ) );
bool check_pilot args( ( CHAR_DATA * ch, SHIP_DATA * ship ) );
bool is_rental args( ( CHAR_DATA * ch, SHIP_DATA * ship ) );
void echo_to_ship( int color, SHIP_DATA * ship, const char *argument );
void echo_to_cockpit( int color, SHIP_DATA * ship, const char *argument );
void echo_to_system( int color, SHIP_DATA * ship,
                    const char *argument, SHIP_DATA * ignore );
bool extract_ship args( ( SHIP_DATA * ship ) );
bool ship_to_room args( ( SHIP_DATA * ship, int vnum ) );
long get_ship_value args( ( SHIP_DATA * ship ) );
bool rent_ship args( ( CHAR_DATA * ch, SHIP_DATA * ship ) );
void damage_ship args( ( SHIP_DATA * ship, int min, int max ) );
void damage_ship_ch args( ( SHIP_DATA * ship, int min, int max, CHAR_DATA * ch ) );
void destroy_ship args( ( SHIP_DATA * ship, CHAR_DATA * ch ) );
void ship_to_starsystem args( ( SHIP_DATA * ship, SPACE_DATA * starsystem ) );
void ship_from_starsystem args( ( SHIP_DATA * ship, SPACE_DATA * starsystem ) );
void new_missile args( ( SHIP_DATA * ship, SHIP_DATA * target, CHAR_DATA * ch, int missiletype ) );
void extract_missile args( ( MISSILE_DATA * missile ) );
SHIP_DATA *ship_in_room( ROOM_INDEX_DATA * room, const char *name );

/* comm.c */
void close_socket( DESCRIPTOR_DATA * dclose, bool force );
void write_to_buffer( DESCRIPTOR_DATA * d, const char *txt, size_t length );
void write_to_pager( DESCRIPTOR_DATA * d, const char *txt, size_t length );
void send_to_char( const char *txt, CHAR_DATA * ch );
void send_to_char_color( const char *txt, CHAR_DATA * ch );
void send_to_desc_color( const char *txt, DESCRIPTOR_DATA *d );
void send_to_pager( const char *txt, CHAR_DATA * ch );
void send_to_pager_color( const char *txt, CHAR_DATA * ch );
void ch_printf( CHAR_DATA * ch, const char *fmt, ... );
void pager_printf( CHAR_DATA * ch, const char *fmt, ... );
void act( short AType, const char *format, CHAR_DATA * ch, const void *arg1, const void *arg2, int type );

/* reset.c */
RD *make_reset args( ( char letter, int extra, int arg1, int arg2, int arg3 ) );
RD *add_reset( ROOM_INDEX_DATA *room, char letter, int extra, int arg1, int arg2, int arg3 );
void reset_area args( ( AREA_DATA * pArea ) );

/* db.c */
const char *fread_flagstring( FILE * fp );
size_t mudstrlcpy( char *dst, const char *src, size_t siz );
size_t mudstrlcat( char *dst, const char *src, size_t siz );
void show_file( CHAR_DATA * ch, const char *filename );
bool is_valid_filename( CHAR_DATA *ch, const char *direct, const char *filename );
char *str_dup args( ( char const *str ) );
void boot_db args( ( bool fCopyOver ) );
void area_update args( ( void ) );
void add_char args( ( CHAR_DATA * ch ) );
CD *create_mobile args( ( MOB_INDEX_DATA * pMobIndex ) );
OD *create_object args( ( OBJ_INDEX_DATA * pObjIndex, int level ) );
void clear_char args( ( CHAR_DATA * ch ) );
void free_char args( ( CHAR_DATA * ch ) );
const char *get_extra_descr( const char *name, EXTRA_DESCR_DATA * ed );
MID *get_mob_index args( ( int vnum ) );
OID *get_obj_index args( ( int vnum ) );
RID *get_room_index args( ( int vnum ) );
char fread_letter args( ( FILE * fp ) );
int fread_number args( ( FILE * fp ) );
float fread_float( FILE * fp );
const char *fread_string( FILE * fp );
char *fread_string_nohash( FILE * fp );
void fread_to_eol args( ( FILE * fp ) );
char *fread_word args( ( FILE * fp ) );
char *fread_line args( ( FILE * fp ) );
int number_fuzzy args( ( int number ) );
int number_range args( ( int from, int to ) );
int number_percent args( ( void ) );
int number_door args( ( void ) );
int number_bits args( ( int width ) );
int number_mm args( ( void ) );
int dice args( ( int number, int size ) );
int interpolate args( ( int level, int value_00, int value_32 ) );
void smash_tilde( char *str );
const char *smash_tilde_static( const char *str );
char *smash_tilde_copy( const char *str );
void hide_tilde args( ( char *str ) );
const char *show_tilde( const char *str );
bool str_cmp( const char *astr, const char *bstr );
bool str_prefix( const char *astr, const char *bstr );
bool str_infix( const char *astr, const char *bstr );
bool str_suffix( const char *astr, const char *bstr );
char *capitalize( const char *str );
char *strlower args( ( const char *str ) );
char *strupper args( ( const char *str ) );
const char *aoran args( ( const char *str ) );
void append_file( CHAR_DATA * ch, const char *file, const char *str );
void append_to_file( const char *file, const char *str );
void bug( const char *str, ... );
void log_string_plus args( ( const char *str, short log_type, short level ) );
void log_printf_plus( short log_type, short level, const char *fmt, ... ) __attribute__ ( ( format( printf, 3, 4 ) ) );
void log_printf( const char *fmt, ... ) __attribute__ ( ( format( printf, 1, 2 ) ) );
RID *make_room( int vnum, AREA_DATA *area );
OID *make_object( int vnum, int cvnum, const char *name );
MID *make_mobile( int vnum, int cvnum, const char *name );
ED *make_exit args( ( ROOM_INDEX_DATA * pRoomIndex, ROOM_INDEX_DATA * to_room, short door ) );
void add_help args( ( HELP_DATA * pHelp ) );
void fix_area_exits args( ( AREA_DATA * tarea ) );
void load_area_file args( ( AREA_DATA * tarea, const char *filename ) );
void randomize_exits args( ( ROOM_INDEX_DATA * room, short maxdir ) );
void make_wizlist args( ( void ) );
void tail_chain args( ( void ) );
void delete_room args( ( ROOM_INDEX_DATA * room ) );
void delete_obj args( ( OBJ_INDEX_DATA * obj ) );
void delete_mob args( ( MOB_INDEX_DATA * mob ) );
void sort_area args( ( AREA_DATA * pArea, bool proto ) );
void sort_area_by_name args( ( AREA_DATA * pArea ) ); /* Fireblade */
void smash_underscore args( ( char *str ) );
const char *smash_underscore args( ( const char *str ) );
AFFECT_DATA *fread_fuss_affect( FILE *fp, const char *word );
const char *smash_color( const char *str );
void fread_fuss_lootdata( FILE *fp, LOOT_DATA *loot );

/* fight.c */
int max_fight args( ( CHAR_DATA * ch ) );
void violence_update args( ( void ) );
ch_ret multi_hit args( ( CHAR_DATA * ch, CHAR_DATA * victim, int dt ) );
short ris_damage args( ( CHAR_DATA * ch, short dam, int ris ) );
ch_ret damage args( ( CHAR_DATA * ch, CHAR_DATA * victim, int dam, int dt ) );
void update_pos args( ( CHAR_DATA * victim ) );
void set_fighting args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void stop_fighting args( ( CHAR_DATA * ch, bool fBoth ) );
void free_fight args( ( CHAR_DATA * ch ) );
CD *who_fighting args( ( CHAR_DATA * ch ) );
void check_killer args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void check_attacker args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void death_cry args( ( CHAR_DATA * ch ) );
void stop_hunting args( ( CHAR_DATA * ch ) );
void stop_hating args( ( CHAR_DATA * ch ) );
void stop_fearing args( ( CHAR_DATA * ch ) );
void start_hunting args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void start_hating args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void start_fearing args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_hunting args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_hating args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_fearing args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_safe args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool is_safe_nm args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool legal_loot args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool check_illegal_pk args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
OBJ_DATA *raw_kill( CHAR_DATA *ch, CHAR_DATA *victim );
bool in_arena args( ( CHAR_DATA * ch ) );
void generate_threat args( ( CHAR_DATA * angry_at, CHAR_DATA * angered, int amount ) );
THREAT_DATA *has_threat args( ( CHAR_DATA * angry_at, CHAR_DATA * angered ) );
bool is_threatened args( ( CHAR_DATA * angry_at ) );
bool is_angered args( ( CHAR_DATA * angered ) );
void free_threat args( ( THREAT_DATA *threat ) );
void decay_threat args( ( void ) );
void decay_threat args( ( CHAR_DATA * angry_at, CHAR_DATA * angered, int dam ) );
CHAR_DATA *most_threat args( ( CHAR_DATA *angered ) );
int res_pen( CHAR_DATA *ch, CHAR_DATA *victim, int dam, EXT_BV damtype );
int dtype_potency( CHAR_DATA *ch, int dam, EXT_BV damtype );

/* makeobjs.c */
OBJ_DATA *make_corpse( CHAR_DATA * ch, CHAR_DATA * killer );
void make_blood args( ( CHAR_DATA * ch ) );
void make_bloodstain args( ( CHAR_DATA * ch ) );
void make_scraps args( ( OBJ_DATA * obj ) );
void make_fire args( ( ROOM_INDEX_DATA * in_room, short timer ) );
OD *make_trap args( ( int v0, int v1, int v2, int v3 ) );
OD *create_money args( ( int amount ) );

/* misc.c */
void actiondesc args( ( CHAR_DATA * ch, OBJ_DATA * obj, void *vo ) );
void jedi_checks args( ( CHAR_DATA * ch ) );
void jedi_bonus args( ( CHAR_DATA * ch ) );
void sith_penalty args( ( CHAR_DATA * ch ) );
EXT_BV fread_bitvector args( ( FILE * fp ) );
void fwrite_bitvector args( ( EXT_BV * bits, FILE * fp ) );
char *print_bitvector args( ( EXT_BV * bits ) );
EXT_BV meb( int bit );
EXT_BV multimeb( int bit, ... );


/* mud_comm.c */
const char *mprog_type_to_name( int type );

/* mud_prog.c */
#ifdef DUNNO_STRSTR
char *strstr args( ( const char *s1, const char *s2 ) );
#endif

void mprog_wordlist_check args( ( const char *arg, CHAR_DATA * mob, CHAR_DATA * actor, OBJ_DATA * object, void *vo, int type ) );
void mprog_percent_check args( ( CHAR_DATA * mob, CHAR_DATA * actor, OBJ_DATA * object, void *vo, int type ) );
void mprog_act_trigger( const char *buf, CHAR_DATA * mob, CHAR_DATA * ch,
                       OBJ_DATA * obj, void *vo );
void mprog_bribe_trigger args( ( CHAR_DATA * mob, CHAR_DATA * ch, int amount ) );
void mprog_entry_trigger args( ( CHAR_DATA * mob ) );
void mprog_give_trigger args( ( CHAR_DATA * mob, CHAR_DATA * ch, OBJ_DATA * obj ) );
void mprog_greet_trigger args( ( CHAR_DATA * mob ) );
void mprog_fight_trigger args( ( CHAR_DATA * mob, CHAR_DATA * ch ) );
void mprog_hitprcnt_trigger args( ( CHAR_DATA * mob, CHAR_DATA * ch ) );
void mprog_death_trigger args( ( CHAR_DATA * killer, CHAR_DATA * mob ) );
void mprog_random_trigger args( ( CHAR_DATA * mob ) );
void mprog_speech_trigger args( ( const char *txt, CHAR_DATA * mob ) );
void mprog_script_trigger args( ( CHAR_DATA * mob ) );
void mprog_hour_trigger args( ( CHAR_DATA * mob ) );
void mprog_time_trigger args( ( CHAR_DATA * mob ) );
void progbug args( ( const char *str, CHAR_DATA * mob ) );
void rset_supermob args( ( ROOM_INDEX_DATA * room ) );
void release_supermob( void );
void mprog_quest_trigger args( ( CHAR_DATA *mob, CHAR_DATA *ch ) );

/* player.c */
void set_title( CHAR_DATA * ch, const char *title );

/* skills.c */
int get_style_type( const char *ability );
bool check_skill( CHAR_DATA * ch, const char *command, const char *argument );
void learn_from_success( CHAR_DATA * ch, int sn );
void learn_from_failure( CHAR_DATA * ch, int sn );
bool check_parry( CHAR_DATA * ch, CHAR_DATA * victim );
bool check_dodge( CHAR_DATA * ch, CHAR_DATA * victim );
bool check_grip( CHAR_DATA * ch, CHAR_DATA * victim );
void disarm( CHAR_DATA * ch, CHAR_DATA * victim );
void trip( CHAR_DATA * ch, CHAR_DATA * victim );
void generate_buff_threat( CHAR_DATA *ch, CHAR_DATA *victim, int amount );
void charge_message( CHAR_DATA *ch, CHAR_DATA *victim, SKILLTYPE *skill, bool StartCasting );
void heal_msg( CHAR_DATA *ch, CHAR_DATA *victim, int amount );
void buff_msg( CHAR_DATA *ch, CHAR_DATA *victim, SKILLTYPE *skill );
void rbuff_msg( CHAR_DATA *ch, CHAR_DATA *victim, SKILLTYPE *skill );
void heal_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void damage_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void buff_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void enfeeble_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void redirect_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void cleanse_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void summon_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void polymorph_skill( CHAR_DATA *ch, SKILLTYPE *skill, CHAR_DATA *victim );
void sort_mob_skills( CHAR_DATA *ch );
bool mob_has_skill( CHAR_DATA *ch, int gsn );
int get_starget( const char *name );
DISC_DATA *get_discipline_from_id( int id );
FACTOR_DATA *get_factor_from_id( int id );
bool has_empty_discipline_slot( CHAR_DATA *ch );
bool is_discipline_set( CHAR_DATA *ch, DISC_DATA *discipline );
bool player_has_discipline( CHAR_DATA *ch, DISC_DATA *discipline );
void add_discipline( CHAR_DATA *ch, DISC_DATA *discipline );
void rem_discipline( CHAR_DATA *ch, DISC_DATA *discipline );
bool player_has_discipline_setslot( CHAR_DATA *ch );
void set_discipline( CHAR_DATA *ch, DISC_DATA *disc );
void unset_discipline( CHAR_DATA *ch, DISC_DATA *disc );
FACTOR_DATA *copy_factor( FACTOR_DATA *factor );
void unset_skill( CHAR_DATA *ch, SKILLTYPE *skill );
void skills_checksum( CHAR_DATA *ch );
void addfactor( CHAR_DATA *ch, SKILLTYPE *skill, FACTOR_DATA *factor );
void remfactor( CHAR_DATA *ch, SKILLTYPE *skill, FACTOR_DATA *factor, bool MakeAvailable );
void update_skill args( ( CHAR_DATA *ch, SKILLTYPE * skill ) );
void update_skills args( ( CHAR_DATA *ch ) );
void factor_to_skill( CHAR_DATA *ch, SKILLTYPE *skill, FACTOR_DATA *factor, bool Add );
int get_num_factors( SKILLTYPE *skill );
int get_num_cost_types( SKILLTYPE *skill );
int get_slot_level( CHAR_DATA *ch, SKILLTYPE *skill );
bool has_factor_already( CHAR_DATA *ch, FACTOR_DATA *factor );
void free_factor( FACTOR_DATA *factor );
void update_disciplines args( ( CHAR_DATA *ch ) );
void update_disciplines args( ( CHAR_DATA *ch, int changed ) );
void update_disciplines args( ( void ) );
bool factor_in_use( CHAR_DATA *ch, FACTOR_DATA *factor );

/* handler.c */
void free_obj( OBJ_DATA * obj );
void explode args( ( OBJ_DATA * obj ) );
int get_exp args( ( CHAR_DATA * ch, int ability ) );
int get_exp_worth args( ( CHAR_DATA * ch ) );
int exp_level args( ( short level ) );
short get_trust args( ( CHAR_DATA * ch ) );
short get_age args( ( CHAR_DATA * ch ) );
short get_curr_str args( ( CHAR_DATA * ch ) );
short get_curr_int args( ( CHAR_DATA * ch ) );
short get_curr_wis args( ( CHAR_DATA * ch ) );
short get_curr_dex args( ( CHAR_DATA * ch ) );
short get_curr_con args( ( CHAR_DATA * ch ) );
short get_curr_agi args( ( CHAR_DATA * ch ) );
short get_curr_cha args( ( CHAR_DATA * ch ) );
short get_curr_lck args( ( CHAR_DATA * ch ) );
short get_curr_frc args( ( CHAR_DATA * ch ) );
bool can_take_proto args( ( CHAR_DATA * ch ) );
int can_carry_n args( ( CHAR_DATA * ch ) );
int can_carry_w args( ( CHAR_DATA * ch ) );
bool is_name( const char *str, const char *namelist );
bool is_name_prefix( const char *str, const char *namelist );
bool nifty_is_name( const char *str, const char *namelist );
bool nifty_is_name_prefix( const char *str, const char *namelist );
void affect_modify args( ( CHAR_DATA * ch, AFFECT_DATA * paf, bool fAdd ) );
void affect_to_char args( ( CHAR_DATA * ch, AFFECT_DATA * paf ) );
void affect_to_char args( ( CHAR_DATA * ch, CHAR_DATA * from, AFFECT_DATA * paf ) );
void affect_remove args( ( CHAR_DATA * ch, AFFECT_DATA * paf ) );
void affect_strip args( ( CHAR_DATA * ch, int sn ) );
bool is_affected args( ( CHAR_DATA * ch, int sn ) );
void affect_join args( ( CHAR_DATA * ch, AFFECT_DATA * paf ) );
void char_from_room args( ( CHAR_DATA * ch ) );
void char_to_room args( ( CHAR_DATA * ch, ROOM_INDEX_DATA * pRoomIndex ) );
OD *obj_to_char args( ( OBJ_DATA * obj, CHAR_DATA * ch ) );
void obj_from_char args( ( OBJ_DATA * obj ) );
int apply_evasion args( ( OBJ_DATA * obj, int iWear ) );
OD *get_eq_char args( ( CHAR_DATA * ch, int iWear ) );
void equip_char args( ( CHAR_DATA * ch, OBJ_DATA * obj, int iWear ) );
void unequip_char args( ( CHAR_DATA * ch, OBJ_DATA * obj ) );
int count_obj_list( OBJ_INDEX_DATA *pObjIndex, OBJ_DATA *list );
void obj_from_room args( ( OBJ_DATA * obj ) );
OD *obj_to_room args( ( OBJ_DATA * obj, ROOM_INDEX_DATA * pRoomIndex ) );
OD *obj_to_obj args( ( OBJ_DATA * obj, OBJ_DATA * obj_to ) );
void obj_from_obj args( ( OBJ_DATA * obj ) );
void extract_obj args( ( OBJ_DATA * obj ) );
void extract_exit args( ( ROOM_INDEX_DATA * room, EXIT_DATA * pexit ) );
void extract_room args( ( ROOM_INDEX_DATA * room ) );
void clean_room args( ( ROOM_INDEX_DATA * room ) );
void clean_obj args( ( OBJ_INDEX_DATA * obj ) );
void clean_mob args( ( MOB_INDEX_DATA * mob ) );
void clean_resets( ROOM_INDEX_DATA *room );
void extract_char args( ( CHAR_DATA * ch, bool fPull ) );
CD *get_char_room( CHAR_DATA * ch, const char *argument );
CD *get_char_world( CHAR_DATA * ch, const char *argument );
OD *get_obj_type( OBJ_INDEX_DATA * pObjIndexData );
OD *get_obj_list( CHAR_DATA * ch, const char *argument, OBJ_DATA * list );
OD *get_obj_list_rev( CHAR_DATA * ch, const char *argument, OBJ_DATA * list );
OD *get_obj_carry( CHAR_DATA * ch, const char *argument );
OD *get_obj_wear( CHAR_DATA * ch, const char *argument );
OD *get_obj_here( CHAR_DATA * ch, const char *argument );
OD *get_obj_world( CHAR_DATA * ch, const char *argument );
int get_obj_number( OBJ_DATA * obj );
int get_obj_weight( OBJ_DATA * obj );
bool room_is_dark args( ( ROOM_INDEX_DATA * pRoomIndex ) );
bool room_is_private args( ( CHAR_DATA * ch, ROOM_INDEX_DATA * pRoomIndex ) );
bool can_see args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
bool can_see_obj args( ( CHAR_DATA * ch, OBJ_DATA * obj ) );
bool can_drop_obj args( ( CHAR_DATA * ch, OBJ_DATA * obj ) );
const char *item_type_name args( ( OBJ_DATA * obj ) );
const char *affect_loc_name args( ( int location ) );
const char *affect_bit_name args( ( EXT_BV * vector ) );
const char *extra_bit_name args( ( int extra_flags ) );
const char *magic_bit_name args( ( int magic_flags ) );
ch_ret check_for_trap args( ( CHAR_DATA * ch, OBJ_DATA * obj, int flag ) );
ch_ret check_room_for_traps args( ( CHAR_DATA * ch, int flag ) );
bool is_trapped args( ( OBJ_DATA * obj ) );
OD *get_trap args( ( OBJ_DATA * obj ) );
ch_ret spring_trap args( ( CHAR_DATA * ch, OBJ_DATA * obj ) );
void name_stamp_stats args( ( CHAR_DATA * ch ) );
void fix_char args( ( CHAR_DATA * ch ) );
void showaffect args( ( CHAR_DATA * ch, AFFECT_DATA * paf ) );
void set_cur_obj args( ( OBJ_DATA * obj ) );
bool obj_extracted args( ( OBJ_DATA * obj ) );
void queue_extracted_obj args( ( OBJ_DATA * obj ) );
void clean_obj_queue args( ( void ) );
void set_cur_char args( ( CHAR_DATA * ch ) );
bool char_died args( ( CHAR_DATA * ch ) );
void queue_extracted_char args( ( CHAR_DATA * ch, bool extract ) );
void clean_char_queue args( ( void ) );
void add_timer args( ( CHAR_DATA * ch, short type, short count, DO_FUN * fun, int value ) );
TIMER *get_timerptr args( ( CHAR_DATA * ch, short type ) );
double get_timer args( ( CHAR_DATA * ch, short type ) );
void extract_timer args( ( CHAR_DATA * ch, TIMER * timer ) );
void remove_timer args( ( CHAR_DATA * ch, short type ) );
bool in_soft_range args( ( CHAR_DATA * ch, AREA_DATA * tarea ) );
bool in_hard_range args( ( CHAR_DATA * ch, AREA_DATA * tarea ) );
bool chance args( ( CHAR_DATA * ch, short percent ) );
bool chance_attrib args( ( CHAR_DATA * ch, short percent, short attrib ) );
OD *clone_object args( ( OBJ_DATA * obj ) );
void split_obj args( ( OBJ_DATA * obj, int num ) );
void separate_obj args( ( OBJ_DATA * obj ) );
bool empty_obj args( ( OBJ_DATA * obj, OBJ_DATA * destobj, ROOM_INDEX_DATA * destroom ) );
OD *find_obj( CHAR_DATA * ch, const char *argument, bool carryonly );
bool ms_find_obj args( ( CHAR_DATA * ch ) );
void worsen_mental_state args( ( CHAR_DATA * ch, int mod ) );
void better_mental_state args( ( CHAR_DATA * ch, int mod ) );
void boost_economy args( ( AREA_DATA * tarea, int gold ) );
void lower_economy args( ( AREA_DATA * tarea, int gold ) );
void economize_mobgold args( ( CHAR_DATA * mob ) );
bool economy_has args( ( AREA_DATA * tarea, int gold ) );
void add_kill args( ( CHAR_DATA * ch, CHAR_DATA * mob ) );
int times_killed args( ( CHAR_DATA * ch, CHAR_DATA * mob ) );
void check_switches( bool possess );
void check_switch( CHAR_DATA *ch, bool possess );
int store_two_value( int v1, int v2 );
int get_value_one( int value );
int get_value_two( int value );
int evasion_from_agi( CHAR_DATA *ch );
int armor_from_con( CHAR_DATA *ch );
int hitroll_from_dex( CHAR_DATA *ch );
int damroll_from_str( CHAR_DATA *ch );
void adjust_stat( CHAR_DATA *ch, int type, int mod );
void create_group( CHAR_DATA *ch );
void disband_group( GROUP_DATA *group );
void group_invite( CHAR_DATA *leader, CHAR_DATA *invitee );
void group_leave( CHAR_DATA *ch );
void group_invite_accept( CHAR_DATA *ch );
void group_add_member( CHAR_DATA *ch, GROUP_DATA *group );
CHAR_DATA *get_group_member( CHAR_DATA *ch, const char *argument );
bool is_skill( int gsn );
void add_queue( CHAR_DATA *ch, int type );
void create_qtimer( CHAR_DATA *ch, int type );
void dispose_qtimer( QTIMER *timer );
bool is_queued( CHAR_DATA *ch, int type );
void extract_cooldown( CHAR_DATA *ch, CD_DATA *cdat );
bool is_on_cooldown( CHAR_DATA *ch, int gsn );
double get_skill_cooldown( CHAR_DATA *ch, int gsn );
void set_on_cooldown( CHAR_DATA *ch, SKILLTYPE *skill );
double get_round( CHAR_DATA *ch );
double get_haste( CHAR_DATA *ch );
void change_mind( CHAR_DATA *ch, int fom );
double get_next_thought( CHAR_DATA *ch );
int get_num_skills( CHAR_DATA *ch );
bool is_charging( CHAR_DATA *ch );
bool is_skill_set( CHAR_DATA *ch, SKILLTYPE *skill );
int get_player_skill_sn( CHAR_DATA *ch, const char *argument );
int get_skill_slot( CHAR_DATA *ch, SKILLTYPE *skill );
int get_skill_slot_level( CHAR_DATA *ch, SKILLTYPE *skill );
bool is_skill_usable( CHAR_DATA *ch, SKILLTYPE *skill );
DISC_DATA *get_discipline( const char *disc_name );
int get_cost_type( const char *argument );
int get_factor_type( const char *factor );
int get_apply_type( const char *apply );
void free_statboost( STAT_BOOST *stat_boost );
int get_stat_value( CHAR_DATA *ch, int stat );
AFFECT_DATA *copy_affect( AFFECT_DATA *aff );
bool can_teach( CHAR_DATA *teacher, DISC_DATA *discipline );
int get_discipline_cost( CHAR_DATA *teacher, DISC_DATA *discipline );
int get_num_affects( EXT_BV *affect );
QUEST_DATA *get_quest_from_id( int id );
AV_QUEST *get_available_quest_from_list args( ( CHAR_DATA *ch, const char *argument ) );
AV_QUEST *get_available_quest_from_list args( ( CHAR_DATA *ch, int list ) );
AV_QUEST *get_available_quest( CHAR_DATA *ch, QUEST_DATA *quest );
PLAYER_QUEST *get_player_quest( CHAR_DATA *ch, QUEST_DATA *quest );
bool has_quest_completed( CHAR_DATA *ch, QUEST_DATA *quest );
QUEST_DATA *get_quest_from_name( const char *argument );
void free_prequest( PRE_QUEST *pquest );
void free_quest( QUEST_DATA *quest );
void free_pquest( PLAYER_QUEST *pquest );
void free_avquest( AV_QUEST *av_quest );
void apply_affect_damtype( CHAR_DATA *ch, EXT_BV **damtype );
ITEM_MATERIAL *copy_material( ITEM_MATERIAL *material );
void free_material( ITEM_MATERIAL *material );
POOL_DATA *get_pool_from_id( int id );
void free_affect( AFFECT_DATA *af );
void free_pool( POOL_DATA *pool );
int used_sockets( OBJ_DATA *obj );
AREA_DATA *get_area_from_filename( const char *filename );
void free_loot( LOOT_DATA *loot );

/* interp.c */
bool check_pos( CHAR_DATA * ch, short position );
void interpret( CHAR_DATA * ch, const char *argument );
bool is_number( const char *arg );
int number_argument( const char *argument, char *arg );
char *one_argument( char *argument, char *arg_first );
const char *one_argument( const char *argument, char *arg_first );
const char *one_argument2( const char *argument, char *arg_first );
ST *find_social( const char *command );
CMDTYPE *find_command( const char *command );
void hash_commands( void );
void start_timer( struct timeval * sttime );
time_t end_timer( struct timeval * sttime );
void send_timer( struct timerset * vtime, CHAR_DATA * ch );
void update_userec( struct timeval * time_used, struct timerset * userec );

/* magic.c */
bool process_spell_components args( ( CHAR_DATA * ch, int sn ) );
int ch_slookup args( ( CHAR_DATA * ch, const char *name ) );
int find_spell args( ( CHAR_DATA * ch, const char *name, bool know ) );
int find_skill args( ( CHAR_DATA * ch, const char *name, bool know ) );
int find_weapon args( ( CHAR_DATA * ch, const char *name, bool know ) );
int find_tongue args( ( CHAR_DATA * ch, const char *name, bool know ) );
int skill_lookup args( ( const char *name ) );
int herb_lookup args( ( const char *name ) );
int personal_lookup args( ( CHAR_DATA * ch, const char *name ) );
int slot_lookup args( ( int slot ) );
int bsearch_skill args( ( const char *name, int first, int top ) );
int bsearch_skill_exact args( ( const char *name, int first, int top ) );
bool saves_poison_death args( ( int level, CHAR_DATA * victim ) );
bool saves_wand args( ( int level, CHAR_DATA * victim ) );
bool saves_para_petri args( ( int level, CHAR_DATA * victim ) );
bool saves_breath args( ( int level, CHAR_DATA * victim ) );
bool saves_spell_staff args( ( int level, CHAR_DATA * victim ) );
ch_ret obj_cast_spell args( ( int sn, int level, CHAR_DATA * ch, CHAR_DATA * victim, OBJ_DATA * obj ) );
int dice_parse( CHAR_DATA * ch, int level, const char *texp );
SK *get_skilltype args( ( int sn ) );

/* request.c */
void init_request_pipe args( ( void ) );
void check_requests args( ( void ) );

/* save.c */
/* object saving defines for fread/write_obj. -- Altrag */
#define OS_CARRY	0
#define OS_CORPSE	1
void write_corpses( CHAR_DATA * ch, const char *name );
void save_char_obj args( ( CHAR_DATA * ch ) );
void save_clone args( ( CHAR_DATA * ch ) );
bool load_char_obj args( ( DESCRIPTOR_DATA * d, char *name, bool preload, bool copyover ) );
void set_alarm args( ( long seconds ) );
void requip_char args( ( CHAR_DATA * ch ) );
void fwrite_obj args( ( CHAR_DATA * ch, OBJ_DATA * obj, FILE * fp, int iNest, short os_type, bool hotboot ) );
void fread_obj args( ( CHAR_DATA * ch, FILE * fp, short os_type ) );
void de_equip_char args( ( CHAR_DATA * ch ) );
void re_equip_char args( ( CHAR_DATA * ch ) );
void save_home args( ( CHAR_DATA * ch ) );

/* shops.c */

/* special.c */
SF *spec_lookup( const char *name );

/* tables.c */
int get_skill( const char *skilltype );
char *spell_name args( ( SPELL_FUN * spell ) );
char *skill_name args( ( DO_FUN * skill ) );
void load_skill_table args( ( void ) );
void save_skill_table args( ( void ) );
void sort_skill_table args( ( void ) );
void load_socials args( ( void ) );
void save_socials args( ( void ) );
void load_commands args( ( void ) );
void save_commands args( ( void ) );
SPELL_FUN *spell_function( const char *name );
DO_FUN *skill_function( const char *name );
void load_herb_table args( ( void ) );
void save_herb_table args( ( void ) );
void sort_player_skill_table( CHAR_DATA * ch );
void fwrite_skill( FILE * fpout, SKILLTYPE * skill );
SKILLTYPE *fread_skill( FILE *fp );
void load_disciplines( void );
void save_disciplines( void );
DISC_DATA *fread_discipline( FILE * fp );
void fwrite_discipline( FILE *fpout, DISC_DATA *discipline );

/* track.c */
void found_prey args( ( CHAR_DATA * ch, CHAR_DATA * victim ) );
void hunt_victim args( ( CHAR_DATA * ch ) );
int find_first_step( ROOM_INDEX_DATA * src, ROOM_INDEX_DATA * target, int maxdist );

/* update.c */
void advance_level args( ( CHAR_DATA * ch, int ability ) );
void gain_exp args( ( CHAR_DATA * ch, int gain, int ability ) );
void gain_condition args( ( CHAR_DATA * ch, int iCond, int value ) );
void update_handler args( ( void ) );
void reboot_check args( ( time_t reset ) );
#if 0
void reboot_check args( ( char *arg ) );
#endif
void auction_update args( ( void ) );
void remove_portal args( ( OBJ_DATA * portal ) );
int max_level( CHAR_DATA * ch, int ability );
void update_stats( CHAR_DATA *ch );

/* hashstr.c */
const char *str_alloc( const char *str );
const char *quick_link( const char *str );
int str_free( const char *str );
void show_hash( int count );
char *hash_stats( void );
char *check_hash( const char *str );
void hash_dump( int hash );
void show_high_hash( int top );
bool in_hash_table( const char *str );

/* newscore.c */
const char *get_race( CHAR_DATA * ch );

#undef	SK
#undef	ST
#undef	CD
#undef	MID
#undef	OD
#undef	OID
#undef	RID
#undef	SF
#undef	BD
#undef	CL
#undef	EDD
#undef	RD
#undef	ED

/*
* mudprograms stuff
*/
extern CHAR_DATA *supermob;
extern OBJ_DATA *supermob_obj;

void oprog_speech_trigger( const char *txt, CHAR_DATA * ch );
void oprog_random_trigger( OBJ_DATA * obj );
void oprog_wear_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
bool oprog_use_trigger( CHAR_DATA * ch, OBJ_DATA * obj, CHAR_DATA * vict, OBJ_DATA * targ, void *vo );
void oprog_remove_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_sac_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_damage_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_repair_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_drop_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_zap_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
char *oprog_type_to_name( int type );
int rprog_custom_trigger( char *command, char *argument, CHAR_DATA * ch );
int mprog_custom_trigger( char *command, char *argument, CHAR_DATA * ch );
int oprog_custom_trigger( char *command, char *argument, CHAR_DATA * ch );
void oprog_greet_trigger( CHAR_DATA * ch );
void oprog_get_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_examine_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_pull_trigger( CHAR_DATA * ch, OBJ_DATA * obj );
void oprog_push_trigger( CHAR_DATA * ch, OBJ_DATA * obj );

/* mud prog defines */



#define ERROR_PROG        -1
#define IN_FILE_PROG      -2

typedef enum
{
   ACT_PROG, SPEECH_PROG, RAND_PROG, FIGHT_PROG, DEATH_PROG, HITPRCNT_PROG,
   ENTRY_PROG, GREET_PROG, ALL_GREET_PROG, GIVE_PROG, BRIBE_PROG, HOUR_PROG,
   TIME_PROG, WEAR_PROG, REMOVE_PROG, SAC_PROG, LOOK_PROG, EXA_PROG, ZAP_PROG,
   GET_PROG, DROP_PROG, DAMAGE_PROG, REPAIR_PROG, RANDIW_PROG, SPEECHIW_PROG,
   PULL_PROG, PUSH_PROG, SLEEP_PROG, REST_PROG, LEAVE_PROG, SCRIPT_PROG,
   USE_PROG, QUEST_PROG, MAX_PROGTYPE
} prog_types;

/*
 * For backwards compatability
 */
#define RDEATH_PROG DEATH_PROG
#define ENTER_PROG  ENTRY_PROG
#define RFIGHT_PROG FIGHT_PROG
#define RGREET_PROG GREET_PROG
#define OGREET_PROG GREET_PROG

void rprog_leave_trigger( CHAR_DATA * ch );
void rprog_enter_trigger( CHAR_DATA * ch );
void rprog_sleep_trigger( CHAR_DATA * ch );
void rprog_rest_trigger( CHAR_DATA * ch );
void rprog_rfight_trigger( CHAR_DATA * ch );
void rprog_death_trigger( CHAR_DATA * killer, CHAR_DATA * ch );
void rprog_speech_trigger( const char *txt, CHAR_DATA * ch );
void rprog_random_trigger( CHAR_DATA * ch );
void rprog_time_trigger( CHAR_DATA * ch );
void rprog_hour_trigger( CHAR_DATA * ch );
char *rprog_type_to_name( int type );

#define OPROG_ACT_TRIGGER
#ifdef OPROG_ACT_TRIGGER
void oprog_act_trigger( const char *buf, OBJ_DATA * mobj, CHAR_DATA * ch, OBJ_DATA * obj, void *vo );
#endif
#define RPROG_ACT_TRIGGER
#ifdef RPROG_ACT_TRIGGER
void rprog_act_trigger( const char *buf, ROOM_INDEX_DATA * room, CHAR_DATA * ch, OBJ_DATA * obj, void *vo );
#endif
