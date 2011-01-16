#include "cbase.h"
#include "triggers.h"

ConVar trigger_jump_speed("trigger_jump_speed", "800");

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
		auto height = toTarget.z;
		auto distance = (toTarget - Vector(0, 0, toTarget.z)).Length() + 50.0f;
		auto speed = trigger_jump_speed.GetFloat();
		auto gravity = cvar->FindVar("sv_gravity")->GetFloat();

		// calculate angle
		auto a = gravity*pow(distance, 2) + 2*height*pow(speed, 2);
		a = pow(speed, 2) + sqrt(pow(speed, 4) - a);
		a /= gravity * distance;
		a = atan(a);

		toTarget.z = 0;
		toTarget.NormalizeInPlace();
		auto rotVec = toTarget.Cross(Vector(0, 0, 1));

		Vector vel;
		VMatrix mat;
		mat.Identity();
		MatrixRotate(mat, rotVec, RAD2DEG(a));
		VectorRotate(toTarget, mat.As3x4(), vel);

		vel.NormalizeInPlace();
		vel = vel * speed;

		DevMsg("jump vel: %f %f %f\n", vel.x, vel.y, vel.z);

		pOther->SetGroundEntity(0);
		pOther->SetBaseVelocity(vel - pOther->GetAbsVelocity());
	}
}
