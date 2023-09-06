# Factorio TAS Generator
This is a helper tool for generating **T**ool **A**ssisted **S**peedruns in Factorio. 

A guide of how to use the tool can be [found here](https://youtu.be/V9tuNoDqc0E?si=oDHc7VpP-eIK6BML).

Showcases: 
* Steelaxe%: [8:04 by EZRaiderz](https://www.youtube.com/watch?v=wbD-xbTWzFk&ab_channel=EZRaiderz) [7:46 by Theis](https://www.youtube.com/watch?v=4zAw3siu-n8&t=365s&ab_channel=Zaspar), [7:35 by Theis](https://youtu.be/CHAKin8ipbk?si=JLagreI1bqgo0RvJ)
* GOTLAP: [17:00 by EZRaiderz](https://www.youtube.com/watch?v=geEoRQ2JEbM&ab_channel=EZRaiderz)
* Zaspar_: [Any%](https://www.youtube.com/watch?v=1r-i5b153uw&t=1482s&ab_channel=Zaspar),  You can follow his progress on [twitch](https://www.twitch.tv/zaspar_). 

### Tooling
The [latest release](https://github.com/MortenTobiasNielsen/Factorio-TAS-Generator/releases) can stand on it's own, but some of these tools are recommended:

* [Game speed controls](https://mods.factorio.com/mod/game-speed) - To help zoom in on the important actions
* [TAS step planner](https://mods.factorio.com/mod/TAS_step_planner) - To help with building a plan from inside factorio
* [TAS Precision helper](https://mods.factorio.com/mod/Theis_tas_helper) - Provides precision control data and also shows list of TAS steps
* [TAS state printer](https://mods.factorio.com/mod/TAS_state_printer) - To help with run desyncs, when you have changed something in the past and it has cascading effect

If you find another tool, do let us know.

### Features and problems
**Bugs** can be reported through [Issues](https://github.com/MortenTobiasNielsen/Factorio-TAS-Generator/issues), and **new features** can be requested there too.

## Developer setup
Do you want to help?
To get started you need [MS Visual studio](https://visualstudio.microsoft.com/downloads/), [MSYS2](https://www.msys2.org/) and [vcpkg](https://vcpkg.io/en/getting-started.html) 
You will need to install wxWidget through MSYS
It is recommended to also install wxFormBuilder, if you want to change GUI elements.

## How it works
This tools works by converting a list of steps into a Factorio mod. The mod will then force the character to execute each step until it reaches the goal.
The list of steps is saved in a csv-like text file, and is displayed in grid table through the tool.

Steps are executed using [Factorio's Lua API](https://lua-api.factorio.com/latest/), so while we strife to simulate realistic inputs there are still differences.
A few of the more noteworthy differences:
* Huge rocks always yield 47 coal and 47 stone. Instead of the random yields in regular play, which can create some hard to deal with incosistencies.
* Construction robots are not available.
* The TAS doesn't need the cursor, however it is still bound by character reach distance.
* Saving the game has to be done through the tool.
