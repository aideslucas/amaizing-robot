/*
 * AStarAlgorithm.cpp
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#include "AStarAlgorithm.h"
#include "math.h"

AStarAlgorithm::AStarAlgorithm(vector<vector<Node> > graph, Node start, Node goal) {
	this->goal = goal;
	this->graph = graph;
	this->start = start;
}

set<Node> AStarAlgorithm::StartAlgorithm()
{
	set<Node> closedSet;
	set<Node> openSet;
	Node current;
	Node neighbour;
	double tentativeGValue;

	openSet.insert(start);

	start.gValue = 0;
	start.fValue = estimatedHeuristicCost(start, goal);

	while (!openSet.empty())
	{
		current = getLowestFValue(openSet);
		if (current.row == goal.row && current.col == goal.col)
		{
			return reconstructPath();
		}

		openSet.erase(current);
		closedSet.insert(current);

		for (int y = current.row-1; y <= current.row+1; y++)
		{
			for (int x = current.col-1; x <= current.col+1; x++)
			{
				neighbour = graph[y][x];
				if (setContains(closedSet,neighbour))
				{
					continue;
				}

				tentativeGValue = current.gValue + distance(current, neighbour);

				if (!setContains(openSet,neighbour))
				{
					openSet.insert(neighbour);
				}
				else if (tentativeGValue >= neighbour.gValue)
				{
					continue;
				}

				neighbour.cameFrom = &current;
				neighbour.gValue = tentativeGValue;
				neighbour.fValue = tentativeGValue + estimatedHeuristicCost(neighbour, goal);
			}
		}
	}
}

bool AStarAlgorithm::setContains(set<Node> nodeSet, Node current)
{
	set<Node>::iterator index;
	Node indexNode;

	if (!nodeSet.empty())
	{
		for (index = nodeSet.begin(); index != nodeSet.end(); index++)
		{
			indexNode = *index;

			if ((indexNode.col == current.col) &&
				(indexNode.row == current.row))
			{
				return true;
			}
		}
	}

	return false;
}

double AStarAlgorithm::distance(Node from, Node to)
{
	int dx = from.col - to.col;
	int dy = from.row - to.row;

	double dist = pow(dx,2) + pow(dy,2);

	return sqrt(dist);
}

const Node AStarAlgorithm::getLowestFValue(const set<Node> nodeSet)
{
	set<Node>::iterator index = nodeSet.begin();
	Node lowestFValue = *index;
	Node currentNode;

	for (index = nodeSet.begin(); index != nodeSet.end(); index++)
	{
		currentNode = *index;

		if (currentNode.fValue < lowestFValue.fValue)
		{
			lowestFValue = currentNode;
		}
	}

	return lowestFValue;
}

double AStarAlgorithm::estimatedHeuristicCost(Node from, Node to)
{

	return distance(from,to);
}

set<Node> AStarAlgorithm::reconstructPath()
{
	Node current, cameFrom;
	current = goal;
	int i = 1;
	while (current.col != start.col || current.row != start.row)
	{
		i++;
		current = *current.cameFrom;
	}

	vector<Node> path;
	path.resize(i);
	path[0] = goal;
	i = 0;
	current = goal;
	while (current.col != start.col || current.row != start.row)
	{
		i++;
		current = *current.cameFrom;
		path[i] = current;
	}

	set<Node> totalPath;

	for (i; i >=0; i--)
	{
		totalPath.insert(path[i]);
	}

	return totalPath;
}

AStarAlgorithm::~AStarAlgorithm() {
	// TODO Auto-generated destructor stub
}

