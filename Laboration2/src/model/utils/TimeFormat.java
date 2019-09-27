package model.utils;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

public class TimeFormat
{
    public static String isoPattern = "yyyy-MM-dd'T'HH:mm:ss'Z'";

    /**
     * Retrieves the date from an ISO-8601 pattern into a pattern of choice
     * @param input
     * @param pattern
     * @return
     */
    public static String FormatISO(String input, String pattern)
    {
        DateTimeFormatter inputFormat = DateTimeFormatter.ofPattern(isoPattern, Locale.ENGLISH);
        DateTimeFormatter outputFormat = DateTimeFormatter.ofPattern(pattern, Locale.ENGLISH);
        LocalDateTime date = LocalDateTime.parse(input, inputFormat);
        return outputFormat.format(date);
    }

    /**
     * Retrieves the current date with the pattern specified
     * @param pattern
     * @return
     */
    public static String GetCurrentDate(String pattern)
    {
        SimpleDateFormat formatter= new SimpleDateFormat(pattern);
        Date date = new Date(System.currentTimeMillis());
        return formatter.format(date);
    }

    /**
     * Tries to convert an input to the ISO format by trying out several date patterns
     * @param input
     * @return
     */
    public static String TryConvertToISO(String input)
    {
        String[] dateFormats = { "MMMM d, yyyy", "MMMM d yyyy", "dd-MM-yy", "dd-MM-yyyy", "MM-dd-yyyy", "yyyy-MM-dd",  };

        // Try date formats
        for (String format : dateFormats)
        {
            String iso = ToISO(input, format);
            if (iso == null)
                continue;

            return iso;
        }

        String[] timeFormats = { "HH", "HH:mm", "HH:mm:ss"  };

        String forcedPattern = "yyyy-MM-dd";
        SimpleDateFormat formatter= new SimpleDateFormat(forcedPattern);
        Date date = new Date(System.currentTimeMillis());
        String dateToday = formatter.format(date);

        // Try time formats
        for (String format : timeFormats)
        {
            String iso = ToISO(dateToday + ' ' + input, forcedPattern + ' ' + format);
            if (iso == null)
                continue;

            return iso;
        }

        return null;
    }

    /**
     * Converts a given date into the ISO 8601 format used for the weather API
     * @param input
     * @param pattern
     * @return
     */
    private static String ToISO(String input, String pattern)
    {
        DateFormat format = new SimpleDateFormat(pattern, Locale.ENGLISH);
        Date date = null;
        try
        {
            date = format.parse(input);
        }
        catch (ParseException e)
        {
            // ignored
        }

        if (date == null)
            return null;

        DateFormat df = new SimpleDateFormat(isoPattern);
        df.setTimeZone(TimeZone.getTimeZone("Europe/Stockholm"));
        return df.format(date);
    }
}
