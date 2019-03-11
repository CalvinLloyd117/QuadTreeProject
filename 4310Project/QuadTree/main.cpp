#include "QuadTree.h"
#include <cstdlib>
#include<iostream>
#include<vector>
#include<ctime>
#include<iomanip>

///function to run an experiment which takes in a quadtree
///and the number of nodes and determines the number of
///nodes visted, found, number of searches, and various
///ratios that tell us the throughput of the QuadTree
void runExperiment(QuadTree, int);

///function to run many experiments. It takes in a quadtree,
///the number of nodes, and the number of iterations to perform.
///It is similar in style to the run experiments function except
///that we perform a certain number of iterations on the quadtree
///and report the average of the results. The format is the same as
///the runExperiment function which displays the number of nodes
///visited, found, number of searches and various ratios all averaged
///out by the iteration amount
void runAverageExperiment(QuadTree, int, int);

using namespace std;

int main()
{
    ///for obtaining random values which we use in
    ///quadtree as points and data values
    srand(time(NULL));
    ///menu implemented for the user to perform various
    ///operations such as running experiments
    int menuOption;
    ///the main quadtree which is a massive grid of
    ///100 by 100, which is a total of 10000 area
    QuadTree experimentTree(Point(0, 0), Point(100, 100));
    QuadTree stdTree(Point(0, 0), Point(100, 100));

    ///the menu which has 7 options and they are below
    while(menuOption!=8)
    {
        ///menu display
        cout<<"Main menu:"<<endl;
        cout<<"1. Insert an element into the Quad Tree."<<endl
            <<"2. Search for an element."<<endl
            <<"3. Populate the tree."<<endl
            <<"4. Search the tree."<<endl
            <<"5. Run Experiment (populate/search)."<<endl
            <<"6. Run Average Experiment(populate/search)."<<endl
            <<"7. Delete a node."<<endl
            <<"8. Exit."<<endl;

        ///ensuring that the input is valid
        do
        {
            cin>>menuOption;
        }while(!cin>>menuOption);

        ///the x and y coordinates and the value associated
        ///at that coordinate
        int x, y, val;

        ///the options
        switch(menuOption)
        {
            ///first case which allows the user to insert a single data value
            ///with the value's coordinate
            case 1:
            {
                cout<<"Enter coordinates to insert, and integer data."<<endl;
                cin>>x>>y>>val;

                ///inserting into the tree by making a Node which stores
                ///the location - x and y and the data value
                Node temp(Point(x,y),val);
                stdTree.insert(&temp);
                stdTree.resetVisited();
                ///to ensure that the input buffer is valid and clearing
                cin.clear();
                break;
            }

            ///second case which allows the user to search for a single
            ///data value by using its coordinates to actually do the search
            case 2:
            {
                cout<<"Enter coordinates to search for."<<endl;
                cin>>x>>y;
                ///outputting the searched value at that coordinate and resetting the tree visited
                ///nodes because that node is considered visited in the tree
                Node *s = stdTree.search(Point(x, y));
                if(s != nullptr)
                {
                    //cout<<stdTree.search(Point(x, y))->data<<endl;
                    cout<<s->data<<endl;
                    cout<<"Visited: "<<stdTree.getVisited()<<" Found: "<<stdTree.getFound()<<endl;
                    stdTree.resetVisited();
                }
                else
                {
                    cout<<"Not in tree"<<endl;
                }

                ///to ensure that the input buffer is valid and clearing
                cin.clear();
                break;
            }

            ///third case which fills the quadtree with random values from 0 to 100.
            ///The coordinates are also randomized and determined to be from 0 to 100.
            ///this is also done for 125 nodes, so that is why we go from 0 to 125 range.
            case 3:
            {
                ///vector of nodes to insert into the quad tree that contain random coordinates
                ///and random values all from the range of 0 to 100.
                vector<Node> nodes;
                for(int i=0; i<125; i++)
                {
                    ///the random values and coordinates
                    int x=rand()%100;
                    int y=rand()%100;
                    int val=rand()%100;

                    ///creating the node with the values and cooridinates
                    Node node(Point(x, y), val);
                    ///inserting into the node vector
                    nodes.push_back(node);

                    ///outputting the values so that we know that they are truly random
                    cout<<"X: "<<x<<" Y: "<<y<<" Val: "<<val<<endl;

                }

                ///second for loop to insert into the tree
                for(int i=0; i<125; i++)
                {
                    ///inserting into the quadtree with the vector of nodes at the position i
                    stdTree.insert(&nodes.at(i));
                    ///outputting the vector of nodes so that we can see what we are inserting into the tree
                    ///and also to compare it to the random values we outputted in the for loop above.
                    cout<<"Node x: "<<nodes.at(i).location.x<<"Node y: "<<nodes.at(i).location.y<<"Node val"<<nodes.at(i).data<<endl<<endl;
                }
                stdTree.resetVisited();
                ///to ensure that the input buffer is valid and clearing
                cin.clear();
                break;
            }

            ///fourth case which allows the user to search for random points in the tree
            case 4:
            {
                ///for loop for 100 searches we perform on random coordinates in the tree
                for(int i=0; i<100; i++)
                {
                    ///the random coordinates
                    int x=rand()%100;
                    int y=rand()%100;
                    ///searching for the values
                    stdTree.search(Point(x, y));
                }

                ///outputting the searched values. The format is visited and found.
                cout<<"Visited: "<<stdTree.getVisited()<<" Found: "<<stdTree.getFound()<<endl;

                ///resetting the tree's visited nodes
                stdTree.resetVisited();

                ///to ensure that the input buffer is valid and clearing
                cin.clear();
                break;
            }

            ///fifth case to conduct a single experiments. The number of iterations is thus 1.
            ///The experiments are conducted by calling the runExperiments helper function
            ///we do this for 125, 250, 500, 1000, 2000 and 4000 nodes just like Finkel and Bentley
            ///did in their paper.
            case 5:
            {
                cout<<"Conducting experiment..."<<endl;
                runExperiment(experimentTree,125);
                experimentTree.resetVisited();
                runExperiment(experimentTree,250);
                experimentTree.resetVisited();
                runExperiment(experimentTree,500);
                experimentTree.resetVisited();
                runExperiment(experimentTree,1000);
                experimentTree.resetVisited();
                runExperiment(experimentTree,2000);
                experimentTree.resetVisited();
                runExperiment(experimentTree,4000);
                experimentTree.resetVisited();
                break;
            }

            ///sixth case to also conduct experiments except that it is more than 1 iteration. It uses
            ///the helper function runAverageExperiment. This will give back the average results for a certain number of iterations
            ///The number of iterations is specified by the user. We  also do this for 125, 250, 500, 1000,
            ///2000 and 4000 nodes just like Finkel and Bentley did in their paper.
            case 6:
            {
                cout<<"Average results of 1000 Experiments..."<<endl;
                runAverageExperiment(experimentTree, 125, 1000);
                experimentTree.resetVisited();
                runAverageExperiment(experimentTree, 250, 1000);
                experimentTree.resetVisited();
                runAverageExperiment(experimentTree, 500, 1000);
                experimentTree.resetVisited();
                runAverageExperiment(experimentTree, 1000, 1000);
                experimentTree.resetVisited();
                runAverageExperiment(experimentTree, 2000, 1000);
                experimentTree.resetVisited();
                runAverageExperiment(experimentTree, 4000, 1000);
                experimentTree.resetVisited();
                break;
            }
            case 7:
            {
                cout<<"Enter coordinates to delete for."<<endl;
                cin>>x>>y;

                ///outputting the searched value at that coordinate and resetting the tree visited
                ///nodes because that node is considered visited in the tree
                //cout<<stdTree.deleteNode(Point(x, y))<<endl;//->data<<endl;
                if(stdTree.deleteNode(Point(x,y)) == nullptr)
                {

                    cout<<"Deleted node"<<endl;
                }
                //cout<<"Visited: "<<stdTree.getVisited()<<" Found: "<<stdTree.getFound()<<endl;
                //stdTree.resetVisited();

                ///to ensure that the input buffer is valid and clearing
                cin.clear();
                break;
            }
            case 8:
            {
                cout<<"Exiting"<<endl;
                return 0;
            }
        }
    }

    ///done
    return 0;
}


///function to run an experiment which takes in a quadtree
///and the number of nodes and determines the number of
///nodes visited, found, number of searches, and various
///ratios that tell us the throughput of the QuadTree.
///It will create a vector of nodes just like in case 3 and fill it up
///with random values. We then perform random searches and report the results.
///The format of the results is the same as Finkel and Bentley and
///is presented in the big a** cout statement.
void runExperiment(QuadTree testTree, int numNodes)
{
    ///creating the vector of nodes with however many nodes
    ///there are.
    vector<Node> nodes;
    for(int i=0; i<numNodes; i++)
    {
        ///random values
        int x=rand()%100;
        int y=rand()%100;
        int val=rand()%100;
        ///inserting into the node vector
        Node node(Point(x, y), val);
        nodes.push_back(node);
    }

    ///inserting into the tree by using the vector of nodes
    for(int i=0; i<numNodes; i++)
    {
        testTree.insert(&nodes.at(i));
    }

    ///performining 100 random searches on the tree just
    ///Finkel and Bentley
    for(int i=0; i<100; i++)
    {
        int x=rand()%100;
        int y=rand()%100;
        testTree.search(Point(x, y));
    }

    ///the big a** cout statement which prints out the results in the same format
    ///as Finkel and Bentley. We also print out to 2 decimal places.
    cout<<fixed<<setprecision(2)<<"Number of Nodes: "<<numNodes
        <<"\t Visited: "<<testTree.getVisited()
        <<"\t Found: "<<testTree.getFound()
        <<"\t Number of Searches: 100"
        <<"\t Visited/Search: "<<static_cast<double>((testTree.getVisited())/((double)(100)))
        <<"\t Found/Search: "<<static_cast<double>((testTree.getFound())/((double)(100)))
        <<"\t Visited/Found: "<<static_cast<double>((testTree.getVisited())/((double)(testTree.getFound())))
        <<endl;

    ///resetting the visited nodes so we dont double count.
    testTree.resetVisited();
}

///function to run many experiments. It takes in a quadtree,
///the number of nodes, and the number of iterations to perform.
///It is similar in style to the run experiments function except
///that we perform a certain number of iterations on the quadtree
///and report the average of the results. The format is the same as
///the runExperiment function which displays the number of nodes
///visited, found, number of searches and various ratios all averaged
///out by the iteration amount.
///The function takes in the quadtree and does the same thing as the above fucntion
///except that we run however many iterations as specified by the user. The only
///difference between the above function and this one is that we run multiple iterations
///instead of only 1.
void runAverageExperiment(QuadTree testTree, int numNodes, int numIt)
{
    ///we report the averages which are stored in these variables.
    double visited=0, found=0, visited_search=0, found_search=0, visited_found=0;

    ///same thign as above where we create the node vector and insert into the tree
    vector<Node> nodes;
    for(int j=0; j<numIt; j++)
    {
        ///creating the vector
        for(int i=0; i<numNodes; i++)
        {
            int x=rand()%100;
            int y=rand()%100;
            int val=rand()%100;
            Node node(Point(x, y), val);
            nodes.push_back(node);
        }

        ///inserting into the tree
        for(int i=0; i<numNodes; i++)
        {
            testTree.insert(&nodes.at(i));
        }

        ///searching the tree
        for(int i=0; i<100; i++)
        {
            int x=rand()%100;
            int y=rand()%100;
            testTree.search(Point(x, y));
        }

        ///storing the resluts each time so we can take the average at the end(the big a** cout statement below).
        visited+=testTree.getVisited();
        found+=testTree.getFound();
        visited_search+=static_cast<double>((testTree.getVisited())/((double)(100)));
        found_search+=static_cast<double>((testTree.getFound())/((double)(100)));
        visited_found+=static_cast<double>((testTree.getVisited())/((double)(testTree.getFound())));
        testTree.resetVisited();
    }

    ///averaging the results
    visited=visited/numIt;
    found=found/numIt;

    ///the big a** cout statement which prints out the average results in the same format
    ///as Finkel and Bentley. We also print out to 2 decimal places.
    cout<<fixed<<setprecision(2)<<"Number of Nodes: "<<numNodes
            <<"\t Visited: "<<visited
            <<"\t Found: "<<found
            <<"\t Number of Searches: 100"
            <<"\t Visited/Search: "<<visited/numIt//visited_search
            <<"\t Found/Search: "<<found/numIt//found_search
            <<"\t Visited/Found: "<<visited/found//visited_found
            <<endl;
}
