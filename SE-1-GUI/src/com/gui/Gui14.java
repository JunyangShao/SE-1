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
	//�������
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
	//���캯��
	boolean file_in=false;
	boolean w=false;
	boolean c=false;
	boolean h=false;
	boolean t=false;
	boolean n=false;
	public Gui14(){
		//�������
		jp1 = new JPanel();
		jp2 = new JPanel();
		jp3 = new JPanel();
		jl1 = new JLabel("���Ʋ���");
		jb1 = new JButton("ִ��");
		jb2 = new JButton("����");
		jb3 = new JButton("����");
		ta = new JTextArea(10, 20);
		ta.setEditable(false);
		ta.append("Hello, world!");
		ta2 = new JTextArea(10, 20);
		ta2.append("Hello, world!");
		openDia = new FileDialog(f, "��", FileDialog.LOAD);
		
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
		
		
		//��ѡ���һ��Ҫ���뵽һ��ButtonGroup
		//������Ļ������Զ�ѡ
		bg = new ButtonGroup();
		
		//���ò��ֹ�����
		GridBagLayout layout = new GridBagLayout();
		setLayout(layout);
		
		//������
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
		
		//���ô���
		setSize(550, 340);
		setLocation(0, 0);
		GridBagConstraints s= new GridBagConstraints();//����һ��GridBagConstraints�� 
		s.fill = GridBagConstraints.BOTH; 
		s.gridwidth=1;//�÷������������ˮƽ��ռ�õĸ����������Ϊ0����˵��������Ǹ��е����һ�� 
		s.weightx = 0;//�÷����������ˮƽ��������ȣ����Ϊ0��˵�������죬��Ϊ0�����Ŵ�������������죬0��1֮�� 
		s.weighty=0;//�÷������������ֱ��������ȣ����Ϊ0��˵�������죬��Ϊ0�����Ŵ�������������죬0��1֮�� 
		layout.setConstraints(jp1, s);//������� 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
		layout.setConstraints(jp2, s);//������� 
		s.gridwidth=0; 
		s.weightx = 0; 
		s.weighty=0; 
		layout.setConstraints(jp3, s);//������� 
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
			openDia.setVisible(true);//��ʾ���ļ��Ի���
            
            String dirpath = openDia.getDirectory();//��ȡ���ļ�·�������浽�ַ����С�
            String fileName = openDia.getFile();//��ȡ���ļ����Ʋ����浽�ַ�����
            
            if (dirpath == null || fileName == null)//�ж�·�����ļ��Ƿ�Ϊ��
                return;
            else
                ta2.setText(null);//�ļ���Ϊ�գ����ԭ���ļ����ݡ�
            file = new File(dirpath, fileName);//�����µ�·��������

            try {
                BufferedReader bufr = new BufferedReader(new FileReader(file));//���Դ��ļ��ж�����
                String line = null;//�����ַ�����ʼ��Ϊ��
                while ((line = bufr.readLine()) != null) {
                    ta2.append(line + "\r\n");//��ʾÿһ������
                }
                bufr.close();//�ر��ļ�
            } catch (FileNotFoundException e1) {
                // �׳��ļ�·���Ҳ����쳣
                e1.printStackTrace();
            } catch (IOException e1) {
                // �׳�IO�쳣
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