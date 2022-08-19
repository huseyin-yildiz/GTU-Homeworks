import java.util.HashMap;
import java.util.Iterator;

/**
 * The Hashmap class for the custom Hashmap iterator which is just extended from the Java HashMap class
 * */
public class MyHashMap<K,V> extends HashMap<K,V> {

    /** Method to get instance the custom iterator */
    public MyIterator<K> myIterator(){
        return new MyIterator<K>();
    }

    /** Method to get instance the custom iterator by starting the given element
     * @param element The element to start with iteration
     * */
    public MyIterator<K> myIterator(K element) throws Exception {
        return new MyIterator<K>(element);
    }

    /** The iterator class for Hashmap */
    public class MyIterator<K> {

        private K[] array;
        int index;

        /** the constructor of the custom iterator */
        public MyIterator() {
            array = (K[]) keySet().toArray();
            index = 0;
        }

        /** the private method to determine if the Hashmap is changed */
        private boolean isChanged() {
            return array.length != size();
        }

        /** the constructor of the custom iterator by starting iteration from the given key
         * @param key the key to start iteration
         * throws exception if the key is not in the hashmap
         * */
        public MyIterator(K key) throws Exception {
            this();
            for (int i = 0; i < array.length; i++) {
                if (array[i].equals(key)) {
                    index = i;
                    return;
                }
            }
            throw new Exception("The given element is not found");
        }

        /** returns if there is next item or not */
        public boolean hasNext() throws Exception {
            if (isChanged())
                throw new Exception("The map has changed. This can not be used.");
            return index + 1 < array.length;
        }

        /** returns if there is previous item or not */
        public boolean hasPrev() throws Exception {
            if (isChanged())
                throw new Exception("The map has changed. This can not be used.");
            return index - 1 < array.length && index -1 >= 0;
        }


        /** returns the next item
         * if the item last item then returns the first item
         * */
        public K next() throws Exception {
            if (isChanged())
                throw new Exception("The map has changed. This can not be used.");
            index = ++index % array.length;
            return array[index];
        }

        /** returns the previous item
         * if the item first item then returns the last item
         * */
        public K prev() throws Exception {
            if (isChanged())
                throw new Exception("The map has changed. This can not be used.");
            index = --index % array.length;
            return array[index];
        }

    }

}