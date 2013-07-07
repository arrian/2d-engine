/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import java.util.ArrayList;

/**
 *
 * @author Arrian
 */
public class DataFolder extends DataNode {
    
    private ArrayList<DataNode> children = new ArrayList<DataNode>();

    private DataFolder()
    {
        super();
    }
    
    public DataFolder(String name) {
        super(name);
    }
    
    public void addDataNode(DataNode node) {
        children.add(node);
    }
    
    @Override
    public int getChildCount() {
        return children.size();
    }
    
    public Object getChild(int index) {
        return children.get(index);
    }

    int getIndex(Object child) {
        return children.indexOf(child);
    }

    @Override
    public DataItem find(int id) {
        for(DataNode child : children)
        {
            DataItem found = child.find(id);
            if(found != null) return found;
        }
        return null;
    }
}
