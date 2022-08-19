package Cse241_Hw7;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.Closeable;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class MainFrame extends JFrame {

	public HexBoard board;
	
	public MainFrame(Hex hexGame) {
		
		super("Hex");
		

		getContentPane().setLayout(new BorderLayout(0, 0));
		
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				int answer = JOptionPane.showConfirmDialog(new JFrame(), "Do you want to close all games ?","Close ?", JOptionPane.YES_NO_OPTION);
				if(answer == JOptionPane.YES_OPTION)
					System.exit(1);
				else
					dispose();
			}
		});
		
		JPanel panel = new JPanel();
		add(panel, BorderLayout.NORTH);
		
		JLabel label = new JLabel(hexGame.getUserName1() + " - " + hexGame.getUserName2() );
		label.setFont(new Font("Tahoma", Font.PLAIN, 18));
		panel.add(label);
		
		JPanel btn_panel = new JPanel();
		getContentPane().add(btn_panel, BorderLayout.EAST);
		btn_panel.setLayout(new GridLayout(10, 1, 0, 0));
		
		JButton btnReset = new JButton("Reset");
		btn_panel.add(btnReset);
		
		JButton btnUndo = new JButton("Undo");
		btn_panel.add(btnUndo);
		
		JButton btnSave = new JButton("Save Game");
		btn_panel.add(btnSave);
		
		JButton btnLoad = new JButton("Load Game");
		btn_panel.add(btnLoad);
		
		
		JButton btnCompare = new JButton("Compare Game");
		btn_panel.add(btnCompare);
		
		JButton btnNew = new JButton("New Game");
		btn_panel.add(btnNew);
		
		board = new HexBoard(hexGame);
		int sizeOfBoardPanel = 40*hexGame.getBoardSize()*3/2;
		setSize(new Dimension(sizeOfBoardPanel + 140, 40*hexGame.getBoardSize()+80 ) );
		add(board, BorderLayout.CENTER);
		
		btnReset.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
			
				hexGame.reset();
				board.updateBoard();
			}
		});
		
		
		btnUndo.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					hexGame.undo();
					if(hexGame.getPlayerNow().equals("Computer") )
						hexGame.undo();
						
					board.updateBoard();
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		
		btnSave.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
			
				try{
					String gameName = JOptionPane.showInputDialog("Enter a name for saving game");
					if(gameName != null)
					{
						hexGame.save(gameName);
						JOptionPane.showMessageDialog(new JFrame(), "The game saved successfully.");
					}
				}
				catch (Exception e1) {
					e1.printStackTrace();
				}
			
			}
		});
		
		
		btnLoad.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				try {
				File games = new File("savedGames/");
				
			      Object[] gameNames = games.list();
			      JComboBox comboBox = new JComboBox(gameNames);
			      JOptionPane.showMessageDialog(null, comboBox, "Select a saved game...",JOptionPane.QUESTION_MESSAGE);
			      String selection = (String)comboBox.getSelectedItem();
			      hexGame.load(selection);
			      hide();
			      MainFrame newFrame = new MainFrame(hexGame);
			      newFrame.board.updateBoard();
			      newFrame.show();
			      
				}
				catch (Exception e2) {
					e2.printStackTrace();
				}
			}
		});
		
		
	
		btnCompare.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
				File games = new File("savedGames/");
				Object[] gameNames = games.list();
			      JComboBox comboBox = new JComboBox(gameNames);
			      JOptionPane.showMessageDialog(null, comboBox, "Select a saved game...",JOptionPane.QUESTION_MESSAGE);
			      String selection = (String)comboBox.getSelectedItem();
			      Hex toCompare = new Hex(8,"a","a");
			      toCompare.load(selection);
			      
			      String text;
			      if(hexGame.compareTo(toCompare) > 0)
			    	  text = "This game has more marked cells than game " + selection ; 
			      else if(hexGame.compareTo(toCompare) < 0)
				    	 text = selection + " has more marked cells than this game."; 
			      else
				    	text = "Both games have same number of marked cells." ;  
			      
			      JOptionPane.showMessageDialog(new JFrame(),text );
				}
				catch(Exception e3)
				{
					e3.printStackTrace();
				}
			
			}
		});
		
		btnNew.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					Hex newHex = new Hex(8, "user1", "user2");
					SettingsFrame newSf = new SettingsFrame(newHex);
					newSf.show();
				}
				
				catch (Exception e4) {
					e4.printStackTrace();
				}
				
			}
		});
		
	}
	
}
