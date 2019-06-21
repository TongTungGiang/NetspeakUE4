# Netspeak Games Coding Test
Progress note

## Toolset
- Unreal Engine version: 4.20.x
    - Starting template: Topdown.

- Visual Studio 2017, with VAX.

- Git Bash

## Daily notes

#### Thursday, 20th June 2019
- Morning: Got the doc from Callum.
- 15.00: Had some free time at work, decided to setup the project on GitHub private. My approach was starting from Item 1 (Farming) with single player mode to get myself familiar with UE4 - from what I'd read earlier about the UE4's multiplayer architecture, it should be easy to switch from single to multi.
- 15.15: Things got set up nicely. Time to commit.
- 15.40: Got another bunch of free time at work. I'm gonna get rid of mouse-based navigation and switch to arrow key-based navigation. Assuming currently I'll only let gamers interact with the map with keyboard. Mouse interaction, such as with cell states, will be in future work category.
- 21.00: Finished dinner. 
    - Next 2 hours plan: 
        - Design for bullet #1: _Programatically generate a grid of slots and have slot states_ and #2 _Have each slot be able to transition from sensible farm based states_.
        - Make a cube mesh to mark the "selected" slot for the character.
    - Design decision:
        - Obviously, we can save a lot of space by not storing empty cells.
        - State machine fits quite well with the situation: I can control the flows between states easily and clearly. Gotta read about UE4's approach on interfaces though. I plan to use something like an ISlot C++ interface with generic functions like get appearance info or switch to another state. Specific classes can derive from it, ideally with blueprint so that designers can change some details, such as state transition.
    - Player movement: I'll have a cube mesh to mark the player's selected slot. Should be easy, but I'll do it in C++ as it involves some vector athrimetic. I'm not comfortable doing so with BP.
        - I tried to have a scene component attached to the player actor, but it'd be easier to have a separate actor just follow the player actor. This would help in multiplayer as well, because this is trivial and can easily be interpolated from player's position - no need to replicate at all.
        - Not sure why when I use this code, the player stops moving. Will investigate tomorrow: `if (Target) SetActorLocation(Target->GetActorLocation());`
    - *Side notes*: Currently I'm grouping source code files into task folder, eg Farming, Moving..., because that's the way I work in Unity. If this is not a recommended folder structure, please make a comment and I appreciate that :)

#### Friday, 21th June 2019
- 14.30: Had an hour of free time at work after the lunch break. Decided to continue working on the marker mechanics. The bug turned out to be the physics settings blocks player's movement. Disable collision of marker actor in C++ constructor then things are fine.
    - Got a moment of confusion in debugging because instructions keep running around (_randomly_?), not sequentially as I expected. Local variable values are also messed up => That was caused by binary optimization, switched to _DebugGame Editor_ instead of _Development Editor_ makes the debugger works as expected. Thank you StackOverflow!
    - The basic idea for the mechanics: 
        - I use player forward direction to decide which slot to put the marker.
        - A static const array in the cpp file is used to store allowed direction (currently just Forward/Backward and Left/Right, but we can easily add other directions if the situation needs, while still being by the vector athrimetic).
        - Dot product operation is used to see which direction is "closest" to where the player is heading at right now.
        - Things still don't work correctly with negative direction cases, gonna check them out this evening.