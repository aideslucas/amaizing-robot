/*
 * AStarAlgorithm.cpp
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#include "AStarAlgorithm.h"

AStarAlgorithm::AStarAlgorithm(vector<vector<point> > graph, Node start, Node goal) {
	this->goal = goal;
	this->graph = graph;
	this->start = start;
}

void AStarAlgorithm::fillHeuristic()
{
	double hValue;

	for (int i = 0; i < graph.size(); i++)
	{
		for(int j = 0; j< graph[i].size(); j++)
		{
			Node node(j, i);
			hValue = estimatedHeuristicCost(node,goal);
			graph[i][j].hValue = hValue;
		}
	}
}


vector<Node *> AStarAlgorithm::StartAlgorithm()
{
	fillHeuristic();
	set<Node> closedSet;
	set<Node> openSet;
	Node current;
	double tentativeGValue;
	vector<Node *> path;

	openSet.insert(start);
	graph[start.row][start.col].gValue = 0;
	graph[start.row][start.col].fValue = graph[start.row][start.col].hValue;

	while (!openSet.empty())
	{
		current = getLowestFValue(openSet);
		if (current.row == goal.row && current.col == goal.col)
		{
			path = reconstructPath();
			return path;
		}

		openSet.erase(current);
		closedSet.insert(current);

		for (int y = current.row-1; y <= current.row+1; y++)
		{
			for (int x = current.col-1; x <= current.col+1; x++)
			{
				if (y < 0 || y >= graph.size() || x < 0 || x >= graph[y].size())
				{
					continue;
				}

				Node neighbour(x,y);
				if (setContains(closedSet,neighbour))
				{
					continue;
				}

				tentativeGValue = graph[current.row][current.col].gValue + distance(current, neighbour);

				if (!setContains(openSet,neighbour))
				{
					openSet.insert(neighbour);
				}
				else if (tentativeGValue >= graph[neighbour.row][neighbour.col].gValue)
				{
					continue;
				}

				graph[neighbour.row][neighbour.col].cameFromRow = current.row;
				graph[neighbour.row][neighbour.col].cameFromCol = current.col;
				graph[neighbour.row][neighbour.col].gValue = tentativeGValue;
				graph[neighbour.row][neighbour.col].fValue = tentativeGValue + graph[current.row][current.col].hValue;
			}
		}
	}

	return path;
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

		if (graph[currentNode.row][currentNode.col].fValue < graph[lowestFValue.row][lowestFValue.col].fValue)
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

vector<Node *> AStarAlgorithm::reconstructPath()
{
	Node current (goal.col, goal.row);
	int i = 1;
	while (current.col != start.col || current.row != start.row)
	{
		i++;
		current.row = graph[current.row][current.col].cameFromRow;
		current.col = graph[current.row][current.col].cameFromCol;
	}

	vector<Node *> path;
	path.resize(i);
	path[0] = &goal;
	i = 0;
	current.row = goal.row;
	current.col = goal.col;

	while (current.col != start.col || current.row != start.row)
	{
		i++;
		current.row = graph[current.row][current.col].cameFromRow;
		current.col = graph[current.row][current.col].cameFromCol;
		path[i] = &current;
	}

	vector<Node *> totalPath;
	totalPath.resize(path.size());

	for (i = path.size(); i >=0; i--)
	{
		totalPath[path.size() - i] = path[i];
	}

	return totalPath;
}

AStarAlgorithm::~AStarAlgorithm() {
	// TODO Auto-generated destructor stub
}

