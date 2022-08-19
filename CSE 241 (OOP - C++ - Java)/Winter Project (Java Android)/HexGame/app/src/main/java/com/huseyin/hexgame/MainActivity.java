package com.huseyin.hexgame;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

import HexEngine.Hex;

public class MainActivity extends AppCompatActivity {                       // board representation activity

    ImageView firstHexCell;
    List<ImageView> hexCells;
    BoardView boardLayout;
    List<BoardView> boardViews = new ArrayList<>();
    Hex myHex;

    int topMargin, marginStart, cellWidth, cellHeight;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {                                             // inflates options menu and add
        getMenuInflater().inflate(R.menu.options_menu,menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {                                 // sets all the options of the option menu
        try {

            switch (item.getItemId()) {
                case R.id.btnUndo    : boardLayout.undo(); break;
                case R.id.btnReset   : boardLayout.reset(); break;
                case R.id.btnNewGame : newGame(); break;
                case R.id.btnSave    : boardLayout.save(); break;
                case R.id.btnCompare : compare(); break;
                case R.id.btnLoadGame: loadGame(); break;
            }
        }catch (Exception e){}
        return true;
    }

    private void loadGame() {                                                                   // loads the game by showing list of the saved games
        AlertDialog.Builder b = new AlertDialog.Builder(this);
        b.setTitle("Select a game to load");
            String[] names = (String[]) Hex.getSavedGamesNames().toArray(new String[0]);
        b.setItems( names, new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int which) {
            //    dialog.dismiss();
                String name = names[which];
                try {
                        boardLayout = null;
                        myHex.load(name);
                        boardLayout = new BoardView(MainActivity.this,myHex,15,myHex.getBoardSize());
                        setContentView(boardLayout);

                } catch (Exception e) {
                    Toast.makeText(MainActivity.this,e.getMessage(),Toast.LENGTH_LONG).show();
                }

            }

        });

        b.show();
    }

    private void compare() {                                                                            // compares the games by showing all saved games

        AlertDialog.Builder b = new AlertDialog.Builder(this);
        b.setTitle("Select a game to compare");
        String[] names = (String[]) Hex.getSavedGamesNames().toArray(new String[0]);
        b.setItems( names, new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int which) {
                //    dialog.dismiss();
                String name = names[which];
                try {
                        Hex other = new Hex(8,"","");
                        other.load(name);
                        int a = myHex.compareTo(other);
                        String message;
                        if(a > 0)
                            message = "This game has more signed cells than the game"+name;
                        else if(a < 0)
                            message = "The game "+ name +" has more signed cells than this game";
                        else
                            message = "Both signed cell size is same";
                        Toast.makeText(MainActivity.this,message, Toast.LENGTH_LONG).show();

                } catch (Exception e) {
                    Toast.makeText(MainActivity.this,e.getMessage(),Toast.LENGTH_LONG).show();
                }

            }

        });

        b.show();
    }



    private void newGame() {                                                                                // starts a new game redirects to settings activity
        Intent intent = new Intent(this, SettingsActivity.class);
        startActivity(intent);
        finish();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {                                                      // oncreate method
        super.onCreate(savedInstanceState);
        //  setContentView(R.layout.activity_main);

        try {

            myHex = (Hex) getIntent().getSerializableExtra("hex");                                         // fetches the hex from intent
            boardLayout = new BoardView(this, myHex, 15, myHex.getBoardSize());
            setContentView(boardLayout);
        }

    catch (Exception e){
        Toast.makeText(this,e.getMessage(),Toast.LENGTH_LONG).show();
    }

    }
}
