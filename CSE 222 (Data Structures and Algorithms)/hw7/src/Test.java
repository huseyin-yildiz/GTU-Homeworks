import java.util.Random;
/**
 * The class for testing and measuring the performance of
 * the adding of the classes that has Testable interface
 * */
public class Test {
    private Testable<Integer> test;
    private final int[] array;

    private double addingTime;

    /** Returns the adding time of 100 extra duration in milliseconds.
     *
     * @return adding time in milliseconds
     */
    public double getAddingTime() {
        return addingTime;
    }

    /**
     * Constructor for testing that takes test object, an array and repetition
     * @param test  The testable object to test adding performance
     * @param array the array to add to the test object before measuring adding-extras time
     * @param repetition the repetition times
     */
    public Test(Testable<Integer> test, int[] array, int repetition) {
        this.test = test;
        this.array = array;
        addingTime = 0;

        try {
            for (int i=0; i<repetition; i++) {
                addingTime += adding();
                this.test = test.getClass().newInstance();
            }
            addingTime /= repetition;           // Average of the adding time
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    /**
     * produces and array and fills it randomly which is used for
     * adding operation with given size.
     * @param size takes size of the array to fill
     * */
    public static int[] get_random_array(int size){
        int[] array = new int[size+100];
        Random rand = new Random();
        for (int i=0; i<size; i++)
            array[i] = rand.nextInt(Integer.MAX_VALUE);
        return array;
    }

    /** Tests adding method with the given size in the constructor  */
    private double adding() {

        for(int i=0; i<array.length-100; i++)
            test.add(array[i]);

        return addExtras();
    }

    /**
     *  Adds extras to array and measures the running time
     * @return running time
     */
    private double addExtras(){
        long start = System.nanoTime();

        for(int i=array.length-100; i<array.length; i++)
            test.add(array[i]);

        long end = System.nanoTime();

        return (double)(end - start)/1000000.0;
    }


    @Override
    public String toString() {
        return
                " Item size = " + array.length +
                        "\n addingTime = " + addingTime + " ms";
    }

}
