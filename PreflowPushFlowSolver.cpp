#ifndef _PREFLOWPUSHFLOWSOLVER_CPP_
#define _PREFLOWPUSHFLOWSOLVER_CPP_

#include"PreflowPushFlowSolver.h"
#include<queue>

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::relable(int v) {
	int newh = Net<CapacityType>::getV() * 2;
	for (int i = 0; i < (int)Net<CapacityType>::e[v].size(); ++i) {
		FlowEdge<CapacityType> *ed = Net<CapacityType>::e[v][i];
		if (ed->getCap() > ed->getFlow()) {
			newh = std::min(h[ed->getVert()] + 1, newh);
		}
	}
	hCnt[h[v]]--;
	int gapC = Net<CapacityType>::getV();
	if (hCnt[h[v]] == 0)
		gapC = h[v];	
	h[v] = newh;
	hCnt[h[v]]++;
	if (gapC < Net<CapacityType>::getV()) {
		for (int i = 0; i < (int)h.size(); ++i) {
			if (h[i] > gapC && h[i] < Net<CapacityType>::getV()) {
				hCnt[h[i]]--;
				h[i] = Net<CapacityType>::getV();
				hCnt[h[i]]++;
			}
		}
	}
}

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::push(int v, 
		FlowEdge<CapacityType> *e) {
	CapacityType f = std::min(exc[v], e->getCap() - e->getFlow());
	e->incFlow(f);
	exc[v] -= f;
	int u = e->getVert();
	exc[u] += f;
	if (exc[u] > CapacityType() && exc[u] <= f) { // was <= 0 
			// and now >= 0
		q.push(u);
	}
}

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::runPreflowPush(int s, 
		int t) {
	h = std::vector<int>(Net<CapacityType>::getV(), 0);
	hCnt = std::vector<int>(Net<CapacityType>::getV() * 2, 0);
	hCnt[Net<CapacityType>::getV()] = 1;
	hCnt[0] = Net<CapacityType>::getV() - 1;
	h[s] = Net<CapacityType>::getV();
	exc = std::vector<CapacityType>(Net<CapacityType>::getV(), 
			CapacityType());
	for (int i = 0; i < (int)Net<CapacityType>::e[s].size(); ++i) {
		FlowEdge<CapacityType> *ed = Net<CapacityType>::e[s][i];
		ed->incFlow(ed->getCap());
		exc[ed->getVert()] += ed->getCap();
		exc[s] -= ed->getCap();
	}
	for (int i = 0; i < (int)Net<CapacityType>::e[t].size(); ++i) {
		exc[t] -= Net<CapacityType>::e[t][i]->getRev()->getCap();
	}
	for (int i = 0; i < (int)Net<CapacityType>::getV(); ++i) {
		if (exc[i] > 0) {
			q.push(i);
		}
	}
	std::vector<int> ind(Net<CapacityType>::getV(), 0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		while (exc[v] > 0) {
			if (ind[v] == (int)Net<CapacityType>::e[v].size()) {
				relable(v);
				ind[v] = 0;
			} else {
				FlowEdge<CapacityType> *ed = 
						Net<CapacityType>::e[v][ind[v]];
				if (ed->getCap() - ed->getFlow() > CapacityType() 
						&& h[ed->getVert()] == h[v] - 1) {
					push(v, ed);		
				} else {
					ind[v]++;
				}
			}
		}
	}
	Net<CapacityType>::flow = -exc[s];
}

#endif
