package model.xml;

import model.utils.XMLParser;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;

public class FileManager
{
    private static String directory = "src/resources/";
    private static String weatherPath = directory + "weather.xml";

    public static File RetrieveWeatherFile()
    {
        return new File(weatherPath);
    }

    /**
     * Appends the element to the root tag 'product' 
     * @param element
     */
    public static void SaveToCache(Element element)
    {
        Document document = XMLParser.RetrieveFromFile(RetrieveWeatherFile());
        Element root = document.getDocumentElement();

        NodeList products = root.getElementsByTagName("product");
        Node product = products.item(0);
        Node node = document.importNode(element, true);
        product.appendChild(node);

        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer;
        try
        {
            transformer = transformerFactory.newTransformer();
        }
        catch (TransformerConfigurationException e)
        {
            e.printStackTrace();
            return;
        }

        StreamResult result = new StreamResult(weatherPath);
        DOMSource source = new DOMSource(document);

        try
        {
            transformer.transform(source, result);
            return;
        }
        catch (TransformerException e)
        {
            e.printStackTrace();
            return;
        }
    }
}
