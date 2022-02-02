
#include "..\\dllmain.h"

UINT* DebugFlag = NULL;		// DebugFlag[4]
UINT* StopFlag = NULL;		// StopFlag[1]
UINT* StatusFlag = NULL;	// StatusFlag[4]
UINT* SystemFlag = NULL;	// SystemFlag[1]
UINT* ItemSetFlag = NULL;	// ItemSetFlag[8]
UINT* ScenarioFlag = NULL;	// ScenarioFlag[8]
UINT* KeyLockFlag = NULL;	// KeyLockFlag[8]
UINT* RoomFlag = NULL;		// RoomFlag[4]
UINT* RoomSaveFlag = NULL;	// RoomSaveFlag[1]
UINT* ExtraFlag = NULL;		// ExtraFlag[1]
UINT* ConfigFlag = NULL;	// ConfigFlag[1]
UINT* DisplayFlag = NULL;	// DisplayFlag[1]

VOID SetBit(UINT* Flag, UINT Bit, BOOL OnOff) {

	UINT* pFlag = (UINT*)(Flag + (Bit >> 5) * 4);
	UINT pBit = 0x80000000 >> ((UCHAR)Bit & 0x1F);
	if (OnOff == OFF) { *pFlag = *pFlag & ~pBit; }
	else { *pFlag = *pFlag | pBit; }

}
BOOL CkBit(UINT* Flag, UINT Bit) {
	return (0x80000000 >> ((byte)Bit & 0x1F) & *(UINT*)(Flag + (Bit >> 5) * 4)) != 0;
	//if ((*(UINT*)(Flag + (Bit >> 3 & 0x1FFFFFFC)) & 0x80000000 >> (Bit & 0x1F)) != 0) { return ON; }
	//return OFF;
}
VOID PrintDebugFlags(VOID) {
	OSReport("<<<<<<<	Debug		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(DBG_TEST_MODE), CkBit(DebugFlag, DBG_TEST_MODE));
	OSReport("%s: %d\n", FieldName(DBG_SCR_TEST), CkBit(DebugFlag, DBG_SCR_TEST));
	OSReport("%s: %d\n", FieldName(DBG_BACK_CLIP), CkBit(DebugFlag, DBG_BACK_CLIP));
	OSReport("%s: %d\n", FieldName(DBG_DBG_CAM), CkBit(DebugFlag, DBG_DBG_CAM));
	OSReport("%s: %d\n", FieldName(DBG_SAT_DISP), CkBit(DebugFlag, DBG_SAT_DISP));
	OSReport("%s: %d\n", FieldName(DBG_EAT_DISP), CkBit(DebugFlag, DBG_EAT_DISP));
	OSReport("%s: %d\n", FieldName(DBG_EVENT_TOOL), CkBit(DebugFlag, DBG_EVENT_TOOL));
	OSReport("%s: %d\n", FieldName(DBG_SLOW_ON), CkBit(DebugFlag, DBG_SLOW_ON));
	OSReport("%s: %d\n", FieldName(DBG_SHADOW_POLYGON), CkBit(DebugFlag, DBG_SHADOW_POLYGON));
	OSReport("%s: %d\n", FieldName(DBG_SCE_AT_DISP), CkBit(DebugFlag, DBG_SCE_AT_DISP));
	OSReport("%s: %d\n", FieldName(DBG_SCR2_TEST), CkBit(DebugFlag, DBG_SCR2_TEST));
	OSReport("%s: %d\n", FieldName(DBG_SHADOW_FRAME), CkBit(DebugFlag, DBG_SHADOW_FRAME));
	OSReport("%s: %d\n", FieldName(DBG_MIRROR_POLYGON), CkBit(DebugFlag, DBG_MIRROR_POLYGON));
	OSReport("%s: %d\n", FieldName(DBG_GROUND_DISP), CkBit(DebugFlag, DBG_GROUND_DISP));
	OSReport("%s: %d\n", FieldName(DBG_SKELETON_DISP), CkBit(DebugFlag, DBG_SKELETON_DISP));
	OSReport("%s: %d\n", FieldName(DBG_ESPTOOL_ONSCR), CkBit(DebugFlag, DBG_ESPTOOL_ONSCR));
	OSReport("%s: %d\n", FieldName(DBG_CINESCO_OFF), CkBit(DebugFlag, DBG_CINESCO_OFF));
	OSReport("%s: %d\n", FieldName(DBG_RTP_DISP), CkBit(DebugFlag, DBG_RTP_DISP));
	OSReport("%s: %d\n", FieldName(DBG_ROOM_WIRE_DISP), CkBit(DebugFlag, DBG_ROOM_WIRE_DISP));
	OSReport("%s: %d\n", FieldName(DBG_EM_YARARE_DISP), CkBit(DebugFlag, DBG_EM_YARARE_DISP));
	OSReport("%s: %d\n", FieldName(DBG_CAM_AREA_OFF), CkBit(DebugFlag, DBG_CAM_AREA_OFF));
	OSReport("%s: %d\n", FieldName(DBG_CLOTH_AT_DISP), CkBit(DebugFlag, DBG_CLOTH_AT_DISP));
	OSReport("%s: %d\n", FieldName(DBG_16), CkBit(DebugFlag, DBG_16));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_ESPTOOL_MEM_USE), CkBit(DebugFlag, DBG_ESPTOOL_MEM_USE));
	OSReport("%s: %d\n", FieldName(DBG_TEX_RENDER_ALL), CkBit(DebugFlag, DBG_TEX_RENDER_ALL));
	OSReport("%s: %d\n", FieldName(DBG_ESPTOOL_ONEM), CkBit(DebugFlag, DBG_ESPTOOL_ONEM));
	OSReport("%s: %d\n", FieldName(DBG_EMINFO_DISP), CkBit(DebugFlag, DBG_EMINFO_DISP));
	OSReport("%s: %d\n", FieldName(DBG_LIGHT_TOOL), CkBit(DebugFlag, DBG_LIGHT_TOOL));
	OSReport("%s: %d\n", FieldName(DBG_EM_COUNT), CkBit(DebugFlag, DBG_EM_COUNT));
	OSReport("%s: %d\n", FieldName(DBG_1D), CkBit(DebugFlag, DBG_1D));	// UNUSED
	OSReport("%s: %d\n", FieldName(EM3F_ADA_SADLER_DEBUG), CkBit(DebugFlag, EM3F_ADA_SADLER_DEBUG));
	OSReport("%s: %d\n", FieldName(DBG_CAM_ANTIGRO_OFF), CkBit(DebugFlag, DBG_CAM_ANTIGRO_OFF));
	OSReport("%s: %d\n", FieldName(DBG_COCKPIT_TOOL), CkBit(DebugFlag, DBG_COCKPIT_TOOL));
	OSReport("%s: %d\n", FieldName(DBG_BOUNDING_DISP), CkBit(DebugFlag, DBG_BOUNDING_DISP));
	OSReport("%s: %d\n", FieldName(DBG_ADJUST_CAM), CkBit(DebugFlag, DBG_ADJUST_CAM));
	OSReport("%s: %d\n", FieldName(DBG_FLAT_FLOOR), CkBit(DebugFlag, DBG_FLAT_FLOOR));
	OSReport("%s: %d\n", FieldName(DBG_OBJ_SKELETON_), CkBit(DebugFlag, DBG_OBJ_SKELETON_));
	OSReport("%s: %d\n", FieldName(DBG_DRAW_SH_TEX), CkBit(DebugFlag, DBG_DRAW_SH_TEX));
	OSReport("%s: %d\n", FieldName(DBG_EM_NO_ATK), CkBit(DebugFlag, DBG_EM_NO_ATK));
	OSReport("%s: %d\n", FieldName(DBG_NO_EST_CALL), CkBit(DebugFlag, DBG_NO_EST_CALL));
	OSReport("%s: %d\n", FieldName(DBG_IN_ESP_TOOL), CkBit(DebugFlag, DBG_IN_ESP_TOOL));
	OSReport("%s: %d\n", FieldName(DBG_TERM_TOOL), CkBit(DebugFlag, DBG_TERM_TOOL));
	OSReport("%s: %d\n", FieldName(DBG_WARN_LEVEL_LOW), CkBit(DebugFlag, DBG_WARN_LEVEL_LOW));
	OSReport("%s: %d\n", FieldName(DBG_2B), CkBit(DebugFlag, DBG_2B));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_2C), CkBit(DebugFlag, DBG_2C));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_2D), CkBit(DebugFlag, DBG_2D));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_2E), CkBit(DebugFlag, DBG_2E));	// UNUSED
	OSReport("%s: %d\n", FieldName(DGG_TIMER_STOP), CkBit(DebugFlag, DGG_TIMER_STOP));
	OSReport("%s: %d\n", FieldName(DBG_SCREEN_SHOT), CkBit(DebugFlag, DBG_SCREEN_SHOT));
	OSReport("%s: %d\n", FieldName(DBG_SERIES_SHOT), CkBit(DebugFlag, DBG_SERIES_SHOT));
	OSReport("%s: %d\n", FieldName(DBG_ASHLEY_NO_CATCH), CkBit(DebugFlag, DBG_ASHLEY_NO_CATCH));
	OSReport("%s: %d\n", FieldName(DBG_RENSYA), CkBit(DebugFlag, DBG_RENSYA));
	OSReport("%s: %d\n", FieldName(DBG_CERO), CkBit(DebugFlag, DBG_CERO));
	OSReport("%s: %d\n", FieldName(DBG_35), CkBit(DebugFlag, DBG_35));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_36), CkBit(DebugFlag, DBG_36));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_37), CkBit(DebugFlag, DBG_37));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_Wii_PAD), CkBit(DebugFlag, DBG_Wii_PAD));
	OSReport("%s: %d\n", FieldName(DBG_39), CkBit(DebugFlag, DBG_39));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3A), CkBit(DebugFlag, DBG_3A));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3B), CkBit(DebugFlag, DBG_3B));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3C), CkBit(DebugFlag, DBG_3C));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3D), CkBit(DebugFlag, DBG_3D));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3E), CkBit(DebugFlag, DBG_3E));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_3F), CkBit(DebugFlag, DBG_3F));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_ROOMJMP), CkBit(DebugFlag, DBG_ROOMJMP));
	OSReport("%s: %d\n", FieldName(DBG_PROC_BAR), CkBit(DebugFlag, DBG_PROC_BAR));
	OSReport("%s: %d\n", FieldName(DBG_SCA_VIEW), CkBit(DebugFlag, DBG_SCA_VIEW));
	OSReport("%s: %d\n", FieldName(DBG_OBA_VIEW), CkBit(DebugFlag, DBG_OBA_VIEW));
	OSReport("%s: %d\n", FieldName(DBG_SLOW_MODE), CkBit(DebugFlag, DBG_SLOW_MODE));
	OSReport("%s: %d\n", FieldName(DBG_NO_SCE_EXE), CkBit(DebugFlag, DBG_NO_SCE_EXE));
	OSReport("%s: %d\n", FieldName(DBG_SINGLE_DISK), CkBit(DebugFlag, DBG_SINGLE_DISK));
	OSReport("%s: %d\n", FieldName(DBG_BUGCHECK_MODE), CkBit(DebugFlag, DBG_BUGCHECK_MODE));
	OSReport("%s: %d\n", FieldName(DBG_NO_DEATH), CkBit(DebugFlag, DBG_NO_DEATH));
	OSReport("%s: %d\n", FieldName(DBG_INF_BULLET), CkBit(DebugFlag, DBG_INF_BULLET));
	OSReport("%s: %d\n", FieldName(DBG_NO_ENEMY), CkBit(DebugFlag, DBG_NO_ENEMY));
	OSReport("%s: %d\n", FieldName(DBG_BGM_STOP), CkBit(DebugFlag, DBG_BGM_STOP));
	OSReport("%s: %d\n", FieldName(DBG_SE_STOP), CkBit(DebugFlag, DBG_SE_STOP));
	OSReport("%s: %d\n", FieldName(DBG_PL_LOCK_FOLLOW), CkBit(DebugFlag, DBG_PL_LOCK_FOLLOW));
	OSReport("%s: %d\n", FieldName(DBG_EM_NO_DEATH), CkBit(DebugFlag, DBG_EM_NO_DEATH));
	OSReport("%s: %d\n", FieldName(DBG_KAIOUKEN), CkBit(DebugFlag, DBG_KAIOUKEN));
	OSReport("%s: %d\n", FieldName(DBG_PAD_INFO), CkBit(DebugFlag, DBG_PAD_INFO));
	OSReport("%s: %d\n", FieldName(DBG_UNDER_CONST), CkBit(DebugFlag, DBG_UNDER_CONST));
	OSReport("%s: %d\n", FieldName(DBG_EM_WEAK), CkBit(DebugFlag, DBG_EM_WEAK));
	OSReport("%s: %d\n", FieldName(DBG_EM_LIFE_DISP), CkBit(DebugFlag, DBG_EM_LIFE_DISP));
	OSReport("%s: %d\n", FieldName(DBG_SHADOW_LIGHT), CkBit(DebugFlag, DBG_SHADOW_LIGHT));
	OSReport("%s: %d\n", FieldName(DBG_CAPTION_OFF), CkBit(DebugFlag, DBG_CAPTION_OFF));
	OSReport("%s: %d\n", FieldName(DBG_TEST_MODE_CK), CkBit(DebugFlag, DBG_TEST_MODE_CK));
	OSReport("%s: %d\n", FieldName(DBG_LIGHT_ERR_CHECK), CkBit(DebugFlag, DBG_LIGHT_ERR_CHECK));
	OSReport("%s: %d\n", FieldName(DBG_EST_CALL_CHK), CkBit(DebugFlag, DBG_EST_CALL_CHK));
	OSReport("%s: %d\n", FieldName(DBG_GX_WARN_ALL), CkBit(DebugFlag, DBG_GX_WARN_ALL));
	OSReport("%s: %d\n", FieldName(DBG_GX_WARN_MIDIUM), CkBit(DebugFlag, DBG_GX_WARN_MIDIUM));
	OSReport("%s: %d\n", FieldName(DBG_GX_WARN_SEVERE), CkBit(DebugFlag, DBG_GX_WARN_SEVERE));
	OSReport("%s: %d\n", FieldName(DBG_PL_NOHIT), CkBit(DebugFlag, DBG_PL_NOHIT));
	OSReport("%s: %d\n", FieldName(DBG_SE_ERR_ALL), CkBit(DebugFlag, DBG_SE_ERR_ALL));
	OSReport("%s: %d\n", FieldName(DBG_QUICK_EM_STOP), CkBit(DebugFlag, DBG_QUICK_EM_STOP));
	OSReport("%s: %d\n", FieldName(DBG_AV_TEST), CkBit(DebugFlag, DBG_AV_TEST));
	OSReport("%s: %d\n", FieldName(DBG_INF_BULLET2), CkBit(DebugFlag, DBG_INF_BULLET2));
	OSReport("%s: %d\n", FieldName(DBG_BATTLE_CAM), CkBit(DebugFlag, DBG_BATTLE_CAM));
	OSReport("%s: %d\n", FieldName(DBG_PL_KLAUSER), CkBit(DebugFlag, DBG_PL_KLAUSER));
	OSReport("%s: %d\n", FieldName(DBG_MAP_ZOOM_ORG), CkBit(DebugFlag, DBG_MAP_ZOOM_ORG));
	OSReport("%s: %d\n", FieldName(DBG_SCISSOR_OFF), CkBit(DebugFlag, DBG_SCISSOR_OFF));
	OSReport("%s: %d\n", FieldName(DBG_LOG_OFF), CkBit(DebugFlag, DBG_LOG_OFF));
	OSReport("%s: %d\n", FieldName(DBG_SCR_CHECK), CkBit(DebugFlag, DBG_SCR_CHECK));
	OSReport("%s: %d\n", FieldName(DBG_OBJ_SERVER), CkBit(DebugFlag, DBG_OBJ_SERVER));
	OSReport("%s: %d\n", FieldName(DBG_START_ST2), CkBit(DebugFlag, DBG_START_ST2));
	OSReport("%s: %d\n", FieldName(DBG_ERRORL_CK), CkBit(DebugFlag, DBG_ERRORL_CK));
	OSReport("%s: %d\n", FieldName(DBG_APP_USE_DBMEM), CkBit(DebugFlag, DBG_APP_USE_DBMEM));
	OSReport("%s: %d\n", FieldName(DBG_REFRACT_CK), CkBit(DebugFlag, DBG_REFRACT_CK));
	OSReport("%s: %d\n", FieldName(DBG_EM_NO_DIE_FLAG), CkBit(DebugFlag, DBG_EM_NO_DIE_FLAG));
	OSReport("%s: %d\n", FieldName(DBG_START_ST3), CkBit(DebugFlag, DBG_START_ST3));
	OSReport("%s: %d\n", FieldName(DBG_6E), CkBit(DebugFlag, DBG_6E));
	OSReport("%s: %d\n", FieldName(DBG_DOOR_SET_MODE), CkBit(DebugFlag, DBG_DOOR_SET_MODE));
	OSReport("%s: %d\n", FieldName(DBG_EFF_NUM_DISP), CkBit(DebugFlag, DBG_EFF_NUM_DISP));
	OSReport("%s: %d\n", FieldName(DBG_SET_HITMARK_ALL), CkBit(DebugFlag, DBG_SET_HITMARK_ALL));
	OSReport("%s: %d\n", FieldName(DBG_FOG_FAR_GREEN), CkBit(DebugFlag, DBG_FOG_FAR_GREEN));
	OSReport("%s: %d\n", FieldName(DBG_SSCRN_PROC_BAR), CkBit(DebugFlag, DBG_SSCRN_PROC_BAR));
	OSReport("%s: %d\n", FieldName(DBG_NO_ETC_SET), CkBit(DebugFlag, DBG_NO_ETC_SET));
	OSReport("%s: %d\n", FieldName(DBG_NO_DEATH2), CkBit(DebugFlag, DBG_NO_DEATH2));
	OSReport("%s: %d\n", FieldName(DBG_NO_PARASITE), CkBit(DebugFlag, DBG_NO_PARASITE));
	OSReport("%s: %d\n", FieldName(DBG_ESP_CHK), CkBit(DebugFlag, DBG_ESP_CHK));
	OSReport("%s: %d\n", FieldName(DBG_NO_EVENT), CkBit(DebugFlag, DBG_NO_EVENT));
	OSReport("%s: %d\n", FieldName(DBG_NO_LASER_LINE), CkBit(DebugFlag, DBG_NO_LASER_LINE));
	OSReport("%s: %d\n", FieldName(DBG_7A), CkBit(DebugFlag, DBG_7A));	// UNUSED
	OSReport("%s: %d\n", FieldName(DBG_SHOP_FULL), CkBit(DebugFlag, DBG_SHOP_FULL));
	OSReport("%s: %d\n", FieldName(DBG_ADA_OMAKE_EV), CkBit(DebugFlag, DBG_ADA_OMAKE_EV));
	OSReport("%s: %d\n", FieldName(DBG_FOG_FAR_COLOR), CkBit(DebugFlag, DBG_FOG_FAR_COLOR));
	OSReport("%s: %d\n", FieldName(DBG_TOOL_EMINFO_DISP), CkBit(DebugFlag, DBG_TOOL_EMINFO_DISP));
	OSReport("%s: %d\n", FieldName(DBG_7F), CkBit(DebugFlag, DBG_7F));
}
VOID PrintStopFlags(VOID) {
	OSReport("<<<<<<<	Stop		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(SPF_KEY), CkBit(StopFlag, SPF_KEY));
	OSReport("%s: %d\n", FieldName(SPF_CAMERA), CkBit(StopFlag, SPF_CAMERA));
	OSReport("%s: %d\n", FieldName(SPF_EM), CkBit(StopFlag, SPF_EM));
	OSReport("%s: %d\n", FieldName(SPF_PL), CkBit(StopFlag, SPF_PL));
	OSReport("%s: %d\n", FieldName(SPF_ESP), CkBit(StopFlag, SPF_ESP));
	OSReport("%s: %d\n", FieldName(SPF_OBJ), CkBit(StopFlag, SPF_OBJ));
	OSReport("%s: %d\n", FieldName(SPF_CTRL), CkBit(StopFlag, SPF_CTRL));
	OSReport("%s: %d\n", FieldName(SPF_LIGHT), CkBit(StopFlag, SPF_LIGHT));
	OSReport("%s: %d\n", FieldName(SPF_SCE), CkBit(StopFlag, SPF_SCE));
	OSReport("%s: %d\n", FieldName(SPF_SCE_AT), CkBit(StopFlag, SPF_SCE_AT));
	OSReport("%s: %d\n", FieldName(SPF_CCHG), CkBit(StopFlag, SPF_CCHG));
	OSReport("%s: %d\n", FieldName(SPF_PL_CCHG), CkBit(StopFlag, SPF_PL_CCHG));
	OSReport("%s: %d\n", FieldName(SPF_NOTSUBSCR), CkBit(StopFlag, SPF_NOTSUBSCR));
	OSReport("%s: %d\n", FieldName(SPF_WATER), CkBit(StopFlag, SPF_WATER));
	OSReport("%s: %d\n", FieldName(SPF_SPECULAR), CkBit(StopFlag, SPF_SPECULAR));
	OSReport("%s: %d\n", FieldName(SPF_EARTHQUAKE), CkBit(StopFlag, SPF_EARTHQUAKE));
	OSReport("%s: %d\n", FieldName(SPF_VIBRATION), CkBit(StopFlag, SPF_VIBRATION));
	OSReport("%s: %d\n", FieldName(SPF_CINESCO), CkBit(StopFlag, SPF_CINESCO));
	OSReport("%s: %d\n", FieldName(SPF_MIST), CkBit(StopFlag, SPF_MIST));
	OSReport("%s: %d\n", FieldName(SPF_SUBCHAR), CkBit(StopFlag, SPF_SUBCHAR));
	OSReport("%s: %d\n", FieldName(SPF_SE), CkBit(StopFlag, SPF_SE));
	OSReport("%s: %d\n", FieldName(SPF_EVT), CkBit(StopFlag, SPF_EVT));
	OSReport("%s: %d\n", FieldName(SPF_BLOCK), CkBit(StopFlag, SPF_BLOCK));
	OSReport("%s: %d\n", FieldName(SPF_ACTBTN), CkBit(StopFlag, SPF_ACTBTN));
	OSReport("%s: %d\n", FieldName(SPF_DATAREAD_AT), CkBit(StopFlag, SPF_DATAREAD_AT));
	OSReport("%s: %d\n", FieldName(SPF_ID_SYSTEM), CkBit(StopFlag, SPF_ID_SYSTEM));
	OSReport("%s: %d\n", FieldName(SPF_ESP_AREA), CkBit(StopFlag, SPF_ESP_AREA));
	OSReport("%s: %d\n", FieldName(SPF_1B), CkBit(StopFlag, SPF_1B));
	OSReport("%s: %d\n", FieldName(SPF_1C), CkBit(StopFlag, SPF_1C));
	OSReport("%s: %d\n", FieldName(SPF_1D), CkBit(StopFlag, SPF_1D));
	OSReport("%s: %d\n", FieldName(SPF_1E), CkBit(StopFlag, SPF_1E));
	OSReport("%s: %d\n", FieldName(SPF_1F), CkBit(StopFlag, SPF_1F));
}
VOID PrintStatusFlags(VOID) {
	OSReport("<<<<<<<	Status		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(STA_BG_OFF), CkBit(StatusFlag, STA_BG_OFF));
	OSReport("%s: %d\n", FieldName(STA_PL_CHECK), CkBit(StatusFlag, STA_PL_CHECK));
	OSReport("%s: %d\n", FieldName(STA_PL_CHECK2), CkBit(StatusFlag, STA_PL_CHECK2));
	OSReport("%s: %d\n", FieldName(STA_MOVIE_ON), CkBit(StatusFlag, STA_MOVIE_ON));
	OSReport("%s: %d\n", FieldName(STA_CUTCHG), CkBit(StatusFlag, STA_CUTCHG));
	OSReport("%s: %d\n", FieldName(STA_MOVIE2_ON), CkBit(StatusFlag, STA_MOVIE2_ON));
	OSReport("%s: %d\n", FieldName(STA_SSCRN_ENABLE), CkBit(StatusFlag, STA_SSCRN_ENABLE));
	OSReport("%s: %d\n", FieldName(STA_CINESCO), CkBit(StatusFlag, STA_CINESCO));
	OSReport("%s: %d\n", FieldName(STA_PL_FIRE), CkBit(StatusFlag, STA_PL_FIRE));
	OSReport("%s: %d\n", FieldName(STA_09), CkBit(StatusFlag, STA_09));
	OSReport("%s: %d\n", FieldName(STA_ACT_DONT_FIRE), CkBit(StatusFlag, STA_ACT_DONT_FIRE));
	OSReport("%s: %d\n", FieldName(STA_DIEDEMO), CkBit(StatusFlag, STA_DIEDEMO));
	OSReport("%s: %d\n", FieldName(STA_BLUR), CkBit(StatusFlag, STA_BLUR));
	OSReport("%s: %d\n", FieldName(STA_SUB_SCRN), CkBit(StatusFlag, STA_SUB_SCRN));
	OSReport("%s: %d\n", FieldName(STA_SHOOTING), CkBit(StatusFlag, STA_SHOOTING));
	OSReport("%s: %d\n", FieldName(STA_PAD_SENSITIVE), CkBit(StatusFlag, STA_PAD_SENSITIVE));
	OSReport("%s: %d\n", FieldName(STA_10), CkBit(StatusFlag, STA_10));
	OSReport("%s: %d\n", FieldName(STA_PL_ACTION), CkBit(StatusFlag, STA_PL_ACTION));
	OSReport("%s: %d\n", FieldName(STA_PL_INVISIBLE), CkBit(StatusFlag, STA_PL_INVISIBLE));
	OSReport("%s: %d\n", FieldName(STA_EVENT), CkBit(StatusFlag, STA_EVENT));
	OSReport("%s: %d\n", FieldName(STA_ASHLEY_HIDE), CkBit(StatusFlag, STA_ASHLEY_HIDE));
	OSReport("%s: %d\n", FieldName(STA_CAM_SHOULDER), CkBit(StatusFlag, STA_CAM_SHOULDER));
	OSReport("%s: %d\n", FieldName(STA_WATER_ALIVE), CkBit(StatusFlag, STA_WATER_ALIVE));
	OSReport("%s: %d\n", FieldName(STA_CAMERA), CkBit(StatusFlag, STA_CAMERA));
	OSReport("%s: %d\n", FieldName(STA_BLACKOUT), CkBit(StatusFlag, STA_BLACKOUT));
	OSReport("%s: %d\n", FieldName(STA_SCOPE_CAMERA), CkBit(StatusFlag, STA_SCOPE_CAMERA));
	OSReport("%s: %d\n", FieldName(STA_RIDE_GONDOLA), CkBit(StatusFlag, STA_RIDE_GONDOLA));
	OSReport("%s: %d\n", FieldName(STA_WIND_ON), CkBit(StatusFlag, STA_WIND_ON));
	OSReport("%s: %d\n", FieldName(STA_PL_JUMP_OFF), CkBit(StatusFlag, STA_PL_JUMP_OFF));
	OSReport("%s: %d\n", FieldName(STA_MIRROR), CkBit(StatusFlag, STA_MIRROR));
	OSReport("%s: %d\n", FieldName(STA_SAND_ALIVE), CkBit(StatusFlag, STA_SAND_ALIVE));
	OSReport("%s: %d\n", FieldName(STA_SELF_SHADOW), CkBit(StatusFlag, STA_SELF_SHADOW));
	OSReport("%s: %d\n", FieldName(STA_PL_SE_FOOT), CkBit(StatusFlag, STA_PL_SE_FOOT));
	OSReport("%s: %d\n", FieldName(STA_PL_SE_WHISTLE), CkBit(StatusFlag, STA_PL_SE_WHISTLE));
	OSReport("%s: %d\n", FieldName(STA_SE_BURST), CkBit(StatusFlag, STA_SE_BURST));
	OSReport("%s: %d\n", FieldName(STA_SUSPEND), CkBit(StatusFlag, STA_SUSPEND));
	OSReport("%s: %d\n", FieldName(STA_TEX_RENDER), CkBit(StatusFlag, STA_TEX_RENDER));
	OSReport("%s: %d\n", FieldName(STA_THERMO_GRAPH), CkBit(StatusFlag, STA_THERMO_GRAPH));
	OSReport("%s: %d\n", FieldName(STA_CAMERA_IN_ROOM), CkBit(StatusFlag, STA_CAMERA_IN_ROOM));
	OSReport("%s: %d\n", FieldName(STA_NO_LIGHTMASK), CkBit(StatusFlag, STA_NO_LIGHTMASK));
	OSReport("%s: %d\n", FieldName(STA_PL_SPEAR_SET), CkBit(StatusFlag, STA_PL_SPEAR_SET));
	OSReport("%s: %d\n", FieldName(STA_PL_SWIM), CkBit(StatusFlag, STA_PL_SWIM));
	OSReport("%s: %d\n", FieldName(STA_PL_BOAT), CkBit(StatusFlag, STA_PL_BOAT));
	OSReport("%s: %d\n", FieldName(STA_WATER_CAMERA), CkBit(StatusFlag, STA_WATER_CAMERA));
	OSReport("%s: %d\n", FieldName(STA_PL_SWIM_CAMERA), CkBit(StatusFlag, STA_PL_SWIM_CAMERA));
	OSReport("%s: %d\n", FieldName(STA_PL_LADDER), CkBit(StatusFlag, STA_PL_LADDER));
	OSReport("%s: %d\n", FieldName(STA_CRITICAL), CkBit(StatusFlag, STA_CRITICAL));
	OSReport("%s: %d\n", FieldName(STA_TAKEAWAY), CkBit(StatusFlag, STA_TAKEAWAY));
	OSReport("%s: %d\n", FieldName(STA_PL_CATCHED), CkBit(StatusFlag, STA_PL_CATCHED));
	OSReport("%s: %d\n", FieldName(STA_SHADOW_EQCOL), CkBit(StatusFlag, STA_SHADOW_EQCOL));
	OSReport("%s: %d\n", FieldName(STA_PL_CATCHHOLD), CkBit(StatusFlag, STA_PL_CATCHHOLD));
	OSReport("%s: %d\n", FieldName(STA_NEARCLIP_TOUCH), CkBit(StatusFlag, STA_NEARCLIP_TOUCH));
	OSReport("%s: %d\n", FieldName(STA_CAMERA_SET_ROOM), CkBit(StatusFlag, STA_CAMERA_SET_ROOM));
	OSReport("%s: %d\n", FieldName(STA_ROOM_RAIN), CkBit(StatusFlag, STA_ROOM_RAIN));
	OSReport("%s: %d\n", FieldName(STA_USE_CAST_SHADOW), CkBit(StatusFlag, STA_USE_CAST_SHADOW));
	OSReport("%s: %d\n", FieldName(STA_PROC_SHD_TEX), CkBit(StatusFlag, STA_PROC_SHD_TEX));
	OSReport("%s: %d\n", FieldName(STA_ALPHA_DRAW2), CkBit(StatusFlag, STA_ALPHA_DRAW2));
	OSReport("%s: %d\n", FieldName(STA_SET_BG_COLOR), CkBit(StatusFlag, STA_SET_BG_COLOR));
	OSReport("%s: %d\n", FieldName(STA_ESPGEN45_SET), CkBit(StatusFlag, STA_ESPGEN45_SET));
	OSReport("%s: %d\n", FieldName(STA_EFFEM2D_TEXRND), CkBit(StatusFlag, STA_EFFEM2D_TEXRND));
	OSReport("%s: %d\n", FieldName(STA_SUB_LADDER), CkBit(StatusFlag, STA_SUB_LADDER));
	OSReport("%s: %d\n", FieldName(STA_SUBCHAR_CTRL), CkBit(StatusFlag, STA_SUBCHAR_CTRL));
	OSReport("%s: %d\n", FieldName(STA_ITEM_GET), CkBit(StatusFlag, STA_ITEM_GET));
	OSReport("%s: %d\n", FieldName(STA_LASERSITE_NOADD), CkBit(StatusFlag, STA_LASERSITE_NOADD));
	OSReport("%s: %d\n", FieldName(STA_PL_DONT_FIRE), CkBit(StatusFlag, STA_PL_DONT_FIRE));
	OSReport("%s: %d\n", FieldName(STA_PL_EM_ACTION), CkBit(StatusFlag, STA_PL_EM_ACTION));
	OSReport("%s: %d\n", FieldName(STA_SUB_CATCHED), CkBit(StatusFlag, STA_SUB_CATCHED));
	OSReport("%s: %d\n", FieldName(STA_CUT_CHANGE), CkBit(StatusFlag, STA_CUT_CHANGE));
	OSReport("%s: %d\n", FieldName(STA_NO_FENCE), CkBit(StatusFlag, STA_NO_FENCE));
	OSReport("%s: %d\n", FieldName(STA_SSCRN_REQUEST), CkBit(StatusFlag, STA_SSCRN_REQUEST));
	OSReport("%s: %d\n", FieldName(STA_ESP_COMPULSION_NOSUSPEND), CkBit(StatusFlag, STA_ESP_COMPULSION_NOSUSPEND));
	OSReport("%s: %d\n", FieldName(STA_PL_MISS_SHOT), CkBit(StatusFlag, STA_PL_MISS_SHOT));
	OSReport("%s: %d\n", FieldName(STA_SUB_BULLDOZER), CkBit(StatusFlag, STA_SUB_BULLDOZER));
	OSReport("%s: %d\n", FieldName(STA_LIT_NO_UPDATE), CkBit(StatusFlag, STA_LIT_NO_UPDATE));
	OSReport("%s: %d\n", FieldName(STA_MAP_DISABLE), CkBit(StatusFlag, STA_MAP_DISABLE));
	OSReport("%s: %d\n", FieldName(STA_USE_SHADOW_LIGHT), CkBit(StatusFlag, STA_USE_SHADOW_LIGHT));
	OSReport("%s: %d\n", FieldName(STA_EVENT_SYSYTEM), CkBit(StatusFlag, STA_EVENT_SYSYTEM));
	OSReport("%s: %d\n", FieldName(STA_INTO_SHOP), CkBit(StatusFlag, STA_INTO_SHOP));
	OSReport("%s: %d\n", FieldName(STA_TIMER_NO_PAUSE), CkBit(StatusFlag, STA_TIMER_NO_PAUSE));
	OSReport("%s: %d\n", FieldName(STA_EFFAREA_USE_CAM), CkBit(StatusFlag, STA_EFFAREA_USE_CAM));
	OSReport("%s: %d\n", FieldName(STA_TITLE), CkBit(StatusFlag, STA_TITLE));
	OSReport("%s: %d\n", FieldName(STA_MAP_CK_UNLIMIT), CkBit(StatusFlag, STA_MAP_CK_UNLIMIT));
	OSReport("%s: %d\n", FieldName(STA_RIFLE_READY), CkBit(StatusFlag, STA_RIFLE_READY));
	OSReport("%s: %d\n", FieldName(STA_LOWPOLY_USE), CkBit(StatusFlag, STA_LOWPOLY_USE));
	OSReport("%s: %d\n", FieldName(STA_TERMINAL), CkBit(StatusFlag, STA_TERMINAL));
	OSReport("%s: %d\n", FieldName(STA_HIGH_TEMPERATURE_THERMO), CkBit(StatusFlag, STA_HIGH_TEMPERATURE_THERMO));
	OSReport("%s: %d\n", FieldName(STA_56), CkBit(StatusFlag, STA_56));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_57), CkBit(StatusFlag, STA_57));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_58), CkBit(StatusFlag, STA_58));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_59), CkBit(StatusFlag, STA_59));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5A), CkBit(StatusFlag, STA_5A));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5B), CkBit(StatusFlag, STA_5B));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5C), CkBit(StatusFlag, STA_5C));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5D), CkBit(StatusFlag, STA_5D));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5E), CkBit(StatusFlag, STA_5E));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_5F), CkBit(StatusFlag, STA_5F));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_SAVEDATA_NO_UPDATE), CkBit(StatusFlag, STA_SAVEDATA_NO_UPDATE));
	OSReport("%s: %d\n", FieldName(STA_BEHIND_CAM), CkBit(StatusFlag, STA_BEHIND_CAM));
	OSReport("%s: %d\n", FieldName(STA_62), CkBit(StatusFlag, STA_62));
	OSReport("%s: %d\n", FieldName(STA_SCISSOR), CkBit(StatusFlag, STA_SCISSOR));
	OSReport("%s: %d\n", FieldName(STA_SLOW), CkBit(StatusFlag, STA_SLOW));
	OSReport("%s: %d\n", FieldName(STA_SUB_ASHLEY), CkBit(StatusFlag, STA_SUB_ASHLEY));
	OSReport("%s: %d\n", FieldName(STA_BIG_MARKER), CkBit(StatusFlag, STA_BIG_MARKER));
	OSReport("%s: %d\n", FieldName(STA_67), CkBit(StatusFlag, STA_67));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_KLAUSER_TRANSFORM), CkBit(StatusFlag, STA_KLAUSER_TRANSFORM));
	OSReport("%s: %d\n", FieldName(STA_69), CkBit(StatusFlag, STA_69));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6A), CkBit(StatusFlag, STA_6A));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6B), CkBit(StatusFlag, STA_6B));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6C), CkBit(StatusFlag, STA_6C));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6D), CkBit(StatusFlag, STA_6D));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6E), CkBit(StatusFlag, STA_6E));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_6F), CkBit(StatusFlag, STA_6F));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_70), CkBit(StatusFlag, STA_70));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_71), CkBit(StatusFlag, STA_71));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_72), CkBit(StatusFlag, STA_72));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_SCREEN_STOP_RESERVE), CkBit(StatusFlag, STA_SCREEN_STOP_RESERVE));
	OSReport("%s: %d\n", FieldName(STA_TYPEWRITER), CkBit(StatusFlag, STA_TYPEWRITER));
	OSReport("%s: %d\n", FieldName(STA_75), CkBit(StatusFlag, STA_75));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_76), CkBit(StatusFlag, STA_76));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_77), CkBit(StatusFlag, STA_77));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_78), CkBit(StatusFlag, STA_78));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_79), CkBit(StatusFlag, STA_79));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7A), CkBit(StatusFlag, STA_7A));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7B), CkBit(StatusFlag, STA_7B));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7C), CkBit(StatusFlag, STA_7C));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7D), CkBit(StatusFlag, STA_7D));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7E), CkBit(StatusFlag, STA_7E));	// UNUSED
	OSReport("%s: %d\n", FieldName(STA_7F), CkBit(StatusFlag, STA_7F));	// UNUSED
}
VOID PrintSystemFlags(VOID) {
	OSReport("<<<<<<<	System		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(SYS_OMAKE_ADA_GAME), CkBit(SystemFlag, SYS_OMAKE_ADA_GAME));
	OSReport("%s: %d\n", FieldName(SYS_OMAKE_ETC_GAME), CkBit(SystemFlag, SYS_OMAKE_ETC_GAME));
	OSReport("%s: %d\n", FieldName(SYS_EXCEPTION), CkBit(SystemFlag, SYS_EXCEPTION));
	OSReport("%s: %d\n", FieldName(SYS_RENDER_END), CkBit(SystemFlag, SYS_RENDER_END));
	OSReport("%s: %d\n", FieldName(SYS_SP_USED), CkBit(SystemFlag, SYS_SP_USED));
	OSReport("%s: %d\n", FieldName(SYS_SOFT_RESET), CkBit(SystemFlag, SYS_SOFT_RESET));
	OSReport("%s: %d\n", FieldName(SYS_DATA_READ), CkBit(SystemFlag, SYS_DATA_READ));
	OSReport("%s: %d\n", FieldName(SYS_ROOMJUMP), CkBit(SystemFlag, SYS_ROOMJUMP));
	OSReport("%s: %d\n", FieldName(SYS_INVISIBLE), CkBit(SystemFlag, SYS_INVISIBLE));
	OSReport("%s: %d\n", FieldName(SYS_DOOR_AFTER), CkBit(SystemFlag, SYS_DOOR_AFTER));
	OSReport("%s: %d\n", FieldName(SYS_DOORDEMO), CkBit(SystemFlag, SYS_DOORDEMO));
	OSReport("%s: %d\n", FieldName(SYS_TRANS_STOP), CkBit(SystemFlag, SYS_TRANS_STOP));
	OSReport("%s: %d\n", FieldName(SYS_CONTINUE), CkBit(SystemFlag, SYS_CONTINUE));
	OSReport("%s: %d\n", FieldName(SYS_SET_BLACK), CkBit(SystemFlag, SYS_SET_BLACK));
	OSReport("%s: %d\n", FieldName(SYS_SN_PC_READ), CkBit(SystemFlag, SYS_SN_PC_READ));
	OSReport("%s: %d\n", FieldName(SYS_SN_PC_READ_TOOL), CkBit(SystemFlag, SYS_SN_PC_READ_TOOL));
	OSReport("%s: %d\n", FieldName(SYS_SSCRN_EXEC), CkBit(SystemFlag, SYS_SSCRN_EXEC));
	OSReport("%s: %d\n", FieldName(SYS_SCREEN_SHOT), CkBit(SystemFlag, SYS_SCREEN_SHOT));
	OSReport("%s: %d\n", FieldName(SYS_NEW_GAME), CkBit(SystemFlag, SYS_NEW_GAME));
	OSReport("%s: %d\n", FieldName(SYS_PS2_ADA_GAME), CkBit(SystemFlag, SYS_PS2_ADA_GAME));
	OSReport("%s: %d\n", FieldName(SYS_SCISSOR_ON), CkBit(SystemFlag, SYS_SCISSOR_ON));
	OSReport("%s: %d\n", FieldName(SYS_SCREEN_STOP), CkBit(SystemFlag, SYS_SCREEN_STOP));
	OSReport("%s: %d\n", FieldName(SYS_CARD_ACCESS), CkBit(SystemFlag, SYS_CARD_ACCESS));
	OSReport("%s: %d\n", FieldName(SYS_LOAD_GAME), CkBit(SystemFlag, SYS_LOAD_GAME));
	OSReport("%s: %d\n", FieldName(SYS_CONTINUE_AFTER), CkBit(SystemFlag, SYS_CONTINUE_AFTER));
	OSReport("%s: %d\n", FieldName(SYS_START_EVT_SKIP), CkBit(SystemFlag, SYS_START_EVT_SKIP));
	OSReport("%s: %d\n", FieldName(SYS_HARD_MODE), CkBit(SystemFlag, SYS_HARD_MODE));
	OSReport("%s: %d\n", FieldName(SYS_MESSAGE_INIT), CkBit(SystemFlag, SYS_MESSAGE_INIT));
	OSReport("%s: %d\n", FieldName(SYS_PUBLICITY_VER), CkBit(SystemFlag, SYS_PUBLICITY_VER));
	OSReport("%s: %d\n", FieldName(SYS_SAVEDATA_EXIST), CkBit(SystemFlag, SYS_SAVEDATA_EXIST));
	OSReport("%s: %d\n", FieldName(SYS_PAL), CkBit(SystemFlag, SYS_PAL));
	OSReport("%s: %d\n", FieldName(SYS_DTV480P), CkBit(SystemFlag, SYS_DTV480P));
}
VOID PrintConfigFlags(VOID) {
	OSReport("<<<<<<<	Config		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(CFG_AIM_REVERSE), CkBit(ConfigFlag, CFG_AIM_REVERSE));
	OSReport("%s: %d\n", FieldName(CFG_WIDE_MODE), CkBit(ConfigFlag, CFG_WIDE_MODE));
	OSReport("%s: %d\n", FieldName(CFG_LOCK_ON), CkBit(ConfigFlag, CFG_LOCK_ON));
	OSReport("%s: %d\n", FieldName(CFG_BONUS_GET), CkBit(ConfigFlag, CFG_BONUS_GET));
	OSReport("%s: %d\n", FieldName(CFG_VIBRATION), CkBit(ConfigFlag, CFG_VIBRATION));
	OSReport("%s: %d\n", FieldName(CFG_KNIFE_MODE), CkBit(ConfigFlag, CFG_KNIFE_MODE));
}
VOID PrintExtraFlags(VOID) {
	OSReport("<<<<<<<	Extra		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(EXT_COSTUME), CkBit(ExtraFlag, EXT_COSTUME));
	OSReport("%s: %d\n", FieldName(EXT_HARD_MODE), CkBit(ExtraFlag, EXT_HARD_MODE));
	OSReport("%s: %d\n", FieldName(EXT_GET_SW500), CkBit(ExtraFlag, EXT_GET_SW500));
	OSReport("%s: %d\n", FieldName(EXT_GET_TOMPSON), CkBit(ExtraFlag, EXT_GET_TOMPSON));
	OSReport("%s: %d\n", FieldName(EXT_GET_ADA), CkBit(ExtraFlag, EXT_GET_ADA));
	OSReport("%s: %d\n", FieldName(EXT_GET_HUNK), CkBit(ExtraFlag, EXT_GET_HUNK));
	OSReport("%s: %d\n", FieldName(EXT_GET_KLAUSER), CkBit(ExtraFlag, EXT_GET_KLAUSER));
	OSReport("%s: %d\n", FieldName(EXT_GET_WESKER), CkBit(ExtraFlag, EXT_GET_WESKER));
	OSReport("%s: %d\n", FieldName(EXT_GET_OMAKE_ADA_GAME), CkBit(ExtraFlag, EXT_GET_OMAKE_ADA_GAME));
	OSReport("%s: %d\n", FieldName(EXT_GET_OMAKE_ETC_GAME), CkBit(ExtraFlag, EXT_GET_OMAKE_ETC_GAME));
	OSReport("%s: %d\n", FieldName(EXT_ASHLEY_ARMOR), CkBit(ExtraFlag, EXT_ASHLEY_ARMOR));
	OSReport("%s: %d\n", FieldName(EXT_GET_PS2_ADA_GAME), CkBit(ExtraFlag, EXT_GET_PS2_ADA_GAME));
	OSReport("%s: %d\n", FieldName(EXT_COSTUME_MAFIA), CkBit(ExtraFlag, EXT_COSTUME_MAFIA));
	OSReport("%s: %d\n", FieldName(EXT_GET_LASER), CkBit(ExtraFlag, EXT_GET_LASER));
	OSReport("%s: %d\n", FieldName(EXT_GET_ADA_TOMPSON), CkBit(ExtraFlag, EXT_GET_ADA_TOMPSON));
	OSReport("%s: %d\n", FieldName(EXT_GET_ADAS_REPORT), CkBit(ExtraFlag, EXT_GET_ADAS_REPORT));
}
VOID PrintDisplayFlags(VOID) {
	OSReport("<<<<<<<	Display		>>>>>>>\n");
	OSReport("%s: %d\n", FieldName(DPF_EM), CkBit(DisplayFlag, DPF_EM));
	OSReport("%s: %d\n", FieldName(DPF_PL), CkBit(DisplayFlag, DPF_PL));
	OSReport("%s: %d\n", FieldName(DPF_SUBCHAR), CkBit(DisplayFlag, DPF_SUBCHAR));
	OSReport("%s: %d\n", FieldName(DPF_OBJ), CkBit(DisplayFlag, DPF_OBJ));
	OSReport("%s: %d\n", FieldName(DPF_SCR), CkBit(DisplayFlag, DPF_SCR));
	OSReport("%s: %d\n", FieldName(DPF_ESP), CkBit(DisplayFlag, DPF_ESP));
	OSReport("%s: %d\n", FieldName(DPF_SHADOW), CkBit(DisplayFlag, DPF_SHADOW));
	OSReport("%s: %d\n", FieldName(DPF_WATER), CkBit(DisplayFlag, DPF_WATER));
	OSReport("%s: %d\n", FieldName(DPF_MIRROR), CkBit(DisplayFlag, DPF_MIRROR));
	OSReport("%s: %d\n", FieldName(DPF_CTRL), CkBit(DisplayFlag, DPF_CTRL));
	OSReport("%s: %d\n", FieldName(DPF_CINESCO), CkBit(DisplayFlag, DPF_CINESCO));
	OSReport("%s: %d\n", FieldName(DPF_FILTER), CkBit(DisplayFlag, DPF_FILTER));
	OSReport("%s: %d\n", FieldName(DPF_GLB_ILM), CkBit(DisplayFlag, DPF_GLB_ILM));
	OSReport("%s: %d\n", FieldName(DPF_CAST_SHADOW), CkBit(DisplayFlag, DPF_CAST_SHADOW));
	OSReport("%s: %d\n", FieldName(DPF_CLOTH), CkBit(DisplayFlag, DPF_CLOTH));
	OSReport("%s: %d\n", FieldName(DPF_COCKPIT), CkBit(DisplayFlag, DPF_COCKPIT));
	OSReport("%s: %d\n", FieldName(DPF_SELF_SHADOW), CkBit(DisplayFlag, DPF_SELF_SHADOW));
	OSReport("%s: %d\n", FieldName(DPF_FOG), CkBit(DisplayFlag, DPF_FOG));
	OSReport("%s: %d\n", FieldName(DPF_ID_SYSTEM), CkBit(DisplayFlag, DPF_ID_SYSTEM));
	OSReport("%s: %d\n", FieldName(DPF_ACTBTN), CkBit(DisplayFlag, DPF_ACTBTN));
	OSReport("%s: %d\n", FieldName(DPF_MESSAGE), CkBit(DisplayFlag, DPF_MESSAGE));
	OSReport("%s: %d\n", FieldName(DPF_TEX_RENDER), CkBit(DisplayFlag, DPF_TEX_RENDER));
	OSReport("%s: %d\n", FieldName(DPF_EFFECT_VU1), CkBit(DisplayFlag, DPF_EFFECT_VU1));
	OSReport("%s: %d\n", FieldName(DPF_17), CkBit(DisplayFlag, DPF_17));
	OSReport("%s: %d\n", FieldName(DPF_18), CkBit(DisplayFlag, DPF_18));
	OSReport("%s: %d\n", FieldName(DPF_19), CkBit(DisplayFlag, DPF_19));
	OSReport("%s: %d\n", FieldName(DPF_1A), CkBit(DisplayFlag, DPF_1A));
	OSReport("%s: %d\n", FieldName(DPF_1B), CkBit(DisplayFlag, DPF_1B));
	OSReport("%s: %d\n", FieldName(DPF_1C), CkBit(DisplayFlag, DPF_1C));
	OSReport("%s: %d\n", FieldName(DPF_1D), CkBit(DisplayFlag, DPF_1D));
	OSReport("%s: %d\n", FieldName(DPF_1E), CkBit(DisplayFlag, DPF_1E));
	OSReport("%s: %d\n", FieldName(DPF_1F), CkBit(DisplayFlag, DPF_1F));
}