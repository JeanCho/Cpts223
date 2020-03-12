/**
 *  Core graph data structure
 *   -- Overhauled to have better storage structures
 * 
 *  Contributors:
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   Aaron S. Crandall, 2019 <acrandal@gmail.com>
 */

#ifndef __GRAPH_H
#define __GRAPH_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <list>
#include <unordered_map>

#include "Vertex.h"

using namespace std;

class Graph
{
	unordered_map<int, Vertex*> verticies;

public:
	// Remove all vertices
	void clear() {
		verticies.clear();
	}

	// Number of vertices in our graph
	std::size_t size() {
		return verticies.size();
	}

	int edges_size() {
		int count = 0;
		for( auto vert : this->verticies ) {
			count += (vert.second)->edges_size();
		}
		return(count);
	}

	/**
	 *  Parses a single in from a dot file
	 */
	void parseDotfileLine( string line, regex newSubGraph ) {
		smatch matched;

		if( regex_match( line, matched, newSubGraph ) ) {
			string strconv = matched[1];
			int srcid = (int)::atof(strconv.c_str());
			strconv = matched[2];
			int destid = (int)::atof(strconv.c_str());
			strconv = matched[3];
			double weight = ::atof(strconv.c_str());
			//cout << "SrcID: " << srcid << " | DestID: " << destid << " | Edge Weight: " << weight << endl;

			Vertex* newSrcVert;
			Vertex* newDestVert;
			auto found = verticies.find(srcid);
			if( found == verticies.end() ) {	// No vertex by that ID yet - create it
				newSrcVert = new Vertex(srcid);
				verticies[srcid] = newSrcVert;
			} else {
				newSrcVert = (*found).second;
			}

			found = verticies.find(destid);
			if( found == verticies.end() ) {	// No vertex by that ID yet - create it
				newDestVert = new Vertex(destid);
				verticies[destid] = newDestVert;
			} else {
				newDestVert = (*found).second;
			}

			newSrcVert->addEdge(newDestVert, weight);
		}
	}

	/**
	 *  Loads a single Graphviz-(limited) formatted dot file with a graph
	 */
	void loadDotFile( string filename ) {
		cout << " Loading dot file: " << filename;
		ifstream ifs( filename );
		string instr;
		regex newSubGraph ("\\s*(\\S+)\\s*->\\s*(\\S+)\\s*\\[.*?weight=\"*(\\S+?)\"*\\s*\\]\\;");
		while (getline(ifs, instr)) {
			parseDotfileLine( instr, newSubGraph );
		}
		cout << " - Done." << endl;
	}

	/**
	 *  Returns stringified version of graph for viewing
	 */
	string to_string( bool with_edges = false ) {
		string ret = "Graph: \n";
		for( auto vert : this->verticies ) {
			ret += (vert.second)->to_string( with_edges ) + "\n";
		}
		return ret;
	}
	void set_indgree()//set indgree for each node
	{
		Vertex* vert;
		for(auto vertice : verticies)
		{
			vert = vertice.second;
			unordered_map<Vertex*, Edge*> Edges = vert->getEdges();
			for(auto Edge : Edges)
			{
				
				//cout<<Edge.first->indegree<<"\n"<<endl;
				int indegree =Edge.first->indegree;
				indegree++;
				Edge.first->setIndegree(indegree);
				//cout<<Edge.first->getId()<<" = ID  \n"<<endl;
				//cout<<indegree<<" = Indgree \n"<<endl;
				
			}
		}
	}

	//** Runs topological sort on this graph
	vector<int> run_topological_sort() {
		//** Start of toposort algorithm **//
		
		set_indgree();
		vector<int> toposort_results = {};
		int minInVert =999;
		int minVertID =0;
		int OriginalSize = verticies.size();
		Vertex* minVert;
		for(int i=0; i< OriginalSize; i++)
		{
			
			for(auto vertice : verticies)
			{
				
				if(vertice.second->indegree <= minInVert)
				{
					minInVert = vertice.second->indegree;
					minVertID = vertice.first;
					minVert = vertice.second;

					
				}
			}
							

			
			unordered_map<Vertex*, Edge*> Edges = minVert->getEdges();
			for(auto Edge : Edges) //before popping out decrees the indegree of the vectors that minVector points
			{
				int indi = Edge.first->indegree;
				//cout <<"Edge going to : "<< Edge.first->getId()<<"\n"<<endl;
				//cout<<"Initial indgree : "<< indi <<"\n"<<endl;
				indi = indi-1;
				
			
				
				Edge.first->setIndegree(indi);
				//cout<<"changed indgree : "<< Edge.first->indegree <<"\n"<<endl;
				//cout<<Edge.first->getId()<<"\n"<<endl;
			}
			toposort_results.push_back(minVertID);
			//cout<<"Indegree : "<<minVert->indegree<<"\n"<<endl;
			//cout<<"EDge size : "<< minVert->edges_size()<<"\n"<<endl;
			//cout<<"Pushing : "<<minVertID<<"\n"<<endl;
			//minVert->setIndegree(999);
			minInVert =999;
			verticies.erase(minVertID); //pop the min indgree vertex from graph
		//** Algorithm complete
		}

		return toposort_results;
		
	}

	//** Returns a vector of Node IDs from the topological sort
	vector<int> get_topological_sort_vector() {
		vector<int> toposort_results = run_topological_sort();

		// TODO: Extra Credit algorithm work goes here

		return toposort_results;
	}
};


#endif
