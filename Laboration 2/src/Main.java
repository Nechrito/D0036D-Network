import view.WeatherAnalysis;

import javax.swing.*;

public class Main
{
    public static void main(String[] args) throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException
    {
        /* Changes the theme to something a bit more modern */
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

        /* Runs a new Runnable instance which invokes the GUI on the 'Event Dispatch Thread' */
        SwingUtilities.invokeLater(() ->
        {
            /* Creates a new instance of the GUI */
            WeatherAnalysis form = new WeatherAnalysis();
        });
    }
}
