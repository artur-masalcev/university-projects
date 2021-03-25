package com.company;

import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public abstract class LoanView {
    protected final Scene scene; //Scene of the view, includes root pane by default
    protected VBox root; //Root pane used to add other elements in it

    public LoanView(){
        root = new VBox();
        root.setSpacing(5);
        root.setPadding(new Insets(10, 10, 10, 10));
        root.setStyle("-fx-background-color: #dddddd");

        scene = new Scene(root, 800,800);
    }

    public Scene getScene(){
        return this.scene;
    }

    abstract public void fillData(ArrayList<PaymentData> monthlyPayment);
}
