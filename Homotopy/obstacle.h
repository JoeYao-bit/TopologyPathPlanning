#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "world_datatype.h"

class Obstacle {


public:
    Obstacle(std::vector<Point2D> points, int index = 0);

    Point2D sample_position();

    int _index;
    std::vector<Point2D> m_points;
    Polygon2D m_pgn;
    Point2D _centroid;
    Point2D m_bk;

    int _min_x;
    int _min_y;
    int _max_x;
    int _max_y;

};

#endif // OBSTACLE_H
