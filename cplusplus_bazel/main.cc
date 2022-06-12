#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "load_input.h"

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);

  if (argc < 3) {
    std::cout << "Usage: main.exe [input-file-name] [output-file-name]" << std::endl;
    return 0;
  }

  std::string input_file_name = argv[1];
  std::string output_file_name = argv[2];

  Graph graph;
  const Vertex* source;
  const Vertex* dest;
  auto load_result = LoadInput(input_file_name, graph, source, dest);
  if (!load_result.ok()) {
    LOG(ERROR) << load_result;
  }

  return 0;
}