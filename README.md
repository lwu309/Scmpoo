<meta charset="UTF-8">

# STRAY SHEEP The Screen Mate

![Windows 3.1](/../images/Windows3.1.png?raw=true) ![Windows 10](/../images/Windows10.png?raw=true)

_STRAY SHEEP The Screen Mate_ (Japanese: STRAY SHEEP スクリーンメイト) is a [digital pet](https://en.wikipedia.org/wiki/Digital_pet) based on Fuji TV's multimedia project _STRAY SHEEP_ (Japanese: ストレイシープ). The application includes notable character animations in Fuji TV's late night animation _The Adventure of STRAY SHEEP_ (1994) (Japanese: ストレイシープの大冒険), featuring main characters such as the sheep Poe and Merry, along with the alien Hue.

This repository aims to reconstruct C source code from disassembly of the original 16-bit New Executable and add compatibility with 32-bit and 64-bit Windows (NT) operating systems.

Compiled executable files are available for download at [Releases](https://github.com/lwu309/Scmpoo/releases) page.

## Usage

Poe appears on desktop and normally chooses random actions (most likely run or walk) with certain probabilities. Some of the actions will play his voice. Seven special actions may occur at times only when there is only one instance running.

Poe will react to visible windows under certain circumstances. For example, Poe may collide with a visible window when running and switch to collision actions, or may fall onto the top edge of a visible window when gravity is enabled.

Up to 9 instances can be run simultaneously. An error message will appear when trying to run another instance exceeding that number. When there are multiple instances, one may collide with another and both will switch to collision actions.

Drag Poe with left/right mouse button to move him to an arbitrary position in the screen view.

Drag a file onto Poe and he will "eat" the file. If the file is a Waveform Audio (.wav), the sound contained will be played.

Double-click with left mouse button to bring up a configuration window. Four options can be modified and will be saved upon clicking "OK" button. Since the application tries to write to a .ini file in Windows directory, administrator privilege is required for the program on Windows Vista and above to save the options. You can exit the instance from the configuration window.

Double-click with right mouse button exits the instance.

Double-click with left mouse button with Ctrl and Shift buttons pressed down to bring up a debug window. Click on the 30 radio buttons to choose Poe's current action, which will take effect instantly. Click the four control buttons to move Poe instantly for 20 pixels by corresponding direction. Click "OK" button to close the debug window.

## Build from source

You can use CMake to generate Visual Studio projects and MinGW Makefiles. A minimum version of 3.16.0 is required.

## Copyright information and credits

Original codebase owned by Village Center, Inc. (defunct)

All character sprites in bitmap images owned by Fuji Television Network, Inc. and Robot Communications Inc.

Artwork: NOMURA Tatsutoshi (Robot)

Producer: SAITŌ Akimi (Fuji TV)

Poe's voice: HARA Masumi
