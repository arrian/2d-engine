/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import com.google.gson.*;
import com.google.gson.annotations.SerializedName;
import data.Data;
import data.DataItem;
import java.awt.Graphics2D;

import util.ScreenPosition;
import util.WorldPosition;
import editor.Editor;
import java.util.ArrayList;
import util.ActionItem;


/**
 *
 * @author Arrian
 */
public abstract class Shape {
    
    protected int id;
    @SerializedName("l") protected int layer;
    @SerializedName("p") protected WorldPosition position;
    @SerializedName("r") protected double rotation;
    protected transient ArrayList<String> resources = new ArrayList<String>();
    
    protected transient String name = null;

    private Shape()
    {
    }
    
    public Shape(int id, WorldPosition position) {
        this.id = id;
        this.position = position;
    }

    public void draw(Editor editor, Graphics2D g2d)
    {
    	draw(g2d, editor.getScreenPosition(position), editor.getWorldScale());
    }
    
    public void drawDebug(Editor editor, Graphics2D g2d)
    {
        drawDebug(g2d, editor.getScreenPosition(position), editor.getWorldScale());
    }

    protected abstract void draw(Graphics2D g2d, ScreenPosition position, double scale);
    protected void drawDebug(Graphics2D g2d, ScreenPosition position, double scale) { draw(g2d, position, scale); }
    public abstract boolean contains(ShapePoint point);
    public abstract boolean intersects(ShapeRectangle rectangle);

    public String serialise() {
        return Integer.toString(id);
    }

    public WorldPosition getPosition() {
        return position;
    }

    public void setPosition(WorldPosition position) {
        this.position = position;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getRotation() {
        return rotation;
    }

    public void setRotation(double rotation) {
        this.rotation = rotation;
    }
    
    public static class ShapeAdapter implements JsonDeserializer<Shape>
    {
        Editor editor;
        Data data;
        
        public ShapeAdapter(Editor editor, Data data) {
            this.editor = editor;
            this.data = data;
        }
        
        @Override
        public Shape deserialize(JsonElement json, java.lang.reflect.Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            
            JsonObject jsonObject =  json.getAsJsonObject();
            JsonPrimitive id = ((JsonPrimitive) jsonObject.get("id"));
            
            if(id == null) return context.deserialize(json, Shape.class);
            
            DataItem item = data.find(id.getAsInt());
            if(item == null) return context.deserialize(json, Shape.class);
            
            Shape shape;
            switch(item.getType())
            {
                case IMAGE: 
                    ShapeImage image = context.deserialize(json, ShapeImage.class);
                    if(item.getResourceCount() > 0) image.setImage(editor.getImageResourceLocation() + item.getResource(0));
                    shape = image;
                    break;
                case IMAGE_ANIMATED: 
                    shape = context.deserialize(json, ShapeImageAnimated.class);
                    break;
                case LINE: 
                    ShapeLine line = context.deserialize(json, ShapeLine.class);
                    line.setComplete(true);
                    shape = line;
                    break;
                case LINE_STRIP: 
                    shape = context.deserialize(json, ShapeLineStrip.class);
                    break;
                case POINT: 
                    shape = context.deserialize(json, ShapePoint.class);
                    break;
                case RECTANGLE: 
                    shape = context.deserialize(json, ShapeRectangle.class);
                    break;
                default: 
                    shape = context.deserialize(json, Shape.class); 
                    break;
            }
            
            shape.setName(item.getName());
            return shape;
        }
    }
}
