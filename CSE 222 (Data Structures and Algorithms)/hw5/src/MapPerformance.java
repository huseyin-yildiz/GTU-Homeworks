import java.time.Duration;
import java.util.Random;
/**
 * The class for testing and measuring the performance of the HashMaps
 * */
public class MapPerformance {
    private KWHashMap test;
    private final int[] array;
    private final int size;
    private final int upperBound;

    private double addingTime;
    private double removingTime;
    private double accessingExistingTime;
    private double accessingNonExistingTime;

    /** Returns the adding function time duration in milliseconds. */
    public double getAddingTime() {
        return addingTime;
    }

    /** Returns the removing function time duration in milliseconds. */
    public double getRemovingTime() {
        return removingTime;
    }

    /** Returns the Accessing-Existing operations time duration in milliseconds. */
    public double getAccessingExistingTime() {
        return accessingExistingTime;
    }

    /** Returns the Accessing-NonExisting operations time duration in milliseconds. */
    public double getAccessingNonExistingTime() {
        return accessingNonExistingTime;
    }

    /**
     * Constructs the instance with the given parrameters
     * @param map The HashMap
     * @param size The size of the data to add-remove etc..
     * */
    public MapPerformance(KWHashMap map, int size, int dataUpperBound) {
        this.test = map;
        array = new int[size];
        this.size = size;
        this.upperBound = dataUpperBound;




        try {
            fill_array();
            addingTime = adding();
            accessingExistingTime = accessingExisting();
            accessingNonExistingTime = accessingNonExisting();
            removingTime = removing();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    /**
     * Fills the array randomly which is used for Hashmap operations.
     * */
    private void fill_array(){
        Random rand = new Random();
        for (int i=0; i<size; i++)
            array[i] = rand.nextInt(upperBound);
    }

    /** Tests adding method of the Hashmap with the given size in the constructor  */
    private double adding() {
        long start = System.nanoTime();

        for(int i=0; i<size; i++)
            test.put(array[i],array[i]);

        long end = System.nanoTime();

        return (double)(end - start)/1000000.0;
    }

    /** Tests removing method of the Hashmap with the given size in the constructor  */
    private double removing(){
        long start = System.nanoTime();

        for(int i=0; i<size; i++)
            test.remove(array[i]);

        long end = System.nanoTime();
        return (double)(end - start)/1000000.0;
    }

    /**
     *  Tests get method of the Hashmap with the given size in the constructor by using data in the array that is
     *  added before
     * */
    private double accessingExisting() throws Exception {
        long start = System.nanoTime();

        for(int i=0; i<size; i++)
            if( test.get(array[i]) == null )
                throw new Exception("The item " + array[i] + "can not be found or accessed");

        long end = System.nanoTime();
        return (double)(end - start)/1000000.0;
    }

    /**
     *  Tests get method of the Hashmap with the given size in the constructor without using data in the array that is
     *  added before
     * */
    private double accessingNonExisting() throws Exception {
        long start = System.nanoTime();

        for(int i=0; i<size; i++)
            if( test.get(array[i]*-1) != null )
                throw new Exception("The item " + array[i] + "found in the map but should not be in it");

        long end = System.nanoTime();
        return (double)(end - start)/1000000.0;
    }

    @Override
    public String toString() {
        return
                " Item size = " + size +
                "\n upperBound = " + upperBound +
                "\n addingTime = " + addingTime + " ms"+
                "\n removingTime = " + removingTime + " ms"+
                "\n accessingExistingTime = " + accessingExistingTime +" ms"+
                "\n accessingNonExistingTime = " + accessingNonExistingTime +" ms";
    }

}
