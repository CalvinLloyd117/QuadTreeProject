#include "QuadTree.h"

QuadTree::QuadTree()
{
    topLeft=Point(0, 0);
    bottomRight=Point(0, 0);
    node=nullptr;
    NW=nullptr;
    NE=nullptr;
    SW=nullptr;
    SE=nullptr;
}

QuadTree::QuadTree(Point topL, Point bottomR)
{
    topLeft=Point(0, 0);
    bottomRight=Point(0, 0);
    node=nullptr;
    NW=nullptr;
    NE=nullptr;
    SW=nullptr;
    SE=nullptr;
}

void QuadTree::insert(Node* inNode)
{

}

Node* QuadTree::search(Point* inPoint)
{

}

bool QuadTree::inSubtree()
{

}

QuadTree::~QuadTree()
{
    //dtor
}
