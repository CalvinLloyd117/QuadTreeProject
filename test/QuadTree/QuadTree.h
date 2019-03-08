#include <iostream>
#include <cmath>
using namespace std;

// Used to hold details of a point
struct Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};

// The main quadtree class
class QuadTree
{
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;

    // Contains details of node
    Node *n;

    // Children of this tree
    QuadTree *topLeftTree;
    QuadTree *topRightTree;
    QuadTree *botLeftTree;
    QuadTree *botRightTree;

public:
    QuadTree();
    QuadTree(Point topL, Point botR);
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
};
