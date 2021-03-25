package com.company;

import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;

public class PaymentData {
    SimpleIntegerProperty id;
    SimpleDoubleProperty monthlyAmount;
    SimpleDoubleProperty loanBodyAmount;
    SimpleDoubleProperty percentAmount;
    SimpleDoubleProperty leftAmount;

    public PaymentData(int id, double monthlyAmount, double loanBodyAmount, double percentAmount, double leftAmount) {
        this.id = new SimpleIntegerProperty(id);
        this.loanBodyAmount = new SimpleDoubleProperty(loanBodyAmount);
        this.monthlyAmount = new SimpleDoubleProperty(monthlyAmount);
        this.percentAmount = new SimpleDoubleProperty(percentAmount);
        this.leftAmount = new SimpleDoubleProperty(leftAmount);
    }

    public int getId(){return this.id.get();};
    public void setId(int id){this.id.set(id);}

    public double getMonthlyAmount(){return this.monthlyAmount.get();}
    public void setMonthlyAmount(double monthlyAmount){this.monthlyAmount.set(monthlyAmount);}

    public double getLoanBodyAmount(){return this.loanBodyAmount.get();}
    public void setLoanBodyAmount(double loanBodyAmount){this.loanBodyAmount.set(loanBodyAmount);}

    public double getPercentAmount(){return this.percentAmount.get();}
    public void setPercentAmount(double percentAmount){this.percentAmount.set(percentAmount);}

    public double getLeftAmount(){return this.leftAmount.get();}
    public void setLeftAmount(double leftAmount){this.leftAmount.set(leftAmount);}
}
