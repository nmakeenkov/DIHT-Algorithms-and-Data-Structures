#ifndef _NET_H_
#define _NET_H_

#include<vector>
#include<queue>
#include<istream>
#include<ostream>
#include"FlowEdge.h"
#include"Graph.h"
#include"BFSGraph.h"

template<typename CapacityType>
class Net;

template<typename CapacityType>
std::istream &operator>>(std::istream &in, Net<CapacityType> &g);

template<typename CapacityType>
std::ostream &operator<<(std::ostream &out, Net<CapacityType> &g);

template<typename CapacityType>
class Net : public Graph {
protected:
	CapacityType flow;
	std::vector<std::vector<FlowEdge<CapacityType> *> > e;
public:
	Net() : Graph(), flow(), e(0) {}
	
	size_t getV() const;

	friend std::istream &operator>> <>(std::istream &in, 
			Net<CapacityType> &g);
	friend std::ostream &operator<< <>(std::ostream &out, 
			Net<CapacityType> &g);
    template<class Graph, class IsValidEdgeFunction>
    friend void BFSGraph::bfs(Graph const &graph, int start, std::vector<int> &distanceToVertex,
                       IsValidEdgeFunction const &isValidEdge);
    friend class FlowSolver;
    friend class DinicFlowSolver;
    friend class PreflowPushFlowSolver;
};

#include"Net.cpp"

#endif
