#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <Xinput.h>

#include "patcher.h"

#include "../shared/ini_reader.h"

#pragma comment(lib, "Xinput.lib")

struct sAddresses
{
	static uintptr_t _Render_Thread;
	static uintptr_t _Physics_Threads;
	static uintptr_t _Job_Threads;
	static uintptr_t _Override_Threading_Config;
	static uintptr_t _Override_Threading_Config_JumpOut;
	static uintptr_t _Mouse_Fix;
	static uintptr_t _Mouse_Fix_JumpOut;
	static uintptr_t _Vehicle_FOV;
	static uintptr_t _Vehicle_FOV_JumpOut;
	static uintptr_t _Player_FOV;
	static uintptr_t _Player_FOV_JumpOut;
	static uintptr_t _fFOV;
	static uintptr_t _fFOVAngle;
	static uintptr_t _fIronsightFOV;
	static uintptr_t _fIronsightFOV_Get_Address;
	static uintptr_t _fIronsightFOV_Get_Address_JumpOut;
	static uintptr_t _fIronsightFOV_Address;
	static uintptr_t _fSaturation;
	static uintptr_t _fSaturation_Get_Address;
	static uintptr_t _fSaturation_Get_Address_JumpOut;
	static uintptr_t _fSaturation_Address;
	static uintptr_t _Get_Addresses;
	static uintptr_t _Get_Addresses_JumpOut;
	static uintptr_t _Apply_New_Values;
	static uintptr_t _Apply_New_Values_JumpOut;
	static uintptr_t _Dev_Console;
	static uintptr_t _Dev_Console_JumpOut;
	static uintptr_t _Rumble_Effects;
	static uintptr_t _Rumble_Effects_JumpOut;
	static uintptr_t _Rumble_Weapons;
	static uintptr_t _Rumble_Weapons_JumpOut;
	static uintptr_t _Rumble_Reset;
	static uintptr_t _Rumble_Reset_JumpOut;
	static uintptr_t _Rumble_Misc;
	static uintptr_t _Rumble_Misc_JumpOut;
	static uintptr_t _Rumble_Strength_Sprint;
	static uintptr_t _Rumble_Strength_Sprint_JumpOut;
	static uintptr_t _Game_Version;
	static uintptr_t _Game_Version_JumpOut;
};

uintptr_t sAddresses::_Render_Thread = 0x180903A8;
uintptr_t sAddresses::_Physics_Threads = 0x180903F8;
uintptr_t sAddresses::_Job_Threads = 0x18090448;
uintptr_t sAddresses::_Override_Threading_Config = 0x102B2EB8;
uintptr_t sAddresses::_Override_Threading_Config_JumpOut = 0x102B2EBD;
uintptr_t sAddresses::_Mouse_Fix = 0x105FF995;
uintptr_t sAddresses::_Mouse_Fix_JumpOut = 0x105FF99B;
uintptr_t sAddresses::_Vehicle_FOV = 0x100DC122;
uintptr_t sAddresses::_Vehicle_FOV_JumpOut = 0x100DC12A;
uintptr_t sAddresses::_Player_FOV = 0x10504CC0;
uintptr_t sAddresses::_Player_FOV_JumpOut = 0x10504CC6;
uintptr_t sAddresses::_fFOV;
uintptr_t sAddresses::_fFOVAngle;
uintptr_t sAddresses::_fIronsightFOV;
uintptr_t sAddresses::_fIronsightFOV_Get_Address = 0x100F5FD3;
uintptr_t sAddresses::_fIronsightFOV_Get_Address_JumpOut = 0x100F5FDA;
uintptr_t sAddresses::_fIronsightFOV_Address;
uintptr_t sAddresses::_fSaturation;
uintptr_t sAddresses::_fSaturation_Get_Address = 0x10563321;
uintptr_t sAddresses::_fSaturation_Get_Address_JumpOut = 0x10563328;
uintptr_t sAddresses::_fSaturation_Address;
uintptr_t sAddresses::_Get_Addresses = 0x10957946;
uintptr_t sAddresses::_Get_Addresses_JumpOut = 0x1095794E;
uintptr_t sAddresses::_Apply_New_Values = 0x10234A48;
uintptr_t sAddresses::_Apply_New_Values_JumpOut = 0x10234A4E;
uintptr_t sAddresses::_Dev_Console = 0x10046974;
uintptr_t sAddresses::_Dev_Console_JumpOut = 0x1004697A;
uintptr_t sAddresses::_Rumble_Effects = 0x101419B1;
uintptr_t sAddresses::_Rumble_Effects_JumpOut = 0x101419B6;
uintptr_t sAddresses::_Rumble_Weapons = 0x1011354F;
uintptr_t sAddresses::_Rumble_Weapons_JumpOut = 0x10113558;
uintptr_t sAddresses::_Rumble_Reset = 0x101417E0;
uintptr_t sAddresses::_Rumble_Reset_JumpOut = 0x101417E5;
uintptr_t sAddresses::_Rumble_Misc = 0x10083A7A;
uintptr_t sAddresses::_Rumble_Misc_JumpOut = 0x10083A7F;
uintptr_t sAddresses::_Rumble_Strength_Sprint = 0x106D292F;
uintptr_t sAddresses::_Rumble_Strength_Sprint_JumpOut = 0x106D2937;
uintptr_t sAddresses::_Game_Version = 0x107C56C3;
uintptr_t sAddresses::_Game_Version_JumpOut = 0x107C56C8;

static int RENDER_THREAD_COUNT;
static int PHYSIC_THREADS_COUNT;
static int JOB_THREADS_COUNT;

static float NEW_PLAYER_FOV;
static float NEW_VEHICLE_FOV;
static float ADS_FOV_MULTIPLIER;
static float OLD_ADS_FOV;
static float NEW_ADS_FOV;
static float NEW_SATURATION_VALUE;

static float RUMBLE_CURVE_LEFT;
static float RUMBLE_CURVE_RIGHT;
static float RUMBLE_STRENGTH_MISC = 1.0f;
static float RUMBLE_STRENGTH_SPRINT = 0.005f;


// JackalPatch v. 1.00
BYTE PatchVersion[] = {
	0x4A, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x50, 0x00, 0x61, 0x00, 0x74, 0x00, 0x63, 
	0x00, 0x68, 0x00, 0x20, 0x00, 0x76, 0x00, 0x2E, 0x00, 0x20, 0x00, 0x31, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00
};

// Print the current Patch version in the Dev Console window
ASM(_Game_Version_Patch) 
{
	__asm
	{
		lea ecx, PatchVersion
		push ecx
		jmp sAddresses::_Game_Version_JumpOut
	}
}

/* 
    0x102B2EB8 might look a bit random as a hooking location, however at this point the game has already loaded the default threading configuration that we wish to override 
    and is just about to call upon the function at 0x102B2EE4 that seems to be responsible for establishing the thread count
*/
ASM(_Override_Threading_Config_Patch)
{
	__asm
	{
		pushad
	}

	if (MEMCMP32(sAddresses::_Render_Thread - 0x28, 0x444E4552)) // standard mode
	{
		Patch<uint32_t>(sAddresses::_Render_Thread, RENDER_THREAD_COUNT);
		Patch<uint32_t>(sAddresses::_Physics_Threads, PHYSIC_THREADS_COUNT);
		Patch<uint32_t>(sAddresses::_Job_Threads, JOB_THREADS_COUNT);
		Patch<uint32_t>(sAddresses::_Job_Threads - 0xc, 0); // RelativeToCoreCnt="0"; otherwise FC2 seemingly ignores our desired job thread count
		Patch<uint32_t>(sAddresses::_Job_Threads - 0x4, 99); // MaxThreadCnt="99"
		Patch<uint32_t>(sAddresses::_Physics_Threads - 0x4, 99); // MaxThreadCnt="99"
	}
	// When FC2 is launched through benchmark tool, addresses for the threading configuration are shifted by 0x50
	else if (MEMCMP32(sAddresses::_Render_Thread + 0x50 - 0x28, 0x444E4552)) // benchmark mode
	{
		Patch<uint32_t>(sAddresses::_Render_Thread + 0x50, RENDER_THREAD_COUNT);
		Patch<uint32_t>(sAddresses::_Physics_Threads + 0x50, PHYSIC_THREADS_COUNT);
		Patch<uint32_t>(sAddresses::_Job_Threads + 0x50, JOB_THREADS_COUNT);
		Patch<uint32_t>(sAddresses::_Job_Threads + 0x50 - 0xc, 0); // RelativeToCoreCnt="0" 
		Patch<uint32_t>(sAddresses::_Job_Threads + 0x50 - 0x4, 99); // MaxThreadCnt="99"
		Patch<uint32_t>(sAddresses::_Physics_Threads + 0x50 - 0x4, 99); // MaxThreadCnt="99"
	}

	__asm
	{
		popad
		push 0x7fffffff // original instruction
		jmp sAddresses::_Override_Threading_Config_JumpOut
	}
}

/* 
    Retrieve non-static addresses for variables such as fIronsightFOV and fSaturation
    This whole procedure might be overly complicated, but I couldn't find any static pointers since CE's pointerscan doesn't work on Linux
*/
ASM(_Get_Addresses_Patch)
{
	__asm
	{	
		cmp sAddresses::_fSaturation_Address, eax
		je _Get_fSaturation_Address
		cmp sAddresses::_fIronsightFOV_Address, eax
		je _Get_fIronsightFOV_Address
		add esi,dword ptr [esp + 0x8]
        mov ecx,dword ptr [esp + 0xc]
		jmp sAddresses::_Get_Addresses_JumpOut
	
	_Get_fSaturation_Address:
	add esi, dword ptr [esp + 0x8]
	mov sAddresses::_fSaturation, esi
	mov ecx, dword ptr [esp + 0xc]
	jmp sAddresses::_Get_Addresses_JumpOut

	_Get_fIronsightFOV_Address:
	add esi, dword ptr [esp + 0x8]
	mov sAddresses::_fIronsightFOV, esi
	mov ecx, dword ptr [esp + 0xc]
	jmp sAddresses::_Get_Addresses_JumpOut
	}
}

// Apply our desired values for fIronsightFOV and fSaturation at the addresses we gathered with _Get_Addresses_Patch
ASM(_Apply_New_Values_Patch)
{
	__asm
	{
		mov ecx, dword ptr [esp + 0x8]
		mov dword ptr [ecx], eax
		pushad
	}
	
	if (sAddresses::_fSaturation != 0)
	{
		Patch(sAddresses::_fSaturation, NEW_SATURATION_VALUE);
		sAddresses::_fSaturation = 0; // set to 0 again to prevent patching at the wrong address when re-loading or loading a new savegame
	}
	
	if (sAddresses::_fIronsightFOV != 0) // If !=0, fIronisghtFOV should equal [ecx] above, hence eax contains our FOV value
	{
		__asm
		{
			popad
			mov OLD_ADS_FOV, eax 
			pushad
		}
		
		NEW_ADS_FOV = OLD_ADS_FOV * ADS_FOV_MULTIPLIER; // Every weapon has its own FOV value for ADS, so we use a multiplier to scale them correctly
		Patch(sAddresses::_fIronsightFOV, NEW_ADS_FOV);
		sAddresses::_fIronsightFOV = 0;
	}
		
	__asm
	{
		popad
		jmp sAddresses::_Apply_New_Values_JumpOut
	}
}

ASM(_fSaturation_Get_Address_Patch)
{
	__asm
	{
		mov	dword ptr [esi + 0xc], 0x54
		mov sAddresses::_fSaturation_Address, esi 
		jmp sAddresses::_fSaturation_Get_Address_JumpOut
	}
}

ASM(_fIronsightFOV_Get_Address_Patch)
{
	__asm
	{
		mov	dword ptr [esi + 0xc], 0xE4
		mov sAddresses::_fIronsightFOV_Address, esi 
		jmp sAddresses::_fIronsightFOV_Get_Address_JumpOut
	}
}

ASM(_Mouse_Patch)
{
	__asm
	{
		fstp dword ptr [esi + 0xc]
        lea ebp,[esi + 0x14]
		cmp dword ptr [esi + 0xc], 0x41200000 // float 10 is the default MaxOutput value for mouse; there are some other values passing through here that we do not wanna touch
        je _New_MaxOutput
		jmp sAddresses::_Mouse_Fix_JumpOut
	
	_New_MaxOutput:
	mov dword ptr [esi + 0xc], 0x49742400 // float 10000000
	jmp sAddresses::_Mouse_Fix_JumpOut
	}
}

// Only executes once every time the player enters a vehicle
ASM(_Vehicle_FOV_Patch)
{
	__asm
	{
		pushad
		mov sAddresses::_fFOVAngle, esi
		add sAddresses::_fFOVAngle, 0x234
	}
	
	Patch(sAddresses::_fFOVAngle, NEW_VEHICLE_FOV);
	
	__asm
	{
		popad
        movss XMM0,dword ptr [esi + 0x234]
		jmp sAddresses::_Vehicle_FOV_JumpOut
	}
}

ASM(_Player_FOV_Patch) 
{
	__asm
	{
		mov sAddresses::_fFOV, esp
		add sAddresses::_fFOV, 0x4
		pushad
	}

	Patch(sAddresses::_fFOV, NEW_PLAYER_FOV);

	__asm
	{
		popad
		movss xmm0, dword ptr [esp + 0x4]
		jmp sAddresses::_Player_FOV_JumpOut
	}
}

// Instead of enabling every CVar individually, we hook the function responsible for checking if the command is developer-only or not
ASM(_Dev_Console_Patch) 
{
	__asm
	{
		mov [edi + 0x14], 0x0 // 0 = unlocked, 1 = developer only
		movzx eax,byte ptr [edi + 0x14]
		mov ecx,dword ptr [esi]
		jmp sAddresses::_Dev_Console_JumpOut
	}
}

void __cdecl ConvertScreenShake()
{
	// Convert any negative curve values to positive - XInputSetState only takes positive values as argument
	if (RUMBLE_CURVE_LEFT < 0)
	{
		RUMBLE_CURVE_LEFT = 0.0f - RUMBLE_CURVE_LEFT;
	}
	
	if (RUMBLE_CURVE_RIGHT < 0)
	{
		RUMBLE_CURVE_RIGHT = 0.0f - RUMBLE_CURVE_RIGHT;
	}
	
	// The curve values are very low by default, so we use a multiplier of 50
	RUMBLE_CURVE_LEFT = RUMBLE_CURVE_LEFT * 50.0f;
	RUMBLE_CURVE_RIGHT = RUMBLE_CURVE_RIGHT * 50.0f;
}

void __cdecl Rumble()
{      
	// Vibration state
    XINPUT_VIBRATION VibrationState;
 
    // Zero memory
    ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));
 
	// Calculate vibration values
    int iLeftMotor  = int(RUMBLE_CURVE_LEFT * 65535.0f);
    int iRightMotor = int(RUMBLE_CURVE_RIGHT * 65535.0f);
	   
	if (iLeftMotor > 65535)
	{
		iLeftMotor = 65535;
	}

	if (iRightMotor > 65535)
	{
		iRightMotor = 65535;
	}

	// Set vibration values
    VibrationState.wLeftMotorSpeed  = iLeftMotor;
    VibrationState.wRightMotorSpeed = iRightMotor;
 
    // Set the vibration state
    XInputSetState(0, &VibrationState);
}

// Explosions, taking damage, Malaria attacks etc.
// Not sure what these values are actually intended for, they might just be for screenshake, but work well for rumble too with some tweaking
ASM(_Rumble_Effects_Patch) 
{
	__asm
	{
		mov eax, dword ptr ds:[0x11606360] // OG instruction
		pushad
		mov eax, dword ptr [esi + 0x124]
		mov RUMBLE_CURVE_LEFT, eax
		mov eax, dword ptr [esi + 0x128]
		mov RUMBLE_CURVE_RIGHT, eax
		cmp dword ptr [esi + 0x124], 0x0 // No need to convert screenshake/rumble if there is none
		jne _Initialize_Conversion
		call Rumble
		popad
		jmp sAddresses::_Rumble_Effects_JumpOut
	
	_Initialize_Conversion:
	call ConvertScreenShake
	call Rumble
	popad
	jmp sAddresses::_Rumble_Effects_JumpOut
	}
}

// Gun Fire
ASM(_Rumble_Weapons_Patch) 
{
	__asm
	{
		movss dword ptr [esp + 0x8c], xmm0 // The values passing through here look like actual rumble data: Silenced and automatic guns produce less rumble, heavy weapons are at maximum of 1.0f
		pushad
		movss RUMBLE_CURVE_LEFT, xmm0
		movss RUMBLE_CURVE_RIGHT, xmm0
		call Rumble
		popad
		jmp sAddresses::_Rumble_Weapons_JumpOut
	
	}
}

// Sprinting, using mounted MGs, firing rocket launcher
ASM(_Rumble_Misc_Patch) 
{
	__asm
	{
		movss dword ptr [esi + 0x30], xmm0 // OG instruction
		pushad
		mov eax, RUMBLE_STRENGTH_MISC
		mov RUMBLE_CURVE_LEFT, eax
		mov RUMBLE_CURVE_RIGHT, eax
		call Rumble
		popad
		mov RUMBLE_STRENGTH_MISC, 0x3F800000 // reset back to default of 1.0f; only necessary because we reduce rumble strength for sprinting in a separate patch
		jmp sAddresses::_Rumble_Misc_JumpOut
	
	}
}

// Reduce vibration strength for sprinting only - No idea why this is not a separate value from other effects
ASM(_Rumble_Strength_Sprint_Patch) 
{
	__asm
	{
		mov ecx, RUMBLE_STRENGTH_SPRINT
		mov RUMBLE_STRENGTH_MISC, ecx
		
		// OG instructions
		lea ecx, [esp + 0x20] 
		mov dword ptr [esp + 0x14], eax
		jmp sAddresses::_Rumble_Strength_Sprint_JumpOut
	}
}

// Reset Vibration State back to zero - Required by XInput API before sending a new rumble event
ASM(_Rumble_Reset_State_Patch) 
{
	__asm
	{
		fld dword ptr [esp + 0x4] // OG instruction
		push ecx
		pushad
		mov RUMBLE_CURVE_LEFT, 0x0
		mov RUMBLE_CURVE_RIGHT, 0x0
		call Rumble
		popad
		jmp sAddresses::_Rumble_Reset_JumpOut
	}
}

void patch()
{
	InjectHook(sAddresses::_Game_Version, _Game_Version_Patch, HOOK_JUMP);
	
	// These hooks always need to be applied, since both the Saturation and ADS FOV tweak rely on them
	InjectHook(sAddresses::_Get_Addresses, _Get_Addresses_Patch, HOOK_JUMP);
	InjectHook(sAddresses::_Apply_New_Values, _Apply_New_Values_Patch, HOOK_JUMP); 
	
	if (get_private_profile_bool("ControllerRumble", TRUE))
	{
		PatchByte(0x104F07F8, 0xEB); // jump over old rumble function call - no point to execute this all the time
		
		InjectHook(sAddresses::_Rumble_Effects, _Rumble_Effects_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_Rumble_Weapons, _Rumble_Weapons_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_Rumble_Reset, _Rumble_Reset_State_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_Rumble_Misc, _Rumble_Misc_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_Rumble_Strength_Sprint, _Rumble_Strength_Sprint_Patch, HOOK_JUMP);
	}
	
	// Same effect as setting "bUseRigidBased" to false for all enemies, buddies and animals in their respective *.xml files inside "entitylibrarypatchoverride"
	// This also appears to fix the floating Zebras I saw during earlier benchmark tests :D
	if (get_private_profile_bool("FixBouncingNPCs", FALSE))
	{
		PatchByte(0x10493CB9, 0xEB);
	}
	
	// Fix shorter grass in D3D10 mode
	// No idea what this mysterious value is actually about... The code that accesses it is only active when using DX10
	if (get_private_profile_bool("D3D10_GrassFix", TRUE))
	{ 
		PatchByte(0x11607DC4, 0x03); // For whatever reason this has to be set to "3" suddenly, when during all my previous testing it worked with a value of "1"
		Nop(0x103436D0, 6); // prevent value at 0x11607DC4 from being overwritten
	}
	
	// Fix clamping when moving mouse at high speed without having to edit \patch\config\inputactionmapcommon.xml
	if (get_private_profile_bool("MouseFix", TRUE))
	{
		InjectHook(sAddresses::_Mouse_Fix, _Mouse_Patch, HOOK_JUMP);
	}
	
	if (get_private_profile_bool("UnlockMachetes", TRUE))
	{
		PatchBytes(0x10048939, (unsigned char*)"\xB0\x01", 2);
	}

	if (get_private_profile_bool("UnlockPredecessorTapes", TRUE))
	{
		PatchBytes(0x102E1D15, (unsigned char*)"\xEB\x0E", 2);
	}

	if (get_private_profile_bool("DisableAimAssist", FALSE))
	{
		PatchBytes(0x107DA856, (unsigned char*)"\xE9\xDD\x00", 3);
	}

	if (get_private_profile_bool("FixJackalTapes", TRUE))
	{
		PatchByte(0x1074E464 + 1, 0x14);
	}

	if (get_private_profile_bool("SkipIntroMovies", FALSE))
	{
		Nop(0x108C735C, 9);
	}

	/* 
	    Restores critical healing animations on infamous difficulty:
	    Every difficulty level has values defined in xx_curves.xml, responsible for slowly draining the players life when going below 1 bar of health.
	    For infamous difficulty, FC2 fails to find the associated curve because it's incorrectly labeled "InfamousHealTime" instead of "InfamousDegenerationRate"...
	    The player simply dies as a result with 1 bar of health remaining, when the respective function skips over parts of the code.
	    Since the curve values are the exact same for each difficulty level regardless, we can spoof the current game difficulty in the "health degeneration function" only, having it apply a curve from any other difficulty instead.
	*/
	if (get_private_profile_bool("RestoreInfamousHealAnimations", TRUE))
	{
		BYTE RestoreCriticalHealAnimations[] = {
			0xBF, 0x02, 0x00, 0x00, 0x00, // mov edi, 0x02 // 2 = Hardcore difficulty
			0x90, 0x90                    // nop, nop
		};		
		PatchBytes(0x106A0FEE, RestoreCriticalHealAnimations);
	}

	if (get_private_profile_bool("CustomFOV", FALSE))
	{
		NEW_PLAYER_FOV = get_private_profile_float("PlayerFOV", "75.0f");
		NEW_VEHICLE_FOV = get_private_profile_float("VehicleFOV", "90.0f");
		ADS_FOV_MULTIPLIER = NEW_PLAYER_FOV / 75.0f; // Calculate the required FOV multiplier for ADS based on current player FOV
		
		InjectHook(sAddresses::_Vehicle_FOV, _Vehicle_FOV_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_Player_FOV, _Player_FOV_Patch, HOOK_JUMP);
		InjectHook(sAddresses::_fIronsightFOV_Get_Address, _fIronsightFOV_Get_Address_Patch, HOOK_JUMP);
	}

	if (get_private_profile_bool("CustomSaturation", TRUE))
	{
		NEW_SATURATION_VALUE = get_private_profile_float("SaturationAmount", "0.8f");
		InjectHook(sAddresses::_fSaturation_Get_Address, _fSaturation_Get_Address_Patch, HOOK_JUMP);
	}
	
	// Better Multithreading without having to unpack patch.dat and edit \patch\engine\settings\defaultthreadingconfig.xml 
	if (get_private_profile_bool("ImproveMultiThreading", TRUE))
	{
		RENDER_THREAD_COUNT = get_private_profile_int("RENDER_THREAD", 1);
		PHYSIC_THREADS_COUNT = get_private_profile_int("PHYSIC_THREADS", 4);
		JOB_THREADS_COUNT = get_private_profile_int("JOB_THREADS", 3);
		
		InjectHook(sAddresses::_Override_Threading_Config, _Override_Threading_Config_Patch, HOOK_JUMP);
	}

	if (get_private_profile_bool("ExtendedConsole", TRUE))
	{
		InjectHook(sAddresses::_Dev_Console, _Dev_Console_Patch, HOOK_JUMP);

		/* 
		    Some CVars require additional tweaking to be enabled, not sure how this works exactly though: 
			A value of 0x4 means disabled for use in the dev console, anything else controls whether it's float or int, and if the CVar is used in GamerProfile.xml I believe
		    Lots of these only seem to report the current settings but changing them ingame has no effect
		*/

		// 0xd = int, 0x9 = int, 0x11 = float, 0x15 = float ?

		//PatchByte(0x1040224A + 1, 0x9); // enable additional commands for display options
		PatchByte(0x103F5749 + 1, 0x15); // enable LOD & rendering distance related commands (works)

		
		PatchByte(0x103F4646 + 3, 0x15); // "SunShadowFadeRange"
		PatchByte(0x103F4856 + 3, 0xd); // "ShadowMapSize"
		PatchByte(0x103F48D5 + 3, 0xd); // "CascadedShadowMapSize"
		PatchByte(0x103F4954 + 3, 0xd); // "RainShadowMapSize"
		PatchByte(0x103F49D3 + 3, 0xd); // "SoftShadows" (works)
		PatchByte(0x103F4A52 + 3, 0xf); // "Use16BitFormat"
		//PatchByte(0x103F5397 + 3, 0x6); // "Shaders" ??? crashes the game at startup
		
		
		PatchByte(0x10048EBB + 3, 0xf); // "FireEnabled" (works)
		PatchByte(0x10048F39 + 3, 0xd); // "MultiCellArraySize"
		PatchByte(0x10048FB7 + 3, 0xf); // "FireSmokeEnabled"

		/*
		PatchByte(0x104022e2 + 3, 0x9); // "MultiSampleLevel"
		PatchByte(0x10402ba9 + 3, 0x9); // "NearPassZMin"
		PatchByte(0x10402c2c + 3, 0x9); // "NearPassZMax"
		PatchByte(0x10402caf + 3, 0x9); // "RenderQuality"
		PatchByte(0x104048a0 + 1, 0x9); // "Environment" "AntiPortal" "???" "Texture" "TextureResolution" "DepthPass" "Water" "Vegetation" "Terrain" "Geometry" "Ambient" "Shadow" quality
		PatchByte(0x10404d92 + 3, 0x9); // "AllowAsynchShaderLoading"
		*/
		
		PatchByte(0x103f7700 + 3, 0xd); // "ShadowMapSize"
		PatchByte(0x103f7783 + 3, 0xd); // "SectorCountX"
		PatchByte(0x103f7806 + 3, 0xd); // "SectorCountY"
		PatchByte(0x103f7889 + 3, 0xd); // "SectorTextureSize"
		//PatchByte(0x103f790c + 3, 0x15); // "Shaders" ???
		
		/*PatchByte(0x103f7280 + 3, 0x15); // "TerrainLodScale"
		
		PatchByte(0x103f6d66 + 3, 0x15); // "ReflectionMaxDistanceScaleModifier"
		PatchByte(0x103f6db0 + 3, 0xd); // "ReflectionTextureSizeX"
		PatchByte(0x103f6e79 + 3, 0xd); // "ReflectionTextureSizeY"
		PatchByte(0x103f6f87 + 3, 0xd); // "ReflectionMultiSampleMode"
		
		PatchByte(0x103f43fb + 3, 0x15); // ??
		PatchByte(0x103f4479 + 3, 0x15); // ??
		PatchByte(0x103f44f7 + 3, 0x15); // "remove" ??
		PatchByte(0x103f4575 + 3, 0x15); // "csmExcludeMask"

		PatchByte(0x103f4325 + 3, 0x15); // "UnSupportedPlatforms"

		PatchByte(0x103f687d + 3, 0x15); // "AntiPortalKillDistanceScale"
		PatchByte(0x103f68ff + 3, 0x15); // "AntiPortalKillDistanceFromCenter"
		
		PatchByte(0x103f79cb + 3, 0x15); // "TextureFilteringQuality"
		
		PatchByte(0x103f7b80 + 3, 0x9); // "DepthPassMode"
		*/
		PatchByte(0x103f7f46 + 3, 0xf); // "ResolutionX"
		PatchByte(0x103f7fc9 + 3, 0xf); // "ResolutionY"
		PatchByte(0x103f8044 + 1, 0xf); // "ShaderModel" & "VolatileTextureSize"
		PatchByte(0x103f8271 + 3, 0x9); // "EnvironmentQuality"
		PatchByte(0x103f82f4 + 3, 0x11); // "AntiPortalQuality"
		PatchByte(0x103f8377 + 3, 0xd); // "PostFxQuality"
		PatchByte(0x103f83fa + 3, 0xe); // "TextureQuality"
		PatchByte(0x103f847d + 3, 0x15); // "TextureResolutionQuality"
		PatchByte(0x103f8500 + 3, 0x14); // "WaterQuality"
		PatchByte(0x103f8583 + 3, 0xf); // "DepthPassQuality"
		PatchByte(0x103f8606 + 3, 0xf); // "VegetationQuality"
		PatchByte(0x103f8689 + 3, 0xf); // "TerrainQuality"
		PatchByte(0x103f870c + 3, 0xf); // "GeometryQuality"
		PatchByte(0x103f878f + 3, 0xf); // "AmbientQuality"
		PatchByte(0x103f8812 + 3, 0xf); // "ShadowQuality"

		PatchByte(0x1004b08a + 3, 0xf); // "QualitySetting"
		PatchByte(0x1004b10d + 3, 0xf); // "Qualities"
		}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (MEMCMP32(0x004011B5, 0x200415FF)) // Check for FarCry2.exe to prevent causing an error when launching FC2 benchmark tool. We will still inject into FarCry2.exe subsequently when a benchmark is started
		{
			init_private_profile();
			patch();
		}
	}

	return TRUE;
}
