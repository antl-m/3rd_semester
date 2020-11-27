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

class GraphExc : public std::logic_error {
 public:
  explicit GraphExc(const std::string &message) : std::logic_error(message) {}
};

template<class V, class E>
class Graph {
 public:
  virtual void push_edge(const E &e, const V &v1, const V &v2) = 0;
  virtual void push_vertex(const V &v) = 0;
  bool connectivity() const;
  std::map<V, std::vector<E>> length(const V &v) const;
  virtual std::size_t size() const = 0;
  friend std::ostream &operator<<(std::ostream &out, const Graph<V, E> &g) {
    return g._print(out);
  }

 protected:

  virtual std::ostream &_print(std::ostream &out) const = 0;

  virtual V _get_by_pos(std::size_t pos) const = 0;

  virtual std::size_t _count_adjacent_to_v(const V &v) const = 0;

  virtual V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const = 0;

  virtual E _edge_of(const V &v1, const V &v2) const = 0;
};

template<class V, class E>
std::map<V, std::vector<E>> Graph<V, E>::length(const V &v) const {
  std::map<V, std::vector<E>> v_to_dist;
  std::map<V, bool> v_to_mark;
  std::queue<V> q;
  q.push(v);
  while (!q.empty()) {
    const V &cur = q.front();
    q.pop();
    for (std::size_t i = 0; i < this->_count_adjacent_to_v(cur); ++i) {
      V adj = this->_adjacent_to_v_by_pos(cur, i);
      if (!v_to_mark[adj]) {
        v_to_mark[adj] = true;
        q.push(adj);
      }
      auto cur_dist = v_to_dist[cur];
      cur_dist.push_back(this->_edge_of(cur, adj));
      if (v_to_dist[adj].empty() || cur_dist.size() < v_to_dist[adj].size())
        v_to_dist[adj] = cur_dist;
    }
  }
  return v_to_dist;
}

template<class V, class E>
bool Graph<V, E>::connectivity() const {
  V s = _get_by_pos(0);
  std::map<V, bool> used;
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
struct Node {
  V vertex;
  E edge;
};

template<class V, class E>
bool operator<(const Node<V, E> &lhs, const Node<V, E> &rhs) {
  return lhs.vertex < rhs.vertex;
}

template<class V, class E>
std::ostream &operator<<(std::ostream &out, const Node<V, E> &n) {
  return out << "(" << n.vertex << ", " << n.edge << ")";
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
  std::ostream &_print(std::ostream &out) const override;
  V _get_by_pos(std::size_t pos) const;
  std::size_t _count_adjacent_to_v(const V &v) const;
  V _adjacent_to_v_by_pos(const V &v, std::size_t pos) const;
  E _edge_of(const V &v1, const V &v2) const;
  bool _check_edge(const V &v1, const V &v2) const;
  std::size_t size() const override;

 private:
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

template<class V, class E>
std::ostream &LinkedGraph<V, E>::_print(std::ostream &out) const {
  return out << link_struct;
}

#endif //GRAPH_H
