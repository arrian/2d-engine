/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package util;

/**
 *
 * @author Arrian
 */
public abstract class ActionItem<T> 
{
    public enum ActionType
    {
        ADD,
        REMOVE
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
        if(initialAction == ActionType.ADD) add();
        else remove();
    }
    
    public final void undo()
    {
        if(initialAction == ActionType.ADD) remove();
        else add();
    }
}
