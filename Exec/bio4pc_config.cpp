
#include "..\\dllmain.h"

tagBio4Config Bio4Config;

VOID Bio4DmyConfig(VOID) {
    UseDebugLogging = 1;
    Bio4Config.dAspectR = 1.3333334f;
    Bio4Config.AspectRatio = 1.3333334f;
    Bio4Config.InternalWidth = 1280.0f;
    Bio4Config.InternalHeight = 720.0f;
    Bio4Config.RefreshRate = 60;
    Bio4Config.Znear = 100.0f;
    Bio4Config.Zfar = 1000000.0f;
    Bio4Config.OrthoT = 240.0f;
    Bio4Config.OrthoB = -240.0f;
    Bio4Config.OrthoL = -320.0f;
    Bio4Config.OrthoR = 320.0f;
    Bio4Config.Vcount = 2;
    Bio4Movie->UseSofdecVideo = 0;
    Bio4Movie->AutoSkipVideos = 0;
    Bio4Config.NoDamage = FALSE;
    Bio4Config.AttacheSize = 0x7C;
    Bio4Config.StartWeapon = 0x23;
    Bio4Config.StartHeal = 0x04;
}
VOID Bio4OpenConfig(VOID) {

    // Open
    TextFileA* List = Text->OpenA("..\\Bin32\\bio4.ini");
    if (List == nullptr) {
        OSReport("bio4.ini does not exist!\n");
        Bio4DmyConfig();
        Bio4SaveConfig();
        return;
    }

    // Parse
    UINT TmpValue = NULL;
    for (size_t n = 0; n < List->Line.size(); n++)
    {
        if (!List->Args[n][NULL].compare("DebugLogging")) { UseDebugLogging = static_cast<BOOL>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("AspectRatio")) {
            Bio4Config.dAspectR = File->GetFloatFromStr(List->Args[n][1].c_str());
            Bio4Config.AspectRatio = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str()));
        }

        if (!List->Args[n][NULL].compare("InternalWidth")) { Bio4Config.InternalWidth = static_cast<DOUBLE>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("InternalHeight")) { Bio4Config.InternalHeight = static_cast<DOUBLE>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("RefreshRate")) { Bio4Config.RefreshRate = static_cast<UINT>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("Znear")) { Bio4Config.Znear = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("Zfar")) { Bio4Config.Zfar = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("OrthoT")) { Bio4Config.OrthoT = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("OrthoB")) { Bio4Config.OrthoB = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("OrthoL")) { Bio4Config.OrthoL = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("OrthoR")) { Bio4Config.OrthoR = static_cast<FLOAT>(File->GetFloatFromStr(List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("Vcount")) { Bio4Config.Vcount = static_cast<BYTE>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("UseCriVideo")) { Bio4Movie->UseSofdecVideo = static_cast<BOOL>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("AutoSkipVideos")) { Bio4Movie->AutoSkipVideos = static_cast<BOOL>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("NoDamage")) {

            Bio4Config.NoDamage = static_cast<BOOL>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str()));

            switch (Bio4Config.NoDamage)
            {
            case 0:
            default:
                break;
            case 1:
                //pG[0x4fc8]
                //INJECT(_SetPlDamage + AllocationBase, nullStub);
                //INJECT(_EndPlDamage + AllocationBase, nullStub);
                //INJECT(_PlSetDamage + AllocationBase, nullStub);
                //INJECT(_dmgCheck + AllocationBase, nullStub);
                //InjectNop(0x0067c51a, 2);	// cPlayer::endDamage
                //InjectNop(0x0067eb33, 2);	// cPlayer::beginDamage
                //InjectNop(0x006b3ed3, 5);	// sceAtFunc_damage
                //InjectNop(0x006b3f62, 5);	// sceAtFunc_damage
                //InjectNop(0x007529a5, 2);	// pl_dmg::Pl_R0_Damage
                //INJECT(_LifeDownSet + AllocationBase, nullStub);
                //INJECT(_LifeDownSet2 + AllocationBase, nullStub);
                InjectNop(0x005b5b65, 355);
                //INJECT(_damageNormal + AllocationBase, nullStub);
                //INJECT(_damageBlow + AllocationBase, nullStub);
                //INJECT(_damageBlast + AllocationBase, nullStub);
                //InjectNop(0x0067ecc6, 228);
                //InjectNop(0x0067edb0, 7);
                break;
            }

        }

        if (!List->Args[n][NULL].compare("AttacheSize")) {

            Bio4Config.AttacheSize = static_cast<BYTE>(File->GetValueFromStr(FALSE, List->Args[n][1].c_str()));

            switch (Bio4Config.AttacheSize)
            {
            case 0:
            default:
                Bio4Config.AttacheSize = 0x7C;
                break;
            case 1:
                Bio4Config.AttacheSize = 0x7D;
                break;
            case 2:
                Bio4Config.AttacheSize = 0x7E;
                break;
            case 3:
                Bio4Config.AttacheSize = 0x7F;
                break;
            }

        }

        if (!List->Args[n][NULL].compare("StartWeapon")) { Bio4Config.StartWeapon = static_cast<BYTE>(File->GetValueFromStr(TRUE, List->Args[n][1].c_str())); }

        if (!List->Args[n][NULL].compare("StartHeal")) { Bio4Config.StartHeal = static_cast<BYTE>(File->GetValueFromStr(TRUE, List->Args[n][1].c_str())); }

    }

    // Cleanup
    Text->Close(List);

}
VOID Bio4SaveConfig(VOID) {

    // Output
    OSReport("Creating Bin32\\bio4.ini...\n");
    _iobuf* _File = File->Open(CREATE_FILE, "..\\Bin32\\bio4.ini");
    if (!_File) { return; }

    // Print
    File->Print(_File, "// The \"DebugLogging\" flag determines if debug strings are recorded to log files\r\n");
    File->Print(_File, "// Debug logs are located in the \"Bin32\" folder and reset at hardboot\r\n");
    File->Print(_File, "DebugLogging\t%d\r\n", UseDebugLogging);
    File->Print(_File, "\r\n");
    File->Print(_File, "// By default, the game's internal resolution is set at 1280x720 in 4:3 aspect ratio\r\n");
    File->Print(_File, "// Output is stretched to whatever resolution is specified in \"RE4\\config.ini\"\r\n");
    File->Print(_File, "// Modifying these values will introduce \"border\" bugs that have yet to be addressed\r\n");
    File->Print(_File, "AspectRatio\t%lf\r\n", Bio4Config.AspectRatio);
    File->Print(_File, "InternalWidth\t%lf\r\n", Bio4Config.InternalWidth);
    File->Print(_File, "InternalHeight\t%lf\r\n", Bio4Config.InternalHeight);
    File->Print(_File, "\r\n");
    File->Print(_File, "// The internal rendering engine is hardcapped at 60fps\r\n");
    File->Print(_File, "// At your own risk (!!!), you can force it higher (120, etc)\r\n");
    File->Print(_File, "// Do not modify this value if your monitor does not support a higher refresh rate!\r\n");
    File->Print(_File, "RefreshRate\t%d\r\n", Bio4Config.RefreshRate);
    File->Print(_File, "\r\n");
    File->Print(_File, "// The following variables aren't used in *every* case scenario\r\n");
    File->Print(_File, "// For \"Vcount,\" lower is better (2 is default)\r\n");
    File->Print(_File, "Znear\t%lf\r\n", Bio4Config.Znear);
    File->Print(_File, "Zfar\t%lf\r\n", Bio4Config.Zfar);
    File->Print(_File, "OrthoT\t%lf\r\n", Bio4Config.OrthoT);
    File->Print(_File, "OrthoB\t%lf\r\n", Bio4Config.OrthoB);
    File->Print(_File, "OrthoL\t%lf\r\n", Bio4Config.OrthoL);
    File->Print(_File, "OrthoR\t%lf\r\n", Bio4Config.OrthoR);
    File->Print(_File, "Vcount\t%d\r\n", Bio4Config.Vcount);
    File->Print(_File, "\r\n");
    File->Print(_File, "// Custom video playback is a work in progress\r\n");
    File->Print(_File, "// The \"UseCriVideo\" flag will force the use of standard CRI/SFD playback\r\n");
    File->Print(_File, "// The \"AutoSkipVideos\" flag will bypass playback of all prerendered movies\r\n");
    File->Print(_File, "// Currently, custom movie routines lack audio rendering\r\n");
    File->Print(_File, "UseCriVideo\t%d\r\n", Bio4Movie->UseSofdecVideo);
    File->Print(_File, "AutoSkipVideos\t%d\r\n", Bio4Movie->AutoSkipVideos);
    File->Print(_File, "\r\n");
    File->Print(_File, "// Debug Game\r\n");
    File->Print(_File, "// The following values determine attache case size and items in New Game\r\n");
    File->Print(_File, "// Accepted values for \"AttacheSize\" are 0-3\r\n");
    File->Print(_File, "// Refer to the internet for \"StartWeapon\" and \"StartHeal\" item list values\r\n");
    File->Print(_File, "NoDamage\t%d\r\n", Bio4Config.NoDamage);
    switch (Bio4Config.AttacheSize)
    {
    case 0x7C:
    default:
        File->Print(_File, "AttacheSize\t%d\r\n", 0);
        break;
    case 0x7D:
        File->Print(_File, "AttacheSize\t%d\r\n", 1);
        break;
    case 0x7E:
        File->Print(_File, "AttacheSize\t%d\r\n", 2);
        break;
    case 0x7F:
        File->Print(_File, "AttacheSize\t%d\r\n", 3);
        break;
    }
    File->Print(_File, "StartWeapon\t0x%02X\r\n", Bio4Config.StartWeapon);
    File->Print(_File, "StartHeal\t0x%02X\r\n", Bio4Config.StartHeal);

    // Complete
    fclose(_File);

}