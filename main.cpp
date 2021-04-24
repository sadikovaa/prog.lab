#include "pugixml.hpp"
#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;
using namespace pugi;

struct Vertex {
    pair<double,double> point;
    bool used = false;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    xml_document doc;
    doc.load_file("auto.xml");
    xml_node dataset = doc.child("dataset");
    unordered_map<string, vector<Vertex>> tram_graph;
    unordered_map<string, vector<Vertex>> troll_graph;
    unordered_map<string, vector<Vertex>> bus_graph;
    unordered_map<string, int> streets;
    unordered_map<string, int> tram_routes;
    unordered_map<string, int> troll_routes;
    unordered_map<string, int> bus_routes;
    vector<pair<string, double> > max_path(3, (make_pair("what", -1)));
    int tram_max = 0;
    int troll_max = 0;
    int bus_max = 0;
    string tram_max_route;
    string troll_max_route;
    string bus_max_route;
    const string TRAM = "Трамвай";
    const string TROLL = "Троллейбус";
    const string BUS = "Автобус";
    int street_max = 0;
    string street;
    for (xml_node stat = dataset.first_child(); stat; stat = stat.next_sibling()) {
        string temp = stat.child_value("routes");
        string new_route;
        string temp_coord = stat.child_value("coordinates");
        Vertex temp_point;
        auto[x, y] = temp_point.point;
        string coordinate;
        for (size_t i = 0; i < temp_coord.size(); i++) {
            if (temp_coord[i] == ',') {
                coordinate.erase(0);
            } else if (temp_coord[i] != ',')
                coordinate += temp_coord[i];
            if (i == temp_coord.size() - 1) {
                coordinate.erase(0);
            }
        }

        for (size_t i = 0; i < temp.size(); i++) {
            if (temp[i] != ',' && temp[i] != '.') {
                new_route += temp[i];
            }
            if (temp[i] == ',' || temp[i] == '.' || i == temp.size() - 1) {
                if (stat.child_value("type_of_vehicle") == TRAM) {
                    tram_routes[new_route] += 1;
                    tram_graph[new_route].push_back(temp_point);
                    if (tram_routes[new_route] > tram_max) {
                        tram_max = tram_routes[new_route];
                        tram_max_route = new_route;
                    }
                } else if (stat.child_value("type_of_vehicle") == TROLL) {
                    troll_routes[new_route] += 1;
                    troll_graph[new_route].push_back(temp_point);
                    if (troll_routes[new_route] > troll_max) {
                        troll_max = troll_routes[new_route];
                        troll_max_route = new_route;
                    }
                } else if (stat.child_value("type_of_vehicle") == BUS) {
                    bus_routes[new_route] += 1;
                    bus_graph[new_route].push_back(temp_point);
                    if (bus_routes[new_route] > bus_max) {
                        bus_max = bus_routes[new_route];
                        bus_max_route = new_route;
                    }
                }
                new_route.erase(0);
            }
        }
    }
    cout << "Max tram way length: " << tram_max << ", route number " << tram_max_route << endl;
    cout << "Max troll way length: " << troll_max << ", route number " << troll_max_route << endl;
    cout << "Max bus way length: " << bus_max << ", route number " << bus_max_route << endl;
    return 0;
}
