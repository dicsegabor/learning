package IO;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Regebbi fajta beolvasashoz kell.
 */
public class Reader {

    Scanner sc;

    public Reader(String fileName) {

        try { sc = new Scanner(new File("Saved Boards\\" + fileName + ".txt")); }
        catch (FileNotFoundException e) { System.out.println("File not found!"); }
    }

    public String[] getBoardLayout() {

        String line = "";

        while(sc.hasNext())
            line += sc.nextLine();

        sc.close();

        return line.split(" ");
    }
}
