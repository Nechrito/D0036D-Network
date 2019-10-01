package controller;

import model.data.Weather;
import model.xml.DataManager;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class FetchPressed
{
    private DataManager dataManager;

    private JTextField city;
    private JTextField time;
    private Information information;

    public FetchPressed(JTextField city, JTextField time, Information information)
    {
        this.city = city;
        this.time = time;
        this.information = information;

        String[] citiesInFrontPage = { "Stockholm", "Skelleftea", "Shanghai", "Beijing", "Istanbul", "Tokyo", "Moscow",  };
        for (String fCity : citiesInFrontPage)
        {
            this.dataManager = new DataManager();
            var weather = dataManager.Retrieve(fCity, "");
            if (weather != null)
                AddToTable(weather);
        }
    }

    public void OnFetchPressed(ActionEvent actionEvent)
    {
        this.dataManager = new DataManager();
        var weather = dataManager.Retrieve(city.getText(), time.getText());
        if (weather == null)
            return;

        AddToTable(weather);
        city.setText("");
        time.setText("");
    }

    private void AddToTable(Weather weather)
    {
        String[] data = { weather.Date, weather.Location.Country, weather.Location.City, weather.Temperature, weather.WindDirection, weather.WindSpeed, weather.WindMS, weather.Humidity, weather.Pressure, weather.Cloudiness, weather.Fog, };
        information.Refresh(data);
    }
}
