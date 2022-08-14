//
//  triangle_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "geometry.h"

#include <vector>
using std::vector;

namespace splashkit_lib
{
    triangle triangle_from(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        triangle result;
        result.points[0] = point_at(x1, y1);
        result.points[1] = point_at(x2, y2);
        result.points[2] = point_at(x3, y3);
        return result;
    }

    triangle triangle_from(const point_2d &p1, const point_2d &p2, const point_2d &p3)
    {
        triangle result;
        result.points[0] = p1;
        result.points[1] = p2;
        result.points[2] = p3;
        return result;
    }

    bool triangle_rectangle_intersect(const triangle &tri, const rectangle &rect)
    {
        double r, l, t, b;

        auto tri_line_rectangle_test = [&](const point_2d &pt1, const point_2d pt2)
        {
            double m, c;
            double top_intersection, bottom_intersection;
            double top_triangle_point, bottom_triangle_point;
            double top_overlap, bottom_overlap;

            if (pt2.x - pt1.x == 0)
                m = 0;
            else
                m = (pt2.y - pt1.y) / (pt2.x - pt1.x);

            c = pt1.y - (m * pt1.x);

            // if the line is going up from right to left then the top intersect point is on the left
            if ( m > 0 )
            {
                top_intersection    = m * l + c;
                bottom_intersection = m * r + c;
            }
            // otherwise it's on the right
            else
            {
                top_intersection    = m * l + c;
                bottom_intersection = m * l + c;
            }

            // work out the top and bottom extents for the triangle
            if ( pt1.y < pt2.y )
            {
                top_triangle_point    = pt1.y;
                bottom_triangle_point = pt2.y;
            }
            else
            {
                top_triangle_point    = pt2.y;
                bottom_triangle_point = pt1.y;
            }

            // and calculate the overlap between those two bounds
            top_overlap = top_intersection > top_triangle_point ? top_intersection : top_triangle_point;
            bottom_overlap = bottom_intersection < bottom_triangle_point ? bottom_intersection : bottom_triangle_point;

            // If the bottom overlap is higher than the top of the rectangle or the top overlap is
            // lower than the bottom of the rectangle we don't have intersection. So return the negative
            // of that. Much faster than checking each of the points is within the bounds of the rectangle.
            return (top_overlap<bottom_overlap) and (not((bottom_overlap<t) or (top_overlap>b)));
        };

        // Perform bounding box check
        if ( not rectangles_intersect(rect, rectangle_around(tri) ) ) return false;

        r = rectangle_right(rect);
        l = rectangle_left(rect);
        t = rectangle_top(rect);
        b = rectangle_bottom(rect);

        // Check line intersects see http://sebleedelisle.com/2009/05/super-fast-trianglerectangle-intersection-test/
        return tri_line_rectangle_test(tri.points[0],tri.points[1])
            or tri_line_rectangle_test(tri.points[1],tri.points[2])
            or tri_line_rectangle_test(tri.points[2],tri.points[0])
            or point_in_triangle(point_at(l, t), tri)
            or point_in_triangle(point_at(l, b), tri)
            or point_in_triangle(point_at(r, t), tri)
            or point_in_triangle(point_at(r, b), tri);
    }

    bool triangles_intersect(const triangle &t1, const triangle &t2)
    {
        // Test if any of the points lie within the other triangle.
        for (int i = 0; i < 3; i++)
        {
            if ( point_in_triangle(t1.points[i], t2) || point_in_triangle(t2.points[i], t1) ) return true;
        }

        vector<line> t1_lines = lines_from(t1);
        vector<line> t2_lines = lines_from(t2);

        // Check if any lines intersect (check first two of both, as if they do not intersect then
        // it cant intersect the third either)
        for (int i = 0; i < 2; i++)
        {
            if ( lines_intersect( t1_lines[i], t2_lines[0] ) || lines_intersect( t1_lines[i], t2_lines[1] ) )
            {
                return true;
            }
        }

        return false;
    }

    point_2d triangle_barycenter(const triangle  &tri)
    {
        return point_at(
                (tri.points[0].x + tri.points[1].x + tri.points[2].x) / 3,
                (tri.points[0].y + tri.points[1].y + tri.points[2].y) / 3);
    }

    string triangle_to_string(const triangle  &tri)
    {
        return "Triangle @" + point_to_string(tri.points[0]) + " - " + point_to_string(tri.points[1]) + " - " + point_to_string(tri.points[2]);
    }
}
