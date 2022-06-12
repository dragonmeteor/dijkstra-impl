#ifndef __LOAD_INPUT_H__
#define __LOAD_INPUT_H__

#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "graph.h"

absl::Status LoadInput(const std::string& file_name, Graph& graph, const Vertex*& source,
                       const Vertex*& dest);

#endif