/*
 * AStarAlgorithm.cpp
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#include "AStarAlgorithm.h"

AStarAlgorithm::AStarAlgorithm(vector<vector<Node> > graph, Node start, Node goal) {
	this->graph = graph;
	this->goal = graph[goal.row][goal.col];
	this->start = graph[start.row][start.col];
}

void AStarAlgorithm::fillHeuristic()
{
	int k = graph.size();
	int m = graph[0].size();
	for (unsigned int i = 0; i < graph.size(); i++)
	{
		for(unsigned int j = 0; j< graph[i].size(); j++)
		{
			if (!graph[i][j].occupied)
			{
				graph[i][j].hValue = estimatedHeuristicCost(graph[i][j],goal);
			}
		}
	}
}

vector<Node> AStarAlgorithm::StartAlgorithm()
{
	fillHeuristic();
	closedSet.clear();
	openSet.clear();

	graph[start.row][start.col].gValue = 0;
	graph[start.row][start.col].fValue = graph[start.row][start.col].hValue;

	openSet.insert(graph[start.row][start.col]);

	while (!openSet.empty())
	{
		Node current = getLowestFValue();
		if (current == goal)
		{
			reconstructPath();
			return totalPath;
		}

		openSet.erase(current);
		closedSet.insert(current);

		for(int y = current.row -1; y <= current.row + 1; y++)
		{
			for(int x = current.col -1; x <= current.col + 1; x++)
			{
				if (y >= 0 && y < graph.size() &&
					x >= 0 && x < graph[0].size() && !graph[y][x].occupied)
				{
					if (setContains(closedSet, graph[y][x]))
					{
						continue;
					}

					int tentativeGValue = current.gValue + distance(current, graph[y][x]);

					if (setContains(openSet,graph[y][x]) || tentativeGValue >= graph[y][x].gValue)
					{
						continue;
					}

					graph[y][x].parentRow = current.row;
					graph[y][x].parentCol = current.col;
					graph[y][x].gValue = tentativeGValue;
					graph[y][x].fValue = graph[y][x].gValue + graph[y][x].hValue;

					if (!setContains(openSet,graph[y][x]))
					{
						openSet.insert(graph[y][x]);
					}
				}
			}
		}
	}

	return totalPath;
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

			if (indexNode == current)
			{
				return true;
			}
		}
	}

	return false;
}

double AStarAlgorithm::distance(Node from, Node to)
{
	if((from.col != to.col) && ( from.row != to.row))
	{
		return (14);
	}
	else
	{
		return (10);
	}
}

Node AStarAlgorithm::getLowestFValue()
{
	set<Node>::iterator index = openSet.begin();
	Node lowestFValue = *index;
	Node currentNode;

	for (index = openSet.begin(); index != openSet.end(); index++)
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
	int dx = from.col - to.col;
	int dy = from.row - to.row;

	double dist = pow(dx,2) + pow(dy,2);

	return sqrt(dist);
}

void AStarAlgorithm::reconstructPath()
{
	int i = 1;
	//set<Node> path;
	//path.insert(graph[goal.row][goal.col]);
	Node current = graph[goal.row][goal.col];
	while (current != graph[start.row][start.col])
	{
		i ++;
		current = graph[current.parentRow][current.parentCol];
		//path.insert(current);
	}
	//path.insert(graph[start.row][start.col]);

	totalPath.resize(i);
	current = graph[goal.row][goal.col];
	totalPath[i - 1] = current;
	i = i - 2;
	//set<Node>::iterator index;
	for (; i >= 0; i--)
	{
		totalPath[i] = current;
		current = graph[current.parentRow][current.parentCol];
	}
}

AStarAlgorithm::~AStarAlgorithm() {
	// TODO Auto-generated destructor stub
}

