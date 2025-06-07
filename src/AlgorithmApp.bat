"C:\msys64\ucrt64\bin\g++.exe"  -g AlgorithmApp.cpp include\Dijkstra.cpp include\RegExManager.cpp include\SortBenchMark.cpp include\Sudoku.cpp include\TFileManager.cpp -o AlgorithmApp.exe -Iinclude  -m64

move AlgorithmApp.exe _dist

cd _dist

AlgorithmApp.exe

cd ..

cls
