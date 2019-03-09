// Driver program
#include "QuadTree.h"
#include <cstdlib>
#include<iostream>
#include<vector>
#include<ctime>
#include<iomanip>
void runExperiment(QuadTree, int);
void runAverageExperiment(QuadTree, int, int);
using namespace std;

int main()
{
     srand(time(NULL));
    int menuOption;
    QuadTree center(Point(0, 0), Point(100, 100));

    //Node temp;
    while(menuOption!=7)
    {
        cout<<"Main menu:"<<endl;
        cout<<"1. Insert an element into the Quad Tree."<<endl
            <<"2. Search for an element."<<endl
            <<"3. Populate the tree."<<endl
            <<"4. Search the tree."<<endl
            <<"5. Run Experiment (populate/search)."<<endl
            <<"6. Run Average Experiment(populate/search)."<<endl
            <<"7. Exit."<<endl;
        do
        {
            cin>>menuOption;
        }while(!cin>>menuOption);

        int x, y, val;
        switch(menuOption)
        {
            case 1:
            {
                cout<<"Enter coordinates to insert, and integer data."<<endl;
                cin>>x>>y>>val;
                Node temp(Point(x,y),val);
                center.insert(&temp);
                cin.clear();
                break;
            }
            case 2:
            {
                cout<<"Enter coordinates to search for."<<endl;
                cin>>x>>y;
                //Point
                cout<<center.search(Point(x, y))->data<<endl;
                cout<<"Visited: "<<center.getVisited()<<" Found: "<<center.getFound()<<endl;
                center.resetVisited();
                cin.clear();
                break;
            }
            case 3:
            {
                vector<Node> nodes;
                for(int i=0; i<125; i++)
                {
                    int x=rand()%100;
                    int y=rand()%100;
                    int val=rand()%100;
                    Node node(Point(x, y), val);
                    nodes.push_back(node);

                    cout<<"X: "<<x<<" Y: "<<y<<" Val: "<<val<<endl;

                }
                for(int i=0; i<125; i++)
                {
                    center.insert(&nodes.at(i));
                    cout<<"Node x: "<<nodes.at(i).location.x<<"Node y: "<<nodes.at(i).location.y<<"Node val"<<nodes.at(i).data<<endl<<endl;
                }
                cin.clear();
                break;
            }
            case 4:
            {
                for(int i=0; i<100; i++)
                {
                    int x=rand()%100;
                    int y=rand()%100;
                    center.search(Point(x, y));
                }
                cout<<"Visited: "<<center.getVisited()<<" Found: "<<center.getFound()<<endl;
                center.resetVisited();
                cin.clear();
                break;
            }
            case 5:
            {
                cout<<"Conducting experiment..."<<endl;
                runExperiment(center, 125);
                runExperiment(center, 250);
                runExperiment(center,500);
                runExperiment(center,1000);
                runExperiment(center,2000);
                runExperiment(center,4000);
                break;
            }
            case 6:
            {
                cout<<"Average results of 100 Experiments..."<<endl;
                runAverageExperiment(center, 125, 100000);
                runAverageExperiment(center, 250, 100000);
                runAverageExperiment(center, 500, 100000);
                runAverageExperiment(center, 1000, 100000);
                runAverageExperiment(center, 2000, 100000);
                runAverageExperiment(center, 4000, 100000);
                break;
            }
        }
    }
    return 0;
}

void runExperiment(QuadTree testTree, int numNodes)
{
    vector<Node> nodes;
    for(int i=0; i<numNodes; i++)
    {
        int x=rand()%100;
        int y=rand()%100;
        int val=rand()%100;
        Node node(Point(x, y), val);
        nodes.push_back(node);

    // cout<<"X: "<<x<<" Y: "<<y<<" Val: "<<val<<endl;
    }
    for(int i=0; i<numNodes; i++)
    {
        testTree.insert(&nodes.at(i));
                    //cout<<"Node x: "<<nodes.at(i).location.x<<"Node y: "<<nodes.at(i).location.y<<"Node val"<<nodes.at(i).data<<endl<<endl;
    }

    for(int i=0; i<100; i++)
    {
        int x=rand()%100;
        int y=rand()%100;
        testTree.search(Point(x, y));
    }
    cout<<fixed<<setprecision(2)<<"Number of Nodes: "<<numNodes
        <<"\t Visited: "<<testTree.getVisited()
        <<"\t Found: "<<testTree.getFound()
        <<"\t Number of Searches: 100"
        <<"\t Visited/Search: "<<static_cast<double>((testTree.getVisited())/((double)(100)))
        <<"\t Found/Search: "<<static_cast<double>((testTree.getFound())/((double)(100)))
        <<"\t Visited/Found: "<<static_cast<double>((testTree.getVisited())/((double)(testTree.getFound())))
        <<endl;
    testTree.resetVisited();
}

void runAverageExperiment(QuadTree testTree, int numNodes, int numIt)
{
    double visited=0, found=0, visited_search=0, found_search=0, visited_found=0;
    vector<Node> nodes;
    for(int j=0; j<numIt; j++)
    {
       for(int i=0; i<numNodes; i++)
        {
            int x=rand()%100;
            int y=rand()%100;
            int val=rand()%100;
            Node node(Point(x, y), val);
            nodes.push_back(node);

        // cout<<"X: "<<x<<" Y: "<<y<<" Val: "<<val<<endl;
        }
        for(int i=0; i<numNodes; i++)
        {
            testTree.insert(&nodes.at(i));
                        //cout<<"Node x: "<<nodes.at(i).location.x<<"Node y: "<<nodes.at(i).location.y<<"Node val"<<nodes.at(i).data<<endl<<endl;
        }

        for(int i=0; i<100; i++)
        {
            int x=rand()%100;
            int y=rand()%100;
            testTree.search(Point(x, y));
        }
        visited+=testTree.getVisited();
        found+=testTree.getFound();

        visited_search+=static_cast<double>((testTree.getVisited())/((double)(100)));
        found_search+=static_cast<double>((testTree.getFound())/((double)(100)));
        visited_found+=static_cast<double>((testTree.getVisited())/((double)(testTree.getFound())));
        testTree.resetVisited();
   }
   visited=visited/numIt;
   found=found/numIt;

    cout<<fixed<<setprecision(2)<<"Number of Nodes: "<<numNodes
            <<"\t Visited: "<<visited
            <<"\t Found: "<<found
            <<"\t Number of Searches: 100"
            <<"\t Visited/Search: "<<visited/numIt//visited_search
            <<"\t Found/Search: "<<found/numIt//found_search
            <<"\t Visited/Found: "<<visited/found//visited_found
            <<endl;
}
