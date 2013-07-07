package data;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.io.*;

import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

/**
 *
 * @author Arrian
 */
public class Data implements TreeModel {
    
    DataNode root;

    public Data()
    {
        super();
    }
    
    public Data(DataNode root) {
        super();
        this.root = root;
        
        
    }

    public static void save(Data data, File file)
    {
        try {
            if (!file.exists()) file.createNewFile();

            FileWriter fw = new FileWriter(file.getAbsoluteFile());
            BufferedWriter bw = new BufferedWriter(fw);

            Gson gson = new Gson();
            bw.write(gson.toJson(data.getRoot()));
            
            bw.close();
        } catch (IOException ex) {
            System.err.println(ex);
        }
    }
    
    public static Data load(File file)
    {
        FileReader fileReader = null;
        try {
            fileReader = new FileReader(file.getAbsoluteFile());
            BufferedReader br = new BufferedReader(fileReader);
            Gson gson = new GsonBuilder().registerTypeAdapter(DataNode.class, new DataNode.DataNodeAdapter()).create();
            Data data = new Data(gson.fromJson(br, DataNode.class));
            return data;
        } catch (FileNotFoundException ex) {
            System.err.println(ex);
        } finally {
            try {
                fileReader.close();
            } catch (IOException ex) {
                System.err.println(ex);
            }
        }
        return new Data();
    }
    
    public DataItem find(int id)
    {
        return root.find(id);
    }

    @Override
    public Object getRoot() {
        return root;
    }

    @Override
    public Object getChild(Object parent, int index) {
        return ((DataFolder) parent).getChild(index);
    }

    @Override
    public int getChildCount(Object parent) {
        return ((DataNode) parent).getChildCount();
    }

    @Override
    public boolean isLeaf(Object node) {
        return (((DataNode) node).getChildCount() == 0);
    }

    @Override
    public void valueForPathChanged(TreePath path, Object newValue) {

    }

    @Override
    public int getIndexOfChild(Object parent, Object child) {
        return ((DataFolder) parent).getIndex(child);
    }

    @Override
    public void addTreeModelListener(TreeModelListener l) {
    }

    @Override
    public void removeTreeModelListener(TreeModelListener l) {
    }

}
