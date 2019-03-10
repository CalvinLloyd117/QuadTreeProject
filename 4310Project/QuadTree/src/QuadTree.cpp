#include "QuadTree.h"

///Quadtree default ctor which sets
///the topLeft and bottom right coordinates to (0,0) and
///sets the dataNode, and the various quadrants to null
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


///Quadtree ctor which takes 2 points which
///are the topL and botR representing coordinates for the
///top left and bottom right respectively. We set the
///internal topLeft and bottomRight coordinate to the given
///coordinates. The rest is the same as the default ctor.
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

///global variables used for the number of nodes found and visited
int QuadTree::numFound;
int QuadTree::numVisited;

///insert function which takes in a new node and inserts into the main
///quadtree. It takes in one node and recursively traverses the tree, until
///the current space is less than or equal to 1 which means that we cannot subdivide
///the tree any further and insert there.
void QuadTree::insert(Node *node)
{
    ///if the node is null then it is not valid
    ///and we do not insert it
    if(node==nullptr)
    {
        cout<<"Not a valid node."<<endl;
        return;
    }

    ///current quadtree cannot contain the node
    ///because it is out of bounds
    if(!inSubtree(node->location))
    {
        cout<<"Tree cannot contain this node."<<endl;
        return;
    }

    ///if the absolute value of the topLeft and bottomRight is less than or equal to
    ///1 then we check if the internal dataNode is null or not and set it to the new node,
    ///else we return and move onto the next check
    if(abs(topLeft.x-bottomRight.x)<=1 && abs(topLeft.y-bottomRight.y) <= 1)
    {
        if (dataNode==nullptr)
        {
            dataNode = node;
        }
        return;
    }

    ///if the topLeft x + bottomRight x/2 >= nodes x location,
    ///then we check the y coordinates as well and then insert into that quadrant
    ///using recursion. The quadrants are NW and SW, and we insert into either of those
    ///depending on the coordinates.
    if((topLeft.x+bottomRight.x)/2>=node->location.x)
    {
        ///this indicates the NW quadrant
        if((topLeft.y+bottomRight.y)/2>=node->location.y)
        {
            ///if the NW quadrant is empty, then we insert into there using recursion.
            if (NW==nullptr)
                NW=new QuadTree(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x+bottomRight.x)/2,
                        (topLeft.y+bottomRight.y)/2));
            NW->insert(node);
        }

        ///this indicates the SW quadrant
        else
        {
            ///if the SW quadrant is empty, then we insert into there using recursion.
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

    ///else we are in the right side of the tree, which are NE and SE quadrants and
    ///we insert there recursively similar to the above quadrants.
    else
    {
        ///similar checks to above
        if((topLeft.y+bottomRight.y)/2>=node->location.y)
        {
            ///inserting into NE quadrant
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

        ///indicates SE quadrant
        else
        {
            ///inserting into the SE quadrant
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

///Function to search the tree, which takes in a point(x,y) which is used for the
///searching. It then traverses the tree until it reaches the requested data value
///associated at that point. It will then return the node.
Node* QuadTree::search(Point p)
{
    ///current quadtree cannot contain the node
    if(!inSubtree(p))
    {
        return nullptr;
    }

    ///base case where we return the dataNode if it is found
    ///and increase numFound because the node is found
    if(dataNode != nullptr)
    {
        numFound++;
        return dataNode;
    }

    ///similar to insert in that we use the coordinates to
    ///determine which quadrant we are in and then use
    ///recursion to search through the tree.
    if((topLeft.x+bottomRight.x)/2>=p.x)
    {
        ///indicates NW quadrant to search
        if((topLeft.y+bottomRight.y)/2>=p.y)
        {
            ///quadrant does not have the point we are searching for
            if(NW == nullptr)
            {
                return nullptr;
            }

            ///increment numVisited because we have visited that
            ///node but have not found it
            numVisited++;

            ///use recursion to continue on the search
            ///and determine if it is in that specific quadrant
            return NW->search(p);
        }

        ///indicates SW
        else
        {
            ///quadrant does not have the point we are searching for
            if(SW == nullptr)
            {
                return nullptr;
            }

            ///increment numVisited because we have visited that
            ///node but have not found it
            numVisited++;

            ///use recursion to continue on the search
            ///and determine if it is in that specific quadrant
            return SW->search(p);
        }
    }
    else
    {
        ///indicates NE
        if((topLeft.y+bottomRight.y)/2>=p.y)
        {
            ///quadrant does not have the point we are searching for
            if (NE==nullptr)
            {
                return nullptr;
            }

            ///increment numVisited because we have visited that
            ///node but have not found it
            numVisited++;

            ///use recursion to continue on the search
            ///and determine if it is in that specific quadrant
            return NE->search(p);
        }
        ///indicates SE
        else
        {
            ///quadrant does not have the point we are searching for
            if(SE==nullptr)
            {
                return nullptr;
            }

            ///increment numVisited because we have visited that
            ///node but have not found it
            numVisited++;

            ///use recursion to continue on the search
            ///and determine if it is in that specific quadrant
            return SE->search(p);
        }
    }
};

///helper function which checks to see if a node could
///possibly exist in a subtree. It is also used to make the
///decision of which subtree to traverse next.
bool QuadTree::inSubtree(Point p)
{
    ///checks if the point P's coordinates are in the tree
    return (p.x >= topLeft.x &&
            p.x <= bottomRight.x &&
            p.y >= topLeft.y &&
            p.y <= bottomRight.y
            );
}

///Function used for experiments.
///Returns the number of nodes that are found when searching.
int QuadTree::getFound()
{
    return numFound;
}

///Function used for experiments.
///Returns the number of nodes that the algorithm visits during a search.
int QuadTree::getVisited()
{
    return numVisited;
}

///Function used to reset the number of found, and visited.
///Should be used after each experiment iteration.
void QuadTree::resetVisited()
{
    numVisited=0;
    numFound=0;
}

