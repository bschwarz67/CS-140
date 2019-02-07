package cs_2150_project_Bryan_Schwarz;

import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Iterator;

public class MediaListManager {
	
	LinkedList<Media> masterList = new LinkedList<>();
	
	//sets masterList of MediaListManager object
	public void setMediaList(LinkedList<Media> masterList) {
		this.masterList = masterList;
	}
	
	//prints masterList. Used after list is created for the first time to show all data parsed from file.
	//Indicates the number of items parsed from the data file initially.
	public void displayMediaList() {
		for(int i = 0; i < masterList.size(); i++) {
			System.out.println(masterList.get(i));
		}
		System.out.println("\nNumber of items in the master list: " + masterList.size() + "\n");
	}
	
	
	//prints the filtered list. Indicates the number of items that match the filter list after printing the filtered
	//list
	private void displayMediaList(LinkedList<Media> filteredList) {
		for(int i = 0; i < filteredList.size(); i++) {
			System.out.println(filteredList.get(i));
		}
		System.out.println("\nNumber of items that match the current filter list: " + filteredList.size() + "\n");
	}
	
	
	//checks to see if a string containing a title exists as a target of a filter object in a list of title filters
	private boolean existsIn(String title, LinkedList<Filter> titleFilters) {
		for (Filter x : titleFilters) {
			if(title.equals(x.getTarget())) {
				return true;
			}
		}
		return false;
	}
	
	//Iterates through master list. For each element in the master list, if it satisfies all filters in the filter
	//list, the element is added the current list of media objects, and the list is printed after checking 
	//each element in the list.
	public void filterMedia(ArrayList<Filter> filterList) {
		LinkedList<Filter> titleFilters = new LinkedList<>();
		LinkedList<Media> currentList = new LinkedList<>();
		
		for(Filter x : filterList) { //add all title filters in the filter list to the title filter list.
			if (x.getField().equals("title")) {
				titleFilters.add(x);
			}
		}
		
		Iterator<Media> itr = masterList.iterator();
		if(!filterList.isEmpty()) { //iterate through, filter masterList if there are filters to use in filterList
			while(itr.hasNext()) {
				boolean addToCurrent = true;
				Media currentElement = itr.next();
				for(Filter currentFilter : filterList) { //for every filter in the current filterList, check if the current
											//element in the masterList satisfies all of the filters, if it does,
											//add it to the currentList
					
					
					if(currentFilter.getField().equals("genre")) { //if the field in currentFilter is genre, check if the
														//genre of currentElement is the same as the genre of
														//designated by the filter, if not, addToCurrent is set to 
														//false and the filtering loop for currentElement is broken 
														//as this filter is not satisfied
						if(!currentElement.getGenre().equals(currentFilter.getTarget())) {
							addToCurrent = false;
							break;
						}
						
					}
					
					else if(currentFilter.getField().equals("rating")) {//if the field in currentFilter is rating, 
						//rating of the currentElement satisfies the designation of the filter if not, 
						//addToCurrent is set to false and the filtering loop for currentElement is broken as this filter
						//is not satisfied
						
						
						//checks that rating of currentElement is greater than the rating designated by the filter
						if(currentFilter.getRelation().equals(">")) {
							if(!(currentElement.getRating() > Double.parseDouble(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file,
							//thus this object is excluded
							else if(currentElement.getRating() < 0) {
								addToCurrent = false;
								break;
							}
							
						}
						//checks that rating of currentElement is less than the rating designated by the filter
						else if(currentFilter.getRelation().equals("<")){
							
							if(!(currentElement.getRating() < Double.parseDouble(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file,
							//thus this object is excluded
							else if(currentElement.getRating() < 0) {
								addToCurrent = false;
								break;
							}
							
						}
					}
						
					
					else if (currentFilter.getField().equals("year")){ //if the field in currentFilter is year, check that
						//year of the currentElement satisfies the designation of the filter. If not, addToCurrent 
						//is set to false and the filtering loop for currentElement is broken as this filter
						//is not satisfied
						
						
						//if currentElement is a movie, checks that its beginYear is greater than the year designated by the filter
						if(currentFilter.getRelation().equals(">") && (currentElement.getGenre().equals("movie") || currentElement.getGenre().equals("unknown"))) {
							if(!(currentElement.getBeginYear() > Integer.parseInt(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file, thus this object is excluded
							else if(currentElement.getBeginYear() < 0) {
								addToCurrent = false;
								break;
							}
	
								
						}
						//if currentElement is a series, checks that its beginYear is greater than the year 
						//designated by the filter 
						else if(currentFilter.getRelation().equals(">") && currentElement.getGenre().equals("series")) {
							if(!(currentElement.getBeginYear() > Integer.parseInt(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file, 
							//thus this object is excluded
							else if(currentElement.getBeginYear() < 0) {
								addToCurrent = false;
								break;
							}
							
						}
						//if currentElement is a movie, checks that its beginYear is less than the year designated by the filter
						else if(currentFilter.getRelation().equals("<") && (currentElement.getGenre().equals("movie") || currentElement.getGenre().equals("unknown"))) {

							if(!(currentElement.getBeginYear() < Integer.parseInt(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file, thus this object is excluded
							else if(currentElement.getBeginYear() < 0) {
								addToCurrent = false;
								break;
							}
						}
						//if currentElement is a series, checks that its endYear is less than the year designated 
						//by the filter 
						else if(currentFilter.getRelation().equals("<") && currentElement.getGenre().equals("series")) {

							if(!(currentElement.getEndYear() < Integer.parseInt(currentFilter.getTarget()))) {
								addToCurrent = false;
								break;
							}
							//a -1 value for beginYear indicates that there was no such value in the text file,
							//thus this object is excluded
							else if(currentElement.getBeginYear() < 0) {
								addToCurrent = false;
								break;
							}
						}
						
						
					}					
				}
				//in the case that currentElementt satisfies all filters in the filterList besides the
				//titleFilterList, and there are designated title filters, check if its title satisfies
				//one of the title filters. If not, object is excluded from currentList.
				if(titleFilters.size() > 0) {
					if(!existsIn(currentElement.getName(), titleFilters)) {
						addToCurrent = false;
					}	
				}
				if(addToCurrent == true) { //addToCurrent will be true if and only if currentElement
					//satisfies all filters designated by user, thus add this object to currentList
					currentList.add(currentElement);
				}
			}
			displayMediaList(currentList); //display updated list
			
		}
		else {
			displayMediaList(masterList); //no filter to update list with, display master list
		}
				
	}
}		
		
	
	
	
	