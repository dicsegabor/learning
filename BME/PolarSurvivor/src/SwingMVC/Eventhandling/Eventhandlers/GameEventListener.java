package SwingMVC.Eventhandling.Eventhandlers;

import SwingMVC.Eventhandling.Events.*;

import java.util.EventListener;

/**
 * A j�t�k fut�sa sor�n felmer�l� eventek kezel�s��rt felel�s.
 * Olyan eventekre kell itt gondolni, amik nem felt�tlen a mez�kh�z k�t�denek,
 * hanem ink�bb a j�t�k eg�sz�hez.
 */
public interface GameEventListener extends EventListener {

    /**
     * A karakter k�r�nek a v�g�re figyel, �s az ehhez tartoz� eventtel h�vja meg.
     * @param event A k�r v�g�hez tartoz� event
     */
    void karakterKorvege(KarakterKorvegeEvent event);

    /**
     * Az �sszes karakter k�r�nek a v�g�re figyel, �s az ehhez tartoz� eventtel h�vja meg.
     * @param event A �sszes karakter k�r�nek v�g�hez tartoz� event
     */
    void korvege(KorvegeEvent event);

    /**
     * A j�t�k v�g�re figyel, �s az ehhez tartoz� eventtel h�vja meg.
     * @param event A j�t�k v�g�hez tartoz� event
     */
    void jatekVege(JatekvegeEvent event);

    /**
     * Ezen kereszt�l lehet �zenentet k�ldeni a felhaszn�l�nak
     * @param event UzenetEvent
     */
    void uzenetEvent(UzenetEvent event);

    /**
     * A karakter �llapotva�ltoz�s�ra figyel
     * @param event KarakterStatusUpdateEvent
     */
    void statusUpdate(KarakterStatusUpdateEvent event);
}
