// chyba dfs od liścia, pierwszy wierzchołek o innym kolorze musi być korzeniem
// wystarczy potem sprawdzić czy jego poddrzewa mają ten sam kolor
#include <vector>
#include <stack>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 500001

using namespace std;

typedef unsigned long vertex_t;

vector<vertex_t> tree[NMAX];
unsigned long    colors[NMAX];
char visited[NMAX];

int check_subtree(vertex_t s) {
  stack<vertex_t> search_stack;
  unsigned long color = colors[s];
  search_stack.push(s);
  
  while (!search_stack.empty()) {
    vertex_t el = search_stack.top();
    search_stack.pop();
    
    visited[el] = 1;
    
    if (colors[el] != color) return 0;

    for (size_t i = 0; i < tree[el].size(); i ++) {
      if (visited[tree[el][i]]) continue;
      search_stack.push(tree[el][i]);
    }
  }

  return 1;
}

int check_children(vertex_t s) {
  memset(visited, 0, NMAX);
  visited[s] = 1;

  // printf("checking children of: %lu\n", s + 1);

  for (size_t i = 0; i < tree[s].size(); i ++) {
    if (!check_subtree(tree[s][i])) return 0;
  }
  return 1;
}

int dfs(vertex_t s) {
  stack<vertex_t> search_stack;
  unsigned long color = colors[s];
  search_stack.push(s);
  
  while (!search_stack.empty()) {
    vertex_t el = search_stack.top();
    search_stack.pop();
    visited[el] = 1;

    // printf("dfs: checking node %lu\n", el + 1);

    for (size_t i = 0; i < tree[el].size(); i ++) {
      if (visited[tree[el][i]]) continue;
      if (colors[tree[el][i]] != color) {
        if (check_children(tree[el][i])) return 1;
        if (check_children(el)) return 1;
        return 0;
      } else {
        search_stack.push(tree[el][i]);
      }
    }
  }
  return 1;
}

int main() {
  unsigned long n;
  scanf("%lu", &n);
  memset(visited, 0, NMAX);
  for (unsigned long i = 0; i < n - 1; i ++) {
    vertex_t a, b;
    scanf("%lu %lu", &a, &b);
    tree[a - 1].push_back(b - 1);
    tree[b - 1].push_back(a - 1);
  }

  for (vertex_t i = 0; i < n; i ++) {
    scanf("%lu", &colors[i]);
  }

  // for (vertex_t i = 0; i < n; i ++) {
  //   printf("node %lu: color - %lu, children:", i + 1, colors[i]);
  //   for (vertex_t j = 0; j < tree[i].size(); j ++) {
  //     printf(" %lu", tree[i][j] + 1);
  //   }
  //   printf("\n");
  // }

  vertex_t leaf_idx = 0;
  while (!(tree[leaf_idx].size() == 1)) leaf_idx ++;
  // printf("first leaf: %lu\n", leaf_idx + 1);

  if (dfs(leaf_idx)) 
    printf("TAK\n");
  else
    printf("NIE\n");
}