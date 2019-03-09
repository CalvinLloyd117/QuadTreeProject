#include "QuadTree.h"

QuadTree::QuadTree()
{
    topLeft=Point(0, 0);
    bottomRight=Point(0, 0);
    dataNode=nullptr;
    NW =nullptr;
    NE=nullptr;
    SW=nullptr;
    SE=nullptr;
}

QuadTree::QuadTree(Point topL, Point botR)
{
    dataNode=nullptr;
    NW=nullptr;
    NE=nullptr;
    SW=nullptr;
    SE=nullptr;
    topLeft=topL;
    bottomRight=botR;
}

// Insert a node into the quadtree
void QuadTree::insert(Node *node)
{
    if(node==nullptr)
    {
        return;
    }

    /// Current quad cannot contain it
    if(!inSubtree(node->location))
    {
        return;
    }

    if(abs(topLeft.x-bottomRight.x)<=1 &&
        abs(topLeft.y-bottomRight.y) <= 1)
    {
        if (dataNode==nullptr)
        {
            dataNode=node;

        }
        return;
    }

    if((topLeft.x+bottomRight.x)/2>=node->location.x)
    {
        // Indicates NW
        if((topLeft.y+bottomRight.y)/2>=node->location.y)
        {
            if (NW==nullptr)
                NW=new QuadTree(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x+bottomRight.x)/2,
                        (topLeft.y+bottomRight.y)/2));
            NW->insert(node);
        }

        // Indicates SW
        else
        {
            if(SW==nullptr)
                SW=new QuadTree(
                                Point(topLeft.x,
                                        (topLeft.y + bottomRight.y)/2),
                                Point((topLeft.x + bottomRight.x)/2,
                                        bottomRight.y)
                                );
            SW->insert(node);
        }
    }
    else
    {
        // Indicates NE
        if((topLeft.y+bottomRight.y)/2>=node->location.y)
        {
            if(NE==nullptr)
            {
                NE=new QuadTree(
                                Point((topLeft.x+bottomRight.x)/2,
                                        topLeft.y),
                                Point(bottomRight.x,
                                        (topLeft.y+bottomRight.y)/2)
                                );
            }

            NE->insert(node);
        }

        // Indicates SE
        else
        {
            if (SE==nullptr)
            {
                SE=new QuadTree(
                                Point((topLeft.x + bottomRight.x) / 2,
                                        (topLeft.y + bottomRight.y) / 2),
                                Point(bottomRight.x, bottomRight.y)
                                );
            }

            SE->insert(node);
        }
    }
}
// Find a node in a quadtree
Node* QuadTree::search(Point p)
{
    // Current quad cannot contain it
    if(!inSubtree(p))
    {
        return nullptr;
    }


    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if(dataNode != nullptr)
    {
        return dataNode;
    }
    if((topLeft.x+bottomRight.x)/2>=p.x)
    {
        // Indicates NW
        if((topLeft.y+bottomRight.y)/2>=p.y)
        {
            if(NW == nullptr)
            {
                return nullptr;
            }
            return NW->search(p);
        }

        // Indicates SW
        else
        {
            if(SW == nullptr)
            {
                return nullptr;
            }

            return SW->search(p);
        }
    }
    else
    {
        // Indicates NE
        if((topLeft.y+bottomRight.y)/2>=p.y)
        {
            if (NE==nullptr)
                return nullptr;
            return NE->search(p);
        }
        // Indicates SE
        else
        {
            if(SE==nullptr)
            {
                return nullptr;
            }

            return SE->search(p);
        }
    }
};

// Check if current quadtree contains the point
bool QuadTree::inSubtree(Point p)
{
    return (p.x >= topLeft.x &&
            p.x <= bottomRight.x &&
            p.y >= topLeft.y &&
            p.y <= bottomRight.y
            );
}

