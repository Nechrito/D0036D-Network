package model.utils;

import model.data.Location;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Geocode
{
    /**
     * Uses nominatim to download the latitude & longitude of the address
     * @param address
     * @param location
     * @return
     */
    public Map<String, Double> DownloadCoordinates(String address, Location location)
    {
        StringBuffer url = new StringBuffer();
        url.append("http://nominatim.openstreetmap.org/search?q=");

        // Swaps the empty spaces in the address with '+'
        String[] split = address.split(" ");
        for (int i = 0; i < split.length; i++)
        {
            url.append(split[i]);

            if (i < split.length - 1)
                url.append("+");
        }

        // Determines the format in which we receive the data
        url.append("&format=xml&addressdetails=1");

        HttpUtility httpUtility = new HttpUtility(url.toString());
        System.out.println("Downloading Geocodes " + url.toString());

        String responseBody;
        try
        {
            responseBody = httpUtility.GET();
        } catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }

        Document document;
        try
        {
            document = XMLParser.RetrieveFromHtml(responseBody, httpUtility.Encoding);
        } catch (ParserConfigurationException e)
        {
            e.printStackTrace();
            return null;
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }
        catch (SAXException e)
        {
            e.printStackTrace();
            return null;
        }

        return FetchGeocodes(document, location);
    }

    private Map<String, Double> FetchGeocodes(Document document, Location location)
    {

        Element rootElement = document.getDocumentElement();
        NodeList element = rootElement.getElementsByTagName("place");
        NamedNodeMap attributes;

        try
        {
            // Attempts to fetch the attributes of the "place" tag which contains geocodes
            attributes = element.item(0).getAttributes();
        }
        catch (Exception e)
        {
            System.out.println("Failed to read your input!");
            return null;
        }

        FetchLocation(document, location);

        Map<String, Double> coords = new HashMap<String, Double>();

        // iterates through the elements attributes to locate the geocodes
        for (int i = 0; i < attributes.getLength(); i++)
        {
            var node = attributes.item(i);
            var name = node.getNodeName();
            var value = node.getNodeValue();

            if (name.equals("lon"))
                coords.put("lon", Double.parseDouble(value));

            if (name.equals("lat"))
                coords.put("lat", Double.parseDouble(value));
        }

        return coords;
    }

    // Retrieves the display name for the city & country code
    private void FetchLocation(Document document, Location location)
    {
        var test = document.getElementsByTagName("town");
        if (test.getLength() <= 0)
        {
            test = document.getElementsByTagName("city");
        }

        var country = document.getElementsByTagName("country").item(0).getTextContent();
        location.City = test.item(0).getTextContent();
        location.Country = country;
    }
}
