

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "player.h"
#include "gamerules.h"
#include "training_gamerules.h"
#include "hltv.h"
#include "game.h"
#include "trains.h"
#include "vehicle.h"
#include "globals.h"

#include "bot_include.h"

namespace sv {

// Move to the bomb on the floor and pick it up

void FetchBombState::OnEnter(CCSBot *me)
{
	me->DestroyPath();
}

// Move to the bomb on the floor and pick it up

void FetchBombState::OnUpdate(CCSBot *me)
{
	if (me->IsCarryingBomb())
	{
		me->PrintIfWatched( "I picked up the bomb\n" );
		me->Idle();
		return;
	}

	CBaseEntity *bomb = TheCSBots()->GetLooseBomb();
	if (bomb != NULL)
	{
		if (!me->HasPath())
		{
			// build a path to the bomb
			if (me->ComputePath(TheNavAreaGrid.GetNavArea(&bomb->pev->origin), &bomb->pev->origin, SAFEST_ROUTE) == false)
			{
				me->PrintIfWatched("Fetch bomb pathfind failed\n");

				// go Hunt instead of Idle to prevent continuous re-pathing to inaccessible bomb
				me->Hunt();
				//return;
			}
		}
	}
	else
	{
		// someone picked up the bomb
		me->PrintIfWatched("Bomb not loose\n");
		me->Idle();
		return;
	}

	// look around
	me->UpdateLookAround();

	if (me->UpdatePathMovement() != CCSBot::PROGRESSING)
		me->Idle();
}

}
