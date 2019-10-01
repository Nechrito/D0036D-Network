package controller;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import java.awt.*;

public class Information
{
    private String[] headers = { "Date", "Country", "City", "Temperature", "Wind Direction", "Wind Speed", "Wind MS", "Humidity", "Pressure", "Cloudiness", "Fog" };

    private JScrollPane jScrollPane;
    private JTable jTable;
    private DefaultTableModel tableModel;
    private int colCount = 0;

    public Information(JScrollPane jScrollPane, JTable jTable)
    {
        this.jScrollPane = jScrollPane;
        this.jTable = jTable;
        this.tableModel = (DefaultTableModel)this.jTable.getModel();
        this.tableModel.setColumnIdentifiers(headers);
    }

    public void Refresh(String[] data)
    {
        tableModel.insertRow(colCount, data);
        colCount++;
    }
}
