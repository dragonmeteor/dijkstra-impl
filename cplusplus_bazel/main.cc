#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"

class Vertex {
public:
    explicit Vertex(absl::string_view name);
    Vertex(const Vertex& other) = delete;
    Vertex& operator=(const Vertex& other) = delete;

    absl::string_view name() const;

private:
    std::string name_;
};

Vertex::Vertex(absl::string_view name): name_(name) {
    // NO-OP
}

absl::string_view Vertex::name() const {
    return name_;
}

class Edge {
public:
    explicit Edge(const Vertex* source, const Vertex* dest, double weight);
    Edge(const Edge& edge) = delete;
    Edge& operator=(const Edge& other) = delete;

    const Vertex* source() const;
    const Vertex* dest() const;
    double weight() const;

private:
    const Vertex* source_;
    const Vertex* dest_;
    double weight_;
};

Edge::Edge(const Vertex* source, const Vertex* dest, double weight): source_(source), dest_(dest), weight_(weight) {
    // NO-OP
}

const Vertex* Edge::source() const {
    return source_;
}

const Vertex* Edge::dest() const {
    return dest_;
}

double Edge::weight() const {
    return weight_;
}

class Graph {
public:
    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete;

private:
    
};

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: main.exe [input-file-name]" << std::endl;
        return 0;
    }

    std::string input_file_name = argv[1];
    std::cout << "Input file: " << input_file_name << std::endl;
    return 0;
}