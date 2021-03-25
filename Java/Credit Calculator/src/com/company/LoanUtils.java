package com.company;

import javafx.scene.control.Alert;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

///TODO no output in LoadTxt function, the method should throw IO exception

public class LoanUtils {
    static ArrayList<PaymentData> annuity(double amount, int years, int months, double percent){
        int monthsAmount = (years * 12) + months;

        ArrayList<PaymentData> result = new ArrayList<>(monthsAmount);

        double monthlyPercent = percent / 100.0 / 12.0;
        double monthlyPayment = Math.ceil(amount * (monthlyPercent + (monthlyPercent / (Math.pow((1 + monthlyPercent), monthsAmount) - 1)) ));
        double leftAmount = (monthlyPayment * monthsAmount);
        double leftCreditAmount = amount;
        double percentAmount;
        double loanBodyAmount;

        for(int i = 0; i < monthsAmount; ++i){
            percentAmount = Math.ceil(leftCreditAmount * monthlyPercent);
            leftAmount -= monthlyPayment;
            loanBodyAmount = monthlyPayment - percentAmount;
            leftCreditAmount -= loanBodyAmount;
            result.add(new PaymentData(i + 1, monthlyPayment, loanBodyAmount, percentAmount, leftAmount));
        }

        return result;
    }

    static ArrayList<PaymentData> linear(double amount, int years, int months, double percent){
        int monthsAmount = (years * 12) + months;

        ArrayList<PaymentData> result = new ArrayList<>(monthsAmount);

        double loanBody = Math.ceil(amount / (double)monthsAmount);
        double yearPercent = percent / 100.0;
        double percentAmount;
        double monthlyPayment;
        double leftAmount = amount;
        double leftCreditAmount = Math.ceil(amount +
                (yearPercent *
                        (monthsAmount * amount - (
                                ((monthsAmount * monthsAmount - monthsAmount) / 2 * amount) / monthsAmount
                                ))) / 12);

        for(int i = 0; i < monthsAmount; ++i){
            percentAmount = Math.ceil((leftAmount * yearPercent) / 12);
            monthlyPayment = loanBody + percentAmount;
            leftAmount -= loanBody;
            if(leftAmount <= 0)leftAmount = 0;
            leftCreditAmount -= monthlyPayment;
            if(leftCreditAmount <= 0)leftCreditAmount = 0;
            result.add(new PaymentData(i + 1,monthlyPayment,loanBody,percentAmount,leftCreditAmount));
        }

        return result;
    }

    static void loadTxt(ArrayList<PaymentData> data){
        try{
            File file = new File("table.txt");
            file.createNewFile();

            FileWriter fileWriter = new FileWriter("table.txt");
            fileWriter.write(String.format("%-15s %-20s %-20s %-20s %-20s\n","Mėnuo","Mokėti",
                    "Kredito kūnas","Kredito procentas","Liko mokėti"));

            data.forEach((n) -> {
                try {
                    fileWriter.write(String.format("%-15d %-20.2f %-20.2f %-20.2f %-20.2f\n",
                            n.getId(),n.getMonthlyAmount(),n.getLoanBodyAmount(),n.getPercentAmount(),n.getLeftAmount()));
                } catch (IOException exception) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Klaida");
                    alert.setHeaderText("Failo sukurimo klaida");
                    alert.setContentText("Neįmanoma sukurti failą (2)");

                    alert.showAndWait();

                    return;
                }
            });

            fileWriter.close();

            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Pranešimas");
            alert.setHeaderText("Failas sėkmingai sukurtas");
            alert.setContentText("Failas yra toje pačioje direktorijoje kur programa");

            alert.showAndWait();

        } catch (IOException exception){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Klaida");
            alert.setHeaderText("Failo sukurimo klaida");
            alert.setContentText("Neįmanoma sukurti failą (1)");

            alert.showAndWait();
        }
    }
}