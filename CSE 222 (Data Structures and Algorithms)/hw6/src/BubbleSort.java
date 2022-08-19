import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class BubbleSort {

    /**
     * Sort the List using the bubble sort algorithm.
     * @pre list objects before sorting.
     * @return list is sorted.
     * @param list The List to be sorted
     */

    public <T> void sort(List<T> list, Comparator<T> comparator){
        T[] array = (T[]) list.toArray();
        sort(array,comparator);
        list.clear();
        Collections.addAll(list,array);
    }

    /**
     * Sort the array using bubble sort algorithm.
     * @pre  table is unsorted objects.
     * post table is sorted.
     * @param table The array to be sorted
     */

    private <T>  void sort(T[] table, Comparator<T> comparator) {
        int pass = 1;
        boolean exchanges = false;
        do {
            exchanges = false;
            for (int i = 0; i < table.length - pass; i++) {
                if ( comparator.compare(table[i],(table[i + 1]) ) > 0) {
                    T temp = table[i];
                    table[i] = table[i + 1];
                    table[i + 1] = temp;
                    exchanges = true;
                }
            }
            pass++;
        } while (exchanges);

    }
}
