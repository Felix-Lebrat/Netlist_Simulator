#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <iostream>

template <typename T>
class Graph
{
private:
    enum Mark {NotVisited,InProgress,Visited};
    struct Node
    {
        Node(){};
        Node(T label,Mark mark):label(label),mark(mark){};
        T label;
        Mark mark;
        std::vector<Node*> link_too;
        std::vector<Node*> linked_by;
    };
    std::vector<Node> m_nodes;
    bool explore(Node *n);
    void explore2(Node *n,std::vector<T> *v);
public:
    void add_node(T x);
    Node* node_of_label(T x);
    void add_edge(T x,T y);
    void clear_marks();
    bool has_cycle();
    std::vector<T> topological();
};

template <typename T>
void Graph<T>::add_node(T x)
{
    m_nodes.push_back(Node(x,NotVisited));
}

using namespace std;

template <typename T>
typename Graph<T>::Node* Graph<T>::node_of_label(T x)
{
    for(int i=0;i<m_nodes.size();i++)
    {
        if(m_nodes[i].label==x)
            return &m_nodes[i];
    }
    return NULL;
}

template <typename T>
void Graph<T>::add_edge(T x,T y)
{
    Graph<T>::Node *n1=node_of_label(x);
    Graph<T>::Node *n2=node_of_label(y);

    n1->link_too.push_back(n2);
    n2->linked_by.push_back(n1);
}

template <typename T>
void Graph<T>::clear_marks()
{
    for(int i=0;i<m_nodes.size();i++)
    {
        m_nodes[i].mark=NotVisited;
    }
}


template <typename T>
bool Graph<T>::explore(Node *n)
{
    if(n->mark==InProgress)
        return true;
    bool ret=false;
    if(n->mark==NotVisited)
    {
        n->mark=InProgress;
        for(int i=0;i<n->link_too.size();i++)
        {
            if(explore(n->link_too[i]))
                return true;
        }
        n->mark=Visited;
    }
    return false;
}

template <typename T>
bool Graph<T>::has_cycle()
{
    clear_marks();
    for(int i=0;i<m_nodes.size();i++)
    {
        if(explore(&(m_nodes[i])))
        {
            return true;
        }
    } 
    return false;
}

template <typename T>
void Graph<T>::explore2(Node *n,vector<T> *v)
{
    if(n->mark==NotVisited)
    {
        n->mark=Visited;
        for(int i=0;i<n->linked_by.size();i++)
        {
            explore2(n->linked_by[i],v);
        }
        v->push_back(n->label);
    }
}

template <typename T>
vector<T> Graph<T>::topological()
{
    if(has_cycle())
    {
        cerr<<"le graphe a un cycle"<<endl;
        exit(EXIT_FAILURE);
    }

    clear_marks();
    vector<T> ret;
    for(int i=0;i<m_nodes.size();i++)
    {
        explore2(&m_nodes[i],&ret);
    }
    return ret;
}

#endif