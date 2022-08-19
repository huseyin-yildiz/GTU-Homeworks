import java.util.TreeSet;

public class ChainTreeMap<K extends Comparable<K>,V> implements KWHashMap<K,V>{


    // Insert inner class Entry<K, V> here.
    // /**The table*/
    private TreeSet<EntrySet<K, V>>[] table;
    /**The number of keys*/
    private int numKeys;
    /**The capacity*/
    private static int CAPACITY = 101;
    /**The maximum load factor*/
    private static final double LOAD_THRESHOLD = 3.0;

    /**
     * The inner class for the entry which is extended from Entry
     * */
    public class EntrySet<K extends Comparable,V> extends Entry<K,V> implements Comparable {

        /**
         * Creates a new key-value pair.
         *
         * @param key   The key
         * @param value The value
         */
        public EntrySet(K key, V value) {
            super(key, value);
        }


        @Override
        public int compareTo(Object o) {
            if(o instanceof EntrySet)
                return this.getKey().compareTo( ((EntrySet<K, V>)o).getKey()  );
            else
                throw new IllegalArgumentException();
        }
    }



    /** Constructor method */
    public ChainTreeMap() {
        table = new TreeSet[CAPACITY];
    }

    /** Constructor method with initial capacity */
    public ChainTreeMap(int capacity) {
        CAPACITY = capacity;
        table = new TreeSet[CAPACITY];
    }


    /*
     * Returns the number of key-value mappings.
     */
    @Override
    public int size() {
        return numKeys;
    }

    /** Returns if the map is empty or not */
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
        TreeSet<EntrySet<K,V>>[] oldTable = table;
        table = new TreeSet[oldTable.length * 2 + 1];
        numKeys = 0;
        for (TreeSet<EntrySet<K, V>> tree : oldTable) {
            if (tree != null) {
                for (EntrySet<K,V> entry : tree) {
                    put(entry.getKey(), entry.getValue());
                    numKeys++;
                }
            }
        }
    }



    /**Method get for class ChainTreeMap.
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
        for (EntrySet<K, V> nextItem : table[index]) {
            if (nextItem.getKey().equals(key))
                return nextItem.getValue();
        }
        // assert: key is not in the table.
        return null;
    }

    /**Method put for class ChainTreeMap.
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
            table[index] = new TreeSet<>();
        }

        // Search the list at table[index] to find the key.
        for (EntrySet<K, V> nextItem : table[index]) {
            // If the search is successful, replace the old value.
            if (nextItem.getKey().equals(key)) {
                // Replace value for this key.
                V oldVal = nextItem.getValue();
                nextItem.setValue(value);
                return oldVal;
            }
        }

        // assert: key is not in the table, add new item.
        table[index].add(new EntrySet<>(key, value));
        numKeys++;
        if (numKeys > (LOAD_THRESHOLD * table.length))
            rehash();
        return null;
    }

    /**Method remove for class ChainTreeMap.
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

        for (EntrySet<K, V> nextItem : table[index]) {
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


    public static void main(String[] args){
        ChainTreeMap<Integer,Integer> a = new ChainTreeMap<>();
        a.put(12,12);
        a.put(11,11);
        System.out.println(a.get(11));

        a.remove(11);

        System.out.println(a.get(11));

        System.out.println(a.get(12));



    }


}
