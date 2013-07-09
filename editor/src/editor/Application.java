package editor;


import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.tree.TreePath;

import data.Data;
import data.DataItem;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import mode.*;
import util.Settings;

/*
 * To change this template, choose Tools | Templates and open the template in
 * the editor.
 */
/**
 *
 * @author Arrian
 */
public class Application extends javax.swing.JFrame {


    /**
     * Creates new form Application
     */
    public Application() {
        initComponents();
        setFocusable(true);
        addKeyListener(getEditor());
        dataPanel.addKeyListener(getEditor());
        editorPanel.addKeyListener(getEditor());
        addMouseWheelListener(getEditor());

        MouseListener ml = new MouseAdapter() {

            @Override
            public void mousePressed(MouseEvent e) {
                int selRow = itemTree.getRowForLocation(e.getX(), e.getY());
                TreePath selPath = itemTree.getPathForLocation(e.getX(), e.getY());
                if (selRow != -1) {
                    if (e.getClickCount() == 1) {
                        Object object = selPath.getLastPathComponent();
                        if (object instanceof DataItem) {
                            DataItem item = (DataItem) selPath.getLastPathComponent();
                            getEditor().setSelectedDataItem(item);
                            modeGroup.setSelected(modeAdd.getModel(), true);
//
//                            idText.setText(Integer.toString(item.getId()));
//                            nameText.setText(item.getName());
//                            imageText.setText(item.getResources().toString());
//                            typeCombo.setSelectedIndex(item.getType().ordinal());
                        }
                    } else if (e.getClickCount() == 2) {
                        Object object = selPath.getLastPathComponent();
                        if (object instanceof DataItem) {
                            DataItem item = (DataItem) selPath.getLastPathComponent();
                            DataDialog dialog = new DataDialog(Application.this, item);
                            dialog.setVisible(true);
                        }
                    }
                }
            }
        };
        itemTree.addMouseListener(ml);
        expandTree();
    }
    
    private Editor getEditor()
    {
        return (Editor) editorPanel;
    }
    
    public void expandTree() {
        for (int i = 0; i < itemTree.getRowCount(); i++) {
            itemTree.expandRow(i);
        }
    }
    
    private void open()
    {
        JFileChooser openFile = new JFileChooser();
        int returnValue = openFile.showOpenDialog(null);
        if(returnValue == JFileChooser.APPROVE_OPTION)
        {
            getEditor().load(openFile.getSelectedFile(), (Data) itemTree.getModel());
        }
    }
    
    private void save()
    {
        if(getEditor().getWorkingFile() == null) {
            saveAs();
        } else {
            getEditor().save();
        }
    }
    
    private void saveAs()
    {
        JFileChooser saveFile = new JFileChooser();
        int returnValue = saveFile.showSaveDialog(null);
        if(returnValue == JFileChooser.APPROVE_OPTION) {
            File file = saveFile.getSelectedFile();
            getEditor().save(file);//, (Data) itemTree.getModel());
        }
    }
    
    private void newWorld()
    {
        int option = JOptionPane.showConfirmDialog(this, "Do you want to save changes to the current world?");
        
        if(option == JOptionPane.YES_OPTION) save();
        if(option != JOptionPane.CANCEL_OPTION) getEditor().clear();
    }
    
    private void setEditorMode(Class c) {

        if(c.equals(ModeSelect.class)) getEditor().setMode(new ModeSelect(getEditor()));
        else if(c.equals(ModeAdd.class)) getEditor().setMode(new ModeAdd(getEditor(), getEditor().getSelectedDataItem()));
        else if(c.equals(ModeMove.class)) getEditor().setMode(new ModeMove(getEditor()));        
        else if(c.equals(ModeRotate.class)) getEditor().setMode(new ModeRotate(getEditor()));
        else if(c.equals(ModeHand.class)) getEditor().setMode(new ModeHand(getEditor()));
    
    }
    
    private void run()
    {
        try 
        {
            String data = "game.dat";
            String world = "world.dat";
            String cell = "0,0";
            String position = "300,300";
            ProcessBuilder pb = new ProcessBuilder(Settings.DEFAULT_EXECUTABLE_LOCATION + Settings.DEFAULT_EXECUTABLE, data, world, cell, position);
            Process p = pb.start();
        } 
        catch (IOException ex) 
        {
            System.err.println(ex);
        }
    }
 
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        modeGroup = new javax.swing.ButtonGroup();
        modeMenuGroup = new javax.swing.ButtonGroup();
        dataPanel = new javax.swing.JPanel();
        itemTreePane = new javax.swing.JScrollPane();
        itemTree = new javax.swing.JTree();
        editorPanel = new Editor();
        tools = new javax.swing.JToolBar();
        newWorld = new javax.swing.JButton();
        openWorld = new javax.swing.JButton();
        saveWorld = new javax.swing.JButton();
        jSeparator6 = new javax.swing.JToolBar.Separator();
        undo = new javax.swing.JButton();
        redo = new javax.swing.JButton();
        jSeparator7 = new javax.swing.JToolBar.Separator();
        modeSelect = new javax.swing.JToggleButton();
        modeAdd = new javax.swing.JToggleButton();
        modeMove = new javax.swing.JToggleButton();
        modeRotate = new javax.swing.JToggleButton();
        modeHand = new javax.swing.JToggleButton();
        jSeparator5 = new javax.swing.JToolBar.Separator();
        run = new javax.swing.JButton();
        showDebug = new javax.swing.JToggleButton();
        showData = new javax.swing.JToggleButton();
        jSeparator2 = new javax.swing.JToolBar.Separator();
        jComboBox1 = new javax.swing.JComboBox();
        jButton3 = new javax.swing.JButton();
        jButton4 = new javax.swing.JButton();
        jSeparator9 = new javax.swing.JToolBar.Separator();
        zoomOut = new javax.swing.JButton();
        zoomIn = new javax.swing.JButton();
        markerSelect = new javax.swing.JButton();
        markerAdd = new javax.swing.JButton();
        jSeparator10 = new javax.swing.JToolBar.Separator();
        worldSettings = new javax.swing.JButton();
        menu = new javax.swing.JMenuBar();
        fileMenu = new javax.swing.JMenu();
        newMenuItem = new javax.swing.JMenuItem();
        openMenuItem = new javax.swing.JMenuItem();
        saveWorldMenuItem = new javax.swing.JMenuItem();
        saveWorldAsMenuItem = new javax.swing.JMenuItem();
        jSeparator1 = new javax.swing.JPopupMenu.Separator();
        jMenuItem4 = new javax.swing.JMenuItem();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem3 = new javax.swing.JMenuItem();
        saveDataMenuItem = new javax.swing.JMenuItem();
        saveDataAsMenuItem = new javax.swing.JMenuItem();
        jSeparator8 = new javax.swing.JPopupMenu.Separator();
        exitMenuItem = new javax.swing.JMenuItem();
        editMenu = new javax.swing.JMenu();
        undoMenuItem = new javax.swing.JMenuItem();
        redoMenuItem = new javax.swing.JMenuItem();
        jSeparator3 = new javax.swing.JPopupMenu.Separator();
        deleteMenuItem = new javax.swing.JMenuItem();
        duplicateMenuItem = new javax.swing.JMenuItem();
        copyMenuItem = new javax.swing.JMenuItem();
        pasteMenuItem = new javax.swing.JMenuItem();
        jSeparator4 = new javax.swing.JPopupMenu.Separator();
        selectMenuItem = new javax.swing.JRadioButtonMenuItem();
        addMenuItem = new javax.swing.JRadioButtonMenuItem();
        moveMenuItem = new javax.swing.JRadioButtonMenuItem();
        rotateMenuItem = new javax.swing.JRadioButtonMenuItem();
        handMenuItem = new javax.swing.JRadioButtonMenuItem();
        toolsMenu = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Editor");
        setIconImages(null);

        dataPanel.setLayout(new java.awt.BorderLayout());

        itemTreePane.setBorder(null);
        itemTreePane.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        itemTreePane.setMaximumSize(new java.awt.Dimension(0, 0));

        itemTree.setModel(Data.load(new File(Settings.DEFAULT_RESOURCE_LOCATION + Settings.DEFAULT_DATA_FOLDER + Settings.DEFAULT_DATA_FILE)));
        itemTree.setToolTipText("");
        itemTree.setAutoscrolls(true);
        itemTree.setDragEnabled(true);
        itemTree.setEditable(true);
        itemTree.setMinimumSize(null);
        itemTree.setName("");
        itemTree.setRootVisible(false);
        itemTree.setShowsRootHandles(true);
        itemTreePane.setViewportView(itemTree);

        dataPanel.add(itemTreePane, java.awt.BorderLayout.CENTER);

        editorPanel.setBackground(new java.awt.Color(255, 255, 255));

        javax.swing.GroupLayout editorPanelLayout = new javax.swing.GroupLayout(editorPanel);
        editorPanel.setLayout(editorPanelLayout);
        editorPanelLayout.setHorizontalGroup(
            editorPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        editorPanelLayout.setVerticalGroup(
            editorPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        tools.setFloatable(false);
        tools.setRollover(true);

        newWorld.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/box--plus.png"))); // NOI18N
        newWorld.setToolTipText("New world");
        newWorld.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        newWorld.setFocusable(false);
        newWorld.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        newWorld.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        newWorld.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newWorldActionPerformed(evt);
            }
        });
        tools.add(newWorld);

        openWorld.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/folder-horizontal-open.png"))); // NOI18N
        openWorld.setToolTipText("Open world");
        openWorld.setFocusable(false);
        openWorld.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        openWorld.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        openWorld.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openWorldActionPerformed(evt);
            }
        });
        tools.add(openWorld);

        saveWorld.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/disk-black.png"))); // NOI18N
        saveWorld.setToolTipText("Save world");
        saveWorld.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        saveWorld.setFocusable(false);
        saveWorld.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        saveWorld.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        saveWorld.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveWorldActionPerformed(evt);
            }
        });
        tools.add(saveWorld);
        tools.add(jSeparator6);

        undo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/arrow-curve-180-left.png"))); // NOI18N
        undo.setToolTipText("Undo");
        undo.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        undo.setFocusable(false);
        undo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        undo.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        undo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                undoActionPerformed(evt);
            }
        });
        tools.add(undo);

        redo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/arrow-curve.png"))); // NOI18N
        redo.setToolTipText("Redo");
        redo.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        redo.setFocusable(false);
        redo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        redo.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        redo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                redoActionPerformed(evt);
            }
        });
        tools.add(redo);
        tools.add(jSeparator7);

        modeGroup.add(modeSelect);
        modeSelect.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/cursor.png"))); // NOI18N
        modeSelect.setSelected(true);
        modeSelect.setToolTipText("Cursor");
        modeSelect.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        modeSelect.setFocusable(false);
        modeSelect.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        modeSelect.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        modeSelect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modeSelectActionPerformed(evt);
            }
        });
        tools.add(modeSelect);

        modeGroup.add(modeAdd);
        modeAdd.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/plus.png"))); // NOI18N
        modeAdd.setToolTipText("Add");
        modeAdd.setFocusable(false);
        modeAdd.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        modeAdd.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        modeAdd.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modeAddActionPerformed(evt);
            }
        });
        tools.add(modeAdd);

        modeGroup.add(modeMove);
        modeMove.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/arrow-move.png"))); // NOI18N
        modeMove.setToolTipText("Move");
        modeMove.setFocusable(false);
        modeMove.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        modeMove.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        modeMove.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modeMoveActionPerformed(evt);
            }
        });
        tools.add(modeMove);

        modeGroup.add(modeRotate);
        modeRotate.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/layer-rotate.png"))); // NOI18N
        modeRotate.setToolTipText("Rotate");
        modeRotate.setFocusable(false);
        modeRotate.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        modeRotate.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        modeRotate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modeRotateActionPerformed(evt);
            }
        });
        tools.add(modeRotate);

        modeGroup.add(modeHand);
        modeHand.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/hand.png"))); // NOI18N
        modeHand.setToolTipText("Hand tool");
        modeHand.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        modeHand.setFocusable(false);
        modeHand.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        modeHand.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        modeHand.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                modeHandActionPerformed(evt);
            }
        });
        tools.add(modeHand);
        tools.add(jSeparator5);

        run.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/control.png"))); // NOI18N
        run.setToolTipText("Test");
        run.setFocusable(false);
        run.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        run.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        run.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                runActionPerformed(evt);
            }
        });
        tools.add(run);

        showDebug.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/grid.png"))); // NOI18N
        showDebug.setSelected(true);
        showDebug.setToolTipText("Show debug");
        showDebug.setFocusable(false);
        showDebug.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        showDebug.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        showDebug.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showDebugActionPerformed(evt);
            }
        });
        tools.add(showDebug);

        showData.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/folder-tree.png"))); // NOI18N
        showData.setSelected(true);
        showData.setToolTipText("Show data");
        showData.setFocusable(false);
        showData.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        showData.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        showData.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                showDataActionPerformed(evt);
            }
        });
        tools.add(showData);
        tools.add(jSeparator2);

        jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "None", "Layer 0", "Layer 1", "Layer 2", "Layer 3", "Layer 4", "Layer 5", "Layer 6", "Layer 7", "Layer 8", "Layer 9" }));
        jComboBox1.setToolTipText("Layer");
        jComboBox1.setLightWeightPopupEnabled(false);
        jComboBox1.setMaximumSize(new java.awt.Dimension(61, 20));
        tools.add(jComboBox1);

        jButton3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/arrow-transition-270.png"))); // NOI18N
        jButton3.setToolTipText("Move down a layer");
        jButton3.setFocusable(false);
        jButton3.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jButton3.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        tools.add(jButton3);

        jButton4.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/arrow-transition-090.png"))); // NOI18N
        jButton4.setToolTipText("Move up a layer");
        jButton4.setFocusable(false);
        jButton4.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        jButton4.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        tools.add(jButton4);
        tools.add(jSeparator9);

        zoomOut.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/magnifier-zoom-in.png"))); // NOI18N
        zoomOut.setToolTipText("Zoom in");
        zoomOut.setFocusable(false);
        zoomOut.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        zoomOut.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        zoomOut.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                zoomOutActionPerformed(evt);
            }
        });
        tools.add(zoomOut);

        zoomIn.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/magnifier-zoom-out.png"))); // NOI18N
        zoomIn.setToolTipText("Zoom out");
        zoomIn.setFocusable(false);
        zoomIn.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        zoomIn.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        zoomIn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                zoomInActionPerformed(evt);
            }
        });
        tools.add(zoomIn);

        markerSelect.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/marker.png"))); // NOI18N
        markerSelect.setToolTipText("Select marker");
        markerSelect.setFocusable(false);
        markerSelect.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        markerSelect.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        markerSelect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                markerSelectActionPerformed(evt);
            }
        });
        tools.add(markerSelect);

        markerAdd.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/marker--plus.png"))); // NOI18N
        markerAdd.setToolTipText("Add marker");
        markerAdd.setFocusable(false);
        markerAdd.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        markerAdd.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        markerAdd.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                markerAddActionPerformed(evt);
            }
        });
        tools.add(markerAdd);
        tools.add(jSeparator10);

        worldSettings.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/map.png"))); // NOI18N
        worldSettings.setToolTipText("World settings");
        worldSettings.setFocusable(false);
        worldSettings.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        worldSettings.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        tools.add(worldSettings);

        fileMenu.setText("File");

        newMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_N, java.awt.event.InputEvent.CTRL_MASK));
        newMenuItem.setText("New World");
        newMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(newMenuItem);

        openMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_O, java.awt.event.InputEvent.CTRL_MASK));
        openMenuItem.setText("Open World");
        openMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(openMenuItem);

        saveWorldMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.event.InputEvent.CTRL_MASK));
        saveWorldMenuItem.setText("Save World");
        saveWorldMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveWorldMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(saveWorldMenuItem);

        saveWorldAsMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        saveWorldAsMenuItem.setText("Save World As...");
        saveWorldAsMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveWorldAsMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(saveWorldAsMenuItem);
        fileMenu.add(jSeparator1);

        jMenuItem4.setText("New Data");
        fileMenu.add(jMenuItem4);

        jMenuItem1.setText("New Data Item");
        fileMenu.add(jMenuItem1);

        jMenuItem3.setText("Open Data Item");
        jMenuItem3.setToolTipText("");
        fileMenu.add(jMenuItem3);

        saveDataMenuItem.setText("Save Data");
        saveDataMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveDataMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(saveDataMenuItem);

        saveDataAsMenuItem.setText("Save Data As...");
        saveDataAsMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveDataAsMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(saveDataAsMenuItem);
        fileMenu.add(jSeparator8);

        exitMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_F4, java.awt.event.InputEvent.ALT_MASK));
        exitMenuItem.setLabel("Exit");
        exitMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                exitMenuItemActionPerformed(evt);
            }
        });
        fileMenu.add(exitMenuItem);

        menu.add(fileMenu);

        editMenu.setText("Edit");

        undoMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_Z, java.awt.event.InputEvent.CTRL_MASK));
        undoMenuItem.setText("Undo");
        undoMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                undoMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(undoMenuItem);

        redoMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_Y, java.awt.event.InputEvent.CTRL_MASK));
        redoMenuItem.setText("Redo");
        redoMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                redoMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(redoMenuItem);
        editMenu.add(jSeparator3);

        deleteMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_DELETE, 0));
        deleteMenuItem.setText("Delete");
        deleteMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                deleteMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(deleteMenuItem);

        duplicateMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_D, java.awt.event.InputEvent.CTRL_MASK));
        duplicateMenuItem.setText("Duplicate");
        duplicateMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                duplicateMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(duplicateMenuItem);

        copyMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_C, java.awt.event.InputEvent.CTRL_MASK));
        copyMenuItem.setText("Copy");
        copyMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                copyMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(copyMenuItem);

        pasteMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_V, java.awt.event.InputEvent.CTRL_MASK));
        pasteMenuItem.setText("Paste");
        pasteMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                pasteMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(pasteMenuItem);
        editMenu.add(jSeparator4);

        selectMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_1, 0));
        modeMenuGroup.add(selectMenuItem);
        selectMenuItem.setSelected(true);
        selectMenuItem.setText("Select");
        selectMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                selectMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(selectMenuItem);

        addMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_2, 0));
        modeMenuGroup.add(addMenuItem);
        addMenuItem.setText("Add");
        addMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(addMenuItem);

        moveMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_3, 0));
        modeMenuGroup.add(moveMenuItem);
        moveMenuItem.setText("Move");
        moveMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                moveMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(moveMenuItem);

        rotateMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_4, 0));
        modeMenuGroup.add(rotateMenuItem);
        rotateMenuItem.setText("Rotate");
        rotateMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                rotateMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(rotateMenuItem);

        handMenuItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_5, 0));
        modeMenuGroup.add(handMenuItem);
        handMenuItem.setText("Hand tool");
        handMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                handMenuItemActionPerformed(evt);
            }
        });
        editMenu.add(handMenuItem);

        menu.add(editMenu);

        toolsMenu.setText("Tools");

        jMenuItem2.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_B, java.awt.event.InputEvent.SHIFT_MASK | java.awt.event.InputEvent.CTRL_MASK));
        jMenuItem2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/icons/control.png"))); // NOI18N
        jMenuItem2.setText("Run");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        toolsMenu.add(jMenuItem2);

        menu.add(toolsMenu);

        setJMenuBar(menu);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(dataPanel, javax.swing.GroupLayout.DEFAULT_SIZE, 250, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(editorPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addComponent(tools, javax.swing.GroupLayout.DEFAULT_SIZE, 1049, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(tools, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(editorPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(dataPanel, javax.swing.GroupLayout.DEFAULT_SIZE, 723, Short.MAX_VALUE)))
        );

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-1057)/2, (screenSize.height-803)/2, 1057, 803);
    }// </editor-fold>//GEN-END:initComponents

    private void openMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openMenuItemActionPerformed
        open();
    }//GEN-LAST:event_openMenuItemActionPerformed

    private void saveWorldMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveWorldMenuItemActionPerformed
        save();
    }//GEN-LAST:event_saveWorldMenuItemActionPerformed

    private void saveWorldAsMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveWorldAsMenuItemActionPerformed
        saveAs();
    }//GEN-LAST:event_saveWorldAsMenuItemActionPerformed

    private void newMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newMenuItemActionPerformed
        newWorld();
    }//GEN-LAST:event_newMenuItemActionPerformed

    private void exitMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_exitMenuItemActionPerformed
        dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
    }//GEN-LAST:event_exitMenuItemActionPerformed

    private void undoMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_undoMenuItemActionPerformed
        getEditor().undo();
    }//GEN-LAST:event_undoMenuItemActionPerformed

    private void redoMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_redoMenuItemActionPerformed
        getEditor().redo();
    }//GEN-LAST:event_redoMenuItemActionPerformed

    private void deleteMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_deleteMenuItemActionPerformed
        getEditor().delete();
    }//GEN-LAST:event_deleteMenuItemActionPerformed

    private void duplicateMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_duplicateMenuItemActionPerformed
        getEditor().duplicate();
    }//GEN-LAST:event_duplicateMenuItemActionPerformed

    private void copyMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_copyMenuItemActionPerformed
        getEditor().copy();
    }//GEN-LAST:event_copyMenuItemActionPerformed

    private void pasteMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_pasteMenuItemActionPerformed
        getEditor().paste();
    }//GEN-LAST:event_pasteMenuItemActionPerformed

    private void newWorldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newWorldActionPerformed
        newWorld();
    }//GEN-LAST:event_newWorldActionPerformed

    private void saveWorldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveWorldActionPerformed
        save();
    }//GEN-LAST:event_saveWorldActionPerformed

    private void undoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_undoActionPerformed
        getEditor().undo();
    }//GEN-LAST:event_undoActionPerformed

    private void redoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_redoActionPerformed
        getEditor().redo();
    }//GEN-LAST:event_redoActionPerformed

    private void modeSelectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modeSelectActionPerformed
        setEditorMode(ModeSelect.class);
        modeMenuGroup.setSelected(selectMenuItem.getModel(), true);
    }//GEN-LAST:event_modeSelectActionPerformed

    private void modeAddActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modeAddActionPerformed
        setEditorMode(ModeAdd.class);
        modeMenuGroup.setSelected(addMenuItem.getModel(), true);
    }//GEN-LAST:event_modeAddActionPerformed

    private void modeMoveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modeMoveActionPerformed
        setEditorMode(ModeMove.class);
        modeMenuGroup.setSelected(moveMenuItem.getModel(), true);
    }//GEN-LAST:event_modeMoveActionPerformed

    private void modeRotateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modeRotateActionPerformed
        setEditorMode(ModeRotate.class);
        modeMenuGroup.setSelected(rotateMenuItem.getModel(), true);
    }//GEN-LAST:event_modeRotateActionPerformed

    private void modeHandActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_modeHandActionPerformed
        setEditorMode(ModeHand.class);
        modeMenuGroup.setSelected(handMenuItem.getModel(), true);
    }//GEN-LAST:event_modeHandActionPerformed

    private void showDebugActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showDebugActionPerformed
        AbstractButton abstractButton = (AbstractButton) evt.getSource();
        boolean selected = abstractButton.getModel().isSelected();
        getEditor().setShowDebug(selected);
    }//GEN-LAST:event_showDebugActionPerformed

    private void saveDataMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveDataMenuItemActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_saveDataMenuItemActionPerformed

    private void saveDataAsMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveDataAsMenuItemActionPerformed
        JFileChooser saveFile = new JFileChooser();
        int returnValue = saveFile.showSaveDialog(null);
        if(returnValue == JFileChooser.APPROVE_OPTION) {
            File file = saveFile.getSelectedFile();
            Data.save((Data)itemTree.getModel(), file);
        }
    }//GEN-LAST:event_saveDataAsMenuItemActionPerformed

    private void markerAddActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_markerAddActionPerformed

        MarkerAddDialog dialog = new MarkerAddDialog(this, true);
        dialog.setVisible(true);
        
        String name = dialog.getMarkerName();
        if(name != null && !name.equals("")) getEditor().addMarker(name);
        
    }//GEN-LAST:event_markerAddActionPerformed

    private void markerSelectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_markerSelectActionPerformed
        MarkerDialog dialog = new MarkerDialog(this, true);
        dialog.setVisible(true);
    }//GEN-LAST:event_markerSelectActionPerformed

    private void runActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_runActionPerformed
        run();
    }//GEN-LAST:event_runActionPerformed

    private void showDataActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_showDataActionPerformed
        AbstractButton abstractButton = (AbstractButton) evt.getSource();
        boolean selected = abstractButton.getModel().isSelected();
        dataPanel.setVisible(selected);
    }//GEN-LAST:event_showDataActionPerformed

    private void zoomOutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_zoomOutActionPerformed
        getEditor().zoom(1);
    }//GEN-LAST:event_zoomOutActionPerformed

    private void zoomInActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_zoomInActionPerformed
        getEditor().zoom(-1);
    }//GEN-LAST:event_zoomInActionPerformed

    private void openWorldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openWorldActionPerformed
        open();
    }//GEN-LAST:event_openWorldActionPerformed

    private void selectMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_selectMenuItemActionPerformed
        setEditorMode(ModeSelect.class);
        modeGroup.setSelected(modeSelect.getModel(), true);
    }//GEN-LAST:event_selectMenuItemActionPerformed

    private void addMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addMenuItemActionPerformed
        setEditorMode(ModeAdd.class);
        modeGroup.setSelected(modeAdd.getModel(), true);
    }//GEN-LAST:event_addMenuItemActionPerformed

    private void moveMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_moveMenuItemActionPerformed
        setEditorMode(ModeMove.class);
        modeGroup.setSelected(modeMove.getModel(), true);
    }//GEN-LAST:event_moveMenuItemActionPerformed

    private void rotateMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_rotateMenuItemActionPerformed
        setEditorMode(ModeRotate.class);
        modeGroup.setSelected(modeRotate.getModel(), true);
    }//GEN-LAST:event_rotateMenuItemActionPerformed

    private void handMenuItemActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_handMenuItemActionPerformed
        setEditorMode(ModeHand.class);
        modeGroup.setSelected(modeHand.getModel(), true);
    }//GEN-LAST:event_handMenuItemActionPerformed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        run();
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {

        try {
            UIManager.setLookAndFeel(
                    UIManager.getSystemLookAndFeelClassName());
        } catch (UnsupportedLookAndFeelException e) {
        } catch (ClassNotFoundException e) {
        } catch (InstantiationException e) {
        } catch (IllegalAccessException e) {
        }

        /*
         * Create and display the form
         */
        java.awt.EventQueue.invokeLater(new Runnable() {

            @Override
			public void run() {
                new Application().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JRadioButtonMenuItem addMenuItem;
    private javax.swing.JMenuItem copyMenuItem;
    private javax.swing.JPanel dataPanel;
    private javax.swing.JMenuItem deleteMenuItem;
    private javax.swing.JMenuItem duplicateMenuItem;
    private javax.swing.JMenu editMenu;
    private javax.swing.JPanel editorPanel;
    private javax.swing.JMenuItem exitMenuItem;
    private javax.swing.JMenu fileMenu;
    private javax.swing.JRadioButtonMenuItem handMenuItem;
    private javax.swing.JTree itemTree;
    private javax.swing.JScrollPane itemTreePane;
    private javax.swing.JButton jButton3;
    private javax.swing.JButton jButton4;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem3;
    private javax.swing.JMenuItem jMenuItem4;
    private javax.swing.JPopupMenu.Separator jSeparator1;
    private javax.swing.JToolBar.Separator jSeparator10;
    private javax.swing.JToolBar.Separator jSeparator2;
    private javax.swing.JPopupMenu.Separator jSeparator3;
    private javax.swing.JPopupMenu.Separator jSeparator4;
    private javax.swing.JToolBar.Separator jSeparator5;
    private javax.swing.JToolBar.Separator jSeparator6;
    private javax.swing.JToolBar.Separator jSeparator7;
    private javax.swing.JPopupMenu.Separator jSeparator8;
    private javax.swing.JToolBar.Separator jSeparator9;
    private javax.swing.JButton markerAdd;
    private javax.swing.JButton markerSelect;
    private javax.swing.JMenuBar menu;
    private javax.swing.JToggleButton modeAdd;
    private javax.swing.ButtonGroup modeGroup;
    private javax.swing.JToggleButton modeHand;
    private javax.swing.ButtonGroup modeMenuGroup;
    private javax.swing.JToggleButton modeMove;
    private javax.swing.JToggleButton modeRotate;
    private javax.swing.JToggleButton modeSelect;
    private javax.swing.JRadioButtonMenuItem moveMenuItem;
    private javax.swing.JMenuItem newMenuItem;
    private javax.swing.JButton newWorld;
    private javax.swing.JMenuItem openMenuItem;
    private javax.swing.JButton openWorld;
    private javax.swing.JMenuItem pasteMenuItem;
    private javax.swing.JButton redo;
    private javax.swing.JMenuItem redoMenuItem;
    private javax.swing.JRadioButtonMenuItem rotateMenuItem;
    private javax.swing.JButton run;
    private javax.swing.JMenuItem saveDataAsMenuItem;
    private javax.swing.JMenuItem saveDataMenuItem;
    private javax.swing.JButton saveWorld;
    private javax.swing.JMenuItem saveWorldAsMenuItem;
    private javax.swing.JMenuItem saveWorldMenuItem;
    private javax.swing.JRadioButtonMenuItem selectMenuItem;
    private javax.swing.JToggleButton showData;
    private javax.swing.JToggleButton showDebug;
    private javax.swing.JToolBar tools;
    private javax.swing.JMenu toolsMenu;
    private javax.swing.JButton undo;
    private javax.swing.JMenuItem undoMenuItem;
    private javax.swing.JButton worldSettings;
    private javax.swing.JButton zoomIn;
    private javax.swing.JButton zoomOut;
    // End of variables declaration//GEN-END:variables
}
