package com.company;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

import java.util.*;

public class LoanTableView extends LoanView{
    private final Label label;
    private final TableView table;

    private TableColumn monthCol;
    private TableColumn monthlyAmountCol;
    private TableColumn loanBodyCol;
    private TableColumn percentCol;
    private TableColumn leftAmountCol;

    private Button getTxtButton;

    private TextField filterFromTextFiled;
    private TextField filterToTextField;
    private Button filterButton;

    private ObservableList<PaymentData> data;
    ArrayList<PaymentData> dataArrayList;

    public LoanTableView(){
        super();
        label = new Label("Paskolos grąžinimo lentelė");
        label.setFont(new Font("Arial", 20));

        table = new TableView();
        table.setEditable(true);

        monthCol = new TableColumn("Mėnuo");
        monthCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        monthlyAmountCol = new TableColumn("Mokėti");
        monthlyAmountCol.setCellValueFactory(new PropertyValueFactory<>("monthlyAmount"));

        loanBodyCol = new TableColumn("Kredito kūnas");
        loanBodyCol.setCellValueFactory(new PropertyValueFactory<>("loanBodyAmount"));

        percentCol = new TableColumn("Kredito procentas");
        percentCol.setCellValueFactory(new PropertyValueFactory<>("percentAmount"));

        leftAmountCol = new TableColumn("Liko mokėti");
        leftAmountCol.setCellValueFactory(new PropertyValueFactory<>("leftAmount"));

        data = FXCollections.observableArrayList();
        table.setItems(data);

        table.getColumns().addAll(monthCol, monthlyAmountCol,  loanBodyCol, percentCol, leftAmountCol);

        getTxtButton = new Button("Parsisiųsti ataskaitą txt formatu");

        getTxtButton.setOnAction(event -> {
            ArrayList<PaymentData> tableData = new ArrayList<>(data);
            LoanUtils.loadTxt(tableData);
        });

        Text filterFromText = new Text("Filtruoti pagal mėnesį nuo");
        Text filterToText = new Text("iki");
        filterFromTextFiled = new TextField();
        filterToTextField = new TextField();
        filterButton = new Button("Filtruoti");

        filterFromTextFiled.setMaxWidth(50);
        filterToTextField.setMaxWidth(50);

        filterButton.setOnAction(event -> {
            if(isDataCorrect()){
                int from = Integer.parseInt(filterFromTextFiled.getText());
                int to = Integer.parseInt(filterToTextField.getText());

                if(to < from){
                    int buff = from;
                    from = to;
                    to = buff;
                }

                data.clear();

                int finalFrom = from;
                int finalTo = to;
                dataArrayList.forEach((n) -> {
                    if(n.getId() >= finalFrom && n.getId() <= finalTo){
                        data.add(n);
                    }
                });
            }
        });

        HBox filterBox = new HBox(filterFromText,filterFromTextFiled,filterToText,filterToTextField,filterButton);
        filterBox.setSpacing(5);
        filterBox.setAlignment(Pos.BASELINE_LEFT);

        root.getChildren().addAll(label, table, filterBox, getTxtButton);
    }

    private void showErrorMessage(String message){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Klaida");
        alert.setHeaderText("Įvesties klaida");
        alert.setContentText(message);

        alert.showAndWait();
    }

    Boolean isDataCorrect(){
        try{
            int test1 = Integer.parseInt(filterFromTextFiled.getText());
            int test2 = Integer.parseInt(filterToTextField.getText());
            if(test1 < 0 || test2 < 0){
                showErrorMessage("Filtravimo parametrai negali būti neigiami");
                return false;
            }
        } catch (NumberFormatException exception){
            showErrorMessage("Filtravimo parametrai įvesti netisingai");
            return false;
        }

        return true;
    }

    @Override
    public void fillData(ArrayList<PaymentData> monthlyPayment){
        dataArrayList = monthlyPayment;
        data.addAll(monthlyPayment);
    }
}
