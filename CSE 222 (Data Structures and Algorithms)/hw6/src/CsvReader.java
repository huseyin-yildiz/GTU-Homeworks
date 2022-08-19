 import java.io.*;

 /**
  * A reader class for csv files
  */
 public class CsvReader {

     private String line;
     private BufferedReader reader;

     /**
      * Constructor for the CSVReader class
      * @param fileName fileName to be read
      * @throws Exception if the file is not found
      */
     public CsvReader(String fileName) throws Exception {

         line = new String("");
         try {
             reader = new BufferedReader(new FileReader(fileName));
         } catch (FileNotFoundException e) {
             e.printStackTrace();
             //throw new Exception("The file can not be found");
         }

         reader.readLine();
     }

     /**
      * returns the lines one by one
      * @return line strings
      */
     public String[] getLine(){
         try
         {
             String[] parts = new String[6];

             if(reader != null)
                line = reader.readLine();
             if (line != null) {
                 String[] s1 = line.split("\"\\[\"\"")[0].split(",");
                parts[0] = s1[1];
                String[] s2 = line.split("\"\\[\"\"")[1].split("\"\"]\"");
                parts[1] = s2[0];
                String[] s3 = s2[1].split(",");
                parts[2] = s3[1];
                parts[3] = s3[2];
                parts[4] = s3[3];
                parts[5] = s3[4];
                return parts;
             }
         }
         catch (IOException e)
         {
             e.printStackTrace();
         }
        return null;
     }



     public static void main(String[] args)
     {

         try {
             CsvReader csvReader = new CsvReader("e-commerce-samples.csv");
             for(String line:csvReader.getLine())
                System.out.println(line);
         } catch (Exception e) {
             e.printStackTrace();
         }
     }
}
