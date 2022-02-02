#pragma once

struct tagBio4Config {

	DOUBLE dAspectR;
	FLOAT AspectRatio;
	DOUBLE InternalWidth;
	DOUBLE InternalHeight;

	UINT RefreshRate;

	FLOAT Znear;
	FLOAT Zfar;
	FLOAT OrthoT;
	FLOAT OrthoB;
	FLOAT OrthoL;
	FLOAT OrthoR;
	BYTE Vcount;

	BOOL NoDamage;
	BYTE AttacheSize;
	BYTE StartWeapon;
	BYTE StartHeal;
};
extern tagBio4Config Bio4Config;

VOID Bio4DmyConfig(VOID);
VOID Bio4OpenConfig(VOID);
VOID Bio4SaveConfig(VOID);