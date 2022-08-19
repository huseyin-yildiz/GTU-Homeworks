import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Test class that tests all hw parts
 */
public class Main {

    public static void main(String[] args){

        System.out.print("\n PART 1.1 \n");
        NavigableSkipList<Integer> sl = new NavigableSkipList<Integer>();

        sl.insert(3);
        sl.insert(30);
        sl.insert(-1);
        sl.insert(13);
        sl.insert(19);
        sl.insert(1);
        sl.insert(5);
        sl.insert(8);
        sl.insert(15);
        sl.insert(20);
        sl.insert(17);
        sl.insert(2);
        sl.insert(5);
        sl.insert(11);
        sl.insert(13);
        sl.insert(4);
        sl.insert(28);
        sl.insert(0);

        System.out.println("After adding: " + sl);

        System.out.print("Iterator: ");
        Iterator<Integer> it = sl.descendingIterator();
        while (it.hasNext())
            System.out.print((it.next() + (it.hasNext() ? ", " : " \n")));

        it = sl.descendingIterator();
        it.next();
        it.next();


        it.remove();
        System.out.println(sl);


        sl.delete(5);
        sl.delete(17);
        sl.delete(28);
        sl.delete(1);
        sl.delete(2);

        System.out.println("After removing some elements:   " + sl);


        System.out.print("\n PART 1.2 \n");

        NavigableAVLTree<Integer> na = new NavigableAVLTree<>();

        na.insert(3);
        na.insert(30);
        na.insert(-1);
        na.insert(13);
        na.insert(19);
        na.insert(1);
        na.insert(5);
        na.insert(8);
        na.insert(15);
        na.insert(20);
        na.insert(17);
        na.insert(2);
        na.insert(5);
        na.insert(11);
        na.insert(13);
        na.insert(4);
        na.insert(28);
        na.insert(0);

        System.out.println("After insertion: " + na.toString());

        System.out.print("Iterator: ");
        it = na.iterator();
        while (it.hasNext())
            System.out.print((it.next() + (it.hasNext() ? ", " : " \n")));

        it = na.iterator();
        it.next();
        it.next();


        it.remove();

        System.out.println("Removing with iterator ");

        it = na.iterator();
        while (it.hasNext())
            System.out.print((it.next() + (it.hasNext() ? ", " : " \n")));



        System.out.println("headSet(4):");
        NavigableAVLTree<Integer> headSet = na.headSet(4);
        it = headSet.iterator();
        while (it.hasNext())
            System.out.print((it.next() + (it.hasNext() ? ", " : " \n")));


        System.out.println("tailSet(4):");
        NavigableAVLTree<Integer> tailSet = na.tailSet(4);
        it = tailSet.iterator();
        while (it.hasNext())
            System.out.print((it.next() + (it.hasNext() ? ", " : " \n")));




        System.out.print("\n PART 2.1 \n");



        BST<Integer> avlTest = new BST();
        avlTest.add(20);
        avlTest.add(30);
        avlTest.add(10);
        avlTest.add(5);
        avlTest.add(15);
        avlTest.add(25);
        avlTest.add(35);
        avlTest.add(3);
        avlTest.add(6);
        avlTest.add(13);

        System.out.println( "is avl: "+BalancingTreeCheck.isAVL(avlTest) );
        avlTest.add(1);
        System.out.println("after adding item that makes imbalanced is avl: "+ BalancingTreeCheck.isAVL(avlTest));

        System.out.print("\n PART 2.2 \n");

        BST<Integer> redBlackTest = new BST();
        redBlackTest = new BST();
        redBlackTest.add(20,false);
        redBlackTest.add(30,true);
        redBlackTest.add(10,false);
        redBlackTest.add(5,true);
        redBlackTest.add(15,false);
        redBlackTest.add(25,false);
        redBlackTest.add(35,false);
        redBlackTest.add(3,false);
        redBlackTest.add(6,false);
        redBlackTest.add(13,true);
        redBlackTest.add(18,true);
        redBlackTest.add(23,false);
        redBlackTest.add(28,false);
        redBlackTest.add(32,false);
        redBlackTest.add(39,false);



        System.out.println("is red-black: "+BalancingTreeCheck.isRedBlack(redBlackTest));

        redBlackTest.add(45,false);
        System.out.println("After adding item that makes imbalanced is red-black: "+BalancingTreeCheck.isRedBlack(redBlackTest));

        System.out.println("\nred root red-black test");
        redBlackTest = new BST<>();
        redBlackTest.add(12,true);
        System.out.println("is red-black: "+BalancingTreeCheck.isRedBlack(redBlackTest));



        System.out.print("\n PART 3 \n");

        HashMap<String,Double> results = new HashMap<>();
        makeTests(results,10000);
        makeTests(results,20000);
        makeTests(results,40000);
        makeTests(results,80000);
        makeGraph(results);




    }
    public static void makeGraph(HashMap<String,Double> results){
        System.out.println("====== Average Running times =======");
        Iterator<Map.Entry<String,Double>> it = results.entrySet().iterator();
        while (it.hasNext()){
            Map.Entry<String,Double> result = it.next();
            int size = (int) (result.getValue()*2000);
            System.out.println(String.format("%15s",result.getKey())+": "+"*".repeat(size));
        }
    }

    public static void makeTests(HashMap<String,Double> results, int size){

        int array[] = Test.get_random_array(size);
        BST<Integer> bst = new BST<>();
        RedBlackTree<Integer> redBlack = new RedBlackTree<>();
        TwoThreeTree<Integer> twoThree = new TwoThreeTree<>();
        BTree<Integer> bTree = new BTree<>(100);
        SkipList<Integer> skipList = new SkipList<>();

        double duration = new Test(bst,array,10).getAddingTime();
        results.put("BST "+size,duration);

        duration = new Test(redBlack,array,10).getAddingTime();
        results.put("Red-Black "+size,duration);

        duration = new Test(twoThree,array,10).getAddingTime();
        results.put("Two-Three "+size,duration);

        duration = new Test(bTree,array,10).getAddingTime();
        results.put("B-Tree "+size,duration);

        duration = new Test(skipList,array,10).getAddingTime();
        results.put("Skip-List "+size,duration);

    }


}
