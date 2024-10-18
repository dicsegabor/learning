package IO;

import Controls.Board;

import java.io.*;

/**
 * A tabla kimenteset es beolvasasat kezeli.
 */
public class BoardIOHandler {

    public static void save(Board board, String fileName){

        try{

            FileOutputStream file = new FileOutputStream("Saved Boards\\" + fileName + ".HEX");
            ObjectOutputStream out = new ObjectOutputStream(file);

            out.writeObject(board);

            out.close();
            file.close();
        }

        catch(IOException ex){

            System.out.println("IOException is caught");
        }
    }

    public static Board load(String fileName){

        Board board = null;

        try{

            FileInputStream file = new FileInputStream("Saved Boards\\" + fileName + ".HEX");
            ObjectInputStream in = new ObjectInputStream(file);

            board = new Board((Board)in.readObject());

            in.close();
            file.close();
        }

        catch(IOException ex){

            System.out.println("IOException is caught");
        }

        catch(ClassNotFoundException ex){

            System.out.println("ClassNotFoundException is caught");
        }

        return board;
    }
}
