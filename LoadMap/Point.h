/*
 * Point.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_
#include "limits.h"

class Point {
public:
	int row;
	int col;

	Point();
	Point(int row, int col);

	void operator()(int col, int row)
	{
		this->col = col;
		this->row = row;
	}
	bool operator<(const Point& point) const
	{
		return (row*INT_MAX + col < point.row*INT_MAX + point.col);
	}
	void operator=(const Point& point)
	{
		this->col = point.col;
		this->row = point.row;
	}
	bool operator==(const Point& point) const
	{
		return (this->col == point.col && this->row == point.row);
	}
	bool operator!=(const Point& point) const
	{
		return (this->col != point.col || this->row != point.row);
	}

	virtual ~Point();
};

#endif /* POINT_H_ */
