#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>
using namespace std;


// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(string name, MetroLine* metroLine, int fare);

    // Getter methods
    string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    string lineName;
    MetroStop* node;

public:
    MetroLine(string name);

    // Getter methods
    string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(string filename);

    // helper function
    MetroStop* search(MetroLine * metroline,string name);
    MetroStop* search_backward(MetroLine * metroline,MetroStop * start,string name);
    MetroStop* search_forward(MetroLine * metroline,MetroStop * start,string name);
    void printLine() const;
    int getTotalStops() const;
};

MetroStop* MetroLine:: search(MetroLine * metroline,string name){
    MetroStop * head=metroline->getNode();
    while(head!=NULL){
        string stopname=head->getStopName();
        if(stopname==name){
            return head;
        }
        head=head->getNextStop();
    }
    return NULL;
}


MetroStop* MetroLine:: search_backward(MetroLine * metroline,MetroStop * start ,string name){
    MetroStop * head=start;
    while(head!=NULL){
        string stopname=head->getStopName();
        if(stopname==name){
            return head;
        }
        head=head->getPrevStop();
    }
    return NULL;
}

MetroStop* MetroLine:: search_forward(MetroLine * metroline,MetroStop * start ,string name){
    MetroStop * head=start;
    while(head!=NULL){
        string stopname=head->getStopName();
        if(stopname==name){
            return head;
        }
        head=head->getNextStop();
    }
    return NULL;
}

MetroLine::MetroLine(string name) {
    lineName = name;
    node = nullptr;
}

string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    MetroStop* head = node;
    int c=0;
    while(head!=NULL){
        c++;
        head=head->getNextStop();
    }
    return c;
}

void MetroLine::populateLine(string filename) {
    // Read the file and populate the line
    /*for(int i=0;i<filename.size();i++){
        if(filename[i]=='.'){
            filename[i]='\0';
        }
    }
    cout<<filename<<endl;*/
    //MetroLine * station=new MetroLine(filename);          use this for these operations
    MetroStop * head=NULL;
    MetroStop * tail=NULL;
    
    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }
    int i = 0;
    string line;
    while (true)
    {   getline(input_file, line);
        
        size_t lastSpacePos = line.find_last_of(" ");
        if (lastSpacePos != string::npos && lastSpacePos < line.length() - 1) {
            string stationName = line.substr(0, lastSpacePos);
            int fare = stoi(line.substr(lastSpacePos + 1));
        
            //cout<<"station name "<<stationName<<"fare "<<fare <<endl;
            MetroStop* newnode = new MetroStop(stationName, this, fare);
            //MetroStop * newnode=new MetroStop(stationName,station,fare);
            //Adding a node to doubly linked list
            if(head==NULL){
                head=newnode;
                this->setNode(head);
                tail=newnode;
            }else{
                newnode->setPrevStop(tail);
                tail->setNextStop(newnode);
                tail=newnode;
            }
        }
        if (input_file.peek() == EOF)
                {                    // cout<<"EOF"<<endl;
                    break;
                }
    }
   // cout<<"printing whole line"<<endl;
    //this->printLine();
    //cout<<this->getTotalStops()<<endl;
    input_file.close();
}

// AVLNode class
class AVLNode {
private:
    string stopName;
    vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;

public:
    AVLNode(string name);

    // Getter methods
    string getStopName() const;
    const vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
    int getHeight();
    void updateHeight();
};

AVLNode::AVLNode(string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    height=1;
}

string AVLNode::getStopName() const {
    return stopName;
}

const vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

int AVLNode::getHeight(){
        //cout<<"from getheight"<<endl;
        return this->height;
}

void AVLNode::updateHeight(){
        int left_height=(left!=NULL)?left->getHeight():0;
        int right_height=(right!=NULL)?right->getHeight():0;
        this->height=1+max(left_height,right_height);
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}


void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);      // return type changed!
    AVLNode* rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    AVLNode* insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
    AVLNode* search(AVLNode * node,string stopName);

};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node==NULL){
        return 0;
    }
    int left_subtree=height(node->getLeft());
    int right_subtree=height(node->getRight());
    return 1+max(left_subtree,right_subtree);
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp
    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if(node==NULL){
        return 0;
    }
    int left_subtree=height(node->getLeft());
    int right_subtree=height(node->getRight());
    return left_subtree-right_subtree;
}

AVLNode* AVLTree::rotateLeft(AVLNode* X) {
    if(X==NULL || X->getRight()==NULL){
        return X;
    }
    AVLNode *Y=X->getRight();
    AVLNode * T2=Y->getLeft();
    Y->setLeft(X);
    X->setRight(T2);
    Y->updateHeight();
    X->updateHeight();
    return Y;
}

AVLNode* AVLTree::rotateRight(AVLNode* Y) {
    if(Y==NULL || Y->getLeft()==NULL){
        return Y;
    }
    AVLNode *X= Y->getLeft();
    AVLNode * T2=X->getRight();
   X->setRight(Y);
    Y->setLeft(T2); 
    X->updateHeight();
    Y->updateHeight();
    return X;
}

void AVLTree::balance(AVLNode* node) {
    if(node==NULL){
        return;
    }
    int balance_factor=balanceFactor(node);
    //Left-Left 
    if(balance_factor>1 && balanceFactor(node->getLeft())>=0){
        rotateRight(node);
        node->updateHeight(); 
    }
    //Right-Right 
    if(balance_factor<-1 && balanceFactor(node->getLeft())<=0){
        rotateLeft(node);
        node->updateHeight(); 
    }
    //Left-Right 
    if(balance_factor>1 && balanceFactor(node->getLeft())<0){
        rotateLeft(node->getLeft());
        rotateRight(node);
        node->updateHeight(); 
    }
    //Right-Left 
    if(balance_factor<-1 && balanceFactor(node->getRight())>0){
        rotateRight(node->getRight());
        rotateLeft(node);
        node->updateHeight(); 
    }

    balance(node->getParent());
}

AVLNode* AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    if(node==NULL){
        AVLNode * newnode=new AVLNode(metroStop->getStopName());
        node=newnode;
        return newnode;
    }
 
    if(node->getStopName() >metroStop->getStopName()){
        node->setLeft(insert(node->getLeft(),metroStop));
    }else{
        node->setRight(insert(node->getRight(),metroStop));
    }
    //cout<<"done"<<endl;
    node->updateHeight();
    int balance_factor=balanceFactor(node);
    //cout<<"node's key "<<node->getStopName()<<endl;
    //cout<<"balance_factor ["<<balance_factor<<"]"<<endl;

    //Left-Left Insertion
    if(balance_factor>1 && node->getLeft()->getStopName()>metroStop->getStopName()){
        return rotateRight(node);
    }
    //Right-Right Insertion
    if(balance_factor<-1 && node->getRight()->getStopName()<metroStop->getStopName()){
        return rotateLeft(node);
    }
    //Left-Right Insertion
    if(balance_factor>1 && node->getLeft()->getStopName()<metroStop->getStopName()){
       node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }
    //Right-Left Insertion
    if(balance_factor<-1 && node->getRight()->getStopName()>metroStop->getStopName()){
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }
    
    return node;                // new root of tree
}

void AVLTree::populateTree(MetroLine* metroLine){
    MetroStop * station_node=metroLine->getNode();
    
    while(station_node!=NULL){
        //cout<<station_node->getStopName()<<endl;
        if(this->getRoot()==NULL){
            AVLNode * newnode=new AVLNode(station_node->getStopName());
            this->setRoot(newnode);
            cout<<this->getRoot()<<endl;
            this->setRoot(insert(this->getRoot(),station_node));

            AVLNode * new_node=searchStop(station_node->getStopName());
            new_node->addMetroStop(station_node);
            //cout<<"Added in if"<<endl;
            //station_node=station_node->getNextStop();
        }
        else{
            if(this->search(this->getRoot(),station_node->getStopName())==NULL){
                    //cout<<"insert location"<<insert(this->getRoot(),station_node)<<endl;
                    this->setRoot(insert(this->getRoot(),station_node));
                    AVLNode * new_node=searchStop(station_node->getStopName());
                    new_node->addMetroStop(station_node);
                    //cout<<"Added in else if"<<endl;
                }
            else{
                    AVLNode * existing_node=searchStop(station_node->getStopName());
                    existing_node->addMetroStop(station_node);
                }
            }
        station_node=station_node->getNextStop();
    }
    cout<<"NUMBER OF NOdES IN THE TREE AS OF NOW : "<<this->getTotalNodes(this->getRoot())<<endl;
}


void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode * AVLTree::search(AVLNode * node,string stopName){
    if(node==NULL){
        return node;
    }
    if(node->getStopName()==stopName){
        return node;
    }
    else if(node->getStopName()>stopName){
        return search(node->getLeft(),stopName);
    }else{
        return search(node->getRight(),stopName);
    }
}

AVLNode* AVLTree::searchStop(string stopName) {
    return search(root,stopName);
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    string direction;
    MetroLine * line_name;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip,string dir, MetroLine * line);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
    string getDirection();
    MetroLine * getLine();
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip,string dir, MetroLine * line) {
    node = metroStop;
    prev = previousTrip;
    direction=dir;
    line_name=line;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

string Trip::getDirection(){
    return direction;
}

MetroLine * Trip:: getLine(){
    return line_name;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    vector<MetroStop*> getStops() const;
    int getTotalFare() const;
    void modify_stops(vector<MetroStop*> demo);
    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

vector<MetroStop*> Path::getStops() const {
    return stops;
}

void Path::modify_stops(vector<MetroStop*> demo){
    stops=demo;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(string origin, string destination);

    // Getter methods
    AVLTree* getTree() const;
    const vector<MetroLine*>& getLines() const;
    int ComputeFare(Path * path);
};

PathFinder::PathFinder(AVLTree* avlTree, const vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}



void PathFinder::createAVLTree(){
//void AVLTree::populateTree(MetroLine* metroLine){
     tree=new AVLTree();                            //Task 1: Create an AVL tree of all the stations.
    for(int i=0;i<lines.size();i++){ 
        MetroLine* metroLine=lines[i];
        cout<<"------------------------------- Metro line name:                 "<<metroLine->getLineName()<<"-------------------------------"<<endl;
        MetroStop * station_node=metroLine->getNode();
        
        while(station_node!=NULL){
            cout<<station_node->getStopName()<<endl;

            if(tree->getRoot()==NULL){
                AVLNode * newnode=new AVLNode(station_node->getStopName());
                //newnode->addMetroStop(station_node);              // now added
                tree->setRoot(newnode);
                //cout<<tree->getRoot()<<endl;
                tree->setRoot(tree->insert(tree->getRoot(),station_node));
                AVLNode * new_node=tree->searchStop(station_node->getStopName());
                new_node->addMetroStop(station_node);

                //tree->insert(tree->getRoot(),station_node)->addMetroStop(station_node);
                //cout<<"Added in if"<<endl;
            }
            else{
                if(tree->search(tree->getRoot(),station_node->getStopName())==NULL){

                        //AVLNode * node_add=tree->insert(tree->getRoot(),station_node);
                        tree->setRoot(tree->insert(tree->getRoot(),station_node));
                        //node_add->addMetroStop(station_node);
                        AVLNode * new_node=tree->searchStop(station_node->getStopName());
                        new_node->addMetroStop(station_node);
                        //cout<<"Added in else if"<<endl;
                    }
                else{
                        AVLNode * existing_node=tree->searchStop(station_node->getStopName());
                        cout<<endl;
                        cout<<"inside else else of create AVL tree function"<<endl;
                        cout<<existing_node->getStopName()<<endl;
                        cout<<"existing nodes from which line ? "<<endl;
                        existing_node->addMetroStop(station_node);
                        vector<MetroStop*> stops= existing_node->getStops();
                        cout<<" stops vector size  "<<stops.size()<<endl;
                        for(int i=0;i<stops.size()-1;i++){
                            //cout<<"hi"<<endl;
                            cout<<stops[i]->getNextStop()->getStopName()<<endl;
                            //cout<<stops[i]->getNextStop()->getLine()<<endl;
                            //cout<<stops[i]->getNextStop()->getLine()->getLineName();
                            //cout<<"hi"<<endl;
                        }
                        //cout<<"existing nodes from which line ? "<<existing_node->getStops()[0]->getLine()->getLineName()<<endl;
                        
                    }
                }
                cout<<endl;
            station_node=station_node->getNextStop();
        }
    }
    cout<<"NUMBER OF NOdES IN THE TREE AS OF NOW : "<<tree->getTotalNodes(tree->getRoot())<<endl;
}

int PathFinder::ComputeFare(Path * path){
    if(path!=NULL){
        return 0 ;
    }
    vector<MetroStop*> path_vector=path->getStops();
    cout<<"printing path"<<endl;
    path->printPath();
    int fare=0;
    int high=path_vector[path_vector.size()-1]->getFare();
    int low=path_vector[0]->getFare();
    cout<<high<<" high fare"<<endl;
    cout<<low<<" low fare"<<endl;
    fare=path_vector[path_vector.size()-1]->getFare()-path_vector[0]->getFare();
    fare=abs(fare);
    path->setTotalFare(fare);
    cout<<fare;
    return fare;
}

Path* PathFinder::findPath(string origin, string destination) {
    Exploration * explore=new Exploration();
    Path * fetched_path=new Path();
    //string temp=origin;
   //origin=destination;
    //destination=temp;

    for(int i=0;i<lines.size();i++){

            MetroLine* metroLine=lines[i];
            cout<<metroLine->getLineName()<<endl;
            MetroStop * station_node=metroLine->search(metroLine,origin);
            MetroStop * station_node_copy=station_node;
            

            if(station_node==NULL){
                cout<<"Node doesn't exist in "<<metroLine->getLineName()<<" line"<<endl;
                continue;
            }

            cout<<station_node->getStopName()<<endl;
            MetroStop * first=station_node;
            //Trip * T1=new Trip(station_node->getPrevStop(),NULL,"Backward");
            Trip * T1=new Trip(station_node,NULL,"Backward",metroLine);
             Trip * T2=new Trip(station_node,NULL,"Forward",metroLine);
           // Trip * T2=new Trip(station_node->getNextStop(),NULL,"Forward");
            explore->enqueue(T1);

            //explore->enqueue(T2);

                                while(station_node!=NULL){                  // We are actually manually performing operations for trip T2
                                    cout<<station_node->getStopName()<<endl; 
                                    if(station_node->getStopName()==destination){           // we found our destination node on the T2 metroline itself
                                        while(station_node->getStopName()!=origin){
                                            fetched_path->addStop(station_node);
                                            station_node=station_node->getPrevStop();                // if destination on T2 trip
                                        }


                                        fetched_path->addStop(station_node);
                                        cout<<" Printing fetched path on line 738 "<<endl;
                                        fetched_path->printPath();

                                        vector<MetroStop*> path=fetched_path->getStops();
                                        //reverse(path.begin(),path.end());
                                        cout<<endl;
                                        cout<<"printing path"<<endl;
                                        fetched_path->modify_stops(path);
                                        fetched_path->printPath();

                                        int fare=path[path.size()-1]->getFare()-path[0]->getFare();
                                        fare=abs(fare);
                                        fetched_path->setTotalFare(fare);
                                        cout<<fetched_path->getTotalFare()<<endl;
                                        cout<<fare<<endl;
                                        return fetched_path;
                                    }
                                    


                                    vector<MetroStop *> stops=tree->searchStop(station_node->getStopName())->getStops();

                                    //cout<<station_node->getStopName()<<endl;
                                    //if(stops.size()>=1){     
                                    if(stops.size()>=2){     
                                        cout<<endl;
                                        cout<<"JUNCTION NAME "<<endl;
                                        cout<<station_node->getStopName()<<endl;                 // junction
                                        int k=stops.size();
                                        cout<<k;
                                        for(int j=0;j<stops.size();j++){
                                            cout<<stops[j]->getLine()->getLineName()<<endl;
                                        }

                                        for(int j=0;j<stops.size();j++){
                                            //Trip * prev_trip=explore->dequeue();
                                            //Trip * T3=new Trip(stops[j]->getNextStop(),T2,"Forward");             // fwd
                                            Trip * T3=new Trip(stops[j],T2,"Forward",stops[j]->getLine());             // fwd
                                            explore->enqueue(T3);
                                            /*MetroLine *p=stops[j]->getLine();
                                            MetroStop * a=p->getNode();
                                            while(a!=NULL){
                                                if(tree->searchStop(a->getStopName())->getStops().size()>=2){
                                                    vector<MetroStop *> def=tree->searchStop(a->getStopName())->getStops();
                                                    for(int i=0;i<def.size();i++){
                                                        Trip * one=new Trip(def[i],T3,"Forward",def[i]->getLine());
                                                        Trip * two=new Trip(def[i],T3,"Backward",def[i]->getLine());
                                                        explore->enqueue(one);
                                                        explore->enqueue(two);
                                                    }
                                                    
                                                }
                                                a=a->getNextStop();
                                            }*/
                                            //Trip * T4=new Trip(stops[j]->getPrevStop(),T2,"Backward");           // bkwd
                                            Trip * T4=new Trip(stops[j],T2,"Backward",stops[j]->getLine());             // fwd
                                            explore->enqueue(T4);
                                        }
                                        cout<<" added trip objects to explore obj"<<endl;
                                        cout<<endl;
                                    }
                                    station_node=station_node->getNextStop();
                                }
            cout<<" just traversed using T2 trip pointer"<<endl;

            cout<<"proceeding towards queue of trip objects  "<<endl;
            
            /*Exploration * dummy=explore;
            while(!dummy->isEmpty()){
                cout<<dummy->dequeue()->getNode()->getStopName()<<endl;
            }*/
                                queue<Trip*> copy=explore->getTrips();
                                while(copy.size()!=0){
                                    Trip * a=copy.front();
                                    copy.pop();
                                    MetroLine * b=a->getLine();
                                    MetroStop * c=b->getNode();
                                    MetroStop * d=c;
                                    while(c!=NULL){
                                        if(tree->searchStop(c->getStopName())->getStops().size()>=2){
                                                    vector<MetroStop *> def=tree->searchStop(c->getStopName())->getStops();
                                                    for(int i=0;i<def.size();i++){
                                                        Trip * one=new Trip(def[i],a,"Forward",def[i]->getLine());
                                                        Trip * two=new Trip(def[i],a,"Backward",def[i]->getLine());
                                                        explore->enqueue(one);
                                                        explore->enqueue(two);
                                                    }
                                        }
                                        c=c->getNextStop();
                                    }
                                    /*while(d!=NULL){

                                        d=d->getPrevStop();
                                    }*/
                                }
            cout<<" going to traverse through explore queue "<<endl;
            Trip * current_trip=NULL;
            
                                while(!explore->isEmpty()  && fetched_path->getStops().size()==0){         //ComputeFare(fetched_path);  //&& fetched_path->getStops().size()==0
                                    //Trip * current_trip=explore->dequeue();
                                    current_trip=explore->dequeue();
                                    /*if (current_trip->getPrev()==NULL && current_trip->getDirection()=="Backward"){
                                        MetroLine * abc=current_trip->getLine();

                                    }*/
                                    string way=current_trip->getDirection();
                                    cout<<endl;
                                    cout<<"Junction name :   "<< current_trip->getNode()->getStopName()<<endl;        // junction name
                                    cout<<current_trip->getDirection()<<endl;
                                    cout<<current_trip->getLine()->getLineName()<<endl;
                                    MetroLine * curr_line=current_trip->getLine();

                                    //MetroStop * node=curr_line->search(curr_line,curr_line->getNode()->getStopName());  // junction node
                                    MetroStop * node=curr_line->search(curr_line,current_trip->getNode()->getStopName());  // junction node
                                    
                                    MetroStop * temp=node;
                                    if(way=="Forward"){
                                        //node=current_trip->getLine()->getNode();
                                       MetroStop * destination_found=curr_line->search_forward(curr_line,node,destination);       // node in metroline with metro station name as destination
                                        MetroStop * temp=destination_found;
                                        while(temp!=NULL && temp!=node->getPrevStop()){          //temp!=node->getPrevStop()
                                            cout<<temp->getStopName()<<endl; 
                                            fetched_path->addStop(temp);
                                            temp=temp->getPrevStop();
                                        }
                                        cout<<" first half  from destination to junction forward"<<endl;
                                       
                                    }
                                    else if(way=="Backward"){
                                        MetroStop * destination_found=curr_line->search_backward(curr_line,node,destination);
                                        MetroStop * temp=destination_found;
                                        while(temp!=NULL && temp!=node->getNextStop()){
                                            cout<<temp->getStopName()<<endl;            // replacing temp->getNextStop() by temp
                                            fetched_path->addStop(temp);
                                            temp=temp->getNextStop();
                                        }
                                        cout<<" first half from destination to junction backward"<<endl;
                                    }
                                }

                                // till above we have printed the path from destination to junction



                                if(fetched_path->getStops().size()!=0){
                                    Trip * parent=current_trip->getPrev();
                                    if(parent==NULL){
                                        vector<MetroStop*> stupid_path=fetched_path->getStops();
                                        int fare=stupid_path[stupid_path.size()-1]->getFare()-stupid_path[0]->getFare();
                                        fare=abs(fare);
                                        fetched_path->setTotalFare(fare);
                                        cout<<fetched_path->getTotalFare()<<endl;
                                        cout<<fare<<endl;
                                        continue;
                                    }
                                    MetroStop * start=station_node_copy;
                                    MetroStop * node_start=parent->getLine()->search(parent->getLine(),start->getStopName());      //MetroStop * start=station_node_copy;
                                   vector<MetroStop*> stupid_path=fetched_path->getStops();
                                   int fare=stupid_path[stupid_path.size()-1]->getFare()-stupid_path[0]->getFare();
                                    fare=abs(fare);
                                    fetched_path->setTotalFare(fare);
                                    cout<<fetched_path->getTotalFare()<<endl;
                                    cout<<fare<<endl;

                                    Path * useless_path=new Path();


                                    MetroStop * junction=current_trip->getNode();
                                    MetroStop * node_end=parent->getLine()->search(parent->getLine(),junction->getStopName());      // junction node
                                    MetroStop * temp1=node_end;
                                    MetroStop * temp2=node_end;
                                    //MetroStop * temp2=parent->getLine()->search_backward(parent->getLine(),junction->getStopName()); 
                                    if(parent->getDirection()=="Forward"){
                                        //while(temp1!=NULL && temp1!=node_start->getPrevStop()){
                                        while(temp1->getPrevStop()!=NULL && temp1!=node_start){
                                            if(useless_path->getStops().size()==0){             // newly added
                                                useless_path->addStop(temp1);
                                            }
                                            cout<<temp1->getPrevStop()->getStopName()<<endl;
                                            fetched_path->addStop(temp1->getPrevStop());
                                            useless_path->addStop(temp1->getPrevStop());
                                            temp1=temp1->getPrevStop();
                                        }
                                        cout<<" second half"<<endl;
                                    }
                                    else if(parent->getDirection()=="Backward"){
                                        //while(temp2!=NULL && temp2!=node_start->getNextStop()){
                                        while(temp2->getNextStop()!=NULL && temp2!=node_start){       // change   replaced temp2 by temp.getnext
                                            if(useless_path->getStops().size()==0){             // newly added
                                                useless_path->addStop(temp1);
                                            }

                                            cout<<temp2->getNextStop()->getStopName()<<endl;
                                            fetched_path->addStop(temp2->getNextStop());                         // change
                                            useless_path->addStop(temp2->getNextStop());
                                            //temp2=temp2->getPrevStop();
                                            temp2=temp2->getNextStop();
                                        }
                                        cout<<" second half"<<endl;
                                    }


                                    vector<MetroStop*> path=fetched_path->getStops();
                                   // reverse(path.begin(),path.end());
                                    cout<<endl;
                                   cout<<"printing path"<<endl;
                                    fetched_path->modify_stops(path);
                                    fetched_path->printPath();

                                    //int fare=path[path.size()-1]->getFare()-path[0]->getFare();
                                    //fare=abs(fare);
                                    vector<MetroStop *> w=useless_path->getStops();
                                    int prev_fare=fetched_path->getTotalFare();
                                    int now_fare= w[ w.size()-1]->getFare()- w[0]->getFare();
                                    now_fare=abs(now_fare);
                                    int new_fare=prev_fare+now_fare;
                                    cout<<prev_fare<<endl;               // fine
                                    cout<<now_fare<<endl;
                                    //new_fare=abs(new_fare);
                                    fetched_path->setTotalFare(new_fare);
                                    cout<<fetched_path->getTotalFare()<<endl;
                                    cout<<new_fare<<endl;
                                    return fetched_path;
                                }
                                     }

            //cout<<"FARE         "<<fetched_path->getTotalFare()<<endl;
            //ComputeFare(fetched_path);
            cout<<"reached the end"<<endl;
            return fetched_path;
}
vector<MetroLine*> lines;


