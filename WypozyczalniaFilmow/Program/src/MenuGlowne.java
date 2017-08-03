import javax.swing.JFrame;

/*
 *  Klasa MenuGlowne
 *
 *  Klasa pozwala na wybor menu klienta lub sprzedawcy oraz na wyjscie z aplikacji
 *  i zapisanie danych do pliku.
 *
 *  Autor: Adam Filipowicz
 *  Data: 31 maja 2017 r.
 */
        
public class MenuGlowne extends javax.swing.JFrame {
    protected static MenuKlient klientMenu;
    protected static MenuSprzedawca sprzedawcaMenu;
    protected Wypozyczalnia wypozyczalnia;
    protected static JOptionUserDialog UI = new JOptionUserDialog();
    protected static final String DATA_FILE_NAME = "WYPOZYCZALNIA.BIN";
    
    private MenuGlowne() {}
    
    public MenuGlowne(Wypozyczalnia wypozyczalnia) {
        initComponents();
        this.wypozyczalnia = wypozyczalnia;
    }


    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        klientButton = new javax.swing.JButton();
        sprzedawcaButton = new javax.swing.JButton();
        wrocButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Wypozyczalnia filmow");
        setPreferredSize(new java.awt.Dimension(800, 600));

        klientButton.setFont(new java.awt.Font("Arial", 1, 24)); // NOI18N
        klientButton.setText("Menu klienta");
        klientButton.setToolTipText("");
        klientButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                klientButtonActionPerformed(evt);
            }
        });

        sprzedawcaButton.setFont(new java.awt.Font("Arial", 1, 24)); // NOI18N
        sprzedawcaButton.setText("Menu sprzedawcy");
        sprzedawcaButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sprzedawcaButtonActionPerformed(evt);
            }
        });

        wrocButton.setText("Wyjdz z aplikacji");
        wrocButton.setToolTipText("");
        wrocButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                wrocButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(46, 46, 46)
                .addComponent(klientButton, javax.swing.GroupLayout.PREFERRED_SIZE, 306, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 89, Short.MAX_VALUE)
                .addComponent(sprzedawcaButton, javax.swing.GroupLayout.PREFERRED_SIZE, 306, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(53, 53, 53))
            .addGroup(layout.createSequentialGroup()
                .addGap(321, 321, 321)
                .addComponent(wrocButton)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(120, 120, 120)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(klientButton, javax.swing.GroupLayout.PREFERRED_SIZE, 197, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(sprzedawcaButton, javax.swing.GroupLayout.PREFERRED_SIZE, 197, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 127, Short.MAX_VALUE)
                .addComponent(wrocButton, javax.swing.GroupLayout.PREFERRED_SIZE, 56, javax.swing.GroupLayout.PREFERRED_SIZE))
        );

        klientButton.getAccessibleContext().setAccessibleName("");
        sprzedawcaButton.getAccessibleContext().setAccessibleName("");

        getAccessibleContext().setAccessibleName("frame1");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * Metoda po nacisnieciu guzika przechodzi do menu klienta.
     * @param evt - nacisniecie guzika powoduje przejscie do menu klienta
     */
    private void klientButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_klientButtonActionPerformed
        klientMenu = new MenuKlient(wypozyczalnia);
        klientMenu.setResizable(false);
        klientMenu.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        klientMenu.setSize(800,500);
        klientMenu.setLocation(500,250);
        klientMenu.setVisible(true);
        this.dispose();
    }//GEN-LAST:event_klientButtonActionPerformed

    /**
     * Metoda po nacisnieciu guzika przechodzi do menu sprzedawcy.
     * @param evt - nacisniecie guzika powoduje przejscie do menu sprzedawcy
     */
    private void sprzedawcaButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sprzedawcaButtonActionPerformed
        sprzedawcaMenu = new MenuSprzedawca(wypozyczalnia);
        sprzedawcaMenu.setResizable(false);
        sprzedawcaMenu.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        sprzedawcaMenu.setSize(800,500);
        sprzedawcaMenu.setLocation(500,250);
        sprzedawcaMenu.setVisible(true);
        this.setVisible(false);
        UI.printErrorMessage("\nUWAGA - MENU SPRZEDAWCY\nNIEAUTORYZOWANE WEJSCIE MOZE BYC KARANE");
    }//GEN-LAST:event_sprzedawcaButtonActionPerformed

    /**
     * Metoda po nacisnieciu guzika zapisuje dane do pliku i wychodzi z aplikacji.
     * @param evt - nacisniecie guzika powoduje zapis danych do pliku i wyjście z aplikacji
     */
    private void wrocButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_wrocButtonActionPerformed
        UI.printInfoMessage("\nProgram zakonczyl dzialanie!");
        System.exit(0);
    }//GEN-LAST:event_wrocButtonActionPerformed
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new MenuGlowne().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton klientButton;
    private javax.swing.JButton sprzedawcaButton;
    private javax.swing.JButton wrocButton;
    // End of variables declaration//GEN-END:variables
}
