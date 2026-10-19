 "C:\msys64\ucrt64\bin\g++.exe"  -g AlgorithmAppTestDLL.cpp  -o AlgorithmAppTestDLL.exe  -m64
 
 move AlgorithmAppTestDLL.exe _dist
 
 cd _dist
 
 AlgorithmAppTestDLL.exe
 
 cd ..