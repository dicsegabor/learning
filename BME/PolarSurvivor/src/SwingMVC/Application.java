package SwingMVC;

import SwingMVC.Controller.Controller;
import SwingMVC.View.GameBoard;

/**
 * Elind�tja a gameBoardot, valamint hozz�rendeli a controllerhez
 */
public class Application {

    public static void main(String[] args){

        GameBoard gameBoard = new GameBoard();
        Controller.getInstance().addGameBoard(gameBoard);
        gameBoard.start();
    }
}
