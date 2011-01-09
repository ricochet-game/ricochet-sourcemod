#include "cbase.h"
#include "triggers.h"

ConVar trigger_jump_speed("trigger_jump_speed", "1");

class CTriggerJump : public CBaseTrigger
{
	const char *m_szTarget;
	float m_fHeight;
	int m_nIsPyramid;

	CBaseEntity *m_pTarget;

public:
	DECLARE_CLASS(CTriggerJump, CBaseTrigger);
	DECLARE_DATADESC();

	void Spawn();

	virtual void StartTouch(CBaseEntity *pOther);
};

LINK_ENTITY_TO_CLASS(trigger_jump, CTriggerJump);

BEGIN_DATADESC(CTriggerJump)
	DEFINE_ENTITYFUNC(StartTouch),

	DEFINE_KEYFIELD(m_szTarget, FIELD_STRING, "target"),
	DEFINE_KEYFIELD(m_fHeight, FIELD_FLOAT, "height"),
	DEFINE_KEYFIELD(m_nIsPyramid, FIELD_INTEGER, "ispyramid"),
END_DATADESC()

void CTriggerJump::Spawn()
{
	BaseClass::Spawn();
	
	SetSolid(SOLID_VPHYSICS);
	VPhysicsInitShadow(false, false);
	SetModel(STRING(GetModelName()));
	SetMoveType(MOVETYPE_NONE);
	SetRenderMode(kRenderNone);
}

void CTriggerJump::StartTouch(CBaseEntity *pOther)
{
	if(m_pTarget == 0)
	{
		m_pTarget = gEntList.FindEntityByName(0, m_szTarget);
		if(m_pTarget == 0)
			return;
	}

	if(pOther->IsPlayer() == true)
	{
		auto toTarget = m_pTarget->GetAbsOrigin() - pOther->GetAbsOrigin();

		toTarget = toTarget * 0.5f;
		toTarget.z = m_fHeight * 3.0f;

		/*Vector out;
		VMatrix mat;
		mat.Identity();
		MatrixRotate(mat, Vector(1.0f, 0.0f, 0.0f), 30.0f);
		VectorRotate(toTarget, mat.As3x4(), out);*/
		
		//VectorNormalizeFast(toTarget);
		DevMsg("toTarget: %f %f %f\n", toTarget.x, toTarget.y, toTarget.z);

		//toTarget = toTarget * trigger_jump_speed.GetFloat();

		pOther->SetAbsVelocity(Vector(0, 0, 0));
		pOther->SetBaseVelocity(toTarget * trigger_jump_speed.GetFloat());
	}
}
