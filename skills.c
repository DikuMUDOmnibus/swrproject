/***************************************************************************
*                           STAR WARS REALITY 1.0                          *
*--------------------------------------------------------------------------*
* Star Wars Reality Code Additions and changes from the Smaug Code         *
* copyright (c) 1997 by Sean Cooper                                        *
* -------------------------------------------------------------------------*
* Starwars and Starwars Names copyright(c) Lucas Film Ltd.                 *
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
*			     Player skills module			   *
****************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"

const char *const spell_flag[] = { "water", "earth", "air", "astral", "area", "distant", "reverse",
   "save_half_dam", "save_negates", "accumulative", "recastable", "noscribe",
   "nobrew", "group", "object", "character", "secretskill", "pksensitive"
};

const char *const spell_saves[] = { "none", "poison_death", "wands", "para_petri", "breath", "spell_staff" };

const char *const spell_damage[] = { "none", "fire", "cold", "electricity", "energy", "acid", "poison", "drain" };

const char *const spell_action[] = { "none", "create", "destroy", "resist", "suscept", "divinate", "obscure",
   "change"
};

const char *const spell_power[] = { "none", "minor", "greater", "major" };

const char *const spell_class[] = { "none", "lunar", "solar", "travel", "summon", "life", "death", "illusion" };

const char *const target_type[TAR_CHAR_MAX] = { "ignore", "offensive", "defensive", "self", "objinv", "any", "aoe_friendly", "aoe_enemy", "aoe_enemy_friend", "unset" };

void show_char_to_char( CHAR_DATA * list, CHAR_DATA * ch );
bool validate_spec_fun( const char *name );
int ris_save( CHAR_DATA * ch, int schance, int ris );
bool check_illegal_psteal( CHAR_DATA * ch, CHAR_DATA * victim );
void failed_casting( struct skill_type *skill, CHAR_DATA * ch, CHAR_DATA * victim, OBJ_DATA * obj );
int xp_compute( CHAR_DATA * gch, CHAR_DATA * victim );

/*
 * Dummy function
 */
void skill_notfound( CHAR_DATA * ch, const char *argument )
{
   send_to_char( "Huh?\r\n", ch );
   return;
}

int get_ssave( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_saves ) / sizeof( spell_saves[0] ); x++ )
    if( !str_cmp( name, spell_saves[x] ) )
      return x;
  return -1;
}

int get_starget( const char *name )
{
   int x;

   for( x = 0; x < TAR_CHAR_MAX; x++ )
      if( !str_cmp( name, target_type[x] ) )
         return x;
    return -1;
}

int get_style_type( const char *ability )
{
   int x;

   for( x = 0; x < STYLE_MAX; x++ )
      if( !str_cmp( ability, style_type[x] ) )
         return x;
   return -1;
}

int get_sflag( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_flag ) / sizeof( spell_flag[0] ); x++ )
    if( !str_cmp( name, spell_flag[x] ) )
      return x;
  return -1;
}

int get_sdamage( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_damage ) / sizeof( spell_damage[0] ); x++ )
    if( !str_cmp( name, spell_damage[x] ) )
      return x;
  return -1;
}

int get_saction( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_action ) / sizeof( spell_action[0] ); x++ )
    if( !str_cmp( name, spell_action[x] ) )
      return x;
  return -1;
}

int get_spower( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_power ) / sizeof( spell_power[0] ); x++ )
    if( !str_cmp( name, spell_power[x] ) )
      return x;
  return -1;
}

int get_sclass( const char *name )
{
  size_t x;

  for( x = 0; x < sizeof( spell_class ) / sizeof( spell_class[0] ); x++ )
    if( !str_cmp( name, spell_class[x] ) )
      return x;
  return -1;
}

bool is_legal_kill( CHAR_DATA * ch, CHAR_DATA * vch )
{
   if( IS_NPC( ch ) || IS_NPC( vch ) )
      return TRUE;
   if( is_safe( ch, vch ) )
      return FALSE;
   return TRUE;
}


extern const char *target_name;  /* from magic.c */

/*
 * Perform a binary search on a section of the skill table
 * Each different section of the skill table is sorted alphabetically
 * Only match skills player knows				-Thoric
 */
bool check_skill( CHAR_DATA * ch, const char *command, const char *argument )
{
   int sn;
   int first = 1;
   int top = gsn_first_tongue - 1;
   struct timeval time_used;
   int mana, move;

   /*
    * bsearch for the skill 
    */
   if( IS_NPC( ch ) )
   {
      for( ;; )
      {
         sn = ( first + top ) >> 1;

         if( LOWER( command[0] ) == LOWER( skill_table[sn]->name[0] )
             && !str_prefix( command, skill_table[sn]->name )
             && ( IS_NPC( ch ) || ( ch->pcdata->learned[sn] > 0 ) ) )
            break;
         if( first >= top )
            return FALSE;
         if( strcasecmp( command, skill_table[sn]->name ) < 1 )
            top = sn - 1;
         else
            first = sn + 1;
      }
      if( !mob_has_skill( ch, sn ) )
         return FALSE;
   }
   else
      return FALSE;


   if( is_on_cooldown( ch, sn ) )
      return TRUE;

   if( !check_pos( ch, skill_table[sn]->minimum_position ) )
      return TRUE;

   if( IS_NPC( ch ) && ( IS_AFFECTED( ch, AFF_CHARM ) || IS_AFFECTED( ch, AFF_POSSESS ) ) )
   {
      send_to_char( "For some reason, you seem unable to perform that...\r\n", ch );
      act( AT_GREY, "$n looks around.", ch, NULL, NULL, TO_ROOM );
      return TRUE;
   }

   /*
    * check if mana is required
    */
   if( skill_table[sn]->min_mana )
   {
      mana = skill_table[sn]->min_mana;

      if( !IS_NPC( ch ) && ch->mana < mana )
      {
         send_to_char( "You need to rest before using the Force any more.\r\n", ch );
         return TRUE;
      }
   }
   else
      mana = 0;

   /*
    * check if move is required
    */
   if( skill_table[sn]->min_move )
   {
      move = skill_table[sn]->min_move;

      if( !IS_NPC( ch ) && ch->move < move )
      {
         send_to_char( "You need to more stamina to use this skill.\r\n", ch );
         return TRUE;
      }
   }
   else
      move = 0;

   ch->casting_skill = sn;
   start_timer( &time_used );
   do_skill( ch, argument );
   end_timer( &time_used );
   update_userec( &time_used, &skill_table[sn]->userec );

   tail_chain(  );
   return TRUE;
}

void do_skill( CHAR_DATA *ch, const char *argument )
{
   CHAR_DATA *victim;
   char arg[MAX_INPUT_LENGTH];
   int gsn, schance;

   gsn = ch->casting_skill;
   argument = one_argument( argument, arg );

   send_to_char( "do_skill getting called.\r\n", ch );

   switch( ch->substate )
   {
      default:
         if( ( skill_table[gsn]->target != TAR_IGNORE && skill_table[gsn]->target != TAR_CHAR_SELF ) && ( victim = get_char_room( ch, arg ) ) == NULL )
         {
            send_to_char( "That person is not here.\r\n", ch );
            return;
         }

         switch( skill_table[gsn]->target )
         {
            default:
               bug( "Skill using uncoded type.", 0 );
               return;
            case TAR_IGNORE:
               if( ch->fighting && ( victim = ch->fighting->who ) == NULL )
               {
                  send_to_char( "You aren't fighting anyone.\r\n", ch );
                  return;
               }
               break;
            case TAR_CHAR_OFFENSIVE:
               if( is_same_group( ch, victim ) )
               {
                  send_to_char( "You can't cast that on someone who is grouped with you.\r\n", ch );
                  return;
               }
               if( victim == ch )
               {
                  send_to_char( "You can't attack yourself!!!\r\n", ch );
               }
               break;
            case TAR_CHAR_DEFENSIVE:
               if( !is_same_group( ch, victim ) )
               {
                  send_to_char( "You can only cast this on someone who is grouped with you.\r\n", ch );
                  return;
               }
               break;
            case TAR_CHAR_SELF:
               victim = ch;
               break;
         }

         schance = IS_NPC( ch ) ? 100 : (int)( ch->pcdata->learned[gsn] );
         if( number_percent( ) < schance )
         {
            if( skill_table[gsn]->charge > 0 )
            {
               send_to_char( "Getting here.\r\n", ch );
               charge_message( ch, victim, gsn, TRUE );
               add_timer( ch, TIMER_DO_FUN, skill_table[gsn]->charge, do_skill, 1 );
               ch->skill_target = victim;
               return;
            }
            charge_message( ch, victim, gsn, FALSE );
            break;
         }
         else
         {
            send_to_char( "You can't seem to focus enough.\r\n", ch );
            learn_from_failure( ch, gsn );
            return;
         }
         return;

      case 1:
         victim = ch->skill_target;
         gsn = ch->casting_skill;
         ch->skill_target = NULL;
         ch->casting_skill = -1;
         adjust_stat( ch, STAT_MANA, -skill_table[gsn]->min_mana );
         adjust_stat( ch, STAT_MOVE, -skill_table[gsn]->min_move );
         charge_message( ch, victim, gsn, FALSE );
         break;

      case SUB_TIMER_DO_ABORT:
         ch->substate = SUB_NONE;
         ch->skill_target = NULL;
         ch->casting_skill = -1;
         send_to_char( "You are interrupted before completing the use of your ability.\r\n", ch );
         return;
   }

   ch->substate = SUB_NONE;
   learn_from_success( ch, gsn );
   /*
    * Handle skill based on ability style
    */
   switch( skill_table[gsn]->style )
   {
      default:
         bug( "Unknown Skill Style being used by %s.", ch->name );
         break;
      case STYLE_HEALING:
         heal_skill( ch, gsn, victim );
         break;
      case STYLE_DAMAGE:
         damage_skill( ch, gsn, victim );
         break;
      case STYLE_BUFF:
         buff_skill( ch, gsn, victim );
         break;
      case STYLE_ENFEEBLE:
         enfeeble_skill( ch, gsn, victim );
         break;
      case STYLE_REDIRECT:
         redirect_skill( ch, gsn, victim );
         break;
      case STYLE_CLEANSE:
         cleanse_skill( ch, gsn, victim );
         break;
      case STYLE_SUMMON:
         summon_skill( ch, gsn, victim );
         break;
      case STYLE_POLYMORPH:
         polymorph_skill( ch, gsn, victim );
         break;
   }
   set_on_cooldown( ch, gsn );
   return;
}

void heal_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
   int amount;

   amount = ch->skill_level[COMBAT_ABILITY] + get_curr_wis( ch );
   if( skill_table[gsn]->stat_boost )
   {
      int stat;
      double mod;

      stat = skill_table[gsn]->stat_boost / 1;
      mod = skill_table[gsn]->stat_boost - stat;
      if( !mod )
         mod = 1;

      switch( stat )
      {
         case APPLY_STR:
            amount += (int)( get_curr_str( ch ) * mod );
            break;
         case APPLY_DEX:
            amount += (int)( get_curr_dex( ch ) * mod );
            break;
         case APPLY_CON:
            amount += (int)( get_curr_con( ch ) * mod );
            break;
         case APPLY_AGI:
            amount += (int)( get_curr_agi( ch ) * mod );
            break;
         case APPLY_INT:
            amount += (int)( get_curr_int( ch ) * mod );
            break;
         case APPLY_WIS:
            amount += (int)( get_curr_wis( ch ) * mod );
            break;
      }
   }
   if( skill_table[gsn]->base_roll_boost )
      amount *= skill_table[gsn]->base_roll_boost;

   amount = res_pen( ch, victim, amount, skill_table[gsn]->damtype );

   adjust_stat( victim, STAT_HIT, amount );
   generate_buff_threat( ch, victim, (int)( .8 * amount ) );
   heal_msg( ch, victim, amount );
   return;
}
void damage_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
   multi_hit( ch, victim, gsn );
   return;
}
void buff_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
}
void enfeeble_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
}
void redirect_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
}
void cleanse_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
   AFFECT_DATA *aff, *aff_next;
   bool friendly;

   if( is_same_group( ch, victim ) )
      friendly = TRUE;
   else
      friendly = FALSE;

   for( aff = victim->first_affect; aff; aff = aff_next )
   {
      aff_next = aff->next;
      if( friendly && aff->affect_type == AFFECT_ENFEEBLE )
      {
         affect_remove( victim, aff );
         break;
      }
      else if( !friendly && aff->affect_type == AFFECT_BUFF )
      {
         affect_remove( victim, aff );
         break;
      }
   }
   generate_buff_threat( ch, victim, ( skill_table[gsn]->threat * ch->skill_level[COMBAT_ABILITY] ) );
   rbuff_msg( ch, victim, gsn );
}
void summon_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
}
void polymorph_skill( CHAR_DATA *ch, int gsn, CHAR_DATA *victim )
{
}

void charge_message( CHAR_DATA *ch, CHAR_DATA *victim, int gsn, bool StartCasting )
{
   char to_char[MAX_INPUT_LENGTH], to_vict[MAX_INPUT_LENGTH], to_room[MAX_INPUT_LENGTH];

   switch( skill_table[gsn]->target )
   {
      case TAR_CHAR_OFFENSIVE:
      case TAR_CHAR_DEFENSIVE:
      case TAR_CHAR_ANY:
         if( StartCasting )
         {
            sprintf( to_char, "You start %s %s on %s.", skill_table[gsn]->type == SKILL_SKILL ? "charging" : "casting",
                               smash_underscore( skill_table[gsn]->name ),
                               IS_NPC( victim ) ? victim->short_descr : victim->name );
            sprintf( to_vict, "%s starts %s %s on you.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                               skill_table[gsn]->type == SKILL_SKILL ? "charging" : "casting",
                               smash_underscore( skill_table[gsn]->name ) );
            sprintf( to_room, "%s starts %s %s on %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                               skill_table[gsn]->type == SKILL_SKILL ? "charging" : "casting",
                               smash_underscore( skill_table[gsn]->name ),
                               IS_NPC( victim ) ? victim->short_descr : victim->name );
         }
         else
         {
            sprintf( to_char, "You %s %s on %s.", skill_table[gsn]->type == SKILL_SKILL ? "use" : "cast",
                               smash_underscore( skill_table[gsn]->name ),
                               IS_NPC( victim ) ? victim->short_descr : victim->name );
            sprintf( to_vict, "%s %s %s on you.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                               skill_table[gsn]->type == SKILL_SKILL ? "uses" : "casts",
                               smash_underscore( skill_table[gsn]->name ) );
            sprintf( to_room, "%s %s %s on %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                               skill_table[gsn]->type == SKILL_SKILL ? "uses" : "casts",
                               smash_underscore( skill_table[gsn]->name ),
                               IS_NPC( victim ) ? victim->short_descr : victim->name );
         }
      case TAR_CHAR_SELF:
         if( StartCasting )
         {
            sprintf( to_char, "You begin to %s %s.", skill_table[gsn]->type == SKILL_SKILL ? "charge" : "cast", smash_underscore( skill_table[gsn]->name ) );
            sprintf( to_room, "%s begins to %s %s.", IS_NPC( ch ) ? ch->short_descr : ch->name, skill_table[gsn]->type == SKILL_SKILL ? "charge" : "cast", smash_underscore( skill_table[gsn]->name ) );
         }
         else
         {
            sprintf( to_char, "You %s %s.", skill_table[gsn]->type == SKILL_SKILL ? "use" : "cast", smash_underscore( skill_table[gsn]->name ) );
            sprintf( to_room, "%s  %s %s.", IS_NPC( ch ) ? ch->short_descr : ch->name, skill_table[gsn]->type == SKILL_SKILL ? "uses" : "casts", smash_underscore( skill_table[gsn]->name ) );
         }
   }
   act( AT_YELLOW, to_char, ch, NULL, victim, TO_CHAR );
   if( to_vict[0] != '\0' )
      act( AT_YELLOW, to_vict, ch, NULL, victim, TO_VICT );
   act( AT_YELLOW, to_room, ch, NULL, victim, TO_NOTVICT );
   return;
}

void buff_msg( CHAR_DATA *ch, CHAR_DATA *victim, int gsn )
{
   char to_char[MAX_INPUT_LENGTH], to_vict[MAX_INPUT_LENGTH], to_room[MAX_INPUT_LENGTH];

   if( ch != victim )
   {
      sprintf( to_char, "You %s %s with the affects of %s.", skill_table[gsn]->target == TAR_CHAR_OFFENSIVE ? "enfeeble" : "buff",
                         IS_NPC( victim ) ? victim->short_descr : victim->name,
                         smash_underscore( skill_table[gsn]->name ) );
      sprintf( to_vict, "%s %s you with the affects of %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         skill_table[gsn]->target == TAR_CHAR_OFFENSIVE ? "enfeebles" : "buffs",
                         smash_underscore( skill_table[gsn]->name ) );
      sprintf( to_room, "%s %s %s with the affects of %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         skill_table[gsn]->target == TAR_CHAR_OFFENSIVE ? "enfeebles" : "buffs",
                         IS_NPC( victim ) ? victim->short_descr : victim->name,
                         smash_underscore( skill_table[gsn]->name ) );
   }
   else
   {
      sprintf( to_char, "You %s yourself with the affects of %s.", skill_table[gsn]->target == TAR_CHAR_OFFENSIVE ? "enfeeble" : "buff", smash_underscore( skill_table[gsn]->name ) );
      sprintf( to_room, "%s %s themselves with the affect of %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         skill_table[gsn]->target == TAR_CHAR_OFFENSIVE ? "enfeebles" : "buffs",
                         smash_underscore( skill_table[gsn]->name ) );
   }

   act( AT_PLAIN, to_char, ch, NULL, victim, TO_CHAR );
   if( to_vict[0] != '\0' )
      act( AT_PLAIN, to_vict, ch, NULL, victim, TO_VICT );
   act( AT_PLAIN, to_room, ch, NULL, victim, TO_NOTVICT );
}

void rbuff_msg( CHAR_DATA *ch, CHAR_DATA *victim, int gsn )
{
   char to_char[MAX_INPUT_LENGTH], to_vict[MAX_INPUT_LENGTH], to_room[MAX_INPUT_LENGTH];

   if( ch != victim )
   {
      sprintf( to_char, "You remove the affects of %s from %s.",
                         smash_underscore( skill_table[gsn]->name ),
                         IS_NPC( victim ) ? victim->short_descr : victim->name );
      sprintf( to_vict, "%s removes the affects of %s from you.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         smash_underscore( skill_table[gsn]->name ) );
      sprintf( to_room, "%s removes the affects of %s from %s.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         smash_underscore( skill_table[gsn]->name ),
                         IS_NPC( victim ) ? victim->short_descr : victim->name );
   }
   else
   {
      sprintf( to_char, "You remove the affects of %s on yourself.", smash_underscore( skill_table[gsn]->name ) );
      sprintf( to_room, "%s removes the affects of %s on themselves.", IS_NPC( ch ) ? ch->short_descr : ch->name,
                         smash_underscore( skill_table[gsn]->name ) );
   }

   act( AT_PLAIN, to_char, ch, NULL, victim, TO_CHAR );
   if( to_vict[0] != '\0' )
      act( AT_PLAIN, to_vict, ch, NULL, victim, TO_VICT );
   act( AT_PLAIN, to_room, ch, NULL, victim, TO_NOTVICT );

}

void heal_msg( CHAR_DATA *ch, CHAR_DATA *victim, int amount )
{
   char to_char[MAX_INPUT_LENGTH], to_vict[MAX_INPUT_LENGTH], to_room[MAX_INPUT_LENGTH];

   if( ch != victim )
   {
      sprintf( to_char, "You heal %s for %d.", IS_NPC( victim ) ? victim->short_descr : victim->name, amount );
      sprintf( to_vict, "%s heals you for %d.", IS_NPC( ch ) ? ch->short_descr : ch->name, amount );
      sprintf( to_room, "%s heals %s for %d.", IS_NPC( ch ) ? ch->short_descr : ch->name, IS_NPC( victim ) ? victim->short_descr : victim->name, amount );
   }
   else
   {
      sprintf( to_char, "You heal yourself for %d.", amount );
      sprintf( to_room, "%s heals themselves for %d.", IS_NPC( ch ) ? ch->short_descr : ch->name, amount );
   }

   act( AT_PLAIN, to_char, ch, NULL, victim, TO_CHAR );
   if( to_vict[0] != '\0' )
      act( AT_PLAIN, to_vict, ch, NULL, victim, TO_VICT );
   act( AT_PLAIN, to_room, ch, NULL, victim, TO_NOTVICT );
}


/*
 * Lookup a skills information
 * High god command
 */
void do_slookup( CHAR_DATA * ch, const char *argument )
{
   char buf[MAX_STRING_LENGTH];
   char arg[MAX_INPUT_LENGTH];
   int sn, x;
   SKILLTYPE *skill = NULL;

   one_argument( argument, arg );
   if( arg[0] == '\0' )
   {
      send_to_char( "Slookup what?\r\n", ch );
      return;
   }

   if( !str_cmp( arg, "all" ) )
   {
      for( sn = 0; sn < top_sn && skill_table[sn] && skill_table[sn]->name; sn++ )
         pager_printf( ch, "Sn: %4d Slot: %4d Skill/spell: '%-20s' Style Type: %s\r\n",
                       sn, skill_table[sn]->slot, skill_table[sn]->name, style_type[skill_table[sn]->style] );
   }
   else if( !str_cmp( arg, "herbs" ) )
   {
      for( sn = 0; sn < top_herb && herb_table[sn] && herb_table[sn]->name; sn++ )
         pager_printf( ch, "%d) %s\r\n", sn, herb_table[sn]->name );
   }
   else
   {
      AFFECT_DATA *aff;
      char num[MAX_STRING_LENGTH];
      int cnt = 0;

      if( arg[0] == 'h' && is_number( arg + 1 ) )
      {
         sn = atoi( arg + 1 );
         if( !IS_VALID_HERB( sn ) )
         {
            send_to_char( "Invalid herb.\r\n", ch );
            return;
         }
         skill = herb_table[sn];
      }
      else if( is_number( arg ) )
      {
         sn = atoi( arg );
         if( ( skill = get_skilltype( sn ) ) == NULL )
         {
            send_to_char( "Invalid sn.\r\n", ch );
            return;
         }
         sn %= 1000;
      }
      else if( ( sn = skill_lookup( arg ) ) >= 0 )
         skill = skill_table[sn];
      else if( ( sn = herb_lookup( arg ) ) >= 0 )
         skill = herb_table[sn];
      else
      {
         send_to_char( "No such skill, spell, proficiency or tongue.\r\n", ch );
         return;
      }
      if( !skill )
      {
         send_to_char( "Not created yet.\r\n", ch );
         return;
      }

      ch_printf( ch, "Sn: %4d Slot: %4d %s: '%-20s'\r\n", sn, skill->slot, skill_tname[skill->type], skill->name );
      ch_printf( ch, "Type: %s  Target: %s  Minpos: %d  Mana: %d  Move: %d Beats: %d Charge: %d\r\n",
                 skill_tname[skill->type],
                 target_type[skill->target],
                 skill->minimum_position, skill->min_mana, skill->min_move, skill->beats, skill->charge );
      ch_printf( ch, "Cooldown: %d Style Type: %s Damtype:",
                 skill->cooldown,
                 style_type[skill->style] );
      if( xIS_EMPTY( skill->damtype ) )
         send_to_char( " none\r\n", ch );
      else
      {
         for( x = 0; x < MAX_DAMTYPE; x++ )
            if( xIS_SET( skill->damtype, x ) )
               ch_printf( ch, " %s,", d_type[x] );
          send_to_char( "\r\n", ch );
      }
      ch_printf( ch, "Stat Boost: %f, Attack Boost: %f\r\nDefense Mod: %f, Base Roll Boost: %f\r\n",
                 skill->stat_boost, skill->attack_boost, skill->defense_mod, skill->base_roll_boost );
      ch_printf( ch, "Flags: %d  Guild: %d  Code: %s\r\n",
                 skill->flags,
                 skill->guild, skill->skill_fun ? skill->skill_fun_name : skill->spell_fun_name );
      ch_printf( ch, "Dammsg: %s\r\nWearoff: %s\n", skill->noun_damage, skill->msg_off ? skill->msg_off : "(none set)" );
      if( skill->dice && skill->dice[0] != '\0' )
         ch_printf( ch, "Dice: %s\r\n", skill->dice );
      if( skill->teachers && skill->teachers[0] != '\0' )
         ch_printf( ch, "Teachers: %s\r\n", skill->teachers );
      if( skill->components && skill->components[0] != '\0' )
         ch_printf( ch, "Components: %s\r\n", skill->components );
      if( skill->participants )
         ch_printf( ch, "Participants: %d\r\n", ( int )skill->participants );
      if( skill->userec.num_uses )
         send_timer( &skill->userec, ch );
      for( aff = skill->first_affect; aff; aff = aff->next )
      {
         if( aff == skill->first_affect )
            send_to_char( "\r\n", ch );
         sprintf( buf, "Affect %d", ++cnt );
         if( aff->location )
         {
            strcat( buf, " modifies " );
            strcat( buf, a_types[aff->location % REVERSE_APPLY] );
            strcat( buf, " by '" );
            sprintf( num, "%d", aff->modifier );
            strcat( buf, num);
            if( !xIS_EMPTY( aff->bitvector ) )
               strcat( buf, "' and" );
            else
               strcat( buf, "'" );
         }
         if( !xIS_EMPTY( aff->bitvector ) )
         {
            strcat( buf, " applies" );
            for( x = 0; x < MAX_AFF; x++ )
               if( xIS_SET( aff->bitvector, x ) )
               {
                  strcat( buf, " " );
                  strcat( buf, a_flags[x] );
               }
         }
         if( aff->duration > 0 )
         {
            strcat( buf, " for '" );
            sprintf( num, "%f", aff->duration );
            strcat( buf, num );
            strcat( buf, "' rounds" );
         }
         if( aff->location >= REVERSE_APPLY )
            strcat( buf, " (affects caster only)" );
         strcat( buf, "\r\n" );
         send_to_char( buf, ch );
         if( !aff->next )
            send_to_char( "\r\n", ch );
      }
      if( skill->hit_char && skill->hit_char[0] != '\0' )
         ch_printf( ch, "Hitchar   : %s\r\n", skill->hit_char );
      if( skill->hit_vict && skill->hit_vict[0] != '\0' )
         ch_printf( ch, "Hitvict   : %s\r\n", skill->hit_vict );
      if( skill->hit_room && skill->hit_room[0] != '\0' )
         ch_printf( ch, "Hitroom   : %s\r\n", skill->hit_room );
      if( skill->miss_char && skill->miss_char[0] != '\0' )
         ch_printf( ch, "Misschar  : %s\r\n", skill->miss_char );
      if( skill->miss_vict && skill->miss_vict[0] != '\0' )
         ch_printf( ch, "Missvict  : %s\r\n", skill->miss_vict );
      if( skill->miss_room && skill->miss_room[0] != '\0' )
         ch_printf( ch, "Missroom  : %s\r\n", skill->miss_room );
      if( skill->die_char && skill->die_char[0] != '\0' )
         ch_printf( ch, "Diechar   : %s\r\n", skill->die_char );
      if( skill->die_vict && skill->die_vict[0] != '\0' )
         ch_printf( ch, "Dievict   : %s\r\n", skill->die_vict );
      if( skill->die_room && skill->die_room[0] != '\0' )
         ch_printf( ch, "Dieroom   : %s\r\n", skill->die_room );
      if( skill->imm_char && skill->imm_char[0] != '\0' )
         ch_printf( ch, "Immchar   : %s\r\n", skill->imm_char );
      if( skill->imm_vict && skill->imm_vict[0] != '\0' )
         ch_printf( ch, "Immvict   : %s\r\n", skill->imm_vict );
      if( skill->imm_room && skill->imm_room[0] != '\0' )
         ch_printf( ch, "Immroom   : %s\r\n", skill->imm_room );
      if( skill->type != SKILL_HERB && skill->guild >= 0 && skill->guild < MAX_ABILITY )
      {
         sprintf( buf, "guild: %s   Align: %4d   lvl: %3d\r\n",
                  ability_name[skill->guild], skill->alignment, skill->min_level );
         send_to_char( buf, ch );
      }
      send_to_char( "\r\n", ch );
   }

   return;
}

/*
 * Set a skill's attributes or what skills a player has.
 * High god command, with support for creating skills/spells/herbs/etc
 */
void do_sset( CHAR_DATA * ch, const char *argument )
{
   char arg1[MAX_INPUT_LENGTH];
   char arg2[MAX_INPUT_LENGTH];
   CHAR_DATA *victim;
   int value;
   int sn;
   bool fAll;

   argument = one_argument( argument, arg1 );
   argument = one_argument( argument, arg2 );

   if( arg1[0] == '\0' || arg2[0] == '\0' || argument[0] == '\0' )
   {
      send_to_char( "Syntax: sset <victim> <skill> <value>\r\n", ch );
      send_to_char( "or:     sset <victim> all     <value>\r\n", ch );
      if( get_trust( ch ) > LEVEL_SUB_IMPLEM )
      {
         send_to_char( "or:     sset save skill table\r\n", ch );
         send_to_char( "or:     sset save herb table\r\n", ch );
         send_to_char( "or:     sset create skill 'new skill'\r\n", ch );
         send_to_char( "or:     sset create herb 'new herb'\r\n", ch );
      }
      if( get_trust( ch ) > LEVEL_GREATER )
      {
         send_to_char( "or:     sset <sn>     <field> <value>\r\n", ch );
         send_to_char( "\r\nField being one of:\r\n", ch );
         send_to_char( "  name code target minpos slot mana beats dammsg wearoff guild minlevel\r\n", ch );
         send_to_char( "  type damtype acttype classtype powertype flag dice value difficulty affect\r\n", ch );
         send_to_char( "  rmaffect level adept hit miss die imm (char/vict/room)\r\n", ch );
         send_to_char( "  charge move threat statboost defensemod attackboost, \r\n", ch );
         send_to_char( "  baserollboost damtype style cooldown\r\n", ch );
         send_to_char( "  components teachers\r\n", ch );
         send_to_char( "Affect having the fields: <location> <modfifier> [duration] [bitvector]\r\n", ch );
         send_to_char( "(See AFFECTTYPES for location, and AFFECTED_BY for bitvector)\r\n", ch );
      }
      send_to_char( "Skill being any skill or spell.\r\n", ch );
      return;
   }

   if( get_trust( ch ) > LEVEL_SUB_IMPLEM && !str_cmp( arg1, "save" ) && !str_cmp( argument, "table" ) )
   {
      if( !str_cmp( arg2, "skill" ) )
      {
         send_to_char( "Saving skill table...\r\n", ch );
         save_skill_table(  );
         return;
      }
      if( !str_cmp( arg2, "herb" ) )
      {
         send_to_char( "Saving herb table...\r\n", ch );
         save_herb_table(  );
         return;
      }
   }
   if( get_trust( ch ) > LEVEL_SUB_IMPLEM
       && !str_cmp( arg1, "create" ) && ( !str_cmp( arg2, "skill" ) || !str_cmp( arg2, "herb" ) ) )
   {
      struct skill_type *skill;
      short type = SKILL_UNKNOWN;

      if( !str_cmp( arg2, "herb" ) )
      {
         type = SKILL_HERB;
         if( top_herb >= MAX_HERB )
         {
            ch_printf( ch, "The current top herb is %d, which is the maximum.  "
                       "To add more herbs,\r\nMAX_HERB will have to be "
                       "raised in mud.h, and the mud recompiled.\r\n", top_sn );
            return;
         }
      }
      else if( top_sn >= MAX_SKILL )
      {
         ch_printf( ch, "The current top sn is %d, which is the maximum.  "
                    "To add more skills,\r\nMAX_SKILL will have to be "
                    "raised in mud.h, and the mud recompiled.\r\n", top_sn );
         return;
      }
      CREATE( skill, struct skill_type, 1 );
      if( type == SKILL_HERB )
      {
         int max, x;

         herb_table[top_herb++] = skill;
         for( max = x = 0; x < top_herb - 1; x++ )
            if( herb_table[x] && herb_table[x]->slot > max )
               max = herb_table[x]->slot;
         skill->slot = max + 1;
      }
      else
         skill_table[top_sn++] = skill;
      skill->name = str_dup( argument );
      skill->noun_damage = str_dup( "" );
      skill->msg_off = str_dup( "" );
      skill->spell_fun = spell_smaug;
      skill->type = type;
      send_to_char( "Done.\r\n", ch );
      return;
   }

   if( arg1[0] == 'h' )
      sn = atoi( arg1 + 1 );
   else
      sn = atoi( arg1 );
   if( get_trust( ch ) > LEVEL_GREATER
       && ( ( arg1[0] == 'h' && is_number( arg1 + 1 ) && ( sn = atoi( arg1 + 1 ) ) >= 0 )
            || ( is_number( arg1 ) && ( sn = atoi( arg1 ) ) >= 0 ) ) )
   {
      struct skill_type *skill;

      if( arg1[0] == 'h' )
      {
         if( sn >= top_herb )
         {
            send_to_char( "Herb number out of range.\r\n", ch );
            return;
         }
         skill = herb_table[sn];
      }
      else
      {
         if( ( skill = get_skilltype( sn ) ) == NULL )
         {
            send_to_char( "Skill number out of range.\r\n", ch );
            return;
         }
         sn %= 1000;
      }

      if( !str_cmp( arg2, "difficulty" ) )
      {
         skill->difficulty = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "participants" ) )
      {
         skill->participants = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "alignment" ) )
      {
         skill->alignment = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "acttype" ) )
      {
         int x = get_saction( argument );

         if( x == -1 )
            send_to_char( "Not a spell action type.\r\n", ch );
         else
         {
            SET_SACT( skill, x );
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }
      if( !str_cmp( arg2, "classtype" ) )
      {
         int x = get_sclass( argument );

         if( x == -1 )
            send_to_char( "Not a spell class type.\r\n", ch );
         else
         {
            SET_SCLA( skill, x );
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }
      if( !str_cmp( arg2, "powertype" ) )
      {
         int x = get_spower( argument );

         if( x == -1 )
            send_to_char( "Not a spell power type.\r\n", ch );
         else
         {
            SET_SPOW( skill, x );
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }
      if( !str_cmp( arg2, "flag" ) )
      {
         int x = get_sflag( argument );

         if( x == -1 )
            send_to_char( "Not a spell flag.\r\n", ch );
         else
         {
            TOGGLE_BIT( skill->flags, 1 << ( x + 11 ) );
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }
      if( !str_cmp( arg2, "saves" ) )
      {
         int x = get_ssave( argument );

         if( x == -1 )
            send_to_char( "Not a saving type.\r\n", ch );
         else
         {
            skill->saves = x;
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }

	if ( !str_cmp( arg2, "code" ) )
	{
	   SPELL_FUN *spellfun;
	   DO_FUN *dofun;

	   if( !str_prefix( "do_", argument ) && ( dofun = skill_function( argument ) ) != skill_notfound )
	     {
	       skill->skill_fun = dofun;
	       skill->spell_fun = NULL;
	       DISPOSE( skill->skill_fun_name );
	       skill->skill_fun_name = str_dup( argument );
	     }		
	   else if( ( spellfun = spell_function( argument ) ) != spell_notfound )
	     {
	       skill->spell_fun = spellfun;
	       skill->skill_fun = NULL;
	       DISPOSE( skill->skill_fun_name );
	       skill->spell_fun_name = str_dup( argument );
	     }
	   else if( validate_spec_fun( argument ) )
	     {
	       send_to_char( "Cannot use a spec_fun for skills or spells.\r\n", ch );
	       return;
	     }
	   else
	     {
	       send_to_char( "Not a spell or skill.\r\n", ch );
	       return;
	     }
	   send_to_char( "Ok.\r\n", ch );
	   return;
	}

      if( !str_cmp( arg2, "target" ) )
      {
         int x = get_starget( argument );

         if( x == -1 )
            send_to_char( "Not a valid target type.\r\n", ch );
         else
         {
            skill->target = x;
            send_to_char( "Ok.\r\n", ch );
         }
         return;
      }
      if( !str_cmp( arg2, "minpos" ) )
      {
         skill->minimum_position = URANGE( POS_DEAD, atoi( argument ), POS_DRAG );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "minlevel" ) )
      {
         skill->min_level = URANGE( 1, atoi( argument ), MAX_LEVEL );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "slot" ) )
      {
         skill->slot = URANGE( 0, atoi( argument ), 30000 );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "mana" ) )
      {
         skill->min_mana = URANGE( 0, atoi( argument ), 2000 );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "move" ) )
      {
         skill->min_move = URANGE( 0, atoi( argument ), 2000 );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "beats" ) )
      {
         skill->beats = URANGE( 0, atoi( argument ), 120 );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "charge" ) )
      {
         skill->charge = atoi( argument );
         send_to_char( "Ok\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "cooldown" ) )
      {
         skill->cooldown = atoi( argument );
         send_to_char( "Ok\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "guild" ) )
      {
         skill->guild = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "value" ) )
      {
         skill->value = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "type" ) )
      {
         skill->type = get_skill( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "style" ) )
      {
         skill->style = get_style_type( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "rmaffect" ) )
      {
         AFFECT_DATA *aff, *aff_next;
         int num = atoi( argument );
         int cnt = 0;

         if( !skill->first_affect )
         {
            send_to_char( "This spell has no special affects to remove.\r\n", ch );
            return;
         }
         for( aff = skill->first_affect; aff; aff = aff_next )
         {
            aff_next = aff->next;

            if( ++cnt == num )
            {
               UNLINK( aff, skill->first_affect, skill->last_affect, next, prev );
               aff->from = NULL;
               if( aff->factor_src )
                  remfactor( NULL, skill, aff->factor_src, FALSE );
               DISPOSE( aff );
               send_to_char( "Removed.\r\n", ch );
               return;
            }
         }
         send_to_char( "Not found.\r\n", ch );
         return;
      }

      /*
       * affect <location> <modifier> <duration> <bitvector>
       */
      if( !str_cmp( arg2, "affect" ) )
      {
         char location[MAX_INPUT_LENGTH];
         char modifier[MAX_INPUT_LENGTH];
         char duration[MAX_INPUT_LENGTH];
         char bitvector[MAX_INPUT_LENGTH];
         int loc, tmpbit;
         EXT_BV bit;
         AFFECT_DATA *aff;

         argument = one_argument( argument, location );
         argument = one_argument( argument, modifier );
         argument = one_argument( argument, duration );

         if( location[0] == '!' )
            loc = get_atype( location + 1 ) + REVERSE_APPLY;
         else
            loc = get_atype( location );
         if( ( loc % REVERSE_APPLY ) < 0 || ( loc % REVERSE_APPLY ) >= MAX_APPLY_TYPE )
         {
            send_to_char( "Unknown affect location.  See AFFECTTYPES.\r\n", ch );
            return;
         }
         xCLEAR_BITS( bit );
         while( argument[0] != 0 )
         {
            argument = one_argument( argument, bitvector );
            if( ( tmpbit = get_aflag( bitvector ) ) == -1 )
               ch_printf( ch, "Unknown bitvector: %s.  See AFFECTED_BY\r\n", bitvector );
            else
               xSET_BIT( bit, tmpbit );
         }
         CREATE( aff, AFFECT_DATA, 1 );
         aff->modifier = atoi( modifier );
         aff->duration = atoi( duration );
         aff->location = loc;
         xSET_BITS( aff->bitvector, bit );
         LINK( aff, skill->first_affect, skill->last_affect, next, prev );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "level" ) )
      {
         skill->min_level = URANGE( 1, atoi( argument ), MAX_LEVEL );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "adept" ) )
      {
         return;
      }
      if( !str_cmp( arg2, "name" ) )
      {
         DISPOSE( skill->name );
         skill->name = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "dammsg" ) )
      {
         DISPOSE( skill->noun_damage );
         if( !str_cmp( argument, "clear" ) )
            skill->noun_damage = str_dup( "" );
         else
            skill->noun_damage = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "wearoff" ) )
      {
         DISPOSE( skill->msg_off );
         if( str_cmp( argument, "clear" ) )
            skill->msg_off = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "hitchar" ) )
      {
         if( skill->hit_char )
            DISPOSE( skill->hit_char );
         if( str_cmp( argument, "clear" ) )
            skill->hit_char = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "hitvict" ) )
      {
         if( skill->hit_vict )
            DISPOSE( skill->hit_vict );
         if( str_cmp( argument, "clear" ) )
            skill->hit_vict = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "hitroom" ) )
      {
         if( skill->hit_room )
            DISPOSE( skill->hit_room );
         if( str_cmp( argument, "clear" ) )
            skill->hit_room = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "misschar" ) )
      {
         if( skill->miss_char )
            DISPOSE( skill->miss_char );
         if( str_cmp( argument, "clear" ) )
            skill->miss_char = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "missvict" ) )
      {
         if( skill->miss_vict )
            DISPOSE( skill->miss_vict );
         if( str_cmp( argument, "clear" ) )
            skill->miss_vict = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "missroom" ) )
      {
         if( skill->miss_room )
            DISPOSE( skill->miss_room );
         if( str_cmp( argument, "clear" ) )
            skill->miss_room = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "diechar" ) )
      {
         if( skill->die_char )
            DISPOSE( skill->die_char );
         if( str_cmp( argument, "clear" ) )
            skill->die_char = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "dievict" ) )
      {
         if( skill->die_vict )
            DISPOSE( skill->die_vict );
         if( str_cmp( argument, "clear" ) )
            skill->die_vict = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "dieroom" ) )
      {
         if( skill->die_room )
            DISPOSE( skill->die_room );
         if( str_cmp( argument, "clear" ) )
            skill->die_room = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "immchar" ) )
      {
         if( skill->imm_char )
            DISPOSE( skill->imm_char );
         if( str_cmp( argument, "clear" ) )
            skill->imm_char = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "immvict" ) )
      {
         if( skill->imm_vict )
            DISPOSE( skill->imm_vict );
         if( str_cmp( argument, "clear" ) )
            skill->imm_vict = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "immroom" ) )
      {
         if( skill->imm_room )
            DISPOSE( skill->imm_room );
         if( str_cmp( argument, "clear" ) )
            skill->imm_room = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "dice" ) )
      {
         if( skill->dice )
            DISPOSE( skill->dice );
         if( str_cmp( argument, "clear" ) )
            skill->dice = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "components" ) )
      {
         if( skill->components )
            DISPOSE( skill->components );
         if( str_cmp( argument, "clear" ) )
            skill->components = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "teachers" ) )
      {
         if( skill->teachers )
            DISPOSE( skill->teachers );
         if( str_cmp( argument, "clear" ) )
            skill->teachers = str_dup( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "statboost" ) )
      {
         skill->stat_boost = atof( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "attackboost" ) )
      {
         skill->attack_boost = atof( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "defensemod" ) )
      {
         skill->defense_mod = atof( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "baserollboost" ) )
      {
         skill->base_roll_boost = atof( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "threat" ) )
      {
         skill->threat = atoi( argument );
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      if( !str_cmp( arg2, "damtype" ) )
      {
         while( argument[0] != '\0' )
         {
            argument = one_argument( argument, arg2 );
            if( ( value = get_damtype( arg2 ) ) == -1 )
            {
               ch_printf( ch, "%s is an invalid damtype.\r\n", arg2 );
               continue;
            }
            xTOGGLE_BIT( skill->damtype, value );
         }
         send_to_char( "Ok.\r\n", ch );
         return;
      }
      do_sset( ch, "" );
      return;
   }

   if( ( victim = get_char_world( ch, arg1 ) ) == NULL )
   {
      if( ( sn = skill_lookup( arg1 ) ) >= 0 )
      {
         sprintf( arg1, "%d %s %s", sn, arg2, argument );
         do_sset( ch, arg1 );
      }
      else
         send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( IS_NPC( victim ) )
   {
      send_to_char( "Not on NPC's.\r\n", ch );
      return;
   }

   fAll = !str_cmp( arg2, "all" );
   sn = 0;
   if( !fAll && ( sn = skill_lookup( arg2 ) ) < 0 )
   {
      send_to_char( "No such skill or spell.\r\n", ch );
      return;
   }

   /*
    * Snarf the value.
    */
   if( !is_number( argument ) )
   {
      send_to_char( "Value must be numeric.\r\n", ch );
      return;
   }

   value = atoi( argument );
   if( value < 0 || value > 100 )
   {
      send_to_char( "Value range is 0 to 100.\r\n", ch );
      return;
   }

   if( fAll )
   {
      for( sn = 0; sn < top_sn; sn++ )
      {
         /*
          * Fix by Narn to prevent ssetting skills the player shouldn't have. 
          */
         if( skill_table[sn]->guild < 0 || skill_table[sn]->guild >= MAX_ABILITY )
            continue;
         if( skill_table[sn]->name
             && ( victim->skill_level[skill_table[sn]->guild] >= skill_table[sn]->min_level || value == 0 ) )
            victim->pcdata->learned[sn] = value;
      }
   }
   else
      victim->pcdata->learned[sn] = value;

   return;
}


void learn_from_success( CHAR_DATA * ch, int sn )
{
   int adept, gain, sklvl, learn, percent, schance;

   if( IS_NPC( ch ) || ch->pcdata->learned[sn] == 0 )
      return;

   if( sn == skill_lookup( "meditate" ) && ch->skill_level[FORCE_ABILITY] < 2 )
      gain_exp( ch, 25, FORCE_ABILITY );

   sklvl = skill_table[sn]->min_level;

   if( skill_table[sn]->guild < 0 || skill_table[sn]->guild >= MAX_ABILITY )
      return;

   adept = ( ch->skill_level[skill_table[sn]->guild] - skill_table[sn]->min_level ) * 5 + 50;
   adept = UMIN( adept, 100 );

   if( ch->pcdata->learned[sn] >= adept )
      return;

   if( sklvl == 0 || sklvl > ch->skill_level[skill_table[sn]->guild] )
      sklvl = ch->skill_level[skill_table[sn]->guild];
   if( ch->pcdata->learned[sn] < 100 )
   {
      schance = ch->pcdata->learned[sn] + ( 5 * skill_table[sn]->difficulty );
      percent = number_percent(  );
      if( percent >= schance )
         learn = 2;
      else if( schance - percent > 25 )
         return;
      else
         learn = 1;
      ch->pcdata->learned[sn] = UMIN( adept, ch->pcdata->learned[sn] + learn );
      if( ch->pcdata->learned[sn] == 100 )   /* fully learned! */
      {
         gain = 50 * sklvl;
         set_char_color( AT_WHITE, ch );
         ch_printf( ch, "You are now an adept of %s!  You gain %d bonus experience!\r\n", skill_table[sn]->name, gain );
      }
      else
      {
         gain = 10 * sklvl;
         if( !ch->fighting && sn != gsn_hide && sn != gsn_sneak )
         {
            set_char_color( AT_WHITE, ch );
            ch_printf( ch, "You gain %d experience points from your success!\r\n", gain );
         }
      }
      gain_exp( ch, gain, skill_table[sn]->guild );
   }
}


void learn_from_failure( CHAR_DATA * ch, int sn )
{
}

void do_gouge( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;
   AFFECT_DATA af;
   short dam;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && !ch->pcdata->learned[gsn_gouge] )
   {
      send_to_char( "You do not yet know of this skill.\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You can't get close enough while mounted.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   percent = number_percent(  ) - ( get_curr_lck( ch ) - 13 );

   if( IS_NPC( ch ) || percent < ch->pcdata->learned[gsn_gouge] )
   {
      dam = number_range( 1, ch->skill_level[COMBAT_ABILITY] );
      global_retcode = damage( ch, victim, dam, gsn_gouge );
      if( global_retcode == rNONE )
      {
         if( !IS_AFFECTED( victim, AFF_BLIND ) )
         {
            af.type = gsn_blindness;
            af.location = APPLY_HITROLL;
            af.modifier = -6;
            af.duration = 3 + ( ch->skill_level[COMBAT_ABILITY] / 20 );
            af.bitvector = meb( AFF_BLIND );
            affect_to_char( victim, &af );
            act( AT_SKILL, "You can't see a thing!", victim, NULL, NULL, TO_CHAR );
         }
         WAIT_STATE( ch, PULSE_VIOLENCE );
         WAIT_STATE( victim, PULSE_VIOLENCE );
         /*
          * Taken out by request - put back in by Thoric
          * * This is how it was designed.  You'd be a tad stunned
          * * if someone gouged you in the eye.
          */
      }
      else if( global_retcode == rVICT_DIED )
      {
         act( AT_BLOOD, "Your fingers plunge into your victim's brain, causing immediate death!", ch, NULL, NULL, TO_CHAR );
      }
      if( global_retcode != rCHAR_DIED && global_retcode != rBOTH_DIED )
         learn_from_success( ch, gsn_gouge );
   }
   else
   {
      WAIT_STATE( ch, skill_table[gsn_gouge]->beats );
      global_retcode = damage( ch, victim, 0, gsn_gouge );
      learn_from_failure( ch, gsn_gouge );
   }

   return;
}

void do_detrap( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   OBJ_DATA *obj;
   OBJ_DATA *trap;
   int percent;
   bool found = FALSE;

   switch ( ch->substate )
   {
      default:
         if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
         {
            send_to_char( "You can't concentrate enough for that.\r\n", ch );
            return;
         }
         argument = one_argument( argument, arg );
         if( !IS_NPC( ch ) && !ch->pcdata->learned[gsn_detrap] )
         {
            send_to_char( "You do not yet know of this skill.\r\n", ch );
            return;
         }
         if( arg[0] == '\0' )
         {
            send_to_char( "Detrap what?\r\n", ch );
            return;
         }
         if( ms_find_obj( ch ) )
            return;
         found = FALSE;
         if( ch->mount )
         {
            send_to_char( "You can't do that while mounted.\r\n", ch );
            return;
         }
         if( !ch->in_room->first_content )
         {
            send_to_char( "You can't find that here.\r\n", ch );
            return;
         }
         for( obj = ch->in_room->first_content; obj; obj = obj->next_content )
         {
            if( can_see_obj( ch, obj ) && nifty_is_name( arg, obj->name ) )
            {
               found = TRUE;
               break;
            }
         }
         if( !found )
         {
            send_to_char( "You can't find that here.\r\n", ch );
            return;
         }
         act( AT_ACTION, "You carefully begin your attempt to remove a trap from $p...", ch, obj, NULL, TO_CHAR );
         act( AT_ACTION, "$n carefully attempts to remove a trap from $p...", ch, obj, NULL, TO_ROOM );
         ch->dest_buf = str_dup( obj->name );
         add_timer( ch, TIMER_DO_FUN, 3, do_detrap, 1 );
/*	    WAIT_STATE( ch, skill_table[gsn_detrap]->beats ); */
         return;
      case 1:
         if( !ch->dest_buf )
         {
            send_to_char( "Your detrapping was interrupted!\r\n", ch );
            bug( "do_detrap: ch->dest_buf NULL!", 0 );
            return;
         }
         strcpy( arg, ( const char* ) ch->dest_buf );
         DISPOSE( ch->dest_buf );
         ch->dest_buf = NULL;
         ch->substate = SUB_NONE;
         break;
      case SUB_TIMER_DO_ABORT:
         DISPOSE( ch->dest_buf );
         ch->substate = SUB_NONE;
         send_to_char( "You carefully stop what you were doing.\r\n", ch );
         return;
   }

   if( !ch->in_room->first_content )
   {
      send_to_char( "You can't find that here.\r\n", ch );
      return;
   }
   for( obj = ch->in_room->first_content; obj; obj = obj->next_content )
   {
      if( can_see_obj( ch, obj ) && nifty_is_name( arg, obj->name ) )
      {
         found = TRUE;
         break;
      }
   }
   if( !found )
   {
      send_to_char( "You can't find that here.\r\n", ch );
      return;
   }
   if( ( trap = get_trap( obj ) ) == NULL )
   {
      send_to_char( "You find no trap on that.\r\n", ch );
      return;
   }

   percent = number_percent(  ) - ( ch->skill_level[SMUGGLING_ABILITY] / 20 ) - ( get_curr_lck( ch ) - 16 );

   separate_obj( obj );
   if( !IS_NPC( ch ) || percent > ch->pcdata->learned[gsn_detrap] )
   {
      send_to_char( "Ooops!\r\n", ch );
      spring_trap( ch, trap );
      learn_from_failure( ch, gsn_detrap );
      return;
   }

   extract_obj( trap );

   send_to_char( "You successfully remove a trap.\r\n", ch );
   learn_from_success( ch, gsn_detrap );
   return;
}

void do_dig( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   OBJ_DATA *obj;
   OBJ_DATA *startobj;
   bool found, shovel;
   EXIT_DATA *pexit;

   switch ( ch->substate )
   {
      default:
         if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
         {
            send_to_char( "You can't concentrate enough for that.\r\n", ch );
            return;
         }
         if( ch->mount )
         {
            send_to_char( "You can't do that while mounted.\r\n", ch );
            return;
         }
         one_argument( argument, arg );
         if( arg[0] != '\0' )
         {
            if( ( pexit = find_door( ch, arg, TRUE ) ) == NULL && get_dir( arg ) == -1 )
            {
               send_to_char( "What direction is that?\r\n", ch );
               return;
            }
            if( pexit )
            {
               if( !IS_SET( pexit->exit_info, EX_DIG ) && !IS_SET( pexit->exit_info, EX_CLOSED ) )
               {
                  send_to_char( "There is no need to dig out that exit.\r\n", ch );
                  return;
               }
            }
         }
         else
         {
            switch ( ch->in_room->sector_type )
            {
               case SECT_CITY:
               case SECT_INSIDE:
                  send_to_char( "The floor is too hard to dig through.\r\n", ch );
                  return;
               case SECT_WATER_SWIM:
               case SECT_WATER_NOSWIM:
               case SECT_UNDERWATER:
                  send_to_char( "You cannot dig here.\r\n", ch );
                  return;
               case SECT_AIR:
                  send_to_char( "What?  In the air?!\r\n", ch );
                  return;
            }
         }
         add_timer( ch, TIMER_DO_FUN, UMIN( skill_table[gsn_dig]->beats / 10, 3 ), do_dig, 1 );
         ch->dest_buf = str_dup( arg );
         send_to_char( "You begin digging...\r\n", ch );
         act( AT_PLAIN, "$n begins digging...", ch, NULL, NULL, TO_ROOM );
         return;

      case 1:
         if( !ch->dest_buf )
         {
            send_to_char( "Your digging was interrupted!\r\n", ch );
            act( AT_PLAIN, "$n's digging was interrupted!", ch, NULL, NULL, TO_ROOM );
            bug( "do_dig: dest_buf NULL", 0 );
            return;
         }
         strcpy( arg, ( const char* ) ch->dest_buf );
         DISPOSE( ch->dest_buf );
         break;

      case SUB_TIMER_DO_ABORT:
         DISPOSE( ch->dest_buf );
         ch->substate = SUB_NONE;
         send_to_char( "You stop digging...\r\n", ch );
         act( AT_PLAIN, "$n stops digging...", ch, NULL, NULL, TO_ROOM );
         return;
   }

   ch->substate = SUB_NONE;

   /*
    * not having a shovel makes it harder to succeed 
    */
   shovel = FALSE;
   for( obj = ch->first_carrying; obj; obj = obj->next_content )
      if( obj->item_type == ITEM_SHOVEL )
      {
         shovel = TRUE;
         break;
      }

   /*
    * dig out an EX_DIG exit... 
    */
   if( arg[0] != '\0' )
   {
      if( ( pexit = find_door( ch, arg, TRUE ) ) != NULL
          && IS_SET( pexit->exit_info, EX_DIG ) && IS_SET( pexit->exit_info, EX_CLOSED ) )
      {
         /*
          * 4 times harder to dig open a passage without a shovel 
          */
         if( ( number_percent(  ) * ( shovel ? 1 : 4 ) ) < ( IS_NPC( ch ) ? 80 : ch->pcdata->learned[gsn_dig] ) )
         {
            REMOVE_BIT( pexit->exit_info, EX_CLOSED );
            send_to_char( "You dig open a passageway!\r\n", ch );
            act( AT_PLAIN, "$n digs open a passageway!", ch, NULL, NULL, TO_ROOM );
            learn_from_success( ch, gsn_dig );
            return;
         }
      }
      learn_from_failure( ch, gsn_dig );
      send_to_char( "Your dig did not discover any exit...\r\n", ch );
      act( AT_PLAIN, "$n's dig did not discover any exit...", ch, NULL, NULL, TO_ROOM );
      return;
   }

   startobj = ch->in_room->first_content;
   found = FALSE;

   for( obj = startobj; obj; obj = obj->next_content )
   {
      /*
       * twice as hard to find something without a shovel 
       */
      if( IS_OBJ_STAT( obj, ITEM_BURRIED )
          && ( number_percent(  ) * ( shovel ? 1 : 2 ) ) < ( IS_NPC( ch ) ? 80 : ch->pcdata->learned[gsn_dig] ) )
      {
         found = TRUE;
         break;
      }
   }

   if( !found )
   {
      send_to_char( "Your dig uncovered nothing.\r\n", ch );
      act( AT_PLAIN, "$n's dig uncovered nothing.", ch, NULL, NULL, TO_ROOM );
      learn_from_failure( ch, gsn_dig );
      return;
   }

   separate_obj( obj );
   REMOVE_BIT( obj->extra_flags, ITEM_BURRIED );
   act( AT_SKILL, "Your dig uncovered $p!", ch, obj, NULL, TO_CHAR );
   act( AT_SKILL, "$n's dig uncovered $p!", ch, obj, NULL, TO_ROOM );
   learn_from_success( ch, gsn_dig );

   return;
}


void do_search( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   OBJ_DATA *obj = NULL;
   OBJ_DATA *container;
   OBJ_DATA *startobj;
   int percent, door;
   bool found, room;

   door = -1;
   switch ( ch->substate )
   {
      default:
         if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
         {
            send_to_char( "You can't concentrate enough for that.\r\n", ch );
            return;
         }
         if( ch->mount )
         {
            send_to_char( "You can't do that while mounted.\r\n", ch );
            return;
         }
         argument = one_argument( argument, arg );
         if( arg[0] != '\0' && ( door = get_door( arg ) ) == -1 )
         {
            container = get_obj_here( ch, arg );
            if( !container )
            {
               send_to_char( "You can't find that here.\r\n", ch );
               return;
            }
            if( container->item_type != ITEM_CONTAINER )
            {
               send_to_char( "You can't search in that!\r\n", ch );
               return;
            }
            if( IS_SET( container->value[1], CONT_CLOSED ) )
            {
               send_to_char( "It is closed.\r\n", ch );
               return;
            }
         }
         add_timer( ch, TIMER_DO_FUN, UMIN( skill_table[gsn_search]->beats / 10, 3 ), do_search, 1 );
         send_to_char( "You begin your search...\r\n", ch );
         ch->dest_buf = str_dup( arg );
         return;

      case 1:
         if( !ch->dest_buf )
         {
            send_to_char( "Your search was interrupted!\r\n", ch );
            bug( "do_search: dest_buf NULL", 0 );
            return;
         }
         strcpy( arg, ( const char* ) ch->dest_buf );
         DISPOSE( ch->dest_buf );
         break;
      case SUB_TIMER_DO_ABORT:
         DISPOSE( ch->dest_buf );
         ch->substate = SUB_NONE;
         send_to_char( "You stop your search...\r\n", ch );
         return;
   }
   ch->substate = SUB_NONE;
   if( arg[0] == '\0' )
   {
      room = TRUE;
      startobj = ch->in_room->first_content;
   }
   else
   {
      if( ( door = get_door( arg ) ) != -1 )
         startobj = NULL;
      else
      {
         container = get_obj_here( ch, arg );
         if( !container )
         {
            send_to_char( "You can't find that here.\r\n", ch );
            return;
         }
         startobj = container->first_content;
      }
   }

   found = FALSE;

   if( ( !startobj && door == -1 ) || IS_NPC( ch ) )
   {
      send_to_char( "You find nothing.\r\n", ch );
      learn_from_failure( ch, gsn_search );
      return;
   }

   percent = number_percent(  );

   if( door != -1 )
   {
      EXIT_DATA *pexit;

      if( ( pexit = get_exit( ch->in_room, door ) ) != NULL
          && IS_SET( pexit->exit_info, EX_SECRET )
          && IS_SET( pexit->exit_info, EX_xSEARCHABLE )
          && percent < ( IS_NPC( ch ) ? 80 : ch->pcdata->learned[gsn_search] ) )
      {
         act( AT_SKILL, "Your search reveals the $d!", ch, NULL, pexit->keyword, TO_CHAR );
         act( AT_SKILL, "$n finds the $d!", ch, NULL, pexit->keyword, TO_ROOM );
         REMOVE_BIT( pexit->exit_info, EX_SECRET );
         learn_from_success( ch, gsn_search );
         return;
      }
   }
   else
      for( obj = startobj; obj; obj = obj->next_content )
      {
         if( IS_OBJ_STAT( obj, ITEM_HIDDEN ) && percent < ch->pcdata->learned[gsn_search] )
         {
            found = TRUE;
            break;
         }
      }

   if( !found )
   {
      send_to_char( "You find nothing.\r\n", ch );
      learn_from_failure( ch, gsn_search );
      return;
   }

   separate_obj( obj );
   REMOVE_BIT( obj->extra_flags, ITEM_HIDDEN );
   act( AT_SKILL, "Your search reveals $p!", ch, obj, NULL, TO_CHAR );
   act( AT_SKILL, "$n finds $p!", ch, obj, NULL, TO_ROOM );
   learn_from_success( ch, gsn_search );
   return;
}


void do_steal( CHAR_DATA * ch, const char *argument )
{
   char buf[MAX_STRING_LENGTH];
   char arg1[MAX_INPUT_LENGTH];
   char arg2[MAX_INPUT_LENGTH];
   CHAR_DATA *victim, *mst;
   OBJ_DATA *obj, *obj_next;
   int percent, xp;

   argument = one_argument( argument, arg1 );
   argument = one_argument( argument, arg2 );

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   if( arg1[0] == '\0' || arg2[0] == '\0' )
   {
      send_to_char( "Steal what from whom?\r\n", ch );
      return;
   }

   if( ms_find_obj( ch ) )
      return;

   if( ( victim = get_char_room( ch, arg2 ) ) == NULL )
   {
      send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( victim == ch )
   {
      send_to_char( "That's pointless.\r\n", ch );
      return;
   }

   if( IS_SET( ch->in_room->room_flags, ROOM_SAFE ) )
   {
      set_char_color( AT_MAGIC, ch );
      send_to_char( "This isn't a good place to do that.\r\n", ch );
      return;
   }

   if( check_illegal_psteal( ch, victim ) )
   {
      send_to_char( "You can't steal from that player.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_steal]->beats );
   percent = number_percent(  ) + ( IS_AWAKE( victim ) ? 10 : -50 )
      - ( get_curr_lck( ch ) - 15 ) + ( get_curr_lck( victim ) - 13 ) + times_killed( ch, victim ) * 7;

   if( victim->position == POS_FIGHTING || percent > ( IS_NPC( ch ) ? 90 : ch->pcdata->learned[gsn_steal] ) )
   {
      /*
       * Failure.
       */
      send_to_char( "Oops...\r\n", ch );
      act( AT_ACTION, "$n tried to steal from you!\r\n", ch, NULL, victim, TO_VICT );
      act( AT_ACTION, "$n tried to steal from $N.\r\n", ch, NULL, victim, TO_NOTVICT );

      sprintf( buf, "%s is a bloody thief!", ch->name );
      do_yell( victim, buf );

      learn_from_failure( ch, gsn_steal );
      if( !IS_NPC( ch ) )
      {
         if( legal_loot( ch, victim ) )
         {
            global_retcode = multi_hit( victim, ch, TYPE_UNDEFINED );
         }
         else
         {
            /*
             * log_string( buf ); 
             */
            if( IS_NPC( ch ) )
            {
               if( ( mst = ch->master ) == NULL )
                  return;
            }
            else
               mst = ch;
            if( IS_NPC( mst ) )
               return;

         }
      }

      return;
   }

   if( IS_NPC( victim ) )
      add_kill( ch, victim ); /* makes it harder to steal from same char */

   if( !str_cmp( arg1, "credits" ) || !str_cmp( arg1, "credit" ) || !str_cmp( arg1, "money" ) )
   {
      int amount;

      amount = ( int )( victim->gold * number_range( 1, 10 ) / 100 );
      if( amount <= 0 )
      {
         send_to_char( "You couldn't get any credits.\r\n", ch );
         learn_from_failure( ch, gsn_steal );
         return;
      }

      ch->gold += amount;
      victim->gold -= amount;
      ch_printf( ch, "Aha!  You got %d credits.\r\n", amount );
      learn_from_success( ch, gsn_steal );
      if( IS_NPC( victim ) );
      {
         xp =
            UMIN( amount * 10,
                  ( exp_level( ch->skill_level[SMUGGLING_ABILITY] + 1 ) -
                    exp_level( ch->skill_level[SMUGGLING_ABILITY] ) ) / 35 );
         xp = UMIN( xp, xp_compute( ch, victim ) );
         gain_exp( ch, xp, SMUGGLING_ABILITY );
         ch_printf( ch, "&WYou gain %ld smuggling experience!\r\n", xp );
      }
      return;
   }

   if( ( obj = get_obj_carry( victim, arg1 ) ) == NULL )
   {
      if( victim->position <= POS_SLEEPING )
      {
         if( ( obj = get_obj_wear( victim, arg1 ) ) != NULL )
         {
            if( ( obj_next = get_eq_char( victim, obj->wear_loc ) ) != obj )
            {
               ch_printf( ch, "They are wearing %s on top of %s.\r\n", obj_next->short_descr, obj->short_descr );
               send_to_char( "You'll have to steal that first.\r\n", ch );
               learn_from_failure( ch, gsn_steal );
               return;
            }
            else
               unequip_char( victim, obj );
         }
      }

      send_to_char( "You can't seem to find it.\r\n", ch );
      learn_from_failure( ch, gsn_steal );
      return;
   }

   if( !can_drop_obj( ch, obj ) || IS_OBJ_STAT( obj, ITEM_INVENTORY ) || IS_OBJ_STAT( obj, ITEM_PROTOTYPE ) )
   {
      send_to_char( "You can't manage to pry it away.\r\n", ch );
      learn_from_failure( ch, gsn_steal );
      return;
   }

   if( ch->carry_number + ( get_obj_number( obj ) / obj->count ) > can_carry_n( ch ) )
   {
      send_to_char( "You have your hands full.\r\n", ch );
      learn_from_failure( ch, gsn_steal );
      return;
   }

   if( ch->carry_weight + ( get_obj_weight( obj ) / obj->count ) > can_carry_w( ch ) )
   {
      send_to_char( "You can't carry that much weight.\r\n", ch );
      learn_from_failure( ch, gsn_steal );
      return;
   }

   send_to_char( "Ok.\r\n", ch );
   learn_from_success( ch, gsn_steal );
   if( IS_NPC( victim ) );
   {
      xp =
         UMIN( obj->cost * 10,
               ( exp_level( ch->skill_level[SMUGGLING_ABILITY] + 1 ) -
                 exp_level( ch->skill_level[SMUGGLING_ABILITY] ) ) / 10 );
      xp = UMIN( xp, xp_compute( ch, victim ) );
      gain_exp( ch, xp, SMUGGLING_ABILITY );
      ch_printf( ch, "&WYou gain %ld smuggling experience!\r\n", xp );
   }
   separate_obj( obj );
   obj_from_char( obj );
   obj_to_char( obj, ch );

   return;
}


void do_backstab( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   CHAR_DATA *victim;
   OBJ_DATA *obj;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't do that right now.\r\n", ch );
      return;
   }

   one_argument( argument, arg );

   if( ch->mount )
   {
      send_to_char( "You can't get close enough while mounted.\r\n", ch );
      return;
   }

   if( arg[0] == '\0' )
   {
      send_to_char( "Backstab whom?\r\n", ch );
      return;
   }

   if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
      send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( victim == ch )
   {
      send_to_char( "How can you sneak up on yourself?\r\n", ch );
      return;
   }

   if( is_safe( ch, victim ) )
      return;

   /*
    * Added stabbing weapon. -Narn 
    */
   if( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL || ( obj->value[3] != WEAPON_VIBRO_BLADE ) )
   {
      send_to_char( "You need to wield a stabbing weapon.\r\n", ch );
      return;
   }

   if( victim->fighting )
   {
      send_to_char( "You can't backstab someone who is in combat.\r\n", ch );
      return;
   }

   /*
    * Can backstab a char even if it's hurt as long as it's sleeping. -Narn 
    */
   if( victim->hit < victim->max_hit && IS_AWAKE( victim ) )
   {
      act( AT_PLAIN, "$N is hurt and suspicious ... you can't sneak up.", ch, NULL, victim, TO_CHAR );
      return;
   }

   percent = number_percent(  ) - ( get_curr_lck( ch ) - 14 ) + ( get_curr_lck( victim ) - 13 );

   WAIT_STATE( ch, skill_table[gsn_backstab]->beats );
   if( !IS_AWAKE( victim ) || IS_NPC( ch ) || percent < ch->pcdata->learned[gsn_backstab] )
   {
      learn_from_success( ch, gsn_backstab );
      global_retcode = multi_hit( ch, victim, gsn_backstab );

   }
   else
   {
      learn_from_failure( ch, gsn_backstab );
      global_retcode = damage( ch, victim, 0, gsn_backstab );
   }
   return;
}


void do_rescue( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   CHAR_DATA *victim;
   CHAR_DATA *fch;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   one_argument( argument, arg );
   if( arg[0] == '\0' )
   {
      send_to_char( "Rescue whom?\r\n", ch );
      return;
   }

   if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
      send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( victim == ch )
   {
      send_to_char( "You try and rescue yourself, but fail miserably.\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && IS_NPC( victim ) )
   {
      send_to_char( "Doesn't need your help!\r\n", ch );
      return;
   }

   if( ( fch = who_fighting( victim ) ) == NULL )
   {
      send_to_char( "They are not fighting right now.\r\n", ch );
      return;
   }

   if( who_fighting( victim ) == ch )
   {
      send_to_char( "One would imagine THEY don't need your help.\r\n", ch );
      return;
   }

   ch->alignment = ch->alignment + 5;
   ch->alignment = URANGE( -1000, ch->alignment, 1000 );

   percent = number_percent(  ) - ( get_curr_lck( ch ) - 14 ) - ( get_curr_lck( victim ) - 16 );

   WAIT_STATE( ch, skill_table[gsn_rescue]->beats );
   if( !IS_NPC( ch ) && percent > ch->pcdata->learned[gsn_rescue] )
   {
      send_to_char( "You fail the rescue.\r\n", ch );
      act( AT_SKILL, "$n tries to rescue you!", ch, NULL, victim, TO_VICT );
      act( AT_SKILL, "$n tries to rescue $N!", ch, NULL, victim, TO_NOTVICT );
      learn_from_failure( ch, gsn_rescue );
      return;
   }

   act( AT_SKILL, "You rescue $N!", ch, NULL, victim, TO_CHAR );
   act( AT_SKILL, "$n rescues you!", ch, NULL, victim, TO_VICT );
   act( AT_SKILL, "$n moves in front of $N!", ch, NULL, victim, TO_NOTVICT );

   ch->alignment = ch->alignment + 50;
   ch->alignment = URANGE( -1000, ch->alignment, 1000 );

   learn_from_success( ch, gsn_rescue );
   stop_fighting( fch, FALSE );
   stop_fighting( victim, FALSE );
   if( ch->fighting )
      stop_fighting( ch, FALSE );

   /*
    * check_killer( ch, fch ); 
    */
   set_fighting( ch, fch );
   set_fighting( fch, ch );
   return;
}

void do_kick( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_kick]->beats );
   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_kick] )
   {
      learn_from_success( ch, gsn_kick );
      global_retcode = damage( ch, victim, number_range( 1, ch->skill_level[COMBAT_ABILITY] ), gsn_kick );
   }
   else
   {
      learn_from_failure( ch, gsn_kick );
      global_retcode = damage( ch, victim, 0, gsn_kick );
   }
   return;
}

void do_punch( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_punch] <= 0 )
   {
      send_to_char( "Your mind races as you realize you have no idea how to do that.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_punch]->beats );
   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_punch] )
   {
      learn_from_success( ch, gsn_punch );
      global_retcode = damage( ch, victim, number_range( 1, ch->skill_level[COMBAT_ABILITY] ), gsn_punch );
   }
   else
   {
      learn_from_failure( ch, gsn_punch );
      global_retcode = damage( ch, victim, 0, gsn_punch );
   }
   return;
}


void do_bite( CHAR_DATA * ch, const char *argument )
{
}


void do_claw( CHAR_DATA * ch, const char *argument )
{
}


void do_sting( CHAR_DATA * ch, const char *argument )
{
}


void do_tail( CHAR_DATA * ch, const char *argument )
{
}


void do_bash( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;
   int schance;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_bash] <= 0 )
   {
      send_to_char( "Your mind races as you realize you have no idea how to do that.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   schance = ( ( ( get_curr_dex( victim ) + get_curr_str( victim ) )
                 - ( get_curr_dex( ch ) + get_curr_str( ch ) ) ) * 10 ) + 10;
   if( !IS_NPC( ch ) && !IS_NPC( victim ) )
      schance += 25;
   if( victim->fighting && victim->fighting->who != ch )
      schance += 19;
   WAIT_STATE( ch, skill_table[gsn_bash]->beats );
   if( IS_NPC( ch ) || ( number_percent(  ) + schance ) < ch->pcdata->learned[gsn_bash] )
   {
      learn_from_success( ch, gsn_bash );
      /*
       * do not change anything here!  -Thoric 
       */
      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      WAIT_STATE( victim, 2 * PULSE_VIOLENCE );
      victim->position = POS_SITTING;
      global_retcode = damage( ch, victim, number_range( 1, ch->skill_level[COMBAT_ABILITY] ), gsn_bash );
   }
   else
   {
      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      learn_from_failure( ch, gsn_bash );
      global_retcode = damage( ch, victim, 0, gsn_bash );
   }
   return;
}


void do_stun( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;
   AFFECT_DATA af;
   int schance;
   bool fail;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_stun] <= 0 )
   {
      send_to_char( "Your mind races as you realize you have no idea how to do that.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   if( ch->move < 16 )
   {
      set_char_color( AT_SKILL, ch );
      send_to_char( "You are far too tired to do that.\r\n", ch );
      return;  /* missing return fixed March 11/96 */
   }

   WAIT_STATE( ch, skill_table[gsn_stun]->beats );
   fail = FALSE;
   schance = ris_save( victim, ch->skill_level[COMBAT_ABILITY], RIS_PARALYSIS );
   if( schance == 1000 )
      fail = TRUE;
   else
      fail = saves_para_petri( schance, victim );

   schance = ( ( ( get_curr_dex( victim ) + get_curr_str( victim ) )
                 - ( get_curr_dex( ch ) + get_curr_str( ch ) ) ) * 10 ) + 10;
   /*
    * harder for player to stun another player 
    */
   if( !IS_NPC( ch ) && !IS_NPC( victim ) )
      schance += sysdata.stun_plr_vs_plr;
   else
      schance += sysdata.stun_regular;
   if( !fail && ( IS_NPC( ch ) || ( number_percent(  ) + schance ) < ch->pcdata->learned[gsn_stun] ) )
   {
      learn_from_success( ch, gsn_stun );
      /*
       * DO *NOT* CHANGE!    -Thoric    
       */
      ch->move -= 15;
      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      WAIT_STATE( victim, PULSE_VIOLENCE );
      act( AT_SKILL, "$N smashes into you, leaving you stunned!", victim, NULL, ch, TO_CHAR );
      act( AT_SKILL, "You smash into $N, leaving $M stunned!", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n smashes into $N, leaving $M stunned!", ch, NULL, victim, TO_NOTVICT );
      if( !IS_AFFECTED( victim, AFF_PARALYSIS ) )
      {
         af.type = gsn_stun;
         af.location = APPLY_EVASION;
         af.modifier = 20;
         af.duration = 3;
         af.bitvector = meb( AFF_PARALYSIS );
         affect_to_char( victim, &af );
         update_pos( victim );
      }
   }
   else
   {
      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      ch->move -= 5;
      learn_from_failure( ch, gsn_stun );
      act( AT_SKILL, "$N charges at you screaming, but you dodge out of the way.", victim, NULL, ch, TO_CHAR );
      act( AT_SKILL, "Your attempt to stun $N leaves you racing past $E as $e laughs.", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n charges screaming at $N, but keeps going right on past.", ch, NULL, victim, TO_NOTVICT );
   }
   return;
}


void do_feed( CHAR_DATA * ch, const char *argument )
{
   send_to_char( "It is not of your nature to feed on living creatures.\r\n", ch );
   return;
}


/*
 * Disarm a creature.
 * Caller must check for successful attack.
 * Check for loyalty flag (weapon disarms to inventory) for pkillers -Blodkai
 */
void disarm( CHAR_DATA * ch, CHAR_DATA * victim )
{
   OBJ_DATA *obj, *tmpobj;

   if( ( obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL )
      return;

   if( ( tmpobj = get_eq_char( victim, WEAR_DUAL_WIELD ) ) != NULL && number_bits( 1 ) == 0 )
      obj = tmpobj;

   if( get_eq_char( ch, WEAR_WIELD ) == NULL && number_bits( 1 ) == 0 )
   {
      learn_from_failure( ch, gsn_disarm );
      return;
   }

   if( IS_NPC( ch ) && !can_see_obj( ch, obj ) && number_bits( 1 ) == 0 )
   {
      learn_from_failure( ch, gsn_disarm );
      return;
   }

   if( check_grip( ch, victim ) )
   {
      learn_from_failure( ch, gsn_disarm );
      return;
   }

   act( AT_SKILL, "$n DISARMS you!", ch, NULL, victim, TO_VICT );
   act( AT_SKILL, "You disarm $N!", ch, NULL, victim, TO_CHAR );
   act( AT_SKILL, "$n disarms $N!", ch, NULL, victim, TO_NOTVICT );
   learn_from_success( ch, gsn_disarm );

   if( obj == get_eq_char( victim, WEAR_WIELD ) && ( tmpobj = get_eq_char( victim, WEAR_DUAL_WIELD ) ) != NULL )
      tmpobj->wear_loc = WEAR_WIELD;

   obj_from_char( obj );
   obj_to_room( obj, victim->in_room );

   return;
}


void do_disarm( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;
   OBJ_DATA *obj;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_disarm] <= 0 )
   {
      send_to_char( "You don't know how to disarm opponents.\r\n", ch );
      return;
   }

   if( get_eq_char( ch, WEAR_WIELD ) == NULL )
   {
      send_to_char( "You must wield a weapon to disarm.\r\n", ch );
      return;
   }

   if( ( victim = who_fighting( ch ) ) == NULL )
   {
      send_to_char( "You aren't fighting anyone.\r\n", ch );
      return;
   }

   if( ( obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL )
   {
      send_to_char( "Your opponent is not wielding a weapon.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_disarm]->beats );
   percent = number_percent(  ) + victim->skill_level[COMBAT_ABILITY] - ch->skill_level[COMBAT_ABILITY]
      - ( get_curr_lck( ch ) - 15 ) + ( get_curr_lck( victim ) - 15 );
   if( !can_see_obj( ch, obj ) )
      percent += 10;
   if( IS_NPC( ch ) || percent < ch->pcdata->learned[gsn_disarm] * 2 / 3 )
      disarm( ch, victim );
   else
   {
      send_to_char( "You failed.\r\n", ch );
      learn_from_failure( ch, gsn_disarm );
   }
   return;
}


/*
 * Trip a creature.
 * Caller must check for successful attack.
 */
void trip( CHAR_DATA * ch, CHAR_DATA * victim )
{
   if( IS_AFFECTED( victim, AFF_FLYING ) || IS_AFFECTED( victim, AFF_FLOATING ) )
      return;
   if( victim->mount )
   {
      if( IS_AFFECTED( victim->mount, AFF_FLYING ) || IS_AFFECTED( victim->mount, AFF_FLOATING ) )
         return;
      act( AT_SKILL, "$n trips your mount and you fall off!", ch, NULL, victim, TO_VICT );
      act( AT_SKILL, "You trip $N's mount and $N falls off!", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n trips $N's mount and $N falls off!", ch, NULL, victim, TO_NOTVICT );
      REMOVE_BIT( victim->mount->act, ACT_MOUNTED );
      victim->mount = NULL;
      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      WAIT_STATE( victim, 2 * PULSE_VIOLENCE );
      victim->position = POS_RESTING;
      return;
   }
   if( victim->wait == 0 )
   {
      act( AT_SKILL, "$n trips you and you go down!", ch, NULL, victim, TO_VICT );
      act( AT_SKILL, "You trip $N and $N goes down!", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n trips $N and $N goes down!", ch, NULL, victim, TO_NOTVICT );

      WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
      WAIT_STATE( victim, 2 * PULSE_VIOLENCE );
      victim->position = POS_RESTING;
   }

   return;
}


void do_pick( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   CHAR_DATA *gch;
   OBJ_DATA *obj;
   EXIT_DATA *pexit;
   SHIP_DATA *ship;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   one_argument( argument, arg );

   if( arg[0] == '\0' )
   {
      send_to_char( "Pick what?\r\n", ch );
      return;
   }

   if( ms_find_obj( ch ) )
      return;

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_pick_lock]->beats );

   /*
    * look for guards 
    */
   for( gch = ch->in_room->first_person; gch; gch = gch->next_in_room )
   {
      if( IS_NPC( gch ) && IS_AWAKE( gch ) && ch->skill_level[SMUGGLING_ABILITY] < gch->top_level )
      {
         act( AT_PLAIN, "$N is standing too close to the lock.", ch, NULL, gch, TO_CHAR );
         return;
      }
   }


   if( ( pexit = find_door( ch, arg, TRUE ) ) != NULL )
   {
      /*
       * 'pick door' 
       */
      /*
       * ROOM_INDEX_DATA *to_room; 
       *//*
       * Unused 
       */
      EXIT_DATA *pexit_rev;

      if( !IS_SET( pexit->exit_info, EX_CLOSED ) )
      {
         send_to_char( "It's not closed.\r\n", ch );
         return;
      }
      if( pexit->key < 0 )
      {
         send_to_char( "It can't be picked.\r\n", ch );
         return;
      }
      if( !IS_SET( pexit->exit_info, EX_LOCKED ) )
      {
         send_to_char( "It's already unlocked.\r\n", ch );
         return;
      }
      if( IS_SET( pexit->exit_info, EX_PICKPROOF ) )
      {
         send_to_char( "You failed.\r\n", ch );
         learn_from_failure( ch, gsn_pick_lock );
         check_room_for_traps( ch, TRAP_PICK | trap_door[pexit->vdir] );
         return;
      }

      if( !IS_NPC( ch ) && number_percent(  ) > ch->pcdata->learned[gsn_pick_lock] )
      {
         send_to_char( "You failed.\r\n", ch );
         learn_from_failure( ch, gsn_pick_lock );
         return;
      }

      REMOVE_BIT( pexit->exit_info, EX_LOCKED );
      send_to_char( "*Click*\r\n", ch );
      act( AT_ACTION, "$n picks the $d.", ch, NULL, pexit->keyword, TO_ROOM );
      learn_from_success( ch, gsn_pick_lock );
      /*
       * pick the other side 
       */
      if( ( pexit_rev = pexit->rexit ) != NULL && pexit_rev->to_room == ch->in_room )
      {
         REMOVE_BIT( pexit_rev->exit_info, EX_LOCKED );
      }
      check_room_for_traps( ch, TRAP_PICK | trap_door[pexit->vdir] );
      return;
   }

   if( ( obj = get_obj_here( ch, arg ) ) != NULL )
   {
      if( obj->item_type != ITEM_CONTAINER )
      {
         send_to_char( "You can't pick that.\r\n", ch );
         return;
      }
      if( !IS_SET( obj->value[1], CONT_CLOSED ) )
      {
         send_to_char( "It's not closed.\r\n", ch );
         return;
      }
      if( obj->value[2] < 0 )
      {
         send_to_char( "It can't be unlocked.\r\n", ch );
         return;
      }
      if( !IS_SET( obj->value[1], CONT_LOCKED ) )
      {
         send_to_char( "It's already unlocked.\r\n", ch );
         return;
      }
      if( IS_SET( obj->value[1], CONT_PICKPROOF ) )
      {
         send_to_char( "You failed.\r\n", ch );
         learn_from_failure( ch, gsn_pick_lock );
         check_for_trap( ch, obj, TRAP_PICK );
         return;
      }

      if( !IS_NPC( ch ) && number_percent(  ) > ch->pcdata->learned[gsn_pick_lock] )
      {
         send_to_char( "You failed.\r\n", ch );
         learn_from_failure( ch, gsn_pick_lock );
         return;
      }

      separate_obj( obj );
      REMOVE_BIT( obj->value[1], CONT_LOCKED );
      send_to_char( "*Click*\r\n", ch );
      act( AT_ACTION, "$n picks $p.", ch, obj, NULL, TO_ROOM );
      learn_from_success( ch, gsn_pick_lock );
      check_for_trap( ch, obj, TRAP_PICK );
      return;
   }

   if( ( ship = ship_in_room( ch->in_room, arg ) ) != NULL )
   {
      char buf[MAX_STRING_LENGTH];

      if( check_pilot( ch, ship ) )
      {
         send_to_char( "&RWhat would be the point of that!\r\n", ch );
         return;
      }

      if( ship->shipstate != SHIP_DOCKED && ship->shipstate != SHIP_DISABLED )
      {
         send_to_char( "&RThat ship has already started to launch", ch );
         return;
      }

      WAIT_STATE( ch, skill_table[gsn_pickshiplock]->beats );

      if( IS_NPC( ch ) || !ch->pcdata || number_percent(  ) > ch->pcdata->learned[gsn_pickshiplock] )
      {
         send_to_char( "You failed.\r\n", ch );
         sprintf( buf, "[ALARM] %s attempting to pick %s.", ch->name, ship->name );
         echo_to_all( AT_RED, buf, 0 );
         learn_from_failure( ch, gsn_pickshiplock );
         return;
      }

      if( !ship->hatchopen )
      {
         ship->hatchopen = TRUE;
         act( AT_PLAIN, "You pick the lock and open the hatch on $T.", ch, NULL, ship->name, TO_CHAR );
         act( AT_PLAIN, "$n picks open the hatch on $T.", ch, NULL, ship->name, TO_ROOM );
         echo_to_room( AT_YELLOW, get_room_index( ship->entrance ), "The hatch opens from the outside." );
         learn_from_success( ch, gsn_pickshiplock );
      }
      return;
   }

   ch_printf( ch, "You see no %s here.\r\n", arg );
   return;
}



void do_sneak( CHAR_DATA * ch, const char *argument )
{
   AFFECT_DATA af;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   send_to_char( "You attempt to move silently.\r\n", ch );
   affect_strip( ch, gsn_sneak );

   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_sneak] )
   {
      af.type = gsn_sneak;
      af.duration = ( int )( ch->skill_level[SMUGGLING_ABILITY] * DUR_CONV );
      af.location = APPLY_NONE;
      af.modifier = 0;
      af.bitvector = meb( AFF_SNEAK );
      affect_to_char( ch, &af );
      learn_from_success( ch, gsn_sneak );
   }
   else
      learn_from_failure( ch, gsn_sneak );

   return;
}



void do_hide( CHAR_DATA * ch, const char *argument )
{
   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   send_to_char( "You attempt to hide.\r\n", ch );

   if( IS_AFFECTED( ch, AFF_HIDE ) )
      xREMOVE_BIT( ch->affected_by, AFF_HIDE );

   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_hide] )
   {
      xSET_BIT( ch->affected_by, AFF_HIDE );
      learn_from_success( ch, gsn_hide );
   }
   else
      learn_from_failure( ch, gsn_hide );
   return;
}



/*
 * Contributed by Alander.
 */
void do_visible( CHAR_DATA * ch, const char *argument )
{
   affect_strip( ch, gsn_invis );
   affect_strip( ch, gsn_mass_invis );
   affect_strip( ch, gsn_sneak );
   xREMOVE_BIT( ch->affected_by, AFF_HIDE );
   if( ch->race != RACE_DEFEL )  /* Defel has perm invis */
     xREMOVE_BIT( ch->affected_by, AFF_INVISIBLE );
   if( ch->race != RACE_NOGHRI ) /* Noghri has perm sneak */
      xREMOVE_BIT( ch->affected_by, AFF_SNEAK );
   send_to_char( "Ok.\r\n", ch );
   return;
}


void do_recall( CHAR_DATA * ch, const char *argument )
{
   ROOM_INDEX_DATA *location;
   CHAR_DATA *opponent;

   location = NULL;

   location = get_room_index( wherehome( ch ) );

   if( get_trust( ch ) < LEVEL_IMMORTAL )
   {
      AREA_DATA *pArea;

      if( !ch->pcdata || !( pArea = ch->pcdata->area ) )
      {
         send_to_char( "Only builders can recall.\r\n", ch );
         return;
      }

      if( ch->in_room->vnum < pArea->low_r_vnum || ch->in_room->vnum > pArea->hi_r_vnum )
      {
         send_to_char( "You can only recall from your assigned area.\r\n", ch );
         return;
      }
   }

   if( !location )
   {
      send_to_char( "You are completely lost.\r\n", ch );
      return;
   }

   if( ch->in_room == location )
      return;

   if( IS_SET( ch->in_room->room_flags, ROOM_NO_RECALL ) )
   {
      send_to_char( "For some strange reason... nothing happens.\r\n", ch );
      return;
   }

   if( xIS_SET( ch->affected_by, AFF_CURSE ) )
   {
      send_to_char( "You are cursed and cannot recall!\r\n", ch );
      return;
   }

   if( ( opponent = who_fighting( ch ) ) != NULL )
   {

      if( number_bits( 1 ) == 0 || ( !IS_NPC( opponent ) && number_bits( 3 ) > 1 ) )
      {
         WAIT_STATE( ch, 4 );
         ch_printf( ch, "You failed!\r\n" );
         return;
      }

      ch_printf( ch, "You recall from combat!\r\n" );
      stop_fighting( ch, TRUE );
   }

   act( AT_ACTION, "$n disappears in a swirl of the Force.", ch, NULL, NULL, TO_ROOM );
   char_from_room( ch );
   char_to_room( ch, location );
   if( ch->mount )
   {
      char_from_room( ch->mount );
      char_to_room( ch->mount, location );
   }
   act( AT_ACTION, "$n appears in a swirl of the Force.", ch, NULL, NULL, TO_ROOM );
   do_look( ch, "auto" );

   return;
}


void do_aid( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   CHAR_DATA *victim;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   one_argument( argument, arg );
   if( arg[0] == '\0' )
   {
      send_to_char( "Aid whom?\r\n", ch );
      return;
   }

   if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
      send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You can't do that while mounted.\r\n", ch );
      return;
   }

   if( victim == ch )
   {
      send_to_char( "Aid yourself?\r\n", ch );
      return;
   }

   if( victim->position > POS_STUNNED )
   {
      act( AT_PLAIN, "$N doesn't need your help.", ch, NULL, victim, TO_CHAR );
      return;
   }

   if( victim->hit <= -400 )
   {
      act( AT_PLAIN, "$N's condition is beyond your aiding ability.", ch, NULL, victim, TO_CHAR );
      return;
   }

   ch->alignment = ch->alignment + 20;
   ch->alignment = URANGE( -1000, ch->alignment, 1000 );

   percent = number_percent(  ) - ( get_curr_lck( ch ) - 13 );
   WAIT_STATE( ch, skill_table[gsn_aid]->beats );
   if( !IS_NPC( ch ) && percent > ch->pcdata->learned[gsn_aid] )
   {
      send_to_char( "You fail.\r\n", ch );
      learn_from_failure( ch, gsn_aid );
      return;
   }

   ch->alignment = ch->alignment + 20;
   ch->alignment = URANGE( -1000, ch->alignment, 1000 );

   act( AT_SKILL, "You aid $N!", ch, NULL, victim, TO_CHAR );
   act( AT_SKILL, "$n aids $N!", ch, NULL, victim, TO_NOTVICT );
   learn_from_success( ch, gsn_aid );
   if( victim->hit < 1 )
      victim->hit = 1;

   update_pos( victim );
   act( AT_SKILL, "$n aids you!", ch, NULL, victim, TO_VICT );
   return;
}


void do_mount( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_mount] <= 0 )
   {
      send_to_char( "I don't think that would be a good idea...\r\n", ch );
      return;
   }

   if( ch->mount )
   {
      send_to_char( "You're already mounted!\r\n", ch );
      return;
   }

   if( ( victim = get_char_room( ch, argument ) ) == NULL )
   {
      send_to_char( "You can't find that here.\r\n", ch );
      return;
   }

   if( !IS_NPC( victim ) || !IS_SET( victim->act, ACT_MOUNTABLE ) )
   {
      send_to_char( "You can't mount that!\r\n", ch );
      return;
   }

   if( IS_SET( victim->act, ACT_MOUNTED ) )
   {
      send_to_char( "That mount already has a rider.\r\n", ch );
      return;
   }

   if( victim->position < POS_STANDING )
   {
      send_to_char( "Your mount must be standing.\r\n", ch );
      return;
   }

   if( victim->position == POS_FIGHTING || victim->fighting )
   {
      send_to_char( "Your mount is moving around too much.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_mount]->beats );
   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_mount] )
   {
      SET_BIT( victim->act, ACT_MOUNTED );
      ch->mount = victim;
      act( AT_SKILL, "You mount $N.", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n skillfully mounts $N.", ch, NULL, victim, TO_NOTVICT );
      act( AT_SKILL, "$n mounts you.", ch, NULL, victim, TO_VICT );
      learn_from_success( ch, gsn_mount );
      ch->position = POS_MOUNTED;
   }
   else
   {
      act( AT_SKILL, "You unsuccessfully try to mount $N.", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n unsuccessfully attempts to mount $N.", ch, NULL, victim, TO_NOTVICT );
      act( AT_SKILL, "$n tries to mount you.", ch, NULL, victim, TO_VICT );
      learn_from_failure( ch, gsn_mount );
   }
   return;
}


void do_dismount( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *victim;

   if( ( victim = ch->mount ) == NULL )
   {
      send_to_char( "You're not mounted.\r\n", ch );
      return;
   }

   WAIT_STATE( ch, skill_table[gsn_mount]->beats );
   if( IS_NPC( ch ) || number_percent(  ) < ch->pcdata->learned[gsn_mount] )
   {
      act( AT_SKILL, "You dismount $N.", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n skillfully dismounts $N.", ch, NULL, victim, TO_NOTVICT );
      act( AT_SKILL, "$n dismounts you.  Whew!", ch, NULL, victim, TO_VICT );
      REMOVE_BIT( victim->act, ACT_MOUNTED );
      ch->mount = NULL;
      ch->position = POS_STANDING;
      learn_from_success( ch, gsn_mount );
   }
   else
   {
      act( AT_SKILL, "You fall off while dismounting $N.  Ouch!", ch, NULL, victim, TO_CHAR );
      act( AT_SKILL, "$n falls off of $N while dismounting.", ch, NULL, victim, TO_NOTVICT );
      act( AT_SKILL, "$n falls off your back.", ch, NULL, victim, TO_VICT );
      learn_from_failure( ch, gsn_mount );
      REMOVE_BIT( victim->act, ACT_MOUNTED );
      ch->mount = NULL;
      ch->position = POS_SITTING;
      global_retcode = damage( ch, ch, 1, TYPE_UNDEFINED );
   }
   return;
}


/**************************************************************************/


/*
 * Check for parry.
 */
bool check_parry( CHAR_DATA * ch, CHAR_DATA * victim )
{
   int chances;

   if( !IS_AWAKE( victim ) )
      return FALSE;

   chances = ch->parry;

   chances = URANGE( 0, chances, 95 );

   if( number_range( 1, 100 ) > chances )
      return FALSE;

   if( !IS_NPC( victim ) && !IS_SET( victim->pcdata->flags, PCFLAG_GAG ) )
       /*SB*/ act( AT_SKILL, "You parry $n's attack.", ch, NULL, victim, TO_VICT );

   if( !IS_NPC( ch ) && !IS_SET( ch->pcdata->flags, PCFLAG_GAG ) )   /* SB */
      act( AT_SKILL, "$N parries your attack.", ch, NULL, victim, TO_CHAR );

   return TRUE;
}



/*
 * Check for dodge.
 */
bool check_dodge( CHAR_DATA * ch, CHAR_DATA * victim )
{
   int chances;

   if( !IS_AWAKE( victim ) )
      return FALSE;

   chances = ch->dodge;

   chances = URANGE( 0, chances, 95 );

   if( number_range( 1, 100 ) > chances )
      return FALSE;

   if( !IS_NPC( victim ) && !IS_SET( victim->pcdata->flags, PCFLAG_GAG ) )
      act( AT_SKILL, "You dodge $n's attack.", ch, NULL, victim, TO_VICT );

   if( !IS_NPC( ch ) && !IS_SET( ch->pcdata->flags, PCFLAG_GAG ) )
      act( AT_SKILL, "$N dodges your attack.", ch, NULL, victim, TO_CHAR );

   return TRUE;
}

void do_poison_weapon( CHAR_DATA * ch, const char *argument )
{
   OBJ_DATA *obj;
   OBJ_DATA *pobj;
   OBJ_DATA *wobj;
   char arg[MAX_INPUT_LENGTH];
   int percent;

   if( !IS_NPC( ch ) && ch->pcdata->learned[gsn_poison_weapon] <= 0 )
   {
      send_to_char( "What do you think you are, a thief?\r\n", ch );
      return;
   }

   one_argument( argument, arg );

   if( arg[0] == '\0' )
   {
      send_to_char( "What are you trying to poison?\r\n", ch );
      return;
   }
   if( ch->fighting )
   {
      send_to_char( "While you're fighting?  Nice try.\r\n", ch );
      return;
   }
   if( ms_find_obj( ch ) )
      return;

   if( !( obj = get_obj_carry( ch, arg ) ) )
   {
      send_to_char( "You do not have that weapon.\r\n", ch );
      return;
   }
   if( obj->item_type != ITEM_WEAPON )
   {
      send_to_char( "That item is not a weapon.\r\n", ch );
      return;
   }
   if( IS_OBJ_STAT( obj, ITEM_POISONED ) )
   {
      send_to_char( "That weapon is already poisoned.\r\n", ch );
      return;
   }
   /*
    * Now we have a valid weapon...check to see if we have the powder. 
    */
   for( pobj = ch->first_carrying; pobj; pobj = pobj->next_content )
   {
      if( pobj->pIndexData->vnum == OBJ_VNUM_BLACK_POWDER )
         break;
   }
   if( !pobj )
   {
      send_to_char( "You do not have the black poison powder.\r\n", ch );
      return;
   }
   /*
    * Okay, we have the powder...do we have water? 
    */
   for( wobj = ch->first_carrying; wobj; wobj = wobj->next_content )
   {
      if( wobj->item_type == ITEM_DRINK_CON && wobj->value[1] > 0 && wobj->value[2] == 0 )
         break;
   }
   if( !wobj )
   {
      send_to_char( "You have no water to mix with the powder.\r\n", ch );
      return;
   }
   /*
    * And does the thief have steady enough hands? 
    */
   if( !IS_NPC( ch ) && ( ch->pcdata->condition[COND_DRUNK] > 0 ) )
   {
      send_to_char( "Your hands aren't steady enough to properly mix the poison.\r\n", ch );
      return;
   }
   WAIT_STATE( ch, skill_table[gsn_poison_weapon]->beats );

   percent = ( number_percent(  ) - get_curr_lck( ch ) - 14 );

   /*
    * Check the skill percentage 
    */
   separate_obj( pobj );
   separate_obj( wobj );
   if( !IS_NPC( ch ) && percent > ch->pcdata->learned[gsn_poison_weapon] )
   {
      set_char_color( AT_RED, ch );
      send_to_char( "You failed and spill some on yourself.  Ouch!\r\n", ch );
      set_char_color( AT_GREY, ch );
      damage( ch, ch, ch->skill_level[HUNTING_ABILITY], gsn_poison_weapon );
      act( AT_RED, "$n spills the poison all over!", ch, NULL, NULL, TO_ROOM );
      extract_obj( pobj );
      extract_obj( wobj );
      learn_from_failure( ch, gsn_poison_weapon );
      return;
   }
   separate_obj( obj );
   /*
    * Well, I'm tired of waiting.  Are you? 
    */
   act( AT_RED, "You mix $p in $P, creating a deadly poison!", ch, pobj, wobj, TO_CHAR );
   act( AT_RED, "$n mixes $p in $P, creating a deadly poison!", ch, pobj, wobj, TO_ROOM );
   act( AT_GREEN, "You pour the poison over $p, which glistens wickedly!", ch, obj, NULL, TO_CHAR );
   act( AT_GREEN, "$n pours the poison over $p, which glistens wickedly!", ch, obj, NULL, TO_ROOM );
   SET_BIT( obj->extra_flags, ITEM_POISONED );
   obj->cost *= ch->skill_level[HUNTING_ABILITY] / 2;
   /*
    * Set an object timer.  Don't want proliferation of poisoned weapons 
    */
   obj->timer = 10 + ch->skill_level[HUNTING_ABILITY];

   if( IS_OBJ_STAT( obj, ITEM_BLESS ) )
      obj->timer *= 2;

   if( IS_OBJ_STAT( obj, ITEM_MAGIC ) )
      obj->timer *= 2;

   /*
    * WHAT?  All of that, just for that one bit?  How lame. ;) 
    */
   act( AT_BLUE, "The remainder of the poison eats through $p.", ch, wobj, NULL, TO_CHAR );
   act( AT_BLUE, "The remainder of the poison eats through $p.", ch, wobj, NULL, TO_ROOM );
   extract_obj( pobj );
   extract_obj( wobj );
   learn_from_success( ch, gsn_poison_weapon );
   return;
}

void do_scribe( CHAR_DATA * ch, const char *argument )
{
}

void do_brew( CHAR_DATA * ch, const char *argument )
{
}

bool check_grip( CHAR_DATA * ch, CHAR_DATA * victim )
{
   int schance;

   if( !IS_AWAKE( victim ) )
      return FALSE;

   if( IS_NPC( victim ) && !IS_SET( victim->defenses, DFND_GRIP ) )
      return FALSE;

   if( IS_NPC( victim ) )
      schance = UMIN( 60, 2 * victim->top_level );
   else
      schance = ( int )( victim->pcdata->learned[gsn_grip] / 2 );

   /*
    * Consider luck as a factor 
    */
   schance += ( 2 * ( get_curr_lck( victim ) - 13 ) );

   if( number_percent(  ) >= schance + victim->top_level - ch->top_level )
   {
      learn_from_failure( victim, gsn_grip );
      return FALSE;
   }
   act( AT_SKILL, "You evade $n's attempt to disarm you.", ch, NULL, victim, TO_VICT );
   act( AT_SKILL, "$N holds $S weapon strongly, and is not disarmed.", ch, NULL, victim, TO_CHAR );
   learn_from_success( victim, gsn_grip );
   return TRUE;
}

void do_circle( CHAR_DATA * ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   CHAR_DATA *victim;
   OBJ_DATA *obj;
   int percent;

   if( IS_NPC( ch ) && IS_AFFECTED( ch, AFF_CHARM ) )
   {
      send_to_char( "You can't concentrate enough for that.\r\n", ch );
      return;
   }

   one_argument( argument, arg );

   if( ch->mount )
   {
      send_to_char( "You can't circle while mounted.\r\n", ch );
      return;
   }

   if( arg[0] == '\0' )
   {
      send_to_char( "Circle around whom?\r\n", ch );
      return;
   }

   if( ( victim = get_char_room( ch, arg ) ) == NULL )
   {
      send_to_char( "They aren't here.\r\n", ch );
      return;
   }

   if( victim == ch )
   {
      send_to_char( "How can you sneak up on yourself?\r\n", ch );
      return;
   }

   if( is_safe( ch, victim ) )
      return;

   if( ( obj = get_eq_char( ch, WEAR_WIELD ) ) == NULL || ( obj->value[3] != 11 && obj->value[3] != 2 ) )
   {
      send_to_char( "You need to wield a piercing or stabbing weapon.\r\n", ch );
      return;
   }

   if( !ch->fighting )
   {
      send_to_char( "You can't circle when you aren't fighting.\r\n", ch );
      return;
   }

   if( !victim->fighting )
   {
      send_to_char( "You can't circle around a person who is not fighting.\r\n", ch );
      return;
   }

   if( victim->num_fighting < 2 )
   {
      act( AT_PLAIN, "You can't circle around them without a distraction.", ch, NULL, victim, TO_CHAR );
      return;
   }

   percent = number_percent(  ) - ( get_curr_lck( ch ) - 16 ) + ( get_curr_lck( victim ) - 13 );

   WAIT_STATE( ch, skill_table[gsn_circle]->beats );
   if( percent < ( IS_NPC( ch ) ? ( ch->skill_level[HUNTING_ABILITY] * 1.5 ) : ch->pcdata->learned[gsn_circle] ) )
   {
      learn_from_success( ch, gsn_circle );
      global_retcode = multi_hit( ch, victim, gsn_circle );

   }
   else
   {
      learn_from_failure( ch, gsn_circle );
      global_retcode = damage( ch, victim, 0, gsn_circle );
   }
   return;
}

/* Berserk and HitAll. -- Altrag */
void do_berserk( CHAR_DATA * ch, const char *argument )
{
   short percent;
   AFFECT_DATA af;

   if( !ch->fighting )
   {
      send_to_char( "But you aren't fighting!\r\n", ch );
      return;
   }

   if( IS_AFFECTED( ch, AFF_BERSERK ) )
   {
      send_to_char( "Your rage is already at its peak!\r\n", ch );
      return;
   }

   percent = IS_NPC( ch ) ? 80 : ch->pcdata->learned[gsn_berserk];
   WAIT_STATE( ch, skill_table[gsn_berserk]->beats );
   if( !chance( ch, percent ) )
   {
      send_to_char( "You couldn't build up enough rage.\r\n", ch );
      learn_from_failure( ch, gsn_berserk );
      return;
   }
   af.type = gsn_berserk;
   /*
    * Hmmm.. 10-20 combat rounds at level 50.. good enough for most mobs,
    * and if not they can always go berserk again.. shrug.. maybe even
    * too high. -- Altrag 
    */
   af.duration = number_range( ch->top_level / 5, ch->top_level * 2 / 5 );
   /*
    * Hmm.. you get stronger when yer really enraged.. mind over matter
    * type thing.. 
    */
   af.location = APPLY_STR;
   af.modifier = 1;
   af.bitvector = meb( AFF_BERSERK );
   affect_to_char( ch, &af );
   send_to_char( "You start to lose control..\r\n", ch );
   learn_from_success( ch, gsn_berserk );
   return;
}

/* External from fight.c */
ch_ret one_hit args( ( CHAR_DATA * ch, CHAR_DATA * victim, int dt ) );
void do_hitall( CHAR_DATA * ch, const char *argument )
{
   CHAR_DATA *vch;
   CHAR_DATA *vch_next;
   short nvict = 0;
   short nhit = 0;
   short percent;

   if( IS_SET( ch->in_room->room_flags, ROOM_SAFE ) )
   {
      send_to_char( "You cannot do that here.\r\n", ch );
      return;
   }

   if( !ch->in_room->first_person )
   {
      send_to_char( "There's no one here!\r\n", ch );
      return;
   }
   percent = IS_NPC( ch ) ? 80 : ch->pcdata->learned[gsn_hitall];
   for( vch = ch->in_room->first_person; vch; vch = vch_next )
   {
      vch_next = vch->next_in_room;
      if( is_same_group( ch, vch ) || !is_legal_kill( ch, vch ) || !can_see( ch, vch ) || is_safe( ch, vch ) )
         continue;
      if( ++nvict > ch->skill_level[COMBAT_ABILITY] / 5 )
         break;
      if( chance( ch, percent ) )
      {
         nhit++;
         global_retcode = one_hit( ch, vch, TYPE_UNDEFINED );
      }
      else
         global_retcode = damage( ch, vch, 0, TYPE_UNDEFINED );
      /*
       * Fireshield, etc. could kill ch too.. :>.. -- Altrag 
       */
      if( global_retcode == rCHAR_DIED || global_retcode == rBOTH_DIED || char_died( ch ) )
         return;
   }
   if( !nvict )
   {
      send_to_char( "There's no one here!\r\n", ch );
      return;
   }
   ch->move = UMAX( 0, ch->move - nvict * 3 + nhit );
   if( nhit )
      learn_from_success( ch, gsn_hitall );
   else
      learn_from_failure( ch, gsn_hitall );
   return;
}



bool check_illegal_psteal( CHAR_DATA * ch, CHAR_DATA * victim )
{
   return FALSE;
}

void do_scan( CHAR_DATA * ch, const char *argument )
{
   ROOM_INDEX_DATA *was_in_room;
   ROOM_INDEX_DATA *to_room;
   EXIT_DATA *pexit;
   short dir = -1;
   short dist;
   short max_dist = 5;

   if( IS_AFFECTED( ch, AFF_BLIND ) && ( !IS_AFFECTED( ch, AFF_TRUESIGHT ) ||
    ( !IS_NPC( ch ) && !IS_SET( ch->act, PLR_HOLYLIGHT ) ) ) )
   {
      send_to_char( "Everything looks the same when you're blind...\r\n", ch );
      return;
   }

   if( argument[0] == '\0' )
   {
      send_to_char( "Scan in a direction...\r\n", ch );
      return;
   }

   if( ( dir = get_door( argument ) ) == -1 )
   {
      send_to_char( "Scan in WHAT direction?\r\n", ch );
      return;
   }

   was_in_room = ch->in_room;
   act( AT_GREY, "Scanning $t...", ch, dir_name[dir], NULL, TO_CHAR );
   act( AT_GREY, "$n scans $t.", ch, dir_name[dir], NULL, TO_ROOM );

   if( IS_NPC( ch ) || ( number_percent(  ) > ch->pcdata->learned[gsn_scan] ) )
   {
      act( AT_GREY, "You stop scanning $t as your vision blurs.", ch, dir_name[dir], NULL, TO_CHAR );
      learn_from_failure( ch, gsn_scan );
      return;
   }

   if( ( pexit = get_exit( ch->in_room, dir ) ) == NULL )
   {
      act( AT_GREY, "You can't see $t.", ch, dir_name[dir], NULL, TO_CHAR );
      return;
   }

   if( ch->top_level < 50 )
      max_dist--;
   if( ch->top_level < 20 )
      max_dist--;

   for( dist = 1; dist <= max_dist; )
   {
      if( IS_SET( pexit->exit_info, EX_CLOSED ) )
      {
         if( IS_SET( pexit->exit_info, EX_SECRET ) )
            act( AT_GREY, "Your view $t is blocked by a wall.", ch, dir_name[dir], NULL, TO_CHAR );
         else
            act( AT_GREY, "Your view $t is blocked by a door.", ch, dir_name[dir], NULL, TO_CHAR );
         break;
      }

      to_room = NULL;
      if( pexit->distance > 1 )
         to_room = generate_exit( ch->in_room, &pexit );

      if( to_room == NULL )
         to_room = pexit->to_room;

      if( room_is_private( ch, to_room ) && get_trust( ch ) < LEVEL_GREATER )
      {
         act( AT_GREY, "Your view $t is blocked by a private room.", ch, dir_name[dir], NULL, TO_CHAR );
         break;
      }
      char_from_room( ch );
      char_to_room( ch, to_room );
      set_char_color( AT_RMNAME, ch );
      send_to_char( ch->in_room->name, ch );
      send_to_char( "\r\n", ch );
      show_list_to_char( ch->in_room->first_content, ch, FALSE, FALSE );
      show_char_to_char( ch->in_room->first_person, ch );

      switch ( ch->in_room->sector_type )
      {
         default:
            dist++;
            break;
         case SECT_AIR:
            if( number_percent(  ) < 80 )
               dist++;
            break;
         case SECT_INSIDE:
         case SECT_FIELD:
         case SECT_UNDERGROUND:
            dist++;
            break;
         case SECT_FOREST:
         case SECT_CITY:
         case SECT_DESERT:
         case SECT_HILLS:
            dist += 2;
            break;
         case SECT_WATER_SWIM:
         case SECT_WATER_NOSWIM:
            dist += 3;
            break;
         case SECT_MOUNTAIN:
         case SECT_UNDERWATER:
         case SECT_OCEANFLOOR:
            dist += 4;
            break;
      }

      if( dist >= max_dist )
      {
         act( AT_GREY, "Your vision blurs with distance and you see no " "farther $t.", ch, dir_name[dir], NULL, TO_CHAR );
         break;
      }
      if( ( pexit = get_exit( ch->in_room, dir ) ) == NULL )
      {
         act( AT_GREY, "Your view $t is blocked by a wall.", ch, dir_name[dir], NULL, TO_CHAR );
         break;
      }
   }

   char_from_room( ch );
   char_to_room( ch, was_in_room );
   learn_from_success( ch, gsn_scan );

   return;
}

void do_slice( CHAR_DATA * ch, const char *argument )
{
}

void generate_buff_threat( CHAR_DATA *ch, CHAR_DATA *victim, int amount )
{
   THREAT_DATA *threat;

   for( threat = first_threat; threat; threat = threat->next )
      if( threat->angry_at == victim )
         generate_threat( ch, threat->angered, amount );

   return;
}

void sort_mob_skills( CHAR_DATA *ch )
{
   int x;
   int holder = -1;

   for( x = 0; x < MAX_NPC_SKILL; x++ )
   {
      if( ch->pIndexData->npc_skills[x] == -1 )
      {
         holder = x;
         continue;
      }
      if( ch->pIndexData->npc_skills[x] != -1 && holder != -1 )
      {
         ch->pIndexData->npc_skills[holder] = ch->pIndexData->npc_skills[x];
         ch->pIndexData->npc_skills[x] = -1;
         x = holder;
         holder = -1;
         continue;
      }
   }
   return;
}

bool mob_has_skill( CHAR_DATA *ch, int gsn )
{
   int x;

   if( !IS_NPC( ch ) )
      return 0;

   for( x = 0; x < MAX_NPC_SKILL; x++ )
   {
      if( ch->pIndexData->npc_skills[x] == gsn )
         return TRUE;
   }
   return FALSE;
}

void do_skillcraft( CHAR_DATA *ch, const char *argument )
{
   SKILLTYPE *skill;
   FACTOR_DATA *factor;
   char arg[MAX_INPUT_LENGTH];
   char arg2[MAX_INPUT_LENGTH];
   int sn, x;

   argument = one_argument( argument, arg );
   argument = one_argument( argument, arg2 );

   if( IS_NPC( ch ) )
   {
      send_to_char( "NPCs cannot create skills.\r\n", ch );
      return;
   }

   if( arg[0] == '\0' || arg2[0] == '\0' )
   {
      send_to_char( "Proper usage: skillcraft <skill> <command> <field> <value>\r\n", ch );
      send_to_char( "Or:           skillcraft create <skill>\r\n", ch );
      send_to_char( "Or:           skillcraft delete <skill>(Not yet in)\r\n", ch );
      send_to_char( "Commands:\r\n", ch );
      send_to_char( "  show name addfactor remfactor type taget style cost damtype\r\n\r\n", ch );

      send_to_char( "Settable Skill Types:", ch );
      for( x = 0; x < MAX_SKILLTYPE; x++ )
         if( xIS_SET( ch->avail_skilltypes, x ) )
            ch_printf( ch, " %s", skill_tname[x] );
      send_to_char( "\r\n", ch );

      send_to_char( "Settable Style Types:", ch );
      for( x = 0; x < STYLE_MAX; x++ )
         if( xIS_SET( ch->avail_skillstyles, x ) )
            ch_printf( ch, " %s", style_type[x] );
      send_to_char( "\r\n", ch );

      send_to_char( "Settable Target Types:", ch );
      for( x = 0; x < TAR_CHAR_MAX; x++ )
         if( xIS_SET( ch->avail_targettypes, x ) )
            ch_printf( ch, " %s", target_type[x] );
      send_to_char( "\r\n", ch );

      send_to_char( "Settable Cost Types:", ch );
      for( x = 0; x < MAX_COST; x++ )
         if( xIS_SET( ch->avail_costtypes, x ) )
            ch_printf( ch, " %s", cost_type[x] );
      send_to_char( "\r\n", ch );

      send_to_char( "Settable Damage Types:", ch );
      for( x = 0; x < MAX_DAMTYPE; x++ )
         if( xIS_SET( ch->avail_damtypes, x ) )
            ch_printf( ch, " %s", d_type[x] );
      send_to_char( "\r\n", ch );

      send_to_char( "Available Factors:\r\n", ch );
      for( factor = ch->first_factor, x = 0; factor; factor = factor->next )
      {
         if( factor->factor_type == APPLY_FACTOR )
         {
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Location: %-10.10s | Apply Type: %-10.10s | Duration: %-10d |\r\n", x,
                       factor_names[factor->factor_type],
                       a_types[factor->location],
                       applytypes_type[factor->apply_type],
                       factor->duration );

            if( factor->location == APPLY_AFFECT )
            {
               for( x = 0; x < MAX_AFF; x++ )
                  if( xIS_SET( factor->affect, x ) )
                     ch_printf( ch, " %s,", a_flags[x] );
               send_to_char( "\r\n", ch );
            }
            else
               ch_printf( ch, " Modifier: %f\r\n", factor->modifier );
         }
         else if( factor->factor_type == STAT_FACTOR )
         {
            int stat;
            double mod;

            stat = factor->modifier / 1;
            mod = factor->modifier - stat;
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Add %d%% of %s to Base Roll\r\n", x,
                       factor_names[factor->factor_type],
                       mod,
                       a_types[stat] );
         }
         else if( factor->factor_type == ATTACK_FACTOR )
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Multiplies Damroll Effect by %f\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         else if( factor->factor_type == DEFENSE_FACTOR )
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Adds %f%% of players global armor to skill damage\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         else if( factor->factor_type == BASEROLL_FACTOR )
           ch_printf( ch, "%2d: Factor Type: %-10.10s | Multiplies Base Roll of Weapon by %f\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         x++;
      }
      return;
   }

   if( !str_cmp( arg, "create" ) )
   {
      if( ch->top_sn >= MAX_PC_SKILL )
      {
         send_to_char( "You have too many skills.\r\n", ch );
         return;
      }

      CREATE( skill, SKILLTYPE, 1 );
      skill->name = str_dup( argument );
      skill->noun_damage = str_dup( "" );
      skill->msg_off = str_dup( "" );
      skill->spell_fun = spell_null;
      skill->type = SKILL_UNSET;
      skill->style = STYLE_UNSET;
      skill->target = TAR_CHAR_UNSET;
      ch->pc_skills[ch->top_sn] = skill;
      ch->top_sn++;
      send_to_char( "Skill created.\r\n", ch );
      save_char_obj( ch );
      saving_char = NULL;
      return;
   }

   if( ( sn = get_player_skill_sn( ch, arg ) ) == -1 )
   {
      ch_printf( ch, "You know no such skill: %s\r\n", arg );
      return;
   }
   skill = ch->pc_skills[sn];

   if( !str_cmp( arg2, "show" ) )
   {
      ch_printf( ch, "Skill Name: %s\r\n", skill->name );
      ch_printf( ch, "Skill Type: %-10.10s Skill Style: %-10.10s Target Type: %-10.10s\r\n",
                 skill_tname[skill->type], style_type[skill->style], target_type[skill->target] );

      ch_printf(  ch, "Cost Type:" );
      for( x = 0; x < MAX_COST; x++ )
         if( xIS_SET( skill->cost, x ) )
            ch_printf( ch, " %s", cost_type[x] );
      send_to_char( "\r\n", ch );

      ch_printf( ch, "Damage Type:" );
      for( x = 0; x < MAX_DAMTYPE; x++ )
         if( xIS_SET( skill->damtype, x  ) )
            ch_printf( ch, " %s", d_type[x] );
      send_to_char( "\r\n", ch );

      for( factor = skill->first_factor, x = 0; factor; factor = factor->next )
      {
         if( factor->factor_type == APPLY_FACTOR )
         {
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Location: %-10.10s | Apply Type: %-10.10s | Duration: %-10d |\r\n", x,
                       factor_names[factor->factor_type],
                       a_types[factor->location],
                       applytypes_type[factor->apply_type],
                       factor->duration );

            if( factor->location == APPLY_AFFECT )
            {
               for( x = 0; x < MAX_AFF; x++ )
                  if( xIS_SET( factor->affect, x ) )
                     ch_printf( ch, " %s,", a_flags[x] );
               send_to_char( "\r\n", ch );
            }
            else
               ch_printf( ch, " Modifier: %f\r\n", factor->modifier );
         }
         else if( factor->factor_type == STAT_FACTOR )
         {
            int stat;
            double mod;

            stat = factor->modifier / 1;
            mod = factor->modifier - stat;
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Add %d%% of %s to Base Roll\r\n", x,
                       factor_names[factor->factor_type],
                       mod,
                       a_types[stat] );
         }
         else if( factor->factor_type == ATTACK_FACTOR )
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Multiplies Damroll Effect by %f\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         else if( factor->factor_type == DEFENSE_FACTOR )
            ch_printf( ch, "%2d: Factor Type: %-10.10s | Adds %f%% of players global armor to skill damage\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         else if( factor->factor_type == BASEROLL_FACTOR )
           ch_printf( ch, "%2d: Factor Type: %-10.10s | Multiplies Base Roll of Weapon by %f\r\n", x,
                       factor_names[factor->factor_type],
                       factor->modifier );
         x++;
      }
   }

   if( !str_cmp( arg2, "addfactor" ) )
   {
      int selection;
      if( !is_number( argument ) )
      {
         send_to_char( "Please enter the number of the factor you wish to add to the skill.\r\n", ch );
         return;
      }

      if( ( selection = atoi( argument ) ) < 0 )
      {
         send_to_char( "Invalid number.\r\n", ch );
         return;
      }

      for( factor = ch->first_factor, x = 0; factor; factor = factor->next )
      {
         if( x == selection )
            break;
         x++;
      }

      if( !factor )
      {
         send_to_char( "Invalid number.\r\n", ch );
         return;
      }

      addfactor( ch, skill, factor );
      update_skill( ch, skill );
      send_to_char( "Factor added.\r\n", ch );
      return;
   }

   if( !str_cmp( arg2, "remfactor" ) )
   {
      int selection;
      if( !is_number( argument ) )
      {
         send_to_char( "Please enter the number of the factor you wish to remove from the skill.\r\n", ch );
         return;
      }

      if( ( selection = atoi( argument ) ) < 0 )
      {
         send_to_char( "Invalid number.\r\n", ch );
         return;
      }

      for( factor = skill->first_factor, x = 0; factor; factor = factor->next )
      {
         if( x == selection )
            break;
         x++;
      }

      if( !factor )
      {
         send_to_char( "Invalid number.\r\n", ch );
         return;
      }

      remfactor( ch, skill, factor, TRUE );
      update_skill( ch, skill );
      send_to_char( "Factor removed.\r\n", ch );
      return;
   }

   send_to_char( "Improper Usage...\r\n", ch );
   do_skillcraft( ch, "" );
   return;
}

void do_skills( CHAR_DATA *ch, const char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   char arg2[MAX_INPUT_LENGTH];
   char arg3[MAX_INPUT_LENGTH];
   char buf[MAX_STRING_LENGTH];
   int x, slot, gsn;
   int column = 0;

   argument = one_argument( argument, arg );
   argument = one_argument( argument, arg2 );
   argument = one_argument( argument, arg3 );

   if( arg[0] == '\0' )
   {
      send_to_char( "&BSkill Slots\r\n-----------\r\n", ch );
      for( x = 0; x < MAX_SKILL_SLOT; x++ )
      {
           slot = ( x + 1 ) * 5;
           ch_printf( ch, "%s(%-3d) %-22.22s&w",
                      ch->skill_level[COMBAT_ABILITY] >= slot ? "&C" : "&z",
                      slot,
                      ch->skill_slots[x] ? ch->skill_slots[x]->name : "none" );
          if( ++column == 3 )
          {
             column = 0;
             send_to_char( "\r\n", ch );
          }
      }
      send_to_char( "\r\n&BAvailable Skills\r\n----------------\r\n", ch );
      for( x = 0; x < MAX_PC_SKILL; x++ )
      {
         if( !ch->pc_skills[x] )
            break;
         if( ch->pc_skills[x]->name[0] != '\0' )
         {
            if( !is_skill_usable( ch, ch->pc_skills[x] ) )
               sprintf( buf, "&zInc" );
            else if( is_skill_set( ch, ch->pc_skills[x] ) )
               sprintf( buf, "&zSet" );
            else
               sprintf( buf, "&CAva" );

            ch_printf( ch, "%-3s: %-21.21s&w",
                       buf,
                       ch->pc_skills[x]->name );
             if( ++column == 3 )
             {
                column = 0;
                send_to_char( "\r\n", ch );
             }
         }
      }
      send_to_char( "\r\nOther Usages: skills <command>\r\n", ch );
      send_to_char( "  Commands: unset set\r\n", ch );
      return;
   }
   if( !str_cmp( arg, "unset" ) )
   {
      if( arg2[0] == '\0' )
      {
         send_to_char( "Proper Usage: skills unset all\r\n", ch );
         send_to_char( "Or:           skills unset <skill_name>\r\n", ch );
         send_to_char( "Or:           skills unset slot <slot number>\r\n", ch );
         send_to_char( "Or:           skills unset level <slot level number>\r\n", ch );
         return;
      }
      else if( !str_cmp( arg2, "all" ) )
      {
         for( x = 0; x < MAX_SKILL_SLOT; x++ )
            ch->skill_slots[x] = NULL;
         send_to_char( "All skills unset.\r\n", ch );
      }
      else if( !str_cmp( arg2, "slot" ) )
      {
         if( ( slot = is_number( arg3 ) ? atoi( arg3 ) : -1 ) <= 0 || slot > 30 ) /* Gets tricky here because slots actually start at 0 but most players won't know that */
         {
            send_to_char( "Not a valid slot number.\r\n", ch );
            do_skills( ch, "unset" );
            return;
         }
         slot--;
         ch->skill_slots[slot] = NULL;
         send_to_char( "Skill unset\r\n", ch );
      }
      else if( !str_cmp( arg2, "level" ) )
      {
         if( ( slot = is_number( arg3 ) ? atoi( arg3 ) : -1 ) <= 0 || slot > 150 || slot % 5 != 0 )
         {
            send_to_char( "Not a valid slot number.\r\n", ch );
            do_skills( ch, "unset" );
            return;
         }
         slot /= 5;
         ch->skill_slots[( slot - 1 )] = NULL;
         send_to_char( "Skill unset\r\n", ch );
      }
      else
      {
         if( ( gsn = get_player_skill_sn( ch, arg2 ) ) == -1 )
         {
            send_to_char( "You have no skill with that name.\r\n", ch );
            return;
         }
         if( !is_skill_set( ch, ch->pc_skills[gsn] ) )
         {
            send_to_char( "No skill with that name is set.\r\n", ch );
            return;
         }
         unset_skill( ch, ch->pc_skills[gsn] );
      }
      save_char_obj( ch );
      saving_char = NULL;
      return;
   }
   if( !str_cmp( arg, "set" ) )
   {
      if( arg2[0] == '\0' )
      {
         send_to_char( "Proper Usage: skills set '<skill>' level <slot level number>\r\n", ch );
         send_to_char( "Or:           skills set '<skill>' slot  <slot number>>\r\n", ch );
         return;
      }
      else
      {
         if( ( gsn = get_player_skill_sn( ch, arg2 ) ) == -1 )
         {
            send_to_char( "You have no skill with that name.\r\n", ch );
            return;
         }
         if( !is_skill_usable( ch, ch->pc_skills[gsn] ) )
         {
            send_to_char( "Skill is not usable.\r\n", ch );
            return;
         }
         if( !str_cmp( arg3, "level" ) )
         {
            if( ( slot = is_number( argument ) ? atoi( argument ) : -1 ) <= 0 || slot > 150 || slot % 5 != 0)
            {
               send_to_char( "Not a valid slot.\r\n", ch );
               return;
            }
            ch->skill_slots[(slot / 5) - 1] = ch->pc_skills[gsn];
            ch_printf( ch, "%s set at level %d\r\n", ch->pc_skills[gsn]->name, slot );
         }
         else if( !str_cmp( arg3, "slot" ) )
         {
           if( ( slot = is_number( argument ) ? atoi( argument ) : -1  ) <= 0 || slot > 30 )
           {
              send_to_char( "Not a valid slot.\r\n", ch );
              return;
           }
           ch->skill_slots[(slot - 1)] = ch->pc_skills[gsn];
           ch_printf( ch, "%s set at slot %d\r\n", ch->pc_skills[gsn]->name, slot );
         }
         else
         {
            send_to_char( "Not proper usage.\r\n", ch );
            do_skills( ch, "set" );
            return;
         }
         save_char_obj( ch );
         saving_char = NULL;
         return;
      }
   }
   send_to_char( "Not a valid input.\r\n", ch );
   return;
}

DISC_DATA *get_discipline_from_id( int id )
{
   DISC_DATA *disc;

   for( disc = first_discipline; disc; disc = disc->next )
      if( disc->id == id )
         return disc;
   return NULL;
}

FACTOR_DATA *get_factor_from_id( int id )
{
   DISC_DATA *disc;
   FACTOR_DATA *factor;

   for( disc = first_discipline; disc; disc = disc->next )
      for( factor = disc->first_factor; factor; factor = factor->next )
         if( factor->id == id )
            return factor;
   return NULL;
}

bool has_empty_discipline_slot( CHAR_DATA *ch )
{
   int x;

   for( x = 0; x < MAX_DISCIPLINE; x++ )
      if( ch->known_disciplines[x] == NULL )
         return TRUE;
   return FALSE;
}

void add_discipline( CHAR_DATA *ch, DISC_DATA *discipline )
{
   int x;

   if( !has_empty_discipline_slot( ch ) )
   {
      bug( "%s: trying to add discipline to a character with no empty slot.", __FUNCTION__ );
      return;
   }
   if( IS_NPC( ch ) )
   {
      bug( "%s: trying to add discipline to an NPC.", __FUNCTION__ );
      return;
   }

   for( x = 0; x < MAX_DISCIPLINE; x++ )
      if( ch->known_disciplines[x] == NULL )
      {
         ch->known_disciplines[x] = discipline;
         break;
      }

   save_char_obj( ch );
   saving_char = NULL;
   return;
}

void rem_discipline( CHAR_DATA *ch, DISC_DATA *discipline )
{
   int x;

   if( !player_has_discipline( ch, discipline ) )
   {
      bug( "%s: trying to remove a discipline that player does not know.", __FUNCTION__ );
      return;
   }
   if( IS_NPC( ch ) )
   {
      bug( "%s: trying to rem discipline to an NPC.", __FUNCTION__ );
      return;
   }

   for( x = 0; x < MAX_DISCIPLINE; x++ )
       if( ch->known_disciplines[x] == discipline )
          ch->known_disciplines[x] = NULL;

   save_char_obj( ch );
   saving_char = NULL;
   return;

}

bool is_discipline_set( CHAR_DATA *ch, DISC_DATA *discipline )
{
   int x;

   for( x = 0; x < MAX_EQUIPPED_DISCIPLINE; x++ )
      if( ch->equipped_disciplines[x] == discipline )
         return TRUE;
   return FALSE;
}

bool player_has_discipline( CHAR_DATA *ch, DISC_DATA *discipline )
{
   int x;

   for( x = 0; x < MAX_DISCIPLINE; x++ )
      if( ch->known_disciplines[x] == discipline )
         return TRUE;
   return FALSE;
}

bool player_has_discipline_setslot( CHAR_DATA *ch )
{
   int x;

   for( x = 0; x < MAX_EQUIPPED_DISCIPLINE; x++ )
      if( ch->equipped_disciplines[x] == NULL )
         return TRUE;
   return FALSE;
}

void set_discipline( CHAR_DATA *ch, DISC_DATA *disc )
{
   FACTOR_DATA *factor;
   int x;

   if( !player_has_discipline_setslot( ch ) )
   {
      bug( "%s: attempting to set a discipline to a character that doesn't have a free slot.", __FUNCTION__ );
      return;
   }
   if( !player_has_discipline( ch, disc ) )
   {
      bug( "%s: attempting to set a discipline to a character that doesn't know the discipline.", __FUNCTION__ );
      return;
   }

   for( x = 0; x < MAX_EQUIPPED_DISCIPLINE; x++ )
      if( ch->equipped_disciplines[x] == NULL )
         ch->equipped_disciplines[x] = disc;

   for( factor = disc->first_factor; factor; factor = factor->next )
   {
      FACTOR_DATA *new_factor;
      new_factor = copy_factor( factor );
      LINK( new_factor, ch->first_factor, ch->last_factor, next, prev );
   }

   xSET_BITS( ch->avail_costtypes, disc->cost );
   xSET_BITS( ch->avail_skilltypes, disc->skill_type );
   xSET_BITS( ch->avail_skillstyles, disc->skill_style );
   xSET_BITS( ch->avail_damtypes, disc->damtype );
   xSET_BITS( ch->avail_targettypes, disc->target_type );

   save_char_obj( ch );
   saving_char = NULL;
   return;
}

void unset_discipline( CHAR_DATA *ch, DISC_DATA *disc )
{
   int x;

   if( !is_discipline_set( ch, disc ) )
   {
      bug( "%s: attempting to unset a discipline that the character doesn't have set.", __FUNCTION__ );
      return;
   }

   /* Remove the Bits and then we will re-add the still equipped disciplines bits */

   xCLEAR_BITS( ch->avail_targettypes );
   xCLEAR_BITS( ch->avail_damtypes );
   xCLEAR_BITS( ch->avail_costtypes );
   xCLEAR_BITS( ch->avail_skilltypes );
   xCLEAR_BITS( ch->avail_skillstyles );

   for( x = 0; x < MAX_EQUIPPED_DISCIPLINE; x++ )
   {
      if( ch->equipped_disciplines[x] == disc )
      {
         ch->equipped_disciplines[x] = NULL;
         continue;
      }
      if( ch->equipped_disciplines[x] == NULL )
         continue;

      xSET_BITS( ch->avail_costtypes, ch->equipped_disciplines[x]->cost );
      xSET_BITS( ch->avail_skilltypes, ch->equipped_disciplines[x]->skill_type );
      xSET_BITS( ch->avail_skillstyles, ch->equipped_disciplines[x]->skill_style );
      xSET_BITS( ch->avail_damtypes, ch->equipped_disciplines[x]->damtype );
      xSET_BITS( ch->avail_targettypes, ch->equipped_disciplines[x]->target_type );
   }

   skills_checksum( ch );
   save_char_obj( ch );
   saving_char = NULL;
   return;
}

FACTOR_DATA *copy_factor( FACTOR_DATA *factor )
{
   FACTOR_DATA *new_factor;

   CREATE( new_factor, FACTOR_DATA, 1 );
   new_factor->id = factor->id;
   new_factor->factor_type = factor->factor_type;
   new_factor->location = factor->location;
   new_factor->affect = factor->affect;
   new_factor->modifier = factor->modifier;
   new_factor->apply_type = factor->apply_type;
   new_factor->duration = factor->duration;
   return new_factor;
}

void unset_skill( CHAR_DATA *ch, SKILLTYPE *skill )
{
   int gsn, slot;

   if( ( gsn = get_player_skill_sn( ch, skill->name ) ) == -1 )
   {
      bug( "%s: can't find skill gsn.", __FUNCTION__ );
      return;
   }

   if( ( slot = get_skill_slot( ch, ch->pc_skills[gsn] ) ) == -1 )
   {
      bug( "%s: skill not set to a slot, can't unset.", __FUNCTION__ );
      return;
   }
   ch->skill_slots[slot] = NULL;
   ch_printf( ch, "%s Unset.", skill->name );
   save_char_obj( ch );
   saving_char = NULL;
   return;
}


void skills_checksum( CHAR_DATA * ch )
{
   FACTOR_DATA *factor;
   int x;


   for( x = 0; x < MAX_PC_SKILL; x++ )
   {
      if( !ch->pc_skills[x] )
         continue;

      if( !xIS_SET( ch->avail_targettypes, ch->pc_skills[x]->target ) )
      {
         ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
         unset_skill( ch, ch->pc_skills[x] );
         continue;
      }
      if( !xHAS_BITS( ch->avail_costtypes, ch->pc_skills[x]->cost ) )
      {
         ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
         unset_skill( ch, ch->pc_skills[x] );
         continue;
      }
      if( !xHAS_BITS( ch->avail_damtypes, ch->pc_skills[x]->damtype ) )
      {
         ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
         unset_skill( ch, ch->pc_skills[x] );
         continue;
      }
      if( !xIS_SET( ch->avail_skilltypes, ch->pc_skills[x]->type ) )
      {
         ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
         unset_skill( ch, ch->pc_skills[x] );
         continue;
      }
      if( !xIS_SET( ch->avail_skillstyles, ch->pc_skills[x]->style ) )
      {
         ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
         unset_skill( ch, ch->pc_skills[x] );
         continue;
      }
      for( factor = ch->pc_skills[x]->first_factor; factor; factor = factor->next )
         if( !is_discipline_set( ch, factor->owner ) )
         {
            ch_printf( ch, "You no longer meet the requirements for %s.\r\n", ch->pc_skills[x]->name );
            unset_skill( ch, ch->pc_skills[x] );
            break;
         }
   }
}

void addfactor( CHAR_DATA *ch, SKILLTYPE *skill, FACTOR_DATA *factor )
{
   UNLINK( factor, ch->first_factor, ch->last_factor, next, prev );
   LINK( factor, skill->first_factor, skill->last_factor, next, prev );
   factor_to_skill( skill, factor, TRUE );
   return;
}

void remfactor( CHAR_DATA *ch, SKILLTYPE *skill, FACTOR_DATA *factor, bool MakeAvailable )
{
   UNLINK( factor, skill->first_factor, skill->last_factor, next, prev );
   if( MakeAvailable )
      LINK( factor, ch->first_factor, ch->last_factor, next, prev );
   else
   {
      factor->owner = NULL;
      DISPOSE( factor );
   }
   factor_to_skill( skill, factor, FALSE );
}

void factor_to_skill( SKILLTYPE *skill, FACTOR_DATA *factor, bool Add )
{
   AFFECT_DATA *affect, *next_affect;
   int mod = factor->modifier;

   if( !Add )
      mod *= -1;

   switch( factor->factor_type )
   {
      case APPLY_FACTOR:
         if( Add )
         {
            CREATE( affect, AFFECT_DATA, 1 );
            affect->duration = factor->duration;
            affect->location = factor->location;
            affect->modifier = factor->modifier;
            affect->bitvector = factor->affect;
            affect->factor_src = factor;
            affect->apply_type = factor->apply_type;
            LINK( affect, skill->first_affect, skill->last_affect, next, prev );
            break;
         }
         else
         {
            for( affect = skill->first_affect; affect; affect = next_affect )
            {
               next_affect = affect->next;
               if( affect->factor_src == factor )
               {
                     UNLINK( affect, skill->first_affect, skill->last_affect, next, prev );
                     affect->from = NULL;
                     affect->factor_src = NULL;
                     DISPOSE( affect );
               }
            }
            break;
         }

      case STAT_FACTOR:
         skill->stat_boost += mod;
         break;
      case ATTACK_FACTOR:
         skill->attack_boost += mod;
         break;
      case DEFENSE_FACTOR:
         skill->defense_mod += mod;
         break;
      case BASEROLL_FACTOR:
         skill->base_roll_boost += mod;
         break;
   }
}

void update_skills( CHAR_DATA *ch )
{
   int x;

   for( x = 0; x < MAX_SKILL_SLOT; x++ )
      if( ch->skill_slots[x] != NULL )
         update_skill( ch, ch->skill_slots[x] );

   return;
}

void update_skill( CHAR_DATA *ch, SKILLTYPE *skill )
{
   int num_factors = get_num_factors( skill );
   int num_cost_type = get_num_cost_types( skill );
   int slot_level;
   int charge = skill->charge;

   if( ( slot_level = get_slot_level( ch, skill ) ) == -1 )
   {
      bug( "%s: bad slot level: %s", __FUNCTION__, skill->name );
      return;
   }

   /* Cooldowns First */

   switch( skill->type )
   {
      case SKILL_SKILL:
         skill->cooldown = (int)( ( ( slot_level / 5 ) * num_factors ) - ( charge / 2 ) );
         break;
      case SKILL_SPELL:
         skill->cooldown = (int)( ( ( slot_level / 10 ) * ( num_factors * 1.5 ) ) - ( charge * 3 ) );
         break;
   }

   /* Now Cost */
   if( xIS_SET( skill->cost, COST_HP ) )
   {
      switch( skill->type )
      {
         case SKILL_SKILL:
            skill->min_hp = (int)( ( slot_level * 2 ) / num_cost_type );
            break;
         case SKILL_SPELL:
            skill->min_hp = (int)( ( slot_level * 4 ) / ( num_cost_type * .9 ) );
            break;
      }
   }
   if( xIS_SET( skill->cost, COST_MANA ) )
   {
      switch( skill->type )
      {
         case SKILL_SKILL:
            skill->min_mana = (int)( ( slot_level * 3 ) / ( num_cost_type *.8 ) );
            break;
         case SKILL_SPELL:
            skill->min_mana = (int)( ( slot_level * 1.5 ) / ( num_cost_type * 1.2 ) );
            break;
      }
   }
   if( xIS_SET( skill->cost, COST_MOVE ) )
   {
      switch( skill->type )
      {
         case SKILL_SKILL:
            skill->min_move = (int)( ( slot_level * 1.5 ) / ( num_cost_type * 1.2 ) );
            break;
         case SKILL_SPELL:
            skill->min_move = (int)( ( slot_level * 3 ) / ( num_cost_type *.8 ) );
            break;
      }
   }

}

int get_slot_level( CHAR_DATA *ch, SKILLTYPE *skill )
{
   int x;

   if( !is_skill_set( ch, skill ) )
   {
      bug( "%s: trying to grab slot level of unset skill: %s", __FUNCTION__, skill->name );
      return 0;
   }

   for( x = 0; x < MAX_SKILL_SLOT; x++ )
      if( ch->skill_slots[x] == skill )
         return ( ( x + 1 ) * 5 );

   return -1;
}

int get_num_factors( SKILLTYPE *skill )
{
   FACTOR_DATA *factor;
   int count = 0;

   for( factor = skill->first_factor; factor; factor = factor->next )
      count++;

   return count;
}

int get_num_cost_types( SKILLTYPE *skill )
{
   int x, count;

   for( x = 0, count = 0; x < MAX_COST; x++ )
      if( xIS_SET( skill->cost, x ) )
         count++;

   return count;
}
