package SwingMVC.Controller;

import Mezo.Mezo;
import Mozgathato.Eszkimo;
import Mozgathato.Karakter;
import Mozgathato.Kutato;
import SwingMVC.Eventhandling.Eventhandlers.GameEventListener;
import SwingMVC.Eventhandling.Eventhandlers.MezoEventListener;
import SwingMVC.Eventhandling.Events.*;
import SwingMVC.Model.Model;
import SwingMVC.View.GameBoard;

import javax.swing.*;
import javax.swing.event.EventListenerList;

/**
 * Singleton Controller
 * A view �s model k�zti �sszek�ttet�st val�s�tja meg
 */
public class Controller {

    private static Controller instance;
    /**
     * Az j�t�k �llapot�t tartalmaz� Model p�ld�ny
     */
    private Model model;
    /**
     * A jelenleg soron l�v� karakter modellbeli megfelel�je
     */
    private Karakter activeKarakter;
    /**
     * A view, amit a felhasz�l� l�t
     */
    private GameBoard gameBoard;
    /**
     * A j�t�k fut�s�t jelz� v�ltoz�
     */
    private boolean running;
    /**
     * Jelzi, hogy a p�lyabet�lt�s random vagy el�re elk�sz�tett p�ly�val t�rt�njen
     */
    private boolean randomMap;

    /**
     * Az esem�nyekre feliratkoz� EventListenerek list�ja
     */
    private EventListenerList listenerList;

    /**
     * A Controller p�ld�ny lek�rdez�se
     * @return A Controller p�ld�ny
     */
    public static Controller getInstance() {

        if(instance == null)
            return new Controller();

        return instance;
    }

    /**
     * A Controller singleton inicializ�l�sa
     */
    public Controller(){

        instance = this;

        running = true;
        randomMap = false;
        listenerList = new EventListenerList();
        // �j model l�trehoz�sa
        model = new Model();
        // a soron k�vetkez� karakter lek�r�se a modellb�l
        activeKarakter = model.getKarakter(0);

        // Az esem�nykezel�k beregisztr�l�sa
        addGameEventListener();
    }

    /**
     * Az adatokat tartalmaz� modell
     * @return A haszn�latban l�v� modell
     */
    public Model getModel() {

        return model;
    }

    /**
     * A jelenleg soron l�v� karakter a modellb�l
     * @return A soron l�v� karakter
     */
    public Karakter getActiveKarakter() {

        return activeKarakter;
    }

    /**
     * Random gener�lt p�ly�t t�lts�n-e be
     * @param isRandom A random p�lyabet�lt�st jelz� boolean
     */
    public void setMap(boolean isRandom){

        randomMap = isRandom;
    }

    /**
     * Felveszi a view-t k�pez� GameBoardot
     * @param gameBoard A megjelen�tend� GameBoard
     */
    public void addGameBoard(GameBoard gameBoard){

        this.gameBoard = gameBoard;
        // soron l�v� karakter kiemel�se
        gameBoard.highlightKarakter();
    }

    /**
     * �j j�t�k ind�t�sa
     */
    public void restart(){

        running = true;

        if(randomMap)
            model.generateRandomMap();
        else
            model.loadDefaultMap();

        activeKarakter = model.getKarakter(0);
        gameBoard.reset();
        gameBoard.repaint();
        gameBoard.revalidate();
    }

    /**
     *
     * @param mezo  A model a param�ter�l kapott mez�re l�pteti az akt�v karaktert.
     */
    public void lep(Mezo mezo){

        model.lep(activeKarakter, mezo);
    }

    /**
     * Akt�v karakter �s
     */
    public void as(){

        model.as(activeKarakter);
    }

    /**
     * Akt�v karakter t�rgyat felvesz.
     */
    public void targyatFelvesz(){

        model.targyatFelvesz(activeKarakter);
    }

    /**
     * Akt�v eszkimo karakter iglut �p�t
     */
    public void iglutEpit(){

        model.iglutEpit((Eszkimo)activeKarakter);
    }

    /**
     * Akt�v karakter s�trat �p�t.
     */
    public void satratEpit(){

        model.satratEpit(activeKarakter);
    }

    /**
     * �sszeszereli a karakter a nyer�shez sz�ks�ges t�rgyakat.
     */
    public void osszeszerel(){

        model.osszeszerel(activeKarakter);
    }

    /**
     * Az akt�v sarkkutat� karakter a param�ter�l kapott mez�t megvizsg�lja
     * @param mezo
     */
    public void jegetNez(Mezo mezo){

        model.jegetNez((Kutato) activeKarakter, mezo);
    }

        //EventHandling
    public void addMezoEventListener(MezoEventListener listener){

        listenerList.add(MezoEventListener.class, listener);
    }

    public void addGameEventListener(GameEventListener listener){

        listenerList.add(GameEventListener.class, listener);
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void atfordultEvent(AtfordulasEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).atfordult(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void lepesEvent(LepesEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).leptek(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void asasEvent(AsasEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).astak(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void epitesEvent(EpitesEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).epites(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void kutatoKepessegEvent(KutatoKepessegEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).kutatoKepesseg(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void targyfelvetelEvent(TargyfelvetelEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).targyfelvetel(eventObject);
        }
    }

    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void targyhasznalatEvent(TargyhasznalatEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).targyhasznalat(eventObject);
        }
    }
    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */

    public void viharEvent(ViharEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == MezoEventListener.class)
                ((MezoEventListener)listeners[i + 1]).vihar(eventObject);
        }
    }

    /**
     * A f�ggv�ny �rtes�ti a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void karakterKorvege(KarakterKorvegeEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == GameEventListener.class)
                ((GameEventListener)listeners[i + 1]).karakterKorvege(eventObject);
        }
    }
    /**
     * A f�ggv�nyek �rtes�tik a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */

    public void korvege(KorvegeEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == GameEventListener.class)
                ((GameEventListener)listeners[i + 1]).korvege(eventObject);
        }
    }

    /**
     * A f�ggv�nyek �rtes�tik a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void jatekVege(JatekvegeEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == GameEventListener.class)
                ((GameEventListener)listeners[i + 1]).jatekVege(eventObject);
        }
    }
    /**
     * A f�ggv�nyek �rtes�tik a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void uzenet(UzenetEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == GameEventListener.class)
                ((GameEventListener)listeners[i + 1]).uzenetEvent(eventObject);
        }
    }
    /**
     * A f�ggv�nyek �rtes�tik a listenereket a param�terben megadott eventr�l.
     * @param eventObject
     */
    public void statusUpdate(KarakterStatusUpdateEvent eventObject){

        Object[] listeners = listenerList.getListenerList();
        for(int i = 0; i < listeners.length; i += 2){

            if(listeners[i] == GameEventListener.class)
                ((GameEventListener)listeners[i + 1]).statusUpdate(eventObject);
        }
    }

    private void addGameEventListener(){

        GameEventListener gameEventListener = new GameEventListener() {

            @Override
            public void karakterKorvege(KarakterKorvegeEvent event) {

                gameBoard.removeHighlightKarakter();
                activeKarakter = model.getNextKarakter(activeKarakter);
                gameBoard.highlightKarakter();

                statusUpdate(new KarakterStatusUpdateEvent(this));
            }

            @Override
            public void korvege(KorvegeEvent event) {}

            @Override
            public void jatekVege(JatekvegeEvent event) {

                if(running) {

                    JOptionPane.showMessageDialog(gameBoard, event.uzenet, "V�ge a j�t�knak", JOptionPane.PLAIN_MESSAGE);
                    running = false;
                    restart();
                }
            }

            @Override
            public void uzenetEvent(UzenetEvent event) {

                JOptionPane.showMessageDialog(gameBoard, event.uzenet, "�zenet" , JOptionPane.PLAIN_MESSAGE);
            }

            @Override
            public void statusUpdate(KarakterStatusUpdateEvent event) {

                gameBoard.setStatusBarText();
                gameBoard.repaint();
                gameBoard.revalidate();
            }
        };

        addGameEventListener(gameEventListener);
    }
}
