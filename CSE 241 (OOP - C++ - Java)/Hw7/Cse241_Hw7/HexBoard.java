package Cse241_Hw7;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


public class HexBoard extends JPanel {

	CellButton cellButton[] ;
	int boardSize;
	private Hex myHex;
	public HexBoard(Hex hexGame) {
		
		myHex = hexGame;
		boardSize = hexGame.getBoardSize();
		
		createBoard(myHex);
	
	}

	public CellButton getCell(int i, int j) {
		return cellButton[i*boardSize + j ];
	}
	
	
	
	public void updateBoard() {

		int x=0;
		for(int i=0; i<boardSize; i++)
			for(int j=0; j<boardSize; j++)
			{
				if(myHex.getCell(i, j) == Hex.CellState.USER1 )
					{
						getCell(i, j).makeBlue();
						getCell(i, j).setEnabled(false);
					}
				if(myHex.getCell(i, j) == Hex.CellState.USER2 )
					{
						getCell(i, j).makeRed();
						getCell(i, j).setEnabled(false);
					}
				if(myHex.getCell(i, j) == Hex.CellState.DOT )
					{
						getCell(i, j).makeWhite();
						getCell(i, j).setEnabled(true);
					}
					x++;
			}
		
		if(myHex.getPlayerNow() == "Computer")
			{
			try{
				myHex.play();
				updateBoard();
			}
			catch (Exception e) {
				e.printStackTrace();
			}
			}
	}
	
	
	
	
	
	public void  createBoard(Hex hexGame) {
		super.setLayout(new GridLayout(boardSize ,1) );
		
		cellButton = new CellButton[boardSize*boardSize];
		
		for(int i=0; i<boardSize; i++)
		{
			JPanel row = new JPanel( new FlowLayout(FlowLayout.LEFT, 0, 0) );
			
			for(int freeSpace = 0; freeSpace < i; freeSpace++ )						// Cell buttons for free space 
			{
				CellButton freeButton = new CellButton(CellState.Free);
				freeButton.setEnabled(false);
				freeButton.setBackground(Color.lightGray);
				freeButton.setPreferredSize(new Dimension(freeButton.getPreferredSize().width/2, freeButton.getPreferredSize().height) );;
				row.add(freeButton);
				
			}
			
			
			for(int j=0; j<boardSize; j++ ) 
			{	
				cellButton[ i*boardSize + j ] = new CellButton( CellState.Free );
				cellButton[ i*boardSize + j ].setLoc(new Location(i,j));
				row.add(cellButton[ i*boardSize + j ]);	
				cellButton[ i*boardSize + j ].addActionListener(new ActionListener() {
					
					
					@Override
					public void actionPerformed(ActionEvent e) {
						try {
								if( hexGame.getPlayerNow() == hexGame.getUserName1() )
								{
									( (CellButton) e.getSource() ).makeBlue();
									Location location = ( (CellButton) e.getSource() ).getLoc();
									hexGame.play(location);
									if(hexGame.getUserName2().equals( "Computer"))
									{
										hexGame.play();
										updateBoard();
									}
								}
								
								else{
									( (CellButton) e.getSource() ).makeRed();
									Location location = ( (CellButton) e.getSource() ).getLoc();
									hexGame.play(location);
									
									
								}
								if( hexGame.isEnd() )
									JOptionPane.showMessageDialog(new JFrame(), "Game is end.");
								else {
									hexGame.changePlayerTurn();
									if( hexGame.isEnd() )
										JOptionPane.showMessageDialog(new JFrame(), "Game is end.");
									hexGame.changePlayerTurn();
								}
								hexGame.print();
								( (CellButton) e.getSource() ).setEnabled(false);
							}
						
							catch(Exception ex)
							{
								ex.printStackTrace();
							}
							
						
						
						
					}
				});
			}
			
			for(int freeSpace = 0; freeSpace < boardSize-i; freeSpace++ )						// Cell buttons for free space 
			{
				CellButton freeButton = new CellButton(CellState.Free);
				freeButton.setEnabled(false);
				//freeButton.setVisible(false);
				freeButton.setBackground(Color.lightGray);
				freeButton.setPreferredSize(new Dimension(freeButton.getPreferredSize().width/2, freeButton.getPreferredSize().height) );;
				row.add(freeButton);					
			}
			
			add(row);
		}
	}
}
