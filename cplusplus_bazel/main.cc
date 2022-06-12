#include <gflags/gflags.h>
#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "load_input.h"
#include "dijkstra.h"

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  if (argc < 3) {
    std::cout << "Usage: main.exe [input-file-name] [output-file-name]" << std::endl;
    return 0;
  }

  std::string input_file_name = argv[1];
  std::string output_file_name = argv[2];
  LOG(INFO) << "Input file name: " << input_file_name;
  LOG(INFO) << "Output file name: " << output_file_name;

  Graph graph;
  const Vertex* source;
  const Vertex* dest;
  auto load_result = LoadInput(input_file_name, graph, source, dest);
  if (!load_result.ok()) {
    LOG(ERROR) << load_result;
    return 0;
  }
  LOG(INFO) << "There are " << graph.num_vertices() << " vertices.";
  LOG(INFO) << "There are " << graph.num_edges() << " edges";
  
  DijkstraResult dijkstra_result;
  auto dijkstra_status = RunDijkstra(graph, source, dijkstra_result);
  if (!dijkstra_status.ok()) {
    LOG(ERROR) << dijkstra_status;
    return 0;
  }

  std::ofstream fout(output_file_name.c_str(), std::ios::out);
  if (!fout.is_open()) {
    LOG(ERROR) << "Cannot open '" << output_file_name << "'.";
    return 0; 
  }
  Path path;
  auto get_path_status = GetPathFromSource(dijkstra_result, dest, path);
  if (!get_path_status.ok()) {
    fout << "-1" << std::endl;
    LOG(INFO) << "-1";
  } else {
    fout << path.length << std::endl;
    LOG(INFO) << path.length;
    for (auto v : path.vertices) {
      fout << v->name() << std::endl;
      LOG(INFO) << v->name();
    } 
  }
  fout.close();

  return 0;
}