package SwingMVC.View;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

/**
 * A jegtablakon megjeleno enitasok kepeit tarolja, illetve kezeli azok betolteset.
 * F� funkci�ja az, hogy megadhatunk neki egy objectet �s bet�lti az ahoz tartoz� k�pet.
 */
public class EntityImage {

    /**
     * A k�p, ami az objektumhoz tartozik.
     * Automatikusan bet�lt�dik a l�trehoz�skor
     */
    private BufferedImage image;

    /**
     * Az object, amihez a k�p tartozik.
     * Ide csak olyanokat adjunk meg, amikhez van k�p�nk.
     */
    private Object entity;

    public EntityImage(Object entity, boolean highlighted){

        this.entity = entity;
        getGraphics(entity, highlighted);
    }

    /**
     * Lek�rdezi a megadot entit�shoz tartoz� grafik�t, az oszt�ly neve alapj�n.
     * @param entity Az entit�s
     * @param highlighted Ki van-e jel�lve. (csak karakter eset�n m�k�dik)
     */
    private void getGraphics(Object entity, boolean highlighted){

        URL path;

        //Ha ki van jel�lve a karakter, akkor a kijel�lt k�et t�lti be hozzz�
        if(!highlighted)
            path = entity.getClass().getResource(entity.getClass().getSimpleName() + ".png");

        //Ha nincs kijel�lve a karakter akkor a nem kjel�t k�pet t�lti be hozz�
        else
            path = entity.getClass().getResource("H" + entity.getClass().getSimpleName() + ".png");

        //Az ImageIO seg�ts�g�vel beolvassuk a k�pet.
        try { image = ImageIO.read(path); }
        catch (IOException e) { System.out.println("A f�jl nem tal�lhat�: '" + path + "'");}
    }

    /**
     * Visszat�r az entit�ssal,
     * �gy el�rhetj�k a k�p modellbeli emgfelel�j�t.
     */
    public Object getEntity() {

        return entity;
    }

    /**
     * Visszat�r a t�rolt k�ppel,
     * �gy el�rhetj�k az objektum view-beli megfelel�j�t.
     */
    public BufferedImage getImage() {

        return image;
    }
}
