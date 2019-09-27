package model.utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpUtility
{
    public String Url;
    public String Encoding;

    public HttpUtility(String url)
    {
        this.Url = url;
    }

    public String GET() throws IOException
    {
        URL urlObj = new URL(this.Url);

        HttpURLConnection connection = (HttpURLConnection) urlObj.openConnection();

        String redirect = connection.getHeaderField("Location");
        if (redirect != null)
        {
            connection = (HttpURLConnection) new URL(redirect).openConnection();
        }

        // For some reason i get the following error: java.lang.IllegalStateException: connect in progress
        // If I set req to GET
        //System.out.println("Sending 'GET' request to: " + this.Url);
        //connection.setRequestMethod("GET");

        int responseCode = connection.getResponseCode();
        if (responseCode != 200)
        {
            System.out.println("Failed, response: " + responseCode);
            return null;
        }

        InputStreamReader inputStreamReader = new InputStreamReader(connection.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
        StringBuffer stringBuffer = new StringBuffer();

        String inputLine;
        while ((inputLine = bufferedReader.readLine()) != null)
        {
            stringBuffer.append(inputLine);
        }


        this.Encoding = inputStreamReader.getEncoding();

        bufferedReader.close();
        inputStreamReader.close();

        return stringBuffer.toString();
    }
}
