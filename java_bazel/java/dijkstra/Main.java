package dijkstra;

import com.google.common.base.Preconditions;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Main {
  public static void main(String[] argv) {
    if (argv.length < 2) {
      System.out.println("Usage: java dijkstra.Main <input-file-name> <output-file-name>");
      return;
    }

    Graph.Builder graphBuilder = Graph.builder();
    String source = "";
    String dest = "";
    String inputFileName = argv[0];
    String outputFileName = argv[1];

    try {
      File file = new File(inputFileName);
      FileReader fileReader = new FileReader(file);
      BufferedReader fin = new BufferedReader(fileReader);
      String line;

      line = fin.readLine();
      int n = Integer.parseInt(line);
      for (int i = 0; i < n; i++) {
        line = fin.readLine().strip();
        graphBuilder.addVertex(line);
      }

      line = fin.readLine();
      int m = Integer.parseInt(line);
      for (int i = 0; i < m; i++) {
        line = fin.readLine();
        String[] comps = line.split(" ");
        Preconditions.checkArgument(comps.length >= 3);
        String u = comps[0].strip();
        String v = comps[1].strip();
        double w = Double.parseDouble(comps[2].strip());
        Preconditions.checkArgument(w >= 0);
        graphBuilder.addEdge(u, v, w);
        graphBuilder.addEdge(v, u, w);
      }

      line = fin.readLine().strip();
      String[] comps = line.split(" ");
      Preconditions.checkArgument(comps.length >= 2);
      source = comps[0].strip();
      dest = comps[1].strip();

      fileReader.close();
    } catch (IOException e) {
      e.printStackTrace();
      return;
    }

    Graph graph = graphBuilder.build();
    Preconditions.checkArgument(!source.isEmpty());
    Preconditions.checkArgument(!dest.isEmpty());
    Preconditions.checkArgument(graph.vertices().contains(source));
    Preconditions.checkArgument(graph.vertices().contains(dest));

    Dijkstra.Result result = Dijkstra.run(graphBuilder.build(), source);

    try {
      BufferedWriter fout = new BufferedWriter(new FileWriter(outputFileName));

      if (result.distance().containsKey(dest)) {
        fout.write(String.format("%f\n", result.distance().get(dest)));
        ArrayList<String> path = new ArrayList<>();
        String current = dest;
        while (current != null && !current.equals("")) {
          path.add(current);
          current = result.prev().get(current);
        }
        for (int i = path.size() - 1; i >= 0; i--) {
          fout.write(path.get(i));
          fout.write("\n");
        }
      } else {
        fout.write("-1\n");
      }

      fout.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
