echo off

ar rvs GameEngine.a Level.o^
 Objects\Object.o Objects\Objects.o^
 Physics\Physics.o Physics\SpatialHash.o Physics\PhysicsEngine.o

echo.


echo done
echo.
exit