package model.utils;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;

public class XMLParser
{
    public static Document RetrieveFromHtml(String data, String encoding) throws ParserConfigurationException, IOException, SAXException
    {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();

        // Stream which reads the bytes from the stringbuffer data
        byte[] buffer = data.getBytes(encoding);
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(buffer);

        // Converts the buffer into a document
        Document document = documentBuilder.parse(byteArrayInputStream);
        document.normalize(); // Reduces redundant lines for elements and attributes

        return document;
    }

    public static Document RetrieveFromFile(File file)
    {
        // The API for DOM which allows us to parse the XML
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder;
        try
        {
            documentBuilder = factory.newDocumentBuilder();
        } catch (ParserConfigurationException e)
        {
            e.printStackTrace();
            return null;
        }

        // Converts the xml to 'Document' which provides methods to read/write to the xml
        Document document;
        try
        {
            document = documentBuilder.parse(file);
            document.normalize();
        }
        catch (SAXException e)
        {
            e.printStackTrace();
            return null;
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }

        return document;
    }
}
