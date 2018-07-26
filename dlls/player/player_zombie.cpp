#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "gamerules.h"
#include "client.h"

void CBasePlayer::MakeZombie(ZombieLevel iEvolutionLevel)
{
	m_bIsZombie = true;
	m_bNotKilled = false;
	m_iZombieLevel = iEvolutionLevel;

	pev->body = 0;
	m_iModelName = iEvolutionLevel ? MODEL_ZOMBIE_ORIGIN : MODEL_ZOMBIE_HOST;

	const char *szModel = iEvolutionLevel ? "zombi_origin" : "zombi_host";
	SET_CLIENT_KEY_VALUE(entindex(), GET_INFO_BUFFER(edict()), "model", const_cast<char *>(szModel));

	static char szModelPath[64];
	Q_snprintf(szModelPath, sizeof(szModelPath), "models/player/%s/%s.mdl", szModel, szModel);
	SetNewPlayerModel(szModelPath);
	//this->m_modelIndexPlayer = MODEL_INDEX(szModelPath);
	//ClientUserInfoChanged


	UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Became_ZOMBIE\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()));

	// remove guns & give nvg
	GiveDefaultItems();
	m_bNightVisionOn = false;
	ClientCommand("nightvision");

	// set default property
	pev->health = 2000;
	pev->armortype = ARMOR_TYPE_HELMET;
	pev->armorvalue = 200;
	pev->gravity = 0.83f;
	ResetMaxSpeed();
}