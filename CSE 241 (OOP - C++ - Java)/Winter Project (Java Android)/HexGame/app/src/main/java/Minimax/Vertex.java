package Minimax;

import HexEngine.Hex;
import HexEngine.Location;

public class Vertex {                                           // The class for Vertexes
    private String id;
    private Location location;
    private Hex.CellState cellState;


    public Vertex(String id, Location location, Hex.CellState cell) {                   // constructor
        this.id = id;
        this.cellState = cell;
        this.location = location;
    }
    public String getId() {
        return id;
    }
    public Hex.CellState getCell() {
        return cellState;
    }
                                                                                                            // getters
    public Location getLocation() {
        return location;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((id == null) ? 0 : id.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)                                                                    // equals overriding for determining other given object is same or not
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Vertex other = (Vertex) obj;
        if (id == null) {
            if (other.id != null)
                return false;
        } else if (!id.equals(other.id))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return id;
    }

}