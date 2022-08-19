import java.util.Arrays;
import java.util.Random;

public class Main {

    public static void main(String[] args){

        // BSTHeapTree
        BSTHeapTree<Integer> bst = new BSTHeapTree<>();
        try {
            bst.add(12);
            bst.add(24);
            bst.add(12);
            System.out.println(bst);

            bst.remove(12);
            bst.remove(12);
            System.out.println(bst);
            bst.remove(24);
            System.out.println(bst);


            System.out.println( bst.find(10) );


        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            bst.add(34);
            bst.add(34);
            bst.add(13);
            bst.add(13);
            bst.add(13);
            System.out.println( bst.find(34) );
            System.out.println( bst.find_mode() );

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }


        // MyHeap - PART 1

        MyHeap<Integer> pq = new MyHeap<Integer>();
        pq.add(12);
        pq.add(8);
        pq.add(10);
        System.out.println(pq);
        System.out.println(pq.remove());
        System.out.println(pq);

        pq.add(55);
        pq.add(11);
        pq.add(4);

        System.out.println(pq);

        MyHeap.Iterator<Integer> it = pq.iterator();
        while (it.hasNext())
        {
            Integer item = (Integer) it.next();
            if(item == 55) {
                item = 59;          /* !! iterator configured to stay at same index because the index of setted item can be changed */
                it.set(item);

            }
            System.out.println(item);

        }

        System.out.println(pq);

        System.out.println(pq.search(1));
        System.out.println(pq.search(59));

        System.out.println(pq);
        System.out.println(pq.remove());
        System.out.println(pq);

        MyHeap<Integer> hp2 = new MyHeap<Integer>();
        hp2.add(27);
        hp2.add(3);
        hp2.add(85);
        pq.merge(hp2);
        System.out.println(pq);

        pq.remove(0);
        System.out.println(pq);
        pq.remove(-5);
        System.out.println(pq);
        pq.remove(80);
        System.out.println(pq);

        pq.remove(1);
        System.out.println(pq);
        pq.remove(2);
        System.out.println(pq);
        pq.remove(3);
        System.out.println(pq);
        pq.remove(4);
        System.out.println(pq);
        pq.remove(2);
        System.out.println(pq);




        // PART 2.1

        BSTHeapTree<Integer> test1 = new BSTHeapTree<>();
        Random rand = new Random();
        int[] array = new int[3000];
        for(int i=0;i<3000; i++)
        {
            array[i] = rand.nextInt(5001);
            try {
                test1.add(array[i]);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        Arrays.sort(array);


        // PART 2.2
        int mode = -1;
        int mode_size = 0;

        int i=0;
        int index=0;
        int size=1;
        boolean checked = true;
        while (index < 2999)
        {
            if(array[index] == array[index+1]  )
                size++;
            else{
                int size2 = 0;

                if(mode_size < size) {
                    mode_size = size;
                    mode = array[index];
                }
                try {
                    size2 = test1.find(array[index]);
                } catch (Exception e) {
                    e.printStackTrace();
                }

                System.out.println(array[index]+" array: "+size+" BSTHeapTree: "+ size2 );
                if(size != size2)
                    checked = false;

                size = 1;
                i++;
            }
            index++;
        }

        if(checked)
            System.out.println("All item numbers same ( ok )\n\n");
        else
            System.out.println("Some item numbers not same\n\n");


    checked = true;
    for (i = 0; i < 10; i++) {
        int numberNotIn = 5000 + rand.nextInt(1000);
        try {
            test1.find(numberNotIn);
            checked = false;
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
    if(checked)
        System.out.println("10 numbers not in BSTHeapTree either ( ok )\n\n");
    else
        System.out.println("Some numbers are contains in BSTHeapTree\n\n");




        // PART 2.3


        int bst_mode = test1.find_mode();

        int mode_size2 = 0;
        for(i=0; i<3000; i++)
            if(array[i] == mode)
                mode_size2++;

        try {

            int bst_mode_size = test1.find(bst_mode);
            int bst_mode_size2 = test1.find(mode);

            System.out.println("BSTHeapTree mode:"+bst_mode+" Array mode:" +mode);
            System.out.println("frequency of " + bst_mode + " in Array:"+ mode_size + " in BSTHeapTree:" +bst_mode_size);
            System.out.println("frequency of " + mode + " in Array:"+ mode_size2 + " in BSTHeapTree:" +bst_mode_size2);

            if(mode_size == mode_size2 && bst_mode_size == bst_mode_size2 && mode_size == bst_mode_size)
                System.out.println("Both mode are have same frequency so both are correct ( ok )");
            else
                System.out.println("Some mode are have not same frequency ");

        } catch (Exception e) {
            e.printStackTrace();
        }




        // PART 2.4

        checked = true;
        for(i=0; i<100; i++) {

            try {
                int occurenceSize1 = test1.remove(array[i*20]);
                int occurenceSize2 = size(array[i*20],array) -1;
                if(occurenceSize1 != occurenceSize2)
                    checked = false;
            } catch (Exception e) { e.printStackTrace(); }
        }
        if(checked)
            System.out.println("\n\nAll occurence size after removing are same ( ok )\n\n");
        else
            System.out.println("\n\nSome occurence size after removing are not same\n\n");

        checked = true;
        for(i=0; i<10; i++)
        {
            int number = 5001+i*2;
            try {
                test1.remove(number);
                checked = false;                    // if doesn not throw exception then its wrong
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        if(checked)
            System.out.println("All 10 numbers are not found to remove ( ok )");
        else
            System.out.println("Some of 10 numbers are found in BST");
    }

    private static int size(int x, int[] array) {
        int size = 0;
        for (int i=0; i<3000; i++)
            if(array[i] == x)
                size++;

            return size;
    }
}
