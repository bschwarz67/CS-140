package cs_2150_project_Bryan_Schwarz;


//class to store information about each line in the text file
//information stored as either a Movie object or Series object, both extend Media.
public class Media {
	protected String name;
	protected String genre;
	protected double rating;
	protected int beginYear;
	protected int endYear;
	
	
	//getters for data in objects of type Media
	protected String getName() {
		return name;
	}
	protected String getGenre() {
		return genre;
	}
	protected double getRating() {
		return rating;
	}
	protected int getBeginYear() {
		return beginYear;
	}
	protected int getEndYear() {
		return endYear;
	}
	
	//returns string of name, genre, rating, beginYear and end year if series
	//returns string of name, genre, rating, beginYear if movie
	public String toString() {
		String mediaString = "";
		
		if(this.genre.equals("series")) {
			mediaString = name + " " + genre + " " + rating + " " + beginYear + "-" + endYear;
		}
		else {
			mediaString = name + " " + genre + " " + rating + " " + beginYear;
		}
		
		return mediaString;
	}
	
}

class Movie extends Media {
	Movie(String name, String genre, double rating, int beginYear) {
		this.name = name;
		this.genre = genre;
		this.rating = rating;
		this.beginYear = beginYear;
	}
}

//as Series may span more than one year, Series object have both beginYear and endYear intialized
class Series extends Media {
	Series(String name, String genre, double rating, int beginYear, int endYear) {
		this.name = name;
		this.genre = genre;
		this.rating = rating;
		this.endYear = endYear;
		this.beginYear = beginYear;
	}
	
	
 }
