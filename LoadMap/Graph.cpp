/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(double graphResolutionInCM) {
	this->graphResolutionInCM = graphResolutionInCM;
	this->resolutionRelation = 0;
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

			this->nodes[y][x].col = x;
			this->nodes[y][x].row = y;
			this->nodes[y][x].occupied = isCellOcupied;
		}
	}
}

Node Graph::getNodeFromCordinates(int x, int y)
{
	int row = y / resolutionRelation;
	int col = x / resolutionRelation;
	Node result(row,col);

	return result;
}

void Graph::paintPathOnMap(Map map, vector<Node *> path)
{
	Node current;

	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		current = *path[pathIndex];

		for (int i = current.row * resolutionRelation; i < (current.row * resolutionRelation) + resolutionRelation; i++)
		{
			for (int j = current.col * resolutionRelation; j < (current.col * resolutionRelation) + resolutionRelation; j++)
			{
				map.paintCell(i,j);
			}
		}
	}
}
