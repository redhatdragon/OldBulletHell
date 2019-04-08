echo off
echo.

echo compiling...
cd BluePyroGameEngine
cmd /c compile
cd..
g++ Graphics.c -c -lmingw32 -mwindows -mconsole^
 -L lib -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf^
 -I include -static-libstdc++
echo.

echo linking...
cd BluePyroGameEngine
cmd /c link
cd..
g++ Graphics.o main.cpp myActors.cpp -g^
 BluePyroGameEngine\GameEngine.a -lmingw32 -mwindows -mconsole^
 -L lib -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf^
 -I include -static-libstdc++
echo.
g++ Graphics.o LevelEditor.cpp myActors.cpp Ui.cpp -o LevelEditor^
 BluePyroGameEngine\GameEngine.a -lmingw32 -mwindows -mconsole^
 -L lib -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf^
 -I include -static-libstdc++
echo.


echo done
echo.
pause
exit