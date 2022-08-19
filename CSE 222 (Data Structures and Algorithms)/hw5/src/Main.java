import java.util.Iterator;

public class Main {

    public static void main(String[] args){

        System.out.println("Coalesced Small Test");
        CoalescedMap<Integer,Integer> coaMap = new CoalescedMap(11);
        MapPerformance test1 = new MapPerformance(coaMap,20,1000);
        System.out.println(test1);

        System.out.println("\nChainTree Small Test");
        ChainTreeMap<Integer,Integer> treeMap = new ChainTreeMap<>(11);
        MapPerformance test2 = new MapPerformance(treeMap,20,1000);
        System.out.println(test2);

        System.out.println("\nChainList Small Test");
        ChainListMap<Integer,Integer> listMap = new ChainListMap<>(11);
        MapPerformance test3 = new MapPerformance(listMap,20,1000);
        System.out.println(test3);

        System.out.println("\nCoalesced Medium Test");
        coaMap = new CoalescedMap();
        test1 = new MapPerformance(coaMap,200,10000);
        System.out.println(test1);

        System.out.println("\nChainTree Medium Test");
        treeMap = new ChainTreeMap<>();
        test2 = new MapPerformance(treeMap,200,10000);
        System.out.println(test2);

        System.out.println("\nChainList Medium Test");
        listMap = new ChainListMap<>();
        test3 = new MapPerformance(listMap,200,10000);
        System.out.println(test3);



        System.out.println("\nCoalesced Large Test");
        coaMap = new CoalescedMap();
        test1 = new MapPerformance(coaMap,2000,100000);
        System.out.println(test1);

        System.out.println("\nChainTree Large Test");
        treeMap = new ChainTreeMap<>();
        test2 = new MapPerformance(treeMap,2000,100000);
        System.out.println(test2);

        System.out.println("\nChainList Large Test");
        listMap = new ChainListMap<>();
        test3 = new MapPerformance(listMap,2000,100000);
        System.out.println(test3);


        // some other test cases

        coaMap = new CoalescedMap<>();
        System.out.println("\n ============== CoalescedMap Some Other Tests ==============");
        testHashMap(coaMap);

        listMap = new ChainListMap<>();
        System.out.println("\n ============== ChainListMap Some Other Tests ==============");
        testHashMap(listMap);

        treeMap = new ChainTreeMap<>();
        System.out.println("\n ============== ChainTreeMap Some Other Tests ==============");
        testHashMap(treeMap);


        MyHashMap<Integer, Integer> hm = new MyHashMap<>();
        hm.put(12,12);
        hm.put(13,13);
        hm.put(45,45);

        try {

            MyHashMap.MyIterator it = hm.myIterator(13);

            while (it.hasNext())
            {
                System.out.println(it.next());
            }

            while (it.hasPrev())
            {
                System.out.println(it.prev());
            }

        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }



    }




    private static void testHashMap(KWHashMap hashmap){

        hashmap.put(1,142);
        hashmap.put(63,63);
        hashmap.put(79,79);

        hashmap.put(96,96);
        if(hashmap.get(96).equals(96))
            System.out.println("adding an item (OK)");
        else
            System.out.println("adding an item (Error)");


        hashmap.put(12,12);
        hashmap.put(12,12);
        hashmap.put(12,15);
        hashmap.put(12,14);
        if(hashmap.get(12).equals(14))
            System.out.println("adding with same key (OK)");
        else
            System.out.println("adding with same key (Error)");


        hashmap.remove(96);
        if(hashmap.get(96) == null)
            System.out.println("removing an item (OK)");
        else
            System.out.println("removing an item (Error)");


        if(hashmap.remove(-5000) == null)
            System.out.println("removing the item not in it (OK)");
        else
            System.out.println("removing the item not in it (Error)");


        if(hashmap.get(-5000) == null)
            System.out.println("getting the item not in it (OK)");
        else
            System.out.println("getting the item not in it (Error)");


        if( hashmap.get(79).equals(79) )
            System.out.println("getting the item in it (OK)");
        else
            System.out.println("getting the item in it (Error)");


        if( ! hashmap.isEmpty() )
            System.out.println("isEmpty method (OK)");
        else
            System.out.println("isEmpty method (Error)");


        if( hashmap.size() == 4)
            System.out.println("size method (OK)");
        else
            System.out.println("size method (Error) " + hashmap.size() );

    }



}
