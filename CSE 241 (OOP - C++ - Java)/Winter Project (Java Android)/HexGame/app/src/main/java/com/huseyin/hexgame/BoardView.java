package com.huseyin.hexgame;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.text.InputType;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import HexEngine.Hex;
import HexEngine.Location;
import Minimax.Minimax;


public class BoardView extends RelativeLayout {                              // a class for boardView

    private int padding;
    private int boardSize;
    private int cellSize;                                                      // required fields
    private Context context;
    private CellView.CellColor color1;
    private CellView.CellColor color2;
    private Hex hex;


    private void init(Context context, Hex hex, int myPadding, int boardSize) throws Exception {                        // initialization method

        this.context = context;
        this.hex = hex;
        LayoutParams layoutParams = new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
        padding = dpToPx(myPadding);                                                                                // initializations
        this.boardSize = boardSize;
        setPadding(padding,padding,padding,padding);
        setCellSize();
        makeBoard();
        setColors(hex);
        updateBoard();


    }

    private void setColors(Hex hex) {                                               // sets colors of board cells
        color1 = CellView.CellColor.valueOf(hex.getUserName1());
        if(hex.getUserName2().equals("Computer")) {
            if (color1 == CellView.CellColor.Blue)
                color2 = CellView.CellColor.Red;
            else
                color2 = CellView.CellColor.Blue;
        }
        else
            color2 = CellView.CellColor.valueOf(hex.getUserName2());
    }

    private void makeBoard() {                                                         // makes board row by row
        CellView.resetId();
        for(int i=0; i<boardSize; i++)
        {
            addCellToNewRow();
            for(int j=0; j<boardSize-1; j++)
                addCellToRow();
        }
    }

    private void addCellToNewRow() {                                                    // adds new cells to new row

        CellView cellView = new CellView(context,cellSize);

        LayoutParams layoutParams = new RelativeLayout.LayoutParams(cellSize, cellSize);
        layoutParams.width = cellSize;
        layoutParams.height = cellSize;

        int id = cellView.getId();

        if(id != 1001) {
            layoutParams.addRule(RelativeLayout.BELOW,id-boardSize);
            layoutParams.topMargin = -cellSize/3 + cellSize / 15;
        }

      //      layoutParams.topMargin = 10;
        cellView.setLayoutParams(layoutParams);
        setCellListener(cellView);
        addView(cellView);
    }

    private void addCellToRow() {                                                           // adds a cell to row
        CellView cellView = new CellView(context,cellSize);

        LayoutParams layoutParams = new RelativeLayout.LayoutParams(cellSize, cellSize);
        layoutParams.setMarginStart(-1*cellSize/3 - dpToPx(2));
        layoutParams.topMargin = -2*cellSize/3 + cellSize/30 ;
        layoutParams.width = cellSize;
        layoutParams.height = cellSize;

        int id = cellView.getId();

        layoutParams.addRule(RelativeLayout.RIGHT_OF, id-1);
        layoutParams.addRule(RelativeLayout.END_OF, id-1);
        layoutParams.addRule(RelativeLayout.BELOW,id-1);
        cellView.setLayoutParams(layoutParams);
        setCellListener(cellView);
        addView(cellView);
    }




    private void setCellSize() {                                          // calculates the appropriate cellSize

         int screenWidth = getContext().getResources().getDisplayMetrics().widthPixels - getPaddingRight() - getPaddingLeft();
         int cellSizeInPx = (int) (( 3.0 * (float)screenWidth ) / ( (float)boardSize * 2.1 ));
         this.cellSize = cellSizeInPx;

    }


    private int dpToPx(float dp){                                        // to convert dp to px
        Resources r = getContext().getResources();
        int px = (int) TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dp,
                r.getDisplayMetrics()
        );
        return px;
    }

    @Override
    public void addView(View child) {
        super.addView(child);

    }

    private void makeRow(ImageView firstHexCell){
        int id = 1000;
        firstHexCell.setId(id);
        for(int i=0; i<boardSize; i++)
        {
            CellView cellView = new CellView(context,60);
         //   if(! isEndOfRow())
               // boardLayout.addView(cellView);
    //      onResume();
        }
    }

    private void setCellListener(CellView cellView){
        cellView.setDrawingCacheEnabled(true);

        cellView.setOnTouchListener(new OnTouchListener() {                         // handling the board screen touches
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Bitmap bmp = Bitmap.createBitmap(v.getDrawingCache());
                int color = bmp.getPixel((int) event.getX(), (int) event.getY());
                if (color == Color.TRANSPARENT)
                    return false;
                else {
                    try {
                        if(event.getAction() == MotionEvent.ACTION_DOWN) {
                            if (hex.getPlayerNow() != "Computer" && !hex.isEnd() ) {            // if player is not computer

                                Location location = cellView.getLocation(boardSize);
                                if (hex.getCell(location).asChar() == '.' ){
                                    hex.play(location);
                                    hex.print();
                                    updateBoard();
                                    if(hex.isEnd()) {
                                        showWinner();
                                        return false;
                                    }
                                    if (hex.getPlayerNow().equals("Computer")) {

                                            Minimax minimax = new Minimax(hex);
                                            Location loc = minimax.bestLocation(hex);                   // plays for computer
                                            hex.play(loc);
                                        updateBoard();
                                            hex.print();

                                        if(hex.isEnd()) {
                                            showWinner();
                                            return false;
                                        }
                                    }
                                }


                            }
                        }
                    }
                    catch (Exception e) {
                        Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_SHORT).show();
                    }

                        return true;
                }
            }
        });
    }

    private void showWinner() throws Exception {                                                                    // shows a winner with a toast message
        String winner = hex.getPlayerNow().equals(hex.getUserName1()) ? hex.getUserName2() : hex.getUserName1();
        Toast.makeText(context, "The game end "+winner+ " is winner" , Toast.LENGTH_LONG).show();
        System.out.println(hex.isEnd());
    }


    public void save() {
                                                                                                                  // taking name to save with a alert dialog
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle("Enter a name to save");

        final EditText input = new EditText(context);
        input.setInputType(InputType.TYPE_CLASS_TEXT);
        builder.setView(input);


        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {                                     // buttons
            @Override
            public void onClick(DialogInterface dialog, int which) {
                String name =  input.getText().toString();
                try {
                    hex.save(name);                                                                                   // saving the game with given name
                    Toast.makeText(context,"The game saved Successfully",Toast.LENGTH_LONG).show();
                } catch (Exception e) {
                    Toast.makeText(context,e.getMessage(),Toast.LENGTH_LONG).show();
                }
            }
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel();
            }
        });

        builder.show();

    }


    private void setCell(Location location, CellView.CellColor color){                      // sets the board cells color
        int cellId = 1001 + boardSize*(location.get_x()) + location.get_y();
        CellView cellView = findViewById(cellId);
        cellView.setColor(color);
    }

    public void updateBoard(){                                                              // updates the board
        for(int i=0; i<boardSize; i++)
            for(int j=0; j<boardSize; j++) {
                    if (hex.getCell(i, j).asChar() == 'o')
                        setCell(new Location(i, j), color1);
                    else if (hex.getCell(i, j).asChar() == 'x')
                        setCell(new Location(i, j), color2);
                    else
                        setCell(new Location(i, j), CellView.CellColor.Gray);

            }


    }



    public BoardView(Context context,Hex hex ,int myPadding, int boardSize) throws Exception {                  // constructors
        super(context);
        init(context ,hex ,myPadding ,boardSize);
    }

    public BoardView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public BoardView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public BoardView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    public void undo() throws Exception {                                                                       // undo operation
        hex.undo();
        if(hex.getPlayerNow().equals( "Computer") )
            hex.undo();
        updateBoard();
    }

    public void reset() throws Exception {                                                                     // resets the board
        hex = new Hex(hex.getBoardSize(),hex.getUserName1(),hex.getUserName2());
        updateBoard();
    }
}
