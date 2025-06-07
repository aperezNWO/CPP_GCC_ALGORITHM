mingw32-make --always-make --debug=v

cd ..

copy src\algorithm.dll dest\lib

copy src\algorithm.dll dest

move src\algorithm.dll src\_dist

cd src\_dist

dir *.*