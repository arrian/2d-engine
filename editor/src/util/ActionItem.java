/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package util;

import java.util.ArrayList;
import shape.Shape;
import world.World;

/**
 *
 * @author Arrian
 */
public abstract class ActionItem<T> 
{
    public enum ActionType
    {
        DO,
        UNDO
    }

    /**
     * Performs an action and saves the action. Performs the 
     * given action when created.
     * @param initialAction
     * @param object 
     */
    public ActionItem(ActionType initialAction, T object) {
        this.initialAction = initialAction;
        this.object = object;
    }
    
    public void initialise()
    {
        redo();
    }
    
    protected ActionType initialAction;
    protected T object;
    
    protected abstract void add();
    protected abstract void remove();
    
    public final void redo()
    {
        if(initialAction == ActionType.DO) add();
        else remove();
    }
    
    public final void undo()
    {
        if(initialAction == ActionType.DO) remove();
        else add();
    }

    public T getObject() {
        return object;
    }
    
    
    
    public static class AddMarkerAction extends ActionItem<Marker>
    {
        World world;

        public AddMarkerAction(World world, ActionItem.ActionType initialAction, Marker object) {
            super(initialAction, object);
            this.world = world;
        }

        @Override
        public void add() {
            world.addMarker(object);
        }

        @Override
        public void remove() {
            world.removeMarker(object);
        }
    }
    
    public static class AddShapeAction extends ActionItem<Shape>
    {
        World world;
        
        public AddShapeAction(World world, ActionItem.ActionType initialAction, Shape object) {
            super(initialAction, object);
            this.world = world;
        }

        @Override
        public void add() {
            world.addShape(object);
        }

        @Override
        public void remove() {
            world.removeShape(object);
        }
    }
    
    public static class AddShapeArrayAction extends ActionItem<ArrayList<Shape>>
    {
        World world;
        
        public AddShapeArrayAction(World world, ActionItem.ActionType initialAction, ArrayList<Shape> object) {
            super(initialAction, object);
            this.world = world;
        }

        @Override
        public void add() {
            for(Shape shape : object) world.addShape(shape);
        }

        @Override
        public void remove() {
            for(Shape shape : object) world.removeShape(shape);
        }
    }
    
    public static class MoveShapeAction extends ActionItem<Shape>
    {
        World world;
        WorldPosition oldPosition;
        WorldPosition newPosition;

        public MoveShapeAction(World world, ActionType initialAction, Shape object, WorldPosition newPosition) {
            super(initialAction, object);
            this.world = world;
            this.oldPosition = object.getPosition();
            this.newPosition = newPosition;
        }

        @Override
        protected void add() {
            object.setPosition(newPosition);
        }

        @Override
        protected void remove() {
            object.setPosition(oldPosition);
        }

        public void setNewPosition(WorldPosition newPosition) {
            this.newPosition = newPosition;
        }
    }
}
