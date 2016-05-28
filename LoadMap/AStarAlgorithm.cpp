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
			if (!graph[i][j].occupied)
			{
				Node node(j, i);
				hValue = estimatedHeuristicCost(node,goal);
				graph[i][j].hValue = hValue;
			}
		}
	}
}

void AStarAlgorithm::fillGAndFValues(Node from)
{
	int i,j;
	double currentGValue;
	closedSet.insert(from);
	for(i=from.row-1; i <=from.row+1; i++)
	{
		for(j=from.col-1; j <= from.col+1; j++)
		{
			if((i >= 0) && (j >= 0) && (i < graph.size()) && (j < graph[i].size()))
			{
				Node node(j, i);
				if (i == goal.row && j == goal.col )
				{
					graph[i][j].cameFromCol = from.col;
					graph[i][j].cameFromRow = from.row;
					graph[i][j].gValue = 0;
					graph[i][j].fValue = 0;
					openSet.insert(node);
				}
				else
				{
					bool inCloseSet = setContains(closedSet,node);
					if((graph[i][j].occupied == false)&&(((j != from.col)||(i != from.row)))&&(!inCloseSet))
					{
						currentGValue = distance(from, node);
						bool inOpenSet = setContains(openSet,node);
						if(inOpenSet)
						{
							if (graph[i][j].gValue > currentGValue)
							{
								graph[i][j].gValue = currentGValue;
								graph[i][j].fValue = graph[i][j].gValue + graph[i][j].hValue;
								graph[i][j].cameFromCol = from.col;
								graph[i][j].cameFromRow = from.row;
							}
						}
						else
						{
							graph[i][j].gValue = currentGValue;
							graph[i][j].fValue = graph[i][j].gValue + graph[i][j].hValue;
							graph[i][j].cameFromCol = from.col;
							graph[i][j].cameFromRow = from.row;
							openSet.insert(node);
						}
					}
				}
			}
		}
	}
}


vector<Node> AStarAlgorithm::StartAlgorithm()
{
	fillHeuristic();
	fillGAndFValues(start);
	Node lowestFValue;

	while (!openSet.empty())
	{
		lowestFValue.col = getLowestFValue().col;
		lowestFValue.row = getLowestFValue().row;

		if ((lowestFValue.col == goal.col) &&
			(lowestFValue.row == goal.row))
		{
			reconstructPath();

			return (totalPath);
		}

		openSet.erase(lowestFValue);
		fillGAndFValues(lowestFValue);
	}

	return (totalPath);
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
	if((from.col != to.col) && ( from.row != to.row))
	{
		return (graph[from.row][from.col].gValue + 14);
	}
	else
	{
		return (graph[from.row][from.col].gValue + 10);
	}
}

Node AStarAlgorithm::getLowestFValue()
{
	set<Node>::iterator index = openSet.begin();
	Node lowestFValue = *index;
	Node currentNode;

	for (index = openSet.begin(); index != openSet.end(); index++)
	{
		currentNode.col = index->col;
		currentNode.row = index->row;

		if (graph[currentNode.row][currentNode.col].fValue < graph[lowestFValue.row][lowestFValue.col].fValue)
		{
			lowestFValue.col = currentNode.col;
			lowestFValue.row = currentNode.row;
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
	double currentCol, currentRow, preCol, preRow;
	int i = 1;
	vector<Node> path;
	currentCol = goal.col;
	currentRow = goal.row;

	while ((currentCol != start.col)||(currentRow != start.row))
	{
		i++;
		preCol = currentCol;
		preRow = currentRow;
		currentRow = graph[preRow][preCol].cameFromRow;
		currentCol = graph[preRow][preCol].cameFromCol;
	}

	path.resize(i);
	totalPath.resize(i);
	i = 0;
	currentCol = goal.col;
	currentRow = goal.row;
	Node current(currentCol, currentRow);
	path[0] = current;
	while ((currentCol != start.col)||(currentRow != start.row))
	{
		i++;
		preCol = currentCol;
		preRow = currentRow;
		currentRow = graph[preRow][preCol].cameFromRow;
		currentCol = graph[preRow][preCol].cameFromCol;
		Node pre(currentCol, currentRow);
		path[i] = pre;
	}

	for (int j = path.size() - 1; j >= 0; j--)
	{
		totalPath[path.size() -1 - j] = path[j];
	}
}

AStarAlgorithm::~AStarAlgorithm() {
	// TODO Auto-generated destructor stub
}

