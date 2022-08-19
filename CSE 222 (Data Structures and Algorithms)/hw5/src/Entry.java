import java.util.Map;

/** Contains key-value pairs for a hash table. */
public class Entry<K, V> implements Map.Entry<K, V> {

    /** The key */
    private K key;
    /** The value */
    private V value;

    /**
     * Creates a new key-value pair.
     * @param key The key
     * @param value The value
     */
    public Entry(K key, V value) {
        this.key = key;
        this.value = value;
    }

    /**
     * Retrieves the key.
     * @return The key
     */
    @Override
    public K getKey() {
        return key;
    }

    /**
     * Retrieves the value.
     * @return The value
     */
    @Override
    public V getValue() {
        return value;
    }

    /**
     * Sets the value.
     * @param val The new value
     * @return The old value
     */
    @Override
    public V setValue(V val) {
        V oldVal = value;
        value = val;
        return oldVal;
    }

    /**
     * Returns a string representation of the Entry.
     * @return The string in format "key=value"
     */
    public String toString() {
        return key + "=" + value;
    }


}
