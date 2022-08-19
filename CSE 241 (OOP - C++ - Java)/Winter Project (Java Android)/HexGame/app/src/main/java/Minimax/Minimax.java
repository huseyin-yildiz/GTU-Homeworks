package Minimax;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import HexEngine.Hex;
import HexEngine.Location;

public class Minimax {

    private Hex hex;
    private Vertex left,right,up,down;
    private int deepth = 2;
    private  int stepLimit;
    Vector<Location> freeCells;

    public Minimax(Hex hex){                                                // constructor
        this.hex = hex;
        stepLimit = hex.getStep() + deepth;
    }

    public int getScoreOfUser2() throws Exception {                             // returns current score of the user 2

        int score = shortestPathOfUsr1() - shortestPathOfUsr2();
        return score;
    }


    private int shortestPathOfUsr2() throws Exception {                                 // returns the shoretest path Size for user2
        Graph graph = getGraph(Hex.CellState.USER2);
        DijkstraAlgorithm da = new DijkstraAlgorithm(graph);
        da.execute(left);
        LinkedList<Vertex> path = da.getPath(right);
        return getWeight(path,graph);
    }

    private int shortestPathOfUsr1() throws Exception {                                          // returns the shoretest path Size for user1
        Graph graph = getGraph(Hex.CellState.USER1);
        DijkstraAlgorithm da = new DijkstraAlgorithm(graph);
        da.execute(up);
        LinkedList<Vertex> path = da.getPath(down);
        return getWeight(path,graph);
    }

    private int getWeight(LinkedList<Vertex> path,Graph graph){                                     // gets the weight of the path
        Iterator<Vertex> it =  path.iterator();
        Vertex old = null;
        if(it.hasNext())
            old = it.next();
        int weight = 0;
        Vertex dest = it.next();
        while(it.hasNext())
        {

            Iterator<Edge> edges = graph.getEdges().iterator();
            while (edges.hasNext())
            {
                Edge edge = edges.next();
                if( edge.getSource().equals(old) && edge.getDestination().equals(dest) ) {
                    weight += edge.getWeight();
                    old = edge.getDestination();
                    dest = it.next();
                    break;
                }
            }
        }
        return weight;
    }

    private Graph getGraph(Hex.CellState userSign) throws Exception {                                               // returns the graph for a users cells
        Vertex[][] vertices = new Vertex[hex.getBoardSize()][hex.getBoardSize()];
        List<Edge> edges = new ArrayList<>();
        List<Vertex> verList = new ArrayList<>();
        left = new Vertex("left",new Location(-1,-1), Hex.CellState.NOPE);
        verList.add(left);
        right = new Vertex("right",new Location(-1,-1), Hex.CellState.NOPE);                                // setting border nodes
        verList.add(right);
        up = new Vertex("up",new Location(-1,-1), Hex.CellState.NOPE);
        verList.add(up);
        down = new Vertex("bottom",new Location(-1,-1), Hex.CellState.NOPE);
        verList.add(down);


        for(int i=0; i<hex.getBoardSize(); i++)
            for(int j=0; j<hex.getBoardSize(); j++) {
                Location location = new Location(i, j);
                Vertex vertex = new Vertex(Integer.toString(i * hex.getBoardSize() + j), location, hex.getCell(i, j));
                vertices[i][j] = vertex;
                verList.add(vertex);

                if(j==0)
                {
                    int weight = 1;
                    if(vertex.getCell() == userSign)
                        weight= 0;
                    edges.add(new Edge((Integer.toString(i*hex.getBoardSize()+j)+"left"),left,vertex,weight));                                  // setting edges of borders
                }

                else if(j==hex.getBoardSize()-1)
                    edges.add(new Edge((Integer.toString(i*hex.getBoardSize()+j)+"right"),vertex,right,0));

                if(i==0) {
                    int weight = 1;
                    if(vertex.getCell() == userSign)
                        weight= 0;
                    edges.add(new Edge((Integer.toString(i * hex.getBoardSize() + j) + "up"), up, vertex, weight));
                }
                else if(i==hex.getBoardSize()-1)
                    edges.add(new Edge((Integer.toString(i*hex.getBoardSize()+j)+"down"),vertex,down,0));

            }


        for(int i=0; i<hex.getBoardSize(); i++)
            for(int j=0; j<hex.getBoardSize(); j++) {
                Edge edge;
                for(Location loc : hex.findConnections(new Location(i,j)))
                {
                    Hex.CellState source = hex.getCell(i,j);
                    Hex.CellState dest = hex.getCell(loc);
                    int weight;
                    if(dest == Hex.CellState.DOT && source == Hex.CellState.DOT)                                        // sets the weights of edges
                        weight = 1;
                    else if(source == Hex.CellState.DOT && dest == userSign )
                        weight = 0;
                    else if(source == userSign && dest == Hex.CellState.DOT)
                        weight = 1;
                    else if(dest == userSign && source == userSign)
                        weight = 0;
                    else
                        continue;

                    edge = new Edge(Integer.toString(2*i*hex.getBoardSize()+j), vertices[i][j], vertices[loc.get_x()][loc.get_y()], weight );
                    edges.add(edge);
                }

            }

            return new Graph(verList,edges);
    }

    public Location bestLocation(Hex hex) throws Exception {                                            // tries to find best location for the user computer
       int max = -100000;
       Location bestLocation = null;
        if(hex.getPlayerNow().equals("Computer"))                // if its computer
        {
            List<Location> locations = new ArrayList<>( hex.getFreeCells() ) ;
            Collections.shuffle( locations ) ;

                for(Location location: locations)
                {
                    if(hex.getCell(location) == Hex.CellState.DOT){
                        Hex state = (Hex) hex.clone();
                        state.setSave(false);
                        state.play(location);
                        int val = min(state);
                        if(val > max) {
                            max = val;
                            bestLocation = location;
                        }
                    }
                }
            return bestLocation;
        }
        throw new Exception("This is not computers turn");
    }


    private int max(Hex hex) throws Exception {                                     // returns maximum score of the given state
        int max = -100000;

        if (hex.getStep() == stepLimit) {
        //    this.hex = hex;
            int score = getScoreOfUser2();
            return score;
        }
        List<Location> locations = new ArrayList<>( hex.getFreeCells() ) ;
        Collections.shuffle( locations ) ;

        for(Location location: locations)
        {
                if(hex.getCell(location) == Hex.CellState.DOT)
                {
                    Hex state = (Hex) hex.clone();
                    state.setSave(false);
                    state.play(location);
                    int val = min(state);
                    if(val > max)
                        max = val;
                }
            }
        return max;

    }


    private int min(Hex hex) throws Exception {                                                     // returns minimum score of the given state
        int min = 100000;

        if(hex.getStep() == stepLimit){
        //    this.hex = hex;
            int score = getScoreOfUser2();
            return score;
        }
        List<Location> locations = new ArrayList<>( hex.getFreeCells() ) ;
        Collections.shuffle( locations ) ;

        for(Location location: locations)
        {
                if(hex.getCell(location) == Hex.CellState.DOT)
                {
                    Hex state = (Hex) hex.clone();
                    state.setSave(false);
                    state.play(location);
                    int val = max(state);
                    if(val < min)
                        min = val;
                }
        }
        return min;
    }



}
