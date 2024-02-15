# NAAA-No-Afterlife-At-All-
##UWE Game Engine Programming Sarle 2024 - Return of order

PROJECT IS NOW RUNNABLE ON BOTH VISUAL STUDIO AND CLION DUE TO CMAKE

###running on clion:
make sure the toolchain is visual studio 
MINGW NOT COMPPATIBLE (due to directx math sdk)
run the cmakelists.txt and it will work

###running on visual studio:
run the cmakelists.txt and it will work




##nitty gritty techy stuff:
cmake now included so visual studio projects files removed meaning project is actually folder depenedent rather then virtual
cmake force sets the version to windows 10 + this stops issues like "audio2redist missing" - now baked into windows os since 8+
cmake force downloads directxtk version dec2023 so no need to push any of those files to repo also fixes issue of broken xtk files
cmake forse downloads bullet3 version 3.25 with flags to remove examples and extra robotics files
cmake copys models textures and sounds folder so rather then being file dependent you can just do {folder}/foo.so rahter then ../{folder}/foo.so


#DEBUGGING ERRORS
make sure all file strings have no "../{folder}" if they are "Assets,Sounds,Textures,Models"