///////////////////////////////////////////////////////////////////////////
// DIJTRA ALGORITHM
///////////////////////////////////////////////////////////////////////////

#ifndef Dijkstra_H // include guard
#define Dijkstra_H
#endif

#include <sstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

  class Dijkstra  
  {
	   public :
		  Dijkstra();
		  ~Dijkstra();
		  vector<string>  StringSplit(const char* p_inputString, std::string p_delimiter, bool adjust);
		  int             minDistance(vector<int> dist, vector<bool> sptSet, int p_vertexSize);
		  string          GetDijkstra(vector<string> vertex, int p_vertexSize, int p_sampleSize, int p_sourcePoint);
		  void            SetDijkstra(int src, int vertexSize);
		  float           Pitagorean(float coord_x, float coord_y);
		  float           GetHipotemuza(const char*vertexString, int index_x, int index_y);
		  string          GenerateRandomMatrix(const char* vertexString, int p_vertexSize);
		  string          GetRandomPoints(int p_vertexSize, int p_sourcePoint);
	  public :
		  vector<int>         dist;
		  vector<string>      path;
		  vector<vector<int>> graph;
   };

