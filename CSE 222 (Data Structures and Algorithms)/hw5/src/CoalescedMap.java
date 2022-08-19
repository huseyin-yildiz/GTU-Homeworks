import java.util.*;

/**
 * Hash table implementation using open addressing with quadratic probing and coalesced method.
 */
public class CoalescedMap<K, V> implements KWHashMap<K, V> {

    private Node[] table;
    private static int START_CAPACITY = 101;
    private double LOAD_THRESHOLD = 0.75;
    private int numKeys;

    /**
     * inner class for to hold the entry with next item
     */
    private static class Node<K,V>{
        private Entry entry;
        private Integer next;

        /** constructor method for Node class */
        public Node(K key, V value){
            entry = new Entry(key,value);
        }

        /** returns the key */
        public K getKey() {
            return (K) entry.getKey();
        }

        /** returns the value */
        public V getValue() {
            return (V) entry.getValue();
        }

        /** sets the the value by taking the paramater value */
        public void setValue(V value) {
            this.entry.setValue(value);
        }

        /** returns the next item index */
        public Integer getNext() {
            return next;
        }

        /** sets the index of the next item */
        public void setNext(int next) {
            this.next = next;
        }
    }

    /** The Constructor of the CoalescedMap class */
    public CoalescedMap() {
        table = new Node[START_CAPACITY];
    }

    /** The Constructor of the CoalescedMap class with start capacity */
    public CoalescedMap(int start_capacity) {
        START_CAPACITY = start_capacity;
        table = new Node[START_CAPACITY];
    }


    /** Returns true if empty */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }

    /**
     * Finds either the target key or the first empty slot in the
     * search the item using quadratic probing.
     * @param key The key of the target object
     * @return The position of the target or the first empty slot if
     *         the target is not in the table.
     */
    private int find(Object key) {

        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length; // Make it positive.
        }

        Integer indexFirst = null;
        Integer indexLast = null;

        int i=1;
        while ( (table[index] != null)    && (!key.equals(table[index].getKey())))
        {
                if(indexFirst == null)
                    indexFirst = index;
                if( table[index].next != null ) {
                        indexLast = index;
                    index = table[index].next;
                    i = (int) Math.sqrt(indexFirst - index);
                }
                else {
                    if(indexFirst == null)
                        indexFirst = index;
                    indexLast = index;
                    index = (indexFirst + i*i) % table.length;
                    if(index < 0)
                        index += table.length;

                   while ( table[index] != null )
                   {
                       i++;
                       index = (indexFirst + i*i) % table.length;
                       if(index < 0)
                           index += table.length;
                   }
                   table[indexLast].setNext(index);
                   return index;
                }
        }
        return index;
    }

    /**
     * Method get for class CoalescedMap.
     * @param key The key being sought
     * @return the value associated with this key if found;
     *         otherwise, null
     */
    @Override
    public V get(Object key) {
        // Find the first table element that is empty
        // or the table element that contains the key.
        int index = find(key);

        // If the search is successful, return the value.
        if (table[index] != null) {
            return (V) table[index].getValue();
        } else {
            return null; // key not found.
        }
    }

    /**
     * Method put for class CoalescedMap.
     * @param key The key of item being inserted
     * @param value The value for this key
     * @return Old value associated with this key if found;
     *         otherwise, null
     */
    @Override
    public V put(K key, V value) {
        // Find the first table element that is empty
        // or the table element that contains the key.
        int index = find(key);

        // If an empty element was found, insert new entry.
        if (table[index] == null) {
            table[index] = new Node<K, V>(key, value);
            numKeys++;
            // Check whether rehash is needed.
            double loadFactor = (double) numKeys / (double) table.length;
            if (loadFactor > LOAD_THRESHOLD) {
                rehash();
            }
            return null;
        }

        // assert: table element that contains the key was found.
        // Replace value for this key.
        V oldVal = (V) table[index].getValue();
        table[index].setValue(value);
        return oldVal;
    }

    /**Method remove for class CoalescedMap.
     @param key The key to be removed
     @return The value associated with this key if
     found; otherwise, null
     */
    @Override
    public V remove(Object key) {
        int index = find(key);
        if(table[index] != null)
        {
            V oldVal = (V) table[index].getValue();

            if(table[index].next != null) {
                int nextIndex = table[index].next;
                table[index] = table[nextIndex];
                table[nextIndex] = null;
                return oldVal;
            }

            table[index] = null;
            numKeys--;
            return oldVal;
        }
        return null;
    }

    @Override
    public int size() {
        return numKeys;
    }

    /**
     * Expands table size when loadFactor exceeds LOAD_THRESHOLD
     */
    private void rehash() {
        // Save a reference to oldTable.
        Node<K, V>[] oldTable = table;
        // Double capacity of this table.
        table = new Node[2 * oldTable.length + 1];

        // Reinsert all items in oldTable into expanded table.
        numKeys = 0;
        for (int i = 0; i < oldTable.length; i++) {
            if ( oldTable[i] != null) {
                // Insert entry in expanded table
                put( oldTable[i].getKey(), oldTable[i].getValue() );
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i=0; i<table.length; i++)
        {
                sb.append(i);
                sb.append("  ");
                if(table[i] != null)
                    sb.append(table[i].getKey());
                else
                    sb.append("NULL");
                sb.append("  ");
                if(table[i] != null)
                    sb.append(table[i].getValue());
                else
                    sb.append("NULL");
                sb.append("  ");
                if(table[i] != null)
                    sb.append(table[i].getNext());
                else
                    sb.append("NULL");
                sb.append("\n");
        }
        return sb.toString();
    }

    public static void main(String args[]){

        CoalescedMap<Integer, Integer> test = new CoalescedMap<>(10);
        test.put(3,3);
        test.put(12,12);
        test.put(13,13);
        test.put(25,25);
        test.put(23,23);
        test.put(51,51);
        test.put(42,42);
        test.remove(13);
        System.out.println(test.toString());

        System.out.println(test.get(23));
        System.out.println(test.get(42));
        System.out.println(test.get(13));
        System.out.println(test.get(35));


        CoalescedMap<Integer, Integer> test2 = new CoalescedMap<>(11);

        for (int i=0; i<100; i++)
        {
            Random random = new Random();
            int num = random.nextInt(10000);
            test2.put(num, num);
        }
        System.out.println(test2);


        // large size test

        CoalescedMap<Integer, Integer> test3 = new CoalescedMap<>();

        for (int i=0; i<1000; i++)
        {
            Random random = new Random();
            int num = random.nextInt(100000);
            test3.put(num, num);
        }
        System.out.println(test3);

    }
}