/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import com.google.gson.*;
import java.lang.ProcessBuilder.Redirect.Type;

/**
 *
 * @author Arrian
 */
public abstract class DataNode {
    private String name = "";

    protected DataNode()
    {
    
    }
    
    public DataNode(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
    
    public abstract int getChildCount();
    
    
    @Override
    public String toString() {
        return name;
    }

    public abstract DataItem find(int id);
    
    public static class DataNodeAdapter implements JsonDeserializer<DataNode>{

        @Override
        public DataNode deserialize(JsonElement json, java.lang.reflect.Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            
            JsonObject jsonObject =  json.getAsJsonObject();
            JsonPrimitive id = ((JsonPrimitive) jsonObject.get("id"));

            if(id != null) return context.deserialize(json, DataItem.class);
            return context.deserialize(json, DataFolder.class);
        }
    }
}
