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
	this->resolutionRelation = graphResolutionInCM / map.getMapResolution();
	int graphRows = map.getHeight() * map.getMapResolution() / graphResolutionInCM;
	int graphColumns = map.getWidth() * map.getMapResolution() / graphResolutionInCM;
	bool isCellOcupied;

	this->nodes.resize(graphRows);

	for (int index = 0; index <graphRows; index++)
	{
		this->nodes[index].resize(graphColumns);
	}

	for (int y = 0; y < graphRows; y ++)
	{
		for (int x = 0; x < graphColumns; x ++)
		{
			isCellOcupied = false;
			for (int i = (y * resolutionRelation) ; (i < (y * resolutionRelation) + resolutionRelation) && (!isCellOcupied); i++)
			{
				for (int j = (x * resolutionRelation); (j < (x * resolutionRelation) + resolutionRelation) && (!isCellOcupied); j++)
				{
					isCellOcupied = map.checkIfInflotedMapCellIsOccupied(i,j);
				}
			}

			(this->nodes[y][x])->setNode(y,x,isCellOcupied);
		}
	}
}

Node Graph::getNodeFromCordinates(int x, int y)
{
	int row = y / resolutionRelation;
	int col = x / resolutionRelation;

	return this->nodes[row][col];
}
