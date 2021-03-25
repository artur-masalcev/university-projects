package com.company;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.util.ArrayList;

public class Main extends Application {
    private Scene form;

    private Button graphButton;
    private TextField amountTextField;
    private ToggleGroup scheduleGroup;
    private RadioButton annuityRadioButton;
    private RadioButton linearRadioButton;
    private TextField percentageTextField;
    private Button tableButton;
    private TextField yearsTextField;
    private TextField monthsTextField;

    public Main(){
        //Amount//
        Text amountText = new Text("Paskolos suma:");
        amountTextField = new TextField();
        Text euroSignText = new Text("€");

        amountTextField.setMaxWidth(100);

        HBox amountBox = new HBox(amountTextField, euroSignText);
        amountBox.setPadding(new Insets(0,0,10,0));
        amountBox.setAlignment(Pos.BASELINE_LEFT);
        amountBox.setSpacing(3);

        //Term//
        Text termText = new Text("Paskolos terminas:");
        Text yearsText = new Text("metų");
        Text monthsText = new Text("mėnesių");
        yearsTextField = new TextField();
        monthsTextField = new TextField();

        yearsTextField.setPrefSize(40,20);
        monthsTextField.setPrefSize(40,20);

        HBox termBox = new HBox(yearsTextField,yearsText,monthsTextField,monthsText);
        termBox.setPadding(new Insets(0,0,10,0));
        termBox.setSpacing(5);
        termBox.setAlignment(Pos.BASELINE_LEFT);

        //Schedule//
        Text scheduleText = new Text("Paskolos grąžinimo grafikas:");
        annuityRadioButton = new RadioButton("anuiteto");
        linearRadioButton = new RadioButton("linijinis");
        scheduleGroup = new ToggleGroup();

        annuityRadioButton.setToggleGroup(scheduleGroup);
        linearRadioButton.setToggleGroup(scheduleGroup);

        HBox scheduleBox = new HBox(annuityRadioButton,linearRadioButton);
        scheduleBox.setPadding(new Insets(0,0,10,0));
        scheduleBox.setSpacing(10);

        //Percentage//
        Text percentageText = new Text("Metinis procentas:");
        percentageTextField = new TextField();
        Text percentSignText = new Text("%");

        percentageTextField.setMaxWidth(40);

        HBox percentageBox = new HBox(percentageTextField,percentSignText);
        percentageBox.setPadding(new Insets(0,0,10,0));
        percentageBox.setAlignment(Pos.BASELINE_LEFT);
        percentageBox.setSpacing(3);

        //Buttons//
        graphButton = new Button("Braižyti grafiką");

        tableButton = new Button("Rodyti lentelę");

        HBox buttonsBox = new HBox(graphButton, tableButton);
        buttonsBox.setPadding(new Insets(70,0,0,0));
        buttonsBox.setSpacing(5);

        //Root//
        VBox root = new VBox(amountText, amountBox, termText, termBox,
                scheduleText, scheduleBox,percentageText,percentageBox, buttonsBox);
        root.setStyle("-fx-background-color: #dddddd");
        root.setSpacing(10);
        root.setPadding(new Insets(5,0,0,10));

        form = new Scene(root,250, 400);
    }

    private void showErrorMessage(String message){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Klaida");
        alert.setHeaderText("Įvesties klaida");
        alert.setContentText(message);

        alert.showAndWait();
    }

    private Boolean isDataCorrect(){
        //Check whether fields are null//
        if(amountTextField.getText().equals("")){
            showErrorMessage("Paskolos suma įvesta netisingai");
            return false;
        }
        else if(yearsTextField.getText().equals("")){
            showErrorMessage("Kredito terminas įvestas neteisingai");
            return false;
        }
        else if(monthsTextField.getText().equals("")){
            showErrorMessage("Kredito terminas įvestas neteisingai");
            return false;
        }
        else if(scheduleGroup.getSelectedToggle() == null){
            showErrorMessage("Pasirinkite gražinimo grafiką");
            return false;
        }
        else if(percentageTextField.getText().equals("")){
            showErrorMessage("Metinis procentas įvestas neteisingai");
            return false;
        }

        //Check whether fields contain only valid format numbers and check whether all numbers are positive//
        try{
            double test = Double.parseDouble(amountTextField.getText());
            if(test == 0){
                showErrorMessage("Paskolos suma negali būti nuliu");
                return false;
            }
            else if(test < 0){
                showErrorMessage("Paskolos suma negali būti neigiama");
                return false;
            }
        } catch (NumberFormatException exception){
            showErrorMessage("Paskolos suma įvesta netisingai");
            return false;
        }

        try{
            int test1 = Integer.parseInt(yearsTextField.getText());
            int test2 = Integer.parseInt(monthsTextField.getText());
            if(test1 < 0 || test2 < 0){
                showErrorMessage("Paskolos terminas negali būti neigiamas");
                return false;
            }
            else if(test1 == 0 && test2 == 0){
                showErrorMessage("Paskolos terminas negali būti lygus nuliui");
                return false;
            }
        } catch (NumberFormatException exception){
            showErrorMessage("Paskolos teriminas įvestas netisingai");
            return false;
        }

        try{
            double test = Double.parseDouble(percentageTextField.getText());
            if(test == 0){
                showErrorMessage("Paskolos procentas negali būti nuliu");
                return false;
            }
            else if(test < 0){
                showErrorMessage("Paskolos procentas negali būti neigiamas");
                return false;
            }
        } catch (NumberFormatException exception){
            showErrorMessage("Metinis procentas įvestas netisingai");
            return false;
        }

        return true;
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Skaičiuoklė");
        primaryStage.setResizable(false);
        primaryStage.setScene(form);
        primaryStage.show();

        tableButton.setOnAction((event) -> {
            if(isDataCorrect()){
                LoanTableView tableView = new LoanTableView();

                RadioButton checked = (RadioButton) scheduleGroup.getSelectedToggle();
                ArrayList<PaymentData> data;

                if (checked.getText() == "anuiteto") {
                    data = LoanUtils.annuity(Double.parseDouble(amountTextField.getText()),
                            Integer.parseInt(yearsTextField.getText()),
                            Integer.parseInt(monthsTextField.getText()),
                                    Double.parseDouble(percentageTextField.getText()));
                } else {
                    data = LoanUtils.linear(Double.parseDouble(amountTextField.getText()),
                            Integer.parseInt(yearsTextField.getText()),
                            Integer.parseInt(monthsTextField.getText()),
                            Double.parseDouble(percentageTextField.getText()));
                }

                tableView.fillData(data);

                Stage tableStage = new Stage();
                tableStage.setScene(tableView.getScene());
                tableStage.setTitle("Paskolos grąžinimo lentelė");
                tableStage.setWidth(600);
                tableStage.setHeight(400);
                tableStage.show();
            }
        });

        graphButton.setOnAction(event -> {
            if(isDataCorrect()){
                LoanGraphView graphView = new LoanGraphView();

                RadioButton checked = (RadioButton) scheduleGroup.getSelectedToggle();
                ArrayList<PaymentData> data;

                if (checked.getText() == "anuiteto") {
                    data = LoanUtils.annuity(Double.parseDouble(amountTextField.getText()),
                            Integer.parseInt(yearsTextField.getText()),
                            Integer.parseInt(monthsTextField.getText()),
                            Double.parseDouble(percentageTextField.getText()));
                } else {
                    data = LoanUtils.linear(Double.parseDouble(amountTextField.getText()),
                            Integer.parseInt(yearsTextField.getText()),
                            Integer.parseInt(monthsTextField.getText()),
                            Double.parseDouble(percentageTextField.getText()));
                }

                graphView.fillData(data);

                Stage graphStage = new Stage();
                graphStage.setScene(graphView.getScene());
                graphStage.setTitle("Paskolos grąžinimo grafikas");
                graphStage.setWidth(600);
                graphStage.setHeight(400);
                graphStage.show();
            }
        });
    }
}
