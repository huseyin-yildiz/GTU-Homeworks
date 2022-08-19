import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class MergeSort {


    /**
     * Sort the List using the merge sort algorithm.
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
     * Sort the array using the merge sort algorithm.
     * @pre table contains Comparable objects.
     * @post table is sorted.
     * @param table The array to be sorted
     */
    private <T>  void sort(T[] table, Comparator<T> comparator) {
        if (table.length > 1) {
            int halfSize = table.length / 2;
            T[] leftTable = (T[]) new Comparable[halfSize];
            T[] rightTable =
                    (T[]) new Comparable[table.length - halfSize];
            System.arraycopy(table, 0, leftTable, 0, halfSize);
            System.arraycopy(table, halfSize, rightTable, 0,
                    table.length - halfSize);
            sort(leftTable,comparator);
            sort(rightTable,comparator);
            merge(table, leftTable, rightTable,comparator);
        }
    }

    /**
     * Merge two sequences.
     * @pre leftSequence and rightSequence are sorted.
     * @post outputSequence is the merged result and is sorted.
     * @param outputSequence The destination
     * @param leftSequence The left input
     * @param rightSequence The right input
     */
    private static <T>  void merge(T[] outputSequence, T[] leftSequence, T[] rightSequence, Comparator<T> comparator) {
        int i = 0;
        int j = 0;
        int k = 0;

        while (i < leftSequence.length && j < rightSequence.length) {

            if (comparator.compare(leftSequence[i],(rightSequence[j])) < 0) {
                outputSequence[k++] = leftSequence[i++];
            } else {
                outputSequence[k++] = rightSequence[j++];
            }
        }
        while (i < leftSequence.length) {
            outputSequence[k++] = leftSequence[i++];
        }
        while (j < rightSequence.length) {
            outputSequence[k++] = rightSequence[j++];
        }
    }
}