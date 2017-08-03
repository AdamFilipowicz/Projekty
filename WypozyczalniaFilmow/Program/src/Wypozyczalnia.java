/*
 *  Klasa Wypozyczalnia
 *
 *  Klasa zawiera wiele metod uzywanych w klasach okienkowych.
 *  Klasa bazuje na obiektach klasy Konto, Film i Wypozyczenie.
 *  Klasa posiada takze listy w ktorych sa one przechowywane.
 *
 *  Autor: Adam Filipowicz
 *  Data: 28 maja 2017 r.
 */

import java.io.IOException;
import java.io.Serializable;
import java.sql.Date;
import java.text.ParseException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement; 
import java.sql.ResultSet; 
import java.util.concurrent.TimeUnit;




class Wypozyczalnia implements Serializable {

    private static final long serialVersionUID = 1L;
    
    /**
     * Połączenie z bazą danych.
     */
    private Connection con;

    private Statement stmt;
    
    private ResultSet rs;

    /**
     * Metoda inicjalizuje połączenie z bazą danych.
     * @throws SQLException 
     */
    void initializeConnection() throws SQLException, IOException, InterruptedException{
        String host = "jdbc:derby://localhost:1527/Wypozyczalnia";
        con = DriverManager.getConnection(host,"Adam","123");
    }

    /**
     * Metoda dodaje film o podanej nazwie do tablicy filmow.
     * @param nazwa - nazwa filmu do dodania
     * @param cena - cena filmu.
     * @param ilosc - ilosc filmu.
     * @param opis - opis filmu.
     * @throws Exception - wyjatek zglaszany, gdy nazwa filmu jest pusta lub gdy film juz istnieje
     */
    void dodajFilm(String nazwa, double cena, int ilosc, String opis) throws Exception{
        if(nazwa==null || nazwa.equals("")) throw(new Exception("Nazwa filmu nie moze byc pusta"));
        if(cena<=0) throw(new Exception("Bledna cena"));
        if(ilosc<=0) throw(new Exception("Bledna ilosc"));
        if(znajdzFilm(nazwa)) throw(new Exception("Film juz istnieje"));
        if(opis.equals("")) throw(new Exception("Opis nie moze byc pusty"));

        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.last();
        int id;
        if(rs.getRow()==0)
            id = 0;
        else
            id=rs.getInt("ID");
        rs.moveToInsertRow();
        rs.updateInt("ID", id + 1);
        rs.updateString("Nazwa", nazwa);
        rs.updateDouble("Cena", cena);
        rs.updateInt("Ilosc", ilosc);
        rs.updateString("Opis", opis);
        
        rs.insertRow();
             
        stmt.close();
        rs.close();
    }

    /**
     * Metoda wycofuje film o podanej nazwie z wypozyczalni (usuwa z tablicy)
     * @param nazwa - nazwa filmu do usuniecia
     * @throws Exception - wyjatek zglaszany, gdy nazwa filmu jest pusta lub bledna
     */
    void wycofajFilm(String nazwa) throws Exception{
        if(nazwa==null) throw(new Exception("Brak filmu"));

        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM";
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0 && !nazwa.equals(rs.getString("Nazwa"))){
            rs.next();
        }
        if(rs.getRow()==0) {
            stmt.close();
            rs.close();
            throw(new Exception("Nie znaleziono danego filmu"));
        }
        rs.deleteRow();
             
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda zmienia parametry filmu o podanej nazwie.
     * @param nazwa - nazwa filmu do dodania
     * @param cena - cena filmu.
     * @param ilosc - ilosc filmu.
     * @param opis - opis filmu.
     * @throws Exception - wyjatek zglaszany, gdy nazwa filmu jest pusta lub gdy film juz istnieje
     */
    void zmienFilm(String nazwa, double cena, int ilosc, String opis) throws Exception{
        if(nazwa==null || nazwa.equals("")) throw(new Exception("Nazwa filmu nie moze byc pusta"));
        if(cena<=0) throw(new Exception("Bledna cena"));
        if(ilosc<=0) throw(new Exception("Bledna ilosc"));
        if(!znajdzFilm(nazwa)) throw(new Exception("Brak filmu"));
        if(opis.equals("")) throw(new Exception("Opis nie moze byc pusty"));

        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))) {
                rs.updateDouble("Cena", cena);
                rs.updateInt("Ilosc", ilosc);
                rs.updateString("Opis", opis);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }

    /**
     * Metoda znajduje nazwe film o podanej nazwie na liscie filmow i zwraca go.
     * @param nazwa - nazwa wyszukiwanego filmu
     * @return Film - gdy film zostanie znaleziony na liscie
     * 		   null - gdy film nie zostanie znaleziony na liscie
     */
    boolean znajdzFilm(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))) {
                stmt.close();
                rs.close();
                return true;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return false;
    }
    /**
     * Metoda znajduje film o podanym indeksie na liscie filmow i zwraca jego nazwe.
     * @param index - indeks wyszukiwanego filmu
     * @return String - gdy film zostanie znaleziony na liscie
     * 		   null - gdy film nie zostanie znaleziony na liscie
     */
    String znajdzNazweFilmu(int index) throws SQLException{
        int i=0;
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(i==index) {
                String nazwaa = rs.getString("Nazwa");
                stmt.close();
                rs.close();
                return nazwaa;
            }
            i++;
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }
    
    /**
     * Metoda znajduje ilosc filmu o podanej nazwie na liscie filmow i zwraca ja.
     * @param nazwa - nazwa wyszukiwanego filmu
     * @return int - ilosc filmu gdy film zostanie znaleziony na liscie
     *         -1 - gdy film nie zostanie znaleziony na liscie
     */
    int znajdzIloscFilmu(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))) {
                int ilosc = rs.getInt("Ilosc");
                stmt.close();
                rs.close();
                return ilosc;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return -1;
    }

    /**
     * Metoda zwracajaca liste filmow jako String.
     * @return lista filmow jako String
     */
    String wypiszListeFilmow() throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        StringBuilder sb = new StringBuilder();
        int n = 0;
        rs.first();
        while(rs.getRow()!=0){
            if (n++ != 0) sb.append("\n");
            sb.append(String.format("Nazwa: %s. Cena: %.2f. Ilosc: %d. Opis: %s.", rs.getString("Nazwa"), rs.getDouble("Cena"), rs.getInt("Ilosc"), rs.getString("Opis")));
            rs.next();
        }
        stmt.close();
        rs.close();
        return sb.toString();
    }
    
    /**
     * Metoda zwiekszajaca ilosc filmu o podana ilosc. ( zwrocenie danej ilosci filmu )
     * @param iloscZwrocona - ilosc jaka chcemy dodac do ilosci naszego filmu.
     */
    void dodajIlosc(String nazwa, int iloscZwrocona) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateInt("Ilosc", rs.getInt("Ilosc") + iloscZwrocona);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda zmieniajaca ilosc filmu.
     * @param nowaIlosc - nowa ilosc filmu.
     */
    void zmienIlosc(String nazwa, int nowaIlosc) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateInt("Ilosc", nowaIlosc);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda ustawiajaca dana cene jako cene filmu.
     * @param nowaCena - cena jaka chcemy przypisac cenie filmu.
     */
    void setCena(String nazwa, double nowaCena) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateDouble("Cena", nowaCena);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda ustawiajaca dana opis jako opis filmu.
     * @param opis - podany opis filmu
     */
    void setOpis(String nazwa, String opis) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateString("Opis", opis);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda zwracajaca cene filmu.
     * @return cena - cena filmu.
     */
    double getCena(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                double cena = rs.getDouble("Cena");
                stmt.close();
                rs.close();
                return cena;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return 0;
    }
    
    /**
     * Metoda zwracajaca ilosc filmu.
     * @return ilosc - ilosc filmu.
     */
    int getIlosc(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                int ilosc = rs.getInt("Ilosc");
                stmt.close();
                rs.close();
                return ilosc;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return 0;
    }
    
    /**
     * Metoda zwracajaca opis filmu.
     * @return opisFilmu - opis filmu.
     */
    String getOpis(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                String opis = rs.getString("Opis");
                stmt.close();
                rs.close();
                return opis;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }
    
    /**
     * Metoda zmniejszajaca ilosc filmu o podana ilosc. ( wypozyczenie danej ilosci filmu przez klienta )
     * @param iloscWypozyczona - ilosc jaka chcemy odjac od ilosci naszego filmu.
     */
    void minusIlosc(String nazwa, int iloscWypozyczona) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM FILM"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateInt("Ilosc", rs.getInt("Ilosc") - iloscWypozyczona);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }


    /**
     * Metoda sprawdza czy istnieje juz sprzedawca (czy jakies konto jest juz utworzone).
     * @return true - gdy istnieje konto sprzedawcy
     * 		   false - gdy nie istnieje konto sprzedawcy
     */
    boolean sprawdzCzyIstniejeSprzedawca() throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        if(rs.getRow()==0){
            stmt.close();
            rs.close();
            return false;
        }
        
        stmt.close();
        rs.close();
        return true;
    }

    /**
     * Metoda sprawdza czy podane konto nalezy do sprzedawcy.
     * @param daneKonto - podane konto, do sprawdzenia
     * @return true - gdy podane konto faktycznie jest kontem sprzedawcy
     * 		   false - gdy podane konto nie jest kontem sprzedawcy
     */
    boolean sprawdzCzyKontoSprzedawcy(String nazwaKonta) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        if(rs.getRow()!=0 && nazwaKonta.equals(rs.getString("Nazwa"))){
            stmt.close();
            rs.close();
            return true;
        }
        stmt.close();
        rs.close();
        return false;
    }
    
    /**
     * Metoda dodaje konto sprzedawcy o podanej nazwie do tablicy kont.
     * @param nazwa - nazwa konta do dodania
     * @return obiekt Konto ktore zostalo dodane do tablicy kont
     * @throws Exception - wyjatek zglaszany, gdy nazwa konta jest pusta
     */
    void zalozKontoSprzedawcy(String nazwa, String haslo, String adres, String nazwisko) throws Exception {
        if (nazwa==null || nazwa.equals("")) throw(new Exception("Nazwa konta nie moze byc pusta"));
        if (haslo.equals("")) throw(new Exception("Haslo nie moze byc puste"));
        if (adres.equals("")) throw(new Exception("Adres nie moze byc pusty"));
        if (nazwisko.equals("")) throw(new Exception("Nazwisko nie moze byc puste"));
        
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        int id = 1;
        rs.moveToInsertRow();
        rs.updateInt("ID", id);
        rs.updateString("Nazwa", nazwa);
        rs.updateInt("Haslo", haslo.hashCode());
        rs.updateString("Adres", adres);
        rs.updateString("Nazwisko", nazwisko);
        
        rs.insertRow();
             
        stmt.close();
        rs.close();
    }

    /**
     * Metoda dodaje konto o podanej nazwie do tablicy kont.
     * @param nazwa - nazwa konta do dodania
     * @param haslo - haslo konta do dodania
     * @param adres - adres konta do dodania
     * @param nazwisko - nazwisko konta do dodania
     * @throws Exception - wyjatek zglaszany, gdy nazwa konta jest pusta lub gdy konto o podanej nazwie juz istnieje
     */
    void zalozKonto(String nazwa, String haslo, String adres, String nazwisko) throws Exception {
        if (nazwa==null || nazwa.equals("")) throw(new Exception("Nazwa konta nie moze byc pusta"));
        if (znajdzKonto(nazwa)!= null) throw(new Exception("Konto juz istnieje"));
        
        if (haslo.equals("")) throw(new Exception("Haslo nie moze byc puste"));
        if (adres.equals("")) throw(new Exception("Adres nie moze byc pusty"));
        if (nazwisko.equals("")) throw(new Exception("Nazwisko nie moze byc puste"));
        
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.last();
        int id = rs.getInt("ID");
        rs.moveToInsertRow();
        rs.updateInt("ID", id + 1);
        rs.updateString("Nazwa", nazwa);
        rs.updateInt("Haslo", haslo.hashCode());
        rs.updateString("Adres", adres);
        rs.updateString("Nazwisko", nazwisko);
        
        rs.insertRow();
             
        stmt.close();
        rs.close();
    }

    /**
     * Metoda usuwa podane konto (usuwa z tablicy)
     * @param konto - konto do usuniecia
     * @throws Exception - wyjatek zglaszany, gdy nazwa konta jest pusta
     */
    void usunKonto(String nazwa) throws Exception {
        if (nazwa==null || nazwa.equals("")) throw(new Exception("Nie podano nazwy konta"));
        
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO";
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0 && !nazwa.equals(rs.getString("Nazwa"))){
            rs.next();
        }
        if(rs.isAfterLast()) {
            stmt.close();
            rs.close();
            throw(new Exception("Nie znaleziono konta o podanej nazwie"));
        }
        rs.deleteRow();
             
        stmt.close();
        rs.close();
    }

    /**
     * Metoda znajduje konto o podanej nazwie na liscie kont i zwraca go.
     * @param nazwa - nazwa wyszukiwanego konta
     * @return nazwaKonta - gdy konto zostanie znalezione na liscie
     *          null - gdy konto nie zostanie znalezione na liscie
     */
    String znajdzKonto(String nazwa) throws Exception {
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))) {
                String nazwaa = rs.getString("Nazwa");
                stmt.close();
                rs.close();
                return nazwaa;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }

    /**
     * Metoda znajduje konto o podanej nazwie na liscie kont i zwraca go jesli podano poprawne haslo.
     * @param nazwa - nazwa wyszukiwanego konta
     * @param haslo - haslo wyszukiwanego konta
     * @return konto - gdy konto zostanie znalezione na liscie i haslo jest poprawne
     * 		   null - gdy konto nie zostanie znalezione na liscie lub/i gdy haslo jest niepoprawne
     */
    String znajdzKonto(String nazwa, String haslo) throws Exception {
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))) {
                if (haslo==null || haslo.hashCode()!=rs.getInt("Haslo")){
                    stmt.close();
                    rs.close();
                    throw new Exception("Bledne haslo");
                }
                String nazwaa = rs.getString("Nazwa");
                stmt.close();
                rs.close();
                return nazwaa;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }

    /**
     * Metoda zwracajaca liste kont jako String.
     * @return lista kont jako String
     */
    String listaKont() throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        StringBuilder sb = new StringBuilder();
        int n = 0;
        rs.first();
        while(rs.getRow()!=0){
            if (n++ != 0) sb.append("\n");
            sb.append(String.format("Nazwa: %s. Nazwisko: %s. Adres: %s.", rs.getString("Nazwa"), rs.getString("Nazwisko"), rs.getString("Adres")));
            rs.next();
        }
        stmt.close();
        rs.close();
        return sb.toString();
    }
    
    /**
     * Metoda przypisujaca atrybutowi adres podanego String'a.
     * @param adres - adres jaki chcemy ustawic dla naszego konta
     */
    void setAdres(String adres, String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateString("Adres", adres);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda przypisujaca atrybutowi nazwisko podanego String'a.
     * @param nazwisko - nazwisko jakie chcemy ustawic dla naszego konta
     */
    void setNazwisko(String nazwisko, String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                rs.updateString("Nazwisko", nazwisko);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda ustawiajaca nowe haslo pod warunkiem podania poprawnego starego hasla.
     * @param stareHaslo - stare haslo
     * @param noweHaslo - nowe haslo
     * @throws Exception - wyjatek zglaszany gdy stare haslo jest niepoprawne
     */
    void setHaslo(String stareHaslo, String noweHaslo, String nazwa) throws Exception {
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                if (stareHaslo==null || stareHaslo.hashCode()!=rs.getInt("Haslo")) throw new Exception("Bledne haslo");
                rs.updateInt("Haslo", noweHaslo.hashCode());
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }
    
    /**
     * Metoda sprawdzajaca czy podane haslo jest prawidlowe.
     * @param podaneHaslo - podane haslo do sprawdzenia
     * @return - true, jesli haslo jest poprawna
     * 		   - false, jesli haslo jest niepoprawne.
     */
    boolean sprawdzHaslo(String podaneHaslo, String nazwa) throws Exception {
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                if (podaneHaslo==null || podaneHaslo.hashCode()!=rs.getInt("Haslo")) return false;
                stmt.close();
                rs.close();
                return true;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        throw new Exception("Bledna nazwa konta");
    }
    
    /**
     * Metoda zwracajaca nazwisko.
     * @return nazwisko - nazwisko konta
     */
    String getNazwisko(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                String nazwisko = rs.getString("Nazwisko");
                stmt.close();
                rs.close();
                return nazwisko;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }
    
    /**
     * Metoda zwracajaca adres.
     * @return adres - adres konta
     */
    String getAdres(String nazwa) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM KONTO"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa"))){
                String adres = rs.getString("Adres");
                stmt.close();
                rs.close();
                return adres;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return null;
    }

    /**
     * Metoda dodaje wypozyczenie o podanych parametrach do historii wypozyczen.
     * @param nazwa - nazwa filmu
     * @param cena - cena filmu
     * @param ilosc - ilosc zakupionego filmu
     * @param nazwaKlienta - nazwa klienta ktory zakupil film
     */
    void dodajDoHistoriiWypozyczen(String nazwa, double cena, int ilosc, String nazwaKlienta, String opis, String dataWypozyczenia, String dataZwrotu) throws SQLException, ParseException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE"; 
        rs = stmt.executeQuery( SQL );
        
        rs.last();
        int id;
        if(rs.getRow()==0)
            id = 0;
        else
            id=rs.getInt("ID");
        rs.moveToInsertRow();
        rs.updateInt("ID", id + 1);
        rs.updateString("Nazwa", nazwa);
        rs.updateDouble("Cena", cena);
        rs.updateInt("Ilosc", ilosc);
        rs.updateString("Opis", opis);
        rs.updateString("Nazwa_Klienta", nazwaKlienta);
        rs.updateDate("Data_Wypozyczenia", Date.valueOf(dataWypozyczenia));
        rs.updateDate("Data_Zwrotu", Date.valueOf(dataZwrotu));
        rs.updateBoolean("Zwrocony", false);
        
        rs.insertRow();
             
        stmt.close();
        rs.close();
    }

    /**
     * Metoda zwracajaca historie wypozyczen dla danego konta jako String.
     * @return historia wypozyczen dla danego konta jako String
     */
    String wyswietlHistorieWypozyczenKlienta(String nazwaKonta) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE"; 
        rs = stmt.executeQuery( SQL );
        
        StringBuilder sb = new StringBuilder();
        int n = 0;
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(nazwaKonta.equals(rs.getString("Nazwa_Klienta"))){
                if (n++ != 0) sb.append("\n");
                String zwrocony;
                if(rs.getBoolean("Zwrocony")) zwrocony="Film zwrocony";
                else            zwrocony="Film NIE zwrocony";
                sb.append(String.format("Nazwa: %s. Cena: %.2f. Ilosc: %d. Opis: %s. Klient: %s. Data wypozyczenia: %s. Data zwrotu: %s. %s", rs.getString("Nazwa"), rs.getDouble("Cena"), rs.getInt("Ilosc"), rs.getString("Opis"), rs.getString("Nazwa_Klienta"), rs.getString("Data_Wypozyczenia"), rs.getString("Data_Zwrotu"), zwrocony));
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return sb.toString();
    }

    /**
     * Metoda zwracajaca historie wypozyczen dla danego konta jako String.
     * @return historia wypozyczen dla danego konta jako String
     */
    String wyswietlHistorieWypozyczen() throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE"; 
        rs = stmt.executeQuery( SQL );
        
        StringBuilder sb = new StringBuilder();
        int n = 0;
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if (n++ != 0) sb.append("\n");
            String zwrocony;
            if(rs.getBoolean("Zwrocony")) zwrocony="Film zwrocony";
            else            zwrocony="Film NIE zwrocony";
            sb.append(String.format("Nazwa: %s. Cena: %.2f. Ilosc: %d. Opis: %s. Klient: %s. Data wypozyczenia: %s. Data zwrotu: %s. %s", rs.getString("Nazwa"), rs.getDouble("Cena"), rs.getInt("Ilosc"), rs.getString("Opis"), rs.getString("Nazwa_Klienta"), rs.getString("Data_Wypozyczenia"), rs.getString("Data_Zwrotu"), zwrocony));
            rs.next();
        }
        stmt.close();
        rs.close();
        return sb.toString();
    }

    /**
     * Metoda znajduje wypozyczenie o podanej nazwie, cenie, ilosci, kliencie i dacie wypozyczenia na liscie wypozyczen i zwraca go.
     * @param nazwa - nazwa wyszukiwanego filmu
     * @param cena - cena wyszukiwanego filmu
     * @param ilosc - ilosc wyszukiwanego filmu
     * @param klient - klient ktory wypozyczyl wyszukiwany film
     * @param dataWypozyczenia - data wypozyczenia wyszukiwanego filmu
     * @return 1 - gdy wypozyczenie zostanie znalezione na liscie
     *          0 - gdy wypozyczenie nie zostanie znalezione na liscie
     */
    int znajdzWypozyczenie(String nazwa, double cena, int ilosc, String klient, String dataWypozyczenia) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        while(rs.getRow()!=0){
            if(nazwa.equals(rs.getString("Nazwa")) && cena==rs.getDouble("Cena") && ilosc==rs.getInt("Ilosc") && klient.equals(rs.getString("Nazwa_Klienta")) && dataWypozyczenia.equals(rs.getString("Data_Wypozyczenia"))) {
                int id = rs.getInt("ID");
                stmt.close();
                rs.close();
                return id;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
        return 0;
    }
    
    /**
     * Metoda znajduje wypozyczenie o podanym numerze indeksu i zwraca go.
     * @param id - indeks wyszukiwanego wypozyczenia
     * @return Wypozyczenie - gdy wypozyczenie zostanie znalezione na liscie
     * 		   null - gdy wypozyczenie nie zostanie znalezione na liscie
     */
    Wypozyczenie znajdzWypozyczenieCale(int id) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE WHERE ID=" + id; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        if(rs.getRow()!=0){
            Wypozyczenie wyp = new Wypozyczenie(rs.getString("Nazwa_Klienta"), rs.getString("Nazwa"), rs.getDouble("Cena"), rs.getInt("Ilosc"), rs.getString("Data_Wypozyczenia"), rs.getString("Data_Zwrotu"), rs.getString("Opis"), rs.getBoolean("Zwrocony"));
            stmt.close();
            rs.close();
            return wyp;
        }
        stmt.close();
        rs.close();
        return null;
    }
    
    /**
     * Metoda uzywana przez sprzedawce. Ustawia film jako zwrocony.
     */
    void setZwrocony(int numerWypozyczenia) throws SQLException{
        stmt = con.createStatement( ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE ); 
        String SQL = "SELECT * FROM WYPOŻYCZENIE"; 
        rs = stmt.executeQuery( SQL );
        
        rs.first();
        rs.next();
        rs.previous();
        while(rs.getRow()!=0){
            if(numerWypozyczenia==rs.getInt("ID")){
                rs.updateBoolean("Zwrocony", true);
                rs.updateRow();
                stmt.close();
                rs.close();
                return;
            }
            rs.next();
        }
        stmt.close();
        rs.close();
    }

}