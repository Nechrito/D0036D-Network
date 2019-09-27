package view;

import model.Server;

import javax.swing.*;
import java.awt.*;

public class Controller extends JFrame
{
    /* Components */
    private JPanel mainPanel;
    private JButton button1;
    private JButton button2;
    private JButton button3;
    private JButton button4;
    private JTextField textField1;
    private JButton setButton;

    public Controller()
    {
        setTitle("Server - Philip Lindh");
        add(mainPanel);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);

        Server server = new Server();
        server.start();

        button1.addActionListener(actionEvent -> server.SendMessage("SET_ALL_RANDOM"));
        button2.addActionListener(actionEvent -> server.SendMessage("SET_ALL_WHITE"));
        button3.addActionListener(actionEvent -> server.SendMessage("SET_ALL_BLACK"));
        button4.addActionListener(actionEvent -> server.SendMessage("SET_ALL_BLUE"));
        setButton.addActionListener(actionEvent -> server.SendMessage(textField1.getText()));
    }
}
