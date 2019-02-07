package cs_2150_project_Bryan_Schwarz;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;

public class FilterListManager {
	ArrayList<Filter> currentFilters = new ArrayList<>(); //list of valid filters being used, w/ targets
	ArrayList<Filter> possibleFilters = new ArrayList<>(); //list of all possible filters
	Scanner scnr;
	
	FilterListManager(Scanner scnr) {
		//initialize filters w/out targets to put in possible filters
		possibleFilters.add(new Filter("genre","=","series"));
		possibleFilters.add(new Filter("genre","=","movie"));
		possibleFilters.add(new Filter("title","=",""));
		possibleFilters.add(new Filter("year",">",""));
		possibleFilters.add(new Filter("year","<",""));
		possibleFilters.add(new Filter("rating",">",""));
		possibleFilters.add(new Filter("rating","<",""));
		Collections.sort(possibleFilters);
		this.scnr = scnr;
	}
	
	
	//return current filters in use
	public ArrayList<Filter> getCurrentFilters() {
		return currentFilters;
	}
	
	
	//prints list of the current filters in use
	public void displayCurrentFilters() {
		
		System.out.println("Filters in use: ");
		for(Filter x : currentFilters) {	
			System.out.println(x.getField() + " " + x.getRelation() + " " + x.getTarget());
		}
		
	}
	//displays possible filters as initialized in constructor.
	public void displayPossibleFilters() {
		int i = 1;

		System.out.println("Possible filters: ");
		for(Filter x : possibleFilters) {
			System.out.println(i + ". " + x.getField() + " " + x.getRelation() + " " + x.getTarget());
			i++;
		}
		
	}

	//function validates input and creates a filter if input is valid. If filter type exists in
	//possible filter list, adds filter to the filter list.
	//If it is not a title filter, the filter will replace a previous filter  of the same field and relation.
	//If a title filter, is added to the list if a filter of same field, relation, target does not exist in current
	public boolean updateFilter() {
		String operation = "";
		String field = "";
		String relation = "";
		String target = "";
		System.out.println("To add a filter enter \"add\" then a filter from the possible filters menu.");
		System.out.println("To remove a filter enter \"remove\" then a filter from the in use menu.");
		System.out.println("If filtering something besides genre, enter a target beside the field and relation.");
		System.out.println("To quit program, enter \"exit\".");
		
		try {//validate input for the operation to be done, adding a filter, removing a filter, or exiting the 
			//program
			operation = scnr.next();
			if(!operation.equals("add") && !operation.equals("remove") && !operation.equals("exit")) {
				throw new IOException();
			}
			if(operation.equals("exit")) {
				System.exit(0);
			}
		}
		catch (IOException e) {
			System.out.println("\nERROR : Improper input for operation, please enter proper input\n");
			scnr.nextLine();
			return false;
		}
		
		try {//validate input for the field type of the filter to be added or removed, must match
			//field in existing filter types
			field = scnr.next();
			if(!field.equals("genre") && !field.equals("rating") && !field.equals("title") && !field.equals("year")) {
				throw new IOException();
			}
		}
		catch (IOException e) {
			System.out.println("\nERROR : Improper input for field, please enter proper input\n");
			scnr.nextLine();
			return false;
		}
		
		try {//validate input for the relation type of the filter to be added or removed, must match
			//relation in existing filter types
			relation = scnr.next();
			if(!relation.equals(">") && !relation.equals("<") && !relation.equals("=")) {
				throw new IOException();
			}
		}
		catch (IOException e) {
			System.out.println("\nERROR : Improper input for relation, please enter proper input\n");
			scnr.nextLine();
			return false;
		}

		try {
			target = scnr.next();
			if(field.equals("genre")) {//validate input for the target if the filter to be added or removed
									//has genre for its field
				if(!target.equals("movie") && !target.equals("series")) {
					throw new IOException();
				}
			}
			else if(field.equals("rating")) {//validate input for the target if the filter to be added or removed
				//has rating for its field
				double ratingInput = 0;
				try {
					ratingInput = Double.parseDouble(target);
				}
				catch(NumberFormatException e) {
					System.out.println("\nERROR : Improper input for target, please enter proper input\n");
					scnr.nextLine();
					return false;
				}
				if(ratingInput > 5.0 || ratingInput < 0.0) {
					throw new IOException();
				}
				
			}
			
			else if(field.equals("year")) {//validate input for the target if the filter to be added or removed
				//has year for its field
				int yearInput = 0;

				try {
					yearInput = Integer.parseInt(target);
				}
				catch(NumberFormatException e) {
					System.out.println("\nERROR : Improper input for target, please enter proper input\n");
					scnr.nextLine();
					return false;
				}
				if(yearInput > 2013 || yearInput < 1914) {
					throw new IOException();
				}
			}
			else {//if filter is title filter, reads the entire title, concatenates to one string
				String titleString = scnr.nextLine();
				
				target += titleString;
			}
			
		}
		catch (IOException e) {
			System.out.println("\nERROR : Improper input for target, please enter proper input\n");
			return false;
		}
		
		//if all input is valid, create new filter with input data
		Filter newFilter = new Filter(field, relation, target);
		
		//add filter to the list of current filters if filter of same field and relation exist in possible filters
		//and filter of same field, relation does not exist in current filters
		if(operation.equals("add") && existsIn(newFilter, possibleFilters) && !existsIn(newFilter, currentFilters)) {
			
			currentFilters.add(newFilter);
			Collections.sort(currentFilters);
			return true;
		}
		//add filter to the list of current filters if filter of same field and relation exist in possible filters
		//if filter does not have title as its field, and filter of same field, relation exists in current filter list, 
		//remove that filter
		else if(operation.equals("add") && existsIn(newFilter, possibleFilters) && existsIn(newFilter, currentFilters) && !field.equals("title")) {
			
			Iterator<Filter> iter = currentFilters.iterator();

			while (iter.hasNext()) {
			    Filter fltr = iter.next();

			    if (fltr.compareTo(newFilter) == 0) {
			    	iter.remove();
			    }
			        
			}
			currentFilters.add(newFilter);
			Collections.sort(currentFilters);
			return true;
		}
		//add a title filter to the list of current filters if filter of same field and relation exist in possible filters
		//and filter of same field, relation, target does not exist in current filter list, add that filter
		else if(operation.equals("add") && existsIn(newFilter, possibleFilters) && field.equals("title") && !titleFilterExistsIn(newFilter, currentFilters)) {
			currentFilters.add(newFilter);
			Collections.sort(currentFilters);
			return true;
		}
		
		
		//remove filter from the list of current filters if filter of same field and relation exist in current filters
		//and filter does not have is not a title filter
		else if(operation.equals("remove") && existsIn(newFilter, currentFilters) && !field.equals("title")) {
			
			Iterator<Filter> iter = currentFilters.iterator();

			while (iter.hasNext()) {
			    Filter fltr = iter.next();

			    if (fltr.compareTo(newFilter) == 0) {
			    	iter.remove();
			    }
			        
			}
			return true;
			
		}
		//remove title filter from the list of current filters if filter of same field, relation, target 
		//exists in current filters
		else if(operation.equals("remove") && existsIn(newFilter, currentFilters) && field.equals("title")) {
			
			Iterator<Filter> iter = currentFilters.iterator();

			while (iter.hasNext()) {
			    Filter fltr = iter.next();

			    if ((fltr.compareTo(newFilter) == 0) && fltr.getTarget().equals(target)) {
			    	iter.remove();
			    }
			        
			}
			return true;
		}
		//in all other cases there is not operation to do, notify user
		else {
			System.out.println("No operation to be done");
			return false;
		}
	}
	
	
	//checks to see if title filter exists in a filter list. Like existsIn method, but also checks
	//to see if the targets of two filters are the same
	private boolean titleFilterExistsIn(Filter filter, ArrayList<Filter> filterList) {
		for(Filter x : filterList) {
			if((x.compareTo(filter) == 0) && x.getTarget().equals(filter.getTarget())) {
				return true;
			}
		}
		return false;
	}
	
	//checks to see if a filter exists in a filter list. 
	private boolean existsIn(Filter filter, ArrayList<Filter> filterList) {
			for(Filter x : filterList) {
				if(x.compareTo(filter) == 0) {
					return true;
				}
			}
		return false;
	}
	
	
}
