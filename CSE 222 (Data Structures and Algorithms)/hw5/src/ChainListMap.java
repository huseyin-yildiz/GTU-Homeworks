import javax.management.OperationsException;
import java.util.*;

public class ChainListMap<K,V> implements KWHashMap<K,V> {

    // Insert inner class Entry<K, V> here.
    // /**The table*/
    private LinkedList<Entry<K, V>>[] table;
    /**The number of keys*/
    private int numKeys;
    /**The capacity*/
    private static int CAPACITY = 101;
    /**The maximum load factor*/
    private static final double LOAD_THRESHOLD = 3.0;





    // Constructor
    public ChainListMap() {
        table = new LinkedList[CAPACITY];
    }

    public ChainListMap(int capacity) {
        CAPACITY = capacity;
        table = new LinkedList[CAPACITY];
    }



    /*
    * Returns the number of key-value mappings.
    */
   @Override
   public int size() {
       return numKeys;
   }

   @Override
   public boolean isEmpty() {
       return numKeys == 0;
   }



    /**
     * Method to rehash table.
     * Allocates a new hash table that is double the size and has an odd length.
     * Reinsert each table entry in the new hash table.
     */
    private void rehash() {
        LinkedList<Entry<K,V>>[] oldTable = table;
        table = new LinkedList[oldTable.length * 2 + 1];
        numKeys = 0;
        for (LinkedList<Entry<K, V>> list : oldTable) {
            if (list != null) {
                for (Entry<K,V> entry : list) {
                    put(entry.getKey(), entry.getValue());
                    numKeys++;
                }
            }
        }
    }



        /**Method get for class ChainListMap.
            @param key The key being sought
            @return The value associated with this key if found;otherwise, null */

        @Override
        public V get(Object key) {
            int index = key.hashCode() % table.length;
            if (index < 0)
                index += table.length;
            if (table[index] == null)
                return null;  // key is not in the table.

            // Search the list at table[index] to find the key.
            for (Entry<K, V> nextItem : table[index]) {
                if (nextItem.getKey().equals(key))
                    return nextItem.getValue();
            }
            // assert: key is not in the table.
            return null;
        }

  /**Method put for class ChainListMap.
       @param key The key of item being inserted
       @param value The value for this key
       @return The old value associated with this key if
                found; otherwise, null
   */
  @Override
  public V put(K key, V value) {
      int index = key.hashCode() % table.length;
      if (index < 0)
          index += table.length;
      if (table[index] == null) {
          // Create a new linked list at table[index].
          table[index] = new LinkedList<>();
      }

      // Search the list at table[index] to find the key.
      for (Entry<K, V> nextItem : table[index]) {
          // If the search is successful, replace the old value.
          if (nextItem.getKey().equals(key)) {
              // Replace value for this key.
              V oldVal = nextItem.getValue();
              nextItem.setValue(value);
              return oldVal;
          }
      }

      // assert: key is not in the table, add new item.
      table[index].addFirst(new Entry<>(key, value));
      numKeys++;
      if (numKeys > (LOAD_THRESHOLD * table.length))
          rehash();
      return null;
}

    /**Method remove for class ChainListMap.
     @param key The key to be removed
     @return The value associated with this key if
     found; otherwise, null
     */
    @Override
    public V remove(Object key) {
        int index = key.hashCode() % table.length;
        if(index < 0)
            index += table.length;
        if (table[index] == null)
            return null;

        for (Entry<K, V> nextItem : table[index]) {
            // If the search is successful, replace the old value.
            if (nextItem.getKey().equals(key)) {
                table[index].remove(nextItem);
                numKeys--;
                if(table[index].isEmpty())
                    table[index] = null;
                return nextItem.getValue();
            }
        }
        return null;
    }

}

