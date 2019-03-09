#ifndef QUADTREE_H
#define QUADTREE_H
struct Point
{
    int x;
    int y;

    Point(int X, int Y)
    {
        x=X;
        y=Y;
    }
    Point()
    {
        x=0;
        y=0;
    }
};

struct Node
{
    Point position;
    int data;
    Node(Point pos, int info)
    {
        position=pos;
        data=info;
    }
    Node()
    {
        data=0;
    }
};

class QuadTree
{
    public:
        QuadTree();
        QuadTree(Point topL, Point bottomR);
        virtual ~QuadTree();
        void populateRandomly();

        void insert(Node*);
        Node* search(Point);

    protected:

    private:
        QuadTree *NW;
        QuadTree *NE;
        QuadTree *SW;
        QuadTree *SE;

        Node* node;

        Point topLeft;
        Point bottomRight;

        bool inSubtree(Point);

};

#endif // QUADTREE_H
