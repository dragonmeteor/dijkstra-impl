#include "load_input.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/types/optional.h"


absl::optional<std::string> ReadLine(std::ifstream& fin) {
  std::string line;
  std::getline(fin, line);
  if (!fin) {
    return absl::nullopt;
  }
  return line;
}

absl::optional<int> ParseInt(const std::string& line) {
  std::istringstream iss(line);
  int output;
  if (!(iss >> output)) {
    return absl::nullopt;
  } else {
    return output;
  }
}

absl::Status LoadInput(const std::string& file_name, Graph& graph, const Vertex*& source,
                       const Vertex*& dest) {
  std::ifstream fin(file_name.c_str(), std::ios::in);
  if (!fin.is_open()) {
    return absl::InvalidArgumentError(absl::StrCat("Cannot open '", file_name, "'!"));
  }

  // Read the number of vertices.
  auto optional_line = ReadLine(fin);
  if (!optional_line.has_value()) {
    return absl::InvalidArgumentError("Cannot read the first line.");
  }
  auto optional_n = ParseInt(optional_line.value());
  if (!optional_n.has_value()) {
    return absl::InvalidArgumentError("Cannot parse vertex count.");
  }
  int n = optional_n.value();

  // Read the vertex names.
  for (int i = 0; i < n; i++) {
    optional_line = ReadLine(fin);
    if (!optional_line.has_value()) {
      return absl::InvalidArgumentError(absl::StrFormat("Cannot parse the %d(th) vertex.", i+1)));
    }
    auto add_result = graph.AddVertex(absl::StripAsciiWhitespace(optional_line.value()));
    if (!add_result.ok()) {
      return add_result;
    }
  }

  // Read the number of edges
  optional_line = ReadLine(fin);
  if (!optional_line.has_value()) {
    return absl::InvalidArgumentError("Cannot read the line containing the edge count.");
  }
  auto optional_m = ParseInt(optional_line.value());
  if (!optional_m.has_value()) {
    return absl::InvalidArgumentError("Cannot parse edge count.");
  }
  int m = optional_m.value();

  // Read the edges.
  for (int i = 0; i < m; i++) {
    optional_line = ReadLine(fin);
    if (!optional_line.has_value()) {
      return absl::InvalidArgumentError(absl::StrFormat("Cannot parse the %d(th) edge.", i+1));      
    }
    std::vector<std::string> comps = absl::StrSplit(optional_line.value(), ' ');
    if (comps.size() < 3) {
      return absl::InvalidArgumentError(absl::StrFormat("Edge #%d: Line does not contain at least 3 words.", i+1));
    }
    
    absl::string_view source_name = absl::StripAsciiWhitespace(comps[0]);
    auto optional_source = graph.GetVertex(source_name);
    if (!optional_source.has_value()) {
      return absl::InvalidArgumentError(absl::StrFormat("Edge #%d: Vertex '%s' does not exist.", i+1, source_name));
    }

    absl::string_view dest_name = absl::StripLeadingAsciiWhitespace(comps[1]);    
  }

  fin.close();
  return absl::OkStatus();
}