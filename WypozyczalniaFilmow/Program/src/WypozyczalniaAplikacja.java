import java.io.IOException;
import java.sql.SQLException;
import javax.swing.JFrame;

/*
 *  Klasa WypozyczalniaAplikacja
 *
 *  Klasa zawiera kilka pól protected ktore sa dziedziczone przez inne klasy okienkowe.
 *  Klasa wczytuje dane z pliku oraz inicjalizuje menu glowne.
 *
 *  Autor: Adam Filipowicz
 *  Data: 31 maja 2017 r.
 */
public class WypozyczalniaAplikacja extends javax.swing.JFrame {
    protected static MenuGlowne glowneMenu;
    
    /**
     * Stworzenie obiektu klasy Wypozyczalnia.
     */
    protected static Wypozyczalnia wypozyczalnia = new Wypozyczalnia();
    
    /**
     * Klasa JOptionUserDialog implementuje metody umozliwiajace
     * wyswietlanie komunikatow oraz wczytywanie danych w oknach
     * dialogowych wyswietlanych przez klase JOptionPane.
     */
    protected static JOptionUserDialog UI = new JOptionUserDialog();
    
    /**
     * Nazwa pliku do zapisu i wczytywania danych.
     */
    protected static final String DATA_FILE_NAME = "WYPOZYCZALNIA.BIN";
    
    /**
     * Wiadomosc powitalna wyswietlana na rozpoczeciu aplikacji.
     */
    private static final String GREETING_MESSAGE =
            "Program Wypozyczalnia\n" +
                    "Autor: Adam Filipowicz\n" +
                    "Data: 28 maja 2017 r.\n";
    
    /**
     * @param args the command line arguments
     * @throws java.sql.SQLException
     */
    public static void main(String[] args) throws IOException, InterruptedException{
        try{
            wypozyczalnia.initializeConnection();
        }
        catch(SQLException e){
            UI.printErrorMessage(e.getMessage());
            return;
        }
        UI.printMessage(GREETING_MESSAGE);
        glowneMenu = new MenuGlowne(wypozyczalnia);
        glowneMenu.setResizable(false);
        glowneMenu.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        glowneMenu.setSize(800,500);
        glowneMenu.setLocation(500,250);
        glowneMenu.setVisible(true);
    }
    
}
