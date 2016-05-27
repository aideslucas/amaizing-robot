/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(double graphResolutionInCM) {
	this->graphResolutionInCM = graphResolutionInCM;
}

Graph::~Graph() {

}

void Graph::buildGraphFromMap(const Map map)
{
	int resolutionRelation = graphResolutionInCM / map.getMapResolution();
	int graphRows = map.getHeight() * map.getMapResolution() / graphResolutionInCM;
	int graphColumns = map.getWidth() * map.getMapResolution() / graphResolutionInCM;
	bool isCellOcupied;

	this->nodes.resize(graphRows);

	for (int index = 0; index <graphRows; index++)
	{
		this->nodes[index].resize(graphColumns);
	}

	for (int y = 0; y < (graphRows * resolutionRelation); y += resolutionRelation)
	{
		for (int x = 0; x < (graphColumns * resolutionRelation); x += resolutionRelation)
		{
			isCellOcupied = false;
			for (int i = y ; (i < y + resolutionRelation) && (!isCellOcupied); i++)
			{
				for (int j = x ; (j < x + resolutionRelation)&&(!isCellOcupied); j++)
				{
					isCellOcupied = map.checkIfInflotedMapCellIsOccupied(i,j);
				}
			}

			(this->nodes[y / resolutionRelation][x / resolutionRelation])->setNode(y,x,isCellOcupied);
		}
	}
}

