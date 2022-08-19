package Cse241_Hw7;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.SwingConstants;


public class SettingsFrame extends JFrame{

	private static final long serialVersionUID = 2377662771703316039L;

	public JTextField textField;
	public JTextField textField2;
	public JTextField textField3;
	public JButton startBtn;
	public ButtonGroup btnGroup;
	public JRadioButton rdBtn1; 
	public JRadioButton rdBtn2; 
	private MainFrame gameFrame;
	
	public MainFrame getGameFrame() {
		return gameFrame;
	}
	
	public SettingsFrame(Hex myHex) {

		btnGroup = new ButtonGroup();
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				int answer = JOptionPane.showConfirmDialog(new JFrame(), "Do you want to close all other games too ?","Close ?", JOptionPane.YES_NO_OPTION);
				if(answer == JOptionPane.YES_OPTION)
					System.exit(1);
				else
					dispose();
			}
		});
		setSize (450, 250);
		JPanel panel = new JPanel();
		add(panel, BorderLayout.NORTH);
		panel.setLayout(new GridLayout(2, 1, 5, 5));
		
		JLabel label1 = new JLabel("Hex Game");
		label1.setFont(new Font("Tahoma", Font.PLAIN, 18));
		label1.setHorizontalAlignment(SwingConstants.CENTER);
		panel.add(label1);
		
		JPanel panel2 = new JPanel();
		panel2.setLayout(new GridLayout(1,2,0,0));
		rdBtn1 = new JRadioButton("Computer -  User");
		rdBtn1.setFont(new Font("Tahoma", Font.PLAIN, 14));
		rdBtn1.setHorizontalAlignment(SwingConstants.CENTER);
		panel2.add(rdBtn1);
		btnGroup.add(rdBtn1);
		
		rdBtn2 = new JRadioButton("User - User");
		rdBtn2.setFont(new Font("Tahoma", Font.PLAIN, 14));
		rdBtn2.setHorizontalAlignment(SwingConstants.CENTER);
		panel2.add(rdBtn2);
		panel.add(panel2);
		btnGroup.add(rdBtn2);
		
		JPanel panel_1 = new JPanel();
		add(panel_1, BorderLayout.SOUTH);
		panel_1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		startBtn = new JButton("Start");
		startBtn.setFont(new Font("Tahoma", Font.PLAIN, 15));
		panel_1.add(startBtn);
		
		JPanel panel_2 = new JPanel();
		add(panel_2, BorderLayout.CENTER);
		panel_2.setLayout(new GridLayout(4, 2, 5, 15));
		
		JLabel label2 = new JLabel("User 1");
		label2.setFont(new Font("Tahoma", Font.PLAIN, 14));
		label2.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(label2);
		
		textField = new JTextField();
		textField.setHorizontalAlignment(SwingConstants.LEFT);
		panel_2.add(textField);
		textField.setColumns(10);
		
		JLabel label3 = new JLabel("User 2");
		label3.setFont(new Font("Tahoma", Font.PLAIN, 14));
		label3.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(label3);
		
		textField2 = new JTextField();
		panel_2.add(textField2);
		textField2.setColumns(10);
		
		JLabel label4 = new JLabel("Board Size");
		label4.setFont(new Font("Tahoma", Font.PLAIN, 14));
		label4.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(label4);
		
		textField3 = new JTextField();
		panel_2.add(textField3);
		textField3.setColumns(10);

	
	
	
	
	
	
		startBtn.addActionListener(new ActionListener() {
		
		@Override
		public void actionPerformed(ActionEvent e) {
			
			try {
					
					int boardSize = Integer.parseInt( textField3.getText() ) ;
					if(boardSize >25 || boardSize < 7)
						throw new Exception();
					String userName1 = textField.getText();
					String userName2 = textField2.getText();
					myHex.setSize(boardSize);
					myHex.setUserName1(userName1);
					myHex.setUserName2(userName2);
					myHex.writeToFile( "Current/step0");
					gameFrame = new MainFrame(myHex);
					gameFrame.show();
					dispose();
				} 
				catch (Exception e1) {
					JOptionPane.showMessageDialog(new JFrame(), "The boardSize must be a number between 7-25");
				}
			
		}
	});
	
		
		
		
		
		rdBtn1.addActionListener(new ActionListener() {
		
		@Override
		public void actionPerformed(ActionEvent e) {
			
		textField2.setText("Computer");	
		textField2.disable();
		}
	});
	
	
	
	
	
		rdBtn2.addActionListener(new ActionListener() {
		
		@Override
		public void actionPerformed(ActionEvent e) {
	
			textField2.enable();
			textField2.setText("");
		}
	});
	
	}
	
}
