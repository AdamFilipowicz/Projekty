/*
 *  Klasa Wypozyczenie
 *
 *  Autor: Adam Filipowicz
 *  Data: 2 sierpnia 2017 r.
 */
public class Wypozyczenie {
    private String nazwaKlienta;
    private String nazwaFilmu;
    private double cena;
    private int ilosc;
    private String dataWypozyczenia;
    private String dataZwrotu;
    private String opis;
    private boolean zwrocony;
    
    public Wypozyczenie(String nazwaKlienta, String nazwaFilmu, double cena, int ilosc, String dataWypozyczenia, String dataZwrotu, String opis, boolean zwrocony){
        this.nazwaKlienta = nazwaKlienta;
        this.nazwaFilmu = nazwaFilmu;
        this.cena = cena;
        this.ilosc = ilosc;
        this.dataWypozyczenia = dataWypozyczenia;
        this.dataZwrotu = dataZwrotu;
        this.opis = opis;
        this.zwrocony = zwrocony;
    }
    
    public String getNazwaKlienta(){
        return nazwaKlienta;
    }
    
    public String getNazwaFilmu(){
        return nazwaFilmu;
    }
    
    public String getDataWypozyczenia(){
        return dataWypozyczenia;
    }
    
    public String getDataZwrotu(){
        return dataZwrotu;
    }
    
    public String getOpis(){
        return opis;
    }
    
    public double getCena(){
        return cena;
    }
    
    public int getIlosc(){
        return ilosc;
    }
    
    public boolean getZwrocony(){
        return zwrocony;
    }
    
}
