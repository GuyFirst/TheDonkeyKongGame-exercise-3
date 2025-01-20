****************************************************************************************************************************************
Names:
Guy First   ID 322372681
Ori Perlman ID 212198949

****************************************************************************************************************************************
Overview
This game is a classic "Donkey Kong"-style arcade game where Mario must save Pauline while avoiding hazards.
The game involves multiple levels with different screen layouts that are loaded from external text files.
In addition, in this exercise special bonuses like hammers and ghosts have been introduced to make the gameplay more exciting.

****************************************************************************************************************************************
Mario Movement & Interactions:
Mario can walk on floors, climb ladders, and jump between platforms.

****************************************************************************************************************************************
IMPORTANT!
To compile the project, make sure the language standart is lease from c++17 (to support the file reading)
****************************************************************************************************************************************
Supported Screen Sizes:
The game is designed to work within a console of size 80x25 (width x height). Our implement DOES NOT support screens that are either smaller than 80X25, or larger than 80X25.
****************************************************************************************************************************************

Additional Features:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Bonus 1: Slow Prints:
Certain game actions, such as screen transitions, are printed slowly for better visual appeal.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Bonus 2: Official Mario, and Donkey Kong Theme Music: 
The menu includes the option to play the iconic Mario theme music, and every stage starts with
the iconic "How High Can You Get" theme from "Donkey Kong Original 1981", for an immersive experience.
Please feel free to delete the music function in the Game::StartGame function,
I left comments in the function to note whiche lines to delete.
(the music is based only on Beep function inside Windows library,
but it might won't work properly if you use specific speakers.)
if you don't familiar with the music, you may visit the link and hear from 00:17:
https://www.youtube.com/watch?v=KJkcNP4VkiM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Bonus 3: Explosion Animation:
When barrels explode, an animated visual is displayed to enhance the experience.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Gameplay Mechanics
Mario & Free Fall:
When Mario is in free fall (e.g., falling off a platform or ladder), He cannot change directions.





