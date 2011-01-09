#include "cbase.h"
#include "triggers.h"

#include "sdk_player.h"

class CTriggerFall : public CBaseTrigger
{
public:
	DECLARE_CLASS(CTriggerFall, CBaseTrigger);
	DECLARE_DATADESC();

	void Spawn();

	virtual void StartTouch(CBaseEntity *pOther);
};

LINK_ENTITY_TO_CLASS(trigger_fall, CTriggerFall);

BEGIN_DATADESC(CTriggerFall)
	DEFINE_ENTITYFUNC(StartTouch),
END_DATADESC()

void CTriggerFall::Spawn()
{
	BaseClass::Spawn();
	
	SetSolid(SOLID_VPHYSICS);
	VPhysicsInitShadow(false, false);
	SetModel(STRING(GetModelName()));
	SetMoveType(MOVETYPE_NONE);
	SetRenderMode(kRenderNone);
}

void CTriggerFall::StartTouch(CBaseEntity *pOther)
{
	DevMsg("FALL TRIGGER\n");
	auto pPlayer = ToSDKPlayer(pOther);
	if(pPlayer == 0)
		return;
	
	if(pPlayer->IsAlive() == false)
		return;
		
	pPlayer->SetHealth(0);
	pPlayer->Event_Killed(CTakeDamageInfo(pPlayer, pPlayer, 0, DMG_PREVENT_PHYSICS_FORCE | DMG_NEVERGIB, SDK_DMG_CUSTOM_SUICIDE));
	pPlayer->Event_Dying();
}
