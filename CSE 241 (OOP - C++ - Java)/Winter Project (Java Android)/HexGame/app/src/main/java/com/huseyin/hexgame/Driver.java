package com.huseyin.hexgame;

import HexEngine.Hex;
import HexEngine.Location;
import Minimax.Minimax;

public class Driver {                                                           // driver class for testing
    public void test() {

        Hex hex = null;

        try {
            hex = new Hex(8,"asd","dfg");
            hex.play(new Location(5,6));
            hex.setSave(false);
            System.out.println(hex.getStep());
            System.out.println(hex.getPlayerNow());
            System.out.println(hex.isEnd());
            System.out.println(hex.findConnections(new Location(3,5)));
            System.out.println(hex.getBoardSize());
            System.out.println(hex.getCell(new Location(3,2)));
            System.out.println(hex.getFreeCells().size());
            System.out.println(hex.getIsOneStart());
            hex.play(new Location(1,2));
            System.out.println(hex.getUserName1());
            System.out.println(hex.getUserName2());
            System.out.println(hex.lastMove());
            hex.undo();
            hex.play(new Location(6,3));
            hex.reset();
            Hex cloneHex = (Hex) hex.clone();
            hex.print();
            System.out.println(hex.getIsOneStart());
            hex.setSize(12);
            hex.print();

            Hex myHex = new Hex(7,"asd","Computer");

            myHex.play(new Location(4,3));
            myHex.play(new Location(1,3));
            myHex.play(new Location(5,4));
            Minimax minimax = new Minimax(myHex);
            myHex.print();
            System.out.println(minimax.getScoreOfUser2());
            Location location = minimax.bestLocation(myHex);
            myHex.print();

        } catch (Exception e) {
            e.printStackTrace();
        }


    }

    public void exceptionTest(){

        Hex hex = null;
        try {
            hex = new Hex(-5, "d", "a");
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            hex = new Hex(12,"asd","qwe");
            hex.play(new Location(-35,-5));
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            hex.save("asdf");
            hex.save("asdf");
        } catch (Exception e) {
            System.out.println(e);
        }


        try {
            hex.play(new Location(3,5));
            hex.play(new Location(3,5));
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            hex.findConnections(new Location());
        } catch (Exception e) {
            System.out.println(e);
        }

        try {

            hex.play();
            hex.play();
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            hex.load("qwerty12345");
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            hex.save("asdf");
        } catch (Exception e) {
            System.out.println(e);
        }




    }
}
