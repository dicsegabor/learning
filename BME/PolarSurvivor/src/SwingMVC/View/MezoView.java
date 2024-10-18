package SwingMVC.View;

import Mezo.*;
import Mozgathato.*;
import SwingMVC.Controller.Controller;
import SwingMVC.Eventhandling.Eventhandlers.MezoEventListener;
import SwingMVC.Eventhandling.Events.*;
import Targy.*;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;
import java.util.HashMap;

/**
 * A mez�h�z tartoz� grafika megjelen�t�s��rt felel�s
 */
public class MezoView extends JPanel {

    /**
     * T�rolja a modellben hozz� tartoz� mez�t
     */
    private Mezo mezo;

    /**
     * A mez�n tal�lhat� entit�sok grafik�i
     */
    private HashMap<Object, JLabel> picLabels;

    /**
     * A mez�h�z tartoz� h�tt�rk�p
     */
    private BufferedImage backgroundImage;

    public MezoView(Mezo mezo){

        picLabels = new HashMap<>();

        this.mezo = mezo;
        setBackgroundImage();
        addMenuListener();

        GridLayout layout = new GridLayout();
        layout.setColumns(3);
        layout.setRows(3);
        layout.setHgap(3);
        layout.setVgap(3);
        setLayout(layout);

        drawEntities();
        legyenHo();

        setupMezoListener();
    }

    /**
     * Visszat�r a mez�vel
     */
    public Mezo getMezo() {

        return mezo;
    }

    /**
     * Kirajzolja a mezo �ltal t�rolt entit�sokat
     */
    private void drawEntities() {

        for(Karakter k : mezo.getKarakterek())
            addEntityImage(new EntityImage(k,false));

        if(mezo.getJegesmedve() != null)
            addEntityImage(new EntityImage(mezo.getJegesmedve(),false));
    }

    /**
     * Lek�rdezi, hogy tartalmazza-e az entit�shoz tartoz� grafik�t
     */
    public boolean containsEntity(Object entity){

        return picLabels.containsKey(entity);
    }

    /**
     * Kiemeli a megadott karaktert
     */
    public void highlightKarakter(Karakter karakter){

        if(picLabels.containsKey(karakter)) {
            removeEntityImage(karakter);
            addEntityImage(new EntityImage(karakter, true));
        }
        repaint();
        revalidate();
    }

    /**
     * Megsz�nteti a megadott karakter kiemel�s�t
     */
    public void removeHighlightKarakter(Karakter karakter){

        if(picLabels.containsKey(karakter)) {
            removeEntityImage(karakter);
            addEntityImage(new EntityImage(karakter, false));
        }
        repaint();
        revalidate();
    }

    /**
     * Be�ll�tja a h�tt�rk�pet a tartalmazott mez� alapj�n
     */
    private void setBackgroundImage(){

        URL path = mezo.getClass().getResource(mezo.getClass().getSimpleName() + ".png");

        try { backgroundImage = ImageIO.read(path); }
        catch (IOException e) { System.out.println("A f�jl nem tal�lhat�: '" + path + "'");}
        setPreferredSize(new Dimension(backgroundImage.getWidth(), backgroundImage.getHeight()));
        repaint();
        revalidate();
    }

    /**
     * Be�ll�tja a h�t�rk�pet a megadott mez�t�pus alapj�n
     */
    public void setBackgroundImage(Object mezotipus){

        URL path = mezotipus.getClass().getResource(mezotipus.getClass().getSimpleName() + ".png");

        try { backgroundImage = ImageIO.read(path); }
        catch (IOException e) { System.out.println("A f�jl nem tal�lhat�: '" + path + "'");}
        setPreferredSize(new Dimension(backgroundImage.getWidth(), backgroundImage.getHeight()));
        repaint();
        revalidate();
    }

    /**
     * Elle�rzi, hogy havasnak kell-e lennie a mez�nek,
     * �s ha igen, akkor rak r� egy r�teg havat, valamint elt�nteti a t�rgyat
     */
    private void legyenHo(){

        if(mezo.getHoreteg() != 0){

            URL path = getClass().getResource("Ho.png");

            try { backgroundImage = ImageIO.read(path); }
            catch (IOException e) { System.out.println("A f�jl nem tal�lhat�: '" + path + "'");}
            setPreferredSize(new Dimension(backgroundImage.getWidth(), backgroundImage.getHeight()));

            if(!mezo.getClass().equals(Lyuk.class)) {

                Targy targy = ((Jegtabla) mezo).getTargy();
                if (targy != null)
                    removeEntityImage(targy);
            }
            repaint();
            revalidate();
        }

        else{
            setBackgroundImage(mezo);

            if(mezo.getKapacitas() != 0) {
                if(!picLabels.containsKey(((Jegtabla) mezo).getTargy())) {

                    Targy targy = ((Jegtabla) mezo).getTargy();
                    if (targy != null)
                        addEntityImage(new EntityImage(targy,false));
                }
            }
        }
    }

    /**
     * Fel�ldefini�l�s. Megrajzolja a h�tteret
     */
    @Override
    protected void paintComponent(Graphics g) {

        super.paintComponent(g);
        g.drawImage(backgroundImage , 0, 0, null);
    }

    /**
     * Hozz�ad a mezoView-hoz egy entit�snak a grafik�j�t
     */
    private void addEntityImage(EntityImage image){

        JLabel picLabel = new JLabel(new ImageIcon(image.getImage()));
        picLabels.putIfAbsent(image.getEntity(), picLabel);
        add(picLabel);
    }

    /**
     * Kit�rli egy entit�s grafik�j�t a mezoView-b�l
     */
    private void removeEntityImage(Object entity){

        if(picLabels.get(entity) != null) {

            remove(picLabels.get(entity));
            picLabels.remove(entity);
        }
    }

    private void addMenuListener(){

        MezoView view = this;

        MouseListener listener = new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {

                if(SwingUtilities.isRightMouseButton(e)) {

                    MezoMenu menu = new MezoMenu(view);
                    menu.show(e.getComponent(), e.getX(), e.getY());
                }
            }

            @Override
            public void mousePressed(MouseEvent e) { }

            @Override
            public void mouseReleased(MouseEvent e) { }

            @Override
            public void mouseEntered(MouseEvent e) { }

            @Override
            public void mouseExited(MouseEvent e) { }
        };

        addMouseListener(listener);
    }

    /**
     * Be�ll�tja a mezoView-hoz tarttoz� listenert, ami a model �ltatl k�ld�tt esem�nyekre reag�l
     */
    private void setupMezoListener(){

        MezoEventListener mezoEventListener = new MezoEventListener() {

            /**
             * A mez� �tfordul�s�ra reag�l
             */
            @Override
            public void atfordult(AtfordulasEvent event) {

                if (mezo.equals(event.getSource()))
                    setBackgroundImage();

            }

            /**
             * A mez�n val� �s�sra reag�l
             */
            @Override
            public void astak(AsasEvent event) {

                if(((Karakter)event.getSource()).getMezo().equals(mezo)) {

                    legyenHo();
                    repaint();
                    revalidate();
                }
            }

            /**
             * A mz�n val� �p�t�sre reag�l
             */
            @Override
            public void epites(EpitesEvent event) {

                if(event.getSource().equals(mezo))
                    addEntityImage(new EntityImage(event.epulet,false));

                repaint();
                revalidate();
            }

            /**
             * A kutat� k�pesss�ghaszn�lat�ra reag�l
             */
            @Override
            public void kutatoKepesseg(KutatoKepessegEvent event) {

                if(event.celpont.equals(mezo))
                    JOptionPane.showMessageDialog(getParent(), "A mezo kapacitasa: " + event.kapacitas + ".", "Kutato", JOptionPane.PLAIN_MESSAGE);
            }

            /**
             * A karakter l�p�s�re reag�l
             */
            @Override
            public void leptek(LepesEvent event) {

                if (mezo.equals(event.honnan)) {

                    removeEntityImage(event.getSource());
                    repaint();
                    revalidate();
                }

                else  if(mezo.equals(event.hova)) {

                    addEntityImage(new EntityImage(event.getSource(),false));
                    repaint();
                    revalidate();
                }
            }

            /**
             * A t�rgyfelv�telre reag�l
             */
            @Override
            public void targyfelvetel(TargyfelvetelEvent event) {

                if(((Karakter)event.getSource()).getMezo().equals(mezo)) {

                    removeEntityImage(event.felvettTargy);
                    JOptionPane.showMessageDialog(getParent(), "A(z) " + event.felvettTargy.tipus() + " felv�ve.", "T�rgyfelv�tel" , JOptionPane.PLAIN_MESSAGE);

                    repaint();
                    revalidate();
                }
            }

            /**
             * A viharra reag�l
             */
            @Override
            public void vihar(ViharEvent event) {

                legyenHo();
                if(mezo.getKapacitas() > 0)
                    if(picLabels.containsKey(((Jegtabla)mezo).getEpulet()))
                        removeEntityImage(((Jegtabla)mezo).getEpulet());
            }

            /**
             * Egy t�rgy haszn�lat�ra reag�l
             */
            @Override
            public void targyhasznalat(TargyhasznalatEvent event) {

                if(((Targy)event.getSource()).tipus().equals(Targytipus.ELELEM) && event.karakter.getMezo().equals(mezo))
                    JOptionPane.showMessageDialog(getParent(), "Az elelem felhasznalva. (lehet, hoy ink�bb a medv�nek kellett volna adni)", "Kajasz�net" , JOptionPane.PLAIN_MESSAGE);
            }
        };

        Controller.getInstance().addMezoEventListener(mezoEventListener);
    }
}
