/*
 *  Klasa JOptionUserDialog
 *
 *  Biblioteka metod do realizacji
 *  dialogu z uzytkownikiem w aplikacjach
 *  z interfejsem okienkowym.
 *
 *  Autor: Adam Filipowicz
 *  Data: 28 maja 2017 r.
 */

import javax.swing.JOptionPane;

class JOptionUserDialog {

    private static final String ERROR_MESSAGE = "Nieprawidlowe dane!\nSprobuj jeszcze raz.";

    private StringBuilder messageBuilder = new StringBuilder();

    void printMessage(String message) {
        messageBuilder.append(message);
        messageBuilder.append("\n");
    }

    void printInfoMessage(String message) {
        messageBuilder.append(message);
        messageBuilder.append("\n");
        JOptionPane.showMessageDialog(null, messageBuilder);
        messageBuilder = new StringBuilder();
    }

    void printErrorMessage(String message) {
        messageBuilder.append(message);
        messageBuilder.append("\n");
        JOptionPane.showMessageDialog(null, messageBuilder, "",JOptionPane.ERROR_MESSAGE);
        messageBuilder = new StringBuilder();
    }

    String enterString(String prompt) {
        messageBuilder.append(prompt);
        String message = JOptionPane.showInputDialog(messageBuilder);
        messageBuilder = new StringBuilder();
        if (message!=null) return message;
        return "";
    }

    int enterInt(String prompt) {
        boolean isError;
        int i = 0;
        do{
            isError = false;
            try{
                i = Integer.parseInt(enterString(prompt));
            } catch(NumberFormatException e){
                printErrorMessage(ERROR_MESSAGE);
                isError = true;
            }
        }while(isError);
        return i;
    }

    double enterDouble(String prompt) {
        boolean isError;
        double d = 0;
        do{
            isError = false;
            try{
                d = Double.parseDouble(enterString(prompt));
            } catch(NumberFormatException e){
                printErrorMessage(ERROR_MESSAGE);
                isError = true;
            }
        }while(isError);
        return d;
    }

}