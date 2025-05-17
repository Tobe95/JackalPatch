# Jackal Patch

<img src="/assets/JackalPatch.gif" alt="Banner">

## Description

Injecting into Far Cry 2's code at runtime, this patch aims to fix the game's most prevalent issues while leaving the game files completely untouched. In a similar fashion to "FC2 Multi Fixer" it also includes some QoL improvements without altering the original gameplay experience in any way. While not specifically tested, it should be compatible with most mods due to its implementation.

## Features

- Fix some general issues: Jackal Tapes Bug, Infamous Critical Healing Animations, Mouse Clamping

- Fix grass rendering in DirectX 10 mode

- Fix bouncing NPCs bug occuring at high framerates (for the most part)

- Unlock Bonus Content: Additional Machetes and Predecessor Missions 

- Extended Developer Console with new CVars for cheats, AI, environment & graphical settings

- Adjustable Saturation - No need to use third party tools like ReShade for vibrant colors

- Controller Rumble (experimental) for XInput compatible devices such as Xbox360 & XboxOne gamepads, SteamDeck etc.

- Disable gamepad aim assist

- Slightly improved performance by changing the game's threading configuration

- Custom FOV

## Installation

1. Download the latest version of [Ultimate-ASI-Loader.zip] (https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases)

2. Download Jackal Patch from the [releases] (https://github.com/Tobe95/JackalPatch/releases) page 

3. Drop the contents of both archives into ```/path/to/game/Far Cry 2/bin``` next to ```FarCry2.exe```.

4. Locate ```JackalPatch.ini``` inside the ```scripts``` folder and change the settings to your liking with a text editor, afterwards launch the game as usual. Done!

- Extra step for Linux & SteamDeck with Proton/Wine: Paste the following into your Far Cry 2 launch options in Steam, Bottles, etc.: ```WINEDLLOVERRIDES="dinput8=n,b" %command%```

## Known Issues

- Changing FOV has no effect on aiming down sights until the player switches weapons once - This is due to the game storing the ADS FOV value for the currently equipped weapon inside the savegame

- Something similar applies for loading a save where the player is seated in a vehicle after changing vehicle FOV. To have the new FOV apply, one has to exit and re-enter the vehicle

- Using mounted machine guns can cause controller vibration to temporarily bug out due to the high rate of fire

## Supported Versions

- Far Cry 2 v.1.0.3 (Fortunes Edition)

## Credits

Many thanks to the following people:

- Sergeanur - [Eagle Patch] (https://github.com/Sergeanur/EaglePatch) for Assassin's Creed served as both a template and inspiration for this project

- Withmorten - For the [win32 patcher] (https://github.com/withmorten/patcher) that Jackal Patch relies on

- ThirteenAG - For [ASI plugin loading] (https://github.com/ThirteenAG/Ultimate-ASI-Loader)

- Boggalog - [An Almost Complete Guide to Far Cry 2 Modding] (https://www.nexusmods.com/farcry2/mods/299) was an invaluable resource in the process of making this patch

- scubrah - For the original [Bouncing NPCs Fix] (https://www.nexusmods.com/farcry2/mods/309)

- Lawrence McCauley - For the [tutorial] (https://lcmccauley.wordpress.com/2014/01/06/gamepadtutorial-part2/) on XInput and the included rumble function

## Tools Used

Ghidra, Cheat Engine, x32dbg, FC2 Enhanced Gibbed Tools
