package cs_2150_project_Bryan_Schwarz;
import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DataFileReader {

	public LinkedList<Media> readFile(String filename) throws IOException {
		BufferedReader movieFileStream = null;
		LinkedList<Media> medias = new LinkedList<>();
		String line = ""; //hold data from line in file
		String title = ""; 
		String beginYear = ""; 
		String endYear = ""; 
		String rating = "";
		String durationType = "";
		
		int intBeginYear = 0;
		int intEndYear = 0;
		double doubleRating = 0.0;
		
		try { //try to open file of name filename using buffered reader
			movieFileStream = new BufferedReader(new FileReader(filename));
		} 
		catch (FileNotFoundException e) { //exception if file not found
			e.printStackTrace();
		}
		
		while((line = movieFileStream.readLine()) != null) { //loop to parse data executes until end of file
			
			
			//parse out title of the movie/series out of the line
			title = line.split("\\|")[0]; //split 
			title = line.split("\\([0-9]?")[0];
			title = title.trim();
			
			
			String year = "";
			try { // from line parse begin Year, or begin year and end year out of the line string if one or both exist
				
				
				//compile a regex to search for the begin year or begin year and end year in the line
				String allMatches;
				Matcher m = Pattern.compile("\\([0-9][0-9][0-9][0-9][-]?[0-9]?[0-9]?[0-9]?[0-9]?\\)").matcher(line);
				if (m.find()) { //assign year string to found pattern if pattern matches
					allMatches = m.group();
					year = allMatches;
					if(year.contains("-")) { //in case that there is begin and end year, parse the begin and end year
						beginYear = year.split("-")[0];
						endYear = year.split("-")[1];
						beginYear = beginYear.split("\\(")[1];
						endYear = endYear.split("\\)")[0];
						intBeginYear = Integer.parseInt(beginYear);
						intEndYear = Integer.parseInt(endYear);
					}
					else if (year.length() > 0) { //in case that year exists in line, but has no end year, parse the begin year
						beginYear = year.split("\\(")[1];
						beginYear = beginYear.split("\\)")[0];
						intBeginYear = Integer.parseInt(beginYear);
						intEndYear = intBeginYear;
					}
				}
				else { //if no pattern matching begin or begin-end year found, throw exception
					throw new IOException();
				}
			}
			catch (IOException e) { //in case of exception, assign begin year and end year value to -1
				intBeginYear = -1;
				intEndYear = -1;
			}
			
			try {//from line parse rating of movie or series as double
				rating = line.split("\\|")[1];
				rating = rating.split(",")[0];
				rating = rating.trim();
				rating = rating.split(" ")[0];
				
				doubleRating = Double.parseDouble(rating);
			}
			catch (NumberFormatException e) { //if rating is blank, assign rating to -1
				doubleRating = -1;
			}
			
			
			try { //from line parse out a unit of the duration in order to later determine if line has data of a movie or series
				durationType = line.split("\\|")[1];
				durationType = durationType.split(",")[1];
				durationType = durationType.trim();
				durationType = durationType.split(" ")[1];
				
			}
			
			//parse out duration type for cases in which string containing duration has no inner white spaces or
			//is blank
			catch(ArrayIndexOutOfBoundsException e) {
				if(durationType.length() > 0 && !durationType.contains(" ")) {
					durationType = durationType.split("[0-9][0-9]?")[1];

				}
				
				else {
					durationType = "";
				}
				
			}
			
			
			//assign data in current line to Series object based on duratationType, add data to mediaList
			if (durationType.matches("Season|Seasons|Episode|Episodes|episodes|Collection|Collections|Chapter|Set|Chapters|Series|Volume|Volumes|Part|Parts|Special")) {
				medias.add(new Series(title, "series", doubleRating, intBeginYear, intEndYear));
			}
			
			//assign data in current line to Movie object based on duratationType, add data to mediaList, in this case
			//actual genre is unknown
			else if (durationType.equals("")){
				medias.add(new Movie(title, "unknown", doubleRating, intBeginYear));
			}
			
			//assign data in current line to Movie object based on duratationType, add data to mediaList
			else {
				medias.add(new Movie(title, "movie", doubleRating, intBeginYear));
			}
			
		}
		return medias; //method return a mediaList of parsed data
	}
}

