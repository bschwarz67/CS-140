package cs_2150_project_Bryan_Schwarz;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {
	public static void main(String [] args) {
		Scanner scnr = new Scanner(System.in);
		
		
		MediaListManager mediaManager = new MediaListManager(); //mediaManager created to contain, edit list of movies, shows
		FilterListManager filterManager = new FilterListManager(scnr); //filterManager created to contain, edit list of filters
		DataFileReader rdr = new DataFileReader(); // dataFileReader object created to read and parse text file with data
		

		
		
		try { //try-catch tries to open and parse textfile
			mediaManager.setMediaList(rdr.readFile("NetflixUSA_Oct15_cleaned.txt")); 
		}
		catch(IOException e) { //if the filehandle is incorrect,IOException caught, tells user to replace string with correct filename
			e.printStackTrace();
			System.out.println("No file found, please replace file name with correct file.");
			return;
		}
		
		mediaManager.displayMediaList(); //initial list of all movies displayed
		while(true) { //until "exit" entered by user, user prompted to choose a filter to add or remove, mediaList updated and 
						//printed as a newly filtered list
			
			filterManager.displayCurrentFilters(); //filters in use
			filterManager.displayPossibleFilters(); //filters to choose from
			
			if(filterManager.updateFilter() == true) { //if a filter was successfully added or removed, update mediaList to match
														//current filters
				mediaManager.filterMedia(filterManager.getCurrentFilters());
			}
			
			
			
			 

			
			

		}
	}
}
