#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {info = inf;}
};


template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
//    Graph & removeEdge(const N &begin, const N &end);
//    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
//    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }

// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
public:
    N info1, info2;
    EdgeAlreadyExists(N &beg, N &end){info1 = beg, info2 = end;}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &ed)
{ out << "Node already exists: " << ed.info1 << " " << ed.info2; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }



// CLASS GRAPH
template <class N, class E>
Graph<N, E>:: Graph(){}

template <class N, class E>
Graph<N, E>:: ~Graph()
{
    typename vector <Node<N, E>*>:: iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
}

template <class N, class E>
unsigned Graph<N,E>::numNodes() const
{
    return nodes.size();
}

template <class N, class E>
unsigned Graph<N,E>::numEdges() const
{
    int nEdges = 0;
    typename vector<Node<N, E>*>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        nEdges += (*it)->edges.size();
    }
    return nEdges;
}

template <class N, class E>
Graph<N, E>& Graph<N, E>::addNode(const N &inf)
{
    typename vector<Node<N,E>*>::iterator it;

    for ( it = nodes.begin(); it != nodes.end(); it++)
        if (inf == (*it)->info) throw NodeAlreadyExists<N>(inf);

    Node<N, E> *n = new Node<N, E>(inf);
    nodes.push_back(n);
    return *this;
}

template <class N, class E>
Graph<N,E> & Graph<N,E>::addEdge(const N &begin, const N &end, const E &val)
{
    typename vector< Node<N, E>*>::iterator it;
    typename vector< Edge<N, E>>::iterator ite;
    bool foundBegin = false;
    bool foundEnd = false;
    Node<N, E> * endNode = NULL;
    Node<N, E> * begNode = NULL;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        if ((*it)->info == begin)
        {
            foundBegin = true;
            begNode = *it;
            for (ite = (*it)->edges.begin(); ite != (*it)->edges.end(); ite++)
                if (ite->destination->info == end) throw EdgeAlreadyExists <N>(begin, end);

            if (foundEnd) break;
        }
        else if ((*it)->info == end)
        {
            endNode = (*it);
            foundEnd = true;
            if (foundBegin) break;
        }
    }
    if (!foundBegin) throw NodeDoesNotExist<N>(begin);
    if (!foundEnd) throw NodeDoesNotExist<N>(end);

    Edge<N,E> e(endNode, val);
    begNode->edges.push_back(e);
    return *this;
}