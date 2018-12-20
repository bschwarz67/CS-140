package cs_2150_project_Bryan_Schwarz;

//class to hold information for filters designated by the user
public class Filter implements Comparable<Filter>{
	private String field;
	private String relation;
	private String target;
	
	Filter (String field, String relation, String target) {
		this.field = field;
		this.relation = relation;
		this.target = target;
	}
	
	
	
	//getter methods for filter data
	protected String getField() {
		return field;
	}
	protected String getRelation() {
		return relation;
	}
	protected String getTarget() {
		return target;
	}
	
	
	//filters compared first by the type of filter designated by field
	//if this is the same, compared by the relation
	public int compareTo(Filter o) { 
		if (o.getField().equals(this.getField())) {
			return this.getRelation().compareTo(o.getRelation());
		}
		else {
			return this.getField().compareTo(o.getField());
		}
		
	}

	
	
	
  	
}
