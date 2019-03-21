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
	JPanel jp0,jp1, jp2, jp3;
	JLabel jl1,jl2,jl3;
	JButton jb1, jb2,jb3;
	JCheckBox jcb1, jcb2, jcb3,jcb4,jcb5;
	ButtonGroup bg;
	JScrollPane jpa1;
	JScrollPane jpa2;
	final JTextArea ta;
	final JTextArea ta2;
	final JTextField tf1;
	final JTextField tf2;
	final JTextField tf3;
	private FileDialog openDia,saveDia;
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
		jp0 = new JPanel();
		jp1 = new JPanel();
		jp2 = new JPanel();
		jp3 = new JPanel();
		jpa2 = new JScrollPane();
		jpa1 = new JScrollPane();
		jl1 = new JLabel("控制参数");
		jl2 = new JLabel("原文件");
		jl3 = new JLabel("搜索结果");
		jb1 = new JButton("执行");
		jb2 = new JButton("导出");
		jb3 = new JButton("导入");
		tf1 = new JTextField(2);
		tf1.setEditable(false);
		tf2 = new JTextField(2);
		tf2.setEditable(false);
		tf3 = new JTextField(2);
		tf3.setEditable(false);
		ta = new JTextArea(10, 20);
		ta.setEditable(false);
		ta.append("Hello, world!");
		ta2 = new JTextArea(10, 20);
		ta2.append("Hello, world!");
		
		//ta.setWrapStyleWord(true);
		//ta.setLineWrap(true);
		//ta2.setWrapStyleWord(true);
		//ta2.setLineWrap(true);
		openDia = new FileDialog(f, "打开", FileDialog.LOAD);
		saveDia = new FileDialog(f, "保存", FileDialog.SAVE);
		
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
		
		
		jp0.add(jl2,BorderLayout.WEST);
		jp0.add(jl3,BorderLayout.EAST);
		//添加组件
		jp1.add(jl1);
		jp1.add(jcb1);
		jp1.add(jcb2);
		jp1.add(jcb3);
		jp1.add(tf1);
		jp1.add(jcb4);
		jp1.add(tf2);
		jp1.add(jcb5);
		jp1.add(tf3);
		
		jpa1.setViewportView(ta2);
		jpa2.setViewportView(ta);
		jp2.add(jpa1,BorderLayout.WEST);
		jp2.add(jpa2,BorderLayout.EAST);
		
		jp3.add(jb1);
		jp3.add(jb3);
		jp3.add(jb2);
		
		add(jp0);
		add(jp2);
		add(jp1);
		add(jp3);
		
		//设置窗体
		setSize(550, 340);
		setLocation(0, 0);
		GridBagConstraints s= new GridBagConstraints();//定义一个GridBagConstraints， 
		s.fill = GridBagConstraints.BOTH; 
		s.gridwidth=0;//该方法是设置组件水平所占用的格子数，如果为0，就说明该组件是该行的最后一个 
		s.weightx = 0;//该方法设置组件水平的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间 
		s.weighty=0;//该方法设置组件垂直的拉伸幅度，如果为0就说明不拉伸，不为0就随着窗口增大进行拉伸，0到1之间 
		layout.setConstraints(jp0, s);//设置组件 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
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
		setResizable(false);
	}
	public static void main(String[] args) {
		Gui14 gui1 = new Gui14();
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().equals("1")) {
			System.out.println("执行键被按下了");
			//这里是"执行"的回调函数
			boolean c1=jcb1.isSelected();
			boolean c2=jcb2.isSelected();
			boolean c3=jcb3.isSelected();
			boolean c4=jcb4.isSelected();
			boolean c5=jcb5.isSelected();
			if((c1&&c2) || (c1&&c3) || (c2&&c3)) {
				System.out.println("不合法输入!不执行");
				String st = "Invalid Input!";
				JOptionPane.showMessageDialog(null, st);
			}
			else {
				//TODO 这里填入C API的调用
				// c1,c2,c3,c4,c5对应 -w -c -h -t -n
				String text1=ta2.getText();
				// text1是输入的单词库
				ta.setText(ta2.getText());
			}
		}
		else if(e.getActionCommand().equals("2")) {
			System.out.println("导入键被按下了");
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
			System.out.println("导出键被按下了");
			if (file == null) {
                saveDia.setVisible(true);//显示保存文件对话框
                String dirpath = saveDia.getDirectory();//获取保存文件路径并保存到字符串中。
                String fileName = saveDia.getFile();////获取打保存文件名称并保存到字符串中
                
                if (dirpath == null || fileName == null)//判断路径和文件是否为空
                    return;//空操作
                else
                    file=new File(dirpath,fileName);//文件不为空，新建一个路径和名称
            }
                try {
                    BufferedWriter bufw = new BufferedWriter(new FileWriter(file));
                    
                    String text = ta.getText();//获取文本内容
                    bufw.write(text);//将获取文本内容写入到字符输出流
                    
                    bufw.close();//关闭文件
                } catch (IOException e1) {
                    //抛出IO异常
                    e1.printStackTrace();
                }
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
			if(check.isSelected()) {
				tf1.setEditable(true);
			}
			else {
				tf1.setEditable(false);
			}
		}
		else if(check.getName().equals("-t")) {
			System.out.println("t");
			if(check.isSelected()) {
				tf2.setEditable(true);
			}
			else {
				tf2.setEditable(false);
			}
		}
		else if(check.getName().equals("-n")) {
			System.out.println("n");
			if(check.isSelected()) {
				tf3.setEditable(true);
			}
			else {
				tf3.setEditable(false);
			}
		}
		
		
	}
	
}