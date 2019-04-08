echo off

g++ Level.cpp -c

cd Physics
cmd /c compile
cd..

cd Objects
cmd /c compile
cd..

echo.
exit