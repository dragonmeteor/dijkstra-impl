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

absl::optional<double> ParseDouble(const std::string& line) {
  std::istringstream iss(line);
  double output;
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
      return absl::InvalidArgumentError(absl::StrFormat("Cannot parse the %d(th) vertex.", i + 1));
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
      return absl::InvalidArgumentError(absl::StrFormat("Cannot parse the %d(th) edge.", i + 1));
    }
    std::vector<std::string> comps = absl::StrSplit(optional_line.value(), ' ');
    if (comps.size() < 3) {
      return absl::InvalidArgumentError(
          absl::StrFormat("Edge #%d: Line does not contain at least 3 words.", i + 1));
    }

    absl::string_view source_name = absl::StripAsciiWhitespace(comps[0]);
    auto optional_source = graph.GetVertex(source_name);
    if (!optional_source.has_value()) {
      return absl::InvalidArgumentError(
          absl::StrFormat("Edge #%d: Vertex '%s' does not exist.", i + 1, source_name));
    }

    absl::string_view dest_name = absl::StripLeadingAsciiWhitespace(comps[1]);
    auto optional_dest = graph.GetVertex(dest_name);
    if (!optional_dest.has_value()) {
      return absl::InvalidArgumentError(
          absl::StrFormat("Edge #%d: Vertex '%s' does not exist.", i + 1, dest_name));
    }

    auto optional_weight = ParseDouble(comps[2]);
    if (!optional_weight.has_value()) {
      return absl::InvalidArgumentError(absl::StrFormat("Edge #%d: Cannot parse weight.", i + 1));
    }
    if (optional_weight.value() < 0) {
      return absl::InvalidArgumentError(
          absl::StrFormat("Edge #%d: Negative weight (%f)", i + 1, optional_weight.value()));
    }
    auto add_edge_result =
        graph.AddEdge(optional_source.value(), optional_dest.value(), optional_weight.value());
    if (!add_edge_result.ok()) {
      return absl::InvalidArgumentError(absl::StrFormat("Edge #%d: Cannot insert.", i + 1));
    }
    add_edge_result =
        graph.AddEdge(optional_dest.value(), optional_source.value(), optional_weight.value());
    if (!add_edge_result.ok()) {
      return absl::InvalidArgumentError(absl::StrFormat("Edge #%d: Cannot insert.", i + 1));
    }
  }

  optional_line = ReadLine(fin);
  if (!optional_line.has_value()) {
    return absl::InvalidArgumentError("Cannot read the last line.");
  }
  std::vector<std::string> comps = absl::StrSplit(optional_line.value(), ' ');
  if (comps.size() < 2) {
    return absl::InvalidArgumentError("The last line does not contain at least 2 words");
  }

  absl::string_view source_name = absl::StripAsciiWhitespace(comps[0]);
  auto optional_source = graph.GetVertex(source_name);
  if (!optional_source.has_value()) {
    return absl::InvalidArgumentError(absl::StrFormat("Vertex '%s' does not exist.", source_name));
  }
  source = optional_source.value();

  absl::string_view dest_name = absl::StripLeadingAsciiWhitespace(comps[1]);
  auto optional_dest = graph.GetVertex(dest_name);
  if (!optional_dest.has_value()) {
    return absl::InvalidArgumentError(absl::StrFormat("Vertex '%s' does not exist.", dest_name));
  }
  dest = optional_dest.value();

  fin.close();
  return absl::OkStatus();
}