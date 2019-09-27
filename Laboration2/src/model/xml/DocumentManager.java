package model.xml;

import model.data.Location;
import model.utils.Geocode;
import model.utils.HttpUtility;
import model.utils.TimeFormat;
import model.utils.XMLParser;
import org.w3c.dom.*;
import org.w3c.dom.traversal.DocumentTraversal;
import org.w3c.dom.traversal.NodeFilter;
import org.w3c.dom.traversal.NodeIterator;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.Map;

public class DocumentManager
{
    public Location Location;
    public Document Document;
    public Element Element;

    public boolean HadToDownload;

    private String city;
    private String time;

    /**
     * Retrieves weather & geocodes from the city provided
     * Uses cache if time is within a 4-hour period of local data
     * @param city
     * @param time
     */
    public DocumentManager(String city, String time)
    {
        this.city = city;
        this.time = time;
        this.Location = new Location();

        Geocode geocode = new Geocode();
        Map<String, Double> coordinates;
        coordinates = geocode.DownloadCoordinates(city, this.Location);
        if (coordinates == null)
            return;

        Double latitude = coordinates.get("lat");
        Double longitude = coordinates.get("lon");

        Location.Latitude = latitude.toString();
        Location.Longitude = longitude.toString();

        // Local xml containing weather data
        File file = FileManager.RetrieveWeatherFile();

        // Parse the xml into the a class of type Document
        this.Document = XMLParser.RetrieveFromFile(file);
        if (this.Document != null)
            this.Element = GetElement(new CacheFilter(time, latitude, longitude));

        if (this.Document != null && this.Element != null)
        {
            HadToDownload = false;
            return;
        }

        HadToDownload = true;
        var url = "https://api.met.no/weatherapi/locationforecast/1.9/.xml?lat=" + latitude + "&lon=" + longitude;
        System.out.println("Downloading Weather " + url);

        // Download
        HttpUtility httpUtility = new HttpUtility(url);
        String html;
        try
        {
            html = httpUtility.GET();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return;
        }

        try
        {
            this.Document = XMLParser.RetrieveFromHtml(html, httpUtility.Encoding);
            this.Element = this.GetElement(new FromURLFilter(time));
        }
        catch (ParserConfigurationException e)
        {
            e.printStackTrace();
            return;
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return;
        }
        catch (SAXException e)
        {
            e.printStackTrace();
            return;
        }
    }

    private Element GetElement(NodeFilter nodeFilter)
    {
        // Provides methods to iterate through nodes
        DocumentTraversal traversal = (DocumentTraversal) this.Document;

        // Allows us to iterate through the documents nodes limited by our custom filter
        NodeIterator iterator = traversal.createNodeIterator(this.Document.getDocumentElement(), NodeFilter.SHOW_ELEMENT, nodeFilter, true);

        for (Node node = iterator.nextNode(); node != null; node = iterator.nextNode())
        {
            return (Element) node;
        }
        return null;
    }
}


class CacheFilter implements  NodeFilter
{
    private String time;
    private Double latitude;
    private Double longitude;

    private boolean nextNodeValid;

    /**
     * Attempts to find an element in the XML file if possible
     * @param time
     * @param latitude
     * @param longitude
     */
    CacheFilter(String time, Double latitude, Double longitude)
    {
        this.time = time;
        this.latitude = latitude;
        this.longitude = longitude;
    }

    @Override
    public short acceptNode(Node node)
    {
        String nodeName = node.getNodeName();

        if (nextNodeValid)
            return NodeFilter.FILTER_ACCEPT;

        if (nodeName.equals("time"))
        {
            Node attribute = node.getAttributes().item(1);

            var fileTime = TimeFormat.FormatISO(attribute.getTextContent(), "dd-MM-yy HH:mm:ss");
            var localTime = TimeFormat.FormatISO(time, "dd-MM-yy HH:mm:ss");

            if (fileTime.compareTo(localTime) >= 4) // Only seems to compare hours and not days etc. but too late to change
            {
                return NodeFilter.FILTER_REJECT;
            }

            NodeList children = node.getChildNodes();

            for (int i = 0; i < children.getLength(); i++)
            {
                Node child = children.item(i);

                if (child.getNodeName() == "location")
                {
                    NamedNodeMap attributes = child.getAttributes();

                    Node lat = attributes.item(1);
                    Node lon = attributes.item(2);

                    double latDouble = Double.parseDouble(lat.getTextContent());
                    double lonDouble = Double.parseDouble(lon.getTextContent());

                    if (Compare(latitude, latDouble) && Compare(longitude, lonDouble))
                    {
                        System.out.println("Found cache which is " + fileTime.compareTo(localTime) + " hours behind");
                        nextNodeValid = true;
                    }
                }
            }
        }
        return NodeFilter.FILTER_REJECT;
    }

    private boolean Compare(Double first, Double second)
    {
        return  Math.abs(first - second) <= 1e-3; // Tolerance, new geocode might differ a tiny bit 
    }
}

class FromURLFilter implements NodeFilter
{
    private String time;

    FromURLFilter(String time)
    {
        this.time = "from=" + '"' + time + '"';
    }

    @Override
    public short acceptNode(Node node)
    {
        String nodeName = node.getNodeName();

        if (nodeName.equals("time"))
        {
            // locate the "from" time attribute
            Node attribute = node.getAttributes().item(1);

            if (attribute.toString().equals(time))
            {
                return NodeFilter.FILTER_ACCEPT;
            }
        }
        return NodeFilter.FILTER_REJECT;
    }
}