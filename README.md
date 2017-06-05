# Deputy Arsh

### What is Deputy Arsh?

Deputy Arsh is a simple monochrome endless runner game for the Atari ST. It was written in C/68000 ASM, with the goal of using no operating system features (aside from the supervisor toggle to access restricted memory).
Everything in Deputy Arsh was written from scratch, including the raster library, sound generation library, custom interrupt vectors, and keyboard/mouse drivers.

![alt text](http://i.imgur.com/lMdaoeY.png "Main Menu")


### Installation

Deputy Arsh can theoretically be played on a real Atari ST, but I don't own one so unfortunately I have never been able to test this.

It can also be played on [Steem Engine](http://steem.atari.st/index.htm), an Atari ST emulator.
Either way once you have the source files on your ST platform of choice you can use my makefile to compile with cc68x, or you can just download **DEP_ARSH.TOS** from this repo.

### Gameplay

[![Gameplay Demo](http://i.imgur.com/52klID4.png)](https://youtu.be/lHjaTq1UsAY)

**JUMP** over **HAYBALES** by pressing **Z**.

**KICK** through **CACTI** by pressing **X**.

**SLIDE** under **VULTURES** by pressing **C**.

The longer you survive the higher your score.

You can also toggle your skin to the unused player 2 sprite by pressing **P**, quit the game by pressing **Q** (CTRL-C won't work because Deputy Arsh takes control of the keyboard from the OS).

You can navigate the main menu and game over screen with either the arrow keys/enter or the mouse.

### FAQ

#### Why are there so few commits?
This project originally used SVN for source control, but once it was done I decided to put it here.

#### Why didn't you use dynamic memory?
I didn't use dynamic memory because normally the OS handles a lot of it and it would've been as much work as the whole game to write it myself.

#### Will there be a sequel?
Ok ok no one is asking this, but I've been thinking about learning Unity/UE4 by making Deputy Arsh: Colour. Coming soon to a theater near you!

![alt text](http://i.imgur.com/zmQPKEH.png "End Screen")

