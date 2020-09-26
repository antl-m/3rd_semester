#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <memory>
#include <type_traits>
#include <algorithm>
#include "Bool.h"








class GraphExc : public std::logic_error {
public:
    explicit GraphExc(const std::string &message);
};







template<class V, class E>
class Graph {
public:
    virtual void push_edge(const E &e, const V& v1, const V& v2) = 0;

    virtual void push_vertex(const V &v) = 0;

    bool connectivity() const;

    std::vector<E> length(const V &v1, const V &v2) const;

protected:
    virtual V _get_by_pos(std::size_t pos) const = 0;

    virtual std::size_t _count_adjacent_to_v(const V &v) const = 0;

    virtual V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const = 0;

    virtual E _edge_of(const V &v1, const V &v2) const = 0;

    virtual std::vector<V> _all_adjacent_to(const V &v) const = 0;

    virtual std::size_t _size() const = 0;
};






template<class V, class E>
bool Graph<V, E>::connectivity() const {
    V s = _get_by_pos(0);
    std::map<V, Bool> used; // логический массив, указывающий, посещена ли вершина
    used[s] = true;
    std::queue<V> q;
    q.push(s);
    while (!q.empty()) // пока мы не обойдем все вершины, которые можно достигнуть из данной
    {
        V v = q.front();
        q.pop(); // достаем из головы очереди одну вершину
        std::cerr<<"current vertex is "<<v<<std::endl;
        for (std::size_t i = 0;
             i < _count_adjacent_to_v(v); ++i) //просмотрим все ребра, исходящие из данной вершины
        {
            std::cerr <<std::endl;
            for(const auto& temp: _all_adjacent_to(v)){
                std::cerr<< temp << ", ";
            }
            std::cerr <<std::endl;
            V to = _adjacent_to_v_by_pos(v, i);
            if (!used[to]) // если текущая вершина еще не была посещена
            {
                std::cerr<<"current adjacent is "<<to<<std::endl;
                used[to] = true; //отмечаем, что мы ее посетили
                q.push(to); // помещаем в очередь
            }
        }
    }
    std::cerr << std::endl;
    for(const auto& [v, b]: used){
        std::cerr<< "{"<<v<<": "<<b<<"} ";
    }
    std::cerr << std::endl;
    return used.size() == _size(); // если все вершины посещены, то граф связный
}

template<class V, class E>
std::vector<E> Graph<V, E>::length(const V &v1, const V &v2) const {
    std::map<V, std::vector<E>> v_to_dist;
    std::map<V, Bool> v_to_mark;
    bool is_integral = std::is_integral<E>::value;
    std::queue<V> q;
    q.push(v1);
    while (!q.empty()) {
        const V &cur = q.front();
        q.pop();
        for (std::size_t i = 0; i < _count_adjacent_to_v(cur); ++i) {
            V adj = _adjacent_to_v_by_pos(cur, i);
            if(is_integral){
                for (std::size_t j = 0; j < _count_adjacent_to_v(cur); ++j){
                    if(_edge_of(cur, _adjacent_to_v_by_pos(cur, j)) < _edge_of(cur, adj) &&
                       !v_to_mark[adj])
                        adj = _adjacent_to_v_by_pos(cur, j);
                }
            }
            if(!v_to_mark[adj]){
                v_to_mark[adj] = true;
                q.push(adj);
                if(is_integral){
                    E cur_dist = (v_to_dist[cur].empty()?0:v_to_dist[cur][0]) +_edge_of(cur, adj);
                    if(v_to_dist[adj].empty() || cur_dist < v_to_dist[adj][0])
                        v_to_dist[adj][0] = cur_dist;
                }else{
                    auto cur_dist = v_to_dist[cur];
                    cur_dist.push_back(_edge_of(cur, adj));
                    if(cur_dist.size() < v_to_dist[adj].size())
                        v_to_dist[adj] = cur_dist;
                }
            }
        }
    }
    return v_to_dist[v2];
}








template<class V, class E>
class MatrixStruct : public std::map<V, std::map<V, E>> {};



template<class V, class E>
class MatrixGraph : public Graph<V, E> {
public:
    void push_edge(const E &e, const V& v1, const V& v2) override;

    void push_vertex(const V &v) override;

private:
    V _get_by_pos(std::size_t pos) const override;

    std::size_t _count_adjacent_to_v(const V &v) const override;

    V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const override;

    E _edge_of(const V &v1, const V &v2) const override;

    std::vector<V> _all_adjacent_to(const V &v) const override{
        std::vector<V> res;
        if(matrx.count(v)){
            for (const auto& [vert, edg]: matrx.at(v)) {
                res.push_back(vert);
            }
        }
        return res;
    }

    std::size_t _size() const{
        return verts.size();
    }

    std::set<V> verts;
    MatrixStruct<V, E> matrx;
};

template<class V, class E>
void MatrixGraph<V, E>::push_edge(const E &e, const V &v1, const V &v2) {
    if(verts.count(v1) == 0 || verts.count(v2) == 0){
        std::stringstream message;
        message << "push_edge: no " << (verts.count(v1) == 0? v1: v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if(matrx.count(v1) && matrx.at(v1).count(v2)){
        std::stringstream message;
        message << "pushEdge: you want to push " << e << " edge at place of "<<matrx[v1][v2]<<" edge.";
        throw GraphExc(message.str());
    }
    matrx[v1][v2] = e;
    matrx[v2][v1] = e;
}

template<class V, class E>
void MatrixGraph<V, E>::push_vertex(const V &v) {
    verts.insert(v);
}

template<class V, class E>
V MatrixGraph<V, E>::_get_by_pos(std::size_t pos) const {
    std::size_t cur = 0;
    for (const auto& v: verts) {
        if(cur == pos)
            return v;
        ++cur;
    }
    throw GraphExc("_get_by_pos: pos " + std::to_string(pos) + " out of range");
}

template<class V, class E>
std::size_t MatrixGraph<V, E>::_count_adjacent_to_v(const V &v) const {
    if(matrx.count(v)){
        return matrx.at(v).size();
    }
    std::stringstream message;
    message << "_count_adjacent_to_v: no vertex "<< v <<" in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
V MatrixGraph<V, E>::_adjacent_to_v_by_pos(const V &v, std::size_t pos) const {
    if(matrx.count(v)){
        std::size_t cur = 0;
        for (const auto& [vert, edg]: matrx.at(v)) {
            if(cur == pos)
                return vert;
            ++cur;
        }
    }
    std::stringstream message;
    message << "_adjacent_to_v_by_pos: no vertex "<< v <<" in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
E MatrixGraph<V, E>::_edge_of(const V &v1, const V &v2) const {
    if(verts.count(v1) == 0 || verts.count(v2) == 0){
        std::stringstream message;
        message << "_edge_of: no " << (verts.count(v1) == 0? v1: v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if(matrx.count(v1) && matrx.at(v1).count(v2)){
        return matrx.at(v1).at(v2);
    }
    std::stringstream message;
    message << "_edge_of: no edge between " << v1 << " and " << v2 << ".";
    throw GraphExc(message.str());
}








template<class V, class E>
struct Node {
    V vertex;
    E edge;
};


template<class V, class E>
bool operator<(const Node<V, E> &lhs, const Node<V, E> &rhs) {
    return lhs.vertex < rhs.vertex;
}

template<class V, class E>
class LinkedGraph : public Graph<V, E> {
public:
    void push_edge(const E &e, const V& v1, const V& v2) override;

    void push_vertex(const V &v) override;

private:
    V _get_by_pos(std::size_t pos) const;

    std::size_t _count_adjacent_to_v(const V &v) const;

    V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const;

    E _edge_of(const V &v1, const V &v2) const;

    std::map<V, std::set<Node<V, E>>> link_struct;
};


#endif //GRAPH_H
