#include <iostream>
#include <cmath>
using namespace std;

// Used to hold details of a point
struct Point
{
    int x;
    int y;

    Point(int X, int Y)
    {
        x = X;
        y = X;
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
    Point location;
    int data;

    Node(Point in, int inData)
    {
        location = in;
        data = inData;
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
    Point bottomRight;

    // Contains details of node
    Node *dataNode;

    // Children of this tree
    QuadTree *NW;
    QuadTree *NE;
    QuadTree *SW;
    QuadTree *SE;

public:
    void randomlyPopulate(int numNodes, )
    QuadTree();
    QuadTree(Point topL, Point botR);
    void insert(Node*);
    Node* search(Point);
    bool inSubtree(Point);
};