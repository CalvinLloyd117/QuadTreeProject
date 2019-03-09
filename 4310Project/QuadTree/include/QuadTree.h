#include <iostream>
#include <cmath>
#include<vector>
using namespace std;

///Data structure defines the points which are used to define
///the location of a node.
struct Point
{
    int x;
    int y;
    ///Point Constructor
    Point(int X, int Y)
    {
        x = X;
        y = Y;
    }
    ///Other constructor.
    Point()
    {
        x = 0;
        y = 0;
    }
};

///Node struct. Uses the point struct to define its location in the space.
///Also contains some data
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

/**************************************************************
* Quad Tree class definition. This class is used to store data
* Nodes, which are points in 2D space. The general structure is
* very similar to the binary tree, except that at each node,
* there are four children.
***************************************************************/
class QuadTree
{
    public:
        ///Default constructor
        QuadTree();

        ///Constructor takes in points Top Left, and bottom Right, which define
        ///the bounds of the tree.
        QuadTree(Point topL, Point botR);

        ///Function for inserting a new node into the tree. Takes in one node,
        ///and recursively traverses the tree, until the current space is less
        ///than or equal to one, at which point the algorithm inserts the node there.
        void insert(Node*);

        ///Function to search the tree. Takes in a point to search for. Traverses
        ///the tree until it reaches the requested node. Then, returns the node.
        Node* search(Point);

        ///Unfinished function to search for all points in a region.
        Node* regionSearch(Point, Point);

        ///Function used for experiments. Returns the number of nodes that are found when searching.
        int getFound();

        ///Function used for experiments. Returns the number of nodes that the algorithm visits during a search.
        int getVisited();

        ///Function used to reset the number of found, and visited.
        ///Should be used after each experiment iteration.
        void resetVisited();

    private:
        ///Helper function. Checks to see if a node could possibly exist in the subtree.
        ///used to make the decision of which subtree to traverse next.
        bool inSubtree(Point);

        ///points to define the bounds of the structure.
        Point topLeft;
        Point bottomRight;

        /// Contains details of node found at the deepest subtree of the structure.
        Node *dataNode;

        ///vector used for region search.
        vector<Node*> tempRegion;

        ///define the four subregions of the current structure.
        QuadTree *NW;
        QuadTree *NE;
        QuadTree *SW;
        QuadTree *SE;

        ///Values used for experiments. Static int so that all Quadtree's (sub trees) share the same value.
        static int numVisited;
        static int numFound;


};
