package SwingMVC.View;

import SwingMVC.Controller.Controller;
import SwingMVC.Model.MapGenerator;
import Targy.Targy;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.charset.StandardCharsets;

/**
 * Ez az oszt�ly felel�s a program megjelen�t�s��rt.
 * Egy JFrame-b�l sz�rmazik, teh�t ez t�rol minden m�st.
 * MEgjelen�t egy men�szallagot, valamint a karakter statusbar-j�t.
 */
public class GameBoard extends JFrame {

    /**
     * A panel, ami a mez�k grafikus megjelen�t�s�t t�rolja.
     * T�rolja a mez�n tal�lhat� entit�sok megjelen�t�s�t is.
     */
    private GamePanel gamePanel;

    /**
     * Az akt�v karakter tulajdons�gait megjelen�t� �llapots�v.
     */
    private JPanel statusBar;

    /**
     * Az akt�v karakter tulajdons�gait megjelen�t� �llapots�vban a sz�veg.
     */
    private JLabel statusLabel;

    public GameBoard(){

        //Be�ll�tjuk az alapvet� dolgokat
        super("Polar Survivor");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setResizable(false);

        //Be�lll�tjuk a gamePanelt
        gamePanel = new GamePanel();
    }

    /**
     * Vissza�ll�tja a gamePanel-t az eredeti �llapot�ba
     * (vagy �j random p�l�t gener�ltat vele)
     */
    public void reset(){

        //Kit�r�lj�k a r�gi objektumokat
        remove(gamePanel);
        remove(statusBar);

        //�j objektumot t�lt�nk be
        gamePanel = new GamePanel();
        buildGUI();
    }

    /**
     * Elrejti az aktu�lis j�t�kot, hogy ne lehessen katintgatni.
     * Ez csak a j�t�k v�g�n h�vjuk meg, hog nem maradjon ott a befejezetlen j�t�k.
     */
    public void hideGame(){

        gamePanel.setVisible(false);
    }

    /**
     * Kiemeli az akt�v karaktert.
     * Kicser�li az akt�v karakter k�p�t egy kijel�lt karakter k�pre.
     */
    public void highlightKarakter() {

        gamePanel.highlightKarakter();
    }

    /**
     * Megsz�nteti az akt�v karakter kiemel�s�t.
     * Kicser�li a kijel�lt akt�v karakter k�p�t egy nem kijel�ltre.
     */
    public void removeHighlightKarakter(){

        gamePanel.removeHighlightKarakter();
    }

    /**
     * L�trehozza az �llapots�vot �s az elemeit, valamint hozz�adja.
     */
    private void createStatusBar(){

        //T�rol�k l�trehoz�sa
        statusBar = new JPanel();
        statusLabel = new JLabel();

        //Be�ll�tjuk a sz�veget
        setStatusBarText();
        statusBar.add(statusLabel);
        statusBar.setVisible(true);

        //Hozz�adjuk a JFrame-hez
        add(statusBar, BorderLayout.SOUTH);
    }

    /**
     * Az �llaptos�vban tal�lhat� adatokat lekrdezi �s belerakja az �llapots�vba
     */
    public void setStatusBarText() {

        //Lek�rdezz�k a munnk�t �s a testh�t az akt�v karaktert�l
        int munka = Controller.getInstance().getActiveKarakter().getMunka();
        int testho = Controller.getInstance().getActiveKarakter().getTestho();

        StringBuilder targylista = new StringBuilder();

        //Lek�rdezz�k a t�rgylist�t
        for (Targy targy : Controller.getInstance().getActiveKarakter().getTargyak())
            targylista.append(targy.tipus());

        statusLabel.setText(Controller.getInstance().getActiveKarakter().tipus() + " || Munka: " + munka + " | Testho: " + testho + " | Targyak: " + targylista);
    }

    /**
     * L�trehozza a men�sort �s elemeit,
     * valamint be�ll�tja azok viselked�s�t
     */
    private void createMenubar(){

        JMenuBar menuBar = new JMenuBar();

        //Reload map gomb l�trehoz�sa
        JMenuItem restart = new JMenuItem("Reload map");
        //Megh�vja a Controller restart f�ggv�ny�t
        restart.addActionListener((event) -> Controller.getInstance().restart());
        menuBar.add(restart);

        //A map men� l�trehoz�sa
        JMenu map = new JMenu("Map");
        menuBar.add(map);

        //Load default map me�pont l�trehoz�sa
        JMenuItem loadDefault = new JMenuItem("Load default map");
        loadDefault.addActionListener((event) -> {Controller.getInstance().setMap(false); Controller.getInstance().restart();});
        map.add(loadDefault);

        //Random generated map me�pont l�trehoz�sa
        JMenuItem generate = new JMenuItem("Random generated map");
        generate.addActionListener((event) -> {Controller.getInstance().setMap(true); Controller.getInstance().restart();});
        map.add(generate);

        //Set generato me�pont l�trehoz�sa
        JMenuItem setGenerator = new JMenuItem("Set generator");
        //L�trehozza a set generator dialog
        setGenerator.addActionListener((event) -> createGeneratorInputDialog());
        map.add(setGenerator);

        //Help me�pont l�trehoz�sa
        JMenuItem help = new JMenuItem("Help");
        //L�trehozza a helpdialogot
        help.addActionListener((event) -> createHelpDialog());
        menuBar.add(help);

        //Exit me�pont l�trehoz�sa
        JMenuItem exit = new JMenuItem("Exit");
        //Kil�p az alkalmaz�sb�l
        exit.addActionListener((event) -> System.exit(0));
        menuBar.add(exit);

        menuBar.setLayout(new GridLayout(1, 4));
        menuBar.setVisible(true);

        add(menuBar,BorderLayout.NORTH);
    }

    /**
     * L�trehozza az Inputdialog-ot, amiben be�ll�thatjuk a p�lyagener�tor adatait
     */
    private void createGeneratorInputDialog(){

        //Beolvas�shoz felvesz�nk 2 textfieldet, �s bele�rjuk a jelenlegi �rt�keket
        JTextField researcherCount = new JTextField(Integer.toString(MapGenerator.researcherCount));
        JTextField eskimoCount = new JTextField(Integer.toString(MapGenerator.eskimoCount));
        JCheckBox polarBear = new JCheckBox("", MapGenerator.polarBear);
        //Advance settings gom l�trehoz�sa
        JButton advanced = new JButton("Show advanced");
        advanced.addActionListener(e -> createAdvancedGeneratorSettings());

        Object[] message = {

                "Kutatok szama", researcherCount,
                "Eszkimok szama", eskimoCount,
                "Jegesmedve", polarBear,
                advanced
        };

        //Az optionpane megjelen�t�se, valamint ki�rt�kel�se
        int option = JOptionPane.showConfirmDialog(this, message, "Set generator", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION)
            MapGenerator.setGenerator(Integer.parseInt(researcherCount.getText()), Integer.parseInt(eskimoCount.getText()), polarBear.isSelected());
    }

    /**
     * Letrehozza azt az inputDialog-ot, ahol a generator tov�bbi be�ll�t�sait �ll�thatjuk
     */
    private void createAdvancedGeneratorSettings(){

        JTextField holeRatio = new JTextField(Integer.toString(MapGenerator.HOLE));
        JTextField unstableRatio = new JTextField(Integer.toString(MapGenerator.UNSTABLE));
        JTextField stableRatio = new JTextField(Integer.toString(MapGenerator.STABLE));
        JTextField holeCoverageRatio = new JTextField(Integer.toString(MapGenerator.HOLE_COVERAGE));
        JTextField itemRatio = new JTextField(Integer.toString(MapGenerator.ITEM_CHANCE));

        Object[] message = {

                "Lyuk esely", holeRatio,
                "Instabil esely", unstableRatio,
                "Stabil esely", stableRatio,
                "Lyuk lefedettseg esely", holeCoverageRatio,
                "Targy esely", itemRatio
        };

        int option = JOptionPane.showConfirmDialog(this, message, "Set generator", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION){

            MapGenerator.HOLE = Integer.parseInt(holeRatio.getText());
            MapGenerator.UNSTABLE = Integer.parseInt(unstableRatio.getText());
            MapGenerator.STABLE = Integer.parseInt(stableRatio.getText());
            MapGenerator.HOLE_COVERAGE = Integer.parseInt(holeCoverageRatio.getText());
            MapGenerator.ITEM_CHANCE = Integer.parseInt(itemRatio.getText());
        }
    }

    /**
     * Letrehozza a dialog-ot, amiben  kiirjuk a help sz�veget
     */
    private void createHelpDialog(){

        //Lek�rdezz�k a help.txt hely�t
        URL url = getClass().getResource("Help.txt");
        //beolvassuk a f�jlt
        String text = "";
        try(InputStream in = url.openStream()){

            byte[] bytes = in.readAllBytes();
            text = new String(bytes, StandardCharsets.UTF_8);
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        //Bet�ltj�k a sz�veget a textareaban
        JTextArea textArea = new JTextArea(text);
        JScrollPane scrollPane = new JScrollPane(textArea);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        scrollPane.setPreferredSize( new Dimension( 700, 600 ) );
        //kirajzoljuk az optionpane-t
        JOptionPane.showMessageDialog(this, scrollPane, "Help", JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * Ezzel a met�dussal lehet elind�tani a j�t�kot.
     * L�that�v� tesi, valamint fel�p�ti a GUI-t.
     */
    public void start(){

        setVisible(true);
        buildGUI();
    }

    /**
     * Fel�p�ti a GUI-t;
     */
    private void buildGUI() {

        createMenubar();
        createStatusBar();
        add(gamePanel,BorderLayout.CENTER);

        pack();
    }
}
