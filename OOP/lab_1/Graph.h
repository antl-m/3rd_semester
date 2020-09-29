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

template<typename V, typename E>
class Graph;


namespace GraphImplNamespace {

    template<class V, class E, typename std::enable_if<!std::is_arithmetic<E>::value, int>::type = 0>
    std::vector<E> _length_func(const Graph<V, E> *this_p, const V &v1, const V &v2) {
        std::map<V, std::vector<E>> v_to_dist;
        std::map<V, Bool> v_to_mark;
        std::queue<V> q;
        q.push(v1);
        while (!q.empty()) {
            const V &cur = q.front();
            q.pop();
            for (std::size_t i = 0; i < this_p->_count_adjacent_to_v(cur); ++i) {
                V adj = this_p->_adjacent_to_v_by_pos(cur, i);
                if (!v_to_mark[adj]) {
                    v_to_mark[adj] = true;
                    q.push(adj);
                }
                auto cur_dist = v_to_dist[cur];
                cur_dist.push_back(this_p->_edge_of(cur, adj));
                if (v_to_dist[adj].empty() || cur_dist.size() < v_to_dist[adj].size())
                    v_to_dist[adj] = cur_dist;
            }
        }
        return v_to_dist[v2];
    }

    template<class V, class E, typename std::enable_if<std::is_arithmetic<E>::value, int>::type = 0>
    std::vector<E> _length_func(const Graph<V, E> *this_p, const V &v1, const V &v2) {
        std::map<V, std::vector<E>> v_to_dist;
        std::map<V, Bool> v_to_mark;
        std::queue<V> q;
        q.push(v1);
        v_to_dist[v1].push_back(E{0});
        v_to_mark[v1] = true;
        while (!q.empty()) {
            const auto &cur = q.front();
            q.pop();
            std::map<V, Bool> adj_mark;
            for (std::size_t i = 0; i < this_p->_count_adjacent_to_v(cur); ++i) {
                V adj = this_p->_adjacent_to_v_by_pos(cur, i);
                for (std::size_t j = 0; j < this_p->_count_adjacent_to_v(cur); ++j) {
                    auto min_adj = this_p->_adjacent_to_v_by_pos(cur, j);
                    if (adj_mark[adj]/* v_to_mark[adj] */ ||
                        (this_p->_edge_of(cur, min_adj) < this_p->_edge_of(cur, adj) && !v_to_mark[min_adj]))
                        adj = min_adj;
                }
                if (!v_to_mark[adj]) {
                    v_to_mark[adj] = true;
                    q.push(adj);
                }
                adj_mark[adj] = true;
                E cur_dist = (v_to_dist[cur].empty() ? 0 : v_to_dist[cur][0]) + this_p->_edge_of(cur, adj);
                if (v_to_dist[adj].empty())
                    v_to_dist[adj].push_back(cur_dist);
                else if (cur_dist < v_to_dist[adj][0])
                    v_to_dist[adj][0] = cur_dist;
            }
        }
        return v_to_dist[v2];
    }
}


template<class V, class E>
class Graph {
public:
    virtual void push_edge(const E &e, const V &v1, const V &v2) = 0;

    virtual void push_vertex(const V &v) = 0;

    bool connectivity() const;

    std::vector<E> length(const V &v1, const V &v2) const;

    virtual std::size_t size() const = 0;

protected:

    virtual V _get_by_pos(std::size_t pos) const = 0;

    virtual std::size_t _count_adjacent_to_v(const V &v) const = 0;

    virtual V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const = 0;

    virtual E _edge_of(const V &v1, const V &v2) const = 0;

    friend std::vector<E> GraphImplNamespace::_length_func<>(const Graph<V, E> *this_p, const V &v1, const V &v2);
};

template<class V, class E>
std::vector<E> Graph<V, E>::length(const V &v1, const V &v2) const {
    return GraphImplNamespace::_length_func(this, v1, v2);
}

template<class V, class E>
bool Graph<V, E>::connectivity() const {
    V s = _get_by_pos(0);
    std::map<V, Bool> used;
    used[s] = true;
    std::queue<V> q;
    q.push(s);
    while (!q.empty()) {
        V v = q.front();
        q.pop();
        for (std::size_t i = 0;
             i < _count_adjacent_to_v(v); ++i) {
            V to = _adjacent_to_v_by_pos(v, i);
            if (!used[to]) {
                used[to] = true;
                q.push(to);
            }
        }
    }
    return used.size() == size();
}


template<class V, class E>
class MatrixStruct : public std::map<V, std::map<V, E>> {
};


template<class V, class E>
class MatrixGraph : public Graph<V, E> {
public:
    void push_edge(const E &e, const V &v1, const V &v2) override;

    void push_vertex(const V &v) override;

    std::size_t size() const override;

private:

    V _get_by_pos(std::size_t pos) const override;

    std::size_t _count_adjacent_to_v(const V &v) const override;

    V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const override;

    E _edge_of(const V &v1, const V &v2) const override;

    std::set<V> verts;
    MatrixStruct<V, E> matrx;
};

template<class V, class E>
void MatrixGraph<V, E>::push_edge(const E &e, const V &v1, const V &v2) {
    if (verts.count(v1) == 0 || verts.count(v2) == 0) {
        std::stringstream message;
        message << "push_edge: no " << (verts.count(v1) == 0 ? v1 : v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if (matrx.count(v1) && matrx.at(v1).count(v2)) {
        std::stringstream message;
        message << "pushEdge: you want to push " << e << " edge at place of " << matrx[v1][v2] << " edge.";
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
    for (const auto &v: verts) {
        if (cur == pos)
            return v;
        ++cur;
    }
    throw GraphExc("_get_by_pos: pos " + std::to_string(pos) + " out of range");
}

template<class V, class E>
std::size_t MatrixGraph<V, E>::_count_adjacent_to_v(const V &v) const {
    if (matrx.count(v)) {
        return matrx.at(v).size();
    }
    std::stringstream message;
    message << "_count_adjacent_to_v: no vertex " << v << " in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
V MatrixGraph<V, E>::_adjacent_to_v_by_pos(const V &v, std::size_t pos) const {
    if (matrx.count(v)) {
        std::size_t cur = 0;
        for (const auto&[vert, edg]: matrx.at(v)) {
            if (cur == pos)
                return vert;
            ++cur;
        }
    }
    std::stringstream message;
    message << "_adjacent_to_v_by_pos: no vertex " << v << " in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
E MatrixGraph<V, E>::_edge_of(const V &v1, const V &v2) const {
    if (verts.count(v1) == 0 || verts.count(v2) == 0) {
        std::stringstream message;
        message << "_edge_of: no " << (verts.count(v1) == 0 ? v1 : v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if (matrx.count(v1) && matrx.at(v1).count(v2)) {
        return matrx.at(v1).at(v2);
    }
    std::stringstream message;
    message << "_edge_of: no edge between " << v1 << " and " << v2 << ".";
    throw GraphExc(message.str());
}

template<class V, class E>
std::size_t MatrixGraph<V, E>::size() const {
    return verts.size();
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
bool operator==(const Node<V, E> &l, const Node<V, E> &r) {
    return l.vertex == r.vertex;
}

template<class V, class E>
class LinkedGraph : public Graph<V, E> {
public:
    void push_edge(const E &e, const V &v1, const V &v2) override;

    void push_vertex(const V &v) override;

private:
    V _get_by_pos(std::size_t pos) const;

    std::size_t _count_adjacent_to_v(const V &v) const;

    V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const;

    E _edge_of(const V &v1, const V &v2) const;

    bool _check_edge(const V &v1, const V &v2) const;

    std::size_t size() const override;

    std::map<V, std::set<Node<V, E>>> link_struct;
};

template<class V, class E>
void LinkedGraph<V, E>::push_edge(const E &e, const V &v1, const V &v2) {
    if (link_struct.count(v1) == 0 || link_struct.count(v2) == 0) {
        std::stringstream message;
        message << "push_edge: no " << (link_struct.count(v1) == 0 ? v1 : v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if (_check_edge(v1, v2)) {
        std::stringstream message;
        message << "push_edge: you want to push " << e << " edge at place of " << _edge_of(v1, v2) << " edge.";
        throw GraphExc(message.str());
    }
    link_struct[v1].insert({v2, e});
    link_struct[v2].insert({v1, e});
}

template<class V, class E>
void LinkedGraph<V, E>::push_vertex(const V &v) {
    link_struct.insert({v, {}});
}

template<class V, class E>
bool LinkedGraph<V, E>::_check_edge(const V &v1, const V &v2) const {
    return link_struct.count(v1) && link_struct.at(v1).find(Node<V, E>{v2, E()}) != link_struct.at(v1).end();

}

template<class V, class E>
V LinkedGraph<V, E>::_get_by_pos(std::size_t pos) const {
    std::size_t cur = 0;
    for (const auto &[vert, node_set]: link_struct) {
        if (cur == pos)
            return vert;
        ++cur;
    }
    throw GraphExc("_get_by_pos: pos " + std::to_string(pos) + " out of range");
}

template<class V, class E>
std::size_t LinkedGraph<V, E>::_count_adjacent_to_v(const V &v) const {
    if (link_struct.count(v)) {
        return link_struct.at(v).size();
    }
    std::stringstream message;
    message << "_count_adjacent_to_v: no vertex " << v << " in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
V LinkedGraph<V, E>::_adjacent_to_v_by_pos(const V &v, std::size_t pos) const {
    if (link_struct.count(v)) {
        std::size_t cur = 0;
        for (const auto&[vert, edg]: link_struct.at(v)) {
            if (cur == pos)
                return vert;
            ++cur;
        }
    }
    std::stringstream message;
    message << "_adjacent_to_v_by_pos: no vertex " << v << " in graph";
    throw GraphExc(message.str());
}

template<class V, class E>
E LinkedGraph<V, E>::_edge_of(const V &v1, const V &v2) const {
    if (link_struct.count(v1) == 0 || link_struct.count(v2) == 0) {
        std::stringstream message;
        message << "_edge_of: no " << (link_struct.count(v1) == 0 ? v1 : v2) << " vertex in graph.";
        throw GraphExc(message.str());
    }
    if (_check_edge(v1, v2)) {
        auto node_it = link_struct.at(v1).find(Node<V, E>{v2, E()});
        return node_it->edge;
    }
    std::stringstream message;
    message << "_edge_of: no edge between " << v1 << " and " << v2 << ".";
    throw GraphExc(message.str());
}

template<class V, class E>
std::size_t LinkedGraph<V, E>::size() const {
    return link_struct.size();
}


#endif //GRAPH_H
