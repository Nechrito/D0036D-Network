package model.xml;

import model.data.Weather;
import model.utils.TimeFormat;
import org.w3c.dom.Element;

public class DataManager
{
    public Weather Retrieve(String city, String time)
    {
        Weather weatherData = new Weather();

        if (time.isEmpty())
        {
            time = TimeFormat.GetCurrentDate("HH:mm");
        }

        String iso = TimeFormat.TryConvertToISO(time);
        if (iso != null)
        {
            time = iso;
            weatherData.Date = TimeFormat.FormatISO(time, "dd-MM-yyyy HH:mm");
        }

        DocumentManager documentManager = new DocumentManager(city, time); // Downloads the Document & retrieves the Element we're searching for
        Element element = documentManager.Element;

        if (element == null)
        {
            System.out.println("Failed to retrieve the requested data, try a date like: 'September 17, 2019' or a time such as '15:30'");
            return null;
        }

        // Save to local xml file
        if (documentManager.HadToDownload)
        {
            FileManager.SaveToCache(element);
        }

        // This is a tad ugly/nested, but hey it works
        weatherData.Location = documentManager.Location;

        weatherData.Temperature   = SetWeatherData(element, "temperature", 2); // celsius
        weatherData.WindDirection = SetWeatherData(element, "windDirection", 0);// degrees
        weatherData.WindSpeed     = SetWeatherData(element, "windSpeed", 3); // name, like "Lett bris"
        weatherData.WindMS        = SetWeatherData(element,"windSpeed", 2); // milliseconds
        weatherData.Humidity      = SetWeatherData(element,"humidity", 1); // Percent
        weatherData.Pressure      = SetWeatherData(element,"pressure", 2); // hPa
        weatherData.Cloudiness    = SetWeatherData(element,"cloudiness", 1); // Percent
        weatherData.Fog           = SetWeatherData(element,"fog", 1); // Percent

        return weatherData;
    }

    private String SetWeatherData(Element element, String tag, int index)
    {
        try
        {
            return element.getElementsByTagName(tag).item(0).getAttributes().item(index).getTextContent();
        }
        catch (Exception e)
        {
            System.out.println("Failed to retrieve " + tag);
        }
        return "?";
    }
}