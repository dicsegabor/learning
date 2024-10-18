package SwingMVC.View;

import Mezo.Mezo;
import SwingMVC.Controller.Controller;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

/**
 * T�rolja a mez�kh�z tartoz� mezoView-kat, �s gondoskodik az elrendez�s�kr�l
 */
public class GamePanel extends JPanel {

    /**
     * Tarolja a j�t�kt�r alapm�ret�t
     */
    public static final Dimension DEFAULT_DIMENSION = new Dimension(840, 700);

    /**
     * T�rolja a mez�kh�z tartoz� mezoView-kat
     */
    private ArrayList<MezoView> mezoViews;

    /**
     * Be�ll�tja a panel tulajdons�gait, valamint felt�lti  mezoView list�t a model alapj�n
     * Kiemeli a kezd� karaktert
     */
    public GamePanel(){

        super();

        mezoViews = new ArrayList<>();

        setPreferredSize(DEFAULT_DIMENSION);
        setMinimumSize(DEFAULT_DIMENSION);
        setBackground(Color.BLACK);

        GridLayout layout = new GridLayout(5, 6);
        setLayout(layout);

        for(Mezo m : Controller.getInstance().getModel().getMezok())
            addMezoView(new MezoView(m));

        highlightKarakter();

        setVisible(true);
    }

    /**
     * Kiemeli az akt�v karaktert
     */
    public void highlightKarakter() {

        for (MezoView mv : mezoViews)
            if(mv.containsEntity(Controller.getInstance().getActiveKarakter()))
                mv.highlightKarakter(Controller.getInstance().getActiveKarakter());
    }

    /**
     * Megsz�nteti az akt�v karakter kiemel�s�t
     */
    public void removeHighlightKarakter(){

        for (MezoView mv : mezoViews)
            if(mv.containsEntity(Controller.getInstance().getActiveKarakter()))
                mv.removeHighlightKarakter(Controller.getInstance().getActiveKarakter());
    }

    /**
     * Hozz�adja a param�terk�nt kapo mezoView-t a list�hoz, valamint a panlehez
     * @param mezoView
     */
    private void addMezoView(MezoView mezoView){

        mezoViews.add(mezoView);
        add(mezoView);
    }
}
