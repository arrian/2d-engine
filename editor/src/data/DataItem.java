/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import java.util.ArrayList;


/**
 *
 * @author Arrian Purcell
 */
public class DataItem extends DataNode {
    private int id = 0;
    private DataType type = DataType.POINT;
    private ArrayList<String> resources = new ArrayList<String>();

    private DataItem()
    {
        super();
    }
    
    public DataItem(int id, String name, DataType type, ArrayList<String> resources, String parent) {
        super(name);
        this.id = id;
        this.type = type;
        this.resources = resources;
    }

    public int getId() {
        return id;
    }

    public DataType getType() {
        return type;
    }

    @Override
    public int getChildCount() {
        return 0;
    }

    public String getResource(int index) {
        return resources.get(index);
    }

    public int getResourceCount()
    {
    	return resources.size();
    }

	public ArrayList<String> getResources()
	{
		return resources;
	}

    @Override
    public DataItem find(int id) {
        if(this.id == id) return this;
        return null;
    }

}
