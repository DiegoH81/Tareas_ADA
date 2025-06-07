#include <iostream>
#include <vector>
#include <queue>

class edge;

class node
{
public:
    int value;
    std::vector<edge> adjacent;

    node(int in_val = -1) : value(in_val), adjacent() {}
};

class edge
{
public:
    node* src, * dest ;
    int weight;

    edge(int in_weight, node* in_src, node* in_dest): weight(in_weight), src(in_src), dest(in_dest)
    {}

    bool operator == (edge& a)
    {
        if (((this->dest == a.dest) && (this->src == a.src) && (this->weight == a.weight)) ||
            ((this->dest == a.src) && (this->src == a.dest) && (this->weight == a.weight))
            )
            return true;

        return false;
    }

};

class comp_edge
{
public:

    bool operator() (edge& a, edge& b) { return a.weight > b.weight; }

};

class adjacent_list
{
private:
    using p_queue = std::priority_queue< edge, std::vector<edge>, comp_edge>;

    std::vector< node* > map;

    bool find_edge_in_node(node* node, edge in_edge)
    {
        for (int i = 0; i < node->adjacent.size(); i++)
            if (node->adjacent[i] == in_edge)
                return true;

        return false;
    }

    void print_node(node* in_node)
    {
        if (!in_node) return;

        std::cout << in_node->value << " :\n";

        std::vector<edge>& adj = in_node->adjacent;

        for (int i = 0; i < adj.size(); i++)
            std::cout << adj[i].src->value << " - " << adj[i].dest->value << " : " << adj[i].weight << "    ";
        std::cout << "\n";
    }

    void add_edges_to_p_q(node* in_node, p_queue& queue)
    {
        for (auto it : in_node->adjacent)
            queue.push(it);
    }

    bool is_node_visited(node* in_node, std::vector<node*> nodes_vec)
    {
        for (auto it : nodes_vec)
            if (it == in_node)
                return true;

        return false;
    }
public:
    struct data
    {
        int src, dest, weight;
        data(int in_src, int in_dest, int in_weight): src(in_src), dest(in_dest), weight(in_weight)
        {}
    };


    adjacent_list(int in_n_nodes)
    {
        for (int i = 0; i < in_n_nodes; i++)
            map.push_back(new node(i + 1));
    }

    void build_list(std::vector < data > in_vec)
    {
        for (int i = 0; i < in_vec.size(); i++)
        {
            int origen{ in_vec[i].src - 1 }, destino{ in_vec[i].dest - 1 }, peso{in_vec[i].weight};

            edge new_edge(peso, map[origen], map[destino]);
            if (!find_edge_in_node(map[origen], new_edge))
                map[origen]->adjacent.push_back(new_edge);

            if (!find_edge_in_node(map[destino], new_edge))
                map[destino]->adjacent.push_back(new_edge);

        }
    }

    void prim()
    {
        std::vector<node* > visited;
        p_queue queue;

        int origin{ 0 }, suma{ 0 };

        visited.push_back(map[origin]);
        add_edges_to_p_q(map[origin], queue);

        while (!queue.empty())
        {
            edge top = queue.top();
            node* a = top.dest, * b = top.src;
            queue.pop();


            if (!is_node_visited(a, visited))
            {
                visited.push_back(a);
                add_edges_to_p_q(a, queue);
                suma += top.weight;
            }
            if (!is_node_visited(b, visited))
            {
                visited.push_back(b);
                add_edges_to_p_q(b, queue);
                suma += top.weight;
            }

            
        }

        std::cout << "SUMA TOTAL: " << suma << "\n";
    }

    void print()
    {
        std::cout << "LISTA\n";
        for (int i = 0; i < map.size(); i++)
            print_node(map[i]);
    }

};



int main()
{
    using data = adjacent_list::data;


    int node_number{ 7 };
    

    adjacent_list test(node_number);

    test.build_list({ data(1, 2, 2), data(1, 3, 3) , data(1, 4, 3) ,
                      data(4, 3, 5) , data(4, 6, 7) , data(3, 6, 6), data(3, 5, 1),
                      data(2, 5, 4) , data(6, 7, 9) , data(2, 3, 4), data(5, 6, 8)
                     });


    test.print();

    test.prim();
}