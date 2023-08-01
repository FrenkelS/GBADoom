
## GBADoom for DOS

A port of **[GBADoom](https://github.com/doomhack/GBADoom)** to DOS. The biggest change is in [source\i_system_dos.c](https://github.com/FrenkelS/GBADoom/blob/master/source/i_system_dos.c). Download **GBADoom.exe** [here](https://github.com/FrenkelS/GBADoom/releases).

**What's different?:**
 - No sound and music
 - No saving and loading
 
## Controls:
|Action      |GBA   |DOS                     |
|------------|------|------------------------|
|Fire        |B     |Ctrl                    |
|Use / Sprint|A     |Enter, Space & Shift    |
|Walk        |D-Pad |Arrow keys              |
|Strafe      |L & R |< & >                   |
|Automap     |SELECT|Tab                     |
|Weapon up   |A + R |Enter, Space & Shift + >|
|Weapon down |A + L |Enter, Space & Shift + <|
|Menu        |Start |Esc                     |
|Quit to DOS |      |F10                     |

## Building:
1) Install [DJGPP](https://github.com/andrewwutw/build-djgpp) to C:\Progs\djgpp\

2) Run `makedos.bat`
