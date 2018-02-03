package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Random;

public class Main {
    public static int width = 800;
    public static int height = 700;
    public static int minRange = 10; //minimal distance between Cities
    public static int indent = 10; //indent from window edges
    public static int CityNumber = 30;
    public static int CodeNumber = 30;
    private static ArrayList<Code> codeSpace;//популяция
    private static ArrayList<City> list;//начальный список городов
    private static ArrayList<Code> history;//то что передается в гуи
    private static MyPanel myPanel;
    public static int currentCode;//номер из history который отображается на экране

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                System.setProperty("java.util.Arrays.useLegacyMergeSort", "true");
                generateList();
                history = new ArrayList<Code>();
                Code first = new Code(list);
                first.countDistance();
                history.add(first);
                createAndShowGUI(history);
            }
        });
    }

    private static void generateList() {
        list = new ArrayList<City>();
        Random random = new Random();
        int countCircles = 0;
        while(countCircles<CityNumber) {
            City newCity = new City(random.nextInt(width-2*City.radius-indent)+indent+City.radius,
                    random.nextInt(height-2*City.radius-indent)+indent+City.radius,0);
            if(checkIfPlaceFreeForCity(newCity)) {
                countCircles++;
                newCity.setOrder(countCircles);
                list.add(newCity);
            }
        }
    }

    private static boolean checkIfPlaceFreeForCity(City newCity) {
        for(City sample: list) {
            if(checkCirclesCrossing(sample, newCity)) {
                return false;
            }
        }
        return true;
    }

    private static boolean checkCirclesCrossing(City one, City two) {
        if(Math.sqrt(Math.pow(one.x-two.x,2)+Math.pow(one.y-two.y,2))<2*City.radius+minRange) {
            return true;
        }
        return false;
    }

    private static void createAndShowGUI(ArrayList<Code> newList) {
        JFrame f = new JFrame("Graph Painter");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setResizable(false);
        /*initializing layout*/
        FlowLayout experimentLayout = new FlowLayout();
        f.setLayout(experimentLayout);
        f.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
        /*panel for control*/
        JPanel panel = new JPanel();
        JButton button = new JButton("Start");
        button.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                Code current = new Code(history.get(currentCode));
                history.clear();
                history.add(current);
                codeSpace = new ArrayList<Code>();
                codeSpace.add(current);
                currentCode = 0;
                for(int i=1; i<CodeNumber; i++) {
                    codeSpace.add(shuffleNewCode());
                }
                GeneticAlgorithm myAlgorithm = new GeneticAlgorithm(codeSpace);
                ArrayList<Code> buf = myAlgorithm.Solve();
                for(int i=1; i<buf.size(); i++) {
                    history.add(buf.get(i));
                }
                for(City city: history.get(history.size()-1).list) {
                    System.out.print(city.order+"-");
                }
                System.out.println();
                System.out.println(history.get(history.size()-1).distance);
            }
        });
        panel.add(button);
        /*adding 2 panels*/
        myPanel = new MyPanel(newList);

        Action rightAction = new AbstractAction(){
            public void actionPerformed(ActionEvent e) {
                if(currentCode<newList.size()-1) {
                    currentCode++;
                }
                myPanel.repaint();
            }
        };

        Action leftAction = new AbstractAction(){
            public void actionPerformed(ActionEvent e) {
                if(currentCode>0) {
                    currentCode--;
                }
                myPanel.repaint();
            }
        };

        InputMap inputMap = myPanel.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = myPanel.getActionMap();
        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "rightAction");
        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "leftAction");
        actionMap.put("rightAction", rightAction);
        actionMap.put("leftAction", leftAction);

        f.add(myPanel);
        f.add(panel);
        f.pack();
        f.setVisible(true);
    }

    /*for code space generation*/

    public static Code shuffleNewCode() {
        ArrayList<City> newList = new ArrayList<City>();
        Random random = new Random();
        while(true) {
            ArrayList<City> buffer = new ArrayList<City>(list);
            while(buffer.size()!=1) {
                newList.add(buffer.remove(random.nextInt(buffer.size())));
            }
            newList.add(buffer.get(0));
            Code newCode = new Code(newList);
            if(isCodeUnique(newCode, codeSpace)) {
                //for(int i=0; i<newCode.size(); i++) {
                    //System.out.print(newCode.get(i).order+"-");                      //print codes
                //}
                //System.out.println();
                return newCode;
            }
        }
    }

    public static boolean isCodeUnique(Code newCode, ArrayList<Code> codeSpace) {
        if(codeSpace.size() == 0) {
            return true;
        }
        for(int j=0; j<codeSpace.size(); j++) {
            boolean isDifferent = false;
            for(int i=0; i<codeSpace.get(0).size(); i++) {
                Code buf = codeSpace.get(j);
                if(!buf.get(i).equals(newCode.get(i))) {
                    isDifferent = true;
                }
            }
            if(!isDifferent) {
                return false;
            }
        }
        return true;
    }

}

class MyPanel extends JPanel {
    private ArrayList<Code> list;
    private int fault = 10;

    public MyPanel(ArrayList<Code> list) {
        this.list = list;
        setBorder(BorderFactory.createLineBorder(Color.black));

        addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                City clicked = belongsToList(e.getX(),e.getY());
                if(clicked.x!=-100) {
                    clicked.x=e.getX();
                    clicked.y=e.getY();
                    repaint();
                }
            }
        });

        addMouseMotionListener(new MouseAdapter() {
            public void mouseDragged(MouseEvent e) {
                City clicked = belongsToList(e.getX(),e.getY());
                clicked.x=e.getX();
                clicked.y=e.getY();
                repaint();
            }
        });
    }

    private City belongsToList(int x, int y) {
        for(int i=0; i<list.get(Main.currentCode).size(); i++) {
            if(Math.sqrt(Math.pow(x-list.get(Main.currentCode).get(i).x,2)+Math.pow(y-list.get(Main.currentCode).get(i).y,2))<City.radius+fault) {
                return list.get(Main.currentCode).get(i);
            }
        }
        return new City(-100,-100,0);
    }

    public Dimension getPreferredSize() {
        return new Dimension(Main.width,Main.height);
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawGraph(g);
    }

    private void drawGraph(Graphics g) {
        g.drawString("iteration: "+Integer.toString(Main.currentCode*10),5,15);
        g.drawString("result: "+Integer.toString(list.get(Main.currentCode).distance),100,15);
        g.drawString("starting from: "+Integer.toString(list.get(Main.currentCode).get(0).order)+
                "-"+Integer.toString(list.get(Main.currentCode).get(1).order)+"-...",200,15);
        g.drawLine(list.get(Main.currentCode).get(0).x,list.get(Main.currentCode).get(0).y,
                list.get(Main.currentCode).get(list.get(Main.currentCode).size()-1).x,
                list.get(Main.currentCode).get(list.get(Main.currentCode).size()-1).y);
        for(int i=0; i<list.get(Main.currentCode).size(); i++) {
            City city = list.get(Main.currentCode).get(i);
            if(i<list.get(Main.currentCode).size()-1) {
                City next = list.get(Main.currentCode).get(i+1);
                g.drawLine(city.x,city.y,next.x,next.y);
            }
            g.setColor(Color.LIGHT_GRAY);
            drawCircle(city,g);
            g.setColor(Color.black);
            if(i+1<10) {
                g.drawString(Integer.toString(city.order),city.x-3,city.y+4);
            } else {
                g.drawString(Integer.toString(city.order),city.x-8,city.y+4);
            }
        }
    }

    private void drawCircle(City City, Graphics g) {
        g.fillOval(City.x-City.radius,City.y-City.radius,2*City.radius,2*City.radius);
        g.drawOval(City.x-City.radius,City.y-City.radius,2*City.radius,2*City.radius);
    }
}