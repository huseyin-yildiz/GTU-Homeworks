package com.huseyin.hexgame;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Point;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import androidx.annotation.Nullable;

import HexEngine.Location;

@SuppressLint("AppCompatCustomView")
public class CellView extends ImageView {                                                       // The view for cell

    enum CellColor{                                             // cell colors
        Blue,
        Red,
        Orange,
        Green,
        Yellow,
        Gray
    }

    private static int id = 1000;
    private int myId;
    private Context context;
    private static CellView lastCellView;
    private Point lastLocation;
    private int cellSize;

    public static void resetId(){
        id = 1000;
    }                           // resets the id
    private void init(Context context, int cellSize){                       // initialization method

        id++;
        myId = id;
        this.context = context;
        this.cellSize = cellSize;

        setId(id);
        setCellLengths(cellSize);
        setColor(CellColor.Gray);

        lastCellView = this;

        setDrawingCacheEnabled(true);


    }


    public Location getLocation(int boardSize){                                                 // returns the location of the cell
        int y = ((myId-1001) % boardSize) ;
        int x = (myId-1001) / boardSize;

        return new Location(x,y);
    }


    public void setColor(CellColor cellColor){                                                              // sets the color of cell
        switch (cellColor)
        {
            case Red: setBackgroundResource(R.drawable.red);break;
            case Blue: setBackgroundResource(R.drawable.blue);break;
            case Green: setBackgroundResource(R.drawable.green);break;
            case Orange: setBackgroundResource(R.drawable.orange);break;
            case Yellow: setBackgroundResource(R.drawable.yellow);break;
            case Gray: setBackgroundResource(R.drawable.gray);break;
            default: setBackgroundResource(R.drawable.gray);break;
        }
    }

    private void setCellLengths(int cellSize) {                                                                 // sets the lengths of the cell according to cellsize

        ImageView iv = (ImageView) LayoutInflater.from(context).inflate(R.layout.cell,null);
        int size = dpToPx(cellSize);
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(size, size);


        layoutParams.setMarginStart(dpToPx(-23) );
        layoutParams.topMargin = dpToPx(-39);
        layoutParams.width = dpToPx(cellSize);
        layoutParams.height = dpToPx(cellSize);


        layoutParams.addRule(RelativeLayout.RIGHT_OF, id-1);
        layoutParams.addRule(RelativeLayout.END_OF, id-1);
        layoutParams.addRule(RelativeLayout.BELOW,id-1);
        setLayoutParams(layoutParams);

    }




    public int dpToPx(float dp){                                                                // to convert dp topx
        Resources r = getContext().getResources();
        int px = (int) TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dp,
                r.getDisplayMetrics()
        );
        return px;
    }



    public CellView(Context context,int cellSize) {                                     // constructors
        super(context);
        init(context,cellSize);
    }

    public CellView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(context,60);

    }

    public CellView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context,60);
    }

    public CellView(Context context, @Nullable AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        init(context,60);
    }
}
