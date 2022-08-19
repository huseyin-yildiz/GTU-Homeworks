package Minimax;


import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import HexEngine.Hex;
import HexEngine.Location;

public class GraphTest {

    public void test(){

        Vertex vertex = new Vertex("1",new Location(1,2), Hex.CellState.DOT);
        Vertex vertex2 = new Vertex("2",new Location(5,4), Hex.CellState.USER2);
        Vertex vertex3 = new Vertex("3",new Location(7,4), Hex.CellState.USER1);
        List<Vertex> vertices = new ArrayList<>();

        List<Edge> edges = new ArrayList<>();

        edges.add( new Edge("3",vertex,vertex2,1) );
        edges.add( new Edge("4",vertex2,vertex3,2) );
        edges.add( new Edge("5",vertex,vertex3, 3 ) );

        Graph graf = new Graph(vertices,edges);

        DijkstraAlgorithm da = new DijkstraAlgorithm(graf);
        da.execute(vertex);
        LinkedList<Vertex> path = da.getPath(vertex3);

        System.out.println(path.size());

    }


}


