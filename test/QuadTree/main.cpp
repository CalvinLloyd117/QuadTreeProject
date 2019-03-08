// Driver program
#include "QuadTree.h"
#include <cstdlib>
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    Point p;
    p.x = 0;
    p.y = 0;
    vector<Point> points;
    points.push_back(p);


    for(int i = 0; i<6; i++)
    {
        int x = rand() % 100;
        int y = rand() % 100;

        cout<<"x:"<<x<<" y:"<<y<<endl;
    }


    QuadTree center(Point(0, 0), Point(8, 8));

    Node a(Point(1, 1), 1);
    Node b(Point(2, 5), 2);
    Node c(Point(7, 6), 3);

    center.insert(&a);
    center.insert(&b);
    center.insert(&c);

    cout << "Node a: " << center.search(Point(1, 1))->data << "\n";

    cout << "Node b: " << center.search(Point(2, 5))->data << "\n";

    cout << "Node c: " << center.search(Point(7, 6))->data << "\n";

    cout << "Non-existing node: " << center.search(Point(5, 5));


    return 0;
}
