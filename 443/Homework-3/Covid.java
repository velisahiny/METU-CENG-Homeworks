



import javax.xml.crypto.dsig.keyinfo.KeyValue;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.stream.Stream;
import java.io.IOException;
import java.text.DecimalFormat;


public class Covid
{
  // You can add your own variables between them.

  // You can add your own variables between them.
  private static final int CountryCodeIndex = 0, LocationIndex= 1, DateIndex  = 2, TotalCasesIndex = 3, NewCasesIndex=4, TotalDeathsIndex=5, NewDeathsIndex=6;
  private String zero= "0";
  // You must not change between them.
  private List<List<String>> rows;

  public Covid()
  {
    try
    {
      this.rows = Files
  				.lines(Paths.get("covid19.csv"))
  				.map(row -> Arrays.asList(row.split(",")))
  				.collect(Collectors.toList());

    }
    catch (IOException e)
    {
			e.printStackTrace();
		}
  }
  // You must not change between them.

  public void printOnlyCases(String location, String date)
  {


  int result = rows.parallelStream().filter(row->row.get(LocationIndex).equals(location)).filter(row -> row.get(DateIndex).equals(date))
          .map(row->Integer.parseInt(row.get(TotalCasesIndex))- Integer.parseInt(row.get(TotalDeathsIndex))).findFirst().orElse(0);
  System.out.printf("Result: "+ result );

  }

  public long getDateCount(String location)
  {
    long toReturn = 0;
    toReturn = rows.parallelStream().filter(row-> row.get(LocationIndex).equals(location)).count();

    return toReturn;
  }

  public int getCaseSum(String date)
  {
    int toReturn = 0;
    toReturn = rows.parallelStream().filter(row->row.get(DateIndex).equals(date)).mapToInt(row->Integer.parseInt(row.get(NewCasesIndex))).reduce(0,(n1,n2)->n1+n2);

    return toReturn;
  }

  public long getZeroRowsCount(String location)
  {
    long toReturn = 0;

    toReturn = rows.parallelStream().filter(row->row.get(LocationIndex).equals(location)).filter(row->row.get(3).equals(zero) && row.get(NewCasesIndex).equals(zero) && row.get(TotalDeathsIndex).equals(zero) && row.get(NewDeathsIndex).equals(zero)).count();
    return toReturn;
  }

  public double getAverageDeath(String location)
  {
    double toReturn = 0;
    toReturn = rows.stream().filter(row->row.get(LocationIndex).equals(location)).mapToDouble(row-> Double.parseDouble(row.get(6))).average().orElse(-1);
    toReturn = Double.parseDouble(new DecimalFormat("##.00").format(toReturn));
    return toReturn;
  }

  public String getFirstDeathDayInFirstTenRows(String location)
  {
    String toReturn = null;
    toReturn = rows.stream().filter(row->row.get(LocationIndex).equals(location)).limit(10).filter(row-> !row.get(NewDeathsIndex).equals("0")).map(row->row.get(DateIndex)).findFirst().orElse("Not Found");
    return toReturn;
  }

  public String[] getDateCountOfAllLocations()
  {
    String[] toReturn = null;
    toReturn =  rows.stream().map(Covid::mapCountryCodeLocation ).distinct().map(pair-> pair.split(":")[0]+ ": " +getDateCount((String) pair.split(":")[1]) ).toArray(String[]::new);
    return toReturn;
  }
  private static String mapCountryCodeLocation(List<String> row ){

    String pair =  row.get(CountryCodeIndex)+":"+row.get(LocationIndex);
    return pair;
  }

  public List<String> getLocationsFirstDeathDay()
  {
    List<String> toReturn = null;

    toReturn = rows.stream().filter(row->row.get(NewDeathsIndex).equals(row.get(TotalDeathsIndex)) && !row.get(NewDeathsIndex).equals(zero) ).map(row -> row.get(LocationIndex)+": "+row.get(DateIndex)).collect(Collectors.toList());

    return toReturn;
  }

  public String trimAndGetMax(String location, int trimCount)
  {
    String toReturn = null;

    List<List<String>> tempRows = rows.stream().filter(row->row.get(LocationIndex).equals(location)).sorted((e1,e2) ->Integer.parseInt( e1.get(NewCasesIndex)) - Integer.parseInt(e2.get(NewCasesIndex))).skip(trimCount).collect(Collectors.toList());
    tempRows = tempRows.stream().limit(tempRows.size()-trimCount).collect(Collectors.toList());
    toReturn = tempRows.stream().sorted((e1,e2) ->Integer.parseInt( e1.get(NewDeathsIndex)) - Integer.parseInt(e2.get(NewDeathsIndex)))
            .max((e1,e2) ->Integer.parseInt( e1.get(NewDeathsIndex)) - Integer.parseInt(e2.get(NewDeathsIndex))).map(row->row.get(DateIndex)+": "+ row.get(NewDeathsIndex) ).orElse(null);
    return toReturn;
  }

  public List<List<String>> getOnlyCaseUpDays(String location)
  {
    List<List<String>> toReturn = null;
    toReturn = rows.stream().filter(row->row.get(LocationIndex).equals(location)).filter(row-> !row.get(NewCasesIndex).equals(zero)).collect(Collectors.toList());
    System.out.printf("Result: "+toReturn.size());
    return toReturn;
  }

  public static void main(String[] args)
  {
    // You can test your function in here.
    // This part is not graded.
    Covid covid = new Covid();
    Arrays.stream(covid.getDateCountOfAllLocations()).forEach(System.out::println);








  }
}
