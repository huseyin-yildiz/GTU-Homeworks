import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class ShellSort {

    /**
     * Sort the List using the Shell sort algorithm.
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
     * Sort the table using Shell sort algorithm.
     * @pre  table contains unsorted objects.
     * @post table is sorted.
     * @param table The array to be sorted
     */

    private <T>  void sort(T[] table, Comparator<T> comparator) {

        int gap = table.length / 2;
        while (gap > 0) {
            for (int nextPos = gap; nextPos < table.length;
                 nextPos++) {
                insert(table, nextPos, gap, comparator);
            }
            if (gap == 2) {
                gap = 1;
            } else {
                gap = (int) (gap / 2.2);
            }
        }
    }

    /**
     * Inserts element at nextPos where it belongs in array.
     * @pre  Elements through nextPos - gap in subarray are sorted.
     * @post Elements through nextPos in subarray are sorted.
     * @param table The array being sorted
     * @param nextPos The position of element to insert
     * @param gap The gap between elements in the subarray
     */
    private static <T>  void insert(T[] table, int nextPos, int gap, Comparator<T>comparator) {
        T nextVal = table[nextPos];
        while ((nextPos > gap - 1)
                && (comparator.compare( nextVal,(table[nextPos - gap])) < 0)) {
            table[nextPos] = table[nextPos - gap];
            nextPos -= gap;
        }
        table[nextPos] = nextVal;
    }
}

