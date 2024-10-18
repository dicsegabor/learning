package Graphics;

import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.control.Button;

/**
 * A jatek vegen hivodik meg. Megmutatja a gyoztest.
 */
public class End extends GUIBase {
    
    private Group root;
    
    public End(Controller controller){
        
        root = new Group();
        
        root.getChildren().add(loadBackGround("Void"));

        Button endButton = null;

        switch (controller.gameBoard.getWinner()) {

            case RED:
                endButton = makeButton("Red Won", new Point2D(533, 323));
                break;

            case BLUE:
                endButton = makeButton("Blue Won", new Point2D(533, 323));
                break;

            default:
                endButton = makeButton("Tie", new Point2D(533, 323));
                break;
        }

        endButton.setOnAction(value -> { controller.primaryStage.getScene().setRoot(controller.menu.getRoot()); controller.gameBoard.reset(); } );
        root.getChildren().add(endButton);
    }

    public Group getRoot() {

        return root;
    }
}
