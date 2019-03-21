package com.gui;
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

class Gui2 {
    private Frame f;// ���崰��
    private MenuBar bar;// ����˵���
    private TextArea ta;
    private Menu fileMenu;// ����"�ļ�"��"�Ӳ˵�"�˵�
    private MenuItem openItem, saveItem, closeItem;// ������Ŀ���˳����͡�����Ŀ���˵���

    private FileDialog openDia;// ���塰�򿪡����桱�Ի���
    private File file;//�����ļ�

    Gui2() {
        init();
    }

    /* ͼ���û����������ʼ�� */
    public void init() {
        f = new Frame("my window");// �����������
        f.setBounds(300, 100, 350, 300);// ���ô���λ�úʹ�С

        bar = new MenuBar();// �����˵���
        ta = new TextArea();// �����ı���
        ta.setEditable(false);
        fileMenu = new Menu("�ļ�");// �������ļ����˵�

        openItem = new MenuItem("��");// ��������"�˵���
        closeItem = new MenuItem("ȷ��");// �������˳�"�˵���

        fileMenu.add(openItem);// �����򿪡��˵�����ӵ����ļ����˵���
        fileMenu.add(closeItem);// �����˳����˵�����ӵ����ļ����˵���

        bar.add(fileMenu);// ���ļ���ӵ��˵�����

        f.setMenuBar(bar);// ���˴���Ĳ˵�������Ϊָ���Ĳ˵�����

        openDia = new FileDialog(f, "��", FileDialog.LOAD);

        f.add(ta);// ���ı�����ӵ�������
        myEvent();// �����¼�����

        f.setVisible(true);// ���ô���ɼ�

    }

    private void myEvent() {
        
        // �򿪲˵������
        openItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                
                openDia.setVisible(true);//��ʾ���ļ��Ի���
                
                String dirpath = openDia.getDirectory();//��ȡ���ļ�·�������浽�ַ����С�
                String fileName = openDia.getFile();//��ȡ���ļ����Ʋ����浽�ַ�����
                
                if (dirpath == null || fileName == null)//�ж�·�����ļ��Ƿ�Ϊ��
                    return;
                else
                    ta.setText(null);//�ļ���Ϊ�գ����ԭ���ļ����ݡ�
                file = new File(dirpath, fileName);//�����µ�·��������

                try {
                    BufferedReader bufr = new BufferedReader(new FileReader(file));//���Դ��ļ��ж�����
                    String line = null;//�����ַ�����ʼ��Ϊ��
                    while ((line = bufr.readLine()) != null) {
                        ta.append(line + "\r\n");//��ʾÿһ������
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

        });
        
        
        // ȷ�ϲ˵������
        // TODO ������������
        closeItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }

        });
        
        // ����رռ���
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);

            }

        });
    }

    public static void main(String[] args) {
        new Gui2();
    }
}
