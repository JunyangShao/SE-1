package com.gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.FileDialog;
import java.awt.Frame;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Gui14 extends JFrame implements ActionListener, ItemListener{
	//定义组件
	JPanel jp1, jp2, jp3;
	JLabel jl1;
	JButton jb1, jb2,jb3;
	JCheckBox jcb1, jcb2, jcb3,jcb4,jcb5;
	ButtonGroup bg;
	final JTextArea ta;
	final JTextArea ta2;
	private FileDialog openDia;
	private File file;
	private Frame f;
	//构造函数
	boolean file_in=false;
	boolean w=false;
	boolean c=false;
	boolean h=false;
	boolean t=false;
	boolean n=false;
	public Gui14(){
		//创建组件
		jp1 = new JPanel();
		jp2 = new JPanel();
		jp3 = new JPanel();
		jl1 = new JLabel("控制参数");
		jb1 = new JButton("执行");
		jb2 = new JButton("导出");
		jb3 = new JButton("导入");
		ta = new JTextArea(10, 20);
		ta.setEditable(false);
		ta.append("Hello, world!");
		ta2 = new JTextArea(10, 20);
		ta2.append("Hello, world!");
		openDia = new FileDialog(f, "打开", FileDialog.LOAD);
		
		jb1.addActionListener(this);
		jb2.addActionListener(this);
		jb3.addActionListener(this);
		jb1.setActionCommand("1");
		jb2.setActionCommand("3");
		jb3.setActionCommand("2");
		
		
		
		jcb1 = new JCheckBox("-w");
		jcb2 = new JCheckBox("-c");
		jcb3 = new JCheckBox("-h");
		jcb4 = new JCheckBox("-t");
		jcb5 = new JCheckBox("-n");
		
		jcb1.setName("-w");
		jcb2.setName("-c");
		jcb3.setName("-h");
		jcb4.setName("-t");
		jcb5.setName("-n");
		
		
		jcb1.addItemListener(this);
		jcb2.addItemListener(this);
		jcb3.addItemListener(this);
		jcb4.addItemListener(this);
		jcb5.addItemListener(this);
		
		
		//单选组件一定要放入到一个ButtonGroup
		//不放入的话，可以多选
		bg = new ButtonGroup();
		
		//设置布局管理器
		GridBagLayout layout = new GridBagLayout();
		setLayout(layout);
		
		//添加组件
		jp1.add(jl1);
		jp1.add(jcb1);
		jp1.add(jcb2);
		jp1.add(jcb3);
		jp1.add(jcb4);
		jp1.add(jcb5);
		
		jp2.add(ta2);
		jp2.add(ta);
		
		jp3.add(jb1);
		jp3.add(jb3);
		jp3.add(jb2);
		
		add(jp2);
		add(jp1);
		add(jp3);
		
		//设置窗体
		setSize(550, 340);
		setLocation(0, 0);
		GridBagConstraints s= new GridBagConstraints();//定义一个GridBagConstraints， 
		s.fill = GridBagConstraints.BOTH; 
		s.gridwidth=1;//该方法是设置组件水平所占用的格子数，如果为0，就说明该组件是该行的最后一个 
		s.weightx = 0;//该方法设置组件水平的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间 
		s.weighty=0;//该方法设置组件垂直的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间 
		layout.setConstraints(jp1, s);//设置组件 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
		layout.setConstraints(jp2, s);//设置组件 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
		layout.setConstraints(jp3, s);//设置组件 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
		setTitle("LAB1");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	public static void main(String[] args) {
		Gui14 gui1 = new Gui14();
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().equals("1")) {
			System.out.println("1");
		}
		else if(e.getActionCommand().equals("2")) {
			System.out.println("2");
			openDia.setVisible(true);//显示打开文件对话框
            
            String dirpath = openDia.getDirectory();//获取打开文件路径并保存到字符串中。
            String fileName = openDia.getFile();//获取打开文件名称并保存到字符串中
            
            if (dirpath == null || fileName == null)//判断路径和文件是否为空
                return;
            else
                ta2.setText(null);//文件不为空，清空原来文件内容。
            file = new File(dirpath, fileName);//创建新的路径和名称

            try {
                BufferedReader bufr = new BufferedReader(new FileReader(file));//尝试从文件中读东西
                String line = null;//变量字符串初始化为空
                while ((line = bufr.readLine()) != null) {
                    ta2.append(line + "\r\n");//显示每一行内容
                }
                bufr.close();//关闭文件
            } catch (FileNotFoundException e1) {
                // 抛出文件路径找不到异常
                e1.printStackTrace();
            } catch (IOException e1) {
                // 抛出IO异常
                e1.printStackTrace();
            }

        }
		else if(e.getActionCommand().equals("3")) {
			System.out.println("3");
		}
		
	}
	@Override
	public void itemStateChanged(ItemEvent e) {
		// TODO Auto-generated method stub
		JCheckBox check=(JCheckBox)e.getSource();
		if(check.getName().equals("-w")) {
			System.out.println("w");
		}
		else if(check.getName().equals("-c")) {
			System.out.println("c");
		}
		else if(check.getName().equals("-h")) {
			System.out.println("h");
		}
		else if(check.getName().equals("-t")) {
			System.out.println("t");
		}
		else if(check.getName().equals("-n")) {
			System.out.println("n");
		}
		
		
	}
	
}