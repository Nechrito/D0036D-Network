package view;

import controller.FetchPressed;
import controller.Information;

import javax.swing.*;
import java.awt.*;

public class WeatherAnalysis extends JFrame
{
    /* Form Components */
    private JPanel panelMain;
    private JButton buttonFetch;
    private JTable tableMain;
    private JScrollPane scrollpaneMain;
    private JTextField textfieldCity;
    private JTextField textfieldDate;

    /* Extensions */
    FetchPressed fetchPressed;
    private Information information;

    public WeatherAnalysis()
    {

        /* Starts the GUI Form with config */
        setTitle("Weather Analysis Client - Philip Lindh");
        add(panelMain);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(1020, 720));
        pack();
        setVisible(true);

        /* Declarations */
        information = new Information(scrollpaneMain, tableMain);
        fetchPressed = new FetchPressed(textfieldCity, textfieldDate, information);

        /* Event listeners */
        buttonFetch.addActionListener(fetchPressed::OnFetchPressed);
    }
}