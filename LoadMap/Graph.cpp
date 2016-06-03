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

			this->nodes[y][x].occupied = isCellOcupied;
		}
	}
}

Point Graph::getPointFromCordinates(cordinates cordinate)
{
	int row = cordinate.y / resolutionRelation;
	int col = cordinate.x / resolutionRelation;
	Point res(row,col);
	return res;
}

void Graph::paintPathOnMap(Map *map, vector<Point> path, int r, int g, int b)
{
	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		paintPathOnMap(map, path[pathIndex],r,g,b);
	}
}

void Graph::paintPathOnMap(Map *map, Point point, int r, int g, int b)
{
	for (int y = point.row * resolutionRelation; y < (point.row * resolutionRelation) + resolutionRelation; y++)
	{
		for (int x = point.col * resolutionRelation; x < (point.col * resolutionRelation) + resolutionRelation; x++)
		{
			map->paintCell(y,x,r,g,b);
		}
	}
}

cordinates Graph::getCordinatesFromPoint(Point point)
{
	cordinates res;
	res.y = (point.row * resolutionRelation) + (resolutionRelation / 2);
	res.x = (point.col * resolutionRelation) + (resolutionRelation / 2);

	return (res);
}
