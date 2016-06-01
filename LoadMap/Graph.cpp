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
	return this->nodes[row][col];
}

void Graph::paintPathOnMap(Map *map, vector<Node> path, int r, int g, int b)
{
	int row,col;

	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		paintPathOnMap(map, path[pathIndex],r,g,b);
	}
}

void Graph::paintPathOnMap(Map *map, Node node, int r, int g, int b)
{
	int row = node.row;
	int col = node.col;
	for (int i = row * resolutionRelation; i < (row * resolutionRelation) + resolutionRelation; i++)
	{
		for (int j = col * resolutionRelation; j < (col * resolutionRelation) + resolutionRelation; j++)
		{
			map->paintCell(i,j,r,g,b);
		}
	}
}
