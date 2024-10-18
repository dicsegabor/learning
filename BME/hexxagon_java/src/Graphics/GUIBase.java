package Graphics;

import Controls.Coordinate;
import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.stage.Screen;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

/**
 * Ez az osztaly segit felbontasfuggetlenul megjeleniteni a programot.
 * Attributumai:
 * primaryScreenBounds: A kepernyo jelenlegi hatarai.
 * widthRatio, heightRatio: mennyivel kissebb, vagy nagyobb, mint az eredeti grafika.
 * backgroundX, backgroundY: mennyivel van eltolodva a hatter.
 */
public class GUIBase {

    protected Rectangle2D primaryScreenBounds;
    protected double widthRatio, heightRatio, backgroundX, backgroundY;

    public GUIBase() {

        primaryScreenBounds = Screen.getPrimary().getBounds();
        loadBackGround("Void");
    }

    /**
     * Betolt egy kepet a kapott fajlnev alapjan es lekezeli az Exception-t.
     * @param fileName A fajlnev, ami alapja betolti a kepet.
     * @return Image
     */
    protected Image loadImage(String fileName) {

        try { return new Image(new FileInputStream("Graphics\\1920x1080\\" + fileName + ".png")); }
        catch (FileNotFoundException e) { System.out.println("File \"" + fileName + ".png\" not found!"); }

        return null;
    }

    /**
     * Beillesti a hatterbe a kepet. Megfeleloen meretezi, valamint kozepre igazitja.
     * @param fileName A fajlnev, ami alapja betolti a kepet.
     * @return ImageView
     */
    protected ImageView loadBackGround(String fileName){

        Image image = loadImage(fileName);
        ImageView imageView = new ImageView(image);

        imageView.setFitHeight(primaryScreenBounds.getHeight());
        imageView.setFitWidth(primaryScreenBounds.getWidth());

        centerImage(imageView);

        widthRatio = imageView.getLayoutBounds().getWidth() / 1728;
        heightRatio = imageView.getLayoutBounds().getHeight() / 1080;

        return imageView;
    }

    /**
     * Kozpre igazitja a kapott kepet.
     * @param imageView A kepnezet amit kzepre igazit.
     */
    protected void centerImage(ImageView imageView){

        double ratioX = imageView.getFitWidth() / imageView.getImage().getWidth();
        double ratioY = imageView.getFitHeight() / imageView.getImage().getHeight();

        double ratio = Math.min(ratioX, ratioY);

        double w = imageView.getImage().getWidth() * ratio;
        double h = imageView.getImage().getHeight() * ratio;

        imageView.setX((imageView.getFitWidth() - w) / 2);
        imageView.setY((imageView.getFitHeight() - h) / 2);
        backgroundX = imageView.getX();
        backgroundY = imageView.getY();

        imageView.setPreserveRatio(true);
    }

    /**
     * Gombot keszit kapott fajlnev, ami a hattere lesz, valamint helyzete alapjan, amit az eredeti grafika alapjan adunk meg.
     * @param fileName A fajlnev, ami alapja betolti a kepet.
     * @param place A pont ahova teszi a gombot.
     * @return Button
     */
    protected Button makeButton(String fileName, Point2D place){

        Button button = imageToButton(fileName);

        placeNode(button, place);

        return button;
    }

    /**
     * Kapott fajnevbol betoltott kepet beallitja a gomb hatterenek, valamint megfeleloen meretezi a gombot a felbontashoz viszonyitva.
     * @param fileName A fajlnev, ami alapja betolti a kepet.
     * @return Button
     */
    protected Button imageToButton(String fileName) {

        Button bt = new Button();

        Image image = loadImage(fileName);

        bt.setBackground(new Background(imageToBackgroundImage(image)));
        bt.setMinSize(image.getWidth() * widthRatio, image.getHeight() * heightRatio);

        return bt;
    }

    /**
     * A gomb hatterehez alakitja at a kepet.
     * @param image A kep, amit atalakit.
     * @return BackgroundImage
     */
    protected BackgroundImage imageToBackgroundImage(Image image) {

        BackgroundSize size = new BackgroundSize(image.getWidth() * widthRatio, image.getHeight() * heightRatio, false, false, false, false);
        return new BackgroundImage(image, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT, size);
    }

    /**
     * A kapott objektumot a kapott heyre helyezi el, de hozzaigazitja a felbontashoz.
     * @param node Az objektum, amit elhelyez.
     * @param place A pont ahova teszi az objektumot.
     */
    protected void placeNode(Node node, Point2D place){

        node.setLayoutX(backgroundX + place.getX() * widthRatio);
        node.setLayoutY(backgroundY + place.getY() * heightRatio);
    }

    /**
     * Atalitja egy kapott gomb hatteret a kapott fajlnev alapjan.
     * @param button A gomb aminek kicsereli a hatteret.
     * @param fileName A fajlnev, ami alapja betolti a kepet.
     */
    protected void setButtonBackground(Button button, String fileName) {

        button.setBackground(new Background(imageToBackgroundImage(loadImage(fileName))));
    }
}
