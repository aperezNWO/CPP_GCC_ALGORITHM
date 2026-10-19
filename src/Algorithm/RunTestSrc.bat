 "C:\msys64\ucrt64\bin\g++.exe" -std=c++20 -g AlgorithmAppTestSrc.cpp  include\Dijkstra.cpp include\RegExManager.cpp include\SortBenchMark.cpp include\Sudoku.cpp include\TFileManager.cpp -o AlgorithmAppTestSrc.exe -Iinclude -DALGORITHM_EXPORTS -m64

move AlgorithmAppTestSrc.exe _dist

cd _dist

AlgorithmAppTestSrc.exe

cd ..

cls
