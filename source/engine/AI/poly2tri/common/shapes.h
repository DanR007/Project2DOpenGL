/*
 * Poly2Tri Copyright (c) 2009-2010, Poly2Tri Contributors
 * http://code.google.com/p/poly2tri/
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of Poly2Tri nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Include guard

#pragma once

#include <vector>
#include <cstddef>
#include <assert.h>
#include <cmath>

#include <glm/vec2.hpp>

namespace p2t {

struct Edge;

struct Point {

  glm::dvec2 _pos;

  /// Default constructor does nothing (for performance).
  Point()
  {
    _pos.x = 0.0;
    _pos.y = 0.0;
  }

  /// The edges this point constitutes an upper ending point
  std::vector<Edge*> edge_list;

  /// Construct using coordinates.
  Point(const double x, const double y) : _pos(x, y) {}
  Point(const glm::dvec2& v) : _pos(v) {}

  /// Set this point to all zeros.
  void set_zero()
  {
      _pos = glm::dvec2(0);
  }

  /// Set this point to some specified coordinates.
  void set(double x, double y)
  {
    _pos.x = x;
    _pos.y = y;
  }

  bool operator==(const Point& v)
  {
      return _pos.x == v._pos.x && _pos.y == v._pos.y;
  }
  /// Negate this point.
  Point operator -() const
  {
    Point v;
    v._pos = -_pos;
    return v;
  }

  /// Add a point to this point.
  void operator +=(const Point& v)
  {
      _pos += v._pos;
  }

  /// Subtract a point from this point.
  void operator -=(const Point& v)
  {
      _pos -= v._pos;
  }
  Point operator -(const Point& v)
  {
      return Point(_pos - v._pos);
  }

  /// Multiply this point by a scalar.
  void operator *=(double a)
  {
      _pos *= a;
  }

  /// Get the length of this point (the norm).
  double Length() const
  {
    return std::sqrt(std::pow(_pos.x, 2) + std::pow(_pos.y, 2));
  }

  /// Convert this point into a unit point. Returns the Length.
  double Normalize()
  {
    double len = Length();
    _pos /= len;
    return len;
  }

};

// Represents a simple polygon's edge
struct Edge {

  Point* p, *q;

  /// Constructor
  Edge(Point& p1, Point& p2) : p(&p1), q(&p2)
  {
    if (p1._pos.y > p2._pos.y) {
      q = &p1;
      p = &p2;
    } else if (p1._pos.y == p2._pos.y) {
      if (p1._pos.x > p2._pos.x) {
        q = &p1;
        p = &p2;
      } else if (p1._pos.x == p2._pos.x) {
        // Repeat points
        assert(false);
      }
    }

    q->edge_list.push_back(this);
  }

  inline Point* GetPoint1() const { return p; }
  inline Point* GetPoint2() const { return q; }
};

// Triangle-based data structures are know to have better performance than quad-edge structures
// See: J. Shewchuk, "Triangle: Engineering a 2D Quality Mesh Generator and Delaunay Triangulator"
//      "Triangulations in CGAL"
class Triangle {
public:

/// Constructor
Triangle(Point& a, Point& b, Point& c);

/// Flags to determine if an edge is a Constrained edge
bool constrained_edge[3];
/// Flags to determine if an edge is a Delauney edge
bool delaunay_edge[3];

Point* GetPoint(const int& index);
Point* PointCW(Point& point);
Point* PointCCW(Point& point);
Point* OppositePoint(Triangle& t, Point& p);

Triangle* GetNeighbor(const int& index);
void MarkNeighbor(Point* p1, Point* p2, Triangle* t);
void MarkNeighbor(Triangle& t);

void MarkConstrainedEdge(const int index);
void MarkConstrainedEdge(Edge& edge);
void MarkConstrainedEdge(Point* p, Point* q);

int Index(const Point* p);
int EdgeIndex(const Point* p1, const Point* p2);

Triangle* NeighborCW(Point& point);
Triangle* NeighborCCW(Point& point);
bool GetConstrainedEdgeCCW(Point& p);
bool GetConstrainedEdgeCW(Point& p);
void SetConstrainedEdgeCCW(Point& p, bool ce);
void SetConstrainedEdgeCW(Point& p, bool ce);
bool GetDelunayEdgeCCW(Point& p);
bool GetDelunayEdgeCW(Point& p);
void SetDelunayEdgeCCW(Point& p, bool e);
void SetDelunayEdgeCW(Point& p, bool e);

bool Contains(Point* p);
bool Contains(const Edge& e);
bool Contains(Point* p, Point* q);
bool ContainPoint(Point* p)
{
    glm::dvec2 vec1, vec2, vec3;
    vec1 = p->_pos - points_[0]->_pos;
    vec2 = p->_pos - points_[1]->_pos;
    vec3 = p->_pos - points_[2]->_pos;
    //edges of triangle
    glm::dvec2 f_e, s_e, t_e;
    f_e = points_[1]->_pos - points_[0]->_pos;
    s_e = points_[2]->_pos - points_[0]->_pos;
    t_e = points_[2]->_pos - points_[1]->_pos;
    bool f_c = (vec1.x * f_e.y - f_e.x * vec1.y) * (vec1.x * s_e.y - s_e.x * vec1.y) <= 0;
    bool s_c = (vec2.x * t_e.y - t_e.x * vec2.y) * (vec2.x * (-s_e.y) - (-s_e.x) * vec2.y) <= 0;
    bool t_c = (vec3.x * (-s_e.y) - (-s_e.x) * vec3.y) * (vec3.x * (-t_e.y) - (-t_e.x) * vec3.y) <= 0;
    return f_c && s_c && t_c;
}
void Legalize(Point& point);
void Legalize(Point& opoint, Point& npoint);
/**
 * Clears all references to all other triangles and points
 */
void Clear();
void ClearNeighbor(Triangle *triangle );
void ClearNeighbors();
void ClearDelunayEdges();

inline bool IsInterior();
inline void IsInterior(bool b);

Triangle& NeighborAcross(Point& opoint);

void DebugPrint();

private:

/// Triangle points
Point* points_[3];
/// Neighbor list
Triangle* neighbors_[3];

/// Has this triangle been marked as an interior triangle?
bool interior_;
};

inline bool cmp(const Point* a, const Point* b)
{
  if (a->_pos.y < b->_pos.y) {
    return true;
  } else if (a->_pos.y == b->_pos.y) {
    // Make sure q is point with greater x value
    if (a->_pos.x < b->_pos.x) {
      return true;
    }
  }
  return false;
}

/// Add two points_ component-wise.
inline Point operator +(const Point& a, const Point& b)
{
  return Point(a._pos + b._pos);
}

/// Subtract two points_ component-wise.
inline Point operator -(const Point& a, const Point& b)
{
  return Point(a._pos - b._pos);
}

/// Multiply point by scalar
inline Point operator *(double s, const Point& a)
{
  return Point(a._pos.x * s, a._pos.y * s);
}

inline bool operator ==(const Point& a, const Point& b)
{
  return a._pos == b._pos;
}

inline bool operator !=(const Point& a, const Point& b)
{
  return a._pos != b._pos;
}

/// Peform the dot product on two vectors.
inline double Dot(const Point& a, const Point& b)
{
  return a._pos.x * b._pos.x + a._pos.y * b._pos.y;
}

/// Perform the cross product on two vectors. In 2D this produces a scalar.
inline double Cross(const Point& a, const Point& b)
{
  return a._pos.x * b._pos.y - a._pos.y * b._pos.x;
}

/// Perform the cross product on a point and a scalar. In 2D this produces
/// a point.
inline Point Cross(const Point& a, double s)
{
  return Point(s * a._pos.y, -s * a._pos.x);
}

/// Perform the cross product on a scalar and a point. In 2D this produces
/// a point.
inline Point Cross(const double s, const Point& a)
{
  return Point(-s * a._pos.y, s * a._pos.x);
}

inline Point* Triangle::GetPoint(const int& index)
{
  return points_[index];
}

inline Triangle* Triangle::GetNeighbor(const int& index)
{
  return neighbors_[index];
}

inline bool Triangle::Contains(Point* p)
{
  return p == points_[0] || p == points_[1] || p == points_[2];
}

inline bool Triangle::Contains(const Edge& e)
{
  return Contains(e.p) && Contains(e.q);
}

inline bool Triangle::Contains(Point* p, Point* q)
{
  return Contains(p) && Contains(q);
}

inline bool Triangle::IsInterior()
{
  return interior_;
}

inline void Triangle::IsInterior(bool b)
{
  interior_ = b;
}

}
