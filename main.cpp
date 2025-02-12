#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
struct State{
    int capacity;
    int distance;
    int node;
    bool operator<(const State& other) const{
        if (capacity == other.capacity){
            return distance > other.distance;
        }
        return capacity < other.capacity;
    }
};

vector<int> dijkstra_max_capacity(int N, vector<vector<pii>>& graph, int start, int end, vector<int>& parent){
    vector<int> max_capacity(N, INT_MIN);
    vector<int> distance(N, INT_MAX);
    priority_queue<State> pq;
    max_capacity[start] = INT_MAX;
    distance[start] = 0;
    pq.push({INT_MAX, 0, start});
    while (!pq.empty()){
        State current = pq.top();
        pq.pop();
        int u = current.node;
        int current_capacity = current.capacity;
        int current_distance = current.distance;
        if (u == end) break;
        if (current_capacity < max_capacity[u] || (current_capacity == max_capacity[u] && current_distance > distance[u])){
            continue;
        }
        for (auto& edge : graph[u]){
            int v = edge.second;
            int weight = edge.first;
            int new_capacity = min(current_capacity, weight);
            int new_distance = current_distance + 1;
            if (new_capacity > max_capacity[v] || (new_capacity == max_capacity[v] && new_distance < distance[v])){
                max_capacity[v] = new_capacity;
                distance[v] = new_distance;
                parent[v] = u;
                pq.push({new_capacity, new_distance, v});
            }
        }
    }
    return max_capacity;
}

vector<int> reconstruct_path(int start, int end, const vector<int>& parent){
    vector<int> path;
    for (int v = end; v != start; v = parent[v]){
        path.push_back(v);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<pii>> graph(N);
    vector<int> parent(N, -1);
    for (int i = 0; i < M; ++i){
        int A, B, W;
        cin >> A >> B >> W;
        A--; 
        B--;
        graph[A].push_back({W, B});
    }
    int S, T;
    cin >> S >> T;
    S--;
    T--;
    vector<int> max_capacity = dijkstra_max_capacity(N, graph, S, T, parent);
    if (max_capacity[T] == INT_MIN){
        cout << "Нет быстрой пути" << endl;
    }else{
        vector<int> path = reconstruct_path(S, T, parent);
        cout << "Путь: ";
        for (int i = 0; i < path.size(); ++i){
            cout << path[i] + 1;
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
    return 0;
}
